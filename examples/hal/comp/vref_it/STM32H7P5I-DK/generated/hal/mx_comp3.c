/**
  ******************************************************************************
  * @file           : mx_comp3.c
  * @brief          : COMP3 Peripheral initialization
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
#include "mx_comp3.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_comp_handle_t hCOMP3;
/******************************************************************************/
/* Exported functions for COMP3 in HAL layer */
/******************************************************************************/
hal_comp_handle_t *mx_comp3_init(void)
{
  if (HAL_COMP_Init(&hCOMP3, HAL_COMP3) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_COMP34_EnableClock();

  hal_comp_config_t comp_config;
  comp_config.input_plus = HAL_COMP_INPUT_PLUS_IO3;
  comp_config.input_minus = HAL_COMP_INPUT_MINUS_VREFINT;
  comp_config.input_hysteresis = HAL_COMP_INPUT_HYSTERESIS_NONE;
  comp_config.output_polarity = HAL_COMP_OUTPUT_POLARITY_NONINVERTED;
  comp_config.output_trigger = HAL_COMP_OUTPUT_TRIG_RISING_FALLING;
  if (HAL_COMP_SetConfig(&hCOMP3, &comp_config) != HAL_OK)
  {
    return NULL;
  }

  /* ### COMP3 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOF_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PF7     ------>   COMP3_INP3
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ANALOG;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  HAL_GPIO_Init(HAL_GPIOF, HAL_GPIO_PIN_7, &gpio_config);

  /* Enable comparator interruption through EXTI */
  HAL_CORTEX_NVIC_SetPriority(COMP3_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(COMP3_IRQn);

  return &hCOMP3;
}

void mx_comp3_deinit(void)
{
  (void)HAL_COMP_DeInit(&hCOMP3);

  HAL_RCC_COMP34_DisableClock();

  HAL_RCC_COMP34_Reset();

  /* De-initialize all GPIOF pins associated with COMP3 */
  HAL_GPIO_DeInit(HAL_GPIOF, HAL_GPIO_PIN_7);

  HAL_CORTEX_NVIC_DisableIRQ(COMP3_IRQn);
}

hal_comp_handle_t *mx_comp3_gethandle(void)
{
  return &hCOMP3;
}

/******************************************************************************/
/*                     COMP3 interrupt through EXTI line                      */
/******************************************************************************/
void COMP3_IRQHandler(void)
{
  HAL_COMP_IRQHandler(&hCOMP3);
}
