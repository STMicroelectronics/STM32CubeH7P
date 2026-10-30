/**
  ******************************************************************************
  * file           : stm32h7pxx_ll_example.c
  * brief          : This example code shows how to use UART LL API to transmit
  *                  and receive a data buffer with a communication process based on DMA transfer.
  *                  The communication is done with the serial terminal emulator PC application.
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype -----------------------------------------------*/
static uint32_t DMA_IRQHandler(DMA_Channel_TypeDef *channel);
static void UART_EndRxTransfer(void);
void mx_uartx_irqhandler(void);
void mx_lpdmax_ch1y_irqhandler(void);
void mx_lpdmax_ch2y_irqhandler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * brief: Transmit MX_UARTx data in DMA mode.
  * param p_data Pointer to data buffer.
  * param size_byte Amount of data elements to be transmitted.
  */
inline void UART_Transmit_DMA(const void *p_data, uint32_t size_byte)
{
  LL_DMA_DisableChannel(MX_LPDMAX_CH1Y_CH);

  LL_DMA_ConfigAddresses(MX_LPDMAX_CH1Y_CH,
                         (uint32_t)p_data,
                         LL_USART_DMA_GetRegAddr(MX_UARTx, LL_USART_DMA_REG_DATA_TRANSMIT));
  LL_DMA_SetBlkDataLength(MX_LPDMAX_CH1Y_CH, size_byte);

  LL_DMA_DisableIT(MX_LPDMAX_CH1Y_CH, LL_DMA_IT_ALL);
  LL_DMA_ClearFlag(MX_LPDMAX_CH1Y_CH, LL_DMA_FLAG_ALL);

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_DMA_EnableIT(MX_LPDMAX_CH1Y_CH, (LL_DMA_IT_TC | LL_DMA_IT_DTE | LL_DMA_IT_USE));
#else
  LL_DMA_EnableIT(MX_LPDMAX_CH1Y_CH, LL_DMA_IT_TC);
#endif /* USE_LL_APP_ERROR */

  LL_DMA_EnableChannel(MX_LPDMAX_CH1Y_CH);

  LL_USART_ClearFlag_TC(MX_UARTx);

  LL_USART_EnableDMAReq_TX(MX_UARTx);
}


/**
  * brief: Receive MX_UARTx data in DMA mode.
  * param p_data Pointer to data buffer.
  * param size_byte Amount of data elements to be received.
  * param character Character to match in the received sequence.
  */
inline void UART_ReceiveUntilCM_DMA(void *p_data, uint32_t size_byte, uint8_t character)
{
  LL_USART_Disable(MX_UARTx);
  LL_USART_SetNodeAddress(MX_UARTx, (uint32_t)character);
  LL_USART_Enable(MX_UARTx);

  LL_USART_ClearFlag(MX_UARTx, (LL_USART_ISR_NE | LL_USART_ISR_ORE | LL_USART_ISR_FE));
  LL_USART_ClearFlag_NE(MX_UARTx);
  LL_USART_RequestRxDataFlush(MX_UARTx);

  LL_USART_EnableIT_CM(MX_UARTx);

  LL_DMA_DisableChannel(MX_LPDMAX_CH2Y_CH);

  LL_DMA_ConfigAddresses(MX_LPDMAX_CH2Y_CH,
                         LL_USART_DMA_GetRegAddr(MX_UARTx, LL_USART_DMA_REG_DATA_RECEIVE),
                         (uint32_t)p_data);
  LL_DMA_SetBlkDataLength(MX_LPDMAX_CH2Y_CH, size_byte);

  LL_DMA_DisableIT(MX_LPDMAX_CH2Y_CH, LL_DMA_IT_ALL);
  LL_DMA_ClearFlag(MX_LPDMAX_CH2Y_CH, LL_DMA_FLAG_ALL);

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_DMA_EnableIT(MX_LPDMAX_CH2Y_CH, (LL_DMA_IT_TC | LL_DMA_IT_DTE | LL_DMA_IT_USE));
#else
  LL_DMA_EnableIT(MX_LPDMAX_CH2Y_CH, LL_DMA_IT_TC);
#endif /* USE_LL_APP_ERROR */

  LL_DMA_EnableChannel(MX_LPDMAX_CH2Y_CH);

  LL_USART_EnableDMAReq_RX(MX_UARTx);
}


