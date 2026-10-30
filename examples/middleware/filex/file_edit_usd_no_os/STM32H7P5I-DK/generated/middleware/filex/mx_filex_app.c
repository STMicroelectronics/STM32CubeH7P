/**
  ******************************************************************************
  * @file           : mx_filex_app.c
  * @brief          : FileX applicative file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_filex_license.md file
  * in the same directory as the generated code.
  * If no mx_filex_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "mx_filex_app.h"

/* Private variables ---------------------------------------------------------*/
static FX_MEDIA fx_media_0;
static FX_FILE  fx_file_0;
static ULONG fx_media_0_buffer[512 / sizeof(ULONG)];

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  Application FileX Initialization.
  * @param  None
  * @retval UINT: FX_SUCCESS on success, error code otherwise
  */
UINT app_filex_init(VOID)
{
  UINT status = FX_SUCCESS;

  fx_system_initialize();

  PRINTF("[INFO] Step 1: Initializing FileX...\n");

  VOID *fx_driver_0_info_ptr = mx_filex_driver_0_get_ctx();

  status = fx_media_open(&fx_media_0, volume_name_0, mx_filex_driver_0, fx_driver_0_info_ptr,
                         (VOID *)fx_media_0_buffer, sizeof(fx_media_0_buffer));

  if (status != FX_SUCCESS)
  {
    PRINTF("[ERROR] error open\n");
    return status;
  }

  PRINTF("[INFO] Step 2: Media opened successfully\n");

  return status;
}

UINT app_filex_process(VOID)
{
  UINT status = FX_SUCCESS;
  ULONG bytes_read;
  CHAR read_buffer[32];
  CHAR data[] = "This is FileX working on STM32";

  /** ########## Step 3 ##########
    * Creates a file called STM32.TXT in the root directory.
    */
  status =  fx_file_create(&fx_media_0, "STM32.TXT");

  /* Check the create status.  */
  if (status != FX_SUCCESS)
  {
    /* Check for an already created status. This is expected on the
    second pass of this loop!  */
    if (status != FX_ALREADY_CREATED)
    {
      /* Create error, call error handler.  */
      return status;
    }
  }
  PRINTF("[INFO] Step 3: STM32.TXT file created in the root directory\n");

  /* Open the test file.  */
  status =  fx_file_open(&fx_media_0, &fx_file_0, "STM32.TXT", FX_OPEN_FOR_WRITE);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, call error handler.  */
    return status;
  }

  /* Seek to the beginning of the test file.  */
  status =  fx_file_seek(&fx_file_0, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, call error handler.  */
    return status;
  }

  /* Write a string to the test file.  */
  status =  fx_file_write(&fx_file_0, data, sizeof(data));

  /* Check the file write status.  */
  if (status != FX_SUCCESS)
  {
    /* Error writing to a file, call error handler.  */
    return status;
  }

  PRINTF("[INFO] Step 4: Write data to STM32.TXT\n");

  /* Close the test file.  */
  status =  fx_file_close(&fx_file_0);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler.  */
    return status;
  }

  status = fx_media_flush(&fx_media_0);

  /* Check the media flush  status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler.  */
    return status;
  }

  /** ########## Step 4 ##########
    * Initializes and performs reception from the SD card to the device.
    */
  /* Open the test file.  */
  status =  fx_file_open(&fx_media_0, &fx_file_0, "STM32.TXT", FX_OPEN_FOR_READ);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, call error handler.  */
    return status;
  }


  /* Seek to the beginning of the test file.  */
  status =  fx_file_seek(&fx_file_0, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, call error handler.  */
    return status;
  }

  /* Read the first 28 bytes of the test file.  */
  status =  fx_file_read(&fx_file_0, read_buffer, sizeof(data), &bytes_read);

  /* Check the file read status.  */
  if ((status != FX_SUCCESS) || (bytes_read != sizeof(data)))
  {
    /* Error reading file, call error handler.  */
    return status;
  }

  PRINTF("[INFO] Step 5: read_buffer read\n");

  /* Close the test file.  */
  status = fx_file_close(&fx_file_0);

  /* Check the file close status. */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler. */
    return status;
  }

  /* Close the media.  */
  status = fx_media_close(&fx_media_0);

  PRINTF("[INFO] Step 6: Media closed successfully\n");

  return status;
}
