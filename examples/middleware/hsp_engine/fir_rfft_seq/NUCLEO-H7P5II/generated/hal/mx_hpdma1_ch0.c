/**
  ******************************************************************************
  * @file           : mx_hpdma1_ch0.c
  * @brief          : Provides HPDMA1_CH0 services
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
#include "mx_hpdma1_ch0.h"

/* Exported variables by reference------------------------------------------------------------------------------------*/

static hal_dma_handle_t hHPDMA1_CH0;
volatile uint32_t end_of_copy_bramab_to_ping_result;

void hpdma1ch0_bramab_to_results_tc_cb(hal_dma_handle_t *hdma);
void hpdma1ch0_error_cb(hal_dma_handle_t *hdma);

/**********************************************************************************************************************/
/* Exported functions for HPDMA1_CH0 in HAL layer */
/**********************************************************************************************************************/
/**
  * @brief  Initialize and configure the hpdma1_ch0 (configuration 1) through HAL layer.
  * @retval Pointer to hal_dma_handle_t structure.
  */
hal_dma_handle_t *mx_hpdma1_ch0_init(void)
{
  if (HAL_DMA_Init(&hHPDMA1_CH0, HAL_HPDMA1_CH0) != HAL_OK)
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
  xfer_cfg.priority        = HAL_DMA_PRIORITY_HIGH;

  if (HAL_DMA_SetConfigDirectXfer(&hHPDMA1_CH0, &xfer_cfg) != HAL_OK)
  {
    return NULL;
  }

  /* Set DMA channel trigger xfer configuration */
  {
    hal_dma_trigger_config_t trigger_cfg;

    trigger_cfg.source    = HAL_HPDMA1_TRIGGER_HSP1_TRGO0;
    trigger_cfg.polarity  = HAL_DMA_TRIGGER_POLARITY_RISING;
    trigger_cfg.mode      = HAL_DMA_TRIGGER_BLOCK_TRANSFER;
    if (HAL_DMA_SetConfigDirectXferTrigger(&hHPDMA1_CH0, &trigger_cfg) != HAL_OK)
    {
      return NULL;
    }
  }

  if (HAL_DMA_RegisterXferCpltCallback(&hHPDMA1_CH0, hpdma1ch0_bramab_to_results_tc_cb) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_DMA_RegisterXferErrorCallback(&hHPDMA1_CH0, hpdma1ch0_error_cb) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the interruption for HPDMA1_CH0 */
  HAL_CORTEX_NVIC_SetPriority(HPDMA1_CH0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HPDMA1_CH0_IRQn);

  return &hHPDMA1_CH0;
}

/**
  * @brief  DeInitialize the hpdma1_ch0 (configuration 1) through HAL layer.
  */
void mx_hpdma1_ch0_deinit(void)
{
  (void)HAL_DMA_DeInit(&hHPDMA1_CH0);
}

/**
  * @brief  Get the HPDMA1_CH0 object.
  */
hal_dma_handle_t *mx_hpdma1_ch0_gethandle(void)
{
  return &hHPDMA1_CH0;
}

/******************************************************************************/
/* HPDMA1 channel 0 interrupt */
/******************************************************************************/
void HPDMA1_CH0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hHPDMA1_CH0);
}

void hpdma1ch0_bramab_to_results_tc_cb(hal_dma_handle_t *hdma)
{
  end_of_copy_bramab_to_ping_result = 1;
}

void hpdma1ch0_error_cb(hal_dma_handle_t *hdma)
{
  while(1);
}