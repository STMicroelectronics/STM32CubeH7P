/**
  ******************************************************************************
  * @file           : mx_hal_def.h
  * @brief          : Exporting peripherals initialization
  *                   Include entry for the target folder to the application.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_HAL_DEF_H
#define MX_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_cortex_mpu.h"
#include "mx_cortex_nvic.h"
#include "mx_rcc.h"
#include "mx_gpio_default.h"
#include "mx_hpdma1_ch0.h"
#include "mx_dma_nodes.h"
#include "mx_pwr.h"
#include "mx_queue.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

/* *********************************************************** */
/*        HPDMA1_CH0_MyDMA_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_Hpdma1_ch0_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyDMA_1
  *                   mx_example_dma
  * @retval hal_dma_handle_t Pointer on the handle on the HPDMA1_CH0 instance
  */
#define mydma_1_init mx_hpdma1_ch0_hal_init

#define mx_example_dma_init mx_hpdma1_ch0_hal_init


/* *********************************************************** */
/*        CORTEX_MPU_MyCORTEX_MPU_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_cortex_mpu_hal with HAL layer
  *         Name of the User label:
  *                   MyCORTEX_MPU_1
  * @retval system_status_t Value based on the system_status_t
  */
#define mycortex_mpu_1_init mx_cortex_mpu_hal_init


/* *********************************************************** */
/*        gpio_default_MyGPIO_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_gpio_default_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyGPIO_1
  *                   mx_gpio_status_led
  * @retval hal_gpio_handle_t Pointer on the handle on the gpio_default instance
  */
#define mygpio_1_init mx_gpio_default_cfg1_hal_init

#define mx_gpio_status_led_init mx_gpio_default_cfg1_hal_init


/* *********************************************************** */
/*        RCC_MyRCC_1: aliases for initialization functions */
/* *********************************************************** */

/**
  * @brief  Initialize the mx_rcc_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyRCC_1
  * @retval hal_rcc_handle_t Pointer on the handle on the RCC instance
  */
#define myrcc_1_init mx_rcc_cfg1_hal_init


/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_icache_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyICACHE_1
  */
#define myicache_1_deinit mx_icache_cfg1_hal_deinit


/* *********************************************************** */
/*        HPDMA1_CH0_MyDMA_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_hpdma1_ch0_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyDMA_1
  *                   mx_example_dma
  */
#define mydma_1_deinit mx_hpdma1_ch0_cfg1_hal_deinit

#define mx_example_dma_deinit mx_hpdma1_ch0_hal_deinit


/* *********************************************************** */
/*        gpio_default_MyGPIO_1: aliases for De-Initialization functions */
/* *********************************************************** */

/**
  * @brief  De-Initialize the mx_gpio_default_cfg1_hal with HAL layer
  *         Name of the User label:
  *                   MyGPIO_1
  *                   mx_gpio_status_led
  */
#define mygpio_1_deinit mx_gpio_default_cfg1_hal_deinit

#define mx_gpio_status_led_deinit mx_gpio_default_cfg1_hal_deinit


/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

/* *********************************************************** */
/*        GPIO: aliases for get EXTI object functions */
/* *********************************************************** */

/* *********************************************************** */
/*        ICACHE_MyICACHE_1: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for ICACHE
  *         Name of the User label:
  *                   MyICACHE_1
  * @retval hal_icache_handle_t Pointer on the handle on the ICACHE instance
  */
#define myicache_1_gethandle mx_icache_hal_gethandle

/* *********************************************************** */
/*        HPDMA1_CH0_MyDMA_1: aliases for get handle functions */
/* *********************************************************** */

/**
  * @brief  Get the HAL handle for HPDMA1_CH0
  *         Name of the User label:
  *                   MyDMA_1
  *                   mx_example_dma
  * @retval hal_dma_handle_t Pointer on the handle on the HPDMA1_CH0 instance
  */
#define mydma_1_gethandle mx_hpdma1_ch0_hal_gethandle

#define mx_example_dma_gethandle mx_hpdma1_ch0_hal_gethandle


/* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
