/**
  ******************************************************************************
  * @file    low_level_obkeys.c
  * @brief   Low Level Interface module to access OBK area in FLASH
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
#include <string.h>
#include "low_level_obkeys.h"
#include "low_level_flash.h"
#include "low_level_security.h"
#include "boot_hal_flowcontrol.h"
#include "boot_hal_cfg.h"
#include "flash_layout.h"
#include "region_defs.h"
#include "boot_hal_utils.h"
#include "boot_hal_legacy.h"

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls_config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif /* !MBEDTLS_CONFIG_FILE */

/* External functions --------------------------------------------------------*/
extern void Error_Handler(void);

/* Private typedef -----------------------------------------------------------*/

/**
  * Arm Flash device structure.
  */
struct arm_obk_flash_dev_s
{
  obk_low_level_device_t *dev;
  ARM_FLASH_INFO *data;       /*!< OBK FLASH memory device data */
};

/* Private defines -----------------------------------------------------------*/
#define ST_SHA256_TIMEOUT         (3U)

#define MAX_SIZE_OBK              ((OBK_HDPL1_CFG_SIZE) > (OBK_HDPL1_DATA_SIZE) ? \
                                   (OBK_HDPL1_CFG_SIZE) : (OBK_HDPL1_DATA_SIZE))

#define OBK_FLASH0_PROG_UNIT      (OBK_HDPL_KEY_SIZE)

/* Allows reading back after an OBK programming */
/* #define CHECK_PROGRAM */
/* Private variables ---------------------------------------------------------*/
static ARM_FLASH_INFO ARM_OBK_FLASH0_DEV_DATA =
{
  .sector_info    = NULL, /* unused */
  .sector_count   = 0U, /* unused */
  .sector_size    = 0U, /* unused */
  .page_size      = 0U, /* unused */
  .program_unit   = OBK_FLASH0_PROG_UNIT, /* Minimum write size in bytes */
  .erased_value   = 0U /* unused*/
};

static struct arm_obk_flash_dev_s ARM_OBK_FLASH0_DEV =
{
  .dev    = &(OBK_FLASH0_DEV),
  .data   = &(ARM_OBK_FLASH0_DEV_DATA)
};

/* Global variables ----------------------------------------------------------*/
#if defined(__ICCARM__)
#pragma location=".ram_init_ro"
#elif defined(__GNUC__)
__attribute__((section(".ram_init_ro")))
#endif /* __ICCARM__ */

obk_hdpl1_config_t OBK_Hdpl1Cfg;

/* Private function prototypes -----------------------------------------------*/
static bool is_range_valid(struct arm_obk_flash_dev_s *flash_dev, uint32_t offset);
static bool is_write_aligned(struct arm_obk_flash_dev_s *flash_dev, uint32_t param);
static bool is_write_allowed(struct arm_obk_flash_dev_s *flash_dev, uint32_t length);
static int32_t OBK_Read(uint32_t offset, void *p_data, uint32_t length);
static int32_t OBK_Write(uint32_t offset, const void *p_data, uint32_t length);
static uint32_t MemoryCompare(const uint8_t *p_add1, const uint8_t *p_add2, uint32_t size);
static hal_status_t ComputeSHA256(uint8_t *p_buffer, uint32_t length, uint8_t *p_sha256);
#if defined(CHECK_PROGRAM)
static bool MemoryIsErased(const uint8_t *p_add, uint32_t size);
#endif /* CHECK_PROGRAM */

/* Function Definitions ------------------------------------------------------*/
/**
  * @brief      Check if the Flash memory boundaries are not violated.
  * @param      flash_dev  Flash device structure \ref arm_obk_flash_dev_s
  * @param      offset     Highest Flash memory address which would be accessed.
  * @return     Returns true if Flash memory boundaries are not violated, false
  *             otherwise.
  */
static bool is_range_valid(struct arm_obk_flash_dev_s *flash_dev, uint32_t offset)
{
  ARG_UNUSED(flash_dev);

  return (offset <= OBK_HDPL1_END) ? (true) : (false);
}

/**
  * @brief  Check if the parameter is aligned to program_unit.
  * @param  flash_dev  Flash device structure \ref arm_obk_flash_dev_s
  * @param  param Any number that can be checked against the
  *               program_unit, e.g. Flash memory address or
  *               data length in bytes.
  * @retval Returns true if param is aligned to program_unit, false
  *         otherwise.
  */
static bool is_write_aligned(struct arm_obk_flash_dev_s *flash_dev, uint32_t param)
{
  return ((param % flash_dev->data->program_unit) != 0U) ? (false) : (true);
}

