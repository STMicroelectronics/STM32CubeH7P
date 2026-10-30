/**
  ******************************************************************************
  * file           : stm32h7pxx_ll_example.c
  * brief          : I2C communication in DMA mode with LL API.
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
/* Describes the current I2C DMA transfer state. */
typedef enum
{
  I2C_XFER_NONE = 0U, /* No transfer is currently active.    */
  I2C_XFER_TX   = 1U, /* A transmit transfer is in progress. */
  I2C_XFER_RX   = 2U  /* A receive transfer is in progress.  */
} i2c_xfer_t;

/* Private define ------------------------------------------------------------*/
#define DMA_OPT_IT_NONE            (0U)
#define DMA_OPT_IT_SILENT          (0xFFFFFFFFU)
#define I2C_XFER_TX_IT_MASK        (LL_I2C_CR1_STOPIE | LL_I2C_CR1_NACKIE)
#define I2C_INTERRUPT_ENABLE_FLAGS (I2C_XFER_TX_IT_MASK | LL_I2C_CR1_TCIE | LL_I2C_CR1_TXIE | LL_I2C_CR1_RXIE)

/** Mask used to clear the transfer configuration bits in I2C CR2 while preserving
  * the other control bits. It removes the address, addressing mode, byte count,
  * reload, and transfer direction fields after a transfer completes.
  */
#define I2C_XFER_INFO ~((uint32_t) (I2C_CR2_SADD | I2C_CR2_HEAD10R | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_RD_WRN))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Tracks the current I2C transfer state shared between the main flow and interrupt handlers. */
static volatile i2c_xfer_t I2C_CurrentXfer = I2C_XFER_NONE;

/* Private functions prototype -----------------------------------------------*/
void mx_lpdmax_chx_irqhandler(void); /* DMA interrupt handler for the transmit DMA channel. */
void mx_lpdmax_chy_irqhandler(void); /* DMA interrupt handler for the receive DMA channel.  */

void mx_i2cx_ev_irqhandler(void);    /* I2C event interrupt handler for transfer-related events. */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
void mx_i2cx_err_irqhandler(void);   /* I2C error interrupt handler.                             */
#endif /* USE_LL_APP_ERROR */

static void DMA_StartDirectXfer(DMA_Channel_TypeDef *dmax_chy, uint32_t src_addr, uint32_t dest_addr,
                                uint32_t size_byte);
static void DMA_IRQHandler(DMA_Channel_TypeDef *dmax_chy);
/* Private functions ---------------------------------------------------------*/


/** brief:  Transmit in controller mode an amount of data in non-blocking mode with DMA.
  * param   responder_address: Target device address.
  * param   tx_buffer:         Pointer to transmission data buffer.
  * param   size:              Number of bytes to transfer.
  */
inline void I2C_Transmit_DMA(uint8_t responder_address, uint8_t *tx_buffer, uint8_t size)
{
  I2C_CurrentXfer = I2C_XFER_TX;

  DMA_StartDirectXfer(MX_LPDMAX_CHX_CH,
                      (uint32_t) tx_buffer,
                      LL_I2C_DMA_GetRegAddrTx(MX_I2Cx),
                      size);

  LL_I2C_HandleTransfer(MX_I2Cx,
                        responder_address,
                        LL_I2C_ADDRSLAVE_7BIT,
                        size,
                        LL_I2C_MODE_AUTOEND,
                        LL_I2C_GENERATE_START_WRITE);

  /* Enable MX_I2Cx interrupts */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_I2C_EnableIT(MX_I2Cx, LL_I2C_CR1_ERRIE | I2C_XFER_TX_IT_MASK);
#else
  LL_I2C_EnableIT(MX_I2Cx, I2C_XFER_TX_IT_MASK);
#endif /* USE_LL_APP_ERROR */

  LL_I2C_EnableDMAReq_TX(MX_I2Cx);
}


/** brief:  Receive in controller mode an amount of data in non-blocking mode with DMA.
  * param   responder_address: Target device address.
  * param   rx_buffer:         Pointer to reception data buffer.
  * param   size:              Number of bytes to transfer.
  */
