/**
  ******************************************************************************
  * file           : example.c
  * brief          : HASH Integrity SHA2-512 with HAL API.
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
#define HASH_TIMEOUT_MS         1000U
#define HASH_OUTPUT_BUFFER_SIZE 64U
#define MESSAGE_SIZE            145U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_hash_handle_t *pHASH;

/** Extract from NIST Publication: SHA Test Vectors for Hashing Byte-Oriented Messages SHA2_512LongMsg.rsp
  *
  * Len = 1160
  * Msg = 664ef2e3a7059daf1c58caf52008c5227e85cdcb83b4c59457f02c508d4f4f69
  * f826bd82c0cffc5cb6a97af6e561c6f96970005285e58f21ef6511d26e709889a7e513
  * c434c90a3cf7448f0caeec7114c747b2a0758a3b4503a7cf0c69873ed31d94dbef2b7b
  * 2f168830ef7da3322c3d3e10cafb7c2c33c83bbf4c46a31da90cff3bfd4ccc6ed4b310
  * 758491eeba603a76
  * MD = edd9ade72168eef57363694b2cf68eb5eed9e17ed6c5b2c607b755f024e30d7
  * 8d5b0612880e5222a7caea68a124c4bebd2a944fc7fc10bc14de1102b2852fbb4
  */
/* Message to be computed */
uint8_t Message[MESSAGE_SIZE] =
{
  0x66, 0x4e, 0xf2, 0xe3, 0xa7, 0x05, 0x9d, 0xaf, 0x1c, 0x58, 0xca, 0xf5, 0x20, 0x08, 0xc5, 0x22,
  0x7e, 0x85, 0xcd, 0xcb, 0x83, 0xb4, 0xc5, 0x94, 0x57, 0xf0, 0x2c, 0x50, 0x8d, 0x4f, 0x4f, 0x69,
  0xf8, 0x26, 0xbd, 0x82, 0xc0, 0xcf, 0xfc, 0x5c, 0xb6, 0xa9, 0x7a, 0xf6, 0xe5, 0x61, 0xc6, 0xf9,
  0x69, 0x70, 0x00, 0x52, 0x85, 0xe5, 0x8f, 0x21, 0xef, 0x65, 0x11, 0xd2, 0x6e, 0x70, 0x98, 0x89,
  0xa7, 0xe5, 0x13, 0xc4, 0x34, 0xc9, 0x0a, 0x3c, 0xf7, 0x44, 0x8f, 0x0c, 0xae, 0xec, 0x71, 0x14,
  0xc7, 0x47, 0xb2, 0xa0, 0x75, 0x8a, 0x3b, 0x45, 0x03, 0xa7, 0xcf, 0x0c, 0x69, 0x87, 0x3e, 0xd3,
  0x1d, 0x94, 0xdb, 0xef, 0x2b, 0x7b, 0x2f, 0x16, 0x88, 0x30, 0xef, 0x7d, 0xa3, 0x32, 0x2c, 0x3d,
  0x3e, 0x10, 0xca, 0xfb, 0x7c, 0x2c, 0x33, 0xc8, 0x3b, 0xbf, 0x4c, 0x46, 0xa3, 0x1d, 0xa9, 0x0c,
  0xff, 0x3b, 0xfd, 0x4c, 0xcc, 0x6e, 0xd4, 0xb3, 0x10, 0x75, 0x84, 0x91, 0xee, 0xba, 0x60, 0x3a,
  0x76
};

/* The expected message of the compute process */
uint8_t ExpectedHash[HASH_OUTPUT_BUFFER_SIZE] =
{
  0xed, 0xd9, 0xad, 0xe7, 0x21, 0x68, 0xee, 0xf5, 0x73, 0x63, 0x69, 0x4b, 0x2c, 0xf6, 0x8e, 0xb5,
  0xee, 0xd9, 0xe1, 0x7e, 0xd6, 0xc5, 0xb2, 0xc6, 0x07, 0xb7, 0x55, 0xf0, 0x24, 0xe3, 0x0d, 0x78,
  0xd5, 0xb0, 0x61, 0x28, 0x80, 0xe5, 0x22, 0x2a, 0x7c, 0xae, 0xa6, 0x8a, 0x12, 0x4c, 0x4b, 0xeb,
  0xd2, 0xa9, 0x44, 0xfc, 0x7f, 0xc1, 0x0b, 0xc1, 0x4d, 0xe1, 0x10, 0x2b, 0x28, 0x52, 0xfb, 0xb4
};

/* Message to be hashed by the accumulation process */
uint8_t Msg65Input[65] __attribute__((aligned(128))) =
{
  0x52, 0x43, 0x31, 0x5f, 0x53, 0x6f, 0x75, 0x72, 0x63, 0x65, 0x61, 0x50, 0x72, 0x6f, 0x6a, 0x65,
  0x63, 0x74, 0x5f, 0x53, 0x46, 0x55, 0x61, 0x45, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x73, 0x61,
  0x53, 0x54, 0x4d, 0x33, 0x32, 0x32, 0x78, 0x47, 0x2d, 0x45, 0x56, 0x41, 0x4c, 0x61, 0x45, 0x57,
  0x41, 0x52, 0x4d, 0x61, 0x53, 0x54, 0x4d, 0x33, 0x32, 0x32, 0x78, 0x47, 0x5f, 0x45, 0x56, 0x41,
  0x4c
};