/**
  * @brief  Control if the length is a multiple of program_unit.
  * @param  flash_dev  Flash device structure \ref arm_obk_flash_dev_s
  * @param  length Number of bytes (multiple of program_unit)
  * @retval Returns true if length is a multiple of program_unit, false
  *         otherwise.
  */
static bool is_write_allowed(struct arm_obk_flash_dev_s *flash_dev, uint32_t length)
{
  return ((length % flash_dev->data->program_unit) != 0U) ? (false) : (true);
}

/**
  * @brief  Memory compare with constant time execution.
  * @param  p_add1 Address of the first buffer to compare
  * @param  p_add2 Address of the second buffer to compare
  * @param  size Size of the comparison
  * @note   Objective is to avoid basic attacks based on time execution
  * @retval 0 if equal, another value otherwise.
  */
static uint32_t MemoryCompare(const uint8_t *p_add1, const uint8_t *p_add2, uint32_t size)
{
  uint8_t result = 0x00U;
  uint32_t i = 0U;

  for (i = 0U; i < size; i++)
  {
    result |= p_add1[i] ^ p_add2[i];
  }
  return result;
}

/**
  * @brief  Verify that the memory is erased.
  * @param  p_add Address of the buffer to verify
  * @param  size Size of the comparison
  * @retval true if erased, false otherwise.
  */
#if defined(CHECK_PROGRAM)
static bool MemoryIsErased(const uint8_t *p_add, uint32_t size)
{
  uint8_t erased_pattern = UINT8_MAX;
  uint32_t i = 0U;

  for (i = 0U; i < size; i++)
  {
    if (*(p_add + i) != erased_pattern)
    {
      return false;
    }
  }
  return true;
}
#endif /* CHECK_PROGRAM */

/**
  * @brief  Read non-encrypted OBkeys.
  * @param  offset Offset in the OBKeys area (aligned on 16 bytes)
  * @param  p_data Data buffer to be filled (aligned on 16 bytes)
  * @param  length Number of bytes (multiple of 16 bytes)
  * @retval ARM_DRIVER error status
  */
