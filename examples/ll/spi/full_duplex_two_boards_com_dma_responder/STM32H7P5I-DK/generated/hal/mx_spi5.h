/**
  ******************************************************************************
  * @file           : mx_spi5.h
  * @brief          : Header for mx_spi5.c file.
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
#ifndef MX_SPI5_H
#define MX_SPI5_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_ll.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USE_SPI5

/* SPI5 TX / GPDMA1_CH0 DMA channel aliases */
#define MX_LPDMAX_CH1Y_CH                     LL_GPDMA1_CH0

/* SPI5 RX / GPDMA1_CH1 DMA channel aliases */
#define MX_LPDMAX_CH2Y_CH                     LL_GPDMA1_CH1

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for SPI in LL layer */
/******************************************************************************/
/**
  * @brief mx_spi5 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
SPI_TypeDef *mx_spi5_init(void);

/**
  * @brief  De-initialize spi5 instance and return it.
  */
void mx_spi5_deinit(void);

/******************************************************************************/
/*          SPI5 global interrupt is managed directly in user code.           */
/******************************************************************************/
/* void SPI5_IRQHandler(void); */

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

#endif /* MX_SPI5_H */
