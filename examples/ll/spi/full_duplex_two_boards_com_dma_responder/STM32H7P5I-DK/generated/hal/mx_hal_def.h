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
#include "mx_pwr.h"
#include "mx_rcc.h"
#include "mx_spi5.h"

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

  /* *************************************************************
    RCC (LL): No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for CMSIS instance
    ************************************************************* */

  /* ***********************************************************
                Aliases to SPI5 used in LL
    *********************************************************** */
#define MX_SPIx  SPI5

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
      SPI5: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_spi5 with LL layer
  *         Name of the User label:
  *                   MX_SPIx
  * @retval SPI5 Pointer on the SPI5
  */
#define mx_spix_init mx_spi5_init

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
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_deinit
    ************************************************************* */

  /* ***********************************************************
      SPI5: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_spi5 with LL layer
  *         Name of the User label:
  *                   MX_SPIx
  */
#define mx_spix_deinit mx_spi5_deinit

/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* ########################################################### */

/* ########### Aliases to get IRQ Handlers functions ########### */
  /* *************************************************************
    SPI5: SPI5 global interrupt
    Alias on SPI5_IRQHandler and SPI5_IRQn
    ************************************************************* */
#define mx_spix_irqhandler SPI5_IRQHandler
#define MX_SPIX_IRQN       SPI5_IRQn

  /* *************************************************************
    SPI5 / GPDMA1_CH0: GPDMA1 channel 0 interrupt
    Alias on GPDMA1_CH0_IRQHandler and GPDMA1_CH0_IRQn
    ************************************************************* */
#define mx_lpdmax_ch1y_irqhandler GPDMA1_CH0_IRQHandler
#define MX_LPDMAX_CH1Y_IRQN       GPDMA1_CH0_IRQn

  /* *************************************************************
    SPI5 / GPDMA1_CH1: GPDMA1 channel 1 interrupt
    Alias on GPDMA1_CH1_IRQHandler and GPDMA1_CH1_IRQn
    ************************************************************* */
#define mx_lpdmax_ch2y_irqhandler GPDMA1_CH1_IRQHandler
#define MX_LPDMAX_CH2Y_IRQN       GPDMA1_CH1_IRQn

  /* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
