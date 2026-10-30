/**
  ******************************************************************************
  * @file    mx_app_hsp_engine_bram_alloc.h
  * @brief   Header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_APP_HSP_ENGINE_BRAM_ALLOC_H
#define MX_APP_HSP_ENGINE_BRAM_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define HSP_BRAM_RSRC_INPUT_SIGNAL_SAMPLES_SIZE  250U
#define HSP_BRAM_RSRC_FIR_COEF_SIZE  51U
#define HSP_BRAM_RSRC_FIR_STATE_TAPS_SIZE  HSP_BRAM_RSRC_FIR_COEF_SIZE
#define HSP_BRAM_RSRC_OUTPUT_SAMPLES_SIZE  250U

/* Exported macros -----------------------------------------------------------*/
/* Exported variables ------------------------------------------------------- */
/* HSP BRAM Static resources */
// extern float32_t rms_kpi;  /* RMS KPI */

/* HSP BRAM Dynamic resources */
// extern hsp_filter_state_identifier_t fir_state_id;  /* BRAM FIR State Identifier */
// extern float32_t *p_buff_in;  /* BRAM Input Buffer */
// extern float32_t *p_coef;  /* BRAM FIR Coefficient Buffer */
// extern float32_t *p_buff_out;  /* BRAM Output Buffer */
// extern float32_t *p_buff_expected;  /* BRAM Expected Output Buffer */

typedef struct {

  /* HSP BRAM Resources allocated statically */
  float32_t *p_rms_kpi;

  /* HSP BRAM Resources allocated dynamically */
  /* ... */
  hsp_filter_state_identifier_t fir_state_id;  /* BRAM FIR State Identifier */
  float32_t *p_buff_in;  /* BRAM Input Buffer */
  float32_t *p_coef;  /* BRAM FIR Coefficient Buffer */
  float32_t *p_buff_out;  /* BRAM Output Buffer */
  float32_t *p_buff_expected;  /* BRAM Expected Output Buffer */

} hsp_bram_resources_t;

hsp_bram_resources_t *mx_app_hsp_engine_bram_getresources(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_APP_HSP_ENGINE_BRAM_ALLOC_H */
