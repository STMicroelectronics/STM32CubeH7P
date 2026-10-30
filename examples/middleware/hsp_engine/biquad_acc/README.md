<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *hsp_engine_biquad_acc*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

How to use the Middleware HSP Engine to process a BIQUAD in Accelerator Mode.

This example shows how to perform a 10 Hz High-pass filter with a BIQUAD.

The input samples are a combination of two sinusoids at 10 Hz and 100 Hz.

The filtered signal is a 100 Hz sine wave.

The input samples, the BIQUAD coefficients, and the reference results are
precomputed offline and embedded as static tables in the example. They are
provided as ready-to-use demonstration data.

The HSP computation is always performed in the **BRAMAB** memory. Therefore, the HSP working buffers must be placed in this memory region.

This example demonstrates, the following services provided by the middleware:

  1. The allocation of resources in the **HSP BRAMAB** memory region.
      - **Dynamic allocation** of buffers for input and output data.
      - **Dynamic allocation** of a BIQUAD state buffer (*Required for a BIQUAD*)
      - **Static allocation** of a variable to store the RMS value (*see item 3*)
  2. The execution of a **BIQUAD** filter with a **HSP Direct command** (*Accelerator Mode*)
  3. The computing of **RMS** (*Root Mean Square*) to check the validity of the BIQUAD filter results.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

__Step 1__: Initializes the HAL HSP Driver and the Middleware HSP Engine.

  In the MW Init step, these resources listed below are allocated in the HSP BRAMAB memory region :

  - **p_buff_in** to store the data to process
  - **p_coef** to store the **BIQUAD** filter coefficients
  - **p_buff_out** to store the **BIQUAD** filter results

__Step 2__: Copy resources in HSP BRAM before processing.

  - Copy the samples to process in the buffer pointed by **p_buff_in**
  - Copy the **BIQUAD** coefficients in the buffer pointed by **p_coefs**

__Step 3__: Demonstrate how to process a BIQUAD in Accelerator Mode.

  - Call the **BIQUAD processing function**

__Step 4__: Demonstrate how to check the validity of BIQUAD results based on reference data.

  - Reuse the **p_buff_in** to copy the *BIQUAD reference results*
  - Process a signal difference between the reference results and those computed and stored in **p_buff_out**
  - Compute the **RMS** (*Root Mean Square*) value

__End of example__: If the RMS value is within the tolerance range, that is, less than 10^-6, the example exits with success.


You can verify that the example runs properly via the status LED and the `ExecStatus` variable.

If you enable `USE_TRACE`, you can follow these execution steps in the terminal logs:

```text
[INFO] Step 1: MW HSP Engine initialization COMPLETED.
[INFO] Step 2: Samples & coefficients loaded into HSP BRAMAB buffers.
[INFO] Step 3: BIQUAD filter executed.
[INFO] Step 4: BIQUAD process OK.
[INFO] Step 5: de-init.
...
```


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the STM32Cube firmware package.")

The HSP peripheral is booted during the MW HSP Engine initialization where the HSP Firmware is loaded in HSP CRAM (Code part) & DRAM (Data part) memory regions.

No HSP configuration is required to execute any processing functions in Accelerator Mode. These functions are provided by the **Middleware HSP Engine** via the **Direct Command** module.

The HSP works in the **HSP BRAMAB** memory region. Then all input data (like samples, coefficient...) must be copied into this region before the execution of any processing functions.

For more details about HSP memory regions such as **BRAMAB**, refer to the STM32 Reference Manual and to the **Middleware HSP Engine** documentation for the selected STM32 series.


## __3. Hardware environment and setup__

### __3.1. Generic Setup__

No specific hardware setup needed for this example.

### __3.2. Specific board setups__

This section describes the exact hardware configurations of your project.
<details>
  <summary>On STM32H7P series.</summary>
  <details>
  <summary>On board NUCLEO-H7P5II.</summary>

  | Board connector   | MCU pin | Signal name          | ARDUINO <br> connector pin | User Label        |
  | :---:             | :---:   | :---:                | :---:                      | :---:             |
  | CN5-6             | PG9     | User green LED (LD1) | D13                        | MX_STATUS_LED     |
  </details>
</details>


## __4. Troubleshooting__

[![Troubleshooting](doc/debug_with-Troubleshooting.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/debug/debug_toc.html "An offline version is also available in the STM32Cube firmware package.")

Find below the points of attention for this specific example.

__Data cache__: The HSP Engine middleware and the HSP HAL driver are not functional when the Data Cache is enabled. To address this, the MPU is configured to mark the AHBSRAM3 and HSPBRAMAB memory regions as non-cacheable.

__Transfer data in HSP BRAMAB__: When transferring any data (samples, coefficient...) in HSP BRAMAB, make sure to call the barrier `__DSB()` before to process any HSP processing functions.

__AC6__: When building this example with **AC6** using **Open-CMSIS-Toolbox** and requesting the **bin** output format, the generated binary output can be split into two region-specific images, **ROM** and **HSP_DATA_BRAM**. This behavior is expected because the application uses separate memory regions for the main code and for the HSP data buffers. If these region-specific binary images are used, each image must be flashed at its corresponding target address. For this reason, it is recommended to use the **.hex** or **.axf** output instead.


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the STM32Cube firmware package.")

The documentation of the drivers of the relevant STM32 series contains more detailed information.

For more details about the HSP memory regions and the Middleware services used by this example, refer to the **Middleware HSP Engine** documentation and to the STM32 Reference Manual of the selected device.

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/embedded-software.html).


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
