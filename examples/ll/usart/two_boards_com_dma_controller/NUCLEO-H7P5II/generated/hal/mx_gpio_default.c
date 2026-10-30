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

/******************************************************************************/
/* Exported functions for GPIO in LL layer                                   */
/******************************************************************************/
system_status_t mx_gpio_default_init(void)
{
  /* Enable peripherals and GPIO Clocks #################################*/
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);

  /*
    GPIO pin labels :
    PG9   ---------> PG9, MX_STATUS_LED
    */

  /* Initialize the output state */
  /* LL_GPIO_WriteOutputPin(PG9_PORT, PG9_PIN, LL_GPIO_PIN_RESET); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(PG9_PORT, PG9_PIN, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(PG9_PORT, PG9_PIN, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(PG9_PORT, PG9_PIN, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure PG9 GPIO pin in output mode */
  LL_GPIO_SetPinMode(PG9_PORT, PG9_PIN, LL_GPIO_MODE_OUTPUT);

  return SYSTEM_OK;
}

system_status_t mx_gpio_default_deinit(void)
{
  /*
    GPIO pin labels :
    PG9   ---------> PG9, MX_STATUS_LED
    */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(PG9_PORT, PG9_PIN, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(PG9_PORT, PG9_PIN, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(PG9_PORT, PG9_PIN, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(PG9_PORT, PG9_PIN, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(PG9_PORT, PG9_PIN, LL_GPIO_PULL_NO);

  /* Reset the current IO output state */
  LL_GPIO_ResetOutputPin(PG9_PORT, PG9_PIN);

  return SYSTEM_OK;
}
