/**
  ******************************************************************************
  * @file           : mx_comp3.c
  * @brief          : COMP3 Peripheral initialization
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
#include "mx_comp3.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/******************************************************************************/
/* Exported functions for COMP3 in LL layer */
/******************************************************************************/
COMP_TypeDef *mx_comp3_init(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP34);

  /* LL_COMP_SetCommonWindowMode(LL_COMP_COMMON_INSTANCE(COMP3), LL_COMP_WINDOW_DISABLE); */
  /* LL_COMP_SetCommonWindowOutput(LL_COMP_COMMON_INSTANCE(COMP3), LL_COMP_WINDOW_OUTPUT_INDEPT); */
  LL_COMP_ConfigInputs(COMP3, LL_COMP_INPUT_MINUS_VREFINT, LL_COMP_INPUT_PLUS_IO3);
  /* LL_COMP_SetInputHysteresis(COMP3, LL_COMP_HYSTERESIS_NONE); */ /* Configuration matches register reset state at startup. */
  /* LL_COMP_SetOutputPolarity(COMP3, LL_COMP_OUTPUTPOL_NONINVERTED); */ /* Configuration matches register reset state at startup. */

  /* ### COMP3 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);

  /**
    [GPIO Pin] ------> [Signal Name]

       PF7     ------>   COMP3_INP3
    **/

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOF, LL_GPIO_PIN_7, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  /* LL_GPIO_SetPinMode(GPIOF, LL_GPIO_PIN_7, LL_GPIO_MODE_ANALOG); */ /* Configuration matches register reset state at startup. */

  /* Configuration of EXTI line used by comparator to generate an interrupt */
  LL_EXTI_EnableRisingTrig_32_63(LL_EXTI_LINE_62);
  LL_EXTI_EnableFallingTrig_32_63(LL_EXTI_LINE_62);

  /* Enable comparator interruption through EXTI */
  NVIC_SetPriority(COMP3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
  NVIC_EnableIRQ(COMP3_IRQn);

  return COMP3;
}

void mx_comp3_deinit(void)
{
  LL_COMP_Disable(COMP3);

  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP34);

  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP34);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP34);

  /* ### GPIO deinitialization of COMP3: COMP3_INP3 ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOF, LL_GPIO_PIN_7, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOF, LL_GPIO_PIN_7, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOF, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOF, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOF, LL_GPIO_PIN_7, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOF, LL_GPIO_PIN_7, LL_GPIO_PIN_RESET);

  NVIC_DisableIRQ(COMP3_IRQn);
}

/******************************************************************************/
/*    COMP3 interrupt through EXTI line is managed directly in user code.     */
/******************************************************************************/
/* void COMP3_IRQHandler(void)
{
}
  */
