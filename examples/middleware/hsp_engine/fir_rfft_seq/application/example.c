/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
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
#include "mx_hsp_engine_app.h"
#include "mx_app_hsp_engine_bram_alloc.h"
#include "mx_app_hsp_engine_seq.h"
#include "mx_app_hsp_engine_process.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t nb_loop = 10U;
uint32_t ret;

/* Private functions prototype -----------------------------------------------*/

/** ########## Step 1 ##########
  * The applicative code initializes the HSP instance and the MW HSP Engine.
  * Record the processing list.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (mx_hsp_init() != NULL)
  {
    /* Initialize the Middleware HSP Engine */
    if (mx_hsp_engine_init_hsp() == 0U)
    {
      PRINTF("[INFO] Step 1: MW HSP Engine initialization COMPLETED.\n");
      return_status = EXEC_STATUS_INIT_OK;
    }
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  PRINTF("[INFO] Step 2: Initiate process.\n");
  if (MX_HSP_Engine_InitiateProcess() != 0U)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 3: Process FIR + RFFT.\n");
  for (uint32_t idx = 0U; idx < nb_loop; idx++)
  {
    ret = MX_HSP_Engine_ProcessFIR_FFT();
    if (ret != 0U)
    {
      goto _app_process_exit;
    }
  }

  PRINTF("[INFO] Step 4: FIR + RFFT process OK.\n");
  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** ########## Step 5 ##########
  * De-initializes the Middleware HSP Engine and then the HSP instance.
  */
app_status_t app_deinit(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  PRINTF("[INFO] Step 5: de-init.\n");

  /** De-initialize the HSP Engine middleware context attached to the HSP1 instance. */
  mx_hsp_engine_deinit_hsp();

  /** De-initialize the HSP1 instance. */
  mx_hsp_deinit();

  return_status = EXEC_STATUS_OK;

  return return_status;
} /* end app_deinit */
