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

/******************************************************************************/
/* Exported functions for I2C2 in LL layer */
/******************************************************************************/
I2C_TypeDef *mx_i2c2_i2c_init(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C123_CLKSOURCE_PCLK1);

  /*
    Timing automatically calculated with:
     - I2C2 input clock at 130000000 Hz
     - I2C clock speed at 1000000 Hz
  */
  LL_I2C_SetTiming(I2C2, 0xE0253A);
  LL_I2C_ConfigOwnAddress1(I2C2, 93 << 1U, LL_I2C_OWNADDRESS1_7BIT);
  /* LL_I2C_SetMasterAddressingMode(I2C2, LL_I2C_ADDRESSING_MODE_7BIT); */ /* Configuration matches register reset state at startup. */
  LL_I2C_WRITE_REG(I2C2, CR2, (LL_I2C_READ_REG(I2C2, CR2) | I2C_CR2_AUTOEND | I2C_CR2_NACK));

  LL_I2C_Enable(I2C2);
  /* ### I2C2 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI | LL_AHB4_GRP1_PERIPH_GPIOB);

  /**
    [GPIO Pin] ------> [Signal Name]

       PI2     ------>   I2C2_SCL
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOI, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  LL_GPIO_SetPinOutputType(GPIOI, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_OPENDRAIN);

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  LL_GPIO_SetPinPull(GPIOI, LL_GPIO_PIN_2, LL_GPIO_PULL_UP);

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOI, LL_GPIO_PIN_2, LL_GPIO_AF_4);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOI, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB8     ------>   I2C2_SDA
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_OPENDRAIN);

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_8, LL_GPIO_PULL_UP);

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_8, LL_GPIO_AF_4);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);

  /* Configure the DMA TX */
  /* ################################################## I2C2 TX DMA configuration */

  /* Enable GPDMA1 clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH0, LL_GPDMA1_REQUEST_I2C2_TX);

  /* Configure DMA channel transfer direction */
  LL_DMA_SetDataTransferDirection(GPDMA1_CH0, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  /* Configure DMA channel priority level */
  /* LL_DMA_SetChannelPriorityLevel(GPDMA1_CH0, LL_DMA_PRIORITY_LOW_WEIGHT_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure DMA channel transfer register 1 */
  LL_DMA_ConfigTransfer(GPDMA1_CH0,
                        (LL_DMA_SRC_ADDR_INCREMENTED | LL_DMA_SRC_DATA_WIDTH_BYTE | \
                         LL_DMA_DEST_ADDR_FIXED | LL_DMA_DEST_DATA_WIDTH_BYTE));

  /* Configure DMA channel hardware request mode */
  /* LL_DMA_SetHWRequestMode(GPDMA1_CH0, LL_DMA_HARDWARE_REQUEST_BURST); */ /* Configuration matches register reset state at startup. */

  /* Enable the interruption for DMA */
  NVIC_SetPriority(GPDMA1_CH0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(GPDMA1_CH0_IRQn);

  /* Configure the DMA RX */
  /* ################################################## I2C2 RX DMA configuration */

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH1, LL_GPDMA1_REQUEST_I2C2_RX);

  /* Configure DMA channel transfer direction */
  /* LL_DMA_SetDataTransferDirection(GPDMA1_CH1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY); */ /* Configuration matches register reset state at startup. */

  /* Configure DMA channel priority level */
  /* LL_DMA_SetChannelPriorityLevel(GPDMA1_CH1, LL_DMA_PRIORITY_LOW_WEIGHT_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure DMA channel transfer register 1 */
  LL_DMA_ConfigTransfer(GPDMA1_CH1,
                        (LL_DMA_SRC_ADDR_FIXED | LL_DMA_SRC_DATA_WIDTH_BYTE | \
                         LL_DMA_DEST_ADDR_INCREMENTED | LL_DMA_DEST_DATA_WIDTH_BYTE));

  /* Configure DMA channel hardware request mode */
  /* LL_DMA_SetHWRequestMode(GPDMA1_CH1, LL_DMA_HARDWARE_REQUEST_BURST); */ /* Configuration matches register reset state at startup. */

  /* Enable the interruption for DMA */
  NVIC_SetPriority(GPDMA1_CH1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(GPDMA1_CH1_IRQn);

  LL_RCC_SetI2CClockSource(LL_RCC_I2C123_CLKSOURCE_PCLK1);
  /* Enable the Event interruption for I2C */
  NVIC_SetPriority(I2C2_EV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(I2C2_EV_IRQn);

  /* Enable the Error interruption for I2C */
  NVIC_SetPriority(I2C2_ERR_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(I2C2_ERR_IRQn);

  return I2C2;
}

void mx_i2c2_i2c_deinit(void)
{
  /* Disable the Event interruption for I2C */
  NVIC_DisableIRQ(I2C2_EV_IRQn);

  /* Disable the Error interruption for I2C */
  NVIC_DisableIRQ(I2C2_ERR_IRQn);

  LL_I2C_Disable(I2C2);

  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);

  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
  /* ### GPIO deinitialization of I2C2: I2C2_SCL ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOI, LL_GPIO_PIN_2, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOI, LL_GPIO_PIN_2, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOI, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOI, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOI, LL_GPIO_PIN_2, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOI, LL_GPIO_PIN_2, LL_GPIO_PIN_RESET);

  /* ### GPIO deinitialization of I2C2: I2C2_SDA ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_8, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOB, LL_GPIO_PIN_8, LL_GPIO_PIN_RESET);

  /* De-initialize the DMA channel */
  LL_DMA_DisableChannel(GPDMA1_CH0);
  LL_DMA_ClearFlag(GPDMA1_CH0, LL_DMA_FLAG_ALL);

  LL_DMA_WRITE_REG(GPDMA1_CH0, CCR, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH0, CTR1, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH0, CTR2, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH0, CBR1, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH0, CTR3, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH0, CBR2, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH0, CLLR, 0U);

  /* Disable the interruption for DMA */
  NVIC_DisableIRQ(GPDMA1_CH0_IRQn);

  /* De-initialize the DMA channel */
  LL_DMA_DisableChannel(GPDMA1_CH1);
  LL_DMA_ClearFlag(GPDMA1_CH1, LL_DMA_FLAG_ALL);

  LL_DMA_WRITE_REG(GPDMA1_CH1, CCR, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH1, CTR1, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH1, CTR2, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH1, CBR1, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH1, CTR3, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH1, CBR2, 0U);
  LL_DMA_WRITE_REG(GPDMA1_CH1, CLLR, 0U);

  /* Disable the interruption for DMA */
  NVIC_DisableIRQ(GPDMA1_CH1_IRQn);
}

/******************************************************************************/
/*           I2C2 event interrupt is managed directly in user code.           */
/******************************************************************************/
/* void I2C2_EV_IRQHandler(void)
{
}
  */

/******************************************************************************/
/*           I2C2 error interrupt is managed directly in user code.           */
/******************************************************************************/
/* void I2C2_ERR_IRQHandler(void)
{
}
  */

/******************************************************************************/
/*        GPDMA1 channel 0 interrupt is managed directly in user code.        */
/******************************************************************************/
/* void GPDMA1_CH0_IRQHandler(void)
{
}
  */

/******************************************************************************/
/*        GPDMA1 channel 1 interrupt is managed directly in user code.        */
/******************************************************************************/
/* void GPDMA1_CH1_IRQHandler(void)
{
}
  */
