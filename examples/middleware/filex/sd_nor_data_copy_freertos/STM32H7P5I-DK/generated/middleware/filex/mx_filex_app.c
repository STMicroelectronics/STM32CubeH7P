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

extern TaskHandle_t BackgroundTask;

/* Private variables ---------------------------------------------------------*/
static FX_MEDIA fx_media_0;
static ULONG fx_media_0_buffer[512 / sizeof(ULONG)];
static FX_MEDIA fx_media_1;
static __attribute__((aligned(32))) ULONG fx_media_1_buffer[512 / sizeof(ULONG)];
static FX_FILE  fx_file_0;
static FX_FILE  fx_file_1;

TaskHandle_t main_task;

/* Copy buffer */
static UCHAR file_copy_buffer[512];
static UCHAR sd_compare_buffer[512];
static UCHAR nor_compare_buffer[512];

/* Private function prototypes -----------------------------------------------*/
VOID fx_task_entry(VOID *args);
/**
  * @brief  Application FileX Initialization.
  * @param  None
  * @retval UINT: FX_SUCCESS on success, error code otherwise
  */
UINT app_filex_init(VOID)
{
  UINT ret;
  /* Create the main FileX task if init code is generated */
  ret = xTaskCreate(fx_task_entry, "fx_main_task", 1024, NULL, 10, &main_task);
  if (ret != pdPASS)
  {
    return FX_PTR_ERROR;
  }
  fx_system_initialize();
  printf("[INFO] Step 1: Initializing FileX...\n");
  return FX_SUCCESS;
}

