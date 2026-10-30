/**
  ******************************************************************************
  * file           : example.c
  * brief          : Erasing and writing to MX25LM51245G XSPI flash memory using indirect mode
  *                  and reading using memory-mapped mode
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

#include <string.h>     /* required for memcmp()       */

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

/* Part obj */
mx25lm51245g_obj_t *pFlashMemoryObj = NULL;
/* Pointer to the memory-mapped base address */
uint8_t *pMX25LM51245GMmp  = NULL;
/* Transmit buffer used for memory write operations */
uint8_t TxBuffer[BUFFER_SIZE] = {0U};
/* Receive buffer used for memory read operations */
uint8_t RxBuffer[BUFFER_SIZE];

/* Private functions prototype -----------------------------------------------*/
static void BufferFill(uint8_t *pbuffer, uint32_t buff_length);


app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /* Prepare the data to be written to the external memory */
  BufferFill(TxBuffer, BUFFER_SIZE);

  /**
    * ########## Step 1 ##########
    * Initialize the MX25LM51245G parts driver and configure it in OPI DTR mode.
    */

  /* Retrieve and store the mx25lm51245g object pointer */
  pFlashMemoryObj = mx_mx25lm51245g_0_getobject();

  /* Initialize the MX25LM51245G Octo SPI memory part */
  if (mx25lm51245g_init(pFlashMemoryObj, MX25LM51245G_0) != MX25LM51245G_OK)
  {
    goto _app_init_exit;
  }

  /* Set the required memory configuration */
  if (mx25lm51245g_set_memconfig(pFlashMemoryObj, MX25LM51245G_OPI_MODE, MX25LM51245G_DTR_TRANSFER) != MX25LM51245G_OK)
  {
    goto _app_init_exit;
  }

  PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
  return_status = EXEC_STATUS_INIT_OK;

_app_init_exit:
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pMX25LM51245GMmp = (uint8_t *) mx25lm51245g_get_memory_mapped_base_address(pFlashMemoryObj);

  /* Clear buffer for next test */
  memset(RxBuffer, 0U, sizeof(RxBuffer));

  /**
    * ########## Step 2 ##########
    * Erase the memory pages to be programmed by sectors,
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
    * Writes a data buffer to the external memory, in indirect mode.
    */

  /* write the TX buffer in the flash memory starting from MX25LM51245G_START_ADDRESS */
  if (mx25lm51245g_write(pFlashMemoryObj, MX25LM51245G_START_ADDRESS,
                         MX25LM51245G_ADD_SIZE,
                         TxBuffer,
                         BUFFER_SIZE) != MX25LM51245G_OK)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 3: Data buffer written to the external memory (OPI DTR - Indirect mode).\n");

  /**
    * ########## Step 4 ##########
    * Reads the same data buffer from the external memory using memory mapped mode,
    * and checks that it matches the buffer written in Step 3.
    */

  /* Enable memory mapped mode */
  if (mx25lm51245g_enable_memory_mapped(pFlashMemoryObj, MX25LM51245G_4BYTES_SIZE) != MX25LM51245G_OK)
  {
    goto _app_process_exit;
  }

  /* Copy data from memory for comparison with the transmit buffer */
  memcpy(RxBuffer, pMX25LM51245GMmp, BUFFER_SIZE);

  PRINTF("[INFO] Step 4: Data buffer read from the external memory (MMP - direct mode).\n");

  /* Verify read data */
  if (memcmp(TxBuffer, RxBuffer, BUFFER_SIZE) != 0)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 4: Data buffer read from the external memory and matching the initial value.\n");

  /* Disable memory mapped mode */
  if (mx25lm51245g_disable_memory_mapped(pFlashMemoryObj) != MX25LM51245G_OK)
  {
    goto _app_process_exit;
  }

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

  if (mx25lm51245g_deinit(pFlashMemoryObj) == MX25LM51245G_OK)
  {
    PRINTF("[INFO] Step 5: Device de-initialization.\n");
    return EXEC_STATUS_OK;
  }

  return EXEC_STATUS_ERROR;
} /* end app_deinit */


/**
  * brief:  fills a buffer with consecutive values
  * param:  pbuffer: pointer to a buffer to fill
  * param:  buff_length: buffer length
  * retval: None
  */
static void BufferFill(uint8_t *pbuffer, uint32_t buff_length)
{
  /* Fills the buffer with consecutive values. */
  for (uint32_t buff_index = 0; buff_index < buff_length; buff_index++)
  {
    pbuffer[buff_index] = buff_index;
  }
}
