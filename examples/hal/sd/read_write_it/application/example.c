/**
  ******************************************************************************
  * file           : example.c
  * brief          : Read and Write operations, in interrupt mode, on an SD card using HAL API
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
#include <string.h> /* memcmp */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DATA_SIZE           (0x06400000U)                   /* Data Size 100MB = 100 * 1024 KB = 100 * 1024 * 1024 B */
#define BUFFER_SIZE         (0x00004000U)                   /* 16KB */
#define ADDRESS             (0x00000400U)                   /* SD Address to write/read data */
#define DATA_PATTERN_BASE   (0xA5U)                         /* First value for the data to write */
#define BLOCK_SIZE          (512U)                          /* Block size supported by write and read functions */
#define TOTAL_BLOCK_COUNT   (DATA_SIZE / BLOCK_SIZE)        /* Total number of 512-byte blocks transferred */
#define NUMBER_OF_BLOCK     (BUFFER_SIZE / BLOCK_SIZE)      /* Number of Block (512B) by Buffer */
#define NUMBER_OF_BUFFER    (DATA_SIZE / BUFFER_SIZE)       /* Number of buffer needed to transfer all data */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_sd_handle_t *pSD;  /* pointer referencing the SD handle from the generated code */

/* Flags updated by HAL callbacks to track asynchronous transfer progress */
volatile uint8_t RxTransferComplete;
volatile uint8_t TxTransferComplete;
volatile uint8_t TransferError;

/* Timestamps used to compute write transfer duration */
uint32_t WriteStartTime = 0U;
uint32_t WriteStopTime = 0U;

/* Timestamps used to compute read transfer duration */
uint32_t ReadStartTime = 0U;
uint32_t ElapsedReadTime = 0U;

/* Buffers used for the write phase and the readback phase */
uint8_t WriteBuffer[BUFFER_SIZE];
uint8_t ReadBuffer[BUFFER_SIZE];

/* Private functions prototype -----------------------------------------------*/
/* HAL callbacks used by the interrupt-driven transfer flow */
static void SdXferCpltCallback(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event);
static void SdErrorCallback(hal_sd_handle_t *hsd);


