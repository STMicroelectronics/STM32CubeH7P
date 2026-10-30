/**
  ******************************************************************************
  * file           : ll_example.h
  * brief          : Header for stm32ynxx_ll_example.c files.
  *                  This file contains example-specific declarations to interface with example.c functions.
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LL_EXAMPLE_H
#define LL_EXAMPLE_H

/* Includes ------------------------------------------------------------------*/
#include "mx_hal_def.h"       /* aliases to the target-specific generated code */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#ifndef USE_LL_APP_TIMEOUT
#define USE_LL_APP_TIMEOUT 0U
#endif /* USE_LL_APP_TIMEOUT */

#ifndef USE_LL_APP_ERROR
#define USE_LL_APP_ERROR 0U
#endif /* USE_LL_APP_ERROR */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** brief:  Transmit in responder mode an amount of data in non-blocking mode with interrupt.
  * param   device_address: Target device address.
  * param   tx_buffer:      Pointer to transmission data buffer.
  * param   size:           Number of bytes to transfer.
  */
void I2C_Transmit_DMA(uint8_t *tx_buffer, uint8_t size);

/** brief:  Receive in responder mode an amount of data in non-blocking mode with interrupt.
  * param   device_address: Target device address.
  * param   rx_buffer:      Pointer to reception data buffer.
  * param   size:           Number of bytes to transfer.
  */
void I2C_Receive_DMA(uint8_t *rx_buffer, uint8_t size);

/** brief:  I2C transfer complete callback. */
void I2C_TxTransferCpltCallback(void);

/** brief:  I2C receive complete callback. */
void I2C_RxTransferCpltCallback(void);

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/** brief: This function provides delay (in milliseconds) based on SysTick counter flag.
  * param: delay_ms Number of milliseconds to delay.
  */
void DelayMs(uint32_t delay_ms);

/** brief:  I2C transfer error callback. */
void I2C_TransferErrorCallback(void);
#endif /* USE_LL_APP_ERROR */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LL_EXAMPLE_H */
