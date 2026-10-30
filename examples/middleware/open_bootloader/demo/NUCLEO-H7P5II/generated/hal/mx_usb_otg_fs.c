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
static hal_pcd_handle_t hUSB_OTG_FS_PCD;

/******************************************************************************/
/* Exported functions for USB_OTG_FS DEVICE (PCD) in HAL layer */
/******************************************************************************/

hal_pcd_handle_t *mx_usb_otg_fs_device_init(void)
{
  hal_pcd_config_t pcd_config;

  /* Configure gh_pcd_USB_OTG_FS */
  if (HAL_PCD_Init(&hUSB_OTG_FS_PCD, HAL_PCD_OTG_FS) != HAL_OK)
  {
    return NULL;
  }

  /* Peripheral USB clock enable */
  HAL_RCC_USBOTGFS_EnableClock();

  if (HAL_RCC_USBOTGFS_SetKernelClkSource(HAL_RCC_USBOTGFS_CLK_SRC_HSI48) != HAL_OK)
  {
    return NULL;
  }

  pcd_config.phy_interface = HAL_PCD_PHY_EMBEDDED_FS;
  pcd_config.pcd_speed = HAL_PCD_SPEED_FS;
  pcd_config.vbus_sensing_enable = HAL_PCD_VBUS_SENSE_DISABLED;

  pcd_config.sof_enable = HAL_PCD_SOF_DISABLED;
  pcd_config.battery_charging_enable = HAL_PCD_BCD_DISABLED;
  pcd_config.lpm_enable = HAL_PCD_LPM_DISABLED;

  HAL_PCD_SetConfig(&hUSB_OTG_FS_PCD, &pcd_config);

  HAL_PCD_SetRxFiFoSize(&hUSB_OTG_FS_PCD, 0x80);
  HAL_PCD_SetTxFiFoSize(&hUSB_OTG_FS_PCD,0x0, 0x80);

  /* Enable the interruption for PCD */
  HAL_CORTEX_NVIC_SetPriority(USB_OTG_FS_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(USB_OTG_FS_IRQn);

  return &hUSB_OTG_FS_PCD;
}
void mx_usb_otg_fs_device_deinit(void)
{
  /* Deinititialize hUSB_OTG_FS_PCD */
  HAL_PCD_DeInit(&hUSB_OTG_FS_PCD);

  /* No GPIO de-initialization required for USB_OTG_FS.DEVICE */
}
/**
  * @brief Get USB PCD handle
  * @param None
  * @retval USB PCD handle
  */
hal_pcd_handle_t *mx_usb_otg_fs_device_gethandle(void)
{
  return &hUSB_OTG_FS_PCD;
}

/******************************************************************************/
/*                     Interruption and Exception Handlers                    */
/******************************************************************************/
void USB_OTG_FS_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hUSB_OTG_FS_PCD);
}
