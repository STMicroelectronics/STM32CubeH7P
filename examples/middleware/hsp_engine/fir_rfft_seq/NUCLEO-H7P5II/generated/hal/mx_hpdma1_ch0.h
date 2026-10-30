/**
  ******************************************************************************
  * @file           : mx_hpdma1_ch0.h
  * @brief          : Header for mx_hpdma1_ch0.c file.
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

/* Define to prevent recursive inclusion ----------------------------------------------------------------------------*/
#ifndef MX_HPDMA1_CH0_H
#define MX_HPDMA1_CH0_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern volatile uint32_t end_of_copy_bramab_to_ping_result;

/* Exported functions ---------------------------------------------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for DMA in HAL layer */
/******************************************************************************/
/**
  * @brief mx_hpdma1_ch0 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_dma_handle_t *mx_hpdma1_ch0_init(void);

/**
  * @brief  De-initialize hpdma1_ch0 instance and return it.
  */
void mx_hpdma1_ch0_deinit(void);

/**
  * @brief  Get the HPDMA1_CH0 object.
  * @retval Pointer on the HPDMA1_CH0 Handle
  */
hal_dma_handle_t *mx_hpdma1_ch0_gethandle(void);

/******************************************************************************/
/* HPDMA1 channel 0 interrupt */
/******************************************************************************/
void HPDMA1_CH0_IRQHandler(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HPDMA1_CH0_H */
