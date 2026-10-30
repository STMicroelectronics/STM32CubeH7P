/**
  ******************************************************************************
  * @file    low_level_security_config.h
  * @brief   Config header for low_level_security.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOW_LEVEL_SECURITY_CONFIG_H
#define LOW_LEVEL_SECURITY_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief MPU configuration structure definition
  */
typedef struct
{
  hal_cortex_mpu_region_idx_t region_idx;       /*!< MPU Region Index */
  hal_cortex_mpu_region_config_t region_config; /*!< MPU Region Configuration */
#if defined(OEMIROT_FLOW_CONTROL)
  uint32_t flow_step_enable;                    /*!< Flow control step (configuration stage) */
  uint32_t flow_ctrl_enable;                    /*!< Flow control (configuration stage) */
  uint32_t flow_step_check;                     /*!< Flow control step (verification stage)  */
  uint32_t flow_ctrl_check;                     /*!< Flow control (verification stage) */
#endif /* OEMIROT_FLOW_CONTROL */
} oemirot_mpu_init_t;

#define LAST_PAGE_IN_BANK                         ((BANK_SIZE - 1) / PAGE_SIZE)
#define LAST_HDP_BLOCK_IN_BANK                    ((BANK_SIZE - 1) / HDP_BLOCK_SIZE)

/* MPU configuration
  ================== */

