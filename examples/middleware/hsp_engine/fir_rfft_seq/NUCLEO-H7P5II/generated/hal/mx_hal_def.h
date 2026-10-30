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
#include "mx_cortex_mpu.h"
#include "mx_cortex_nvic.h"
#include "mx_gpio_default.h"
#include "mx_hpdma1_ch0.h"
#include "mx_hpdma1_ch15.h"
#include "mx_hsp1.h"
#include "mx_pwr.h"
#include "mx_rcc.h"

#include "mx_usart2.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* ########### Aliases to initialization functions ########### */

  /* ***********************************************************
      gpio_default: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_gpio_default with HAL layer
  *         Name of the User label:
  *                   mx_gpio_status_led
  * @retval system_status_t Value based on the system_status_t
  */
#define mx_gpio_status_led_init mx_gpio_default_init

/* *********************************************************** */
/*        HSP_MyHSP_1: aliases for initialization functions    */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_hsp1_hal with HAL layer
  *         Name of the User label:
  *                   MyHSP_1
  * @retval system_status_t Value based on the system_status_t
  */
#define myhsp_1_init mx_hsp1_hal_init

#define mx_hsp_init myhsp_1_init

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_icache_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  * @retval hal_icache_handle_t Pointer on the handle on the ICACHE instance
  */
#define myicache_1_init mx_icache_init


/* *********************************************************** */
/*        RCC_MyRCC_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_rcc_hal with HAL layer
  *         Name of the User label:
  *                   MyRCC_1
  * @retval system_status_t Value based on the system_status_t
  */
#define myrcc_1_init mx_rcc_init


  /* *************************************************************
    USART2: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_usart2_uart_init
    ************************************************************* */

/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

/* *********************************************************** */
/*        gpio_default_MyGPIO_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_gpio_default_hal with HAL layer
  *         Name of the User label:
  *                   MyGPIO_1
  *                   mx_gpio_status_led
  */
#define mygpio_1_deinit mx_gpio_default_deinit

#define mx_gpio_status_led_deinit mx_gpio_default_deinit

/* *********************************************************** */
/*        HSP_MyHSP_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_hsp1_hal with HAL layer
  *         Name of the User label:
  *                   MyHSP_1
  */
#define myhsp_1_deinit mx_hsp1_hal_deinit

#define mx_hsp_deinit myhsp_1_deinit


/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_icache_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  */
#define myicache_1_deinit mx_icache_deinit


  /* *************************************************************
    USART2: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_usart2_uart_deinit
    ************************************************************* */

/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* *********************************************************** */
/*        GPIO: aliases for get EXTI object functions */
/* *********************************************************** */

/* *********************************************************** */
/*        HSP_MyHSP_1: aliases for get handle functions  */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for HSP
  *         Name of the User label:
  *                   MyHSP_1
  * @retval hal_hsp_handle_t Pointer on the handle on the HSP instance
  */
#define myhsp_1_gethandle               mx_hsp1_hal_gethandle


/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for get handle functions  */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for ICACHE
  *         Name of the User label:
  *                   MyICACHE_1
  * @retval hal_icache_handle_t Pointer on the handle on the ICACHE instance
  */
#define myicache_1_gethandle mx_icache_gethandle

/* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
