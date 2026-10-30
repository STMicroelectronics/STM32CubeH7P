/**
  ******************************************************************************
  * @file           : mx_tim5.c
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
#include "mx_tim5.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_tim_handle_t hTIM5;

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for TIM5 in HAL layer */
/******************************************************************************/
hal_tim_handle_t *mx_tim5_init(void)
{
  if (HAL_TIM_Init(&hTIM5, HAL_TIM5) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_TIM5_EnableClock();

  /* Timer configuration to reach the output frequency at 24.39 kHz */
  hal_tim_config_t config;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  config.prescaler              = 519;
  config.counter_mode           = HAL_TIM_COUNTER_UP;
  config.period                 = 0x28;
  config.repetition_counter     = 0;
  if (HAL_TIM_SetConfig(&hTIM5, &config) != HAL_OK)
  {
    return NULL;
  }

  /* Sampling Clock */
  if (HAL_TIM_SetDTSPrescaler(&hTIM5, HAL_TIM_DTS_DIV1) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_TIM_SetDTS2Prescaler(&hTIM5, HAL_TIM_DTS2_DIV1) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_oc_channel_config_t oc_config;

  oc_config.polarity       = HAL_TIM_OC_LOW;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM5, HAL_TIM_CHANNEL_1, &oc_config) != HAL_OK)
  {
    return NULL;
  }
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x14;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM5, HAL_TIM_OC_COMPARE_UNIT_1,
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_OC_EnableComparePreload(&hTIM5, HAL_TIM_OC_COMPARE_UNIT_1) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_ic_channel_config_t ic_config;

  ic_config.source    = HAL_TIM_INPUT_TIM5_TI2_GPIO;
  ic_config.polarity  = HAL_TIM_IC_RISING;
  ic_config.filter    = HAL_TIM_FDIV1;
  if (HAL_TIM_IC_SetConfigChannel(&hTIM5, HAL_TIM_CHANNEL_2, &ic_config) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_ic_capture_unit_config_t ic_capture_unit_config;

  ic_capture_unit_config.source     = HAL_TIM_IC_DIRECT;
  ic_capture_unit_config.prescaler  = HAL_TIM_IC_DIV1;
  if (HAL_TIM_IC_SetConfigCaptureUnit(&hTIM5, HAL_TIM_IC_CAPTURE_UNIT_2, &ic_capture_unit_config) != HAL_OK)
  {
    return NULL;
  }

  /* Update Event Management */
  if (HAL_TIM_SetUpdateSource(&hTIM5, HAL_TIM_UPDATE_REGULAR) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_TIM_EnableUpdateGeneration(&hTIM5) != HAL_OK)
  {
    return NULL;
  }

  /* Slave Mode Configuration */
  hal_tim_slave_config_t slave_config;
  slave_config.mode     = HAL_TIM_SLAVE_GATED;
  slave_config.trigger  = HAL_TIM_TRIG_TI2FP2;
  if (HAL_TIM_SetSynchroSlave(&hTIM5, &slave_config) != HAL_OK)
  {
    return NULL;
  }

  /* Master Mode Configuration */
  if (HAL_TIM_SetTriggerOutput(&hTIM5, HAL_TIM_TRGO_ENABLE) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_EnableMasterSlaveMode(&hTIM5) != HAL_OK)
  {
    return NULL;
  }

  /* ### TIM5 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOF_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PF6     ------>   TIM5_CH1
       PF7     ------>   TIM5_CH2
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_4;
  HAL_GPIO_Init(HAL_GPIOF, HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7, &gpio_config);

  return &hTIM5;
}

void mx_tim5_deinit(void)
{
  (void)HAL_TIM_DeInit(&hTIM5);

  HAL_RCC_TIM5_DisableClock();

  HAL_RCC_TIM5_Reset();

  /* De-initialize all GPIOF pins associated with TIM5 */
  HAL_GPIO_DeInit(HAL_GPIOF, HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7);
}

hal_tim_handle_t *mx_tim5_gethandle(void)
{
  return &hTIM5;
}
