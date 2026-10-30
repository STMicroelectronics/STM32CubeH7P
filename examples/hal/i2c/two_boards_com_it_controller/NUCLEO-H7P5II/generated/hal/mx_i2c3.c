/**
  ******************************************************************************
  * @file           : mx_i2c3.c
  * @brief          : I2C3 Peripheral initialization
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
#include "mx_i2c3.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_i2c_handle_t hI2C3;

/******************************************************************************/
/* Exported functions for I2C3 in HAL layer */
/******************************************************************************/
hal_i2c_handle_t *mx_i2c3_i2c_init(void)
{
  hal_i2c_config_t i2c_config;

  if (HAL_I2C_Init(&hI2C3, HAL_I2C3) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_I2C3_EnableClock();

  /*
    Timing automatically calculated with:
     - I2C3 input clock at 130000000 Hz
     - I2C clock speed at 1000000 Hz
  */
  i2c_config.timing           = 0xE0253A;
  i2c_config.addressing_mode  = HAL_I2C_ADDRESSING_7BIT;
  i2c_config.own_address1     = 93 << 1U;
  if (HAL_I2C_SetConfig(&hI2C3, &i2c_config) != HAL_OK)
  {
    return NULL;
  }

  HAL_I2C_EnableAnalogFilter(&hI2C3);

  /* ### I2C3 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOC_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PC8     ------>   I2C3_SCL
       PC9     ------>   I2C3_SDA
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_8;
  HAL_GPIO_Init(HAL_GPIOC, HAL_GPIO_PIN_8 | HAL_GPIO_PIN_9, &gpio_config);

  if (HAL_RCC_I2C123_SetKernelClkSource(HAL_RCC_I2C123_CLK_SRC_PCLK1) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the Event interruption for I2C */
  HAL_CORTEX_NVIC_SetPriority(I2C3_EV_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(I2C3_EV_IRQn);

  /* Enable the Error interruption for I2C */
  HAL_CORTEX_NVIC_SetPriority(I2C3_ERR_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(I2C3_ERR_IRQn);

  return &hI2C3;
}

void mx_i2c3_i2c_deinit(void)
{
  /* Disable the Event interruption for I2C */
  HAL_CORTEX_NVIC_DisableIRQ(I2C3_EV_IRQn);

  /* Disable the Error interruption for I2C */
  HAL_CORTEX_NVIC_DisableIRQ(I2C3_ERR_IRQn);

  (void)HAL_I2C_DeInit(&hI2C3);

  HAL_RCC_I2C3_Reset();

  HAL_RCC_I2C3_DisableClock();

  /* De-initialize all GPIOC pins associated with I2C3 */
  HAL_GPIO_DeInit(HAL_GPIOC, HAL_GPIO_PIN_8 | HAL_GPIO_PIN_9);
}

hal_i2c_handle_t *mx_i2c3_i2c_gethandle(void)
{
  return &hI2C3;
}

/******************************************************************************/
/*                            I2C3 event interrupt                            */
/******************************************************************************/
void I2C3_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&hI2C3);
}

/******************************************************************************/
/*                            I2C3 error interrupt                            */
/******************************************************************************/
void I2C3_ERR_IRQHandler(void)
{
  HAL_I2C_ERR_IRQHandler(&hI2C3);
}
