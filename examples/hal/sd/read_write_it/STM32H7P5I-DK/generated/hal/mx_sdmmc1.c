/**
  ******************************************************************************
  * @file           : mx_sdmmc1.c
  * @brief          : SDMMC1 Peripheral initialization
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
#include "mx_sdmmc1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_sd_handle_t hSDMMC1;

/******************************************************************************/
/* Exported functions for SDMMC1 in HAL layer                                 */
/******************************************************************************/
hal_sd_handle_t *mx_sdmmc1_sd_init(void)
{
  hal_sd_config_t sd_config;

  if (HAL_SD_Init(&hSDMMC1, HAL_SD_CARD_1) != HAL_OK)
  {
    return NULL;
  }

  /* SD GPIO Configuration **************************************************/
  /* ### SDMMC1 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOE_EnableClock();

  HAL_RCC_GPIOA_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PE2     ------>   SDMMC1_CK
       PE3     ------>   SDMMC1_D0
       PE4     ------>   SDMMC1_D1
       PE5     ------>   SDMMC1_D2
       PE6     ------>   SDMMC1_D3
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_14;
  HAL_GPIO_Init(HAL_GPIOE, HAL_GPIO_PIN_2 | HAL_GPIO_PIN_3 | HAL_GPIO_PIN_4 | HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PA5     ------>   SDMMC1_CMD
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_5, &gpio_config);

  if (HAL_RCC_SDMMC1_SetKernelClkSource(HAL_RCC_SDMMC1_CLK_SRC_PLL2S) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_SDMMC1_EnableClock();

  sd_config.clk_cfg.clk_edge       = HAL_SD_CLOCK_EDGE_FALLING;
  sd_config.clk_cfg.clk_power_save = HAL_SD_CLOCK_POWER_SAVE_DISABLE;
  sd_config.bus_wide               = HAL_SD_BUS_WIDE_4BIT;
  sd_config.hw_flow_ctrl           = HAL_SD_HARDWARE_FLOW_CONTROL_ENABLE;
  sd_config.clk_cfg.clk_hz         = 20000000;

  sd_config.transceiver            = HAL_SD_TRANSCEIVER_NOT_PRESENT;
  sd_config.data_timeout_cycle     = HAL_SD_DATA_MAX_TIMEOUT;
  sd_config.stop_xfer_timeout_ms   = HAL_SD_STOP_XFER_MAX_TIMEOUT;
  sd_config.erase_timeout_ms       = HAL_SD_ERASE_MAX_TIMEOUT;
  if (HAL_SD_SetConfig(&hSDMMC1, &sd_config) != HAL_OK)
  {
    return NULL;
  }
    /* Enable the interruption for SD */
  HAL_CORTEX_NVIC_SetPriority(SDMMC1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(SDMMC1_IRQn);
  return &hSDMMC1;
}

void mx_sdmmc1_sd_deinit(void)
{
  /* Disable the interuption for SD */
  HAL_CORTEX_NVIC_DisableIRQ(SDMMC1_IRQn);

  (void)HAL_SD_DeInit(&hSDMMC1);

  HAL_RCC_SDMMC1_Reset();

  HAL_RCC_SDMMC1_DisableClock();

  /* De-initialize all GPIOE pins associated with SDMMC1 */
  HAL_GPIO_DeInit(HAL_GPIOE, HAL_GPIO_PIN_2 | HAL_GPIO_PIN_3 | HAL_GPIO_PIN_4 | HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6);

  /* De-initialize all GPIOA pins associated with SDMMC1 */
  HAL_GPIO_DeInit(HAL_GPIOA, HAL_GPIO_PIN_5);
}

hal_sd_handle_t *mx_sdmmc1_sd_gethandle(void)
{
  return &hSDMMC1;
}

/******************************************************************************/
/*                          SDMMC1 global interrupt                           */
/******************************************************************************/
void SDMMC1_IRQHandler(void)
{
  HAL_SD_IRQHandler(&hSDMMC1);
}
