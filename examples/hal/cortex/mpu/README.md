<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *hal_cortex_mpu*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

How to use the Cortex MPU to manage a memory region as privileged read only, perform an authorized read, and handle a memory fault triggered by an unauthorized write access.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, MPU regions, and the system clock.

The application executes the following __example steps__:

__Step 1__: Initializes the Cortex MPU to configure a memory region in SRAM as privileged read only.

__Step 2__: Reads from the privileged read-only region.

__Step 3__: Attempts an unauthorized write to the privileged read only region to trigger and handle a memory management fault.

__Step 4__: Deinitializes the Cortex MPU before leaving the scenario.

__End of example__: Reports the outcome of the example via the variable **`ExecStatus`**.
If the memory fault is correctly detected and handled, the **status LED** remains turned on to indicate success.

By enabling `USE_TRACE`, you can follow the execution step in the terminal logs:

```text
[INFO] Step 1: CORTEX initialization COMPLETED.
[INFO] Step 2: Reads from the privileged read-only region.
[INFO] Step 3: Attempts an unauthorized write to the privileged read-only region.
[INFO] Write access violation detected (caught by MPU).
[INFO] Step 4: CORTEX deinitialization COMPLETED.
```


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the STM32Cube firmware package.")

__MPU__:

This example demonstrates the Cortex MPU configured as indicated below:

  - A region in SRAM is configured as privileged read-only.
  - The memory attribute index used is HAL_CORTEX_MPU_MEM_ATTR_1.
  - The MPU is globally enabled with HAL_CORTEX_MPU_Enable().


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

No specific hardware setup is needed for this example.

### __3.2. Specific board setups__

This section describes the exact hardware configurations of your project.

<details>
  <summary>On STM32H7P series.</summary>
  <details>
    <summary>On board NUCLEO-H7P5II.</summary>

  |  MCU pin  |  Signal name  |  User Label   |
  |:---------:|:-------------:|:-------------:|
  |    PG9    |     GPIO      | MX_STATUS_LED |
  |    PA2    |   USART2_TX   |       -       |

  </details>

  <details>
    <summary>On board STM32H7P5I-DK.</summary>

  |  MCU pin  |  Signal name  |  User Label   |
  |:---------:|:-------------:|:-------------:|
  |    PH6    |     GPIO      | MX_STATUS_LED |
  |    PA2    |   USART2_TX   |       -       |

  </details>
</details>
</details>


## __4. Troubleshooting__

[![Troubleshooting](doc/debug_with-Troubleshooting.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/debug/debug_toc.html "An offline version is also available in the STM32Cube firmware package.")

Here are the points of attention for this specific example:

__Exception flow__: The memory management exception is not a standard interrupt. When the handler returns, execution resumes at the faulty instruction, potentially causing an infinite fault loop.

__Safe recovery__: To avoid being stuck, the example uses setjmp/longjmp to save and restore the program context, allowing the application to recover gracefully after a fault.


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the STM32Cube firmware package.")

The documentation of the drivers of the relevant STM32 series contains more detailed information.

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/embedded-software.html).


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
