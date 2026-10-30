/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
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
#include "example.h"
#include "mx_filex_app.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
void (*UserApp)(void);
uint32_t JumpAddress;
volatile uint8_t ExtiDetected = 0;

/* Private functions prototype -----------------------------------------------*/
static void CallUserApp(uint32_t Address);

/** ########## Step 1 ##########
  * Initializes FileX.
  */
/* The init of the sd instance is triggered by the applicative code */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_INIT_OK;

  if (HAL_GPIO_ReadPin(MX_STATUS_BUTTON_PORT, MX_STATUS_BUTTON_PIN) == HAL_GPIO_PIN_SET)
  {
    ExtiDetected = 0;
    /* Initialize the filex system component */
    if (app_filex_init() != 0)
    {
      return_status = EXEC_STATUS_ERROR;
    }
  }
  else
  {
    ExtiDetected = 1;
    CallUserApp(USER_APP_ADDRESS);
  }

  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_OK;

  if (app_filex_process() != 0)
  {
    return_status = EXEC_STATUS_ERROR;
  }
  return return_status;
} /* end app_process */


/** Calls the user application.
  * param  address: address of the user application.
  * retval None
  */
static void CallUserApp(uint32_t Address)
{
  /* Print info about the to be loaded App*/
  PRINTF("[INFO] **********************************\n");
  PRINTF("[INFO] *** In Application Programming ***\n");
  PRINTF("[INFO] **********************************\n");
  PRINTF("[INFO] Loading app from 0x%08" PRIX32 " (SP:0x%08" PRIX32 " PC:0x%08" PRIX32 ")\n",
         (uint32_t)Address, *(uint32_t *)Address, *(uint32_t *)(Address + 4));
  PRINTF("[INFO] **********************************\n");
  /* Check App signature from loading address, the SP must be in the range of the RAM used by the application */
  /* Please note that this assumes that the RAM region starts at RAM_START_ADDRESS, otherwise change it accordingly. */
  if (((*(__IO uint32_t *)Address) & RAM_RANGE_MASK) != RAM_START_ADDRESS)
  {
    PRINTF("[INFO] Invalid signature (SP)\n");
    while (1)
    {
    }
  }

  /* De-initialize all initialized peripherals */
  mx_gpio_status_led_deinit();
  mx_example_sd_deinit();

  /* Disable HAL and HAL timer (TIM6) */
  HAL_SuspendTick();
  HAL_DeInit();
  mx_rcc_deinit();

  /* Disable SysTick interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(SysTick_IRQn);

  /* Clear any pending SysTick interrupt */
  HAL_CORTEX_NVIC_ClearPendingIRQ(SysTick_IRQn);

  /* Set SP and jump to PC */
  JumpAddress = *(__IO uint32_t *)(Address + 4);
  UserApp = (void (*)(void)) JumpAddress;
  __set_MSP(*(__IO uint32_t *) Address);
  UserApp();
}

/** ########## Step 5 ##########
  * Deinitializes the SD instance before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  mx_example_sd_deinit();
  PRINTF("[INFO] Step 6: Deinitializes SD instance\n");
  return EXEC_STATUS_OK;

} /* end app_deinit */