/* Initial MPU configuration for OEMiRoT execution */
static const oemirot_mpu_init_t mpu_regions_cfg_init[] =
{
  /* Region 0: Allows RW access to peripherals */
  {
    HAL_CORTEX_MPU_REGION_0,
    {
      PERIPH_START,
      HAL_CORTEX_MPU_REGION_SIZE_512MB,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW,
      HAL_CORTEX_MPU_DEVICE_MEM_SHAREABLE,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      0x00U
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R0,
    FLOW_CTRL_MPU_I_EN_R0,
    FLOW_STEP_MPU_I_CH_R0,
    FLOW_CTRL_MPU_I_CH_R0
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 1: Allows RW access to all user flash by default (Not cacheable) */
  {
    HAL_CORTEX_MPU_REGION_1,
    {
      FLASH_BASE,
      HAL_CORTEX_MPU_REGION_SIZE_2MB,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_NCACHEABLE,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      0x00U
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R1,
    FLOW_CTRL_MPU_I_EN_R1,
    FLOW_STEP_MPU_I_CH_R1,
    FLOW_CTRL_MPU_I_CH_R1
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 6: Allows execution to ROT code */
  {
    HAL_CORTEX_MPU_REGION_6,
    {
      ROT_MPU_ADDR,
      ROT_MPU_SIZE,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE,
      ROT_MPU_SUB_REGION
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R6,
    FLOW_CTRL_MPU_I_EN_R6,
    FLOW_STEP_MPU_I_CH_R6,
    FLOW_CTRL_MPU_I_CH_R6
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 7: Allows RW access to all SRAM */
  {
    HAL_CORTEX_MPU_REGION_7,
    {
      SRAM_START,
      HAL_CORTEX_MPU_REGION_SIZE_512MB,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WB_RWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      0x00U
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R7,
    FLOW_CTRL_MPU_I_EN_R7,
    FLOW_STEP_MPU_I_CH_R7,
    FLOW_CTRL_MPU_I_CH_R7
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 8: Allows RO access to RO */
  {
    HAL_CORTEX_MPU_REGION_8,
    {
      RO_AND_SYSTEM_MEM_START,
      HAL_CORTEX_MPU_REGION_SIZE_2KB,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_NCACHEABLE,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      0x00U
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R8,
    FLOW_CTRL_MPU_I_EN_R8,
    FLOW_STEP_MPU_I_CH_R8,
    FLOW_CTRL_MPU_I_CH_R8
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 9: Allows RO access to System Memory */
  {
    HAL_CORTEX_MPU_REGION_9,
    {
      SYSTEM_FLASH_BASE,
      HAL_CORTEX_MPU_REGION_SIZE_128KB,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_NCACHEABLE,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      0x00U
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R9,
    FLOW_CTRL_MPU_I_EN_R9,
    FLOW_STEP_MPU_I_CH_R9,
    FLOW_CTRL_MPU_I_CH_R9
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 10: Allows execution of RSSLIB */
  {
    HAL_CORTEX_MPU_REGION_10,
    {
      RSSLIB_START,
      HAL_CORTEX_MPU_REGION_SIZE_8KB,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE,
      0x00U
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_I_EN_R10,
    FLOW_CTRL_MPU_I_EN_R10,
    FLOW_STEP_MPU_I_CH_R10,
    FLOW_CTRL_MPU_I_CH_R10
#endif /* OEMIROT_FLOW_CONTROL */
  }
};

/* Updated MPU configuration for jump to application.
   First MPU region in this list will be configured only at this stage,
   this region will be enabled later by RSSlib service, after having closed
   HDP area (containing RoT code/data area).
   Following regions in this list are configured and directly enabled. */
#define SECURITY_APP_MPU_REGION_COUNTER (5U)
static const oemirot_mpu_init_t mpu_regions_cfg_appli[SECURITY_APP_MPU_REGION_COUNTER] =
{
  /* Region 1: Allows execution of the next stage application (1/5) */
  {
    HAL_CORTEX_MPU_REGION_1,
    {
      APP_MPU_MAIN_ADDR,
      APP_MPU_MAIN_SIZE,
      HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE,
      APP_MPU_MAIN_SUB_REGION
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_A_EN_R1,
    FLOW_CTRL_MPU_A_EN_R1,
    FLOW_STEP_MPU_A_CH_R1,
    FLOW_CTRL_MPU_A_CH_R1
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 2: Allows execution of the next stage application (2/5) */
  {
    HAL_CORTEX_MPU_REGION_2,
    {
      APP_MPU_START_ALIGN_L1_ADDR,
      APP_MPU_START_ALIGN_L1_SIZE,
      HAL_CORTEX_MPU_REGION_ALL_RW_FAULT,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      APP_MPU_START_ALIGN_L1_SUB_REGION
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_A_EN_R2,
    FLOW_CTRL_MPU_A_EN_R2,
    FLOW_STEP_MPU_A_CH_R2,
    FLOW_CTRL_MPU_A_CH_R2
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 3: Allows execution of the next stage application (3/5) */
  {
    HAL_CORTEX_MPU_REGION_3,
    {
      APP_MPU_START_ALIGN_L2_ADDR,
      APP_MPU_START_ALIGN_L2_SIZE,
      HAL_CORTEX_MPU_REGION_ALL_RW_FAULT,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      APP_MPU_START_ALIGN_L2_SUB_REGION
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_A_EN_R3,
    FLOW_CTRL_MPU_A_EN_R3,
    FLOW_STEP_MPU_A_CH_R3,
    FLOW_CTRL_MPU_A_CH_R3
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 4: Allows execution of the next stage application (4/5) */
  {
    HAL_CORTEX_MPU_REGION_4,
    {
      APP_MPU_END_ALIGN_L1_ADDR,
      APP_MPU_END_ALIGN_L1_SIZE,
      HAL_CORTEX_MPU_REGION_ALL_RW_FAULT,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      APP_MPU_END_ALIGN_L1_SUB_REGION
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_A_EN_R4,
    FLOW_CTRL_MPU_A_EN_R4,
    FLOW_STEP_MPU_A_CH_R4,
    FLOW_CTRL_MPU_A_CH_R4
#endif /* OEMIROT_FLOW_CONTROL */
  },
  /* Region 5: Allows execution of the next stage application (5/5) */
  {
    HAL_CORTEX_MPU_REGION_5,
    {
      APP_MPU_END_ALIGN_L2_ADDR,
      APP_MPU_END_ALIGN_L2_SIZE,
      HAL_CORTEX_MPU_REGION_ALL_RW_FAULT,
      HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA,
      HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE,
      APP_MPU_END_ALIGN_L2_SUB_REGION
    },
#if defined(OEMIROT_FLOW_CONTROL)
    FLOW_STEP_MPU_A_EN_R5,
    FLOW_CTRL_MPU_A_EN_R5,
    FLOW_STEP_MPU_A_CH_R5,
    FLOW_CTRL_MPU_A_CH_R5
#endif /* OEMIROT_FLOW_CONTROL */
  }
};

/* product_state control
   ===================== */
typedef enum
{
  OEMIROT_OB_PRODUCT_STATE_OPEN         = 0x39U, /*!< OEMIROT option-bytes Product State Open         */
  OEMIROT_OB_PRODUCT_STATE_PROVISIONING = 0x17U, /*!< OEMIROT option-bytes Product State Provisioning */
  OEMIROT_OB_PRODUCT_STATE_CLOSED       = 0x72U, /*!< OEMIROT option-bytes Product State Closed       */
  OEMIROT_OB_PRODUCT_STATE_LOCKED       = 0x5CU  /*!< OEMIROT option-bytes Product State Locked       */
} oemirot_ob_product_state_t;

#define NB_PRODUCT_STATE (4U)

static const oemirot_ob_product_state_t ProductStatePrioList[NB_PRODUCT_STATE] =
{
  OEMIROT_OB_PRODUCT_STATE_OPEN,
  OEMIROT_OB_PRODUCT_STATE_PROVISIONING,
  OEMIROT_OB_PRODUCT_STATE_CLOSED,
  OEMIROT_OB_PRODUCT_STATE_LOCKED
};

/* Tamper
   ====== */
/* OEMiRoT tampers configuration begin */
/* Format the definitions for configuring supported tampers required by the HAL/LL driver */
#define TAMP_INTERNAL_TAMPER        (HAL_TAMP_INTERNAL_TAMPER_9 | HAL_TAMP_INTERNAL_TAMPER_15)
#define TAMP_INTERNAL_IT_TAMPER     (HAL_TAMP_INTERNAL_IT_TAMPER_9 | HAL_TAMP_INTERNAL_IT_TAMPER_15)
#define TAMP_ITAMP_NOERASE_TAMPER   (LL_TAMP_ITAMP_NOERASE_TAMPER9 | LL_TAMP_ITAMP_NOERASE_TAMPER15)

/* Resources protected by tamper mechanism */
#define OEMIROT_TAMPER_RESOURCES \
  ( \
    HAL_TAMP_RESOURCE_1 | \
    HAL_TAMP_RESOURCE_4  \
  )

/* OEMiRoT tampers configuration end */

#if defined(OEMIROT_TAMPER_ENABLE)
/* Configure tamper in confirmed mode: secrets are erased on a tamper fault */
static const hal_tamp_internal_individual_config_t IndivInternalTamperConf =
{
  .erase_secrets = HAL_TAMP_INTERNAL_SECRETS_ERASE
};
#endif /* OEMIROT_TAMPER_ENABLE */

#ifdef __cplusplus
}
#endif

#endif /* LOW_LEVEL_SECURITY_CONFIG_H */
