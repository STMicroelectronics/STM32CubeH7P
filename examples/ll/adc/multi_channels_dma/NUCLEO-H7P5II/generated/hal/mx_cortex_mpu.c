/**
  ******************************************************************************
  * @file           : mx_cortex_mpu.c
  * @brief          : CORTEX_MPU Peripheral initialization
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
#include "mx_cortex_mpu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/******************************************************************************/
/* Exported functions for CORTEX_MPU in LL layer */
/******************************************************************************/

system_status_t mx_cortex_mpu_init(void)
{
  /* Disables the MPU */
  ARM_MPU_Disable();

  /*
     Initializes and configures the MPU Region
  */

  ARM_MPU_SetRegionEx(0, 0x00000000,
                      (0x1F << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x00 << MPU_RASR_AP_Pos)
                      | (0x1 << MPU_RASR_XN_Pos)
                      | (0x87 << MPU_RASR_SRD_Pos));

  STM32_WRITE_REG(MPU->RNR, 0);
  STM32_SET_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);

  ARM_MPU_SetRegionEx(1, 0x30000000,
                      (0x09 << MPU_RASR_SIZE_Pos)
                      | (0x000C0000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x03 << MPU_RASR_AP_Pos)
                      | (0x1 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));

  STM32_WRITE_REG(MPU->RNR, 1);
  STM32_SET_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);

  /* Enables the MPU */
  ARM_MPU_Enable(MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk);

  return SYSTEM_OK;
}

void mx_cortex_mpu_deinit(void)
{
  /* Disables the MPU */
  ARM_MPU_Disable();

  STM32_WRITE_REG(MPU->RNR, 0);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 1);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 2);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 3);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 4);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 5);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 6);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 7);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 8);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 9);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 10);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 11);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 12);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 13);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 14);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
  STM32_WRITE_REG(MPU->RNR, 15);
  STM32_CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);

  /*
     Deinitializes and configures the MPU Region to default
  */
  ARM_MPU_SetRegionEx(0, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(1, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(2, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(3, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(4, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(5, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(6, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(7, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(8, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(9, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(10, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(11, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(12, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(13, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(14, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
  ARM_MPU_SetRegionEx(15, 0x00000000,
                      (0x1B << MPU_RASR_SIZE_Pos)
                      | (0x00000000 &  (MPU_RASR_TEX_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk | MPU_RASR_C_Msk))
                      | (0x01 << MPU_RASR_AP_Pos)
                      | (0x00 << MPU_RASR_XN_Pos)
                      | (0x00 << MPU_RASR_SRD_Pos));
}
