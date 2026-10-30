/**
  ******************************************************************************
  * file           : mx_tcpp01.c
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

/* Includes ------------------------------------------------------------------*/
#include "mx_tcpp01.h"

static tcpp01_obj_t  tcpp01_0_obj;

/**
  * @brief initialize the IO layer.
  * @param  pio      pointer to the part IO structure.
  * @retval error status.
  */
int32_t tcpp01_io_init(tcpp01_io_t *pio)
{
  /* Part Status */
  int ret = 0;

  switch (pio->id)
  {
    case TCPP01_0:
      pio->phadc        = TCPP01_0_ADC_GETHANDLE();
      pio->db_port      = TCPP01_0_DB_GPIO_PORT;
      pio->db_pin       = TCPP01_0_DB_PIN;
      pio->active_state = TCPP01_0_DB_ACTIVE_STATE;
      pio->phexti       = TCPP01_0_EXTI_GETHANDLE();
      pio->irq_line     = TCPP01_0_IRQ_LINE;
      pio->int_port     = TCPP01_0_INT_GPIO_PORT;
      pio->int_pin      = TCPP01_0_INT_PIN;
      pio->Ra           = TCPP01_0_VBUS_RA;
      pio->Rb           = TCPP01_0_VBUS_RB;
      pio->Vdd          = TCPP01_0_VDD;

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
tcpp01_obj_t *mx_tcpp01_0_getobject(void)
{
  return &tcpp01_0_obj;
}