static int32_t OBK_Read(uint32_t offset, void *p_data, uint32_t length)
{
  uint8_t *p_destination = (uint8_t *) p_data;
  hal_flash_handle_t *p_hflash = mx_rot_flash_gethandle();
  hal_flash_t p_flash = HAL_FLASH_GetInstance(p_hflash);
  hal_flash_itf_ob_obk_t read_key;
  uint32_t key_index = offset / OBK_HDPL_KEY_SIZE;

  /* Check parameters */
  if ((is_range_valid(&ARM_OBK_FLASH0_DEV, offset + length - 1U) != true)
      || (is_write_aligned(&ARM_OBK_FLASH0_DEV, offset) != true)
      || (is_write_allowed(&ARM_OBK_FLASH0_DEV, length) != true)
      || (length > MAX_SIZE_OBK))
  {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  (void) HAL_FLASH_ITF_Unlock(p_flash);
  (void) HAL_FLASH_ITF_OB_Unlock(p_flash);

  while (p_destination < ((uint8_t *)p_data + length))
  {
    if (key_index >= OBK_HDPL_KEY_NBR)
    {
      return ARM_DRIVER_ERROR_SPECIFIC;
    }
    if (HAL_FLASH_ITF_OB_ReadKey(p_flash,
                                 HAL_FLASH_ITF_OBK_HDPL_0,
                                 key_index,
                                 &read_key) != HAL_OK)
    {
      return ARM_DRIVER_ERROR_SPECIFIC;
    }
    memcpy(p_destination, &read_key, OBK_HDPL_KEY_SIZE);

    key_index++;
    p_destination += OBK_HDPL_KEY_SIZE;
  }

  (void) HAL_FLASH_ITF_OB_Lock(p_flash);
  (void) HAL_FLASH_ITF_Lock(p_flash);

  return ARM_DRIVER_OK;
}

/**
  * @brief  Write non-encrypted OBkeys.
  * @param  offset Offset in the OBKeys area (aligned on 16 bytes)
  * @param  p_data Data buffer to be written non-encrypted (aligned on 16 bytes)
  * @param  length Number of bytes (multiple of 16 bytes)
  * @retval ARM_DRIVER error status
  */
static int32_t OBK_Write(uint32_t offset, const void *p_data, uint32_t length)
{
#if defined(CHECK_PROGRAM)
  uint8_t p_written_data[MAX_SIZE_OBK] = {0U};
  hal_flash_itf_ob_obk_t written_key;
#endif /* CHECK_PROGRAM */
  uint8_t *p_source = (uint8_t *) p_data;
  hal_flash_itf_ob_obk_t key_to_write;
  uint32_t key_index = offset / OBK_HDPL_KEY_SIZE;
  uint32_t start_key_index = offset / OBK_HDPL_KEY_SIZE;
  uint32_t end_key_index = (offset + length) / OBK_HDPL_KEY_SIZE;
  uint32_t keys_to_erase = 0x0U;
  hal_flash_handle_t *p_hflash = mx_rot_flash_gethandle();
  hal_flash_t p_flash = HAL_FLASH_GetInstance(p_hflash);

  /* Check parameters */
  if ((is_range_valid(&ARM_OBK_FLASH0_DEV, offset + length - 1U) != true)
      || (is_write_aligned(&ARM_OBK_FLASH0_DEV, offset) != true)
      || (is_write_allowed(&ARM_OBK_FLASH0_DEV, length) != true)
      || (length > MAX_SIZE_OBK))
  {
    return ARM_DRIVER_ERROR_PARAMETER;
  }

  /* Unlock FLASH area */
  (void) HAL_FLASH_ITF_Unlock(p_flash);
  (void) HAL_FLASH_ITF_OB_Unlock(p_flash);

  /* Build the bit field to erase the keys */
  for (key_index = start_key_index; key_index < end_key_index; key_index ++)
  {
    keys_to_erase |= (HAL_FLASH_OBK_KEY_0 << key_index);
  }

  /* Erase OBKeys */
  if (HAL_FLASH_ITF_OB_EraseKey(p_flash, HAL_FLASH_ITF_OBK_HDPL_0, keys_to_erase) != HAL_OK)
  {
    return ARM_DRIVER_ERROR_SPECIFIC;
  }

#if defined(CHECK_PROGRAM)
  for (key_index = start_key_index; key_index < end_key_index; key_index ++)
  {
    /* Verify that the erased words are all 0xFFFFFFFF */
    if (HAL_FLASH_ITF_OB_ReadKey(p_flash,
                                 HAL_FLASH_ITF_OBK_HDPL_0,
                                 key_index,
                                 &written_key) != HAL_OK)
    {
      return ARM_DRIVER_ERROR_SPECIFIC;
    }

    if (MemoryIsErased((uint8_t *)written_key, OBK_HDPL_KEY_SIZE) != true)
    {
      ROT_LOG_ERR("The FLASH OBK %d isn't erased", key_index);
      return ARM_DRIVER_ERROR_SPECIFIC;
    }
  }
#endif /* CHECK_PROGRAM */

  for (key_index = start_key_index; key_index < end_key_index; key_index ++)
  {
    if (p_source >= ((uint8_t *)p_data + length))
    {
      return ARM_DRIVER_ERROR_SPECIFIC;
    }

    /* Program OBKeys */
    memcpy(&key_to_write, p_source, OBK_HDPL_KEY_SIZE);
    if (HAL_FLASH_ITF_OB_ProgramKey(p_flash,
                                    HAL_FLASH_ITF_OBK_HDPL_0,
                                    key_index,
                                    &key_to_write) != HAL_OK)
    {
      return ARM_DRIVER_ERROR_SPECIFIC;
    }

#if defined(CHECK_PROGRAM)
    /* Verify that the programmed data matches the expected values */
    if (HAL_FLASH_ITF_OB_ReadKey(p_flash,
                                 HAL_FLASH_ITF_OBK_HDPL_0,
                                 key_index,
                                 &written_key) != HAL_OK)
    {
      ROT_LOG_ERR("The programmed FLASH OBK %d couldn't be read", key_index);
      return ARM_DRIVER_ERROR_SPECIFIC;
    }
    if (MemoryCompare((uint8_t *)destination, (uint8_t *)p_written_data, length) != 0U)
    {
      ROT_LOG_ERR("The FLASH OBK programming index %d failed", key_index);
      return ARM_DRIVER_ERROR_SPECIFIC;
    }
#endif /* CHECK_PROGRAM */

    p_source += OBK_HDPL_KEY_SIZE;
  }

  /* Check there were no issue */
  if (p_source < ((uint8_t *)p_data + length))
  {
    return ARM_DRIVER_ERROR_SPECIFIC;
  }

  /* Lock the User Flash area */
  (void) HAL_FLASH_ITF_OB_Lock(p_flash);
  (void) HAL_FLASH_ITF_Lock(p_flash);

  return ARM_DRIVER_OK;
}

/**
  * @brief  Compute SHA256.
  * @param  p_buffer pointer to the input buffer to be hashed
  * @param  length length of the input buffer in bytes
  * @param  p_sha256 pointer to the computed digest
  * @retval HAL error status
  */
static hal_status_t ComputeSHA256(uint8_t *p_buffer, uint32_t length, uint8_t *p_sha256)
{
  hal_hash_handle_t *p_hash;
  hal_hash_config_t hash_config;
  uint32_t computed_size = 0U;

  /* Get hash handle */
  p_hash = mx_rot_hash_gethandle();

  hash_config.algorithm = HAL_HASH_ALGO_SHA256;
  hash_config.data_swapping = HAL_HASH_DATA_SWAP_BYTE;
  if (HAL_HASH_SetConfig(p_hash, &hash_config) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* HASH computation */
  if (HAL_HASH_Compute(p_hash,
                       p_buffer,
                       length,
                       p_sha256,
                       SHA256_LENGTH,
                       &computed_size,
                       ST_SHA256_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}

/* Public Function Definitions ------------------------------------------------------*/

/**
  * @brief  Read data in OBkeys HDPL1.
  * @param  p_obk_hdpl1_data pointer on HDPL1 data
  * @retval HAL error status
  */
hal_status_t OBK_ReadHdpl1Data(obk_hdpl1_data_t *p_obk_hdpl1_data)
{
  uint8_t sha256[SHA256_LENGTH] = { 0U };
  uint32_t address = (uint32_t) p_obk_hdpl1_data;

  /* Read configuration in OBKeys */
  if (OBK_Read(OBK_HDPL1_DATA_OFFSET,
               (void *) p_obk_hdpl1_data,
               sizeof(obk_hdpl1_data_t)) != ARM_DRIVER_OK)
  {
    return HAL_ERROR;
  }

  /* Verify SHA256 on the whole HDPL1 data except first 32 bytes of SHA256 */
  if (ComputeSHA256((uint8_t *)(address + SHA256_LENGTH),
                    sizeof(obk_hdpl1_data_t) - SHA256_LENGTH,
                    sha256) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if (MemoryCompare(p_obk_hdpl1_data->SHA256, sha256, SHA256_LENGTH) != 0U)
  {
    ROT_LOG_ERR("Wrong OBK HDPL1 data");
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Update data in OBkeys HDPL1.
  * @param  p_obk_hdpl1_data pointer on HDPL1 data
  * @retval HAL error status
  */
hal_status_t OBK_UpdateHdpl1Data(obk_hdpl1_data_t *p_obk_hdpl1_data)
{
  uint8_t sha256[SHA256_LENGTH] = { 0U };
  uint32_t address = (uint32_t) p_obk_hdpl1_data;

  /* Verify SHA256 on the whole HDPL1 data except first 32 bytes of SHA256 */
  if (ComputeSHA256((uint8_t *)(address + SHA256_LENGTH),
                    sizeof(obk_hdpl1_data_t) - SHA256_LENGTH,
                    sha256) != HAL_OK)
  {
    ROT_LOG_ERR("Wrong OBK HDPL1 data");
    return HAL_ERROR;
  }

  (void) memcpy(&p_obk_hdpl1_data->SHA256[0], &sha256[0], SHA256_LENGTH);

  /* Write configuration in OBKeys */
  if (OBK_Write(OBK_HDPL1_DATA_OFFSET,
                (void *) p_obk_hdpl1_data,
                sizeof(obk_hdpl1_data_t)) != ARM_DRIVER_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Read configuration in OBkeys HDPL1.
  * @param  p_obk_hdpl1_cfg pointer on HDPL1 configuration
  * @retval None
  */
void OBK_ReadHdpl1Config(obk_hdpl1_config_t *p_obk_hdpl1_cfg)
{
  uint8_t sha256[SHA256_LENGTH] = { 0U };
  uint32_t address = (uint32_t) p_obk_hdpl1_cfg;

  /* Read configuration in OBKeys */
  if (OBK_Read(OBK_HDPL1_CFG_OFFSET,
               (void *) p_obk_hdpl1_cfg,
               sizeof(obk_hdpl1_config_t)) != ARM_DRIVER_OK)
  {
    Error_Handler();
  }

  /* Verify SHA256 on the whole HDPL1 config except first 32 bytes of SHA256 */
  if (ComputeSHA256((uint8_t *)(address + SHA256_LENGTH),
                    sizeof(obk_hdpl1_config_t) - SHA256_LENGTH,
                    sha256) != HAL_OK)
  {
    Error_Handler();
  }
  if (MemoryCompare(&p_obk_hdpl1_cfg->SHA256[0], &sha256[0], SHA256_LENGTH) != 0U)
  {
    ROT_LOG_ERR("read: Wrong OBK HDPL1 cfg");
    Error_Handler();
  }
}

/**
  * @brief  Verify configuration in OBkeys HDPL1.
  * @param  p_obk_hdpl1_cfg pointer on HDPL1 configuration
  * @retval None
  */
void OBK_VerifyHdpl1Config(obk_hdpl1_config_t *p_obk_hdpl1_cfg)
{
  uint8_t sha256[SHA256_LENGTH] = { 0U };
  uint32_t address = (uint32_t) p_obk_hdpl1_cfg;

  /* Verify SHA256 on the whole HDPL1 config except first 32 bytes of SHA256 */
  if (ComputeSHA256((uint8_t *)(address + SHA256_LENGTH),
                    sizeof(obk_hdpl1_config_t) - SHA256_LENGTH,
                    sha256) != HAL_OK)
  {
    Error_Handler();
  }
  if (MemoryCompare(&p_obk_hdpl1_cfg->SHA256[0], &sha256[0], SHA256_LENGTH) != 0U)
  {
    ROT_LOG_ERR("verify: Wrong OBK HDPL1 cfg");
    Error_Handler();
  }
}

/**
  * @brief  Get counter.
  * @param  counter_id image identifier
  * @param  p_counter pointer on current Fw version
  * @retval HAL error status
  */
hal_status_t OBK_GetNVCounter(enum nv_counter_t counter_id, uint32_t *p_counter)
{
  obk_hdpl1_data_t OBK_data = { 0U };

  /* Read all OBK hdpl1 data & control SHA256 */
  if (OBK_ReadHdpl1Data(&OBK_data) != HAL_OK)
  {
    return HAL_ERROR;
  }
  *p_counter = 0xFFFFFFFFU;
  switch (counter_id)
  {
    case BOOT_NV_COUNTER_0 :
      if (OBK_data.Image0CurVersion >= OBK_data.Image0PrevVersion)
      {
        *p_counter = OBK_data.Image0CurVersion;
        return HAL_OK;
      }
      break;
    case BOOT_NV_COUNTER_1 :
      if (OBK_data.Image1CurVersion >= OBK_data.Image1PrevVersion)
      {
        *p_counter = OBK_data.Image1CurVersion;
        return HAL_OK;
      }
      break;
    case BOOT_NV_COUNTER_2 :
      if (OBK_data.Image2CurVersion >= OBK_data.Image2PrevVersion)
      {
        *p_counter = OBK_data.Image2CurVersion;
        return HAL_OK;
      }
      break;
    case BOOT_NV_COUNTER_3 :
      if (OBK_data.Image3CurVersion >= OBK_data.Image3PrevVersion)
      {
        *p_counter = OBK_data.Image3CurVersion;
        return HAL_OK;
      }
      break;
    default :
      break;
  }
  return HAL_ERROR;
}

/**
  * @brief  Update counter in OBKeys.
  * @param  counter_id image identifier
  * @param  counter Fw version
  * @retval HAL error status
  */
hal_status_t OBK_UpdateNVCounter(enum nv_counter_t counter_id, uint32_t counter)
{
  hal_status_t status = HAL_ERROR;
  obk_hdpl1_data_t OBK_data = { 0U };

  /* Read all OBK hdpl1 data & control SHA256 */
  if (OBK_ReadHdpl1Data(&OBK_data) != HAL_OK)
  {
    return HAL_ERROR;
  }

  switch (counter_id)
  {
    case BOOT_NV_COUNTER_0 :
      OBK_data.Image0PrevVersion = OBK_data.Image0CurVersion;
      OBK_data.Image0CurVersion = counter;
      break;
    case BOOT_NV_COUNTER_1 :
      OBK_data.Image1PrevVersion = OBK_data.Image1CurVersion;
      OBK_data.Image1CurVersion = counter;
      break;
    case BOOT_NV_COUNTER_2 :
      OBK_data.Image2PrevVersion = OBK_data.Image2CurVersion;
      OBK_data.Image2CurVersion = counter;
      break;
    case BOOT_NV_COUNTER_3 :
      OBK_data.Image3PrevVersion = OBK_data.Image3CurVersion;
      OBK_data.Image3CurVersion = counter;
      break;
    default :
      return HAL_ERROR;
      break;
  }
  /* Update all OBK hdpl1 data with associated SHA256 */
  status = OBK_UpdateHdpl1Data(&OBK_data);

  return status;
}
