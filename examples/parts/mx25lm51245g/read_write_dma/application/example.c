/**
  ******************************************************************************
  * file           : example.c
  * brief          : mx25lm51245g OCTOSPI Flash memory read/write dma example
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

/* Private macro -------------------------------------------------------------*/

/** @user: Define the number of pages to be programmed in one operation. */
#define PAGE_NBR                   16U

/** @user: Define the starting page index for memory operations. */
#define PAGE_INDEX                 0U

/** @user: configure the buffer size, the number of pages to be written to memory
  * The BUFFER_SIZE value must be even, with a minimum value of 2 and maximum MX25LM51245G_FLASH_SIZE.
  */
#define BUFFER_SIZE                (MX25LM51245G_PAGE_SIZE * PAGE_NBR)

/** @user: configure the read/write address size 3 or 4 bytes.
  */
#define MX25LM51245G_ADD_SIZE       MX25LM51245G_4BYTES_SIZE

/** @user: Configure the start address for read/write operations.
  * The address must be aligned to the address size and page/sector/block size.
  */
#define MX25LM51245G_START_ADDRESS  (MX25LM51245G_PAGE_SIZE * PAGE_INDEX)

/* Private variables ---------------------------------------------------------*/

/* Flash memory pointer */
mx25lm51245g_obj_t *pFlashMemoryObj = NULL;

/* buffer used for write operations */
/** Declaring these buffers as non-cacheable is not mandatory.
  * the MX25LM51245G driver internally manages cache maintenance before each DMA transfer.
  */
uint8_t TxBuffer[BUFFER_SIZE] = {0U};
/* buffer used for read operations */
uint8_t RxBuffer[BUFFER_SIZE] = {0U};

/* Callback Flag */
volatile uint32_t WriteCallbackFlag;
volatile uint32_t ReadCallbackFlag;

/* Private functions prototype -----------------------------------------------*/

static void BufferFill(uint8_t *pbuffer, uint32_t buff_length);
static void WriteDmaCallback(mx25lm51245g_obj_t *pobj, void *parg);
static void ReadDmaCallback(mx25lm51245g_obj_t *pobj, void *parg);