/**
  * brief: This function handles the DMA transfer complete and error events.
  * param  channel Pointer to the DMA channel.
  * retval DMA transfer status (0: transfer ongoing, 1: transfer complete, 2: error)
  */
static uint32_t DMA_IRQHandler(DMA_Channel_TypeDef *channel)
{
  uint32_t trans_status = 0U;

  /* Check if transfer complete flag is set */
  if (LL_DMA_IsActiveFlag_TC(channel))
  {
    LL_DMA_ClearFlag_TC(channel);
    trans_status = 1U; /* Transfer complete */
  }
  /* Check if error flags are set */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  if (LL_DMA_IsActiveFlag_DTE(channel))
  {
    LL_DMA_ClearFlag_DTE(channel);
    trans_status = 2U; /* Error */
  }
  if (LL_DMA_IsActiveFlag_USE(channel))
  {
    LL_DMA_ClearFlag_USE(channel);
    trans_status = 2U; /* Error */
  }
#endif /* USE_LL_APP_ERROR */

  return trans_status;
}


/**
  * brief: This function handles UART receive complete and character match interrupts.
  */
static void UART_EndRxTransfer(void)
{
  LL_DMA_DisableChannel(MX_LPDMAX_CH2Y_CH);
  LL_USART_DisableIT_CM(MX_UARTx);
  LL_USART_DisableDMAReq_RX(MX_UARTx);
}


/**
  * brief: IRQ Handler for MX_UARTx UART instance.
  *        Handles character match and transmission-complete interrupts.
  */
void mx_uartx_irqhandler(void)
{
  extern volatile uint8_t RxTransferComplete;
  extern volatile uint8_t TxTransferComplete;

  if (LL_USART_IsActiveFlag_CM(MX_UARTx))
  {
    LL_USART_ClearFlag_CM(MX_UARTx);
    UART_EndRxTransfer();
    RxTransferComplete = 1U;
  }

  if (LL_USART_IsActiveFlag_TC(MX_UARTx))
  {
    LL_USART_ClearFlag_TC(MX_UARTx);
    LL_USART_DisableIT_TC(MX_UARTx);
    TxTransferComplete = 1U;
  }
}


/**
  * brief: IRQ Handler for MX_LPDMAX_CH1Y DMA channel.
  *        Handles TX transfer complete interrupt.
  */
void mx_lpdmax_ch1y_irqhandler(void)
{
  extern volatile uint8_t TxTransferComplete;
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  extern volatile uint8_t TransferError;
#endif /* USE_LL_APP_ERROR */

  uint32_t status = DMA_IRQHandler(MX_LPDMAX_CH1Y_CH);

  if (status == 1U)
  {
    LL_DMA_DisableChannel(MX_LPDMAX_CH1Y_CH);
    LL_USART_DisableDMAReq_TX(MX_UARTx);
    LL_USART_EnableIT_TC(MX_UARTx);
  }
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  else if (status == 2U)
  {
    TransferError = 1U;
    LL_DMA_DisableChannel(MX_LPDMAX_CH1Y_CH);
  }
#endif /* USE_LL_APP_ERROR */
}


/**
  * brief: IRQ Handler for MX_LPDMAX_CH2Y DMA channel.
  *        Handles RX transfer complete interrupt.
  */
void mx_lpdmax_ch2y_irqhandler(void)
{
  extern volatile uint8_t RxTransferComplete;
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  extern volatile uint8_t TransferError;
#endif /* USE_LL_APP_ERROR */

  uint32_t status = DMA_IRQHandler(MX_LPDMAX_CH2Y_CH);

  if (status == 1U)
  {
    LL_DMA_DisableChannel(MX_LPDMAX_CH2Y_CH);
    RxTransferComplete = 1U;
  }
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  else if (status == 2U)
  {
    TransferError = 1U;
    LL_DMA_DisableChannel(MX_LPDMAX_CH2Y_CH);
  }
#endif /* USE_LL_APP_ERROR */
}
