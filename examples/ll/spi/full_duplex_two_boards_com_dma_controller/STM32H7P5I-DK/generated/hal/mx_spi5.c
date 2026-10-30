/**
  ******************************************************************************
  * @file           : mx_spi5.c
  * @brief          : SPI5 Peripheral initialization
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
#include "mx_spi5.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/

/******************************************************************************/
/* Exported functions for SPI in LL layer */
/******************************************************************************/
SPI_TypeDef *mx_spi5_init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI45_CLKSOURCE_PCLK2);
  uint32_t cfg1_config = LL_SPI_DATA_WIDTH_8_BIT | LL_SPI_BAUD_RATE_PRESCALER_16;
  uint32_t cfg2_config = LL_SPI_MODE_MASTER | LL_SPI_FULL_DUPLEX | LL_SPI_CLOCK_POLARITY_LOW
                       | LL_SPI_CLOCK_PHASE_1_EDGE | LL_SPI_MSB_FIRST | LL_SPI_NSS_SOFT;

  LL_SPI_SetConfig(SPI5, cfg1_config, cfg2_config);

  /* LL_SPI_SetStandard(SPI5, LL_SPI_PROTOCOL_MOTOROLA); */ /* Configuration matches register reset state at startup. */

  /* LL_SPI_SetInterDataIdleness(SPI5, LL_SPI_MIDI_DELAY_0_CYCLE); */ /* Configuration matches register reset state at startup. */

  /* LL_SPI_SetFIFOThreshold(SPI5, LL_SPI_FIFO_THRESHOLD_1_DATA); */ /* Configuration matches register reset state at startup. */

  /* ### SPI5 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);

  /**
    [GPIO Pin] ------> [Signal Name]

       PH6     ------>   SPI5_SCK
       PH7     ------>   SPI5_MISO
       PH8     ------>   SPI5_MOSI
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  LL_GPIO_SetPinSpeed(GPIOH, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinSpeed(GPIOH, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinSpeed(GPIOH, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOH, LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOH, LL_GPIO_PIN_6, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */
  /* LL_GPIO_SetPinPull(GPIOH, LL_GPIO_PIN_7, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */
  /* LL_GPIO_SetPinPull(GPIOH, LL_GPIO_PIN_8, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOH, LL_GPIO_PIN_6, LL_GPIO_AF_5);
  LL_GPIO_SetAFPin_0_7(GPIOH, LL_GPIO_PIN_7, LL_GPIO_AF_5);
  LL_GPIO_SetAFPin_8_15(GPIOH, LL_GPIO_PIN_8, LL_GPIO_AF_5);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOH, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinMode(GPIOH, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinMode(GPIOH, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);

  /* Enable the interrupt for SPI */
  NVIC_SetPriority(SPI5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(SPI5_IRQn);
  /* ################################################## SPI5 TX DMA configuration */

  /* Enable GPDMA1 clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH0, LL_GPDMA1_REQUEST_SPI5_TX);

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
  /* ################################################## SPI5 RX DMA configuration */

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH1, LL_GPDMA1_REQUEST_SPI5_RX);

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
return SPI5;
}

void mx_spi5_deinit(void)
{
  /* Disable the interrupt for SPI */
  NVIC_DisableIRQ(SPI5_IRQn);

  LL_SPI_Disable(SPI5);

  /* ### GPIO deinitialization of SPI5: SPI5_SCK,SPI5_MISO,SPI5_MOSI ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOH, LL_GPIO_PIN_6, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinMode(GPIOH, LL_GPIO_PIN_7, LL_GPIO_MODE_ANALOG);
  LL_GPIO_SetPinMode(GPIOH, LL_GPIO_PIN_8, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOH, LL_GPIO_PIN_6, LL_GPIO_AF_0);
  LL_GPIO_SetAFPin_0_7(GPIOH, LL_GPIO_PIN_7, LL_GPIO_AF_0);
  LL_GPIO_SetAFPin_8_15(GPIOH, LL_GPIO_PIN_8, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOH, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOH, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_LOW);
  LL_GPIO_SetPinSpeed(GPIOH, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOH, LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOH, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinPull(GPIOH, LL_GPIO_PIN_7, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinPull(GPIOH, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOH, LL_GPIO_PIN_6 | LL_GPIO_PIN_7 | LL_GPIO_PIN_8, LL_GPIO_PIN_RESET);

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
/*          SPI5 global interrupt is managed directly in user code.           */
/******************************************************************************/
/* void SPI5_IRQHandler(void)
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