VOID fx_task_entry(VOID *args)
{
  UINT status;
  ULONG bytes_read;
  ULONG bytes_written;
  ULONG sd_bytes_read;
  ULONG nor_bytes_read;
  ULONG index;
  CHAR file_name[FX_MAX_LONG_NAME_LEN];
  UINT find_status, attr;
  UINT verify_status = FX_SUCCESS;
  VOID *fx_driver_0_info_ptr;
  VOID *fx_driver_1_info_ptr;

  /** ########## Step 3 ##########
    * Format and open the NOR flash media.
    */
  fx_driver_0_info_ptr = mx_filex_driver_0_get_ctx();
  if (fx_driver_0_info_ptr == NULL)
  {
    printf("[ERROR] NOR flash context init failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  MX_FILEX_MEDIA_FORMAT_CONFIG *media_0_format_cfg;
  media_0_format_cfg = mx_filex_driver_0_get_media_format_config();

  status = fx_media_format(&fx_media_0,
                           mx_filex_driver_0,
                           fx_driver_0_info_ptr,
                           (VOID *)fx_media_0_buffer,
                           sizeof(fx_media_0_buffer),
                           volume_name_0,
                           media_0_format_cfg->number_of_fats,
                           media_0_format_cfg->directory_entries,
                           media_0_format_cfg->hidden_sectors,
                           media_0_format_cfg->total_sectors,
                           media_0_format_cfg->bytes_per_sector,
                           media_0_format_cfg->sectors_per_cluster,
                           media_0_format_cfg->heads,
                           media_0_format_cfg->sectors_per_track);

  if (status != FX_SUCCESS)
  {
    printf("[ERROR] error NOR format\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  printf("[INFO] NOR Media formatted successfully.\n");

  status = fx_media_open(&fx_media_0, volume_name_0, mx_filex_driver_0, fx_driver_0_info_ptr,
                         (VOID *)fx_media_0_buffer, sizeof(fx_media_0_buffer));

  if (status != FX_SUCCESS)
  {
    printf("[ERROR] error NOR media open\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  printf("[INFO] Step 3: NOR Media opened successfully.\n");

  /** ########## Step 4 ##########
    * Open the SD card media.
    */
  fx_driver_1_info_ptr = mx_filex_driver_1_get_ctx();

  status = fx_media_open(&fx_media_1, volume_name_1, mx_filex_driver_1, fx_driver_1_info_ptr,
                         (VOID *)fx_media_1_buffer, sizeof(fx_media_1_buffer));

  if (status != FX_SUCCESS)
  {
    printf("[ERROR] error SD media open\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  printf("[INFO] Step 4: SD Media opened successfully.\n");

  /* ---------------------------------------------------------
   * Open the source file on the SD in read mode
   * --------------------------------------------------------- */
  find_status = fx_directory_first_full_entry_find(&fx_media_1, file_name, &attr, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

  while (find_status == FX_SUCCESS)
  {
  if (!(attr & FX_DIRECTORY))
  {
    UINT len = strlen(file_name);
    if (len > 4)
    {
      CHAR *ext = &file_name[len - 4];

      if ((ext[0] == '.') &&
          (tolower((unsigned char)ext[1]) == 't') &&
          (tolower((unsigned char)ext[2]) == 'x') &&
          (tolower((unsigned char)ext[3]) == 't'))
      {
        PRINTF("[INFO] txt file found: %s\n", file_name);
        break;
      }
    }
  }

    find_status = fx_directory_next_full_entry_find(&fx_media_1, file_name, &attr, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  }

  if (find_status != FX_SUCCESS)
  {
    PRINTF("[INFO] No .txt file found\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_open(&fx_media_1, &fx_file_1, file_name, FX_OPEN_FOR_READ);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] Cannot open source file on SD. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_seek(&fx_file_1, 0);

  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_seek on SD failed. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* ---------------------------------------------------------
   * Create the destination file on NOR
   * --------------------------------------------------------- */
  status = fx_file_create(&fx_media_0, file_name);
  if ((status != FX_SUCCESS) && (status != FX_ALREADY_CREATED))
  {
    printf("[ERROR] Cannot create destination file on NOR. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* ---------------------------------------------------------
   * Open the destination file on NOR in write mode
   * --------------------------------------------------------- */
  status = fx_file_open(&fx_media_0, &fx_file_0, file_name, FX_OPEN_FOR_WRITE);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] Cannot open destination file on NOR. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Return to the beginning of the destination file */
  status = fx_file_seek(&fx_file_0, 0);

  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_seek on NOR failed. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /** ########## Step 5 ##########
    * Copy the file from SD to NOR.
    */
  /* ---------------------------------------------------------
   * Copy loop: read SD -> write NOR
   * --------------------------------------------------------- */
  do
  {
    bytes_read = 0;
    bytes_written = 0;

    status = fx_file_read(&fx_file_1, file_copy_buffer, sizeof(file_copy_buffer), &bytes_read);
    if ((status != FX_SUCCESS) && (status != FX_END_OF_FILE))
    {
      printf("[ERROR] fx_file_read failed. status = %u\n", status);
      xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
    }

    if (bytes_read > 0)
    {
      status = fx_file_write(&fx_file_0, file_copy_buffer, bytes_read);
      if (status != FX_SUCCESS)
      {
        printf("[ERROR] fx_file_write failed. status = %u\n", status);
        xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
      }

      bytes_written = bytes_read;
      printf("[INFO] Copied %lu bytes.\n", bytes_written);
    }

    if (status == FX_END_OF_FILE)
    {
      break;
    }

  } while (bytes_read > 0);

  printf("[INFO] Step 5: Copy data from SD to NOR.\n");

  /* ---------------------------------------------------------
   * Close the files
   * --------------------------------------------------------- */
  status = fx_file_close(&fx_file_0);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_close destination failed. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_close(&fx_file_1);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_close source failed. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Physical save */
  status = fx_media_flush(&fx_media_0);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_media_flush NOR failed. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Physical save */
  status = fx_media_flush(&fx_media_1);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_media_flush SD failed. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_open(&fx_media_0, &fx_file_0, file_name, FX_OPEN_FOR_READ);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] Cannot open source file on NOR. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_open(&fx_media_1, &fx_file_1, file_name, FX_OPEN_FOR_READ);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] Cannot open source file on SD. status = %u\n", status);
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_seek(&fx_file_0, 0);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_seek on NOR failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_seek(&fx_file_1, 0);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_seek on SD failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /** ########## Step 6 ##########
    * Verify data integrity.
    */
  while (verify_status == FX_SUCCESS)
  {
    sd_bytes_read = 0;
    nor_bytes_read = 0;

    status = fx_file_read(&fx_file_1, sd_compare_buffer, sizeof(sd_compare_buffer), &sd_bytes_read);
    if ((status != FX_SUCCESS) && (status != FX_END_OF_FILE))
    {
      verify_status = status;
      break;
    }

    status = fx_file_read(&fx_file_0, nor_compare_buffer, sizeof(nor_compare_buffer), &nor_bytes_read);
    if ((status != FX_SUCCESS) && (status != FX_END_OF_FILE))
    {
      verify_status = status;
      break;
    }

    if (sd_bytes_read != nor_bytes_read)
    {
      verify_status = FX_IO_ERROR;
      break;
    }

    for (index = 0; index < sd_bytes_read; index++)
    {
      if (sd_compare_buffer[index] != nor_compare_buffer[index])
      {
        verify_status = FX_IO_ERROR;
        break;
      }
    }

    if ((verify_status == FX_IO_ERROR) || (sd_bytes_read == 0))
    {
      break;
    }
  }

  status = fx_file_close(&fx_file_0);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_close on NOR failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_file_close(&fx_file_1);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_file_close on SD failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  if (verify_status != FX_SUCCESS)
  {
    printf("[ERROR] SD and NOR file content differs\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  printf("[INFO] Step 6: SD and NOR files are identical.\n");

  /* Close the media */
  status = fx_media_close(&fx_media_1);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_media_close on SD failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_media_close(&fx_media_0);
  if (status != FX_SUCCESS)
  {
    printf("[ERROR] fx_media_close on NOR failed\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  printf("[INFO] End of FileX task.\n");

  /* Notify the background task that the example runs as expected. */
  if (xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_SUCCESS, eSetValueWithOverwrite) == pdFAIL)
  {
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }
  vTaskDelete(main_task);
}
