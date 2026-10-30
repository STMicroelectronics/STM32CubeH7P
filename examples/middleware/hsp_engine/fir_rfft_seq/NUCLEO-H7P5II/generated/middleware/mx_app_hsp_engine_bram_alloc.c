/**
  ******************************************************************************
  * @file           : mx_app_hsp_engine_bram_alloc.c
  * @brief          : This file contains resources allocated in HSP BRAM memory
                      region
  ******************************************************************************
  * @attention
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

#include "mx_app_hsp_engine_bram_alloc.h"
#include "hsp_bram.h"

/* Exported variables --------------------------------------------------------*/
static hsp_bram_resources_t g_bram_resources;

/** The "fir_coefs" table below is precomputed offline and embedded as static example data.
  * It provides the FIR coefficients for the FIR filter example.
  * The buffer is stored in HSP BRAM memory region to avoid to transfer the coefgicients from the system memory
  * to the HSP BRAM at runtime, which can be time consuming.
  */
static float fir_coefs[HSP_BRAM_RSRC_FIR_COEF_SIZE]  __attribute__((section(".HSP_DATA_BRAM"))) = {
  0.00240166, 0.00483097, 0.00663137, 0.00619702, 0.00217623, -0.00566713, -0.0157708, -0.0246505,
  -0.0275608, -0.0198746, 0.00120821, 0.0352238, 0.0778732, 0.121663, 0.157681, 0.178013,
  0.178013, 0.157681, 0.121663, 0.0778732, 0.0352238, 0.00120821, -0.0198746, -0.0275608,
  -0.0246505, -0.0157708, -0.00566713, 0.00217623, 0.00619702, 0.00663137, 0.00483097, 0.00240166
};
static uint32_t pl_call __attribute__((section(".HSP_DATA_BRAM"))) = 0U;
/* Private variables ---------------------------------------------------------*/
static hsp_bram_resources_t g_bram_resources;

/* Private function prototypes -----------------------------------------------*/

/* Exported function ---------------------------------------------------------*/
/**
  * @brief  Get the HSP BRAM Resources object.
  * @retval Pointer on the HSP BRAM Resources
  */
hsp_bram_resources_t *mx_app_hsp_engine_bram_getresources(void)
{
  return &g_bram_resources;
}

uint32_t HSP_BRAM_AllocateHook(hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;

  /* Static allocations ------------------------------------------------------*/
  g_bram_resources.fir_coefs = fir_coefs;
  g_bram_resources.pl_call = &pl_call;

  /* Dynamic allocations -----------------------------------------------------*/
  g_bram_resources.fir_state_id = HSP_BRAM_MallocStateBuffer_Fir(hmw, HSP_BRAM_RSRC_FIR_STATE_TAPS_SIZE, HSP_BRAM_RSRC_SAMPLES_NBR, HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.fir_state_id == 0UL) error++;

  g_bram_resources.p_buff_in = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_SAMPLES_NBR, HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_buff_in == NULL) error++;

  g_bram_resources.p_results = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_SAMPLES_NBR, HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_results == NULL) error++;

  return error;
}
