/**
  ******************************************************************************
  * file           : example.c
  * brief          : Generate random numbers with multiple RNG configurations
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
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RNG_NUMBERS   8U      /* Number of 32-bit random numbers that will be generated */
#define RNG_GENERATION_TIMEOUT   10U            /* Timeout for generation in millisecond */
#define RNG_CUSTOM_GENERATION_TIMEOUT   500U    /* Longer timeout for custom RNG configuration */
/* CR register field values */
#define RNG_CAND_NIST_CR_CONFIG1_VALUE   0x84U
#define RNG_CAND_NIST_CR_CONFIG2_VALUE   0x00U
#define RNG_CAND_NIST_CR_CONFIG3_VALUE   0x0FU

/* NSCR register field values */
#define RNG_CAND_NIST_NSCR_OSC1_VALUE    0x07U
#define RNG_CAND_NIST_NSCR_OSC2_VALUE    0x07U
#define RNG_CAND_NIST_NSCR_OSC3_VALUE    0x07U

#define RNG_CAND_GERMANBSI_CR_CONFIG1_VALUE        0x83U
#define RNG_CAND_GERMANBSI_CR_CONFIG2_VALUE        0x00U
#define RNG_CAND_GERMANBSI_CR_CONFIG3_VALUE        0x0FU

/* NSCR register field values */
#define RNG_CAND_GERMANBSI_NSCR_OSC1_VALUE         0x07U
#define RNG_CAND_GERMANBSI_NSCR_OSC2_VALUE         0x07U
#define RNG_CAND_GERMANBSI_NSCR_OSC3_VALUE         0x07U
#define VALID_CUSTOM_CONFIG1_VALUE                 1U
#define VALID_CUSTOM_CONFIG2_VALUE                 2U
#define VALID_CUSTOM_CONFIG3_VALUE                 3U
#define RNG_CUSTOM_CLOCK_DIVIDER_VALUE             HAL_RNG_CLOCK_DIVIDER_BY_1024
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
hal_rng_handle_t *pRNG;  /* pointer referencing the RNG handle from the generated code */
uint32_t RandomNumbers[RNG_NUMBERS] = {0}; /* array to store the generated random numbers */
hal_rng_config_t rng_config;
/* Private functions prototype -----------------------------------------------*/
static app_status_t SetHealthFactorConfigs(uint32_t htcr1, uint32_t htcr2, uint32_t htcr3)
{
  HAL_RNG_SetHealthFactorConfig(pRNG, HAL_RNG_HTCR1, htcr1);
  HAL_RNG_SetHealthFactorConfig(pRNG, HAL_RNG_HTCR2, htcr2);
  HAL_RNG_SetHealthFactorConfig(pRNG, HAL_RNG_HTCR3, htcr3);

  return EXEC_STATUS_OK;
}

static app_status_t GenerateRandomNumbers(const char *step_label, const char *configuration_name,
                                          uint32_t timeout)
{
  if (HAL_RNG_GenerateRandomNumber(pRNG, RandomNumbers, RNG_NUMBERS, timeout) != HAL_OK)
  {
    if (HAL_RNG_GetLastErrorCodes(pRNG) != HAL_RNG_ERROR_SEED)
    {
      return EXEC_STATUS_ERROR;
    }

    if (HAL_RNG_RecoverSeedError(pRNG) != HAL_OK)
    {
      return EXEC_STATUS_ERROR;
    }

    if (HAL_RNG_GenerateRandomNumber(pRNG, RandomNumbers, RNG_NUMBERS, timeout) != HAL_OK)
    {
      return EXEC_STATUS_ERROR;
    }
  }

  for (uint32_t i = 0; i < RNG_NUMBERS; i++)
  {
    PRINTF("[INFO] Step %s (%s):%" PRId32 " - Generate 32-bit random number: 0x%" PRIx32 ".\n",
           step_label, configuration_name, i + 1, RandomNumbers[i]);
  }
  return EXEC_STATUS_OK;
}

/** ########## Step 1 ##########
  * The init of the RNG instance is triggered by the applicative code.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pRNG = mx_default_rng_init();

  if (pRNG != NULL)
  {
    PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }

  return return_status;
} /* end app_init */


/** ########## Step 2 ##########
  * Generates random numbers using multiple RNG configurations with
  * additional health tests enabled.
  */
app_status_t app_process(void)
{
  /* Step 2.1: NIST Candidate configuration + additional health tests */
  if (SetHealthFactorConfigs(RNG_HTCRx_VALUE,
                             RNG_HTCRx_VALUE,
                             RNG_HTCRx_VALUE) != EXEC_STATUS_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  if (GenerateRandomNumbers("2.1", "NIST configuration + additional health", RNG_GENERATION_TIMEOUT)
      != EXEC_STATUS_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  /* Step 2.2: German BSI configuration + additional health tests */
  (void)memset(RandomNumbers, 0, sizeof(RandomNumbers));
  if (HAL_RNG_SetCandidateGermanBSIConfig(pRNG) != HAL_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  if (SetHealthFactorConfigs(0x0000FFFFU,
                             0x0000FFFFU,
                             0x0000FFFFU) != EXEC_STATUS_OK)
  {
    return EXEC_STATUS_ERROR;
  }
  if (GenerateRandomNumbers("2.2", "German BSI configuration + additional health", RNG_GENERATION_TIMEOUT)
      != EXEC_STATUS_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  /* Step 2.3: Custom configuration + additional health tests */
  (void)memset(RandomNumbers, 0, sizeof(RandomNumbers));

  /* Modify RNG parameters with custom configurations */
  rng_config.config_1              = 0x1FU;
  rng_config.config_2              = 0x00U;
  rng_config.config_3              = 0x0DU;
  rng_config.clock_divider         = HAL_RNG_CLOCK_DIVIDER_BY_1;
  rng_config.standard              = HAL_RNG_CUSTOM;
  rng_config.clock_error_detection = HAL_RNG_CLOCK_ERROR_DETECTION_ENABLED;
  rng_config.health_test           = 0xAAC7U;
  rng_config.noise_src.osc_1_src   = HAL_RNG_OSCILLATOR_SOURCE_1
                                     | HAL_RNG_OSCILLATOR_SOURCE_2
                                     | HAL_RNG_OSCILLATOR_SOURCE_3;
  rng_config.noise_src.osc_2_src   = HAL_RNG_OSCILLATOR_SOURCE_1
                                     | HAL_RNG_OSCILLATOR_SOURCE_2
                                     | HAL_RNG_OSCILLATOR_SOURCE_3;
  rng_config.noise_src.osc_3_src   = HAL_RNG_OSCILLATOR_SOURCE_1
                                     | HAL_RNG_OSCILLATOR_SOURCE_2
                                     | HAL_RNG_OSCILLATOR_SOURCE_3;

  if (HAL_RNG_SetConfig(pRNG, &rng_config) != HAL_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  if (SetHealthFactorConfigs(RNG_HTCRx_VALUE,
                             RNG_HTCRx_VALUE,
                             RNG_HTCRx_VALUE) != EXEC_STATUS_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  if (GenerateRandomNumbers("2.3", "Custom configuration + additional health",
                            RNG_CUSTOM_GENERATION_TIMEOUT) != EXEC_STATUS_OK)
  {
    return EXEC_STATUS_ERROR;
  }

  return EXEC_STATUS_OK;
} /* end app_process */


/** ########## Step 3 ##########
  * Deinitializes the RNG instance before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  PRINTF("[INFO] Step 3: Device de-init.\n");
  mx_default_rng_deinit();

  return EXEC_STATUS_OK;
} /* end app_deinit */