/** ########## Step 1 ##########
  * Initialize the SD peripheral from application code, register the callbacks
  * used by interrupt mode, and fill the write buffer with a known pattern.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pSD = mx_example_sd_init();

  if (pSD != NULL)
  {
    HAL_SD_RegisterXferCpltCallback(pSD, SdXferCpltCallback);
    HAL_SD_RegisterErrorCallback(pSD, SdErrorCallback);

    PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }

  /* Fill the write buffer with a deterministic pattern for later comparison. */
  for (uint32_t i = 0; i < BUFFER_SIZE; i++)
  {
    WriteBuffer[i] = DATA_PATTERN_BASE + i;
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  uint32_t buffer_counter = 0U;
  uint32_t tick_start;

  /* Clear the TX, RX, and transfer error flags before starting a new test sequence. */
  TxTransferComplete = 0U;
  RxTransferComplete = 0U;
  TransferError = 0U;

  if (HAL_SD_Erase(pSD, ADDRESS, ADDRESS + TOTAL_BLOCK_COUNT - 1U) != HAL_OK)
  {
    goto _app_process_exit;
  }

  tick_start = HAL_GetTick();
  /* Wait until the erase command completes or abort on timeout. */
  while (HAL_SD_GetCardState(pSD) != HAL_SD_CARD_TRANSFER)
  {
    /* Check if erase timeout is not reached */
    if ((HAL_GetTick() - tick_start) >= HAL_SD_ERASE_MAX_TIMEOUT)
    {
      goto _app_process_exit;
    }
  }

  /** ########## Step 2 ##########
    * Write the content of the write buffer repeatedly to the SD card until DATA_SIZE bytes
    * have been transferred.
    */
  WriteStartTime = HAL_GetTick();
  while (buffer_counter < NUMBER_OF_BUFFER)
  {
    if (HAL_SD_WriteBlocks_IT(pSD,
                              WriteBuffer,
                              (ADDRESS + buffer_counter * NUMBER_OF_BLOCK), NUMBER_OF_BLOCK) != HAL_OK)
    {
      goto _app_process_exit;
    }

    while ((TxTransferComplete == 0U) && (TransferError == 0U))
    {
      /** Put the CPU in Wait For Interrupt state. An SD interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the IT mode. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError != 0)
    {
      goto _app_process_exit;
    }

    /* Wait until the SD card is ready to accept the next write transaction. */
    while (HAL_SD_GetCardState(pSD) != HAL_SD_CARD_TRANSFER)
    {
    }

    TxTransferComplete = 0U;
    buffer_counter++;
  }

  WriteStopTime = HAL_GetTick();
  PRINTF("[INFO] Step 2: Blocks written in %"PRIu32" ms. Write speed of %" PRIu32 " Byte/s.\n",
         WriteStopTime - WriteStartTime,
         DATA_SIZE / (WriteStopTime - WriteStartTime)
        );


  /** ########## Step 3 ##########
    * Read back the same card area into the read buffer, using the same
    * chunking strategy as the write phase, and verify each chunk immediately
    * so the whole DATA_SIZE transfer is validated.
    */
  buffer_counter = 0;
  while (buffer_counter < NUMBER_OF_BUFFER)
  {
    ReadStartTime = HAL_GetTick();

    if (HAL_SD_ReadBlocks_IT(pSD,
                             ReadBuffer,
                             (ADDRESS + buffer_counter * NUMBER_OF_BLOCK), NUMBER_OF_BLOCK) != HAL_OK)
    {
      goto _app_process_exit;
    }

    while ((RxTransferComplete == 0U) && (TransferError == 0U))
    {
      /** Put the CPU in Wait For Interrupt state. An SD interrupt or a SystTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the IT mode. It can be replaced by your own code.
        */
      __WFI();
    }

    if (TransferError != 0U)
    {
      goto _app_process_exit;
    }

    while (HAL_SD_GetCardState(pSD) != HAL_SD_CARD_TRANSFER)
    {
      /* Wait until the SD card is ready to serve the next read transaction. */
    }

    ElapsedReadTime += HAL_GetTick() - ReadStartTime;

    /**
      * Compare the write buffer and the read buffer to confirm data integrity.
      */
    if (memcmp(WriteBuffer, ReadBuffer, BUFFER_SIZE) != 0)
    {
      PRINTF("[ERROR] Step 3: Data MISMATCH identified.\n");
      goto _app_process_exit;
    }

    RxTransferComplete = 0;
    buffer_counter++;
  }
  PRINTF("[INFO] Step 3: Reading and writing buffers are identical. Blocks read in %"PRIu32" ms. Read speed of %" PRIu32
         " Byte/s.\n",
         ElapsedReadTime,
         DATA_SIZE / ElapsedReadTime
        );

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  if (return_status == EXEC_STATUS_ERROR)
  {
    PRINTF("[ERROR] Error during reading/writing operation.\n");
  }
  return return_status;
} /* end app_process */


/** ########## Step 4 ##########
  * Deinitializes the SD instance before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  PRINTF("[INFO] Step 4: de-init\n");
  /* De-initialization of the SD instance and of the transfer interruptions */
  mx_example_sd_deinit();

  return EXEC_STATUS_OK;
} /* end app_deinit */


/** SD transfer-complete callback.
  * Sets the flag associated with the completed transfer direction.
  */
static void SdXferCpltCallback(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event)
{
  if (cb_event == HAL_SD_EVENT_CB_TX_CPLT)
  {
    TxTransferComplete = 1U;
  }
  else if (cb_event == HAL_SD_EVENT_CB_RX_CPLT)
  {
    RxTransferComplete = 1U;
  }
}


/** SD error callback.
  * Signals that the current asynchronous transfer failed.
  */
static void SdErrorCallback(hal_sd_handle_t *hsd)
{
  TransferError = 1U;
}
