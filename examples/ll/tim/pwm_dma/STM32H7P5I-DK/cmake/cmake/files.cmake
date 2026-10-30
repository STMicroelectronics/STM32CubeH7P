# file-format: 1.0.0
if(CMAKE_BUILD_TYPE STREQUAL "release_GCC_STM32H7P5I-DK")
  target_sources(${CMAKE_PROJECT_NAME} PRIVATE ../../application/example.c ../../application/main.c ../../application/stm32h7pxx_ll_example.c ../../application/example.h ../../application/main.h ../../application/ll_example.h)
elseif(CMAKE_BUILD_TYPE STREQUAL "debug_GCC_STM32H7P5I-DK")
  target_sources(${CMAKE_PROJECT_NAME} PRIVATE ../../application/example.c ../../application/main.c ../../application/stm32h7pxx_ll_example.c ../../application/example.h ../../application/main.h ../../application/ll_example.h)
endif()