inline void I2C_Receive_DMA(uint8_t responder_address, uint8_t *rx_buffer, uint8_t size)
{
  I2C_CurrentXfer = I2C_XFER_RX;

  DMA_StartDirectXfer(MX_LPDMAX_CHY_CH,
                      LL_I2C_DMA_GetRegAddrRx(MX_I2Cx),
                      (uint32_t)rx_buffer,
                      size);

  LL_I2C_HandleTransfer(MX_I2Cx,
                        responder_address,
                        LL_I2C_ADDRSLAVE_7BIT,
                        size,
                        LL_I2C_MODE_AUTOEND,
                        LL_I2C_GENERATE_START_READ);

  /* Enable MX_I2Cx interrupts */
#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_I2C_EnableIT(MX_I2Cx, LL_I2C_CR1_ERRIE | I2C_XFER_TX_IT_MASK);
#else
  LL_I2C_EnableIT(MX_I2Cx, I2C_XFER_TX_IT_MASK);
#endif /* USE_LL_APP_ERROR */

  LL_I2C_EnableDMAReq_RX(MX_I2Cx);
}


/** brief: Start the DMA channel direct transfer.
  * param  dmax_chy :  Channel pointer to the LPDMA channel.
  * param  src_addr :  Source address
  * param  dest_addr:  Destination address
  * param  size_byte:  Size in byte
  */
static inline void DMA_StartDirectXfer(DMA_Channel_TypeDef *dmax_chy, uint32_t src_addr, uint32_t dest_addr,
                                       uint32_t size_byte)
{
  LL_DMA_ConfigAddresses(dmax_chy, src_addr, dest_addr);
  LL_DMA_SetBlkDataLength(dmax_chy, size_byte);

  LL_DMA_ClearFlag(dmax_chy, LL_DMA_FLAG_ALL);

  LL_DMA_DisableIT(dmax_chy, LL_DMA_IT_ALL);

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  LL_DMA_EnableIT(dmax_chy, (LL_DMA_IT_TC | LL_DMA_IT_DTE | LL_DMA_IT_USE));
#else
  LL_DMA_EnableIT(dmax_chy, LL_DMA_IT_TC);
#endif /* USE_LL_APP_ERROR */

  LL_DMA_ConfigLinkUpdate(dmax_chy, 0U, 0U);

  LL_DMA_EnableChannel(dmax_chy);
}


/**
  *  Handles the MX_LPDMAX_CHY_CH interrupts.
  */
void mx_lpdmax_chy_irqhandler(void)
{
  DMA_IRQHandler(MX_LPDMAX_CHY_CH);
}


/**
  *  Handles the MX_LPDMAX_CHX_CH interrupts.
  */
void mx_lpdmax_chx_irqhandler(void)
{
  DMA_IRQHandler(MX_LPDMAX_CHX_CH);
}


/**
  *  Handles the MX_I2Cx event interrupts.
  */
void mx_i2cx_ev_irqhandler(void)
{
  i2c_xfer_t completed_xfer = I2C_XFER_NONE;

  if (LL_I2C_IsActiveFlag_NACK(MX_I2Cx) != 0U)
  {
    LL_I2C_ClearFlag_NACK(MX_I2Cx);
  }

  if (LL_I2C_IsActiveFlag_STOP(MX_I2Cx) != 0U)
  {
    LL_I2C_ClearFlag_STOP(MX_I2Cx);
    LL_I2C_DisableIT(MX_I2Cx, I2C_INTERRUPT_ENABLE_FLAGS);
    completed_xfer = I2C_CurrentXfer;
    I2C_CurrentXfer = I2C_XFER_NONE;
  }

  LL_I2C_WRITE_REG(MX_I2Cx, CR2, (LL_I2C_READ_REG(MX_I2Cx, CR2) & I2C_XFER_INFO));

  if (completed_xfer == I2C_XFER_TX)
  {
    if (LL_I2C_IsActiveFlag_TXIS(MX_I2Cx) != 0U)
    {
      LL_I2C_TransmitData8(MX_I2Cx, 0U);
    }

    LL_I2C_ClearFlag_TXE(MX_I2Cx);

    LL_I2C_DisableDMAReq_TX(MX_I2Cx);

    I2C_TxTransferCpltCallback();
  }

  if (completed_xfer == I2C_XFER_RX)
  {
    LL_I2C_DisableDMAReq_RX(MX_I2Cx);

    I2C_RxTransferCpltCallback();
  }

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  if (completed_xfer == I2C_XFER_NONE)
  {
    LL_I2C_DisableDMAReq_TX(MX_I2Cx);
    LL_I2C_DisableDMAReq_RX(MX_I2Cx);

    I2C_TransferErrorCallback();
  }
#endif /* USE_LL_APP_ERROR */
}


