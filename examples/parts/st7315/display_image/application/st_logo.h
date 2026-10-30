/**
  ******************************************************************************
  * file    : st_logo.h
  * brief   : This file contains ARGB8888 image 320x240.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ST_LOGO_H
#define ST_LOGO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ST128_64_HEIGHT 64
#define ST128_64_WIDTH 128

extern const uint8_t st_logo[1024];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ST_LOGO_H */
