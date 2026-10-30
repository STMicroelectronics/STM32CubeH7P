/**
  ******************************************************************************
  * @file           : mx_gpio_default.h
  * @brief          : Header for mx_gpio_default.c file.
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
#ifndef MX_GPIO_DEFAULT_H
#define MX_GPIO_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/******************************************************************************/
/* Exported defines for gpio_default in HAL layer                             */
/******************************************************************************/

/* GPIO pin aliases for PF0 */
#define UCPD_FLT_PORT                                   HAL_GPIOF
#define UCPD_FLT_PIN                                    HAL_GPIO_PIN_0

#define MX_EXTI_TRIGGER_PORT                            HAL_GPIOF
#define MX_EXTI_TRIGGER_PIN                             HAL_GPIO_PIN_0

/* GPIO pin aliases for PF5 */
#define UCPD_DBN_PORT                                   HAL_GPIOF
#define UCPD_DBN_PIN                                    HAL_GPIO_PIN_5
#define UCPD_DBN_INIT_STATE                             HAL_GPIO_PIN_SET
#define UCPD_DBN_ACTIVE_STATE                           HAL_GPIO_PIN_SET
#define UCPD_DBN_INACTIVE_STATE                         HAL_GPIO_PIN_RESET

/* GPIO pin aliases for PG9 */
#define PG9_PORT                                        HAL_GPIOG
#define PG9_PIN                                         HAL_GPIO_PIN_9
#define PG9_INIT_STATE                                  HAL_GPIO_PIN_RESET
#define PG9_ACTIVE_STATE                                HAL_GPIO_PIN_SET
#define PG9_INACTIVE_STATE                              HAL_GPIO_PIN_RESET

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for gpio_default in HAL layer                           */
/******************************************************************************/
/**
  * @brief mx_gpio_default init function
  * This function configures the hardware resources used in this example
  * @retval 0  GPIO group correctly initialized
  * @retval -1 Issue detected during GPIO group initialization
  */
system_status_t mx_gpio_default_init(void);

/**
  * @brief  De-initialize gpio_default instance.
  */
system_status_t mx_gpio_default_deinit(void);

/**
  * @brief  Get the EXTI0 object.
  * @retval Pointer on the EXTI0 Handle
  */
hal_exti_handle_t *mx_gpio_default_exti0_gethandle(void);

/******************************************************************************/
/*                EXTI Line 0 interrupt through the EXTI line                 */
/******************************************************************************/
void EXTI0_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_GPIO_DEFAULT_H */
