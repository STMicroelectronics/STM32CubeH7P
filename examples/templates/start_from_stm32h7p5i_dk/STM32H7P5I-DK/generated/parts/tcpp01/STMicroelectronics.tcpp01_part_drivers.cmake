# origin-pack: generated_STMicroelectronics::tcpp01_part_drivers@0.0.1
# file-format: 1.0.0
project(generated_STMicroelectronics_tcpp01_part_drivers_0_0_1)
cmake_minimum_required(VERSION 3.30)
add_library(generated_STMicroelectronics_tcpp01_part_drivers_0_0_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_generated_STMicroelectronics_tcpp01_part_drivers_0_0_1)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:STM32CubeMX2 Config#Csub:TCPP01#Cversion:1.0.0#generated:true")
endif()

# All conditions used by this package

# condition: generated_STMicroelectronics.tcpp01_part_drivers.0.0.1:TCPP01 CFG Condition
# description: STMicroelectronics configuration for TCPP01 part driver
set(generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_CFG_Condition "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:USBPD#.*Csub:TCPP01 Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:USBPD#.*Csub:TCPP01 IO#.*Cvariant:ADC EXTI(#.*|$)>,>>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_CFG_Condition enabled")


# condition: generated_STMicroelectronics.tcpp01_part_drivers.0.0.1:TCPP01 Core Condition
# description: STMicroelectronics TCPP01 Core Driver
set(generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_Core_Condition "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:USBPD#.*Csub:TCPP01 IO(#.*|$)>,>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_Core_Condition enabled")


# condition: generated_STMicroelectronics.tcpp01_part_drivers.0.0.1:TCPP01 Custom IO Condition
# description: 
set(generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_Custom_IO_Condition "1")
message(DEBUG "CMSIS condition generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_Custom_IO_Condition enabled")


# condition: generated_STMicroelectronics.tcpp01_part_drivers.0.0.1:TCPP01 IO ADC EXTI Condition
# description: STMicroelectronics TCPP01 IO ADC Polling and EXTI Drivers
set(generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_IO_ADC_EXTI_Condition "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:ADC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:EXTI(#.*|$)>,>>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_IO_ADC_EXTI_Condition enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:STM32CubeMX2 Config#Csub:TCPP01#Cversion:1.0.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Board_Part_STM32CubeMX2_Config_TCPP01_1_0_0")
  target_compile_definitions(generated_STMicroelectronics_tcpp01_part_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_CFG_Condition}:-DCMSIS_USE_generated_Board_Part_STM32CubeMX2_Config_TCPP01_1_0_0=1>")
  target_include_directories(generated_STMicroelectronics_tcpp01_part_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_CFG_Condition}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_tcpp01_part_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.tcpp01_part_drivers.0.0.1_TCPP01_CFG_Condition}:${CMAKE_CURRENT_LIST_DIR}/mx_tcpp01.c>")
endif()

