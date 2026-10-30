/**
  **********************************************************************************************************************
  * @file    eeprom_emul_conf.h
  * @brief   EEPROM Emulation configuration file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_eeprom_emulation_license.md file
  * in the same directory as the generated code.
  * If no mx_eeprom_emulation_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef EEPROM_EMUL_CONF_H
#define EEPROM_EMUL_CONF_H
#ifdef __cplusplus
extern "C" {
#endif

/* Private constants ---------------------------------------------------------*/

/*!<  Algorithm selection: EEPROM emulation supports two algorithms, one for the FLITF flash interface and
  one for the NVM flash interface. Select the required algorithm by enabling either EE_ALGO_FLITF or
  EE_ALGO_NVM. */
#define EE_ALGO_FLITF                 (1)

/*!<  Number of bytes per EEPROM data line. This value depends on the flash type embedded in the STM32
      product and can be either 8 or 16. */
#define EE_FRAME_LINE_SIZE            (16)


/*!<  EEPROM emulation start address */
#define EE_START_PAGE_ADDRESS         (0x8100000U)


/*!< Start address of the flash */
#define EE_FLASH_BASE_ADDRESS         (0x8100000U)

/*!< Flash page size */
#define EE_FLASH_PAGE_SIZE            (8192U)


/*!<  Total number of variables stored in EEPROM emulation */
#define EE_NB_OF_VARIABLES            (1000U)

/*!<  Number of guard pages used to reduce frequent transfers */
#define EE_GUARD_PAGES_NUMBER         (1U)

/*!<  Requested number of EEPROM emulation cycles. The minimum value is 1 for 10 Kcycles by default.
      Higher values increase the number of required pages. */
#define EE_CYCLES_NUMBER              (1U)

/*!<  Time budget, in milliseconds, granted to a single call of EE_CleanUpProgressive().
      A smaller value improves application responsiveness by splitting the page transfer
      into shorter slices, at the cost of more calls to complete the cleanup. */
#define EE_CLEANUP_PROGRESSIVE_TIME_MS (100UL)

#ifdef __cplusplus
}
#endif


#endif /*EEPROM_EMUL_CONF_H */
