/**
  ******************************************************************************
  * file           : stm32h7pxx_ll_example.c
  * brief          : I3C target example with entry to low power mode using
  *                  LL API.
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

/* Includes ------------------------------------------------------------------*/
#include "ll_example.h"

/* Private define ------------------------------------------------------------*/
#define I3C_TRANSFER_MAX_WORD  16U

#define I3C_NOTIFY_IT          (LL_I3C_IER_DAUPDIE | LL_I3C_IER_WKPIE) /* Target notification IT */
#define I3C_TRANSMIT_IT       \
  (LL_I3C_IER_FCIE | LL_I3C_IER_TXFNFIE) /* Target transmit IT */
#define I3C_RECEIVE_IT        \
  (LL_I3C_IER_FCIE | LL_I3C_IER_RXFNEIE) /* Target receive IT */

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  I3C_TRANSFER_NONE = 0U,
  I3C_TRANSFER_RX   = 1U,
  I3C_TRANSFER_TX   = 2U,
} i3c_transfer_context_t;

/* Private variables ---------------------------------------------------------*/

/**
  * Transfer context for the MX_I3Cx instance, used by the interrupt handlers.
  * TxData/TxCount, RxData/RxCount: current buffer pointers and remaining payload bytes to transmit/receive.
  */
static const uint8_t *TxData;
static uint8_t *RxData;
static uint32_t TxCount;
static uint32_t RxCount;
static i3c_transfer_context_t Context;

/* Private functions prototype -----------------------------------------------*/
static void I3C_TransmitWordTreatment_IT(const uint8_t **tx_data, uint32_t *tx_size_byte);
static void I3C_ReceiveWordTreatment_IT(uint8_t **rx_data, uint32_t *rx_size_byte);
void I3C1_EV_IRQHandler(void); /* Function to handle event interrupt notification */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
void I3C1_ERR_IRQHandler(void); /* Function to handle error interrupt notification */
#endif /* USE_LL_APP_ERROR */

/* Private functions ---------------------------------------------------------*/

/** brief: Gets the MX_I3Cx own dynamic address.
  * retval: Value of the own dynamic address.
  */
inline uint32_t I3C_GetOwnDynamicAddress(void)
{
  return (uint32_t)(LL_I3C_GetOwnDynamicAddress(MX_I3Cx));
}


/** brief: Gets the validity status of the MX_I3Cx own dynamic address.
  * retval: 1 if the dynamic address is valid, 0 otherwise.
  */
inline uint32_t I3C_IsOwnDynamicAddressValid(void)
{
  return LL_I3C_IsEnabledOwnDynAddress(MX_I3Cx);
}


/** brief: Activates the notification feature of the MX_I3Cx instance.
  */
inline void I3C_ActivateNotification(void)
{
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_I3C_EnableIT(MX_I3Cx, (I3C_NOTIFY_IT | LL_I3C_IER_ERRIE));
#else
  LL_I3C_EnableIT(MX_I3Cx, I3C_NOTIFY_IT);
#endif /* USE_LL_APP_ERROR */

}


/** brief: Starts a target receive operation in interrupt mode for the MX_I3Cx instance.
  * param rx_data: Pointer to the receive buffer.
  * param size_byte: Number of bytes expected to be received.
  * retval: SYSTEM_OK when the receive is armed.
  */
inline system_status_t I3C_Receive_IT(uint8_t *rx_data, uint32_t size_byte)
{
  if ((rx_data == NULL) || (size_byte == 0U) || (LL_I3C_IsEnabled(MX_I3Cx) == 0U))
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /* Store buffer context for ISR-driven RX. */
  Context = I3C_TRANSFER_RX;
  RxData = rx_data;
  RxCount = size_byte;

  I3C_ReceiveWordTreatment_IT(&RxData, &RxCount);
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_I3C_EnableIT(MX_I3Cx, (I3C_RECEIVE_IT | LL_I3C_IER_ERRIE));
#else
  LL_I3C_EnableIT(MX_I3Cx, I3C_RECEIVE_IT);
#endif /* USE_LL_APP_ERROR */

  return SYSTEM_OK;
}


/** brief: Starts a target transmit operation in interrupt mode for the MX_I3Cx instance.
  * param tx_data: Pointer to the transmit payload buffer.
  * param size_byte: Number of bytes to be transmitted.
  * retval: SYSTEM_OK when the transmit is armed.
  */
inline system_status_t I3C_Transmit_IT(const uint8_t *tx_data, uint32_t size_byte)
{
  if ((tx_data == NULL) || (size_byte == 0U) || (LL_I3C_IsEnabled(MX_I3Cx) == 0U))
  {
    return SYSTEM_PERIPHERAL_ERROR;
  }

  /* Store buffer context for ISR-driven TX. */
  Context = I3C_TRANSFER_TX;
  TxData = tx_data;
  TxCount = size_byte;

  I3C_TransmitWordTreatment_IT(&TxData, &TxCount);

  LL_I3C_ConfigTxPreload(MX_I3Cx, (uint16_t)TxCount);
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_I3C_EnableIT(MX_I3Cx, (I3C_TRANSMIT_IT | LL_I3C_IER_ERRIE));
#else
  LL_I3C_EnableIT(MX_I3Cx, I3C_TRANSMIT_IT);
#endif /* USE_LL_APP_ERROR */

  return SYSTEM_OK;
}


/** brief: Drains the MX_I3Cx RX FIFO by word, at most I3C_TRANSFER_MAX_WORD.
  * param rx_data: Pointer to current RX pointer.
  * param rx_size_byte: Pointer to remaining RX bytes.
  */
