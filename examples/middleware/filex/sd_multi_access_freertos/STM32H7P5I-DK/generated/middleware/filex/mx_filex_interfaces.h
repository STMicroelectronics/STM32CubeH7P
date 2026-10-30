/**
  ******************************************************************************
  * @file           : mx_filex_interfaces.h
  * @brief          : FileX applicative file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_filex_license.md file
  * in the same directory as the generated code.
  * If no mx_filex_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MX_FILEX_INTERFACES_H__
#define __MX_FILEX_INTERFACES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mx_hal_def.h"
#include "stm32_fx_sd_dma_os_driver.h"

/* Exported types ------------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
#define mx_filex_driver_0  stm32_fx_sd_dma_os_driver
#define volume_name_0 "STM32_VOLUME"


/* Exported functions prototypes ---------------------------------------------*/
VOID *mx_filex_driver_0_get_ctx(VOID);

#ifdef __cplusplus
}
#endif

#endif /* __MX_FILEX_INTERFACES_H__ */
