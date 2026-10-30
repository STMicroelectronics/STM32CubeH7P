<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *hal_dma_repeated_block*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

How to configure and use the DMA HAL API to perform repeated block transactions.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

__Step 1__: Configures the DMA in memory to memory repeated block mode.
            Registers the user callbacks for DMA events: transfer errors and transfer complete.

__Step 2__: Starts the DMA repeated block transfer.

__Step 3__: Waits for one of these DMA interrupts: transfer complete or transfer error,
and then compares the destination buffer with the expected values.

__Step 4__: Deinitializes the DMA.

__End of example__: Reports the outcome of the data transfer via the variable **`ExecStatus`**,
and the **status LED** remains turned on in case of success.


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the STM32Cube firmware package.")

- The *DMA* is configured in memory to memory repeated block mode (block count = 4).
- The *DMA* is configured with source and destination increment
- The *DMA* is triggered by software.
- Source and destination buffers are declared as uint32_t arrays, it matches the DMA configuration to work with word data width. This avoids data misalignment.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

JTAG/SWD probe may be used to check variables and buffers.

### __3.2. Specific board setups__

<details>
  <summary>On STM32H7P series.</summary>
  <details>
    <summary>On board NUCLEO-H7P5II.</summary>

  |  MCU pin  |  Signal name  |  User Label   |
  |:---------:|:-------------:|:-------------:|
  |    PG9    |     GPIO      | MX_STATUS_LED |

  </details>

  <details>
    <summary>On board STM32H7P5I-DK.</summary>

  |  MCU pin  |  Signal name  |  User Label   |
  |:---------:|:-------------:|:-------------:|
  |    PH6    |     GPIO      | MX_STATUS_LED |

  </details>
</details>



## __4. Troubleshooting__

[![Troubleshooting](doc/debug_with-Troubleshooting.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/debug/debug_toc.html "An offline version is also available in the STM32Cube firmware package.")

Here are the points of attention for this specific example:

Check DMA, cache, and MPU alignment requirements to avoid data corruption or transfer issues.

In case you cannot use the non cacheble area memory, Take care of __cache coherency issue__:
When the data cache memory is enabled, it is generally not in the path of DMA transfer, thus a cache coherency issue might
appear. It might be necessary to tackle cache coherency.
See H7 FAQ:
[DMA-is-not-working-on-STM32H7-devices](https://community.st.com/s/article/FAQ-DMA-is-not-working-on-STM32H7-devices).

Take care of __DMA ports__:
Depending on STM32 series, and DMA instance used (GPDMA/HPDMA/LPDMA) specific DMA ports constraints must be respected.
For details, refer to the reference manual of your MCU. You can also see the application note in the `__5. See Also` section.


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the STM32Cube firmware package.")

- [Application Note AN2548](https://www.st.com/resource/en/application_note/an2548-introduction-to-dma-controller-for-stm32-mcus-stmicroelectronics.pdf): Using the STM32F0/F1/F3/Gx/Lx Series DMA controller
- [Application Note AN4031](https://www.st.com/resource/en/application_note/an4031-using-the-stm32f2-stm32f4-and-stm32f7-series-dma-controller-stmicroelectronics.pdf): Using the STM32F2, STM32F4 and STM32F7 Series DMA controller
- [Application Note AN5593](https://www.st.com/resource/en/application_note/an5593-how-to-use-the-gpdma-for-stm32-mcus-stmicroelectronics.pdf): How to use the GPDMA for STM32U5 Series microcontrollers

The documentation of the drivers of the relevant STM32 series contains more detailed information.

For instance for the STM32C5 series: [HAL documentation](https://dev.st.com/stm32cube-docs/stm32c5xx-hal-drivers/latest/en/index.html).

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/embedded-software.html).


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
