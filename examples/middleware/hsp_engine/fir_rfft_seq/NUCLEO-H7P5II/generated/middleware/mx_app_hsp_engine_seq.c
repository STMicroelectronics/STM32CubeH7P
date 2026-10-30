/**
  ******************************************************************************
  * @file   mx_app_hsp_engine_seq.c
  * @brief  This file implements the application using Processing List
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

#include "mx_app_hsp_engine_seq.h"
#include "mx_app_hsp_engine_bram_alloc.h"

/* Exported variables --------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static uint32_t MX_HSP_SEQ_Record_PL_FIR_FFT(hsp_engine_context_t *hmw);


/**
  * @brief Hook to gather the record of all Processing list
  * @param hmw  Pointer the HSP Engine middleware context @ref hsp_engine_context_t
  * @retval uint32_t
  */
uint32_t HSP_SEQ_RecordPLHook(hsp_engine_context_t *hmw)
{
  uint32_t error = 0U;

  /* Record and Configure the Processing Lists -------------------------------*/
  if (MX_HSP_SEQ_Record_PL_FIR_FFT(hmw) != 0U) error++;

  /* Configure and enable TRGO HSP Outputs -----------------------------------*/
  if (HSP_CORE_OUTPUT_SetConfig(hmw, HSP_CORE_TRGO_0, HSP_CORE_TRGO_SRC_SPE) != HSP_CORE_OK) error++;
  if (HSP_CORE_OUTPUT_Enable(hmw) != HSP_CORE_OK) error++;

  /* Enable all HSP Events attached to a processing list ---------------------*/
  if (HSP_SEQ_EVENT_Enable(hmw, HSP_SEQ_ALL_EVENTS_MASK) != HSP_CORE_OK) error++;

  return error;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief Record FIR and FFT Processing list
  * @param hmw  Pointer the HSP Engine middleware context @ref hsp_engine_context_t
  * @retval uint32_t
  */
static uint32_t MX_HSP_SEQ_Record_PL_FIR_FFT(hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;
  hsp_core_status_t mw_status;
  hsp_bram_resources_t *p_bram_rsrc = mx_app_hsp_engine_bram_getresources();

  mw_status = HSP_SEQ_StartRecordPL(hmw, HSP_SEQ_PL_ID_FIR_FFT);
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_ScaInc_u32(hmw, p_bram_rsrc->pl_call, p_bram_rsrc->pl_call, HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_Fir_f32(hmw, p_bram_rsrc->p_buff_in, p_bram_rsrc->fir_coefs, p_bram_rsrc->fir_state_id, p_bram_rsrc->p_results, HSP_BRAM_RSRC_SAMPLES_NBR, HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_Rfft_f32(hmw, p_bram_rsrc->p_results, HSP_LOG2NBP_256, 0U, 1U, HSP_RFFT_TYPE_1, HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;

  /* Compute the magnitude of RFFT results */
  mw_status = HSP_SEQ_CmplxMag_f32(hmw, p_bram_rsrc->p_results, p_bram_rsrc->p_results, HSP_BRAM_RSRC_SAMPLES_NBR, HSP_SEQ_IOTYPE_DEFAULT);
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_SetTrgo(hmw, HSP_SEQ_TRGO_0);
  if (mw_status != HSP_CORE_OK) error++;

  mw_status = HSP_SEQ_StopRecordPL(hmw);
  if (mw_status != HSP_CORE_OK) error++;

  /* Configure the Event with DMA as trigger */
  hsp_seq_event_trigger_config_t trigger_cfg;
  trigger_cfg.polarity = HSP_SEQ_TRGIN_POLARITY_RISING;
  trigger_cfg.source = HSP_TRGIN_DMA_TC_0;
  trigger_cfg.evt_sync = HSP_SEQ_EVENT_SYNC_TCU_DISABLED;

  mw_status = HSP_SEQ_EVENT_SetConfig_Trigger(hmw, HSP_SEQ_PL_ID_FIR_FFT, &trigger_cfg);
  if (mw_status != HSP_CORE_OK) error++;

  return error;
}
