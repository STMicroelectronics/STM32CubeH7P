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
#include "stm32_ll.h"
#include "mx_cortex_mpu.h"
#include "mx_cortex_nvic.h"
#include "mx_cortex_scb.h"
#include "mx_gpio_default.h"
#include "mx_pwr.h"
#include "mx_rcc.h"
#include "mx_rtc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
  /* *************************************************************
    Cortex_MPU (LL): No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for CMSIS instance
    ************************************************************* */

  /* *************************************************************
    Cortex_NVIC (LL): No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for CMSIS instance
    ************************************************************* */

  /* *************************************************************
    Cortex_SCB (LL): No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for CMSIS instance
    ************************************************************* */

  /* *************************************************************
    PWR (LL): No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for CMSIS instance
    ************************************************************* */

  /* ***********************************************************
                Aliases to RCC used in LL
    *********************************************************** */
#define mx_clock  RCC

  /* ***********************************************************
                Aliases to RTC used in LL
    *********************************************************** */
#define MX_RTCx  RTC

/* Exported macros -----------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

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

  /* *************************************************************
    gpio_default: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_gpio_default_init
    ************************************************************* */

  /* *************************************************************
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_init
    ************************************************************* */

  /* ***********************************************************
      RCC: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_rcc with LL layer
  *         Name of the User label:
  *                   mx_clock
  * @retval RCC Pointer on the RCC
  */
#define mx_clock_init mx_rcc_init

  /* ***********************************************************
      RTC: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_rtc with LL layer
  *         Name of the User label:
  *                   MX_RTCx
  * @retval RTC Pointer on the RTC
  */
#define mx_rtcx_init mx_rtc_init

/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

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

  /* *************************************************************
    gpio_default: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_gpio_default_deinit
    ************************************************************* */

  /* *************************************************************
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_deinit
    ************************************************************* */

  /* ***********************************************************
      RTC: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_rtc with LL layer
  *         Name of the User label:
  *                   MX_RTCx
  */
#define mx_rtcx_deinit mx_rtc_deinit

/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* ########################################################### */

/* ########### Aliases to get IRQ Handlers functions ########### */
  /* *************************************************************
    RTC: RTC Wakeup/alarmA+B/timestamp/SSRU interrupt through the EXTI line
    Alias on RTC_IRQHandler and RTC_IRQn
    ************************************************************* */
#define mx_rtcx_irqhandler RTC_IRQHandler
#define MX_RTCX_IRQN       RTC_IRQn

  /* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
