/**
  ******************************************************************************
  * file           : example.c
  * brief          : The responder's application handling SYNC/FOLLOW_UP time
  *                  synchronization over FDCAN with HAL API.
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "example.h"

#include <string.h> /* importing memset function */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Timer resolution: one timer tick equals 125 ns. */
#define TIMER_TICK_NS     (125ULL)
/* One second expressed in nanoseconds. */
#define ONE_SECOND_NS     (1000000000ULL)

/* Private macro -------------------------------------------------------------*/
#define GET_32BIT_FROM_BYTES(ARRAY) \
  ((((uint32_t)(ARRAY)[3U]) << 24U) | (((uint32_t)(ARRAY)[2U]) << 16U) \
   | (((uint32_t)(ARRAY)[1U]) << 8U) | (uint32_t)(ARRAY)[0U])
/* Convert nanoseconds to whole seconds. */
#define NANOSEC_TO_SEC(VAL)   ((uint32_t)((VAL) / ONE_SECOND_NS))
/* Convert nanoseconds to timer ticks. */
#define NANOSEC_TO_TIM(VAL)   ((uint32_t)((VAL) / TIMER_TICK_NS))
/* Header identifier */
#define SYNC_FRAME_ID     (0x111U)

/* Private variables ---------------------------------------------------------*/
hal_fdcan_handle_t *pFDCAN; /* Pointer referencing the FDCAN handle from the generated code */
hal_tim_handle_t *pTIM;     /* Pointer referencing the TIM handle from the generated code */

/* Interrupt-driven state flags and software time base. */
volatile uint8_t SyncCaptureCompleted = 0U;
volatile uint8_t SyncFrameReceived = 0U;
volatile uint8_t FollowUpFrameReceived = 0U;
volatile uint32_t UpdateCallbackCount = 0U;

/* Controller timestamp seconds part from the SYNC payload. */
uint32_t ReceivedSync = 0U;
/* Controller timestamp nanoseconds part from the Follow-Up payload. */
uint32_t ReceivedFollowUpNs = 0U;

/* Captured Receive EOF timestamp ticks for the received SYNC frame. */
uint8_t ReceiveStamp[4U] = {0U};

/* Private functions prototype -----------------------------------------------*/
static void InputCaptureCallback(hal_tim_handle_t *, hal_tim_channel_t);
static void UpdateCallback(hal_tim_handle_t *);
static void ReceiveFifo0Callback(hal_fdcan_handle_t *hfdcan,
                                 uint32_t receive_fifo_it);
static app_status_t StartTimestampCapture(void);
static app_status_t StopTimestampCapture(void);
static void ApplySynchronizedTime(void);
static void ResetSyncState(void);
static uint64_t TimToNanosec(uint64_t timer_value);
static uint64_t GetCapturedTime(const uint8_t *timestamp_capture);
static uint64_t GetCurrentTime(void);

app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  hal_status_t hal_status;

  /** ########## Step 1 ##########
    * The init of the FDCAN and TIM instances is triggered by the applicative code.
    */
  pFDCAN = mx_example_fdcan_init();
  if (pFDCAN == NULL)
  {
    goto _app_init_exit;
  }

  pTIM = mx_example_tim_init();
  if (pTIM == NULL)
  {
    goto _app_init_exit;
  }

  hal_status = HAL_FDCAN_RegisterRxFifo0Callback(pFDCAN, ReceiveFifo0Callback);
  if (hal_status != HAL_OK)
  {
    goto _app_init_exit;
  }

  hal_status = HAL_TIM_RegisterInputCaptureCallback(pTIM, InputCaptureCallback);
  if (hal_status != HAL_OK)
  {
    goto _app_init_exit;
  }

  hal_status = HAL_TIM_RegisterUpdateCallback(pTIM, UpdateCallback);
  if (hal_status != HAL_OK)
  {
    goto _app_init_exit;
  }

  hal_status = HAL_TIM_Start_IT(pTIM);
  if (hal_status != HAL_OK)
  {
    goto _app_init_exit;
  }

  hal_status = HAL_FDCAN_Start(pFDCAN);
  if (hal_status != HAL_OK)
  {
    goto _app_init_exit;
  }

  PRINTF("[INFO] Client: initialization COMPLETED. Waiting for SYNC/FOLLOW_UP frames.\n");
  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
}


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR; /* Function return status. */

  /** ########## Step 2 ##########
    * Start timestamp capture phase for the Receive channel.
    */
  if (StartTimestampCapture() != EXEC_STATUS_OK)
  {
    goto _app_process_exit;
  }

  /** ########## Step 3 ##########
    * Wait until both SYNC and Follow-Up frames are received.
    */
  /* Wait until both SYNC and Follow-Up frames are received. */
  while ((SyncFrameReceived == 0U) || (FollowUpFrameReceived == 0U))
  {
    __WFI();
  }

  /* Wait until the Receive EOF timestamp capture is complete. */
  while (SyncCaptureCompleted == 0U)
  {
    __WFI();
  }

  /** ########## Step 4 ##########
    * End capture window and apply synchronized time update.
    */
  if (StopTimestampCapture() != EXEC_STATUS_OK)
  {
    goto _app_process_exit;
  }

  /* Apply synchronized time correction from received SYNC/FOLLOW_UP information. */
  ApplySynchronizedTime();

  PRINTF("[INFO] Client: received SYNC (seconds = %" PRIu32 "), "
         "FOLLOW_UP (nanoseconds = %" PRIu32 "). Synchronized time = %" PRIu64 " ns.\n",
         ReceivedSync, ReceivedFollowUpNs, GetCurrentTime());

  /* Reset state for the next synchronization sequence. */
  ResetSyncState();

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
}


