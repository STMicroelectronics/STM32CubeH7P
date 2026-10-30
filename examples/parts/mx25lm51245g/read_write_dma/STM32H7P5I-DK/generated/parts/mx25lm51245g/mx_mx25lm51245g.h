/**
  ******************************************************************************
  * file           : mx_mx25lm51245g.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_MX25LM51245G_H
#define MX_MX25LM51245G_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mx25lm51245g.h"
#include "mx_hal_def.h"

/* Exported macro ------------------------------------------------------------*/
/* Part Config ID */
#define MX25LM51245G_0                              0
/* No label has been defined for this part driver instance,
 * so no alias is generated for MX25LM51245G_0 or mx_mx25lm51245g_0_getobject(). */

/* Resource bindings */
#define MX25LM51245G_0_BASE_ADDR         XSPI1_BASE
#define MX25LM51245G_0_XSPI_GETHANDLE    mx_xspi1_gethandle
 
 

/* Functions to retrieve the part object */
mx25lm51245g_obj_t *mx_mx25lm51245g_0_getobject(void);
 
 

#ifdef __cplusplus
}
#endif

#endif /* MX_MX25LM51245G_H */
