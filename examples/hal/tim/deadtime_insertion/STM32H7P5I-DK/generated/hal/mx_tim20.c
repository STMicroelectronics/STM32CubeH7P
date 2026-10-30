/**
  ******************************************************************************
  * @file           : mx_tim20.c
  * @brief          : Peripheral initialization
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
#include "mx_tim20.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_tim_handle_t hTIM20;

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for TIM20 in HAL layer */
/******************************************************************************/
hal_tim_handle_t *mx_tim20_init(void)
{
  if (HAL_TIM_Init(&hTIM20, HAL_TIM20) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_TIM20_EnableClock();

  /* Timer configuration to reach the output frequency at 8 kHz */
  hal_tim_config_t config;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  config.prescaler              = 8124;
  config.counter_mode           = HAL_TIM_COUNTER_UP;
  config.period                 = 0x7;
  config.repetition_counter     = 0;
  if (HAL_TIM_SetConfig(&hTIM20, &config) != HAL_OK)
  {
    return NULL;
  }

  /* Sampling Clock */
  if (HAL_TIM_SetDTSPrescaler(&hTIM20, HAL_TIM_DTS_DIV2) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_TIM_SetDTS2Prescaler(&hTIM20, HAL_TIM_DTS2_DIV1) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_oc_channel_config_t oc_config;

  oc_config.polarity       = HAL_TIM_OC_HIGH;
  oc_config.idle_state     = HAL_TIM_OC_IDLE_STATE_RESET;
  oc_config.override_state = HAL_TIM_OC_OVERRIDE_RESET;
  oc_config.break_mode     = HAL_TIM_OC_BREAKMODE_IMMEDIATE;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM20, HAL_TIM_CHANNEL_2, &oc_config) != HAL_OK)
  {
    return NULL;
  }

  oc_config.polarity       = HAL_TIM_OC_HIGH;
  oc_config.idle_state     = HAL_TIM_OC_IDLE_STATE_RESET;
  oc_config.override_state = HAL_TIM_OC_OVERRIDE_RESET;
  oc_config.break_mode     = HAL_TIM_OC_BREAKMODE_IMMEDIATE;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM20, HAL_TIM_CHANNEL_2N, &oc_config) != HAL_OK)
  {
    return NULL;
  }
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x4;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_2,
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_OC_EnableComparePreload(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_2) != HAL_OK)
  {
    return NULL;
  }

  /* Update Event Management */
  if (HAL_TIM_SetUpdateSource(&hTIM20, HAL_TIM_UPDATE_REGULAR) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_TIM_EnableUpdateGeneration(&hTIM20) != HAL_OK)
  {
    return NULL;
  }

  /* Deadtime Configuration */
  if (HAL_TIM_SetDeadtime(&hTIM20, 252, 252) != HAL_OK)
  {
    return NULL;
  }

  /* ### TIM20 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOC_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PC2     ------>   TIM20_CH2
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_9;
  HAL_GPIO_Init(HAL_GPIOC, HAL_GPIO_PIN_2, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PC3     ------>   TIM20_CH2N
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_8;
  HAL_GPIO_Init(HAL_GPIOC, HAL_GPIO_PIN_3, &gpio_config);

  return &hTIM20;
}

void mx_tim20_deinit(void)
{
  (void)HAL_TIM_DeInit(&hTIM20);

  HAL_RCC_TIM20_DisableClock();

  HAL_RCC_TIM20_Reset();

  /* De-initialize all GPIOC pins associated with TIM20 */
  HAL_GPIO_DeInit(HAL_GPIOC, HAL_GPIO_PIN_2 | HAL_GPIO_PIN_3);
}

hal_tim_handle_t *mx_tim20_gethandle(void)
{
  return &hTIM20;
}
