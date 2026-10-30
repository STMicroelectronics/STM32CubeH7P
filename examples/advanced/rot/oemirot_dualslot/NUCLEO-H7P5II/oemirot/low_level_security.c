/**
  ******************************************************************************
  * @file    low_level_security.c
  * @brief   security protection implementation for secure boot
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "boot_hal_cfg.h"
#include "boot_hal_flowcontrol.h"
#include "region_defs.h"
#include "mcuboot_config.h"
#include "low_level_security.h"
#include "low_level_security_config.h"
#include "boot_hal_utils.h"
#include "low_level_rng.h"
#include "bootutil_priv.h"
#include <inttypes.h> /* PRIx32, PRIu32 */

/* Private defines -----------------------------------------------------------*/
#if defined(__FPU_USED) && (__FPU_USED == 1U)
#error "FPU core sticky bit must be disabled in boot stage to allow flexibility to use it or not in next stage"
#endif /* (__FPU_USED) && (__FPU_USED == 1U) */

/* Log macro enabled only when uFlowStage is FLOW_STAGE_CFG */
#define SECURITY_PROTECTION_LOG(...) \
  do { if (uFlowStage == FLOW_STAGE_CFG) { ROT_LOG_INF(__VA_ARGS__); } } while (0)

#define TAMP_SR_NO_EVENT (0U)

#define WRP_CFG_START          (FLASH_ROT_WRP_START_OFFSET / PAGE_SIZE)
#define WRP_CFG_END            (FLASH_ROT_WRP_END_OFFSET / PAGE_SIZE)
#if (WRP_CFG_END > LAST_PAGE_IN_BANK)
#error "WRP configuration check not supported"
#endif /* (WRP_CFG_END > LAST_PAGE_IN_BANK) */

#define HDP_CFG_START          (0U)
#define HDP_CFG_END            (FLASH_ROT_HDP_END_OFFSET / HDP_BLOCK_SIZE)
#if (HDP_CFG_END > LAST_HDP_BLOCK_IN_BANK)
#error "HDP configuration check not supported"
#endif /* (HDP_CFG_END > LAST_PAGE_IN_BANK) */

/* Private function prototypes -----------------------------------------------*/
static void mpu_init_cfg(void);
static void mpu_appli_cfg(void);
static void ram_init_cfg(void);
static void tamper_init_cfg(void);
static void tamper_clear_flags(void);
static void flash_ecc_init_cfg(void);
static void flash_ecc_appli_cfg(void);
static void flash_init_cfg(void);
static void flash_appli_cfg(void);
static void crypto_reset_clocks(void);
static void cache_init_cfg(void);

/* external function prototypes ----------------------------------------------*/

/* Exported function definitions ---------------------------------------------*/

/**
  * @brief  Provided the early tamper configuration for Reset_Handler.
  * @param  None
  * @note   No stack must be used.
  * @retval None
  */
void SECURITY_ApplyTamperEarlyStartup(void)
{
  /* enable write access to backup domain */
  HAL_PWR_DisableRTCDomainWriteProtection();
  (void)HAL_PWR_IsEnabledRTCDomainWriteProtection(); /* Dummy read to wait for write effectiveness */

  /**
    * Enable RCC APB clock of RTC for tamper register access
    * Note: This access is done in register interface,
    * because if a tamper has occurred, the RAM is write-ignored / read as zero
    */
  STM32_ATOMIC_SET_BIT_32(RCC->APB4ENR, RCC_APB4ENR_RTCAPBEN & LL_APB4_GRP1_PERIPH_ALL_EN_MASK);

  /**
    * Release reset of back-up domain in case it is set, to avoid
    * blocking the device (system reset does not release it)
    */
  STM32_ATOMIC_CLEAR_BIT_32(RCC->BDCR, RCC_BDCR_VSWRST);
  (void)STM32_READ_REG(RCC->BDCR); /* Dummy read to wait for write effectiveness */

  /* LL_TAMP */
  /* Check if a tamper has occurred */
  if (LL_TAMP_IsActiveFlag_ITAMP(LL_TAMP_ITAMP_ALL) != 0U)
  {
    /* ITAMP flag set, clear it */
    tamper_clear_flags();
  }
  else if (LL_TAMP_IsActiveFlag_TAMP(LL_TAMP_ALL) != 0U)
  {
    /* TAMP flag set, clear it */
    tamper_clear_flags();
  }
  else
  {
    /**
      * Enable TAMP IRQ , to catch tamper interrupt in TAMP_IRQHandler
      * else a stack in SRAM is cleaned a HardFault can occur, at every pop of
      * function
      */
    __enable_irq();
    HAL_CORTEX_NVIC_EnableIRQ(TAMP_IRQn);
  }
}

