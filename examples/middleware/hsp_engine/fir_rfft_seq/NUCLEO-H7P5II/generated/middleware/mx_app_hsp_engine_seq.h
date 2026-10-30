/**
  ******************************************************************************
  * @file    mx_app_hsp_engine_seq.h
  * @brief   Header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_APP_HSP_ENGINE_SEQ_H
#define MX_APP_HSP_ENGINE_SEQ_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp.h"

/* Declare all #define related to the Processing List IDs

  - For Processing List ID not attached to any event, just set a unsigned int value in range[1..N] where N depend of
    the STM32 Device (see Reference Manual)
      #define HSP_SEQ_PL_ID_FIR         2U
      #define HSP_SEQ_PL_ID_TRIG_OUTPUT  30U

  - For Processing List ID attached to an event, use HSP_SEQ_EVENT_x value
      #define HSP_SEQ_PL_ID_FIR_EVT_CSEG   HSP_SEQ_EVENT_4
      #define HSP_SEQ_PL_ID_FIR_EVT_TRGIN  HSP_SEQ_EVENT_20
...
 */
#define HSP_SEQ_PL_ID_FIR_FFT         HSP_SEQ_EVENT_2

#define HSP_SEQ_ALL_EVENTS_MASK  \
  (0x0UL                                               \
   | HSP_SEQ_EVENT_ID_TO_BITMASK(HSP_SEQ_PL_ID_FIR_FFT))
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_APP_HSP_ENGINE_SEQ_H */

