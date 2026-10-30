/**
  ******************************************************************************
  * file           : stm32h7pxx_ll_example.c
  * brief          : Enter and exit the Stop mode through an EXTI interrupt using the LL API
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype -----------------------------------------------*/
void mx_extix_irqhandler(void);

/* Private functions ---------------------------------------------------------*/

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


/** brief: Clear the Stop flag.
  */
inline void PWR_ClearStopFlag(void)
{
  LL_PWR_ClearFlag_STOP();
}


/** brief: Enter the Stop mode request.
  */
inline void PWR_EnterStopMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB_EnableDeepSleep();

  LL_PWR_SetPowerMode(LL_PWR_STOP_MODE);

  /* Wait For Interrupt Request */
  __WFI();
}


/** brief:  Check if the system has resumed from Stop mode.
  * retval: system_status_t
  */
inline system_status_t PWR_CheckSystemStopMode(void)
{
  system_status_t system_status = SYSTEM_PERIPHERAL_ERROR;

  /* Check that the system has resumed from Stop mode */
  if (LL_PWR_IsActiveFlag_STOP() != 0U)
  {
    system_status = SYSTEM_OK;
  }

  return system_status;
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
