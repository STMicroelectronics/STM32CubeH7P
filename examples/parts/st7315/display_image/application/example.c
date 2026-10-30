/**
  ******************************************************************************
  * file           : example.c
  * brief          : display a monochrome bitmap image using the ST7315
  *                  128x64 OLED module.
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
#include <string.h>

#include "example.h"
#include "st7315.h"
#include "st_logo.h"    /* image data defined in this file */

/* Private variables ---------------------------------------------------------*/

/* Application-owned frame buffer (ST7315_COLUMN_NUMBER * ST7315_PAGE_NUMBER = 1024 bytes) */
static uint8_t frame_buffer[ST7315_FRAME_BUFFER_SIZE];

/* ST7315 instance */
st7315_obj_t *pOledObj = NULL;

/* Private functions prototype -----------------------------------------------*/
static void DrawPixel(uint8_t *fb, uint16_t xpos, uint16_t ypos, uint8_t color);
static void DrawMonoImage(uint8_t *fb, const uint8_t *image, uint16_t width, uint16_t height);


/** ########## Step 1 ##########
  * Initializes the ST7315 instance, attaches the frame buffer, and clears the DDRAM.
  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  /* Retrieve and store the ST7315 OLED object pointer */
  pOledObj = mx_oled_part_getobject();
  /* initialize the oled controller */
  if (st7315_init(pOledObj, MX_OLED_PART) != ST7315_OK)
  {
    goto _app_init_exit;
  }

  if (st7315_set_frame_buffer(pOledObj, frame_buffer) != ST7315_OK)
  {
    goto _app_init_exit;
  }
  /* Clean the display's DDRAM to remove any residual/random data */
  if (st7315_clean_ddram(pOledObj) != ST7315_OK)
  {
    goto _app_init_exit;
  }

  PRINTF("[INFO] Step 1: Device initialization COMPLETED.\n");
  return_status = EXEC_STATUS_INIT_OK;
_app_init_exit:
  return return_status;
} /* end app_init */


/** ########## Step 2 ##########
  * Renders the ST logo monochrome bitmap into the frame buffer
  * and transfers it to the display.
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;

  (void)memset(frame_buffer, 0x00U, sizeof(frame_buffer));
  DrawMonoImage(frame_buffer, st_logo, ST128_64_WIDTH, ST128_64_HEIGHT);
  /** Synchronize the display's DDRAM with the frame buffer content.
    * This function transfers the frame buffer content to the display controller.
    */
  if (st7315_synchronize(pOledObj) != ST7315_OK)
  {
    goto _app_process_exit;
  }

  PRINTF("[INFO] Step 2: ST Logo Displayed.\n");

  /* this delay to show the final result */
  HAL_Delay(2000);

  return_status = EXEC_STATUS_OK;
_app_process_exit:
  return return_status;
} /* end app_process */


app_status_t app_deinit(void)
{
  /** No resources to release in this example.
    * app_deinit() is only for reference and will never be executed.
    */

  return EXEC_STATUS_OK;
} /* end app_deinit */


/* Private helpers: pixel-level access for the page-format frame buffer.    */
/* The ST7315 stores pixels in pages: each byte covers 8 vertically         */
/* stacked pixels (bit 0 = top row of the page, bit 7 = bottom row).        */

static void DrawPixel(uint8_t *fb, uint16_t xpos, uint16_t ypos, uint8_t color)
{
  /* Panel polarity: bit 1 = white (lit), bit 0 = black */
  if (color == ST7315_COLOR_WHITE)
  {
    fb[xpos + (ypos / 8U) * ST7315_PIXEL_WIDTH] |= (uint8_t)(1U << (ypos % 8U));
  }
  else
  {
    fb[xpos + (ypos / 8U) * ST7315_PIXEL_WIDTH] &= (uint8_t)(~(1U << (ypos % 8U)));
  }
}

/* Copy a raw monochrome image into the page-format frame buffer.           */
/* Cleared bits (logo shape) are drawn lit (WHITE) on a black background.   */
static void DrawMonoImage(uint8_t *fb, const uint8_t *image, uint16_t width, uint16_t height)
{
  uint16_t bytes_per_row = (uint16_t)(width / 8U);

  for (uint16_t y = 0U; y < height; y++)
  {
    for (uint16_t x = 0U; x < width; x++)
    {
      uint8_t bit = (uint8_t)((image[(y * bytes_per_row) + (x / 8U)] >> (7U - (x % 8U))) & 0x01U);
      DrawPixel(fb, x, y, (bit == 0U) ? ST7315_COLOR_WHITE : ST7315_COLOR_BLACK);
    }
  }
}
