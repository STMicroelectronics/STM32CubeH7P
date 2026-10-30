/**
  ******************************************************************************
  * @file           : mx_lptim2.c
  * @brief          : LPTIM2 Peripheral initialization
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
#include "mx_lptim2.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported variables by reference--------------------------------------------*/
/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for SW instance in LL layer */
/******************************************************************************/
LPTIM_TypeDef *mx_lptim2_init(void)
{
  /* Init GPIO */
  /* ### LPTIM2 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);

  /**
    [GPIO Pin] ------> [Signal Name]

       PA4     ------>   LPTIM2_CH1
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_MEDIUM);

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_4, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_4, LL_GPIO_PULL_UP);

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_4, LL_GPIO_AF_6);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ALTERNATE);

  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE_LSE);

  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM2);

  /*Configure the low power timer's time-base unit.*/
  LL_LPTIM_Enable(LPTIM2);
  LL_LPTIM_WRITE_REG(LPTIM2, ICR, LL_LPTIM_FLAG_ALL);
  LL_LPTIM_SetRepetition(LPTIM2, 0x0000);

  /* Infinite loop */
  do
  {
  }
  while (LL_LPTIM_IsActiveFlag_REPOK(LPTIM2) == 0);
  LL_LPTIM_ClearFlag_REPOK(LPTIM2);
  LL_LPTIM_SetAutoReload(LPTIM2, 0xFFFF);

  /* Infinite loop */
  do
  {
  }
  while (LL_LPTIM_IsActiveFlag_ARROK(LPTIM2) == 0);
  LL_LPTIM_ClearFlag_ARROK(LPTIM2);
  LL_LPTIM_Disable(LPTIM2);
  /* LL_LPTIM_SetClockSource(LPTIM2, LL_LPTIM_CLK_SOURCE_INTERNAL); */ /* Configuration matches register reset state at startup. */
  /* LL_LPTIM_SetCounterMode(LPTIM2, LL_LPTIM_COUNTER_MODE_INTERNAL); */ /* Configuration matches register reset state at startup. */
  /* LL_LPTIM_SetPrescaler(LPTIM2, LL_LPTIM_PRESCALER_DIV1); */ /* Configuration matches register reset state at startup. */

  /*Configure the Input channel/Input Capture*/
  LL_LPTIM_SetRemap(LPTIM2, LL_LPTIM_LPTIM2_IC1_RMP_GPIO);
  /* LL_LPTIM_IC_SetPolarity(LPTIM2, LL_LPTIM_CHANNEL_CH1, LL_LPTIM_ICPOLARITY_RISING); */ /* Configuration matches register reset state at startup. */
  /* LL_LPTIM_IC_SetFilter(LPTIM2, LL_LPTIM_CHANNEL_CH1, LL_LPTIM_ICFLT_CLOCK_DIV1); */ /* Configuration matches register reset state at startup. */
  /* LL_LPTIM_IC_SetPrescaler(LPTIM2, LL_LPTIM_CHANNEL_CH1, LL_LPTIM_ICPSC_DIV1); */ /* Configuration matches register reset state at startup. */
  LL_LPTIM_CC_SetChannelMode(LPTIM2, LL_LPTIM_CHANNEL_CH1, LL_LPTIM_CCMODE_INPUTCAPTURE);

  /* ################################################## LPTIM2 IC1 DMA configuration */

  /* Enable GPDMA1 clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);

  /* Configure DMA channel transfer request */
  LL_DMA_SetPeriphRequest(GPDMA1_CH0, LL_GPDMA1_REQUEST_LPTIM2_IC1);

  /* Configure DMA channel transfer direction */
  /* LL_DMA_SetDataTransferDirection(GPDMA1_CH0, LL_DMA_DIRECTION_PERIPH_TO_MEMORY); */ /* Configuration matches register reset state at startup. */

  /* Configure DMA channel priority level */
  LL_DMA_SetChannelPriorityLevel(GPDMA1_CH0, LL_DMA_PRIORITY_HIGH);

  /* Configure DMA channel transfer register 1 */
  LL_DMA_ConfigTransfer(GPDMA1_CH0,
                        (LL_DMA_SRC_ADDR_FIXED | LL_DMA_SRC_DATA_WIDTH_HALFWORD | \
                         LL_DMA_DEST_ADDR_INCREMENTED | LL_DMA_DEST_DATA_WIDTH_HALFWORD));

  /* Configure DMA channel hardware request mode */
  /* LL_DMA_SetHWRequestMode(GPDMA1_CH0, LL_DMA_HARDWARE_REQUEST_BURST); */ /* Configuration matches register reset state at startup. */

  /* Enable the interruption for DMA */
  NVIC_SetPriority(GPDMA1_CH0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(GPDMA1_CH0_IRQn);
return LPTIM2;
}

void mx_lptim2_deinit(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM2);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM2);

  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM2);
  /* deinit GPIO configuration */
  /* ### GPIO deinitialization of LPTIM2: LPTIM2_CH1 ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_4, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_4, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_4, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOA, LL_GPIO_PIN_4, LL_GPIO_PIN_RESET);

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
}

/******************************************************************************/
/*        GPDMA1 channel 0 interrupt is managed directly in user code.        */
/******************************************************************************/
/* void GPDMA1_CH0_IRQHandler(void)
{
}
  */
