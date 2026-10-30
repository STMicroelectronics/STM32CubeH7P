/**
  ******************************************************************************
  * file           : mx_tcpp01.h
  * brief          : Code generation for the TCPP01 part driver.
  ******************************************************************************
  * attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_tcpp01_license.md file
  * in the same directory as the generated code.
  * If no mx_tcpp01_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_TCPP01_H
#define MX_TCPP01_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tcpp01.h"
#include "mx_hal_def.h"

/* Exported macro ------------------------------------------------------------*/
/* Part Config ID */
#define TCPP01_0                   0

/* No label has been defined for this part driver instance,
 * so no alias is generated for TCPP010 or mx_tcpp010_getobject(). */

/* Part interface Properties */
#define TCPP01_0_ADC_GETHANDLE      mx_adc4_gethandle
/* Part cable plugged pin detection Properties */
#define TCPP01_0_EXTI_GETHANDLE     mx_gpio_default_exti0_gethandle
#define TCPP01_0_IRQ_LINE           EXTI0_IRQn
/* Part Dead Battery Pin Properties */
#define TCPP01_0_DB_GPIO_PORT      HAL_GPIOF
#define TCPP01_0_DB_PIN            HAL_GPIO_PIN_5
#define TCPP01_0_DB_ACTIVE_STATE   HAL_GPIO_PIN_SET

/* Part Interrupt Pin Control Properties */
#define TCPP01_0_INT_GPIO_PORT      HAL_GPIOF
#define TCPP01_0_INT_PIN            HAL_GPIO_PIN_0

/* Part VBUS detection Properties */
/* Value of VBUS voltage divider RA in Ohm */
#define TCPP01_0_VBUS_RA          68000
/* Value of VBUS voltage divider RB in Ohm */
#define TCPP01_0_VBUS_RB          100000
/* Value of VDD in mv */
#define TCPP01_0_VDD              3300

/* Functions to retrieve the part object */
tcpp01_obj_t *mx_tcpp01_0_getobject(void);

#ifdef __cplusplus
}
#endif

#endif /* MX_TCPP01_H */