#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/**
  *  Handles the MX_I2Cx error interrupts.
  */
void mx_i2cx_err_irqhandler(void)
{
  if (LL_I2C_IsActiveFlag_BERR(MX_I2Cx) != 0U)
  {
    LL_I2C_ClearFlag_BERR(MX_I2Cx);
  }

  if (LL_I2C_IsActiveFlag_ARLO(MX_I2Cx) != 0U)
  {
    LL_I2C_ClearFlag_ARLO(MX_I2Cx);
  }

  if (LL_I2C_IsActiveFlag_OVR(MX_I2Cx) != 0U)
  {
    LL_I2C_ClearFlag_OVR(MX_I2Cx);
  }

  LL_I2C_DisableDMAReq_TX(MX_I2Cx);
  LL_I2C_DisableDMAReq_RX(MX_I2Cx);
  LL_I2C_DisableIT(MX_I2Cx, LL_I2C_CR1_ERRIE | I2C_INTERRUPT_ENABLE_FLAGS);

  I2C_TransferErrorCallback();
}
#endif /* USE_LL_APP_ERROR */


/**
  * brief: Handles the DMA channels interrupts.
  * param: channel pointer to the LPDMA channel.
  */
static inline void DMA_IRQHandler(DMA_Channel_TypeDef *dmax_chy)
{
  DMA_TypeDef *instance;
  uint32_t    flags;
  uint32_t    its;
  uint32_t    dma_channel;

  instance     = LL_DMA_GET_INSTANCE(dmax_chy);
  dma_channel  = LL_DMA_GET_CHANNEL_IDX(dmax_chy);
  its          = LL_DMA_READ_REG((dmax_chy), CCR);
  flags        = LL_DMA_READ_REG((dmax_chy), CSR);

  /* Check DMA channel active interrupts */
  if (LL_DMA_IsActiveFlag_MIS(instance, dma_channel) == 0U)
  {
    return; /* the global interrupt flag for the current channel is down , nothing to do */
  }

  /* Transfer Complete Interrupt management */
  if (STM32_READ_BIT((flags & its), LL_DMA_FLAG_TC) != 0U)
  {
    LL_DMA_ClearFlag_TC(dmax_chy);

    return;
  }

#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
  /* Error Interrupt management */
  LL_DMA_ClearFlag(dmax_chy, LL_DMA_FLAG_ALL);

  /* Check error flags */
  if (((flags & its) & (LL_DMA_FLAG_DTE | LL_DMA_FLAG_USE)) != 0U)
  {
    LL_DMA_ResetChannel(dmax_chy);

    LL_DMA_DisableIT(dmax_chy, LL_DMA_IT_ALL);

    I2C_TransferErrorCallback();
  }
#endif /* USE_LL_APP_ERROR */
}


#if defined(USE_LL_APP_ERROR) && (USE_LL_APP_ERROR == 1)
/**
  * brief: This function provides delay (in milliseconds) based on SysTick counter flag.
  * param: delay_ms Number of milliseconds to delay.
  */
inline void DelayMs(uint32_t delay_ms)
{
  LL_Delay_NoISR(delay_ms);
}
#endif /* USE_LL_APP_ERROR */

