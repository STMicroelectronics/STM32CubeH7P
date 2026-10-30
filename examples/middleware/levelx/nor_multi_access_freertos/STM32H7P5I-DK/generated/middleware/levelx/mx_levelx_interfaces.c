/**
  ******************************************************************************
  * @file           : mx_levelx_interfaces.c
  * @brief          : generate functions to initialize flash interface
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_levelx_license.md file
  * in the same directory as the generated code.
  * If no mx_levelx_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mx_levelx_interfaces.h"
static STM32_LX_NOR_FLASH_DRIVER_CONTEXT nor_flash_driver_0_ctx;

static ULONG nor_flash_driver_0_read_buffer[LX_NOR_SECTOR_SIZE];

/**
 * mx_lx_nor_flash_driver_0_get_ctx()
 */
VOID *mx_lx_nor_flash_driver_0_get_ctx(VOID)
{
  mx25lm51245g_obj_t *pFlashObj;

  /* Retrieve the NOR flash object pointer */
  pFlashObj = mx_mx25lm51245g_0_getobject();

  /* Initialize the memory part */
  if (mx25lm51245g_init(pFlashObj, MX25LM51245G_0) != MX25LM51245G_OK)
  {
    return NULL;
  }

  if (mx25lm51245g_set_memconfig(pFlashObj, MX25LM51245G_OPI_MODE, MX25LM51245G_DTR_TRANSFER) != MX25LM51245G_OK)
  {
    return NULL;
  }

  /* Setup the levelx nor flash context */
  nor_flash_driver_0_ctx.nor_flash_flags = STM32_LX_NOR_FLAG_NONE;
  nor_flash_driver_0_ctx.nor_flash_read_buffer       = nor_flash_driver_0_read_buffer;
  nor_flash_driver_0_ctx.nor_flash_get_driver_object = (nor_flash_get_object *)mx_mx25lm51245g_0_getobject;
  nor_flash_driver_0_ctx.nor_flash_op_timeout        = 460000U;

  return (VOID *)&nor_flash_driver_0_ctx;
}
