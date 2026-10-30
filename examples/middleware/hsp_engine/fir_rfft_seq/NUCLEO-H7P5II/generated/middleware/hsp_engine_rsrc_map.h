/**
  ******************************************************************************
  * @file    hsp_engine_rsrc_map.h
  * @brief   Header file for interfaces
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
#ifndef HSP_ENGINE_RSRC_MAP_H
#define HSP_ENGINE_RSRC_MAP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "interface.h"
#include "stm32_hal.h" /* Select the hal file corresponding to the device in use (i.e. stm32f3xx_hal.h, stm32f0xx_hal.h, ...) */
#include "hsp_api_def.h"

/* Exported constants --------------------------------------------------------*/
/* Defines for HSP TRGIN sources ---------------------------------------------*/
#define HSP_TRGIN_DMA_TC_0  ((uint32_t)HAL_HSP1_TRGIN_HPDMA_CH15_TC)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_ENGINE_RSRC_MAP_H */
