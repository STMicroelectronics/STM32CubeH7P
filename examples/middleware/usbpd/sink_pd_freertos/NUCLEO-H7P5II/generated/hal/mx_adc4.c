/**
  ******************************************************************************
  * @file           : mx_adc4.c
  * @brief          : ADC4 Peripheral initialization
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
#include "mx_adc4.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_adc_handle_t hADC4;

/******************************************************************************/
/* Exported functions for ADC4 in HAL layer */
/******************************************************************************/
hal_adc_handle_t *mx_adc4_init(void)
{
  if (HAL_ADC_Init(&hADC4, HAL_ADC4) != HAL_OK)
  {
    return NULL;
  }

    HAL_RCC_ADC34_EnableClock();

  if (HAL_RCC_ADC_SetKernelClkSource(HAL_RCC_ADC_CLK_SRC_HCLK3) != HAL_OK)
  {
    return NULL;
  }

  hal_adc_config_t adc_config;
  hal_adc_channel_config_t adc_channel_config;

  adc_config.resolution          = HAL_ADC_RESOLUTION_8_BIT;
  adc_config.sampling_mode       = HAL_ADC_SAMPLING_MODE_NORMAL;
  if (HAL_ADC_SetConfig(&hADC4, &adc_config) != HAL_OK)
  {
    return NULL;
  }

  /****************************************************************************/
  /* Configuration of basic features (mandatory)                              */
  /****************************************************************************/

  /* ==================== Group Regular ====================*/
  hal_adc_reg_config_t reg_config;
  reg_config.trigger_src        = HAL_ADC_REG_TRIG_SOFTWARE;
  reg_config.sequencer_length   = 1;
  reg_config.sequencer_discont  = HAL_ADC_REG_SEQ_DISCONT_DISABLE;
  reg_config.continuous         = HAL_ADC_REG_CONV_CONTINUOUS;
  reg_config.overrun            = HAL_ADC_REG_OVR_DATA_OVERWRITTEN;
  reg_config.data_transfer      = HAL_ADC_REG_DATA_TRANSFER_NONE;
  if (HAL_ADC_REG_SetConfig(&hADC4, &reg_config) != HAL_OK)
  {
    return NULL;
  }

  adc_channel_config.group           = HAL_ADC_GROUP_REGULAR;
  adc_channel_config.sequencer_rank  = 1;
  adc_channel_config.sampling_time   = HAL_ADC_SAMPLING_TIME_848CYCLES_5;
  adc_channel_config.input_mode      = HAL_ADC_IN_SINGLE_ENDED;
  if (HAL_ADC_SetConfigChannel(&hADC4, HAL_ADC_CHANNEL_17, &adc_channel_config) != HAL_OK)
  {
    return NULL;
  }

  /****************************************************************************/
  /* Configuration of additional features (optional)                          */
  /****************************************************************************/

  /* ### ADC4 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOE_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PE9     ------>   ADC4_INP17
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ANALOG;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  HAL_GPIO_Init(HAL_GPIOE, HAL_GPIO_PIN_9, &gpio_config);

  return &hADC4;
}

void mx_adc4_deinit(void)
{
  (void)HAL_ADC_DeInit(&hADC4);

  HAL_RCC_ADC34_DisableClock();

  HAL_RCC_ADC34_Reset();

  /* De-initialize all GPIOE pins associated with ADC4 */
  HAL_GPIO_DeInit(HAL_GPIOE, HAL_GPIO_PIN_9);
}

hal_adc_handle_t *mx_adc4_gethandle(void)
{
  return &hADC4;
}