/**
  * @brief  Enable the cryptography clocks.
  * @param  None
  * @retval None
  */
void SECURITY_EnableCryptoClocks(void)
{
  /**
    * - Stop all used Crypton S_HCLK using RCC
    * - Drive low pulse on RNG_HRESETn, HASH_HRESETn using RCC
    * - Start all used crypton clocks RNG_HCLK, HASH_HCLK
    */
  crypto_reset_clocks();

  /* -3- Enable the clock of the used Crypto IPs */
  HAL_RCC_RNG_EnableClock();
  HAL_RCC_HASH_EnableClock();
}

/**
  * @brief  Disable the cryptography clocks.
  * @param  None
  * @retval None
  */
void SECURITY_DisableCryptoClocks(void)
{
  /**
    * - Stop all used Crypton S_HCLK using RCC
    * - Drive low pulse on RNG_HRESETn, HASH_HRESETn using RCC
    */
  crypto_reset_clocks();
}

/**
  * @brief  Apply the runtime security protections.
  * @param  None
  * @note   By default, the recommended security protections for the platform are applied.
  * @retval None
  */
void SECURITY_ApplyRunTimeProtections(void)
{
  SECURITY_PROTECTION_LOG("Applying runtime security protections:");

  /* Configure cache */
  cache_init_cfg();

  /* Set MPU to forbid execution outside of immutable code */
  mpu_init_cfg();

  /* Configure FLASH access */
  flash_init_cfg();

  /* With OEMIROT_DEV_MODE, active tamper calls Error_Handler */
  tamper_init_cfg();

  /* Configure SRAM ECC */
  ram_init_cfg();

  /* Configure FLASH ECC */
  flash_ecc_init_cfg();
}

/**
  * @brief  Update the runtime security protections for application start.
  * @param  None
  * @retval None
  */
void SECURITY_UpdateRunTimeProtections(void)
{
  /* Update MPU config for application execution */
  mpu_appli_cfg();

  /* Update FLASH configuration for application execution */
  flash_appli_cfg();

  /* Update FLASH ECC for application execution */
  flash_ecc_appli_cfg();
}

/**
  * @brief  Check if the Static security protections are correctly configured.
  *         Those protections are not impacted by a Reset. They are set using the Option Bytes.
  *         When the device is locked, these protections cannot be changed anymore.
  * @param  None
  * @note   By default, the recommended static security protections for the platform is checked.
  * @retval None
  */
