<img src="doc/subbrand-stm32.svg" width="50" alt="STM32 Subbrand Logo"/>

# __Example: *hsp_engine_fir_rfft_seq*__

**Example version:** 2.0.0

[![User Manual](doc/read_the-UM.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/index.html "An offline version is also available in the STM32Cube firmware package.")

How to use the Middleware HSP Engine to process a FIR filter followed by an RFFT in Sequencer Mode with DMA-triggered processing.

This example shows how to perform a low-pass FIR filtering followed by an RFFT and a magnitude computation on successive sample blocks.

The input signal, sampled at 48000 Hz, is a combination of sinusoids at 750 Hz, 3000 Hz, 6000 Hz, and 8000 Hz split into 3 buffers of 256 samples.

After the FIR filtering, the dominant frequencies remaining in the spectrum are 750 Hz and 3000 Hz.

The input samples and the FIR coefficients are precomputed offline and embedded as static tables in the example. They are provided as ready-to-use demonstration data.

The HSP computation is always performed in the **BRAMAB** memory. Therefore, the HSP working buffers must be placed in this memory region.

This example demonstrates, the following services provided by the middleware:

  1. The allocation of resources in the **HSP BRAMAB** memory region.
      - **Dynamic allocation** of an input buffer for samples.
      - **Dynamic allocation** of a result buffer used by the FIR, RFFT, and magnitude processing.
      - **Dynamic allocation** of a FIR state buffer (*required for a FIR*).
      - **Static allocation** of the FIR coefficients.
      - **Static allocation** of a variable used to count the number of Processing List calls.
  2. The recording of a **Processing List** to process a **FIR** filter, an **RFFT**, and a magnitude computation in **Sequencer Mode**.
  3. The configuration of an **HSP Event** to trigger the Processing List on a DMA Transfer Complete event.
  4. The use of **Ping/Pong buffers** to overlap data transfers and processing.
  5. The trigger of a DMA transfer from the Processing List to export the computed RFFT magnitude.


## __1. Detailed scenario__

__Initialization phase__: At main program start, the `mx_system_init()` function is called. It initializes the peripherals, nonvolatile memory (such as flash memory, NVM, or external memories), MPU regions (if applicable), the system clock, and the SysTick.

The application executes the following __example steps__:

__Step 1__: Initializes the HAL HSP Driver and the Middleware HSP Engine.

  In the MW Init step, these resources listed below are allocated in the HSP BRAMAB memory region:

  - **p_buff_in** to store the data to process
  - **p_results** to store the FIR, RFFT, and magnitude results
  - **fir_state_id** to store the **FIR** filter state buffer

  These static resources are also allocated in HSP BRAM:

  - **fir_coefs** to store the **FIR** filter coefficients
  - **pl_call** to count the number of Processing List calls

  Record a Processing List to process a **FIR** filter followed by an **RFFT** and a magnitude computation in **Sequencer Mode**.
  The Processing List performs these operations in sequence:

  1. Start recording the Processing List.
  2. Increment the **pl_call** counter.
  3. Call the **FIR** processing function to filter the input data and store the results in the result buffer.
  4. Call the **RFFT** processing function on the filtered data.
  5. Call the complex magnitude processing function on the RFFT output.
  6. Set **TRGO0** so that the DMA transfer of results can be triggered by the Processing List.
  7. Stop recording the Processing List.
  8. Configure the HSP event so that the Processing List is triggered on the rising edge of the DMA Transfer Complete event.

__Step 2__: Initiate the first processing.

  - Copy the first sample series into the Ping buffer in system memory.
  - Start the DMA transfer that exports the future RFFT magnitude results from **HSP BRAMAB** to the Ping result buffer.
  - Start the DMA transfer that copies the Ping input buffer to **p_buff_in** in **HSP BRAMAB**.

__Step 3__: Process the next sample series with Ping/Pong buffering.

  For each next sample series:

  - Fill the Pong buffer while the Ping buffer is being processed.
  - Wait for the DMA transfer of the previous results to complete.
  - Start the DMA transfer used to export the next RFFT magnitude results.
  - Start the DMA transfer that copies the Pong input buffer to **HSP BRAMAB**.
  - Let the DMA Transfer Complete event trigger the recorded Processing List.
  - Check the validity of the spectral results by:
    - Analyze the exported RFFT magnitude buffer.
    - Extract the dominant frequencies whose magnitude is above the configured threshold.
    - Check that exactly 2 dominant frequencies are found.
    - Check that these frequencies are **750 Hz** and **3000 Hz**.
  - Swap the Ping and Pong Buffer addresses for the next iteration.

__Step 4__: Report successful completion after all processing iterations have passed the validation checks.

__End of example__: If all iterations complete and the detected dominant frequencies are **750 Hz** and **3000 Hz**, the example exits with success.


You can verify that the example runs properly via the status LED and the `ExecStatus` variable.

If you enable `USE_TRACE`, you can follow these execution steps in the terminal logs:

```text
[INFO] Step 1: MW HSP Engine initialization COMPLETED.
[INFO] Step 2: Initiate process.
[INFO] Step 3: Process FIR + RFFT.
[INFO] Step 4: FIR + RFFT process OK.
[INFO] Step 5: de-init.
...
```


## __2. Example configuration__

[![Configuration Manual](doc/configure_with-ConfigurationMa.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/configure/config_toc.html "An offline version is also available in the STM32Cube firmware package.")

The HSP peripheral is booted during the MW HSP Engine initialization where the HSP Firmware is loaded in HSP CRAM (Code part) & DRAM (Data part) memory regions.

This example uses **Sequencer Mode**. The Processing List is configured to run after a DMA Transfer Complete event and to emit **TRGO0** so that another DMA transfer can export the results.

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

__Frequency check__: The result validation relies on the magnitude threshold and on the expected dominant frequencies of the filtered signal. If you modify the input dataset, the FIR coefficients, or the FFT size, update the expected frequencies accordingly.

__AC6__: When building this example with **AC6** using **Open-CMSIS-Toolbox** and requesting the **bin** output format, the generated binary output can be split into two region-specific images, **ROM** and **HSP_DATA_BRAM**. This behavior is expected because the application uses separate memory regions for the main code and for the HSP data buffers. If these region-specific binary images are used, each image must be flashed at its corresponding target address. For this reason, it is recommended to use the **.hex** or **.axf** output instead.


## __5. See Also__

[![SeeAlso](doc/go_further_with-STM32.svg)](https://dev.st.com/stm32cube-docs/examples/arch-v1/en/more/more_toc.html "An offline version is also available in the STM32Cube firmware package.")

The documentation of the drivers of the relevant STM32 series contains more detailed information.

More information about the STM32 ecosystem can be found in the [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone/embedded-software.html).


## __6. License__

Copyright (c) 2026 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE file in the root directory
of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
