/**
  ******************************************************************************
  * file           : example.c
  * brief          : I3C target example with entry to low power mode using
  *                  LL API.
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
#include "ll_example.h"
#include <string.h> /* importing memcmp and memset functions */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TARGET_DYNAMIC_ADDRESS   0x32U   /* Dynamic address expected */
#define VALID_ADDRESS            1U      /* Dynamic address valid */

/* @user: set the maximum number of attempts to complete a data transfer
   between the two boards */
#define MAX_COM_ATTEMPTS         10U

/* @user: must match the controller transfer size.
  Keep this value word-aligned for the paired private_it_controller example. */
#define RECEIVE_BUFFER_SIZE      40U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Dynamic address assignment notification received. */
volatile uint32_t DynamicAddressAssignmentReceived = 0U;
/* RX transfer is completed. */
volatile uint32_t ReceiveTransferComplete = 0U;
/* TX transfer is completed. */
volatile uint32_t TransmitTransferComplete = 0U;

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/* Transfer error detected. */
volatile uint32_t TransferError = 0U;
#endif /* USE_LL_APP_ERROR */

/* Dynamic address assignment completed for this power cycle. */
uint8_t DynamicAddressAssignmentCompleted = 0U;

/* Buffer used for reception */
uint8_t RxBuffer[RECEIVE_BUFFER_SIZE] = {0U};

/* Private functions prototype -----------------------------------------------*/
static app_status_t I3C_DynamicAddressAssignment(void);

/** ########## Step 1 ##########
  * The initialization of the I3C instance is triggered by the application.
  * The LL helper layer activates the I3C target instance.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (mx_i3cx_init() == NULL)
  {
    goto _app_init_exit;
  }

  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /* Memorizes the number of attempts. */
  uint32_t com_attempts = 0U;

  /**
    * ########## Step 2 ##########
    * Perform dynamic address assignment.
    * Waits and Checks the dynamic address assignment completion.
    * The dynamic address assignment is executed only once in app_process.
    */
  if (!DynamicAddressAssignmentCompleted)
  {
    if (I3C_DynamicAddressAssignment() != EXEC_STATUS_OK)
    {
      return EXEC_STATUS_ERROR;
    }
  }

  /* Clear the MX_I3Cx RX buffer before starting a new transfer */
  memset(RxBuffer, 0U, RECEIVE_BUFFER_SIZE);

  while ((com_attempts < MAX_COM_ATTEMPTS)
         && (return_status == EXEC_STATUS_ERROR))
  {
    /* Clear I3C interrupt flags before starting a new transfer attempt */
    ReceiveTransferComplete = 0U;

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
    TransferError = 0U;
#endif /* USE_LL_APP_ERROR */

    /* Start a new communication attempt */
    com_attempts++;


    /** ########## Step 3 ##########
      * Start target receive in interrupt mode, then enter low-power mode.
      * The target wakes up when the controller starts the transfer.
      */
    if (I3C_Receive_IT(RxBuffer, RECEIVE_BUFFER_SIZE) != SYSTEM_OK)
    {
      return_status = EXEC_STATUS_ERROR;
      continue;
    }
    else
    {
      /* Enter low-power mode after RX is armed. */
      if (mx_pwr_enter_low_power() != SYSTEM_OK)
      {
        return EXEC_STATUS_ERROR;
      }

      /*Exit low-power mode to wake up the target */
      if (mx_pwr_exit_low_power() != SYSTEM_OK)
      {
        return EXEC_STATUS_ERROR;
      }
    }


    /** ########## Step 4 ##########
      * After wakeup, wait for receive complete or error.
      */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
    while ((ReceiveTransferComplete == 0U) && (TransferError == 0U))
#else
    while (ReceiveTransferComplete == 0U)
#endif /* USE_LL_APP_ERROR */
    {
      /** Put the CPU in Wait For Interrupt state.
        * An MX_I3Cx interrupt or a SysTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the IT
        * mode. It can be replaced by your own code.
        */
      __WFI();
    }

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
    if (TransferError == 1U)
    {
      /* RX transfer is not correctly completed. Report the error, then
         restart the communication. */
      return_status = EXEC_STATUS_ERROR;
      continue;
    }
#endif /* USE_LL_APP_ERROR */


    /** ########## Step 5 ##########
      * Start target transmit in interrupt mode to echo the received buffer.
      */
    TransmitTransferComplete = 0U;

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
    TransferError = 0U;
#endif /* USE_LL_APP_ERROR */

    if (I3C_Transmit_IT(RxBuffer, RECEIVE_BUFFER_SIZE) != SYSTEM_OK)
    {
      return_status = EXEC_STATUS_ERROR;
      continue;
    }


    /** ########## Step 6 ##########
      * Wait for transmit complete or error.
      * Use Wait For Interrupt state while waiting for completion.
      */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
    while ((TransmitTransferComplete == 0U) && (TransferError == 0U))
#else
    while (TransmitTransferComplete == 0U)
#endif /* USE_LL_APP_ERROR */
    {
      /** Put the CPU in Wait For Interrupt state.
        * An MX_I3Cx interrupt or a SysTick interrupt can wake up the CPU.
        * @user: This process is used to illustrate the interest of the IT
        * mode. It can be replaced by your own code.
        */
      __WFI();
    }

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
    if (TransferError == 1U)
    {
      /* TX transfer error occurred. Handle and retry. */
      return_status = EXEC_STATUS_ERROR;
      continue;
    }
#endif /* USE_LL_APP_ERROR */

    return_status = EXEC_STATUS_OK;

  } /* end while */

  return return_status;
} /* end app_process */


