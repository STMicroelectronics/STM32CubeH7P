<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *hal_sd_read_write_it*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

How to use the HAL API to read and write data from an SD card in interruption mode through the SDMMC interface.
A calculation for read and write speed is done.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

__Step 1__: configures and initializes the SD instance.

__Step 2__: initializes and performs transmission from the device to the SD card.

__Step 3__: initializes and performs reception from the SD card to the device, then compares the transmitted and received data.

__Step 4__: deinitializes the SD instance.

__End of example__: After step 4, the example is completed.
You can verify that the example runs properly via the status LED and the `ExecStatus` variable.

If you enable `USE_TRACE`, you can follow these execution steps in the terminal logs:
```text
[INFO] Step 1: Device initialization COMPLETED.
[INFO] Step 2: Blocks written in xxx ms.
[INFO] Step 3: Reading and writing buffers are identical. Blocks read in xxx ms.
[INFO] Step 4: de-init
...
```


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the STM32Cube firmware package.")

The __SD__ is configured with the following features and settings:

  - Rising edge detection.
  - Clock power save disabled.
  - Bus width of 4 bits.
  - Hardware flow control is enabled.
  - No transceiver.
  - Maximum data timeout.
  - Maximum transfer timeout.
  - Maximum erase timeout.
  - Select GPIO pins supporting the SD alternate function.
    They are configured in push-pull mode with no pull-up or pull-down.

  **_NOTE:_** the SDMCC interrupt is enabled.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

This section describes the hardware setup principles that apply to any board.

<!--
@startuml
@startditaa{doc/ASCII_sd_connection.png}
    +----------------------------------------------------------------+
    |          +--------------+                     +--------------+ |
    |          |STM32 SDMMCi  |                     | SD CONNECTOR | |
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
-->

![ASCII_sd_connection](doc/ASCII_sd_connection.png)

### __3.2. Specific board setups__

This section describes the exact hardware configurations of your project.

The different signals used for the SDMMC can be observed by connecting an oscilloscope or a logical analyzer to the
corresponding board connectors.

<!-- YOUR BOARDS ADDED HERE BY README GENERATION -->


<details>
  <summary>On STM32H7P series.</summary>
  <details>
    <summary>On board STM32H7P5I-DK.</summary>

  |  MCU pin  |  Signal name  |  User Label   |
  |:---------:|:-------------:|:-------------:|
  |    PH6    |     GPIO      | MX_STATUS_LED |
  |    PA2    |   USART2_TX   |       -       |
  |    PE2    |   SDMMC1_CK   |       -       |
  |    PA5    |  SDMMC1_CMD   |       -       |
  |    PE3    |   SDMMC1_D0   |       -       |
  |    PE4    |   SDMMC1_D1   |       -       |
  |    PE5    |   SDMMC1_D2   |       -       |
  |    PE6    |   SDMMC1_D3   |       -       |

  </details>
</details>



## __4. Troubleshooting__

  - If the SD transfer is done in polling or interrupt mode, it is highly recommended to enable the hardware flow control feature to avoid any underrun error.

[![Troubleshooting](doc/debug_with-Troubleshooting.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/debug/debug_toc.html "An offline version is also available in the STM32Cube firmware package.")


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the STM32Cube firmware package.")

This [application note](https://www.st.com/resource/en/application_note/dm00525510-getting-started-with-stm32h7-series-sdmmc-host-controller-stmicroelectronics.pdf)
explains the basis about the SDMMC host controller.

The documentation of the drivers of the relevant STM32 series contains more detailed information.

For instance for the STM32C5 series: [HAL documentation](https://dev.st.com/stm32cube-docs/stm32c5xx-hal-drivers/latest/en/index.html).

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/embedded-software.html).


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
