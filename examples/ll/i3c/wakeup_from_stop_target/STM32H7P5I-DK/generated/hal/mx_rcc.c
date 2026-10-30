
/**
  ******************************************************************************
  * @file           : mx_rcc.c
  * @brief          : STM32 RCC program body
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
#include "mx_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/******************************************************************************/
/* Exported functions for RCC in LL layer */
/******************************************************************************/

/**
  * Configure the system core clock only and activate it using the LL RCC unitary APIs (footprint optimization)
  *         The system Clock is configured as follow :
  *            System Clock source            = PLLCLK
  *            SYSCLK(Hz)                     = 520000000
  *            CPUCLK(Hz)                     = 520000000
  *            AXICLK/ACLK(Hz)                = 260000000
  *            CPU Prescaler                  = 1
  *            ACLK Prescaler                 = 2
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 2
  *            APB4 Prescaler                 = 2
  *            PLL1M                          = 8
  *            PLL1N                          = 65
  *            PLL1P                          = 1
  *            PLL1Q                          = 2
  *            PLL1R                          = 1
  *            PLL1S                          = 1
  *            PLL1T                          = 1
  *            PLL1FracN                      = 0
  *            Flash Latency(WS)              = 6
  */
system_status_t mx_rcc_init(void)
{
  /* Configure the Voltage scaling level */
  LL_PWR_SetRegulatorVoltageScaling(LL_PWR_REGU_VOLT_SCALE_0);

  /* Poll on VOS ready and Active VOS ready flag to reach correct voltage */
  while((LL_PWR_IsActiveFlag_VOS() == 0U) || (LL_PWR_IsActiveFlag_ACTVOS() == 0U));

  /* LL_RCC_HSI_SetDivider(LL_RCC_HSI_DIV_1); */ /* Configuration matches register reset state at startup. */
  /* LL_RCC_HSI_Enable();
  do
  {
  }
  while (LL_RCC_HSI_IsReady() != 1U);
  */

  LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSI);
  LL_RCC_PLL1_SetM(8U);
  LL_RCC_PLL1_SetN(65U);
  LL_RCC_PLL1_SetP(1U);
  LL_RCC_PLL1_SetQ(2U);
  /* LL_RCC_PLL1_SetS(1U); */ /* Configuration matches register reset state at startup. */
  LL_RCC_PLL1_SetInputRange(LL_RCC_PLL1INPUTRANGE_8_16);
  LL_RCC_PLL1_SetVCORange(LL_RCC_PLL1VCORANGE_384_1672);

  LL_RCC_PLL1_Enable();
  /* Infinite loop */
  do
  {
  }
  while (LL_RCC_PLL1_IsReady() != 1U);

  LL_RCC_PLL1_EnableOutputP();

  /* Frequency will be increased */
  LL_FLASH_SetLatency(FLASH, LL_FLASH_LATENCY_6WS);
  if (LL_FLASH_GetLatency(FLASH) != LL_FLASH_LATENCY_6WS)
  {
    return SYSTEM_CLOCK_ERROR;
  }
  LL_FLASH_SetProgrammingDelay(FLASH, LL_FLASH_PROGRAM_DELAY_3);

  /** Initializes the CPU, AHB and APB busses clocks */
  LL_RCC_ConfigBusClock(LL_RCC_BMCLK_PRESCALER_2, LL_RCC_APB1_PRESCALER_2 |
                        LL_RCC_APB2_PRESCALER_2 | LL_RCC_APB4_PRESCALER_2);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
  /* Wait till System clock is ready */
  /* Infinite loop */
  do
  {
  }
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1);

  LL_SetSystemCoreClock(520000000U);
  LL_Init1msTick(SystemCoreClock);

  /* No GPIO configuration required for RCC */

  return SYSTEM_OK;
}