/** brief: Performs dynamic address assignment and verifies the assigned
  * target address.
  * retval: example status
  */
static app_status_t I3C_DynamicAddressAssignment(void)
{
  DynamicAddressAssignmentReceived = 0U;

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  TransferError = 0U;
#endif /* USE_LL_APP_ERROR */

  /* Activate notification for dynamic address assignment */
  I3C_ActivateNotification();

  /* Wait for dynamic address assignment completion or an error */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  while ((DynamicAddressAssignmentReceived == 0U) && (TransferError == 0U))
#else
  while (DynamicAddressAssignmentReceived == 0U)
#endif /* USE_LL_APP_ERROR */
  {
    /** Put the CPU in Wait For Interrupt state.
      * An MX_I3Cx interrupt or a SysTick interrupt can wake up the CPU.
      * @user: This process is used to illustrate the interest of the IT mode.
      * It can be replaced by your own code.
      */
    __WFI();
  }

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  if (TransferError == 1U)
  {
    return EXEC_STATUS_ERROR;
  }
#endif /* USE_LL_APP_ERROR */

  if ((I3C_IsOwnDynamicAddressValid() != VALID_ADDRESS)
      || (I3C_GetOwnDynamicAddress() != (uint32_t)TARGET_DYNAMIC_ADDRESS))
  {
    return EXEC_STATUS_ERROR;
  }

  DynamicAddressAssignmentCompleted = 1U;

  return EXEC_STATUS_OK;
} /* end I3C_DynamicAddressAssignment */


/**
  * MX_I3Cx target notification callback (interrupt mode).
  * @user This implementation of the MX_I3Cx target notification callback
  * can be customized.
  * This function is executed when dynamic address assignment is completed
  * (step 2).
  */
void I3C_DynamicAddressAssignmentCompleteCallback(void)
{
  DynamicAddressAssignmentReceived = 1U;
}


/**
  * MX_I3Cx target RX transfer complete callback (interrupt mode).
  * @user This implementation of the MX_I3Cx target transfer complete
  * callback can be customized.
  * This function is executed when the RX transfer is completed by an
  * interrupt (step 4).
  */
void I3C_ReceiveCompleteCallback(void)
{
  /* Signal RX transfer completion for step 4 */
  ReceiveTransferComplete = 1U;
}


/**
  * MX_I3Cx target TX transfer complete callback (interrupt mode).
  * @user This implementation of the MX_I3Cx target transfer complete
  * callback can be customized.
  * This function is executed when the TX transfer is completed by an
  * interrupt (step 6).
  */
void I3C_TransmitCompleteCallback(void)
{
  /* Signal TX transfer completion for step 6 */
  TransmitTransferComplete = 1U;
}


#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/**
  * MX_I3Cx target transfer error callback (interrupt mode).
  * @user This implementation of the MX_I3Cx target transfer error callback
  * can be customized.
  * This function is executed when a transfer error interrupt occurs
  * (steps 4 or 6).
  */
void I3C_ErrorCallback(void)
{
  /* Signal transfer error for steps 4 and 6 */
  TransferError = 1U;
}
#endif /* USE_LL_APP_ERROR */


/** De-initializes the MX_I3Cx instance before leaving the scenario.
  * In this example, app_deinit is never called and it is provided as a
  * reference only.
  */
app_status_t app_deinit(void)
{
  mx_i3cx_deinit();

  return EXEC_STATUS_OK;
} /* end app_deinit */

