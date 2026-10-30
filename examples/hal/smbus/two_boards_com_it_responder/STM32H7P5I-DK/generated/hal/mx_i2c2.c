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
static hal_smbus_handle_t hI2C2;

/******************************************************************************/
/* Exported functions for I2C2 in HAL layer */
/******************************************************************************/
hal_smbus_handle_t *mx_i2c2_smbus_init(void)
{
  hal_smbus_config_t smbus_config;

  if (HAL_SMBUS_Init(&hI2C2, HAL_SMBUS2) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_I2C2_EnableClock();

  /*
    Timing automatically calculated with:
     - I2C2 input clock at 130000000 Hz
     - I2C clock speed at 1000000 Hz
  */
  smbus_config.timing           = 0xE0253A;
  smbus_config.own_address1     = 63 << 1U;
  smbus_config.device_mode      = HAL_SMBUS_PERIPHERAL_MODE_SLAVE;
  if (HAL_SMBUS_SetConfig(&hI2C2, &smbus_config) != HAL_OK)
  {
    return NULL;
  }

  HAL_SMBUS_EnableAnalogFilter(&hI2C2);
  HAL_SMBUS_EnablePacketErrorCheck(&hI2C2);

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
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_4;
  HAL_GPIO_Init(HAL_GPIOI, HAL_GPIO_PIN_2, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB8     ------>   I2C2_SDA
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_OPENDRAIN;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_4;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_8, &gpio_config);

  if (HAL_RCC_I2C123_SetKernelClkSource(HAL_RCC_I2C123_CLK_SRC_PCLK1) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the Event interruption for I2C */
  HAL_CORTEX_NVIC_SetPriority(I2C2_EV_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(I2C2_EV_IRQn);

  /* Enable the Error interruption for I2C */
  HAL_CORTEX_NVIC_SetPriority(I2C2_ERR_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(I2C2_ERR_IRQn);

  return &hI2C2;
}

void mx_i2c2_smbus_deinit(void)
{
  /* Disable the Event interruption for I2C */
  HAL_CORTEX_NVIC_DisableIRQ(I2C2_EV_IRQn);

  /* Disable the Error interruption for I2C */
  HAL_CORTEX_NVIC_DisableIRQ(I2C2_ERR_IRQn);

  (void)HAL_SMBUS_DeInit(&hI2C2);

  HAL_RCC_I2C2_Reset();

  HAL_RCC_I2C2_DisableClock();

  /* De-initialize all GPIOI pins associated with I2C2 */
  HAL_GPIO_DeInit(HAL_GPIOI, HAL_GPIO_PIN_2);

  /* De-initialize all GPIOB pins associated with I2C2 */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_8);
}

hal_smbus_handle_t *mx_i2c2_smbus_gethandle(void)
{
  return &hI2C2;
}

/******************************************************************************/
/*                            I2C2 event interrupt                            */
/******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
  HAL_SMBUS_EV_IRQHandler(&hI2C2);
}

/******************************************************************************/
/*                            I2C2 error interrupt                            */
/******************************************************************************/
void I2C2_ERR_IRQHandler(void)
{
  HAL_SMBUS_ERR_IRQHandler(&hI2C2);
}
