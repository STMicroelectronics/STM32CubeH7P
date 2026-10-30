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
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);

  /**
    [GPIO Pin] ------> [Signal Name]

       PC4     ------>   LPTIM2_ETR
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_4, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_4, LL_GPIO_PULL_UP);

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_4, LL_GPIO_AF_3);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_4, LL_GPIO_MODE_ALTERNATE);

  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE_LSI);

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
  LL_LPTIM_SetAutoReload(LPTIM2, 0x7D00);

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

  /*Configure the Output channel/Output Compare*/
  LL_LPTIM_Enable(LPTIM2);
  LL_LPTIM_WRITE_REG(LPTIM2, ICR, LL_LPTIM_ISR_CMP1OK);
  LL_LPTIM_OC_SetCompareCH1(LPTIM2, 32000);

  /* Infinite loop */
  do
  {
  }
  while (LL_LPTIM_IsActiveFlag_CMP1OK(LPTIM2) == 0);
  LL_LPTIM_ClearFlag_CMP1OK(LPTIM2);
  LL_LPTIM_Disable(LPTIM2);

  /*Configure External Trigger (ETR) input*/
  LL_LPTIM_ConfigTrigger(LPTIM2, LL_LPTIM_TRIG_SOURCE_GPIO, LL_LPTIM_TRIG_FILTER_NONE, LL_LPTIM_TRIG_POLARITY_RISING_FALLING);

  /* Enable the LPTIM global interruption */
  NVIC_SetPriority(LPTIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(LPTIM2_IRQn);

return LPTIM2;
}

void mx_lptim2_deinit(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM2);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM2);

  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM2);
  /* deinit GPIO configuration */
  /* ### GPIO deinitialization of LPTIM2: LPTIM2_ETR ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_4, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_4, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_4, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOC, LL_GPIO_PIN_4, LL_GPIO_PIN_RESET);

  /* Disable the LPTIM global interruption */
  NVIC_DisableIRQ(LPTIM2_IRQn);
}

/******************************************************************************/
/*         LPTIM2 global interrupt is managed directly in user code.          */
/******************************************************************************/
/* void LPTIM2_IRQHandler(void)
{
}
  */
