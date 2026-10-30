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
static __attribute__((aligned(32))) ULONG fx_media_0_buffer[512 / sizeof(ULONG)];

static FX_FILE  fx_file_one;
static FX_FILE  fx_file_two;

TaskHandle_t task_0;
TaskHandle_t task_1;
TaskHandle_t main_task;

/* Declaration of the Event Group */
EventGroupHandle_t xEventGroup;

/* Event Flags Bits */
const EventBits_t xBit1 = (1 << 0);
const EventBits_t xBit2 = (1 << 1);
const EventBits_t xBit3 = (1 << 2);

/* Private function prototypes -----------------------------------------------*/
VOID fx_task_entry(VOID *args);
VOID app_task_entry_one(VOID *args);
VOID app_task_entry_two(VOID *args);
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
  /* Create per-interface FileX task */
  ret = xTaskCreate(app_task_entry_one, "app_task_entry_one", 1024, NULL, 5, &task_0);

  if (ret != pdPASS)
  {
    return FX_PTR_ERROR;
  }
  /* Create per-interface FileX task */
  ret = xTaskCreate(app_task_entry_two, "app_task_entry_two", 1024, NULL, 5, &task_1);

  if (ret != pdPASS)
  {
    return FX_PTR_ERROR;
  }

  /* Creation of the Event Group */
  xEventGroup = xEventGroupCreate();

  PRINTF("[INFO] Step 1: tasks and event created\n");

  fx_system_initialize();
  PRINTF("[INFO] Step 2: Initializing FileX...\n");
  return FX_SUCCESS;
}

