/**
  ******************************************************************************
  * @file           : mx_comp3.h
  * @brief          : Header for mx_comp3.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_COMP3_H
#define MX_COMP3_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for COMP in HAL layer */
/******************************************************************************/
/**
  * @brief mx_comp3 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_comp_handle_t *mx_comp3_init(void);

/**
  * @brief  De-initialize comp3 instance and return it.
  */
void mx_comp3_deinit(void);

/**
  * @brief  Get the COMP3 object.
  * @retval Pointer on the COMP3 Handle
  */
hal_comp_handle_t *mx_comp3_gethandle(void);

/******************************************************************************/
/*                     COMP3 interrupt through EXTI line                      */
/******************************************************************************/
void COMP3_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_COMP3_H */
