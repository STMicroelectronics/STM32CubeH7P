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
/* BRAM Resources Static Allocation ------------------------------------------*/
float32_t rms_kpi __attribute__((section(".HSP_DATA_BRAM"))) = { 10.0f };

/* BRAM Resources Dynamic Allocation -----------------------------------------*/
// hsp_filter_state_identifier_t fir_state_id;  /* BRAM FIR State Identifier */

// float32_t *p_buff_in;  /* BRAM Input Buffer */
// float32_t *p_coef;  /* BRAM FIR Coefficient Buffer */
// float32_t *p_buff_out;  /* BRAM Output Buffer */
// float32_t *p_buff_expected;  /* BRAM Expected Output Buffer */

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
  g_bram_resources.p_rms_kpi = &rms_kpi;

  /* Dynamic allocations -----------------------------------------------------*/
  g_bram_resources.fir_state_id = HSP_BRAM_MallocStateBuffer_Fir(hmw, HSP_BRAM_RSRC_FIR_STATE_TAPS_SIZE,
                                                                 HSP_BRAM_RSRC_INPUT_SIGNAL_SAMPLES_SIZE,
                                                                 HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.fir_state_id == 0UL) error++;

  g_bram_resources.p_buff_in = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_INPUT_SIGNAL_SAMPLES_SIZE,
                                                            HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_buff_in == NULL) error++;

  g_bram_resources.p_coef = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_FIR_COEF_SIZE, HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_coef == NULL) error++;

  g_bram_resources.p_buff_out = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_OUTPUT_SAMPLES_SIZE,
                                                             HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_buff_out == NULL) error++;

  g_bram_resources.p_buff_expected = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_OUTPUT_SAMPLES_SIZE,
                                                                   HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_buff_expected == NULL) error++;

  return error;
}
