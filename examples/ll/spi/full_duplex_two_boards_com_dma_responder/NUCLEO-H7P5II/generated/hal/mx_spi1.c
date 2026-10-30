/**
  ******************************************************************************
  * @file           : mx_spi1.c
  * @brief          : SPI1 Peripheral initialization
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
#include "mx_spi1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/

/******************************************************************************/
/* Exported functions for SPI in LL layer */
/******************************************************************************/
SPI_TypeDef *mx_spi1_init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
  LL_RCC_SetSPIClockSource(LL_RCC_SPI1_CLKSOURCE_PLL1Q);
  uint32_t cfg1_config = LL_SPI_DATA_WIDTH_8_BIT | LL_SPI_BAUD_RATE_PRESCALER_2;
  uint32_t cfg2_config = LL_SPI_MODE_SLAVE | LL_SPI_FULL_DUPLEX | LL_SPI_CLOCK_POLARITY_LOW
                       | LL_SPI_CLOCK_PHASE_1_EDGE | LL_SPI_MSB_FIRST | LL_SPI_NSS_SOFT;

  LL_SPI_SetConfig(SPI1, cfg1_config, cfg2_config);

  /* LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA); */ /* Configuration matches register reset state at startup. */

  /* LL_SPI_SetInterDataIdleness(SPI1, LL_SPI_MIDI_DELAY_0_CYCLE); */ /* Configuration matches register reset state at startup. */

  /* LL_SPI_SetFIFOThreshold(SPI1, LL_SPI_FIFO_THRESHOLD_1_DATA); */ /* Configuration matches register reset state at startup. */

  /* ### SPI1 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG | LL_AHB4_GRP1_PERIPH_GPIOC | LL_AHB4_GRP1_PERIPH_GPIOB);

  /**
    [GPIO Pin] ------> [Signal Name]

       PG9     ------>   SPI1_SCK
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  LL_GPIO_SetPinSpeed(GPIOG, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOG, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOG, LL_GPIO_PIN_9, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOG, LL_GPIO_PIN_9, LL_GPIO_AF_2);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOG, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);

  /**
    [GPIO Pin] ------> [Signal Name]

       PC11    ------>   SPI1_MISO
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_11, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_11, LL_GPIO_AF_5);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB2     ------>   SPI1_MOSI
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_2, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_2, LL_GPIO_AF_5);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);

  /* Enable the interrupt for SPI */
  NVIC_SetPriority(SPI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(SPI1_IRQn);
  /* ################################################## SPI1 TX DMA configuration */

  /* Enable GPDMA1 clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH0, LL_GPDMA1_REQUEST_SPI1_TX);

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
  /* ################################################## SPI1 RX DMA configuration */

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH1, LL_GPDMA1_REQUEST_SPI1_RX);

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
return SPI1;
}

void mx_spi1_deinit(void)
{
  /* Disable the interrupt for SPI */
  NVIC_DisableIRQ(SPI1_IRQn);

  LL_SPI_Disable(SPI1);

  /* ### GPIO deinitialization of SPI1: SPI1_SCK ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOG, LL_GPIO_PIN_9, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOG, LL_GPIO_PIN_9, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOG, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOG, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOG, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOG, LL_GPIO_PIN_9, LL_GPIO_PIN_RESET);

  /* ### GPIO deinitialization of SPI1: SPI1_MISO ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_11, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_11, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_11, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOC, LL_GPIO_PIN_11, LL_GPIO_PIN_RESET);

  /* ### GPIO deinitialization of SPI1: SPI1_MOSI ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_2, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_2, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOB, LL_GPIO_PIN_2, LL_GPIO_PIN_RESET);

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
/*          SPI1 global interrupt is managed directly in user code.           */
/******************************************************************************/
/* void SPI1_IRQHandler(void)
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
