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
#include "hsp.h"

/* Exported constants --------------------------------------------------------*/
#define HSP_BRAM_RSRC_SAMPLES_NBR  (256U)
#define HSP_BRAM_RSRC_FIR_COEF_SIZE  (32U)

#define HSP_BRAM_RSRC_FIR_STATE_TAPS_SIZE  HSP_BRAM_RSRC_FIR_COEF_SIZE

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
  float32_t *fir_coefs;
  uint32_t *pl_call;

  hsp_filter_state_identifier_t fir_state_id;
  float32_t *p_buff_in;
  float32_t *p_results;
} hsp_bram_resources_t;

/* Exported functions -----------------------------------------------------------*/
hsp_bram_resources_t *mx_app_hsp_engine_bram_getresources(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_APP_HSP_ENGINE_BRAM_ALLOC_H */
