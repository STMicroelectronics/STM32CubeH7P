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
FX_FILE         fx_file;
hal_flash_handle_t *gh_flash;

static FX_MEDIA fx_media_0;
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
    return status;
  }

  PRINTF("[INFO] Step 2: Media opened successfully.\n");

  return status;
}

UINT app_filex_process(VOID)
{
  UINT status = FX_SUCCESS;
  CHAR file_name[FX_MAX_LONG_NAME_LEN];
  UINT read_buffer[READ_BUFFER_SIZE];
  ULONG bytes_read;
  ULONG flash_address = USER_APP_ADDRESS;
  UINT find_status, attr;
  ULONG size;
  UINT y, mo, d, h, mi, s;

  gh_flash = mx_flash_gethandle();

  find_status = fx_directory_first_full_entry_find(&fx_media_0, file_name, &attr, &size, &y, &mo, &d, &h, &mi, &s);

  while (find_status == FX_SUCCESS)
  {
    if (!(attr & FX_DIRECTORY))
    {
      UINT len = strlen(file_name);
      if ((len > 4) && (strcmp(&file_name[len - 4], ".BIN") == 0))
      {
        PRINTF("[INFO] BIN file found: %s\n", file_name);
        break;
      }
    }

    find_status = fx_directory_next_full_entry_find(&fx_media_0, file_name, &attr, &size, &y, &mo, &d, &h, &mi, &s);
  }

  if (find_status != FX_SUCCESS)
  {
    PRINTF("[INFO] No .BIN file found\n");
    return find_status;
  }

  status =  fx_file_open(&fx_media_0, &fx_file, file_name, FX_OPEN_FOR_READ);
  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, call error handler.  */
    return status;
  }

  PRINTF("[INFO] Step 3: Open firmware file from carte SD.\n");

  if (HAL_FLASH_ITF_Unlock(HAL_FLASH) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Erase the full bank2 of the flash memory */
  if (HAL_FLASH_EraseBank(gh_flash, HAL_FLASH_BANK_2, FLASH_OPERATION_TIMEOUT) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Seek to the beginning of the test file.  */
  status =  fx_file_seek(&fx_file, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, call error handler.  */
    return status;
  }

  do
  {

    /* Read sizeof(read_buffer) chunk from the exec into buffer.  */
    status =  fx_file_read(&fx_file, (VOID *) read_buffer, READ_BUFFER_SIZE, &bytes_read);

    /* Check the file read status.  */
    if (status != FX_SUCCESS)
    {
      /* We check if we reached EOF */
      if (status == FX_END_OF_FILE)
      {
        break;
      }

      /* Error while reading file, call error handler.  */
      return status;
    }

    if (HAL_FLASH_ProgramByAddr(gh_flash, flash_address, (const uint32_t *) read_buffer,
                                bytes_read, FLASH_OPERATION_TIMEOUT) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Increment the flash address by bytes_read bytes */
    flash_address = flash_address + READ_BUFFER_SIZE;

  } while (bytes_read);

  PRINTF("[INFO] Step 4: Read file chunk by chunk and write into flash.\n");

  /* Flash programmed, can be locked again */
  if (HAL_FLASH_ITF_Lock(HAL_FLASH) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Close the test file.  */
  status = fx_file_close(&fx_file);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler.  */
    return status;
  }

  status = fx_media_close(&fx_media_0);

  PRINTF("[INFO] Step 5: Close file and media.\n");

  return status;

}
