/**
  ******************************************************************************
  * @file           : mx_i3c1.c
  * @brief          : I3C1 Peripheral initialization
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
#include "mx_i3c1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/

/******************************************************************************/
/* Exported functions for I3C in LL layer */
/******************************************************************************/
I3C_TypeDef *mx_i3c1_init(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I3C1);
  /* LL_RCC_SetI3CClockSource(LL_RCC_I3C1_CLKSOURCE_PCLK1); */ /* Configuration matches register reset state at startup. */

  /* Set the target mode */
  /* LL_I3C_SetMode(I3C1, LL_I3C_MODE_TARGET); */ /* Configuration matches register reset state at startup. */

  /**
    * I3C1 timing_reg1 calculated by CubeMX2 with:
    * Bus available duration = 1000 ns
    */
  LL_I3C_SetBusCharacteristic(I3C1, 0x80U);

  /* Set the identifier value in DCR register */
  LL_I3C_SetDeviceCharacteristics(I3C1, 198U);

  /* Set the MIPI identifier value in EPIDR register */
  LL_I3C_SetMIPIInstanceID(I3C1, 1U);

  /* Set the control capability, IBI payload support and max speed limitation in BCR register */
  /* LL_I3C_ConfigPayloadEntDAA(I3C1, LL_I3C_NO_DATA_SPEED_LIMITATION, LL_I3C_IBI_NO_ADDITIONAL_DATA, LL_I3C_DEVICE_ROLE_AS_TARGET); */ /* Configuration matches register reset state at startup. */

  /* Set the maximum read length (target mode) */
  /* LL_I3C_SetMaxReadLength(I3C1, 0U); */ /* Configuration matches register reset state at startup. */

  /* Set the maximum write length (target mode) */
  /* LL_I3C_SetMaxWriteLength(I3C1, 0U); */ /* Configuration matches register reset state at startup. */

  /* Set the response configuration for GET MaX Data Speed (GETMXDS) CCC */
  /* LL_I3C_SetConfigGETMXDS(I3C1, LL_I3C_HANDOFF_ACTIVITY_STATE_0, LL_I3C_GETMXDS_FORMAT_1, LL_I3C_TURNAROUND_TIME_TSCO_LESS_12NS, 0U); */ /* Configuration matches register reset state at startup. */

  /* Set the FIFO configuration */
  LL_I3C_ConfigTgtFifo(I3C1, LL_I3C_TXFIFO_THRESHOLD_1_8, LL_I3C_RXFIFO_THRESHOLD_1_8);

  /* Enable the I3C peripheral */
  LL_I3C_Enable(I3C1);

  /* ### I3C1 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);

  /**
    [GPIO Pin] ------> [Signal Name]

       PC8     ------>   I3C1_SCL
       PC9     ------>   I3C1_SDA
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_8 | LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_8, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */
  /* LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_9, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_8, LL_GPIO_AF_3);
  LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_9, LL_GPIO_AF_3);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);

  return I3C1;
}

void mx_i3c1_deinit(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I3C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I3C1);

  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I3C1);
  /* ### GPIO deinitialization of I3C1: I3C1_SCL,I3C1_SDA ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_8, LL_GPIO_AF_0);
  LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_9, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_8 | LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOC, LL_GPIO_PIN_8 | LL_GPIO_PIN_9, LL_GPIO_PIN_RESET);
}