VOID fx_task_entry(VOID *args)
{
  UINT status;
  VOID *fx_driver_0_info_ptr = mx_filex_driver_0_get_ctx();

  status = fx_media_open(&fx_media_0, volume_name_0, mx_filex_driver_0, fx_driver_0_info_ptr,
                         (VOID *)fx_media_0_buffer, sizeof(fx_media_0_buffer));

  if (status != FX_SUCCESS)
  {
    PRINTF("[ERROR] error open\n");
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  PRINTF("[INFO] Step 3: Media opened successfully.\n");

  xEventGroupSetBits(xEventGroup, xBit1);

  if ((xEventGroupWaitBits(xEventGroup, xBit2, pdTRUE, pdTRUE, TIMEOUT) & xBit2) == xBit2)
  {
    PRINTF("[INFO] Step 4: STM32_FILE1.TXT file creates and reads data.\n");
  }
  else
  {
    /* xBit2 was not set. Handle the error. */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  if ((xEventGroupWaitBits(xEventGroup, xBit3, pdTRUE, pdTRUE, TIMEOUT) & xBit3) == xBit3)
  {
    PRINTF("[INFO] Step 5: STM32_FILE2.TXT file creates and reads data.\n");
  }
  else
  {
    /* xBit3 was not set. Handle the error. */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Close the media.  */
  status = fx_media_close(&fx_media_0);

  /* Check the media close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the media, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }
  /** ########## Step 6 ##########
    * Complete the scenario by ensuring that the media is properly closed.
    */

  vTaskDelete(task_0);
  vTaskDelete(task_1);


  while (1)
  {
    /* Notify the background task that the example runs as expected. */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_SUCCESS, eSetValueWithOverwrite);
  }
}

VOID app_task_entry_one(VOID *args)
{
  /* Waiting for an event from main task */
  xEventGroupWaitBits(xEventGroup, xBit1, pdTRUE, pdFALSE, TIMEOUT);

  UINT status;
  ULONG bytes_read;
  CHAR read_buffer[32];
  CHAR data[] = "This is FileX working concurrently on STM32";

  /* Create a file called STM32_FILE1.TXT in the root directory.  */
  status = fx_file_create(&fx_media_0, "STM32_FILE1.TXT");

  /* Check the create status.  */
  if (status != FX_SUCCESS)
  {
    /* Check for an already created status. This is expected on the
    second pass of this loop!  */
    if (status != FX_ALREADY_CREATED)
    {
      /* Create error, notify the background task.  */
      xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
    }
  }

  /* Open the test file.  */
  status = fx_file_open(&fx_media_0, &fx_file_one, "STM32_FILE1.TXT", FX_OPEN_FOR_WRITE);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Seek to the beginning of the test file.  */
  status = fx_file_seek(&fx_file_one, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Write a string to the test file.  */
  status = fx_file_write(&fx_file_one, data, sizeof(data));

  /* Check the file write status.  */
  if (status != FX_SUCCESS)
  {
    /* Error writing to a file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Close the test file.  */
  status = fx_file_close(&fx_file_one);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_media_flush(&fx_media_0);

  /* Check the media flush  status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Open the test file.  */
  status = fx_file_open(&fx_media_0, &fx_file_one, "STM32_FILE1.TXT", FX_OPEN_FOR_READ);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Seek to the beginning of the test file.  */
  status = fx_file_seek(&fx_file_one, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Read the content of the test file.  */
  status = fx_file_read(&fx_file_one, read_buffer, sizeof(data), &bytes_read);

  /* Check the file read status.  */
  if ((status != FX_SUCCESS) || (bytes_read != sizeof(data)))
  {
    /* Error reading file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Close the test file.  */
  status = fx_file_close(&fx_file_one);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Sending a signal to main task */
  xEventGroupSetBits(xEventGroup, xBit2);

  /* Notify the background task that the example runs as expected. */
  if (xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_SUCCESS, eSetValueWithOverwrite) == pdFAIL)
  {
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  while (1)
  {
    vTaskDelay(100);
  }
}

VOID app_task_entry_two(VOID *args)
{
  /* Waiting for an event from main task */
  xEventGroupWaitBits(xEventGroup, xBit1, pdTRUE, pdFALSE, TIMEOUT);

  UINT status;
  ULONG bytes_read;
  CHAR read_buffer[32];
  CHAR data[] = "This is FileX working concurrently on STM32";

  /* Create a file called STM32_FILE2.TXT in the root directory.  */
  status = fx_file_create(&fx_media_0, "STM32_FILE2.TXT");

  /* Check the create status.  */
  if (status != FX_SUCCESS)
  {
    /* Check for an already created status. This is expected on the
    second pass of this loop!  */
    if (status != FX_ALREADY_CREATED)
    {
      /* Create error, notify the background task.  */
      xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
    }
  }

  /* Open the test file.  */
  status = fx_file_open(&fx_media_0, &fx_file_two, "STM32_FILE2.TXT", FX_OPEN_FOR_WRITE);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Seek to the beginning of the test file.  */
  status = fx_file_seek(&fx_file_two, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Write a string to the test file.  */
  status = fx_file_write(&fx_file_two, data, sizeof(data));

  /* Check the file write status.  */
  if (status != FX_SUCCESS)
  {
    /* Error writing to a file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Close the test file.  */
  status = fx_file_close(&fx_file_two);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  status = fx_media_flush(&fx_media_0);

  /* Check the media flush  status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Open the test file.  */
  status = fx_file_open(&fx_media_0, &fx_file_two, "STM32_FILE2.TXT", FX_OPEN_FOR_READ);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Seek to the beginning of the test file.  */
  status = fx_file_seek(&fx_file_two, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Read the content of the test file.  */
  status = fx_file_read(&fx_file_two, read_buffer, sizeof(data), &bytes_read);

  /* Check the file read status.  */
  if ((status != FX_SUCCESS) || (bytes_read != sizeof(data)))
  {
    /* Error reading file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Close the test file.  */
  status = fx_file_close(&fx_file_two);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, notify the background task.  */
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  /* Sending a signal to main task */
  xEventGroupSetBits(xEventGroup, xBit3);

  /* Notify the background task that the example runs as expected. */
  if (xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_SUCCESS, eSetValueWithOverwrite) == pdFAIL)
  {
    xTaskNotify(BackgroundTask, NOTIFICATION_VALUE_ERROR, eSetValueWithOverwrite);
  }

  while (1)
  {
    vTaskDelay(100);
  }
}
