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

  /* Timer configuration to reach the output frequency at 10 kHz */
  hal_tim_config_t config;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  config.prescaler              = 519;
  config.counter_mode           = HAL_TIM_COUNTER_UP;
  config.period                 = 0x63;
  config.repetition_counter     = 0;
  if (HAL_TIM_SetConfig(&hTIM20, &config) != HAL_OK)
  {
    return NULL;
  }

  /* Sampling Clock */
  if (HAL_TIM_SetDTSPrescaler(&hTIM20, HAL_TIM_DTS_DIV1) != HAL_OK)
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
  oc_config.break_mode     = HAL_TIM_OC_BREAKMODE_DELAY1;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM20, HAL_TIM_CHANNEL_2, &oc_config) != HAL_OK)
  {
    return NULL;
  }
  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x5A;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_2,
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_OC_EnableComparePreload(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_2) != HAL_OK)
  {
    return NULL;
  }

  oc_config.polarity       = HAL_TIM_OC_HIGH;
  oc_config.idle_state     = HAL_TIM_OC_IDLE_STATE_RESET;
  oc_config.override_state = HAL_TIM_OC_OVERRIDE_RESET;
  oc_config.break_mode     = HAL_TIM_OC_BREAKMODE_IMMEDIATE;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM20, HAL_TIM_CHANNEL_3, &oc_config) != HAL_OK)
  {
    return NULL;
  }
  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x5A;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_3,
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_OC_EnableComparePreload(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_3) != HAL_OK)
  {
    return NULL;
  }

  oc_config.polarity       = HAL_TIM_OC_HIGH;
  oc_config.idle_state     = HAL_TIM_OC_IDLE_STATE_RESET;
  oc_config.override_state = HAL_TIM_OC_OVERRIDE_RESET;
  oc_config.break_mode     = HAL_TIM_OC_BREAKMODE_DELAY2;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM20, HAL_TIM_CHANNEL_4, &oc_config) != HAL_OK)
  {
    return NULL;
  }
  oc_compare_unit_config.mode  = HAL_TIM_OC_PWM1;
  oc_compare_unit_config.pulse = 0x5A;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_4,
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_OC_EnableComparePreload(&hTIM20, HAL_TIM_OC_COMPARE_UNIT_4) != HAL_OK)
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

  /* Break Configuration */
  if (HAL_TIM_BREAK_EnableAutomaticOutput(&hTIM20) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_off_states_config_t off_states;

  off_states.off_state_run  = HAL_TIM_OFF_STATE_RUN_ENABLE;
  off_states.off_state_idle = HAL_TIM_OFF_STATE_IDLE_ENABLE;
  if (HAL_TIM_BREAK_SetOutputOffStates(&hTIM20, &off_states) != HAL_OK)
  {
    return NULL;
  }

  /* Break 1 Configuration */
  hal_tim_break_input_config_t break_input;

  break_input.polarity  = HAL_TIM_BREAK_INPUT_LOW;
  break_input.filter    = HAL_TIM_FDIV1;
  break_input.mode      = HAL_TIM_BREAK_INPUT_MODE_INPUT;
  if (HAL_TIM_BREAK_SetConfigInput(&hTIM20, HAL_TIM_BREAK_INPUT_1, &break_input) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_BREAK_SetBreakDelay(&hTIM20, HAL_TIM_BREAK_DELAY1, 60) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_BREAK_SetBreakDelay(&hTIM20, HAL_TIM_BREAK_DELAY2, 120) != HAL_OK)
  {
    return NULL;
  }

  /* GPIO Break1 Input Source Configuration */
  if (HAL_TIM_BREAK_SetInputSourcePolarity(&hTIM20, HAL_TIM_BREAK_INPUT_1, HAL_TIM_BRK_TIM20_GPIO,
                                           HAL_TIM_BREAK_INPUT_SRC_NONINVERTED) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_BREAK_EnableInputSource(&hTIM20, HAL_TIM_BREAK_INPUT_1, HAL_TIM_BRK_TIM20_GPIO) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_BREAK_EnableInput(&hTIM20, HAL_TIM_BREAK_INPUT_1) != HAL_OK)
  {
    return NULL;
  }

  /* ### TIM20 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOD_EnableClock();

  HAL_RCC_GPIOC_EnableClock();

  HAL_RCC_GPIOI_EnableClock();

  HAL_RCC_GPIOB_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PD10    ------>   TIM20_CH3
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_9;
  HAL_GPIO_Init(HAL_GPIOD, HAL_GPIO_PIN_10, &gpio_config);

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

       PI2     ------>   TIM20_CH4
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_9;
  HAL_GPIO_Init(HAL_GPIOI, HAL_GPIO_PIN_2, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB8     ------>   TIM20_BKIN
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_9;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_8, &gpio_config);

  return &hTIM20;
}

void mx_tim20_deinit(void)
{
  (void)HAL_TIM_DeInit(&hTIM20);

  HAL_RCC_TIM20_DisableClock();

  HAL_RCC_TIM20_Reset();

  /* De-initialize all GPIOD pins associated with TIM20 */
  HAL_GPIO_DeInit(HAL_GPIOD, HAL_GPIO_PIN_10);

  /* De-initialize all GPIOC pins associated with TIM20 */
  HAL_GPIO_DeInit(HAL_GPIOC, HAL_GPIO_PIN_2);

  /* De-initialize all GPIOI pins associated with TIM20 */
  HAL_GPIO_DeInit(HAL_GPIOI, HAL_GPIO_PIN_2);

  /* De-initialize all GPIOB pins associated with TIM20 */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_8);
}

hal_tim_handle_t *mx_tim20_gethandle(void)
{
  return &hTIM20;
}
