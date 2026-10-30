/**
  ******************************************************************************
  * @file           : mx_xspi1.c
  * @brief          : XSPI1 Peripheral initialization
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

/* Includes ------------------------------------------------------------------*/
#include "mx_xspi1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_xspi_handle_t hXSPI1;

static hal_dma_handle_t hHPDMA1_CH0;
static hal_dma_handle_t hHPDMA1_CH1;
/******************************************************************************/
/* Exported functions for XSPI in HAL layer */
/******************************************************************************/
hal_xspi_handle_t *mx_xspi1_init(void)
{
  hal_xspi_config_t xspi_config;
  hal_xspi_memory_config_t memory_config;
  hal_xspi_timing_config_t timing_config;
  uint32_t p_max_clock_phase;

  if (HAL_XSPI_Init(&hXSPI1, HAL_XSPI1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_XSPI1_EnableClock();

  if (HAL_RCC_XSPI1_SetKernelClkSource(HAL_RCC_XSPI1_CLK_SRC_HCLK5) != HAL_OK)
  {
    return NULL;
  }

/* Main peripheral configuration */
  memory_config.mode = HAL_XSPI_MEMORY_SINGLE;
  memory_config.type = HAL_XSPI_MEMORY_TYPE_MACRONIX;
  memory_config.size_bit = HAL_XSPI_MEMORY_SIZE_512MBIT;
  memory_config.wrap_size_byte = HAL_XSPI_WRAP_NOT_SUPPORTED;
  memory_config.cs_boundary = HAL_XSPI_CS_BOUNDARY_NONE;

  timing_config.clk_prescaler = 1U;
  timing_config.shift = HAL_XSPI_SAMPLE_SHIFT_NONE;
  timing_config.hold = HAL_XSPI_DELAY_HOLD_QUARTCYCLE;
  timing_config.cs_high_time_cycle = 2U;
  timing_config.cs_refresh_time_cycle = 0U;
  timing_config.dlyb_state = HAL_XSPI_DLYB_ON;

  xspi_config.memory = memory_config;
  xspi_config.timing = timing_config;

  if (HAL_XSPI_SetConfig(&hXSPI1, &xspi_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_XSPI_SetFifoThreshold(&hXSPI1, 4U) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_XSPI_SetMemorySelection(&hXSPI1, HAL_XSPI_MEMORY_SELECTION_NCS1) != HAL_OK)
  {
    return NULL;
  }

  /* ### XSPI1 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOD_EnableClock();

  HAL_RCC_GPIOB_EnableClock();

  HAL_RCC_GPIOG_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PD2     ------>   XSPI1_CLK
       PD15    ------>   XSPI1_IO4
       PD14    ------>   XSPI1_IO5
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_3;
  HAL_GPIO_Init(HAL_GPIOD, HAL_GPIO_PIN_2 | HAL_GPIO_PIN_15 | HAL_GPIO_PIN_14, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PD0     ------>   XSPI1_DQS0
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_3;
  HAL_GPIO_Init(HAL_GPIOD, HAL_GPIO_PIN_0, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PD7     ------>   XSPI1_IO0
       PD6     ------>   XSPI1_IO1
       PD5     ------>   XSPI1_IO2
       PD4     ------>   XSPI1_IO3
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_8;
  HAL_GPIO_Init(HAL_GPIOD, HAL_GPIO_PIN_7 | HAL_GPIO_PIN_6 | HAL_GPIO_PIN_5 | HAL_GPIO_PIN_4, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PD13    ------>   XSPI1_IO6
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_10;
  HAL_GPIO_Init(HAL_GPIOD, HAL_GPIO_PIN_13, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB9     ------>   XSPI1_IO7
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_9, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PB2     ------>   XSPI1_NCLK
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_12;
  HAL_GPIO_Init(HAL_GPIOB, HAL_GPIO_PIN_2, &gpio_config);

  /**
    [GPIO Pin] ------> [Signal Name]

       PG10    ------>   XSPI1_NCS1
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_UP;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_3;
  HAL_GPIO_Init(HAL_GPIOG, HAL_GPIO_PIN_10, &gpio_config);

  /* Configure the DMA TX */

  /* Configure the HPDMA1_CH0 DMA channel for XSPI1 TX */
  if (HAL_DMA_Init(&hHPDMA1_CH0, HAL_HPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_HPDMA1_EnableClock();

  hal_dma_direct_xfer_config_t xfer_cfg_xspi1_dma;
  xfer_cfg_xspi1_dma.request         = HAL_HPDMA1_REQUEST_XSPI1;
  xfer_cfg_xspi1_dma.direction       = HAL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  xfer_cfg_xspi1_dma.src_inc         = HAL_DMA_SRC_ADDR_INCREMENTED;
  xfer_cfg_xspi1_dma.dest_inc        = HAL_DMA_DEST_ADDR_FIXED;
  xfer_cfg_xspi1_dma.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_BYTE;
  xfer_cfg_xspi1_dma.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_BYTE;
  xfer_cfg_xspi1_dma.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigPeriphDirectXfer(&hHPDMA1_CH0, &xfer_cfg_xspi1_dma) != HAL_OK)
  {
    return NULL;
  }

  /* Set DMA channel access ports xfer configuration */
  {
    if (HAL_DMA_SetConfigDirectXferPort(&hHPDMA1_CH0, HAL_DMA_PORT0, HAL_DMA_PORT1) != HAL_OK)
    {
      return NULL;
    }
  }

  /* Enable the interruption for HPDMA1_CH0 */
  HAL_CORTEX_NVIC_SetPriority(HPDMA1_CH0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HPDMA1_CH0_IRQn);

  /* Link the Transmit DMA handle to the XSPI handle */
  if (HAL_XSPI_SetTxDMA(&hXSPI1, &hHPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }

  /* Configure the DMA RX */

  /* Configure the HPDMA1_CH1 DMA channel for XSPI1 RX */
  if (HAL_DMA_Init(&hHPDMA1_CH1, HAL_HPDMA1_CH1) != HAL_OK)
  {
    return NULL;
  }

  xfer_cfg_xspi1_dma.request         = HAL_HPDMA1_REQUEST_XSPI1;
  xfer_cfg_xspi1_dma.direction       = HAL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  xfer_cfg_xspi1_dma.src_inc         = HAL_DMA_SRC_ADDR_FIXED;
  xfer_cfg_xspi1_dma.dest_inc        = HAL_DMA_DEST_ADDR_INCREMENTED;
  xfer_cfg_xspi1_dma.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_BYTE;
  xfer_cfg_xspi1_dma.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_BYTE;
  xfer_cfg_xspi1_dma.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigPeriphDirectXfer(&hHPDMA1_CH1, &xfer_cfg_xspi1_dma) != HAL_OK)
  {
    return NULL;
  }

  /* Set DMA channel access ports xfer configuration */
  {
    if (HAL_DMA_SetConfigDirectXferPort(&hHPDMA1_CH1, HAL_DMA_PORT1, HAL_DMA_PORT0) != HAL_OK)
    {
      return NULL;
    }
  }

  /* Enable the interruption for HPDMA1_CH1 */
  HAL_CORTEX_NVIC_SetPriority(HPDMA1_CH1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HPDMA1_CH1_IRQn);

  /* Link the Receive DMA handle to the XSPI handle */
  if (HAL_XSPI_SetRxDMA(&hXSPI1, &hHPDMA1_CH1) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the interrupt for XSPI */
  HAL_CORTEX_NVIC_SetPriority(XSPI1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(XSPI1_IRQn);
      /* Delay block configuration */
  if (HAL_XSPI_DLYB_Enable(&hXSPI1) != HAL_OK)
  {
    return NULL;
  }
  p_max_clock_phase = 4U;

  if (HAL_XSPI_DLYB_SetConfigDelay(&hXSPI1, p_max_clock_phase) != HAL_OK)
  {
    return NULL;
  }

  return &hXSPI1;
}

void mx_xspi1_deinit(void)
{
  /* Disable the interrupt for XSPI */
  HAL_CORTEX_NVIC_DisableIRQ(XSPI1_IRQn);

  (void)HAL_XSPI_DeInit(&hXSPI1);

  HAL_RCC_XSPI1_Reset();

  HAL_RCC_XSPI1_DisableClock();

  /* De-initialize all GPIOD pins associated with XSPI1 */
  HAL_GPIO_DeInit(HAL_GPIOD, HAL_GPIO_PIN_0 | HAL_GPIO_PIN_2 | HAL_GPIO_PIN_4 | HAL_GPIO_PIN_5 | HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7 | HAL_GPIO_PIN_13 | HAL_GPIO_PIN_14 | HAL_GPIO_PIN_15);

  /* De-initialize all GPIOB pins associated with XSPI1 */
  HAL_GPIO_DeInit(HAL_GPIOB, HAL_GPIO_PIN_2 | HAL_GPIO_PIN_9);

  /* De-initialize all GPIOG pins associated with XSPI1 */
  HAL_GPIO_DeInit(HAL_GPIOG, HAL_GPIO_PIN_10);

  /* De-initialize the DMA channel */
  HAL_DMA_DeInit(&hHPDMA1_CH0);

  /* Disable the interruption for DMA */
  HAL_CORTEX_NVIC_DisableIRQ(HPDMA1_CH0_IRQn);

  /* De-initialize the DMA channel */
  HAL_DMA_DeInit(&hHPDMA1_CH1);

  /* Disable the interruption for DMA */
  HAL_CORTEX_NVIC_DisableIRQ(HPDMA1_CH1_IRQn);
  }

hal_xspi_handle_t *mx_xspi1_gethandle(void)
{
  return &hXSPI1;
}

/******************************************************************************/
/*                         HPDMA1 channel 0 interrupt                         */
/******************************************************************************/
void HPDMA1_CH0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hHPDMA1_CH0);
}

/******************************************************************************/
/*                         HPDMA1 channel 1 interrupt                         */
/******************************************************************************/
void HPDMA1_CH1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hHPDMA1_CH1);
}

/******************************************************************************/
/*                           XSPI1 global interrupt                           */
/******************************************************************************/
void XSPI1_IRQHandler(void)
{
  HAL_XSPI_IRQHandler(&hXSPI1);
}