void SECURITY_CheckStaticProtections(void)
{
  hal_flash_t flash = mx_rot_flash_gethandle()->instance;
  uint32_t ob_value = 0U;
  uint32_t i = 0U;
  uint32_t lifecycle_idx = 0U;
  uint32_t ob_start_page = 0U;
  uint32_t ob_end_page   = 0U;
  uint32_t ob_page_nbr   = 0U;
  uint32_t expected = 0U;
  (void)i;

  SECURITY_PROTECTION_LOG("Checking Option Bytes static security protections:");

#if defined(OEMIROT_OB_WRP_CHECK)
  /* Check OB write protection */
  for (i = WRP_CFG_START; i <= WRP_CFG_END; i++)
  {
    if (HAL_FLASH_ITF_OB_IsEnabledPageWRP(flash, HAL_FLASH_BANK_1, i) != HAL_FLASH_ITF_OB_WRP_PAGE_PROTECTED)
    {
      ROT_LOG_ERR("* wrp1 KO: wrp missing on page %" PRIu32, i);
      Error_Handler();
    }
  }
  SECURITY_PROTECTION_LOG("- wrp1 OK [start: 0x%" PRIx32 ", end: 0x%" PRIx32 "]",
                          (uint32_t)WRP_CFG_START,
                          (uint32_t)WRP_CFG_END);

#endif /* OEMIROT_OB_WRP_CHECK */

  /* Check OB hide protection */
  HAL_FLASH_ITF_OB_GetHDPArea(flash, HAL_FLASH_BANK_1, &ob_start_page, &ob_page_nbr);
  ob_end_page = ob_start_page + ob_page_nbr - 1U;

  if ((ob_start_page != (uint32_t)HDP_CFG_START) || (ob_end_page != (uint32_t)HDP_CFG_END))
  {
    ROT_LOG_ERR("* hdp1 KO: expected [start: 0x%" PRIx32 ", end: 0x%" PRIx32
                "], OB [start: 0x%" PRIx32 ", end: 0x%" PRIx32 "]",
                (uint32_t)HDP_CFG_START,
                (uint32_t)HDP_CFG_END,
                ob_start_page,
                ob_end_page);
    Error_Handler();
  }
  SECURITY_PROTECTION_LOG("- hdp1 OK [start: 0x%" PRIx32 ", end: 0x%" PRIx32 "]",
                          (uint32_t)HDP_CFG_START, (uint32_t)HDP_CFG_END);

  /* Check product_state : boot if current product_state is greater or equal to selected product_state */
  expected = (uint32_t)OEMIROT_OB_PRODUCT_STATE_MIN;
  /* Identify product_state mini selected */
  for (lifecycle_idx = 0U; lifecycle_idx < NB_PRODUCT_STATE; lifecycle_idx++)
  {
    if (ProductStatePrioList[lifecycle_idx] == expected)
    {
      break;
    }
  }
  if (lifecycle_idx >= NB_PRODUCT_STATE)
  {
    Error_Handler();
  }
  /* Control if current product_state is allowed */
  ob_value = RSSLIB_PFUNC->GetProductState();
  for (; lifecycle_idx < NB_PRODUCT_STATE; lifecycle_idx++)
  {
    if (ProductStatePrioList[lifecycle_idx] == ob_value)
    {
      break;
    }
  }
  if (lifecycle_idx >= NB_PRODUCT_STATE)
  {
    ROT_LOG_ERR("* product_state KO: minimum expected [0x%" PRIx32 "], OB [0x%" PRIx32 "]",
                expected,
                ob_value);
    Error_Handler();
  }
  SECURITY_PROTECTION_LOG("- product_state OK [0x%" PRIx32 "]", (uint32_t)ProductStatePrioList[lifecycle_idx]);
}

/* Private function definitions ----------------------------------------------*/

/**
  * @brief  Disable and reset the cryptography clocks.
  * @param  None
  * @retval None
  */
static void crypto_reset_clocks(void)
{
  /* -1- Disable the clock of all the used Crypto IPs */
  HAL_RCC_RNG_DisableClock();
  HAL_RCC_HASH_DisableClock();

  /* -2- Reset all the used Crypto IPs */
  HAL_RCC_RNG_Reset();
  HAL_RCC_HASH_Reset();
}

/**
  * @brief  Mpu initial configuration for OEMiRoT execution.
  * @param  None
  * @note   The MPU is configured at the beginning of OEMiRoT execution,
  *         to protect the OEMiRoT code and data, and forbid execution outside of OEMiRoT code area.
  *         The MPU configuration is checked later in the execution to ensure it has not been modified.
  * @retval None
  */
