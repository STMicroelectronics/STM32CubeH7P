/**
  ******************************************************************************
  * @file           : mx_spi5.c
  * @brief          : SPI5 Peripheral initialization
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
#include "mx_spi5.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_spi_handle_t hSPI5;

/******************************************************************************/
/* Exported functions for SPI in HAL layer */
/******************************************************************************/
hal_spi_handle_t *mx_spi5_init(void)
{
  hal_spi_config_t spi_config;

  if (HAL_SPI_Init(&hSPI5, HAL_SPI5) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_SPI5_EnableClock();

  if (HAL_RCC_SPI45_SetKernelClkSource(HAL_RCC_SPI45_CLK_SRC_PCLK2) != HAL_OK)
  {
    return NULL;
  }

  spi_config.mode = HAL_SPI_MODE_SLAVE;
  spi_config.direction = HAL_SPI_DIRECTION_FULL_DUPLEX;
  spi_config.data_width = HAL_SPI_DATA_WIDTH_8_BIT;
  spi_config.clock_polarity = HAL_SPI_CLOCK_POLARITY_LOW;
  spi_config.clock_phase = HAL_SPI_CLOCK_PHASE_1_EDGE;
  spi_config.baud_rate_prescaler = HAL_SPI_BAUD_RATE_PRESCALER_2;
  spi_config.first_bit = HAL_SPI_MSB_FIRST;
  spi_config.nss_pin_management = HAL_SPI_NSS_PIN_MGMT_INTERNAL;

  if (HAL_SPI_SetConfig(&hSPI5, &spi_config) != HAL_OK)
  {
    return NULL;
  }

  hal_spi_crc_config_t spi_crc_config;

  spi_crc_config.crc_polynomial = 263;
  spi_crc_config.crc_length = HAL_SPI_CRC_LENGTH_16_BIT;
  spi_crc_config.crc_tx_init_pattern = HAL_SPI_CRC_TX_INIT_PATTERN_ALL_ZERO;
  spi_crc_config.crc_rx_init_pattern = HAL_SPI_CRC_RX_INIT_PATTERN_ALL_ZERO;

  if (HAL_SPI_SetConfigCRC(&hSPI5, &spi_crc_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_SPI_EnableCRC(&hSPI5) != HAL_OK)
  {
    return NULL;
  }

  /* ### SPI5 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOH_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PH6     ------>   SPI5_SCK
       PH7     ------>   SPI5_MISO
       PH8     ------>   SPI5_MOSI
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_5;
  HAL_GPIO_Init(HAL_GPIOH, HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7 | HAL_GPIO_PIN_8, &gpio_config);

  /* Enable the interrupt for SPI */
  HAL_CORTEX_NVIC_SetPriority(SPI5_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(SPI5_IRQn);

  return &hSPI5;
}

void mx_spi5_deinit(void)
{
  /* Disable the interrupt for SPI */
  HAL_CORTEX_NVIC_DisableIRQ(SPI5_IRQn);

  (void)HAL_SPI_DeInit(&hSPI5);

  HAL_RCC_SPI5_Reset();

  HAL_RCC_SPI5_DisableClock();

  /* De-initialize all GPIOH pins associated with SPI5 */
  HAL_GPIO_DeInit(HAL_GPIOH, HAL_GPIO_PIN_6 | HAL_GPIO_PIN_7 | HAL_GPIO_PIN_8);
}

hal_spi_handle_t *mx_spi5_gethandle(void)
{
  return &hSPI5;
}

/******************************************************************************/
/*                           SPI5 global interrupt                            */
/******************************************************************************/
void SPI5_IRQHandler(void)
{
  HAL_SPI_IRQHandler(&hSPI5);
}
