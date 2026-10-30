/**
  ******************************************************************************
  * @file           : mx_filex_interfaces.c
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
      
/* Includes ------------------------------------------------------------------*/
#include "mx_filex_interfaces.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static STM32_FX_SD_DRIVER_CONTEXT mx_stm32_fx_sd_ctx_0;

/* Private function prototypes -----------------------------------------------*/
/* get the internal object */
VOID *mx_filex_driver_0_get_ctx(VOID)
{
  mx_stm32_fx_sd_ctx_0.flags = FX_SD_FLAG_CACHE_MAINTENANCE;
  mx_stm32_fx_sd_ctx_0.sd_max_timeout = 10000;
  mx_stm32_fx_sd_ctx_0.sd_handle = mx_sdmmc1_sd_gethandle();
  return (VOID *)&mx_stm32_fx_sd_ctx_0;
}