static void mpu_init_cfg(void)
{
#if defined(OEMIROT_MPU_ENABLE)
  hal_cortex_mpu_region_config_t read_region_config = {0U};
  uint32_t i = 0U;
  uint32_t privdefena_bit = 0U;
  uint32_t hfnmien_bit = 0U;
  hal_cortex_mpu_status_t mpu_enabled = HAL_CORTEX_MPU_DISABLED;

  SECURITY_PROTECTION_LOG("- mpu");

  /* Configuration stage */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* Configure MPU regions */
    for (i = 0U; i < ARRAY_SIZE(mpu_regions_cfg_init); i++)
    {
      /* Configure the MPU region */
      if (HAL_CORTEX_MPU_SetConfigRegion(mpu_regions_cfg_init[i].region_idx,
                                         &(mpu_regions_cfg_init[i].region_config)) != HAL_OK)
      {
        Error_Handler();
      }

      /* Enable the MPU region */
      HAL_CORTEX_MPU_EnableRegion(mpu_regions_cfg_init[i].region_idx);

      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, mpu_regions_cfg_init[i].flow_step_enable,
                        mpu_regions_cfg_init[i].flow_ctrl_enable);
    }

    /* Configure overall MPU (including during HF/NMI handlers, and without background region) */
    HAL_CORTEX_MPU_Enable(HAL_CORTEX_MPU_HARDFAULT_NMI_ENABLE, HAL_CORTEX_MPU_ACCESS_FAULT_ALL);

    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_MPU_I_EN, FLOW_CTRL_MPU_I_EN);
  }
  /* Verification stage */
  else
  {
    /* Verify MPU regions */
    for (i = 0U; i < ARRAY_SIZE(mpu_regions_cfg_init); i++)
    {
      /* Get configuration of the MPU region */
      HAL_CORTEX_MPU_GetConfigRegion(mpu_regions_cfg_init[i].region_idx, &read_region_config);

      /* Verify MPU region configuration */
      if ((read_region_config.base_addr != mpu_regions_cfg_init[i].region_config.base_addr)
          || (read_region_config.size != mpu_regions_cfg_init[i].region_config.size)
          || (read_region_config.access_attr != mpu_regions_cfg_init[i].region_config.access_attr)
          || (read_region_config.mem_attr != mpu_regions_cfg_init[i].region_config.mem_attr)
          || (read_region_config.exec_attr != mpu_regions_cfg_init[i].region_config.exec_attr)
          || (read_region_config.sub_region != mpu_regions_cfg_init[i].region_config.sub_region))
      {
        Error_Handler();
      }

      /* Verify MPU region is enabled */
      if (HAL_CORTEX_MPU_IsEnabledRegion(mpu_regions_cfg_init[i].region_idx) != HAL_CORTEX_MPU_REGION_ENABLED)
      {
        Error_Handler();
      }

      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, mpu_regions_cfg_init[i].flow_step_check,
                        mpu_regions_cfg_init[i].flow_ctrl_check);
    }

    /* Verify MPU overall configuration */
    privdefena_bit = STM32_READ_BIT(MPU->CTRL, MPU_CTRL_PRIVDEFENA_Msk);
    hfnmien_bit = STM32_READ_BIT(MPU->CTRL, MPU_CTRL_HFNMIENA_Msk);
    mpu_enabled = HAL_CORTEX_MPU_IsEnabled();

    if ((privdefena_bit != (uint32_t)HAL_CORTEX_MPU_ACCESS_FAULT_ALL)
        || (hfnmien_bit != (uint32_t)HAL_CORTEX_MPU_HARDFAULT_NMI_ENABLE)
        || (mpu_enabled != HAL_CORTEX_MPU_ENABLED))
    {
      Error_Handler();
    }

    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_MPU_I_CH, FLOW_CTRL_MPU_I_CH);
  }
#endif /* OEMIROT_MPU_ENABLE */
}

/**
  * @brief  Configure RAM with ECC and enable ECC interrupt if supported.
  * @param  None
  * @retval None
  */
static void ram_init_cfg(void)
{
}

/**
  * @brief  Mpu config update for jump to application.
  * @param  None
  * @note   The MPU configuration is updated before jumping to application,
  *         to set the appropriate permissions for the application execution
  *         (ex: allow execution and read/write access on application area,
  *         forbid execution and allow read/write access on data area, etc.).
  * @retval None
  */
static void mpu_appli_cfg(void)
{
#if defined(OEMIROT_MPU_ENABLE)
  hal_cortex_mpu_region_config_t read_region_config = {0U};
  uint32_t i = 0U;

  /* Configuration stage */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* Reconfigure MPU regions */
    for (i = 0U; i < ARRAY_SIZE(mpu_regions_cfg_appli); i++)
    {
      /* Configure the MPU region */
      if (HAL_CORTEX_MPU_SetConfigRegion(mpu_regions_cfg_appli[i].region_idx,
                                         &(mpu_regions_cfg_appli[i].region_config)) != HAL_OK)
      {
        Error_Handler();
      }

#if (SECURITY_APP_MPU_REGION_COUNTER > 1)
      /* Enable the MPU region except if the first one in the table */
      if (i != 0U)
      {
        HAL_CORTEX_MPU_EnableRegion(mpu_regions_cfg_appli[i].region_idx);
      }
#endif /* (SECURITY_APP_MPU_REGION_COUNTER > 1) */

      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, mpu_regions_cfg_appli[i].flow_step_enable,
                        mpu_regions_cfg_appli[i].flow_ctrl_enable);
    }
  }
  /* Verification stage */
  else
  {
    /* Verify MPU regions */
    for (i = 0U; i < ARRAY_SIZE(mpu_regions_cfg_appli); i++)
    {
      /* Get configuration of the MPU region */
      HAL_CORTEX_MPU_GetConfigRegion(mpu_regions_cfg_appli[i].region_idx, &read_region_config);

      /* Verify MPU region configuration */
      if ((read_region_config.base_addr != mpu_regions_cfg_appli[i].region_config.base_addr)
          || (read_region_config.size != mpu_regions_cfg_appli[i].region_config.size)
          || (read_region_config.access_attr != mpu_regions_cfg_appli[i].region_config.access_attr)
          || (read_region_config.mem_attr != mpu_regions_cfg_appli[i].region_config.mem_attr)
          || (read_region_config.exec_attr != mpu_regions_cfg_appli[i].region_config.exec_attr)
          || (read_region_config.sub_region != mpu_regions_cfg_appli[i].region_config.sub_region))
      {
        Error_Handler();
      }

#if (SECURITY_APP_MPU_REGION_COUNTER > 1)
      if (i != 0U)
      {
        /* Verify the MPU region is enabled, if not the first one in the table */
        if (HAL_CORTEX_MPU_IsEnabledRegion(mpu_regions_cfg_appli[i].region_idx) != HAL_CORTEX_MPU_REGION_ENABLED)
        {
          Error_Handler();
        }
      }
      else
#endif /* (SECURITY_APP_MPU_REGION_COUNTER > 1) */
      {
        /* Verify the MPU region is disabled, if the first one in the table */
        if (HAL_CORTEX_MPU_IsEnabledRegion(mpu_regions_cfg_appli[i].region_idx) != HAL_CORTEX_MPU_REGION_DISABLED)
        {
          Error_Handler();
        }
      }

      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, mpu_regions_cfg_appli[i].flow_step_check,
                        mpu_regions_cfg_appli[i].flow_ctrl_check);
    }
  }
