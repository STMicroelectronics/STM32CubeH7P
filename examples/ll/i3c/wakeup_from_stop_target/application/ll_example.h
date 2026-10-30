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

/** brief: Activates the notification feature of the MX_I3Cx instance.
  */
void I3C_ActivateNotification(void);

/** brief: Gets the MX_I3Cx own dynamic address.
  * retval: Value of the own dynamic address.
  */
uint32_t I3C_GetOwnDynamicAddress(void);

/** brief: Gets the validity status of the MX_I3Cx own dynamic address.
  * retval: 1 if the dynamic address is valid, 0 otherwise.
  */
uint32_t I3C_IsOwnDynamicAddressValid(void);

/** brief: Starts a target receive operation in interrupt mode for the MX_I3Cx instance.
  * param rx_data: Pointer to the receive buffer.
  * param size_byte: Number of bytes expected to be received.
  * retval: SYSTEM_OK when the receive is armed.
  */
system_status_t I3C_Receive_IT(uint8_t *rx_data, uint32_t size_byte);

/** brief: Starts a target transmit operation in interrupt mode for the MX_I3Cx instance.
  * param tx_data: Pointer to the transmit payload buffer.
  * param size_byte: Number of bytes to be transmitted.
  * retval: SYSTEM_OK when the transmit is armed.
  */
system_status_t I3C_Transmit_IT(const uint8_t *tx_data, uint32_t size_byte);

/** brief: MX_I3Cx dynamic address assignment complete callback.
  */
void I3C_DynamicAddressAssignmentCompleteCallback(void);

/** brief: MX_I3Cx RX complete callbacks.
  */
void I3C_ReceiveCompleteCallback(void);

/** brief: MX_I3Cx TX complete callbacks.
  */
void I3C_TransmitCompleteCallback(void);

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/** brief: MX_I3Cx transfer error callback.
  */
void I3C_ErrorCallback(void);
#endif /* USE_LL_APP_ERROR */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LL_EXAMPLE_H */
