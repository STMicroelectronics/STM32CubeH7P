/**
  ******************************************************************************
  * file           : mx_mx25lm51245g.c
  * brief          : Code generation for the MX25LM51245G part driver.
  ******************************************************************************
  * attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_mx25lm51245g_license.md file
  * in the same directory as the generated code.
  * If no mx_mx25lm51245g_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "mx_mx25lm51245g.h"

static mx25lm51245g_obj_t  mx25lm51245g_0_obj;

/**
  * @brief initialize the IO layer.
  * @param  pio      pointer to the part IO structure.
  * @retval error status.
  */
int32_t mx25lm51245g_io_init(mx25lm51245g_io_t *pio)
{
  /* Part Status */
  int ret = 0;

  switch (pio->id)
  {
    case MX25LM51245G_0:
      pio->phxspi                      = MX25LM51245G_0_XSPI_GETHANDLE();
      pio->memory_base_address         = MX25LM51245G_0_BASE_ADDR;
      break;
 
 
    default:
      /* Error -- Unknown ID */
      ret = -1;
      break;
  }

  return ret;
}

/**
  * @brief Function to retrieve the Part object 0.
  * @retval part object.
  */
mx25lm51245g_obj_t *mx_mx25lm51245g_0_getobject(void)
{
  return &mx25lm51245g_0_obj;
}
 
 