#endif /* OEMIROT_MPU_ENABLE */
}

/**
  * @brief  Configure the tamper detection.
  * @param  None
  * @retval None
  */
static void tamper_init_cfg(void)
{
#if defined(OEMIROT_TAMPER_ENABLE)
  uint32_t is_tamp_enabled = 0U;
  uint32_t is_it_enabled = 0U;
  uint32_t config_internal_tampers = 0U;

  SECURITY_PROTECTION_LOG("- tamper");

  /* configuration stage */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* TAMP Init */
    if (mx_rot_tamp_init() != SYSTEM_OK)
    {
      Error_Handler();
    }

    /* Enable access to tamper registers */
    HAL_PWR_DisableRTCDomainWriteProtection();

    /*  Internal Tamper activation  */
    if (HAL_TAMP_INTERNAL_SetConfigTampers(TAMP_INTERNAL_TAMPER, &IndivInternalTamperConf) != HAL_OK)
    {
      Error_Handler();
    }
    if (HAL_TAMP_INTERNAL_Start(TAMP_INTERNAL_TAMPER, TAMP_INTERNAL_IT_TAMPER) != HAL_OK)
    {
      Error_Handler();
    }
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_TAMP_INT_EN, FLOW_CTRL_TAMP_INT_EN);

    /*  Set tamper configuration privileged only  */
    if (HAL_TAMP_SetPrivAttr(HAL_TAMP_PRIV_ITEM_TAMP, HAL_TAMP_PRIV) != HAL_OK)
    {
      Error_Handler();
    }
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_TAMP_PRIV_EN, FLOW_CTRL_TAMP_PRIV_EN);

    /*  Activate Secret Erase  */
    if (HAL_TAMP_EnableResourceProtection(OEMIROT_TAMPER_RESOURCES) != HAL_OK)
    {
      Error_Handler();
    }
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_TAMP_CFG_EN, FLOW_CTRL_TAMP_CFG_EN);
  }
  /* verification stage */
  else
  {
    /*  Check Internal Tamper activation */
    is_tamp_enabled = LL_TAMP_GetEnabled(TAMP_INTERNAL_TAMPER);
    is_it_enabled = LL_TAMP_IsEnabledIT(TAMP_INTERNAL_IT_TAMPER);
    config_internal_tampers = LL_TAMP_GetConfigInternalTampers(TAMP_ITAMP_NOERASE_TAMPER);

    if ((is_tamp_enabled != TAMP_INTERNAL_TAMPER)
        || (is_it_enabled != 1U)
        || (config_internal_tampers != 0x0U))
    {
      Error_Handler();
    }
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_TAMP_INT_CH, FLOW_CTRL_TAMP_INT_CH);

    /*  Check tamper configuration privileged only   */
    if (HAL_TAMP_GetPrivAttr(HAL_TAMP_PRIV_ITEM_TAMP) != HAL_TAMP_PRIV)
    {
      Error_Handler();
    }
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_TAMP_PRIV_CH, FLOW_CTRL_TAMP_PRIV_CH);

    /*  Check Secret Erase */
    if (HAL_TAMP_IsEnabledResourceProtection(OEMIROT_TAMPER_RESOURCES) != HAL_TAMP_PROTECT_RESOURCES_ENABLED)
    {
      Error_Handler();
    }
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_TAMP_CFG_CH, FLOW_CTRL_TAMP_CFG_CH);
  }
