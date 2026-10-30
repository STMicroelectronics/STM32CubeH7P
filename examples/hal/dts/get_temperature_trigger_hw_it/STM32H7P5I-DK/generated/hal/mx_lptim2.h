/**
  ******************************************************************************
  * @file           : mx_lptim2.h
  * @brief          : Header for mx_lptim2.c file.
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
#ifndef MX_LPTIM2_H
#define MX_LPTIM2_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/******************************************************************************/
/* Exported functions for SW instance in HAL layer */
/******************************************************************************/
/**
  * @brief mx_lptim2 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_lptim_handle_t *mx_lptim2_init(void);

/**
  * @brief  De-initialize mx_lptim2 instance and return it.
  */
void mx_lptim2_deinit(void);

/**
  * @brief  Get the mx_lptim2 object.
  * @retval Pointer on the mx_lptim2 Handle
  */
hal_lptim_handle_t *mx_lptim2_gethandle(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_LPTIM2_H */
