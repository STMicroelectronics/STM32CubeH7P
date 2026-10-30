
/**
  ******************************************************************************
  * @file           : mx_adc4.h
  * @brief          : Header for mx_adc4.c file.
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
#ifndef MX_ADC4_H
#define MX_ADC4_H

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
/* Exported functions for ADC in HAL layer */
/******************************************************************************/
/**
  * @brief mx_adc4 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_adc_handle_t *mx_adc4_init(void);

/**
  * @brief  De-initialize adc4 instance and return it.
  */
void mx_adc4_deinit(void);

/**
  * @brief  Get the ADC4 object.
  * @retval Pointer on the ADC4 Handle
  */
hal_adc_handle_t *mx_adc4_gethandle(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_ADC4_H */
