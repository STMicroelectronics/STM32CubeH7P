/**
  ******************************************************************************
  * file           : stm32h7pxx_pwr_optim_example.c
  * brief          : System configuration for STM32H7Pxx Stop mode.
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE.md
  * file in the root directory of this software component.
  * If no LICENSE.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pwr_optim_example.h"

/* Exported functions ------------------------------------------------------- */

/**
  * brief  Configure the system clock and power baseline used by the example.
  * retval system status
  */
system_status_t PWR_SystemOptimization(void)
{
  if (mx_rccx_init() != SYSTEM_OK)
  {
    return SYSTEM_CLOCK_ERROR;
  }

  if (mx_pwr_init() != SYSTEM_OK)
  {
    return SYSTEM_POWER_ERROR;
  }

  return SYSTEM_OK;
}
