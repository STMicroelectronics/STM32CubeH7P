/**
  ******************************************************************************
  * @file           : mx_i2c2.c
  * @brief          : I2C2 Peripheral initialization
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
#include "mx_i2c2.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_i2c_handle_t hI2C2;

/******************************************************************************/
/* Exported functions for I2C2 in HAL layer */
/******************************************************************************/
hal_i2c_handle_t *mx_i2c2_i2c_init(void)
{
  hal_i2c_config_t i2c_config;

  if (HAL_I2C_Init(&hI2C2, HAL_I2C2) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_I2C2_EnableClock();

  /*
    Timing automatically calculated with:
     - I2C2 input clock at 130000000 Hz
     - I2C clock speed at 1000000 Hz
  */
  i2c_config.timing           = 0xE0253A;
  i2c_config.addressing_mode  = HAL_I2C_ADDRESSING_7BIT;
  i2c_config.own_address1     = 63 << 1U;
  if (HAL_I2C_SetConfig(&hI2C2, &i2c_config) != HAL_OK)
  {
    return NULL;
  }

  HAL_I2C_EnableAnalogFilter(&hI2C2);

  /* ### I2C2 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOI_EnableClock();

  HAL_RCC_GPIOB_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PI2     ------>   I2C2_SCL
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_4;
  HAL_GPIO_Init(HAL_GPIOI, HAL_GPIO_PIN_2, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB8     ------>   I2C2_SDA
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_4;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_8, &gpio_config);

  if (HAL_RCC_I2C123_SetKernelClkSource(HAL_RCC_I2C123_CLK_SRC_PCLK1) != HAL_OK)
  {
    return NULL;
  }

  return &hI2C2;
}

void mx_i2c2_i2c_deinit(void)
{
  (void)HAL_I2C_DeInit(&hI2C2);

  HAL_RCC_I2C2_Reset();

  HAL_RCC_I2C2_DisableClock();

  /* De-initialize all GPIOI pins associated with I2C2 */
  HAL_GPIO_DeInit(HAL_GPIOI, HAL_GPIO_PIN_2);

  /* De-initialize all GPIOB pins associated with I2C2 */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_8);
}

hal_i2c_handle_t *mx_i2c2_i2c_gethandle(void)
{
  return &hI2C2;
}
