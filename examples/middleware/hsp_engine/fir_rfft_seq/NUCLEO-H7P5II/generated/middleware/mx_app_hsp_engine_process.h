/**
  ******************************************************************************
  * @file    mx_app_hsp_engine_process.h
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
#ifndef MX_APP_HSP_ENGINE_PROCESS_H
#define MX_APP_HSP_ENGINE_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp.h"

/* Exported functions --------------------------------------------------------*/
uint32_t MX_HSP_Engine_InitiateProcess(void);
uint32_t MX_HSP_Engine_ProcessFIR_FFT(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_APP_HSP_ENGINE_PROCESS_H */

