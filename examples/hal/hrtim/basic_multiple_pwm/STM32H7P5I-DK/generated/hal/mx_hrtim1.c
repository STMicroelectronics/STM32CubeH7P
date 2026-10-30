/**
  ******************************************************************************
  * @file           : mx_hrtim1.c
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
#include "mx_hrtim1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported variables by reference--------------------------------------------*/
static hal_hrtim_handle_t hHRTIM1;

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for SW instance in HAL layer */
/******************************************************************************/

hal_hrtim_handle_t *mx_hrtim1_init(void)
{
  /* HRTIM instance initialization */
  if (HAL_HRTIM_Init(&hHRTIM1, HAL_HRTIM1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_HRTIM1_EnableClock();

  /* No GPIO configuration required for HRTIM1 */
  /* HRTIM output channels configuration */
  hal_hrtim_output_config_t output_config;

  /* HAL_HRTIM_CHD1 configuration */
  output_config.set = HAL_HRTIM_OUT_SET_PERIOD;
  output_config.reset = HAL_HRTIM_OUT_RESET_CMP1;
  output_config.polarity = HAL_HRTIM_OUTPUT_ACTIVE_HIGH;
  output_config.idle_level = HAL_HRTIM_OUTPUT_IDLE_INACTIVE;
  output_config.fault_level = HAL_HRTIM_OUTPUT_FAULT_NONE;

  if (HAL_HRTIM_OUT_SetConfig(&hHRTIM1, HAL_HRTIM_CHD1, &output_config) != HAL_OK)
  {
    return NULL;
  }

  /* HAL_HRTIM_CHD2 configuration */
  output_config.set = HAL_HRTIM_OUT_SET_CMP2;
  output_config.reset = HAL_HRTIM_OUT_RESET_PERIOD;
  output_config.polarity = HAL_HRTIM_OUTPUT_ACTIVE_HIGH;
  output_config.idle_level = HAL_HRTIM_OUTPUT_IDLE_INACTIVE;
  output_config.fault_level = HAL_HRTIM_OUTPUT_FAULT_NONE;

  if (HAL_HRTIM_OUT_SetConfig(&hHRTIM1, HAL_HRTIM_CHD2, &output_config) != HAL_OK)
  {
    return NULL;
  }

  /* HAL_HRTIM_CHF1 configuration */
  output_config.set = HAL_HRTIM_OUT_SET_PERIOD;
  output_config.reset = HAL_HRTIM_OUT_RESET_CMP1;
  output_config.polarity = HAL_HRTIM_OUTPUT_ACTIVE_HIGH;
  output_config.idle_level = HAL_HRTIM_OUTPUT_IDLE_INACTIVE;
  output_config.fault_level = HAL_HRTIM_OUTPUT_FAULT_NONE;

  if (HAL_HRTIM_OUT_SetConfig(&hHRTIM1, HAL_HRTIM_CHF1, &output_config) != HAL_OK)
  {
    return NULL;
  }

  /* HAL_HRTIM_CHF2 configuration */
  output_config.set = HAL_HRTIM_OUT_SET_CMP2;
  output_config.reset = HAL_HRTIM_OUT_RESET_CMP3;
  output_config.polarity = HAL_HRTIM_OUTPUT_ACTIVE_HIGH;
  output_config.idle_level = HAL_HRTIM_OUTPUT_IDLE_INACTIVE;
  output_config.fault_level = HAL_HRTIM_OUTPUT_FAULT_NONE;

  if (HAL_HRTIM_OUT_SetConfig(&hHRTIM1, HAL_HRTIM_CHF2, &output_config) != HAL_OK)
  {
    return NULL;
  }

  /* Timers configuration */
  hal_hrtim_timer_config_t timer_config;

  /* Timer D configuration */
  /* Time base configuration */
  timer_config.prescaler = HAL_HRTIM_TIM_PRESCALER_DIV1;
  timer_config.period = 5200;
  timer_config.repetition = 0;
  timer_config.operating_mode = HAL_HRTIM_TIM_MODE_CONTINUOUS;
  timer_config.counting_mode = HAL_HRTIM_TIM_COUNTING_UP;

  if (HAL_HRTIM_TIM_SetConfig(&hHRTIM1, HAL_HRTIM_TIMD, &timer_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_HRTIM_TIM_SetCompareValue(&hHRTIM1, HAL_HRTIM_TIMD, HAL_HRTIM_COMPARE_UNIT_1, 1300) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_HRTIM_TIM_SetCompareValue(&hHRTIM1, HAL_HRTIM_TIMD, HAL_HRTIM_COMPARE_UNIT_2, 3900) != HAL_OK)
  {
    return NULL;
  }

  /* Timer F configuration */
  /* Time base configuration */
  timer_config.prescaler = HAL_HRTIM_TIM_PRESCALER_DIV1;
  timer_config.period = 15760;
  timer_config.repetition = 0;
  timer_config.operating_mode = HAL_HRTIM_TIM_MODE_CONTINUOUS;
  timer_config.counting_mode = HAL_HRTIM_TIM_COUNTING_UP;

  if (HAL_HRTIM_TIM_SetConfig(&hHRTIM1, HAL_HRTIM_TIMF, &timer_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_HRTIM_TIM_SetCompareValue(&hHRTIM1, HAL_HRTIM_TIMF, HAL_HRTIM_COMPARE_UNIT_1, 3940) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_HRTIM_TIM_SetCompareValue(&hHRTIM1, HAL_HRTIM_TIMF, HAL_HRTIM_COMPARE_UNIT_2, 7880) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_HRTIM_TIM_SetCompareValue(&hHRTIM1, HAL_HRTIM_TIMF, HAL_HRTIM_COMPARE_UNIT_3, 11820) != HAL_OK)
  {
    return NULL;
  }

  /* ### HRTIM1 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOC_EnableClock();

  HAL_RCC_GPIOI_EnableClock();

  HAL_RCC_GPIOB_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PC6     ------>   HRTIM1_CHF1
       PC7     ------>   HRTIM1_CHF2
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_11;
  HAL_GPIO_Init(HAL_GPIOC, HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PI2     ------>   HRTIM1_CHD1
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_12;
  HAL_GPIO_Init(HAL_GPIOI, HAL_GPIO_PIN_2, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB8     ------>   HRTIM1_CHD2
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_12;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_8, &gpio_config);

  return &hHRTIM1;
}

void mx_hrtim1_deinit(void)
{
  (void)HAL_HRTIM_DeInit(&hHRTIM1);

  HAL_RCC_HRTIM1_Reset();

  HAL_RCC_HRTIM1_DisableClock();

  /* De-initialize all GPIOC pins associated with HRTIM1 */
  HAL_GPIO_DeInit(HAL_GPIOC, HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7);

  /* De-initialize all GPIOI pins associated with HRTIM1 */
  HAL_GPIO_DeInit(HAL_GPIOI, HAL_GPIO_PIN_2);

  /* De-initialize all GPIOB pins associated with HRTIM1 */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_8);
}

hal_hrtim_handle_t *mx_hrtim1_gethandle(void)
{
  return &hHRTIM1;
}
