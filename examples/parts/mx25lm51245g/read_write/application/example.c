/**
  ******************************************************************************
  * file           : example.c
  * brief          : mx25lm51245g OCTOSPI Flash memory read/write example
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
#include <string.h>             /* required for memset() and memcmp() */
#include "example.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @user: configure the buffer size, the number of bytes be written to memory
  * the BUFFER_SIZE value must be even with a minimum value of 2
  */
#define BUFFER_SIZE        4096U

/** @user: configure the start address to be written to
  * the MX25LM51245G_START_ADDRESS must be even (A0=0)
  */
#define MX25LM51245G_START_ADDRESS      2U*MX25LM51245G_SECTOR_4K


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
mx25lm51245g_obj_t *pFlashObj;

uint8_t TxBuffer[BUFFER_SIZE] = {0}; /* buffer used for write operations */
uint8_t RxBuffer[BUFFER_SIZE] = {0}; /* buffer used for read operations */

/* Memory blocks to be erased */
uint16_t BlocksToErase = 0;

/* Private functions prototype -----------------------------------------------*/
static void BufferFill(uint8_t *pbuffer, uint32_t buff_length);


/** ########## Step 1 ##########
  * The init of the XSPI instance and the MX25LM51245G part are triggered by the applicative code.
  */
app_status_t app_init(void)
{

  app_status_t return_status = EXEC_STATUS_ERROR;

  /* Retrieve and store the mx25lm51245g object pointer */
  pFlashObj = mx_mx25lm51245g_0_getobject();

  /* Prepare the data to be written to the Flash memory */
  BufferFill(TxBuffer, BUFFER_SIZE);

  /* Calculate number of blocks to erase */
  BlocksToErase = (uint16_t)((BUFFER_SIZE / MX25LM51245G_BLOCK_64K) + 1U);

  /* Part initialization */
  if (mx25lm51245g_init(pFlashObj, MX25LM51245G_0) == MX25LM51245G_OK)
  {
    PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }
  else
  {
    PRINTF("[ERROR] Step 1: Device initialization ERROR.\n");
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /**
    * ########## Step 2 ##########
    * Erases blocks from the external memory.
    * Then writes a data buffer to the same area, in indirect mode, using Octal interface and Double transfer rate.
    */
  /* Set the Flash config to OPI-DTR */
  if (mx25lm51245g_set_memconfig(pFlashObj, MX25LM51245G_OPI_MODE, MX25LM51245G_DTR_TRANSFER) != MX25LM51245G_OK)
  {
    PRINTF("[ERROR] Step 2: Error while setting the interface/transfer rate configuration of the external memory.\n");
    goto _app_process_exit;
  }
  for (uint16_t i = 0U ; i < BlocksToErase ; i++)
  {
    if (mx25lm51245g_erase(pFlashObj, MX25LM51245G_START_ADDRESS + (i * MX25LM51245G_BLOCK_64K),
                           MX25LM51245G_ERASE_BLOCK) != MX25LM51245G_OK)
    {
      printf("[ERROR] Step 2: Error while erasing the blocks from the external memory.\n");
      goto _app_process_exit;
    }
  }
  /* Write to the external flash */
  if (mx25lm51245g_write(pFlashObj, MX25LM51245G_START_ADDRESS, MX25LM51245G_4BYTES_SIZE,
                         TxBuffer, BUFFER_SIZE) != MX25LM51245G_OK)
  {
    PRINTF("[ERROR] Step 2: Error while writing data to the external memory.\n");
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 2: Data buffer written to the external memory (OPI-DTR - Indirect mode).\n");

  /**
    * ########## Step 3 ##########
    * Reads the same data buffer from the external memory, and checks that it matches the buffer written in Step 2.
    */


  /* Reuse the configuration set in Step 2: no need to call mx25lm51245g_set_memconfig() again. */

  /* Read from the external memory */
  if (mx25lm51245g_read(pFlashObj, MX25LM51245G_START_ADDRESS, MX25LM51245G_4BYTES_SIZE,
                        RxBuffer, BUFFER_SIZE) != MX25LM51245G_OK)
  {
    PRINTF("[ERROR] Step 3: Error while reading data from the external memory.\n");
    goto _app_process_exit;
  }
  /* Compare the two data buffers */
  if (memcmp(TxBuffer, RxBuffer, BUFFER_SIZE) != 0)
  {
    PRINTF("[ERROR] Step 3: Data mismatch detected.\n");
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 3: Data buffer read from the external memory and matching the initial value.\n");
  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** ########## Step 4 ##########
  * Deinitializes the MX25LM51245G before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  PRINTF("[INFO] Step 4: Device de-initialization.\n");
  if (mx25lm51245g_deinit(pFlashObj) != MX25LM51245G_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  return EXEC_STATUS_OK;
} /* end app_deinit */


/**
  * brief:  fills a buffer with arbitrary values
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