/* The expected message of the accumulation process */
uint8_t Msg65Expected [HASH_OUTPUT_BUFFER_SIZE] =
{
  0x62, 0xfb, 0x87, 0x98, 0xbb, 0x5d, 0x7b, 0x40, 0x99, 0x7f, 0x06, 0x5b, 0x93, 0x52, 0x74, 0xf3,
  0xfe, 0x18, 0xc6, 0xd2, 0x64, 0xbd, 0x73, 0x2e, 0x82, 0x1a, 0xba, 0xfc, 0x6b, 0xd0, 0xf2, 0xbe,
  0xd7, 0x85, 0x28, 0xe4, 0x71, 0xd7, 0x21, 0x6c, 0x99, 0x5c, 0x42, 0x16, 0x57, 0x22, 0xf1, 0xb8,
  0x5d, 0x69, 0xb5, 0xf4, 0x4c, 0x21, 0x38, 0x82, 0xd7, 0xee, 0x9d, 0xb3, 0xe7, 0xc3, 0xdf, 0x6a
};

/* Output of accumulation message */
uint8_t SHA512_Output[HASH_OUTPUT_BUFFER_SIZE] = {0};
uint32_t SHA512_OutputSize;

/* Computed HASH message */
uint8_t computed_hash_message[HASH_OUTPUT_BUFFER_SIZE] = {0};
uint32_t ComputedSize;

/* Private functions prototype -----------------------------------------------*/


/** ########## Step 1 ##########
  * Initializes the HASH instance.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  pHASH = mx_example_hash_init();
  if (pHASH != NULL)
  {
    PRINTF("[INFO] Step 1: HASH initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }
  else
  {
    PRINTF("[ERROR] Step 1: HASH initialization ERROR.\n");
    return_status = EXEC_STATUS_ERROR;
  }

  return return_status;
} /* end app_init */


/** ########## Step 2 ##########
  * Demonstrates how to digest a message, using SHA2-512 algorithm.
  * For a single buffer to be hashed, HAL_HASH_Compute() is called,
  * and for multi-buffer input, HAL_HASH_Update() and HAL_HASH_Finish() are called.
  * This step is scheduled as follows:
  * Step 2.1: Computes and verifies the HASH message.
  * Step 2.2: Updates and verifies the HASH message of multi-buffer.
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /** ########## Step 2.1 ##########
    * Computes and verifies the HASH message.
    */

  /* Compute the message */
  if (HAL_HASH_Compute(pHASH, Message, MESSAGE_SIZE,
                       computed_hash_message, HASH_OUTPUT_BUFFER_SIZE, &ComputedSize,
                       HASH_TIMEOUT_MS) != HAL_OK)
  {
    goto _app_process_exit;
  }

  /* Verify the computed hash message */
  if (memcmp(computed_hash_message, ExpectedHash, HASH_OUTPUT_BUFFER_SIZE) != 0U)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 2.1: HASH message compute and verification COMPLETED.\n");

  /*Clears all data */
  memset((void *)computed_hash_message, 0U, sizeof(computed_hash_message));

  /** ########## Step 2.2 ##########
    * Updates and verifies the HASH message.
    */

  /* Start HASH update process in polling mode with the first input buffer */
  if (HAL_HASH_Update(pHASH, Msg65Input, 8, HASH_TIMEOUT_MS) != HAL_OK)
  {
    goto _app_process_exit;
  }

  /* HASH update process in polling mode with the second input buffer */
  if (HAL_HASH_Update(pHASH, Msg65Input + 8, 20, HASH_TIMEOUT_MS) != HAL_OK)
  {
    goto _app_process_exit;
  }

  /* HASH update process in polling mode with the third input buffer */
  if (HAL_HASH_Update(pHASH, Msg65Input + 28, 4, HASH_TIMEOUT_MS) != HAL_OK)
  {
    goto _app_process_exit;
  }

  /* HASH update process in polling mode with the third input buffer */
  if (HAL_HASH_Update(pHASH, Msg65Input + 32, 33, HASH_TIMEOUT_MS) != HAL_OK)
  {
    goto _app_process_exit;
  }

  /* Finish HASH update process */
  if (HAL_HASH_Finish(pHASH, SHA512_Output, HASH_OUTPUT_BUFFER_SIZE, &SHA512_OutputSize, HASH_TIMEOUT_MS) != HAL_OK)
  {
    goto _app_process_exit;
  }

  /* Verify the computed hash message */
  if (memcmp(SHA512_Output, Msg65Expected, HASH_OUTPUT_BUFFER_SIZE) != 0U)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 2.2: HASH message update and verification COMPLETED.\n");

  /* Clears all data */
  memset((void *)SHA512_Output, 0U, sizeof(SHA512_Output));

  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
} /* end app_process */


/** ########## Step 3 ##########
  * Deinitializes the HASH peripheral before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  mx_example_hash_deinit();

  PRINTF("[INFO] Step 3: HASH peripheral deinitialization COMPLETED.\n");

  return EXEC_STATUS_OK;
} /* end app_deinit */
