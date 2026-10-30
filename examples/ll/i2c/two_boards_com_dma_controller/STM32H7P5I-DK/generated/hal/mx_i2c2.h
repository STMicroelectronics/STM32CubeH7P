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
#include "stm32_ll.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USE_I2C2

/* I2C2 TX / GPDMA1_CH0 DMA channel aliases */
#define MX_LPDMAX_CHX_CH                      LL_GPDMA1_CH0

/* I2C2 RX / GPDMA1_CH1 DMA channel aliases */
#define MX_LPDMAX_CHY_CH                      LL_GPDMA1_CH1

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for I2C in LL layer */
/******************************************************************************/
/**
  * @brief mx_i2c2_i2c init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
I2C_TypeDef *mx_i2c2_i2c_init(void);

/**
  * @brief  De-initialize i2c2 instance and return it.
  */
void mx_i2c2_i2c_deinit(void);

/******************************************************************************/
/*           I2C2 event interrupt is managed directly in user code.           */
/******************************************************************************/
/* void I2C2_EV_IRQHandler(void); */

/******************************************************************************/
/*           I2C2 error interrupt is managed directly in user code.           */
/******************************************************************************/
/* void I2C2_ERR_IRQHandler(void); */

/******************************************************************************/
/*        GPDMA1 channel 0 interrupt is managed directly in user code.        */
/******************************************************************************/
/* void GPDMA1_CH0_IRQHandler(void); */

/******************************************************************************/
/*        GPDMA1 channel 1 interrupt is managed directly in user code.        */
/******************************************************************************/
/* void GPDMA1_CH1_IRQHandler(void); */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_I2C2_H */
