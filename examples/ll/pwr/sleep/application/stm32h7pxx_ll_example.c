/**
  ******************************************************************************
  * file           : stm32h7pxx_ll_example.c
  * brief          : Enter and exit the Sleep mode through an EXTI interrupt using the LL API
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ll_example.h"

/* Private functions prototype -----------------------------------------------*/
void mx_extix_irqhandler(void);

/** brief:  System configuration for typical power consumption.
  * retval: system status
  */
system_status_t PWR_SystemOptimization(void)
{
  if (mx_rccx_init() != SYSTEM_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (mx_pwrx_init() != SYSTEM_OK)
  {
    return SYSTEM_POWER_ERROR;
  }

  return SYSTEM_OK;
}


/** brief: Enable the EXTI Line 13 interrupt.
  */
inline void EXTI_EnableLineMode_IT(void)
{
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_13);
}


/** brief: Enter the Sleep mode request.
  */
inline void PWR_EnterSleepMode(void)
{
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  SCB_DisableDeepSleep();

  /* Wait For Interrupt Request */
  __WFI();
}


/** brief: Handles the EXTI line interrupts.
  */
void mx_extix_irqhandler(void)
{
  if (LL_EXTI_IsActiveTriggerFlag_0_31(MX_EXTIX_EXTI_LINE) != 0U)
  {
    LL_EXTI_ClearTriggerFlag_0_31(MX_EXTIX_EXTI_LINE);
  }
}
