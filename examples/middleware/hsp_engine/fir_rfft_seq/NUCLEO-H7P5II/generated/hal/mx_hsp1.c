/**
  ******************************************************************************
  * @file           : mx_hsp1.c
  * @brief          : HSP1 Peripheral initialization
  ******************************************************************************
  * @attention
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
#include "mx_hsp1.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/
static hal_hsp_handle_t hHSP1;

/******************************************************************************/
/* Exported functions for HSP1 in HAL layer (SW instance MyHSP_1) */
/******************************************************************************/
hal_hsp_handle_t *mx_hsp1_hal_init(void)
{
  HAL_RCC_HSP1_EnableClock();

  if (HAL_HSP_Init(&hHSP1, HAL_HSP1) != HAL_OK)
  {
    return NULL;
  }

  /* Enable HSP interrupt */
  HAL_CORTEX_NVIC_SetPriority(HSP1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HSP1_IRQn);

  return &hHSP1;
}

void mx_hsp1_hal_deinit(void)
{
  /* Disable the interruption for HSP */
  HAL_CORTEX_NVIC_DisableIRQ(HSP1_IRQn);

  HAL_HSP_DeInit(&hHSP1);

  HAL_RCC_HSP1_Reset();

  HAL_RCC_HSP1_DisableClock();
}

hal_hsp_handle_t *mx_hsp1_hal_gethandle(void)
{
  return &hHSP1;
}

/******************************************************************************/
/*                     HSP global non-secure interrupt                    */
/******************************************************************************/
void HSP1_IRQHandler(void)
{
  HAL_HSP_IRQHandler(&hHSP1);
}
