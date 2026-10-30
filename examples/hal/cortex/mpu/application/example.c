/**
  *********************************************************************************
  * file           : example.c
  * brief          : use the Cortex-MPU to configure a memory region as privileged read-only,
  *                  perform an authorized read,
  *                  and handle a memory fault triggered by an unauthorized write access.

  *********************************************************************************
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
#include <string.h> /* importing memcmp and memset functions */
#include <setjmp.h> /* Used for saving and restoring program context with setjmp() and longjmp() */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
  * 32-byte buffer placed in the ".mpu_ro" section
  * with 32-byte alignment for MPU-protected memory.
  */
#if defined(__ICCARM__)
#pragma location = ".ram_ro"
__root volatile char PrivilegedReadOnlyArray[32] = "DataBuffer";
#else
__attribute__((section(".ram_ro"), aligned(32)))
volatile char PrivilegedReadOnlyArray[32] = "DataBuffer";
#endif /* defined(__ICCARM__) */

/** Longjmp buffer used to save the program state with setjmp.
  * longjmp() restores the set of registers pointed to by this buffer.
  */
jmp_buf MpuJmpBuf;
/* Private functions prototype -----------------------------------------------*/

/** ########## Step 1 ##########
  * Initializes the Cortex MPU to ensure proper memory protection before running the application.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  if (mx_example_cortex_init() != SYSTEM_OK)
  {
    return_status = EXEC_STATUS_ERROR;
    PRINTF("[ERROR] Step 1: CORTEX initialization ERROR.\n");
  }
  else
  {
    PRINTF("[INFO] Step 1: CORTEX initialization COMPLETED.\n");
    return_status = EXEC_STATUS_INIT_OK;
  }
  return return_status;
} /* end app_init */


app_status_t app_process(void)
{
  uint8_t write_value = 0xAA; /* arbitrary value easy to spot in memory if the write succeeds */

  /** ########## Step 2 ##########
    * Triggers authorized read access to the privileged read-only region.
    */
  (void)PrivilegedReadOnlyArray[0];
  PRINTF("[INFO] Step 2: Reads from the privileged read-only region.\n");

  /** ########## Step 3 ##########
    * Attempts unauthorized write access to the privileged read-only region.
  */
  PRINTF("[INFO] Step 3: Attempts an unauthorized write to the privileged read-only region.\n");
  /* Save execution context to allow recovery after a fault */
  if (setjmp(MpuJmpBuf) == 0)
  {
    /* Try to write to the protected region (this causes a memory fault and trigs MemManage_Handler()) */
    memcpy((void *)PrivilegedReadOnlyArray, &write_value, 1);

    /* If we get here, no fault was caught by the MPU */
    PRINTF("[ERROR] Write access did NOT trigger a memory fault as expected.\n");
    return EXEC_STATUS_ERROR;
  }
  else
  {
    /* The longjmp in the fault handler restored the context with the return value 1 */
    PRINTF("[INFO] Write access violation detected (caught by MPU).\n");
    return EXEC_STATUS_OK;
  }
} /* end app_process */


/** ########## Step 4 ##########
  * Deinitializes the CORTEX before leaving the scenario.
  */
app_status_t app_deinit(void)
{
  mx_example_cortex_deinit();

  PRINTF("[INFO] Step 4: CORTEX deinitialization COMPLETED.\n");

  return EXEC_STATUS_OK;
}


/**
  * brief: Memory Management Fault Handler.
  * This handler is called when an MPU access violation occurs.
  * It sets the violation flag and prints a message.
  */
void MemManage_Handler(void)
{
  /* Use longjmp to return to the saved context (setjmp) */
  longjmp(MpuJmpBuf, 1);

}

