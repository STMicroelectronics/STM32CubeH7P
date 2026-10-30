<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *filex_sd_multi_access_freertos*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

This application provides an example of FileX stack usage.

it demonstrates the FileX's concurrent file access capabilities. The application is designed to execute file operations on the SD card device, the code provides all required software code for handling SD card I/O operations.

The application starts by calling the FreeRTOS initialization routine which creates multithreaded environment for
starting the concurrent
FileX's two main threads that handle file operations. At this stage, all FileX resources are created, the SDIO driver is initialized and the application creates 3 threads with the same priorities:

- main_task used to initialize the SD card driver and opening it as a FileX Media.
- fx_thread_one used to create, write and read operations for file fx_file_one.
- fx_thread_two used to create, write and read operations for file fx_file_two.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

- __Step 1__: Creates a event and 3 tasks with the same priority.
- __Step 2__: Starts the FreeRTOS scheduler.
- __Step 3__: Use 'task entry' to initialize the SD card driver and open it as a FileX Media.
- __Step 4__: Use 'task one' to perform create, write, and read operations on the file fx_file_one.
- __Step 5__: Use 'task two' to execute creation, writing, and reading operations for the file fx_file_two.


__End of example__: After Step 5, the example is completed. You can check its status via the status LED.


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](
https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the Cube Firmware package.")

- *SD*: is configured with the following features and settings:
- rising edge detection
- clock power save disabled
- bus wide of 4 bits
- hardware flow control disabled
- no transceiver
- maximum data timeout
- maximum transfer timeout
- maximum erase timeout
- selected gpio pins support the SD alternate function. They are configured in push - pull mode with no pull - up or
pull - down.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

Please find below the hardware setup principle that applies to any board.

plantUML ditaa integration supports PNG only

@startuml
@startditaa{doc / ASCII_sd_connection.png}
+---------------------------------------------------------------- +
|          +-------------- +                     +-------------- + |
|          | STM32 SDMMC  |                     | SD CONNECTOR | |
|          |              |                     |              | |
|          |     STDIO_D1 *-------------------- -* STDIO_D1     | |
|          |              |                     |              | |
|          |     STDIO_D0 *-------------------- -* STDIO_D0     | |
|          |              |                     |              | |
|          |    STDIO_CLK *-------------------- -* STDIO_CLK    | |
|          |              |                     |              | |
|          |    STDIO_CMD *-------------------- -* STDIO_CMD    | |
|          |              |                     |              | |
|          |     STDIO_D3 *-------------------- -* STDIO_D3     | |
|          |              |                     |              | |
|          |     STDIO_D2 *-------------------- -* STDIO_D2     | |
|          |              |                     |              | |
|          +-------------- +                     +-------------- + |
| STM32 Board                                                    |
+---------------------------------------------------------------- +
@endditaa
@enduml

![](doc / ASCII_sd_connection.png)

### __3.2. Specific board setups__

The different signals used for the SDMMC can be observed by connecting an oscilloscope or a logical analyser to the
corresponding board connectors.

Please find the exact hardware configurations of your project below.

<details>
<summary>On STM32H7P series.</summary>

<details>
<summary>On board STM32H7P5I-DK.</summary>

| Board connector | MCU pin | Signal name | ARDUINO <br> connector pin |
| :-------------: | :-----: | :---------: | :------------------------: |
| NA              | PE3     | SDMMC1_D0   | NA                         |
| NA              | PE4     | SDMMC1_D1   | NA                         |
| NA              | PE5     | SDMMC1_D2   | NA                         |
| NA              | PE6     | SDMMC1_D3   | NA                         |
| NA              | PE2     | SDMMC1_CK   | NA                         |
| NA              | PA5     | SDMMC1_CMD  | NA                         |

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
If no LICENSE file comes with this software, it is provided AS - IS.