app_status_t app_deinit(void)
{
  /* Stop timer interrupt-driven operation. */
  HAL_TIM_Stop_IT(pTIM);
  /* Release timer resources. */
  mx_example_tim_deinit();

  /* Stop FDCAN peripheral activity. */
  HAL_FDCAN_Stop(pFDCAN);
  /* Release FDCAN resources. */
  mx_example_fdcan_deinit();

  /* Signal clean shutdown. */
  return EXEC_STATUS_OK;
}


static app_status_t StartTimestampCapture(void)
{
  hal_status_t hal_status;

  /* Capture Rx EOF on channel 1 for the incoming SYNC frame. */
  hal_status = HAL_TIM_IC_StartChannel_DMA(pTIM,
                                           HAL_TIM_CHANNEL,
                                           ReceiveStamp,
                                           sizeof(uint32_t));
  if (hal_status != HAL_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  return EXEC_STATUS_OK;
}


static app_status_t StopTimestampCapture(void)
{
  hal_status_t hal_status;

  hal_status = HAL_TIM_IC_StopChannel_DMA(pTIM, HAL_TIM_CHANNEL);
  if (hal_status != HAL_OK)
  {
    /* Stop capture DMA on channel 1. */
    return EXEC_STATUS_ERROR;
  }

  return EXEC_STATUS_OK;
}


static void ApplySynchronizedTime(void)
{
  uint64_t adjusted_responder_time_ns;
  uint64_t controller_time_ns;
  uint32_t adjusted_seconds;

  /*
    * Rebuild controller absolute timestamp from two frames:
    * - SYNC provides the seconds part.
    * - Follow-Up provides the nanoseconds part.
    * Keeping both avoids up to ~1 second of synchronization error.
    */
  controller_time_ns = ((uint64_t)ReceivedSync * ONE_SECOND_NS)
                       + (uint64_t)ReceivedFollowUpNs;

  /* Compute corrected local absolute time from captured RX timestamp. */
  adjusted_responder_time_ns = (GetCurrentTime() - GetCapturedTime(ReceiveStamp))
                               + controller_time_ns;

  /* Update software seconds counter and hardware timer counter. */
  adjusted_seconds = NANOSEC_TO_SEC(adjusted_responder_time_ns);
  UpdateCallbackCount = adjusted_seconds;
  HAL_TIM_SetCounter(
    pTIM,
    NANOSEC_TO_TIM(
      adjusted_responder_time_ns - ((uint64_t)adjusted_seconds * ONE_SECOND_NS)));
}


static void ResetSyncState(void)
{
  SyncCaptureCompleted = 0U;
  SyncFrameReceived = 0U;
  FollowUpFrameReceived = 0U;
  ReceivedSync = 0U;
  ReceivedFollowUpNs = 0U;
  memset(ReceiveStamp, 0x00, sizeof(ReceiveStamp));
}


static void InputCaptureCallback(hal_tim_handle_t *htim,
                                 hal_tim_channel_t channel)
{
  (void)htim;

  if (channel == HAL_TIM_CHANNEL)
  {
    /* Mark Receive EOF timestamp capture completion. */
    SyncCaptureCompleted = 1U;
  }
}


static void UpdateCallback(hal_tim_handle_t *htim)
{
  (void)htim;

  /* Count timer overflows (seconds accumulation). */
  UpdateCallbackCount++;
}


static void ReceiveFifo0Callback(hal_fdcan_handle_t *hfdcan,
                                 uint32_t receive_fifo_it)
{
  hal_fdcan_rx_header_t receive_header;
  uint8_t receive_buffer[64U] = {0U};

  if ((receive_fifo_it & HAL_FDCAN_IT_RX_FIFO_0_NEW_MSG) == 0U)
  {
    /* Ignore callback calls that are not new-message events. */
    return;
  }

  /* Pop the newly received frame from Receive FIFO0. */
  HAL_FDCAN_GetReceivedMessage(
    hfdcan,
    HAL_FDCAN_RX_FIFO_0,
    &receive_header,
    receive_buffer);

  /* Process only the SYNC and Follow-Up frames used by this example. */
  if ((receive_header.b.identifier == SYNC_FRAME_ID)
      && (receive_header.b.identifier_type == HAL_FDCAN_ID_STANDARD)
      && (receive_header.b.frame_type == HAL_FDCAN_FRAME_DATA)
      && (receive_header.b.data_length
          == HAL_FDCAN_DATA_LEN_CAN_FDCAN_8_BYTE))
  {
    if (receive_buffer[0U] == 0x10U)
    {
      /* Store controller timestamp seconds part. */
      ReceivedSync = GET_32BIT_FROM_BYTES(&receive_buffer[4]);
      SyncFrameReceived = 1U;
    }
    else if (receive_buffer[0U] == 0x18U)
    {
      /* Store controller timestamp nanoseconds part. */
      ReceivedFollowUpNs = GET_32BIT_FROM_BYTES(&receive_buffer[4]);
      FollowUpFrameReceived = 1U;
    }
  }
}


static uint64_t TimToNanosec(uint64_t timer_value)
{
  return timer_value * TIMER_TICK_NS;
}


static uint64_t GetCapturedTime(const uint8_t *timestamp_capture)
{
  /* Build absolute time from captured timer ticks and overflow seconds. */
  return TimToNanosec(GET_32BIT_FROM_BYTES(timestamp_capture))
         + ((uint64_t)UpdateCallbackCount * ONE_SECOND_NS);
}


static uint64_t GetCurrentTime(void)
{
  /* Build absolute time from timer counter and overflow seconds. */
  return TimToNanosec((uint64_t)HAL_TIM_GetCounter(pTIM))
         + ((uint64_t)UpdateCallbackCount * ONE_SECOND_NS);
}
