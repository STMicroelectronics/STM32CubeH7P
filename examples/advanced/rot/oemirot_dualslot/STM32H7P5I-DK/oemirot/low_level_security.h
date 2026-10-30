/**
  ******************************************************************************
  * @file    low_level_security.h
  * @brief   Header for low_level_security.c module
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOW_LEVEL_SECURITY_H
#define LOW_LEVEL_SECURITY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "boot_hal_cfg.h"
#include "flash_layout.h"

void  SECURITY_ApplyTamperEarlyStartup(void);
void  SECURITY_EnableCryptoClocks(void);
void  SECURITY_DisableCryptoClocks(void);
void  SECURITY_ApplyRunTimeProtections(void);
void  SECURITY_UpdateRunTimeProtections(void);
void  SECURITY_CheckStaticProtections(void);
void  SECURITY_UpdateLoaderRunTimeProtections(void);
void  SECURITY_SetLoaderCodeSecure(void);

/* Exported types ------------------------------------------------------------*/
/* ToDo: BEGIN: TEMPORARY ----------------------------------------------------*/
typedef uint32_t (*RSSLIB_JumpHDPlvl2_TypeDef)(uint32_t VectorTableAddr, uint32_t MPUIndex);
typedef uint32_t (*RSSLIB_JumpHDPlvl3_TypeDef)(uint32_t VectorTableAddr, uint32_t MPUIndex);
typedef uint32_t (*RSSLIB_GetProductState_TypeDef)(void);

typedef struct
{
  uint32_t Reserved1[11];                              /* Address offset 0x00 */
  __IM RSSLIB_JumpHDPlvl2_TypeDef     JumpHDPLvl2;     /* Address offset 0x2C */
  __IM RSSLIB_JumpHDPlvl3_TypeDef     JumpHDPLvl3;     /* Address offset 0x30 */
  __IM RSSLIB_GetProductState_TypeDef GetProductState; /* Address offset 0x34 */
} rss_descriptor_t;

#define RSSLIB_PFUNC      ((rss_descriptor_t *)RSSLIB_PFUNC_BASE_NS)
/* END: TEMPORARY ------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* LOW_LEVEL_SECURITY_H */
