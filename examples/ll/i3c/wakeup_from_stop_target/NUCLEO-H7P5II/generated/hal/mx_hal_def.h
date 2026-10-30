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
#include "mx_i3c1.h"
#include "mx_pwr.h"
#include "mx_rcc.h"

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

  /* ***********************************************************
                Aliases to I3C1 used in LL
    *********************************************************** */
#define MX_I3Cx  I3C1

  /* ***********************************************************
                Aliases to PWR used in LL
    *********************************************************** */
#define mx_pwrx  PWR

  /* ***********************************************************
                Aliases to RCC used in LL
    *********************************************************** */
#define mx_rccx  RCC

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

  /* ***********************************************************
      I3C1: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_i3c1 with LL layer
  *         Name of the User label:
  *                   MX_I3Cx
  * @retval I3C1 Pointer on the I3C1
  */
#define mx_i3cx_init mx_i3c1_init

  /* ***********************************************************
      PWR: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_pwr with LL layer
  *         Name of the User label:
  *                   mx_pwrx
  * @retval PWR Pointer on the PWR
  */
#define mx_pwrx_init mx_pwr_init

  /* ***********************************************************
      RCC: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_rcc with LL layer
  *         Name of the User label:
  *                   mx_rccx
  * @retval RCC Pointer on the RCC
  */
#define mx_rccx_init mx_rcc_init

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

  /* ***********************************************************
      I3C1: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_i3c1 with LL layer
  *         Name of the User label:
  *                   MX_I3Cx
  */
#define mx_i3cx_deinit mx_i3c1_deinit

  /* ***********************************************************
      PWR: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_pwr with LL layer
  *         Name of the User label:
  *                   mx_pwrx
  */
#define mx_pwrx_deinit mx_pwr_deinit

/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* ########################################################### */

/* ########### Aliases to get IRQ Handlers functions ########### */
  /* *************************************************************
    I3C1: I3C1 event interrupt
    Alias on I3C1_EV_IRQHandler and I3C1_EV_IRQn
    ************************************************************* */
#define mx_i3cx_ev_irqhandler I3C1_EV_IRQHandler
#define MX_I3CX_EV_IRQN       I3C1_EV_IRQn

  /* *************************************************************
    I3C1: I3C1 error interrupt
    Alias on I3C1_ERR_IRQHandler and I3C1_ERR_IRQn
    ************************************************************* */
#define mx_i3cx_err_irqhandler I3C1_ERR_IRQHandler
#define MX_I3CX_ERR_IRQN       I3C1_ERR_IRQn

  /* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
