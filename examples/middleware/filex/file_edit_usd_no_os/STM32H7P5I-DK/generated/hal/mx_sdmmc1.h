/**
  ******************************************************************************
  * @file           : mx_sdmmc1.h
  * @brief          : Header for mx_sdmmc1.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_stm32h7pxx_hal_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_stm32h7pxx_hal_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_SDMMC1_H
#define MX_SDMMC1_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for SD in HAL layer */
/******************************************************************************/
/**
  * @brief mx_sdmmc1_sd init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_sd_handle_t *mx_sdmmc1_sd_init(void);

/**
  * @brief  De-initialize sdmmc1 instance and return it.
  */
void mx_sdmmc1_sd_deinit(void);
/**
  * @brief  Get the SDMMC1 object.
  * @retval Pointer on the SDMMC1 Handle
  */
hal_sd_handle_t *mx_sdmmc1_sd_gethandle(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_SDMMC1_H */
