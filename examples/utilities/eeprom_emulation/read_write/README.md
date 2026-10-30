<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *eeprom_emulation_read_write*__

**Example version:** 2.0.5

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

How to use the eeprom_emulation utility on an STM32 microcontroller to perform writing and reading data.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.
In the `app_init()` function, `mx_eeprom_emulation_init()` is called to initialize the eeprom_emulation utility.


The application executes the following __example steps__:

__Step 1__: Configures and initializes the eeprom_emulation utility (number of variables, flash base address used for eeprom_emulation)

__Step 2__: Write elements data (8 bits) into the eeprom_emulation memory.

__Step 3__: read written elements data from eeprom_emulation memory and check the content of read elements.

__End of example__: Steps 2 and 3 are repeated `EXAMPLE_LOOP_COUNT = 20` times, then the example is completed. You can check it status via the status LED.

If you enable `USE_TRACE`, you can follow these execution steps in the terminal logs:

```text
[INFO] Step 1: EEPROM INITIALIZATION COMPLETED.
[INFO] Step 2: start the write process.
[INFO] Step 3: START READ PROCESS.
[INFO] Step 3: READ and WRITTEN VARIABLES ARE EQUAL.
```


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the STM32Cube firmware package.")


__eeprom_emulation__: The eeprom_emulation configuration in specific to the flash technology of each STM32 product.

  __crc__: The CRC is configured with a 16-bit length and a user-defined polynomial.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

No specific setup for this example.

### __3.2. Specific board setups__

This section describes the exact hardware configurations of your project.

<details>
<summary>On STM32H7P series.</summary>

<details>
  <summary>Common EEPROM Emulation configuration.</summary>

  eeprom_emulation is configured as follow:

  - _ee_frame line_size_: __16__

  - _EE_START_PAGE_ADDRESS_: 0x8100000U

  - _EE_START_BASE_ADDRESS_: 0x8100000U

  - __EE_FLASH_PAGE_SIZE__: __8192U__

  - _ee_nb_of_variables_: __1000U__

  - _ee_cycle_number_: __1U__

**_NOTE:_**  To optimize flash access and avoid contention with code execution from Bank 1, the Eeprom emulation is placed in Bank 2, allowing efficient and non-blocking read/write operations.

</details>
<details>
  <summary>On board NUCLEO-H7P5II.</summary>

  | Board pin   | MCU pin | Signal name          | ARDUINO <br> connector pin |
  | :---:       | :---:   | :---:                | :---:        |
  | CN5-6       | PG9     | MX_STATUS_LED        | D13          |

  </details>
</details>

  </details>
</details>


## __4. Troubleshooting__

[![Troubleshooting](doc/debug_with-Troubleshooting.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/debug/debug_toc.html "An offline version is also available in the STM32Cube firmware package.")

Find below the points of attention for this specific example.

__Memory wear__: It is important to note that flash memory should be used carefully to avoid unnecessary usage. Memory should not be written to in loops, as this can quickly use up the limited number of write cycles.

__Data location__: the applicative code is stored at the top of the flash memory space. The eeprom_emulation allocated memory is located in the EDATA part of the memory layout. This is important to make sure the program code is not affected when storing eeprom_emulation data.

__Data granularity__: Data alignment and data size selection for programming and reading are managed by the eeprom_emulation solution.


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the STM32Cube firmware package.")

This [application note](https://www.st.com/resource/en/application_note/an5701-stm32cube-mcu-package-examples-for-stm32u5-series-stmicroelectronics.pdf)
explains further this XXX feature.

The documentation of the drivers of the relevant STM32 series contains more detailed information.

the user manual of the eeprom_emulation utility contains more detailed information about using the eeprom_emulation.

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/embedded-software.html).


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
