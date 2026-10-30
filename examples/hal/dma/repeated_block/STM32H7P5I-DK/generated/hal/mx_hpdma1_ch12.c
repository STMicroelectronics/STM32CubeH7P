/**
  ******************************************************************************
  * @file           : mx_hpdma1_ch12.c
  * @brief          : Provides HPDMA1_CH12 services
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "mx_hpdma1_ch12.h"

/* Exported variables by reference------------------------------------------------------------------------------------*/
static hal_dma_handle_t hHPDMA1_CH12;

/**********************************************************************************************************************/
/* Exported functions for HPDMA1_CH12 in HAL layer */
/**********************************************************************************************************************/
/**
  * @brief  Initialize and configure the hpdma1_ch12 (configuration 1) through HAL layer.
  * @retval Pointer to hal_dma_handle_t structure.
  */
hal_dma_handle_t *mx_hpdma1_ch12_init(void)
{
  if (HAL_DMA_Init(&hHPDMA1_CH12, HAL_HPDMA1_CH12) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_HPDMA1_EnableClock();

  hal_dma_direct_xfer_config_t xfer_cfg;

  xfer_cfg.request         = HAL_DMA_REQUEST_SW;
  xfer_cfg.direction       = HAL_DMA_DIRECTION_MEMORY_TO_MEMORY;
  xfer_cfg.src_inc         = HAL_DMA_SRC_ADDR_INCREMENTED;
  xfer_cfg.dest_inc        = HAL_DMA_DEST_ADDR_INCREMENTED;
  xfer_cfg.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_WORD;
  xfer_cfg.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_WORD;
  xfer_cfg.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigDirectXfer(&hHPDMA1_CH12, &xfer_cfg) != HAL_OK)
  {
    return NULL;
  }

  /* Set DMA channel repeated block xfer configuration */
  {
    hal_dma_repeat_block_config_t repeat_block_cfg;

    repeat_block_cfg.block_count            = 4;
    repeat_block_cfg.burst_src_offset_byte  = 0;
    repeat_block_cfg.burst_dest_offset_byte = 0;
    repeat_block_cfg.block_src_offset_byte  = 32;
    repeat_block_cfg.block_dest_offset_byte = 0;
    repeat_block_cfg.burst_src_inc          = HAL_DMA_BURST_SRC_ADDR_INCREMENTED;
    repeat_block_cfg.burst_dest_inc         = HAL_DMA_BURST_DEST_ADDR_INCREMENTED;
    repeat_block_cfg.block_src_inc          = HAL_DMA_BLOCK_SRC_ADDR_INCREMENTED;
    repeat_block_cfg.block_dest_inc         = HAL_DMA_BLOCK_DEST_ADDR_INCREMENTED;
    repeat_block_cfg.xfer_event_mode        = HAL_DMA_DIRECT_XFER_EVENT_BLOCK;
    if (HAL_DMA_SetConfigDirectXferRepeatBlock(&hHPDMA1_CH12, &repeat_block_cfg) != HAL_OK)
    {
      return NULL;
    }
  }

  /* Enable the interruption for HPDMA1_CH12 */
  HAL_CORTEX_NVIC_SetPriority(HPDMA1_CH12_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HPDMA1_CH12_IRQn);

  return &hHPDMA1_CH12;
}

/**
  * @brief  DeInitialize the hpdma1_ch12 (configuration 1) through HAL layer.
  */
void mx_hpdma1_ch12_deinit(void)
{
  /* Disable the interruption for HPDMA1_CH12 */
  HAL_CORTEX_NVIC_DisableIRQ(HPDMA1_CH12_IRQn);

  (void)HAL_DMA_DeInit(&hHPDMA1_CH12);
}

/**
  * @brief  Get the HPDMA1_CH12 object.
  */
hal_dma_handle_t *mx_hpdma1_ch12_gethandle(void)
{
  return &hHPDMA1_CH12;
}

/******************************************************************************/
/* HPDMA1 channel 12 interrupt */
/******************************************************************************/
void HPDMA1_CH12_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hHPDMA1_CH12);
}