#endif /* OEMIROT_TAMPER_ENABLE */
}

/**
  * @brief  Disable NMI on double ECC flash error during OEMiRoT execution.
  * @param  None
  * @note   It avoids blocking the device in case of double ECC error during boot execution.
  *         The NMI is re-enabled on double ECC error for jump to application, to allow the
  *         device to reset in case of double ECC error during application execution.
  *         This is done in flash_ecc_appli_cfg() function.
  * @retval None
  */
static void flash_ecc_init_cfg(void)
{
  {
    /* configuration stage
    =================== */
    if (uFlowStage == FLOW_STAGE_CFG)
    {
      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_ECC_I_EN, FLOW_CTRL_FLASH_ECC_I_EN);
    }
    /* verification stage
    ================== */
    else
    {
      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_ECC_I_CH, FLOW_CTRL_FLASH_ECC_I_CH);
    }
  }

}

/**
  * @brief  Enable back NMI on double ECC flash error for jump to application.
  * @param  None
  * @retval None
  */
static void flash_ecc_appli_cfg(void)
{
  {
    /* configuration stage
    =================== */
    if (uFlowStage == FLOW_STAGE_CFG)
    {
      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_ECC_A_EN, FLOW_CTRL_FLASH_ECC_A_EN);
    }
    /* verification stage
    ================== */
    else
    {
      /* Execution stopped if flow control failed */
      FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_ECC_A_CH, FLOW_CTRL_FLASH_ECC_A_CH);
    }
  }
}

/**
  * @brief  Clear tamper flags and pending IRQ in case of tamper detection during boot.
  * @param  None
  * @note   This function is called when a tamper event is detected during the early startup
  *         (or when the device was in sleep mode and woke up on tamper event).
  *         It clears the tamper flags and pending IRQ to allow the device to boot.
  * @retval None
  */
static void tamper_clear_flags(void)
{
  /* Clear ITAMP and TAMP flags */
  LL_TAMP_ClearFlag_ITAMP(LL_TAMP_ITAMP_ALL);
  LL_TAMP_ClearFlag_TAMP(LL_TAMP_ALL);
  (void)LL_TAMP_IsActiveFlag_ITAMP(LL_TAMP_ITAMP_ALL); /* Dummy read to wait for write effectiveness */
  HAL_CORTEX_NVIC_ClearPendingIRQ(TAMP_IRQn);

  Error_Handler();
}

/**
  * @brief  Configure flash access.
  * @param  None
  * @retval None
  */
static void flash_init_cfg(void)
{
  /* configuration stage
  =================== */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_I_EN_B1 ^ FLOW_STEP_FLASH_I_EN_B2, FLOW_CTRL_FLASH_I_EN_B2);
  }
  /* verification stage
  ================== */
  else
  {
    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_I_CH_B1 ^ FLOW_STEP_FLASH_I_CH_B2, FLOW_CTRL_FLASH_I_CH_B2);
  }
}

/**
  * @brief  Configure flash access.
  * @param  None
  * @retval None
  */
static void flash_appli_cfg(void)
{
  /* configuration stage
  =================== */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_A_EN_B1 ^ FLOW_STEP_FLASH_A_EN_B2, FLOW_CTRL_FLASH_A_EN_B2);
  }
  /* verification stage
  ================== */
  else
  {
    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_FLASH_A_CH_B1 ^ FLOW_STEP_FLASH_A_CH_B2, FLOW_CTRL_FLASH_A_CH_B2);
  }
}

/**
  * @brief  Cache init.
  * @param  None
  * @retval None
  */
static void cache_init_cfg(void)
{
  /* configuration stage
  =================== */
  if (uFlowStage == FLOW_STAGE_CFG)
  {
    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_CACHE_LOCK_I_EN, FLOW_CTRL_CACHE_LOCK_I_EN);
  }
  /* verification stage
  ================== */
  else
  {
    /* Execution stopped if flow control failed */
    FLOW_CONTROL_STEP(uFlowProtectValue, FLOW_STEP_CACHE_LOCK_I_CH, FLOW_CTRL_CACHE_LOCK_I_CH);
  }
}
