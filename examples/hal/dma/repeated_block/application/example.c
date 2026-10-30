/**
  ******************************************************************************
  * file           : example.c
  * brief          : DMA repeated block incremented gather transaction.
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

#include <string.h>     /* required for memcmp() */
#include "example.h"

#define DMA_ALIGNMENT 8U /* user define to adjust the data alignment to the DMA IP of the SoC */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define SRC_BUFFER_SIZE_IN_WORDS        (48U) /* source buffer size in words */
#define GATHER_BUFFER_SIZE_IN_WORDS     (16U) /* Destination expected gathered data buffer size in words */
#define GATHER_BLOCK_SIZE_IN_BYTES      (16U)  /* Number of bytes transferred per repeated block */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_dma_handle_t *pDMA;  /* pointer referencing the DMA handle from the generated code */

/* SrcBuffer is declared as const, so that it is placed in Flash. */
__attribute__((aligned(DMA_ALIGNMENT)))
const uint32_t SrcBuffer[SRC_BUFFER_SIZE_IN_WORDS] =
{
  0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,

  0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
  0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,

  0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB,

  0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
  0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,

  0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC,

  0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
  0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,

  0xDDDDDDDD, 0xDDDDDDDD, 0xDDDDDDDD, 0xDDDDDDDD,

  0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
  0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80
};

/* IncrementGatherExpectedResultBuffer is declared as const, so that it is placed in Flash. */
__attribute__((aligned(DMA_ALIGNMENT)))
const uint32_t IncrementGatherExpectedResultBuffer[GATHER_BUFFER_SIZE_IN_WORDS] =
{
  0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA,
  0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB, 0xBBBBBBBB,
  0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC, 0xCCCCCCCC,
  0xDDDDDDDD, 0xDDDDDDDD, 0xDDDDDDDD, 0xDDDDDDDD
};

/** Destination increment gather buffer for CPU and DMA.
  * - Non-cacheable memory for data cache consistency.
  * - Aligned for DMA constraints.
  */
__attribute__((section("non_cacheable_area"), aligned(DMA_ALIGNMENT)))
uint32_t DstIncrementGatherBuffer[GATHER_BUFFER_SIZE_IN_WORDS];

volatile uint8_t TransferError;    /* Set to 1 if a transfer error is detected */
volatile uint8_t TransferComplete; /* Set to 1 if the transfer is correctly completed */

/* Private functions prototype -----------------------------------------------*/
static void TransferCompleteCallback(hal_dma_handle_t *handle_dma);
static void TransferErrorCallback(hal_dma_handle_t *handle_dma);


/** ########## Step 1 ##########
  * The init of the DMA instance configured in repeated block mode is triggered by the applicative code.
  * User's callbacks for DMA error and DMA complete are registered.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pDMA = mx_example_dma_init();
  if (pDMA == NULL)
  {
    goto _app_init_exit;
  }

  /* Select Callbacks functions called after Transfer complete and Transfer error */
  if (HAL_DMA_RegisterXferCpltCallback(pDMA, TransferCompleteCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }
  if (HAL_DMA_RegisterXferErrorCallback(pDMA, TransferErrorCallback) != HAL_OK)
  {
    goto _app_init_exit;
  }

  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


/** ########## Step 2 ##########
  * Starts the DMA repeated block transfer
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  TransferError = 0;
  TransferComplete = 0;

  if (HAL_DMA_StartDirectXfer_IT(pDMA, (uint32_t)SrcBuffer, (uint32_t)DstIncrementGatherBuffer,
                                 GATHER_BLOCK_SIZE_IN_BYTES)  != HAL_OK)
  {
    goto _app_process_exit;
  }

  /** ########## Step 3 ##########
    * Waits for one of these DMA interrupts: transfer complete or transfer error,
    * then compares destination and expected buffers.
    */
  while (!TransferComplete && !TransferError)
  {
    /** Put the CPU in Wait For Interrupt state. A DMA interrupt or a SystTick interrupt can wake up the CPU.
      * @user: This process is used to illustrate the interest of the DMA. It can be replaced by your own code.
      */
    __WFI();
  }

  if ((TransferComplete != 1) || (TransferError == 1))
  {
    goto _app_process_exit;
  }

  /* Compare expected result with destination buffer */
  if (memcmp(DstIncrementGatherBuffer, IncrementGatherExpectedResultBuffer,
             GATHER_BUFFER_SIZE_IN_WORDS * sizeof(uint32_t)) != 0)
  {
    goto _app_process_exit;
  }

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** ########## Step 4 ##########
  * Deinitializes the DMA instance before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  mx_example_dma_deinit();

  return EXEC_STATUS_OK;
} /* end app_deinit */


/** DMA transfer complete callback
  * @user This implementation of the DMA complete callback can be customized.
  * This function is executed if the transfer complete interrupt is generated.
  */
static void TransferCompleteCallback(hal_dma_handle_t *handle_dma)
{
  /* async processing related to step 3 */
  TransferComplete = 1;
}


/** DMA transfer error callback
  * @user This implementation of the DMA error callback can be customized.
  * This function is executed if the transfer error interrupt is generated during the DMA transfer.
  */
static void TransferErrorCallback(hal_dma_handle_t *handle_dma)
{
  /* async processing related to step 3 */
  TransferError = 1;
}