static void I3C_ReceiveWordTreatment_IT(uint8_t **rx_data, uint32_t *rx_size_byte)
{
  I3C_TypeDef *p_i3cx = MX_I3Cx;
  uint32_t transfer_count = (*rx_size_byte + 3U) / 4U;

  if (transfer_count > I3C_TRANSFER_MAX_WORD)
  {
    transfer_count = I3C_TRANSFER_MAX_WORD;
  }

  /* Receive transfer_count while RX FIFO not empty */
  while ((LL_I3C_IsActiveFlag_RXFNE(p_i3cx) != 0U) && (transfer_count != 0U))
  {
    uint32_t word = LL_I3C_ReceiveData32(p_i3cx);
    uint32_t remaining = *rx_size_byte;
    uint32_t copy_count = (remaining >= 4U) ? 4U : remaining;

    for (uint32_t i = 0U; i < copy_count; i++)
    {
      (*rx_data)[i] = (uint8_t)((word >> (8U * i)) & 0xFFU);
    }

    (*rx_data) += copy_count;

    if (*rx_size_byte > 4U)
    {
      *rx_size_byte -= copy_count;
    }
    else
    {
      *rx_size_byte = 0U;
    }

    transfer_count--;
  }
}


/** brief: Fills the MX_I3Cx TX FIFO by word, at most I3C_TRANSFER_MAX_WORD.
  * param tx_data: Pointer to current TX pointer.
  * param tx_size_byte: Pointer to remaining TX bytes.
  */
static void I3C_TransmitWordTreatment_IT(const uint8_t **tx_data, uint32_t *tx_size_byte)
{
  I3C_TypeDef *p_i3cx = MX_I3Cx;
  uint32_t transfer_count = (*tx_size_byte + 3U) / 4U;

  if (transfer_count > I3C_TRANSFER_MAX_WORD)
  {
    transfer_count = I3C_TRANSFER_MAX_WORD;
  }

  /* Transmit transfer_count while TX FIFO not full */
  while ((LL_I3C_IsActiveFlag_TXFNF(p_i3cx) != 0U) && (transfer_count != 0U))
  {
    uint32_t word = 0U;
    uint32_t remaining = *tx_size_byte;
    uint32_t copy_count = (remaining >= 4U) ? 4U : remaining;

    for (uint32_t i = 0U; i < copy_count; i++)
    {
      word |= ((uint32_t)(*tx_data)[i] << (8U * i));
    }

    LL_I3C_TransmitData32(p_i3cx, word);
    (*tx_data) += 4U;

    if (*tx_size_byte > 4U)
    {
      *tx_size_byte -= 4U;
    }
    else
    {
      *tx_size_byte = 0U;
    }

    transfer_count--;
  }
}


/** brief: Handles the MX_I3Cx event interrupts.
  */
void I3C1_EV_IRQHandler(void)
{
  /* Wakeup event. */
  if (LL_I3C_IsActiveMaskFlag_WKP(MX_I3Cx) != 0U)
  {
    LL_I3C_ClearFlag_WKP(MX_I3Cx);
  }

  /* Dynamic address assignment events. */
  /* Dynamic Address Assignment update event: own dynamic address is updated. */
  if (LL_I3C_IsActiveMaskFlag_DAUPD(MX_I3Cx) != 0U)
  {
    LL_I3C_ClearFlag_DAUPD(MX_I3Cx);

    I3C_DynamicAddressAssignmentCompleteCallback();

    return;
  }

  /* Private transfer events. */
  /* RX FIFO not empty: drain received data into the application buffer. */
  if ((Context == I3C_TRANSFER_RX) && (LL_I3C_IsActiveMaskFlag_RXFNE(MX_I3Cx) != 0U))
  {
    I3C_ReceiveWordTreatment_IT(&RxData, &RxCount);
  }

  /* TX FIFO not full: fill FIFO with data from the application buffer. */
  if ((Context == I3C_TRANSFER_TX) && (LL_I3C_IsActiveMaskFlag_TXFNF(MX_I3Cx) != 0U))
  {
    I3C_TransmitWordTreatment_IT(&TxData, &TxCount);
  }

  /* Frame complete event. */
  if (LL_I3C_IsActiveMaskFlag_FC(MX_I3Cx) != 0U)
  {
    LL_I3C_ClearFlag_FC(MX_I3Cx);

    /* Treatment of the RX data after reception is complete. */
    if (Context == I3C_TRANSFER_RX)
    {
      I3C_ReceiveWordTreatment_IT(&RxData, &RxCount);
      if (RxCount == 0UL)
      {
        LL_I3C_DisableIT(MX_I3Cx, I3C_RECEIVE_IT);
        Context = I3C_TRANSFER_NONE;
        I3C_ReceiveCompleteCallback();
      }
    }

    /* Treatment of the TX data after transmission is complete. */
    if (Context == I3C_TRANSFER_TX)
    {
      I3C_TransmitWordTreatment_IT(&TxData, &TxCount);
      if (TxCount == 0UL)
      {
        LL_I3C_DisableIT(MX_I3Cx, I3C_TRANSMIT_IT);
        Context = I3C_TRANSFER_NONE;
        I3C_TransmitCompleteCallback();
      }
    }
  }
}

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/** brief: Handles the MX_I3Cx error interrupts.
  */
void I3C1_ERR_IRQHandler(void)
{
  /* Check on the error interrupt flag and source */
  if (LL_I3C_IsActiveFlag_ERR(MX_I3Cx) != 0U)
  {
    LL_I3C_ClearFlag_ERR(MX_I3Cx);

    I3C_ErrorCallback();
  }
}
#endif /* USE_LL_APP_ERROR */

