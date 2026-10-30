/**
  ******************************************************************************
  * @file           : mx_gpio_default.c
  * @brief          : gpio_default Peripheral initialization
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
#include "mx_gpio_default.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/
static hal_exti_handle_t hEXTI0;

/******************************************************************************/
/* Exported functions for GPIO in HAL layer                                   */
/******************************************************************************/
system_status_t mx_gpio_default_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOF_EnableClock();

  HAL_RCC_GPIOG_EnableClock();

  /*
    GPIO pin labels :
    PF0   ---------> UCPD_FLT, MX_EXTI_TRIGGER
    */
  /* Configure PF0 GPIO pin in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_UP;
  if (HAL_GPIO_Init(UCPD_FLT_PORT, UCPD_FLT_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  hal_exti_config_t exti_config;

  HAL_RCC_SBS_EnableClock();

  /* Initialize the EXTI for line 0 */
  HAL_EXTI_Init(&hEXTI0, HAL_EXTI_LINE_0);

  /* Set the trigger as RISING_FALLING for the GPIOF */
  exti_config.trigger   = HAL_EXTI_TRIGGER_RISING_FALLING;
  exti_config.gpio_port = HAL_EXTI_GPIOF;
  HAL_EXTI_SetConfig(&hEXTI0, &exti_config);

  /* Set line 0 Interrupt priority */
  HAL_CORTEX_NVIC_SetPriority(EXTI0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_7, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(EXTI0_IRQn);

  /*
    GPIO pin labels :
    PF5   ---------> UCPD_DBN
    */
  /* Configure PF5 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = UCPD_DBN_INIT_STATE;
  if (HAL_GPIO_Init(UCPD_DBN_PORT, UCPD_DBN_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PG9   ---------> PG9
    */
  /* Configure PG9 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = PG9_INIT_STATE;
  if (HAL_GPIO_Init(PG9_PORT, PG9_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_deinit(void)
{
  /* De-initialize the EXTI for GPIOF line0 */
  HAL_EXTI_DeInit(&hEXTI0);

  /* set line 0 Interrupt priority */
  HAL_CORTEX_NVIC_DisableIRQ(EXTI0_IRQn);

  /* De-initialize pins of GPIOF port */
  HAL_GPIO_DeInit(HAL_GPIOF, UCPD_FLT_PIN | UCPD_DBN_PIN);

  /* De-initialize pins of GPIOG port */
  HAL_GPIO_DeInit(PG9_PORT, PG9_PIN);

  return SYSTEM_OK;
}

hal_exti_handle_t *mx_gpio_default_exti0_gethandle(void)
{
  return &hEXTI0;
}

/******************************************************************************/
/*                EXTI Line 0 interrupt through the EXTI line                 */
/******************************************************************************/
void EXTI0_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&hEXTI0);
}
