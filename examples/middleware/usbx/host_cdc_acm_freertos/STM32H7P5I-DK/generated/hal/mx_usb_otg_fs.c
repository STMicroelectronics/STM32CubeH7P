/**
  ******************************************************************************
  * @file           : mx_usb_otg_fs.c
  * @brief          : USB_OTG_FS Peripheral initialization
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
#include "mx_usb_otg_fs.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_hcd_handle_t hUSB_OTG_FS_HCD;

/******************************************************************************/
/* Exported functions for USB_OTG_FS HOST (HCD) in HAL layer */
/******************************************************************************/

hal_hcd_handle_t *mx_usb_otg_fs_host_init(void)
{
  hal_hcd_config_t hcd_config;

  /* Configure hUSB_OTG_FS_HCD */
  if (HAL_HCD_Init(&hUSB_OTG_FS_HCD, HAL_HCD_OTG_FS) != HAL_OK)
  {
    return NULL;
  }

  /* Peripheral USB clock enable */
  HAL_RCC_USBOTGFS_EnableClock();

  if (HAL_RCC_USBOTGFS_SetKernelClkSource(HAL_RCC_USBOTGFS_CLK_SRC_HSI48) != HAL_OK)
  {
    return NULL;
  }

  hcd_config.phy_interface = HAL_HCD_PHY_EMBEDDED_FS;
  hcd_config.hcd_speed = HAL_HCD_SPEED_FS;

  HAL_HCD_SetConfig(&hUSB_OTG_FS_HCD, &hcd_config);

  /* Enable the interruption for HCD */
  HAL_CORTEX_NVIC_SetPriority(USB_OTG_FS_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_6, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(USB_OTG_FS_IRQn);

  return &hUSB_OTG_FS_HCD;
}
void mx_usb_otg_fs_host_deinit(void)
{
  /* Deinititialize hUSB_OTG_FS_HCD */
  HAL_HCD_DeInit(&hUSB_OTG_FS_HCD);

  /* No GPIO de-initialization required for USB_OTG_FS.HOST */
}
/**
  * @brief Get USB HCD handle
  * @param None
  * @retval USB HCD handle
  */
hal_hcd_handle_t *mx_usb_otg_fs_host_gethandle(void)
{
  return &hUSB_OTG_FS_HCD;
}

/******************************************************************************/
/*                     Interruption and Exception Handlers                    */
/******************************************************************************/
void USB_OTG_FS_IRQHandler(void)
{
  HAL_HCD_IRQHandler(&hUSB_OTG_FS_HCD);
}
