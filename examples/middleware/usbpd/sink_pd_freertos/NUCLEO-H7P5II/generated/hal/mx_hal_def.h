/**
  ******************************************************************************
  * @file           : mx_hal_def.h
  * @brief          : Exporting peripherals initialization
  *                   Include entry for the target folder to the application.
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
#ifndef MX_HAL_DEF_H
#define MX_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "mx_def.h"
#include "stm32_hal.h"
#include "mx_adc4.h"
#include "mx_cortex_mpu.h"
#include "mx_cortex_nvic.h"
#include "mx_cortex_scb.h"
#include "mx_gpio_default.h"
#include "mx_pwr.h"
#include "mx_rcc.h"
#include "mx_tim1.h"
#include "mx_tim6.h"
#include "mx_usart2.h"
#include "mx_ucpd1.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

  /* ***********************************************************
      ADC4: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_adc4 with HAL layer
  *         Name of the User label:
  *                   mx_example_adc
  * @retval hal_adc_handle_t Pointer on the handle on the ADC4 instance
  */
#define mx_example_adc_init mx_adc4_init

  /* *************************************************************
    Cortex_MPU: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_mpu_init
    ************************************************************* */

  /* *************************************************************
    Cortex_NVIC: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_nvic_init
    ************************************************************* */

  /* *************************************************************
    Cortex_SCB: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_scb_init
    ************************************************************* */

  /* ***********************************************************
      gpio_default: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_gpio_default with HAL layer
  *         Name of the User label:
  *                   mx_exti_trigger
  * @retval system_status_t Value based on the system_status_t
  */
#define mx_exti_trigger_init mx_gpio_default_init

  /* *************************************************************
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_init
    ************************************************************* */

  /* *************************************************************
    RCC: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_rcc_init
    ************************************************************* */

  /* ***********************************************************
      TIM1: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_tim1 with HAL layer
  *         Name of the User label:
  *                   mx_example_tim
  * @retval hal_tim_handle_t Pointer on the handle on the TIM1 instance
  */
#define mx_example_tim_init mx_tim1_init

  /* *************************************************************
    TIM6: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_tim6_init
    ************************************************************* */

  /* ***********************************************************
      USART2: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_usart2_uart with HAL layer
  *         Name of the User label:
  *                   mx_example_uart
  * @retval hal_uart_handle_t Pointer on the handle on the USART2 instance
  */
#define mx_example_uart_init mx_usart2_uart_init

  /* ***********************************************************
      UCPD1: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_ucpd1 with HAL layer
  *         Name of the User label:
  *                   mx_example_ucpd
  * @retval hal_ucpd_handle_t Pointer on the handle on the UCPD1 instance
  */
#define mx_example_ucpd_init mx_ucpd1_init

/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

  /* ***********************************************************
      ADC4: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_adc4 with HAL layer
  *         Name of the User label:
  *                   mx_example_adc
  */
#define mx_example_adc_deinit mx_adc4_deinit

  /* *************************************************************
    Cortex_MPU: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_mpu_deinit
    ************************************************************* */

  /* *************************************************************
    Cortex_NVIC: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_nvic_deinit
    ************************************************************* */

  /* *************************************************************
    Cortex_SCB: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_scb_deinit
    ************************************************************* */

  /* ***********************************************************
      gpio_default: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_gpio_default with HAL layer
  *         Name of the User label:
  *                   mx_exti_trigger
  */
#define mx_exti_trigger_deinit mx_gpio_default_deinit

  /* *************************************************************
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_deinit
    ************************************************************* */

  /* ***********************************************************
      TIM1: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_tim1 with HAL layer
  *         Name of the User label:
  *                   mx_example_tim
  */
#define mx_example_tim_deinit mx_tim1_deinit

  /* *************************************************************
    TIM6: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_tim6_deinit
    ************************************************************* */

  /* ***********************************************************
      USART2: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_usart2_uart with HAL layer
  *         Name of the User label:
  *                   mx_example_uart
  */
#define mx_example_uart_deinit mx_usart2_uart_deinit

  /* ***********************************************************
      UCPD1: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_ucpd1 with HAL layer
  *         Name of the User label:
  *                   mx_example_ucpd
  */
#define mx_example_ucpd_deinit mx_ucpd1_deinit

/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

  /* ***********************************************************
      ADC4: aliases for get handle functions
    *********************************************************** *//**
  * @brief  Get the HAL handle for ADC4
  *         Name of the User label:
  *                   mx_example_adc
  * @retval hal_adc_handle_t Pointer on the handle on the ADC4 instance
  */
#define mx_example_adc_gethandle mx_adc4_gethandle

  /* *************************************************************
    gpio_default / EXTI0: No EXTI software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_gpio_default_exti0_gethandle
    ************************************************************* */

  /* ***********************************************************
      TIM1: aliases for get handle functions
    *********************************************************** *//**
  * @brief  Get the HAL handle for TIM1
  *         Name of the User label:
  *                   mx_example_tim
  * @retval hal_tim_handle_t Pointer on the handle on the TIM1 instance
  */
#define mx_example_tim_gethandle mx_tim1_gethandle

  /* *************************************************************
    TIM6: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_tim6_gethandle
    ************************************************************* */

  /* ***********************************************************
      USART2: aliases for get handle functions
    *********************************************************** *//**
  * @brief  Get the HAL handle for USART2
  *         Name of the User label:
  *                   mx_example_uart
  * @retval hal_uart_handle_t Pointer on the handle on the USART2 instance
  */
#define mx_example_uart_gethandle mx_usart2_uart_gethandle

  /* ***********************************************************
      UCPD1: aliases for get handle functions
    *********************************************************** *//**
  * @brief  Get the HAL handle for UCPD1
  *         Name of the User label:
  *                   mx_example_ucpd
  * @retval hal_ucpd_handle_t Pointer on the handle on the UCPD1 instance
  */
#define mx_example_ucpd_gethandle mx_ucpd1_gethandle

/* ########################################################### */

/* ########### Aliases to get IRQ Handlers functions ########### */
  /* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
