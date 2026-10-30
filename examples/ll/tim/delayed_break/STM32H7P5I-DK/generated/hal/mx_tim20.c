/**
  ******************************************************************************
  * @file           : mx_tim20.c
  * @brief          : Peripheral initialization
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
#include "mx_tim20.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for TIM20 in LL layer */
/******************************************************************************/

TIM_TypeDef *mx_tim20_init(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM20);

  /* Timer configuration to reach the output frequency at 10 kHz */
  LL_TIM_SetPrescaler(TIM20, 519);
  /* LL_TIM_SetCounterMode(TIM20, LL_TIM_COUNTERMODE_UP); */ /* Configuration matches register reset state at startup. */
  LL_TIM_SetAutoReload(TIM20, 99);
  /* LL_TIM_SetClockDivision(TIM20, LL_TIM_CLOCKDIVISION_DIV1); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_SetClockDivision2(TIM20, LL_TIM_CLOCKDIVISION2_DIV1); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_SetClockSource(TIM20, LL_TIM_CLK_INTERNAL); */ /* Configuration matches register reset state at startup. */

  /* Channel 2 Configuration */
  /* LL_TIM_OC_SetPolarity(TIM20, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetIdleState(TIM20, LL_TIM_CHANNEL_CH2, LL_TIM_OCIDLESTATE_RESET); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetOverrideState(TIM20, LL_TIM_CHANNEL_CH2, LL_TIM_OCOVERRIDE_RESET); */ /* Configuration matches register reset state at startup. */
  LL_TIM_OC_SetBreakMode(TIM20, LL_TIM_CHANNEL_CH2, LL_TIM_OCBREAKMODE_DELAY1);

  /* Compare Unit 2 Configuration */
  LL_TIM_OC_SetMode(TIM20, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetCompareValue(TIM20, LL_TIM_OC_COMPARE_UNIT_2, 90);
  LL_TIM_OC_EnablePreload(TIM20, LL_TIM_CHANNEL_CH2);

  /* Channel 3 Configuration */
  /* LL_TIM_OC_SetPolarity(TIM20, LL_TIM_CHANNEL_CH3, LL_TIM_OCPOLARITY_HIGH); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetIdleState(TIM20, LL_TIM_CHANNEL_CH3, LL_TIM_OCIDLESTATE_RESET); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetOverrideState(TIM20, LL_TIM_CHANNEL_CH3, LL_TIM_OCOVERRIDE_RESET); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetBreakMode(TIM20, LL_TIM_CHANNEL_CH3, LL_TIM_OCBREAKMODE_IMMEDIATE); */ /* Configuration matches register reset state at startup. */

  /* Compare Unit 3 Configuration */
  LL_TIM_OC_SetMode(TIM20, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetCompareValue(TIM20, LL_TIM_OC_COMPARE_UNIT_3, 90);
  LL_TIM_OC_EnablePreload(TIM20, LL_TIM_CHANNEL_CH3);

  /* Channel 4 Configuration */
  /* LL_TIM_OC_SetPolarity(TIM20, LL_TIM_CHANNEL_CH4, LL_TIM_OCPOLARITY_HIGH); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetIdleState(TIM20, LL_TIM_CHANNEL_CH4, LL_TIM_OCIDLESTATE_RESET); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_OC_SetOverrideState(TIM20, LL_TIM_CHANNEL_CH4, LL_TIM_OCOVERRIDE_RESET); */ /* Configuration matches register reset state at startup. */
  LL_TIM_OC_SetBreakMode(TIM20, LL_TIM_CHANNEL_CH4, LL_TIM_OCBREAKMODE_DELAY2);

  /* Compare Unit 4 Configuration */
  LL_TIM_OC_SetMode(TIM20, LL_TIM_CHANNEL_CH4, LL_TIM_OCMODE_PWM1);
  LL_TIM_OC_SetCompareValue(TIM20, LL_TIM_OC_COMPARE_UNIT_4, 90);
  LL_TIM_OC_EnablePreload(TIM20, LL_TIM_CHANNEL_CH4);

  /* Disable update interrupt with update generation (UG)
     by changing update request source (URS) to avoid update flag (UIF) */
  LL_TIM_SetUpdateSource(TIM20, LL_TIM_UPDATESOURCE_COUNTER);
  /* Generate an update event to reload the prescaler
     and the repetition counter (if applicable) values immediately */
  LL_TIM_GenerateEvent_UPDATE(TIM20);

  /* Update Event Management */
  LL_TIM_SetUpdateSource(TIM20, LL_TIM_UPDATESOURCE_REGULAR);
  /* LL_TIM_EnableUpdateEvent(TIM20); */ /* Configuration matches register reset state at startup. */

  /* Break Configuration */
  LL_TIM_EnableAutomaticOutput(TIM20);

  LL_TIM_SetOffStates(TIM20, LL_TIM_OSSI_ENABLE, LL_TIM_OSSR_ENABLE);

  /* Break Configuration */
  /* LL_TIM_ConfigBRK(TIM20, LL_TIM_BREAK_POLARITY_LOW, LL_TIM_BREAK_FILTER_FDIV1, LL_TIM_BREAK_AFMODE_INPUT); */ /* Configuration matches register reset state at startup. */
  LL_TIM_SetBreakDelay(TIM20, LL_TIM_BREAK_DELAY1, 60);
  LL_TIM_SetBreakDelay(TIM20, LL_TIM_BREAK_DELAY2, 120);

  /* Break Input Sources Configuration */
  /* LL_TIM_SetBreakInputSourcePolarity(TIM20, LL_TIM_BREAK_INPUT_1, LL_TIM_TIM20_BRK_GPIO, LL_TIM_BREAK_INPUT_SRC_NONINVERTED); */ /* Configuration matches register reset state at startup. */
  /* LL_TIM_EnableBreakInputSource(TIM20, LL_TIM_BREAK_INPUT_1, LL_TIM_TIM20_BRK_GPIO); */ /* Configuration matches register reset state at startup. */

  /* Enable Break 1 Input */
  LL_TIM_EnableBreakInput(TIM20, LL_TIM_BREAK_INPUT_1);

  /* ### TIM20 GPIO Configuration ########################### */

  /* GPIO Clocks activation */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD | LL_AHB4_GRP1_PERIPH_GPIOC | LL_AHB4_GRP1_PERIPH_GPIOI | LL_AHB4_GRP1_PERIPH_GPIOB);

  /**
    [GPIO Pin] ------> [Signal Name]

       PD10    ------>   TIM20_CH3
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOD, LL_GPIO_PIN_10, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_10, LL_GPIO_AF_9);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);

  /**
    [GPIO Pin] ------> [Signal Name]

       PC2     ------>   TIM20_CH2
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_2, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_2, LL_GPIO_AF_9);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);

  /**
    [GPIO Pin] ------> [Signal Name]

       PI2     ------>   TIM20_CH4
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOI, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOI, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  /* LL_GPIO_SetPinPull(GPIOI, LL_GPIO_PIN_2, LL_GPIO_PULL_NO); */ /* Configuration matches register reset state at startup. */

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOI, LL_GPIO_PIN_2, LL_GPIO_AF_9);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOI, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB8     ------>   TIM20_BKIN
    **/

  /* Configure IO output speed (Low, Medium, High or Very-High) */
  /* LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_LOW); */ /* Configuration matches register reset state at startup. */

  /* Configure IO output type (Push-Pull or Open-Drain) */
  /* LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL); */ /* Configuration matches register reset state at startup. */

  /* Activate the Pull-up, Pull-down resistor, or No pull for the current IO */
  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_8, LL_GPIO_PULL_UP);

  /* Configure the Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_8, LL_GPIO_AF_9);

  /* Configure IO direction mode (Input, Output, Alternate or Analog) */
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);

  return TIM20;
}

void mx_tim20_deinit(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM20);

  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM20);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM20);

  /* ### GPIO deinitialization of TIM20: TIM20_CH3 ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_10, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_10, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOD, LL_GPIO_PIN_10, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOD, LL_GPIO_PIN_10, LL_GPIO_PIN_RESET);

  /* ### GPIO deinitialization of TIM20: TIM20_CH2 ########################### */

  /* Configure IO in Analog Mode */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_2, LL_GPIO_MODE_ANALOG);

  /* Configure the default Alternate Function in current IO */
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_2, LL_GPIO_AF_0);

  /* Configure the default value for IO Speed */
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_LOW);

  /* Configure the default value IO Output Type */
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);

  /* Deactivate the Pull-up and Pull-down resistor for the current IO */
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_2, LL_GPIO_PULL_NO);

  /* Reset the IO output state */
  LL_GPIO_WriteOutputPin(GPIOC, LL_GPIO_PIN_2, LL_GPIO_PIN_RESET);

  /* ### GPIO deinitialization of TIM20: TIM20_CH4 ########################### */

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

  /* ### GPIO deinitialization of TIM20: TIM20_BKIN ########################### */

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
}
