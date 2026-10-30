/**
  ******************************************************************************
  * @file           : mx_i2c2.h
  * @brief          : Header for mx_i2c2.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_I2C2_H
#define MX_I2C2_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for SMBUS in HAL layer */
/******************************************************************************/
/**
  * @brief mx_i2c2_smbus init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_smbus_handle_t *mx_i2c2_smbus_init(void);

/**
  * @brief  De-initialize i2c2 instance and return it.
  */
void mx_i2c2_smbus_deinit(void);

/**
  * @brief  Get the I2C2 object.
  * @retval Pointer on the I2C2 Handle
  */
hal_smbus_handle_t *mx_i2c2_smbus_gethandle(void);

/******************************************************************************/
/*                            I2C2 event interrupt                            */
/******************************************************************************/
void I2C2_EV_IRQHandler(void);

/******************************************************************************/
/*                            I2C2 error interrupt                            */
/******************************************************************************/
void I2C2_ERR_IRQHandler(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_I2C2_H */
