<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *filex_sd_nor_data_copy_freertos*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

This application provides an example of FileX usage with FreeRTOS.

It demonstrates how to use FileX to handle file operations on two storage media:


- a **NOR flash** device,
- an **SD card** device.

The application initializes the FileX system, creates a dedicated FreeRTOS task, formats and opens the NOR flash media, open the SD card media and look for the first file with the .txt extension in the root directory, copies a file from the SD card to the NOR flash, and verifies data integrity by comparing the two files.

The example includes all required software components to manage NOR flash and SD card I/O operations through FileX.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, memory interfaces, MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

- __Step 1__: Initialize FileX and create the task.
- __Step 2__: Starts the FreeRTOS scheduler.
- __Step 3__: Format and open the NOR flash media.
- __Step 4__: Open the SD card media.
- __Step 5__: Copy the file from SD to NOR.
- __Step 6__: Verify data integrity.
__End of example__: The example finishes by closing the opened files, flushing pending data to the media, and closing both FileX media properly.

<b>Note</b>:

  - A FAT32 compatible SD card is expected to be used in this example.
  - The program will start file operations without formatting the media SD, so all user related files are kept.
  - Ensure that the file with the .txt extension is placed on the microSD card before starting the application.


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the Cube Firmware package.")

- *SD*: is configured with the following features and settings:
  - falling edge detection
  - clock power save disabled
  - bus wide of 4 bits
  - hardware flow control enabled
  - no transceiver
  - maximum data timeout
  - maximum transfer timeout
  - maximum erase timeout
  - selected gpio pins support the SD alternate function. They are configured in push-pull mode with no pull-up or
  pull-down.

- *NOR*: Configured with the following features and settings:
  - Write, read, and erase operations enabled
  - Optimized for concurrent access
  - Configured for high-speed operations
  - Selected GPIO pins support the NOR alternate function. They are configured in push-pull mode with no pull-up or pull-down.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

Please find below the hardware setup principle that applies to any board.

plantUML ditaa integration supports PNG only

@startuml
@startditaa{doc/mx25lm51245g_generic_hardware_setup.png}
  +-------------------------+                     +-------------------------+
  |          +--------------+                     |                         |
  |          |STM32 XSPIi   |                     |                         |
  |          |              |                     |                         |
  |          |          CLK *---------------------* SCLK                    |
  |          |              |                     |                         |
  |          |       DQS/WS *---------------------* DQS                     |
  |          |              |                     |                         |
  |          |      IO[7:0] *---------------------* SIO[7:0]                |
  |          |              |                     |                         |
  |          |          nCS *---------------------* CS#                     |
  |          |              |                     |                         |
  |          |              |                     |                         |
  |          +--------------+                     |                         |
  |                         |                     |                         |
  |                         |                     |                         |
  | STM32 MCU               |                     |      mx25lm51245g flash |
  +-------------------------+                     +-------------------------+
@endditaa
@enduml

@startuml
@startditaa{doc/ASCII_sd_connection.png}
    +----------------------------------------------------------------+
    |          +--------------+                     +--------------+ |
    |          | STM32 SDMMC  |                     | SD CONNECTOR | |
    |          |              |                     |              | |
    |          |     STDIO_D1 *---------------------* STDIO_D1     | |
    |          |              |                     |              | |
    |          |     STDIO_D0 *---------------------* STDIO_D0     | |
    |          |              |                     |              | |
    |          |    STDIO_CLK *---------------------* STDIO_CLK    | |
    |          |              |                     |              | |
    |          |    STDIO_CMD *---------------------* STDIO_CMD    | |
    |          |              |                     |              | |
    |          |     STDIO_D3 *---------------------* STDIO_D3     | |
    |          |              |                     |              | |
    |          |     STDIO_D2 *---------------------* STDIO_D2     | |
    |          |              |                     |              | |
    |          +--------------+                     +--------------+ |
    | STM32 Board                                                    |
    +----------------------------------------------------------------+
@endditaa
@enduml

### __3.2. Specific board setups__

The different signals used for the SDMMC can be observed by connecting an oscilloscope or a logical analyser to the
corresponding board connectors.

Please find the exact hardware configurations of your project below.

<details>
<summary>On STM32H7P series.</summary>

<details>
  <summary>On board STM32H7P5I-DK.</summary>

| Board connector | MCU pin | Signal name     | ARDUINO <br> connector pin |
| :-------------: | :-----: | :-------------: | :------------------------: |
| NA              | PE3     | SDMMC1_D0       | NA                         |
| NA              | PE4     | SDMMC1_D1       | NA                         |
| NA              | PE5     | SDMMC1_D2       | NA                         |
| NA              | PE6     | SDMMC1_D3       | NA                         |
| NA              | PE2     | SDMMC1_CK       | NA                         |
| NA              | PA5     | SDMMC1_CMD      | NA                         |


| Board connector | MCU pin | Signal name     | ARDUINO <br> connector pin |
| :-------------: | :-----: | :-------------: | :------------------------: |
| NA              | PJ5     |  XSPIM_P2_CLK   | NA                         |
| NA              | PJ7     |  XSPIM_P2_DQS0  | NA                         |
| NA              | PJ1     |  XSPIM_P2_IO0   | NA                         |
| NA              | PJ2     |  XSPIM_P2_IO1   | NA                         |
| NA              | PJ3     |  XSPIM_P2_IO2   | NA                         |
| NA              | PJ4     |  XSPIM_P2_IO3   | NA                         |
| NA              | PJ8     |  XSPIM_P2_IO4   | NA                         |
| NA              | PJ9     |  XSPIM_P2_IO5   | NA                         |
| NA              | PJ10    |  XSPIM_P2_IO6   | NA                         |
| NA              | PJ11    |  XSPIM_P2_IO7   | NA                         |
| NA              | PJ12    |  XSPIM_P2_NCS2  | NA                         |

</details>
</details>


## __4. Troubleshooting__

[![Troubleshooting](doc/debug_with-Troubleshooting.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/debug/debug_toc.html "An offline version is also available in the Cube Firmware package.")


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the Cube Firmware package.")


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