void mx_rcc_deinit(void)
{
  /* Disable RCC interrupts */
  LL_RCC_DisableIT(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSERDY | \
                   LL_RCC_IT_CSIRDY | LL_RCC_IT_HSI48RDY | LL_RCC_IT_PLL1RDY | LL_RCC_IT_PLL2RDY | \
                   LL_RCC_IT_PLL3RDY | LL_RCC_IT_LSECSS);

  /* Reset System clock */
  LL_RCC_HSI_SetDivider(LL_RCC_HSI_DIV_1);
  LL_RCC_HSI_Enable();
  /* Infinite loop */
  do
  {
  }
  while (LL_RCC_HSI_IsReady() != 1U);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  /* Wait till System clock is ready */
  /* Infinite loop */
  do
  {
  }
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);

  /* Reset all bus dividers */
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_PRESCALER_1);
  LL_RCC_ConfigBusClock(LL_RCC_BMCLK_PRESCALER_1, LL_RCC_APB1_PRESCALER_1 |
                        LL_RCC_APB2_PRESCALER_1 | LL_RCC_APB4_PRESCALER_1);

  SystemCoreClock = HSI_VALUE;

  /* Adapt Systick interrupt period */

  /* Reset all remaining oscillators not in backup domain (excepted the one used for System clock) */
  uint32_t read_value = LL_RCC_READ_REG(CR);

  LL_RCC_WRITE_REG(CR, (RCC_CR_Rst | (read_value & (RCC_CR_HSEBYP | RCC_CR_HSEEXT))));
  LL_RCC_WRITE_REG(CR, RCC_CR_Rst); /* HSE EXT and BYP disabled only when HSE has been disabled */

  LL_RCC_LSI_Disable();

  /* Reset MCO, RTC prescaler and wake up system clock */

  /* Reset MCO, wake up system clock (not RTC prescaler) */
  read_value  = LL_RCC_READ_REG(CFGR);
  LL_RCC_WRITE_REG(CFGR, (RCC_CFGR_Rst | (read_value & RCC_CFGR_RTCPRE)));

  /* Reset PLLs */
  LL_RCC_WRITE_REG(PLLCKSELR, RCC_PLLCKSELR_Rst);
  LL_RCC_WRITE_REG(PLLCFGR, RCC_PLLCFGR_Rst);

  LL_RCC_WRITE_REG(PLL1DIVR1, RCC_PLL1DIVR1_Rst);
  LL_RCC_WRITE_REG(PLL1DIVR2, RCC_PLL1DIVR2_Rst);
  LL_RCC_WRITE_REG(PLL1FRACR, RCC_PLL1FRACR_Rst);
  LL_RCC_WRITE_REG(PLL1SSCGR, RCC_PLL1SSCGR_Rst);

  LL_RCC_WRITE_REG(PLL2DIVR1, RCC_PLL2DIVR1_Rst);
  LL_RCC_WRITE_REG(PLL2DIVR2, RCC_PLL2DIVR2_Rst);
  LL_RCC_WRITE_REG(PLL2FRACR, RCC_PLL2FRACR_Rst);
  LL_RCC_WRITE_REG(PLL2SSCGR, RCC_PLL2SSCGR_Rst);

  LL_RCC_WRITE_REG(PLL3DIVR1, RCC_PLL3DIVR1_Rst);
  LL_RCC_WRITE_REG(PLL3DIVR2, RCC_PLL3DIVR2_Rst);
  LL_RCC_WRITE_REG(PLL3FRACR, RCC_PLL3FRACR_Rst);
  LL_RCC_WRITE_REG(PLL3SSCGR, RCC_PLL3SSCGR_Rst);

  /* Clear RCC flags */
  LL_RCC_ClearFlag(LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSERDY | \
                   LL_RCC_IT_CSIRDY | LL_RCC_IT_HSI48RDY | LL_RCC_IT_PLL1RDY | LL_RCC_IT_PLL2RDY | \
                   LL_RCC_IT_PLL3RDY | LL_RCC_IT_HSECSS | LL_RCC_IT_LSECSS);

  LL_RCC_ClearResetFlags();
}

/**
  * configures and activate the clocks used by all the peripherals selected within the project
  */
system_status_t mx_rcc_peripherals_clock_config(void)
{
  /* Resources using HSI (64 MHz):
    I3C1
  */
  /* HSI already enabled inside mx_rcc_init() */

  return SYSTEM_OK;
}
