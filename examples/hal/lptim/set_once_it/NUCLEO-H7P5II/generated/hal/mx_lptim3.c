/**
  ******************************************************************************
  * @file           : mx_lptim3.c
  * @brief          : LPTIM3 Peripheral initialization
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
#include "mx_lptim3.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported variables by reference--------------------------------------------*/
static hal_lptim_handle_t hLPTIM3;

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for SW instance in HAL layer */
/******************************************************************************/

hal_lptim_handle_t *mx_lptim3_init(void)
{
  /* Init GPIO */
  /* ### LPTIM3 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOC_EnableClock();

  HAL_RCC_GPIOE_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PC1     ------>   LPTIM3_CH1
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_11;
  HAL_GPIO_Init(HAL_GPIOC, HAL_GPIO_PIN_1, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PE12    ------>   LPTIM3_ETR
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_11;
  HAL_GPIO_Init(HAL_GPIOE, HAL_GPIO_PIN_12, &gpio_config);

  hal_lptim_config_t  config;

  if (HAL_LPTIM_Init(&hLPTIM3, HAL_LPTIM3) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_LPTIM3_EnableClock();

  if (HAL_RCC_LPTIM23_SetKernelClkSource(HAL_RCC_LPTIM23_CLK_SRC_LSI) != HAL_OK)
  {
    return NULL;
  }

  /* Timer configuration to reach the output frequency at 1 kHz */
  config.mode               = HAL_LPTIM_SET_ONCE;
  config.clock_source       = HAL_LPTIM_CLK_INTERNAL;
  config.period             = 0x1F;
  config.prescaler          = HAL_LPTIM_CLK_SRC_DIV1;
  config.repetition_counter = 0;

  if (HAL_LPTIM_SetConfig(&hLPTIM3, &config) != HAL_OK)
  {
    return NULL;
  }

  hal_lptim_oc_config_t oc_config1;
  oc_config1.pulse = 0x10;
  oc_config1.polarity = HAL_LPTIM_OC_HIGH;
  if (HAL_LPTIM_OC_SetConfigChannel(&hLPTIM3, HAL_LPTIM_CHANNEL_1, &oc_config1) != HAL_OK)
  {
    return NULL;
  }

  hal_lptim_ext_trig_config_t ext_trig_conf;
  ext_trig_conf.source = HAL_LPTIM_EXT_TRIG_GPIO;
  ext_trig_conf.polarity = HAL_LPTIM_TRIG_RISING;
  ext_trig_conf.filter = HAL_LPTIM_FDIV1;
  if (HAL_LPTIM_SetConfigExtTrigInput(&hLPTIM3, &ext_trig_conf) != HAL_OK)
  {
    return NULL;
  }
  /* Enable the LPTIM global interruption */
  HAL_CORTEX_NVIC_SetPriority(LPTIM3_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(LPTIM3_IRQn);

  return &hLPTIM3;
}

void mx_lptim3_deinit(void)
{
  (void)HAL_LPTIM_DeInit(&hLPTIM3);

  HAL_RCC_LPTIM3_Reset();

  HAL_RCC_LPTIM3_DisableClock();

  /* De-initialize all GPIOC pins associated with LPTIM3 */
  HAL_GPIO_DeInit(HAL_GPIOC, HAL_GPIO_PIN_1);

  /* De-initialize all GPIOE pins associated with LPTIM3 */
  HAL_GPIO_DeInit(HAL_GPIOE, HAL_GPIO_PIN_12);

  /* Disable Timer global interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(LPTIM3_IRQn);
}

hal_lptim_handle_t *mx_lptim3_gethandle(void)
{
  return &hLPTIM3;
}

/******************************************************************************/
/*                          LPTIM3 global interrupt                           */
/******************************************************************************/
void LPTIM3_IRQHandler(void)
{
  HAL_LPTIM_IRQHandler(&hLPTIM3);
}
