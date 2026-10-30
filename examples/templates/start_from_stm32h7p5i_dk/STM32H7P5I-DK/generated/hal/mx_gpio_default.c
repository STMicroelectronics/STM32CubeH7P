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
static hal_exti_handle_t hEXTI13;
static hal_exti_handle_t hEXTI8;

/******************************************************************************/
/* Exported functions for GPIO in HAL layer                                   */
/******************************************************************************/
system_status_t mx_gpio_default_init(void)
{
  hal_gpio_config_t  gpio_config;

  HAL_RCC_GPIOC_EnableClock();

  HAL_RCC_GPIOE_EnableClock();

  HAL_RCC_GPIOG_EnableClock();

  HAL_RCC_GPIOH_EnableClock();

  /*
    GPIO pin labels :
    PC13  ---------> PC13
    */
  /* Configure PC13 GPIO pin in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  if (HAL_GPIO_Init(PC13_PORT, PC13_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  hal_exti_config_t exti_config;

  HAL_RCC_SBS_EnableClock();

  /* Initialize the EXTI for line 13 */
  HAL_EXTI_Init(&hEXTI13, HAL_EXTI_LINE_13);

  /* Set the trigger as RISING_FALLING for the GPIOC */
  exti_config.trigger   = HAL_EXTI_TRIGGER_RISING_FALLING;
  exti_config.gpio_port = HAL_EXTI_GPIOC;
  HAL_EXTI_SetConfig(&hEXTI13, &exti_config);

  /* Set line 13 Interrupt priority */
  HAL_CORTEX_NVIC_SetPriority(EXTI13_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(EXTI13_IRQn);

  /*
    GPIO pin labels :
    PE1   ---------> PE1
    */
  /* Configure PE1 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = PE1_INIT_STATE;
  if (HAL_GPIO_Init(PE1_PORT, PE1_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PG4   ---------> CS_DISP
    */
  /* Configure PG4 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = CS_DISP_INIT_STATE;
  if (HAL_GPIO_Init(CS_DISP_PORT, CS_DISP_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PG6   ---------> D_C_DISP
    */
  /* Configure PG6 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = D_C_DISP_INIT_STATE;
  if (HAL_GPIO_Init(D_C_DISP_PORT, D_C_DISP_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PG8   ---------> PG8, MX_EXTI_TRIGGER
    */
  /* Configure PG8 GPIO pin in input mode */
  gpio_config.mode            = HAL_GPIO_MODE_INPUT;
  gpio_config.pull            = HAL_GPIO_PULL_UP;
  if (HAL_GPIO_Init(PG8_PORT, PG8_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  HAL_RCC_SBS_EnableClock();

  /* Initialize the EXTI for line 8 */
  HAL_EXTI_Init(&hEXTI8, HAL_EXTI_LINE_8);

  /* Set the trigger as RISING_FALLING for the GPIOG */
  exti_config.trigger   = HAL_EXTI_TRIGGER_RISING_FALLING;
  exti_config.gpio_port = HAL_EXTI_GPIOG;
  HAL_EXTI_SetConfig(&hEXTI8, &exti_config);

  /* Set line 8 Interrupt priority */
  HAL_CORTEX_NVIC_SetPriority(EXTI8_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(EXTI8_IRQn);

  /*
    GPIO pin labels :
    PH6   ---------> MKB_SCK
    */
  /* Configure PH6 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = MKB_SCK_INIT_STATE;
  if (HAL_GPIO_Init(MKB_SCK_PORT, MKB_SCK_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /*
    GPIO pin labels :
    PH15  ---------> PH15
    */
  /* Configure PH15 GPIO pin in output mode */
  gpio_config.mode            = HAL_GPIO_MODE_OUTPUT;
  gpio_config.speed           = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.pull            = HAL_GPIO_PULL_NO;
  gpio_config.output_type     = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.init_state      = PH15_INIT_STATE;
  if (HAL_GPIO_Init(PH15_PORT, PH15_PIN, &gpio_config) != HAL_OK)
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_deinit(void)
{
  /* De-initialize the EXTI for GPIOC line13 */
  HAL_EXTI_DeInit(&hEXTI13);

  /* set line 13 Interrupt priority */
  HAL_CORTEX_NVIC_DisableIRQ(EXTI13_IRQn);

  /* De-initialize the EXTI for GPIOG line8 */
  HAL_EXTI_DeInit(&hEXTI8);

  /* set line 8 Interrupt priority */
  HAL_CORTEX_NVIC_DisableIRQ(EXTI8_IRQn);

  /* De-initialize pins of GPIOC port */
  HAL_GPIO_DeInit(PC13_PORT, PC13_PIN);

  /* De-initialize pins of GPIOE port */
  HAL_GPIO_DeInit(PE1_PORT, PE1_PIN);

  /* De-initialize pins of GPIOG port */
  HAL_GPIO_DeInit(HAL_GPIOG, CS_DISP_PIN | D_C_DISP_PIN | PG8_PIN);

  /* De-initialize pins of GPIOH port */
  HAL_GPIO_DeInit(HAL_GPIOH, MKB_SCK_PIN | PH15_PIN);

  return SYSTEM_OK;
}

hal_exti_handle_t *mx_gpio_default_exti13_gethandle(void)
{
  return &hEXTI13;
}

hal_exti_handle_t *mx_gpio_default_exti8_gethandle(void)
{
  return &hEXTI8;
}

/******************************************************************************/
/*                EXTI Line 13 interrupt through the EXTI line                */
/******************************************************************************/
void EXTI13_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&hEXTI13);
}

/******************************************************************************/
/*                EXTI Line 8 interrupt through the EXTI line                 */
/******************************************************************************/
void EXTI8_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&hEXTI8);
}
