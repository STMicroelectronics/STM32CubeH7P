/**
  ******************************************************************************
  * @file           : mx_pwr.c
  * @brief          : PWR Peripheral initialization
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
#include "mx_pwr.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/******************************************************************************/
/* Exported functions for PWR in LL layer                                    */
/******************************************************************************/

system_status_t mx_pwr_init(void)
{
  /****************************************************************************/
  /* Main supply configuration                                                */
  /****************************************************************************/
  /* Stop Voltage scaling configuration */
  /* LL_PWR_SetStopRegulatorVoltageScaling(LL_PWR_REGU_STOP_VOLT_SCALE_HIGH); */ /* Configuration matches register reset state at startup. */

  /****************************************************************************/
  /* Configuration of the UCPD (USB Type-C and Power Delivery) PWR features   */
  /****************************************************************************/
  /* Enable Dead Battery mode */
  /* LL_PWR_EnableUCPDDeadBattery(); */ /* Configuration matches register reset state at startup. */

  /* Enable UCPD configuration retention in Standby mode */
  /* LL_PWR_EnableUCPDRetentionStandbyMode(); */ /* Configuration matches register reset state at startup. */

  return SYSTEM_OK;
}

system_status_t mx_pwr_deinit(void)
{
  return SYSTEM_OK;
}
