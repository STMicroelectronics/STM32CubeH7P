
/**
  ******************************************************************************
  * @file           : mx_rcc.c
  * @brief          : STM32 RCC program body
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

/* Includes ------------------------------------------------------------------*/
#include "mx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/******************************************************************************/
/* Exported functions for RCC in HAL layer */
/******************************************************************************/

/**
  * Configure the system core clock only and activate it using the HAL RCC unitary APIs (footprint optimization)
  *         The system Clock is configured as follow :
  *            System Clock source            = HSI
  *            SYSCLK(Hz)                     = 64000000
  *            CPUCLK(Hz)                     = 64000000
  *            AXICLK/ACLK(Hz)                = 32000000
  *            CPU Prescaler                  = 1
  *            ACLK Prescaler                 = 2
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 2
  *            APB4 Prescaler                 = 2
  *            Flash Latency(WS)              = 6
  */
system_status_t mx_rcc_init(void)
{
  /* Configure the Voltage scaling level */
  if (HAL_PWR_SetMainRegulatorVoltageScalingRange(HAL_PWR_VOLT_SCALE_0) != HAL_OK)
  {
    return SYSTEM_POWER_ERROR;
  }

  if (HAL_RCC_HSI_Enable(HAL_RCC_HSI_DIV1) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /** Initializes the CPU, AHB and APB busses clocks */
  hal_rcc_bus_clk_config_t config_bus;
  config_bus.sysclk_prescaler = HAL_RCC_SYSCLK_PRESCALER1;
  config_bus.aclk_prescaler   = HAL_RCC_ACLK_PRESCALER2;
  config_bus.pclk1_prescaler  = HAL_RCC_PCLK_PRESCALER2;
  config_bus.pclk2_prescaler  = HAL_RCC_PCLK_PRESCALER2;
  config_bus.pclk4_prescaler  = HAL_RCC_PCLK_PRESCALER2;
  if (HAL_RCC_SetBusClockConfig(&config_bus) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_HSI) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /* Frequency has been decreased */
  if (HAL_FLASH_ITF_SetLatency(HAL_FLASH, HAL_FLASH_ITF_LATENCY_6) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }
  if (HAL_FLASH_ITF_SetProgrammingDelay(HAL_FLASH, HAL_FLASH_ITF_PROGRAM_DELAY_3) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (HAL_UpdateCoreClock() != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /* No GPIO configuration required for RCC */

  return SYSTEM_OK;
}

void mx_rcc_deinit(void)
{
  HAL_RCC_Reset();
}

/**
  * configures and activate the clocks used by all the peripherals selected within the project
  */
system_status_t mx_rcc_peripherals_clock_config(void)
{
  /* Resources using PCLK1 (16 MHz):
    USART2
  */

  /* Resources using PLL2 (86 MHz):
    SDMMC1
  */

  hal_rcc_pll_config_t config_pll2;
  config_pll2.pll_source      = HAL_RCC_PLL_SRC_HSI;
  config_pll2.pll_m           = 32U;
  config_pll2.pll_n           = 129U;
  config_pll2.pll_p           = 3U;
  config_pll2.pll_q           = 1U;
  config_pll2.pll_r           = 1U;
  config_pll2.pll_s           = 3U;
  config_pll2.pll_t           = 1U;
  config_pll2.pll_fracn       = 0U;
  config_pll2.pll_input_range = HAL_RCC_PLL_INPUT_RANGE_2_4;
  config_pll2.pll_vco_range   = HAL_RCC_PLL_VCO_RANGE_150_420;
  config_pll2.pll_sscg_state  = HAL_RCC_PLL_SSCG_DISABLE;
  if (HAL_RCC_PLL2_SetConfig(&config_pll2) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (HAL_RCC_PLL2_Enable() != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  /* Resources using PLL2S (86 MHz):
    SDMMC1
  */
  if (HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL2_OUTPUT_S) != HAL_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  return SYSTEM_OK;
}