app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /* Prepare the data to be written to the external memory */
  BufferFill(TxBuffer, BUFFER_SIZE);

  /**
    * ########## Step 1 ##########
    * The initialization of the MX25LM51245G part is triggered by the applicative code.
    */

  /* Retrieve and store the mx25lm51245g object pointer */
  pFlashMemoryObj = mx_mx25lm51245g_0_getobject();

  /* Initialize the MX25LM51245G Octo SPI memory part */
  if (mx25lm51245g_init(pFlashMemoryObj, MX25LM51245G_0) != MX25LM51245G_OK)
  {
    goto _app_init_exit;
  }

  /* Set the flash memory io to OPI DTR mode */
  if (mx25lm51245g_set_memconfig(pFlashMemoryObj, MX25LM51245G_OPI_MODE, MX25LM51245G_DTR_TRANSFER) != MX25LM51245G_OK)
  {
    goto _app_init_exit;
  }

  /* Register callback */
  if (mx25lm51245g_register_write_cplt_callback(pFlashMemoryObj,
                                                WriteDmaCallback, (void *) &WriteCallbackFlag) != MX25LM51245G_OK)
  {
    goto _app_init_exit;
  }

  /* Register callback */
  if (mx25lm51245g_register_read_cplt_callback(pFlashMemoryObj,
                                               ReadDmaCallback, (void *) &ReadCallbackFlag) != MX25LM51245G_OK)
  {
    goto _app_init_exit;
  }

  /* An aligned custom bounce buffer can be registered with mx25lm51245g_set_dma_buffer().
    * In this single-instance example, the driver's default internal buffer is sufficient. */
  PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");

  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  mx25lm51245g_status_t status = MX25LM51245G_OK;

  /**
    * ########## Step 2 ##########
    * Erase the memory pages by sectors,
    * to ensure the memory is properly prepared for subsequent operations.
    */

  /**
    * All sectors that overlap with the address range [start_address, start_address + buffer_size)
    * will be erased.
    */
  if (mx25lm51245g_sectors_erase(pFlashMemoryObj, MX25LM51245G_START_ADDRESS, BUFFER_SIZE) != MX25LM51245G_OK)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 2: Memory erased (OPI DTR - Indirect mode).\n");

  /**
    * ########## Step 3 ##########
    * Writes a data buffer to the external memory, in indirect mode, using OPI mode with double transfer.
    */

  /* Write the TX buffer in the flash memory starting from MX25LM51245G_START_ADDRESS */
  if (mx25lm51245g_write_dma_async(pFlashMemoryObj, MX25LM51245G_START_ADDRESS, MX25LM51245G_ADD_SIZE,
                                   TxBuffer,
                                   BUFFER_SIZE) != MX25LM51245G_OK)
  {
    goto _app_process_exit;
  }

  while ((WriteCallbackFlag == 0) && (status != MX25LM51245G_ERROR))
  {
    /* Advance async write state if a copy is pending, then trigger the next DMA write chunk */
    status = mx25lm51245g_exec_data_handler(pFlashMemoryObj);
    /**
      * Enter sleep mode and wait for a DMA interrupt or a SysTick interrupt to wake up the CPU.
      * @user: The sleep mode is used to illustrate the interest of the DMA. It can be replaced by your own code.
      */
    __WFI(); /* Wait for interrupt */
  }
  if (status == MX25LM51245G_ERROR)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 3: Data buffer written to the external memory (OPI DTR - Indirect mode).\n");

  /**
    * ########## Step 4 ##########
    * Reads the same data buffer from the external memory, and checks that it matches the buffer written in Step 3.
    */

  /* Clear the RX buffer before read data */
  memset(RxBuffer, 0U, sizeof(RxBuffer));

  /* Read back the data from the flash memory starting from MX25LM51245G_START_ADDRESS */
  if (mx25lm51245g_read_dma_async(pFlashMemoryObj, MX25LM51245G_START_ADDRESS, MX25LM51245G_ADD_SIZE,
                                  RxBuffer, BUFFER_SIZE) != MX25LM51245G_OK)
  {
    goto _app_process_exit;
  }

  while ((ReadCallbackFlag == 0) && (status != MX25LM51245G_ERROR))
  {
    /* Advance async read state if a copy is pending, then trigger the next DMA read chunk */
    status = mx25lm51245g_exec_data_handler(pFlashMemoryObj);
    /**
      * Enter sleep mode and wait for a DMA interrupt or a SysTick interrupt to wake up the CPU.
      * @user: The sleep mode is used to illustrate the interest of the DMA. It can be replaced by your own code.
      */
    __WFI();  /* Wait for interrupt */
  }
  if (status == MX25LM51245G_ERROR)
  {
    goto _app_process_exit;
  }

  /* Compare the two data buffers */
  if (memcmp(TxBuffer, RxBuffer, BUFFER_SIZE) != 0)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 4: Data buffer read from the external memory and matching the initial value.\n");

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


app_status_t app_deinit(void)
{
  /**
    * ########## Step 5 ##########
    * De-initializes the MX25LM51245G part before leaving the scenario.
    */

  if (mx25lm51245g_deinit(pFlashMemoryObj) != MX25LM51245G_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  PRINTF("[INFO] Step 5: Device de-initialization.\n");

  return EXEC_STATUS_OK;
} /* end app_deinit */


/**
  * brief:  fills a buffer with consecutive values
  * param:  pbuffer: pointer to a buffer to fill
  * param:  buff_length: buffer length
  * retval: None
  */
static void BufferFill(uint8_t *pbuffer, uint32_t buff_length)
{
  /* Fills the buffer with an arbitrary content.
   * Here we just loop over sequential integers (0..255).
   */
  for (uint32_t buff_index = 0; buff_index < buff_length; buff_index++)
  {
    pbuffer[buff_index] = (uint8_t)(buff_index & 0xFF);
  }
}

/**
  * brief DMA write completion callback.
  *
  * This function is called when the DMA write operation completes.
  * It sets the flag pointed to by 'parg' to 1 to signal completion.
  *
  * param pobj Pointer to the MX25LM51245G object (unused in this callback).
  * param parg Pointer to a volatile flag variable to be set upon completion.
  */
static void WriteDmaCallback(mx25lm51245g_obj_t *pobj, void *parg)
{
  volatile uint32_t *pflag = parg;
  *pflag = 1U;
}

/**
  * brief DMA read completion callback.
  *
  * This function is called when the DMA read operation completes.
  * It sets the flag pointed to by 'parg' to 1 to signal completion.
  *
  * param pobj Pointer to the MX25LM51245G object (unused in this callback).
  * param parg Pointer to a volatile flag variable to be set upon completion.
  */
static void ReadDmaCallback(mx25lm51245g_obj_t *pobj, void *parg)
{
  volatile uint32_t *pflag = parg;
  *pflag = 1U;
}
