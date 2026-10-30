/**
  ******************************************************************************
  * @file           : mx_hpdma1_ch15.c
  * @brief          : Provides HPDMA1_CH15 services
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
#include "mx_hpdma1_ch15.h"

/* Exported variables by reference------------------------------------------------------------------------------------*/

static hal_dma_handle_t hHPDMA1_CH15;
volatile uint32_t end_of_copy_ping_to_bramab;

void hpdma1ch15_ping_to_bramab_tc_cb(hal_dma_handle_t *hdma);
void hpdma1ch15_error_cb(hal_dma_handle_t *hdma);

/**********************************************************************************************************************/
/* Exported functions for HPDMA1_CH15 in HAL layer */
/**********************************************************************************************************************/
/**
  * @brief  Initialize and configure the hpdma1_ch15 (configuration 1) through HAL layer.
  * @retval Pointer to hal_dma_handle_t structure.
  */
hal_dma_handle_t *mx_hpdma1_ch15_init(void)
{
  if (HAL_DMA_Init(&hHPDMA1_CH15, HAL_HPDMA1_CH15) != HAL_OK)
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

  if (HAL_DMA_SetConfigDirectXfer(&hHPDMA1_CH15, &xfer_cfg) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_DMA_RegisterXferCpltCallback(&hHPDMA1_CH15, hpdma1ch15_ping_to_bramab_tc_cb) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_DMA_RegisterXferErrorCallback(&hHPDMA1_CH15, hpdma1ch15_error_cb) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the interruption for HPDMA1_CH15 */
  HAL_CORTEX_NVIC_SetPriority(HPDMA1_CH15_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HPDMA1_CH15_IRQn);

  return &hHPDMA1_CH15;
}

/**
  * @brief  DeInitialize the hpdma1_ch15 (configuration 1) through HAL layer.
  */
void mx_hpdma1_ch15_deinit(void)
{
  (void)HAL_DMA_DeInit(&hHPDMA1_CH15);
}

/**
  * @brief  Get the HPDMA1_CH15 object.
  */
hal_dma_handle_t *mx_hpdma1_ch15_gethandle(void)
{
  return &hHPDMA1_CH15;
}

/******************************************************************************/
/* HPDMA1 channel 0 interrupt */
/******************************************************************************/
void HPDMA1_CH15_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hHPDMA1_CH15);
}

void hpdma1ch15_ping_to_bramab_tc_cb(hal_dma_handle_t *hdma)
{
  end_of_copy_ping_to_bramab = 1;
}

void hpdma1ch15_error_cb(hal_dma_handle_t *hdma)
{
  while(1);
}