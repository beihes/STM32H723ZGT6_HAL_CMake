# THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.20)

# 环境选择
if(WIN32)
    MESSAGE(STATUS "Now is windows!")
    set(TOOLPATH "C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/arm-none-eabi-")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++.exe)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_AR ${TOOLPATH}ar.exe)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy.exe)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump.exe)
    set(SIZE ${TOOLPATH}size.exe)
elseif(UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_AR ${TOOLPATH}ar)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump)
    set(SIZE ${TOOLPATH}size)
else()
    MESSAGE(STATUS "Unsupported system!")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(STM32H723ZGT6_HAL_CMake C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Uncomment for hardware floating point
add_compile_options(-mfloat-abi=hard -mfpu=fpv5-d16)
add_compile_options(-mcpu=cortex-m7 -mthumb)
add_compile_options(-ffunction-sections -fdata-sections -fmessage-length=0)
add_compile_options(-specs=nano.specs)

message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(VERBOSE "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(VERBOSE "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(VERBOSE "Maximum optimization for size")
    add_compile_options(-Os)
else()
    message(VERBOSE "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif()

add_compile_options(-Wall)

# 库文件
include_directories(
    Core/Inc
    Core/ThreadSafe
    Drivers/CMSIS/Device/ST/STM32H7xx/Include
    Drivers/CMSIS/Include
    Drivers/STM32H7xx_HAL_Driver/Inc
    Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    FATFS/App
    FATFS/Target
    Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc
    Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    Middlewares/Third_Party/Fatfs/src
    Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    Middlewares/Third_Party/FreeRTOS/Source/include
    Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    USB_DEVICE/App
    USB_DEVICE/Target)

add_definitions(
    -DDEBUG 
    -DUSE_PWR_LDO_SUPPLY
    -DUSE_HAL_DRIVER 
    -DSTM32H723xx 
    -DSTM32_THREAD_SAFE_STRATEGY=4)

# 源文件
file(GLOB_RECURSE SOURCES
    "Core/Src/*.c"
    "Core/Startup/startup_stm32h723zgtx.s"
    "Core/ThreadSafe/*.c"
    "Drivers/STM32H7xx_HAL_Driver/Src/*.c"
    "FATFS/App/*.c"
    "FATFS/Target/*.c"
    "Middlewares/ST/STM32_USB_Device_Library/*.c"
    "Middlewares/Third_Party/Fatfs/*.c"
    "Middlewares/Third_Party/FreeRTOS/*.c"
    "USB_DEVICE/App/*.c"
    "USB_DEVICE/Target/*.c"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/STM32H723ZGTX_FLASH.ld
    # ${CMAKE_SOURCE_DIR}/STM32H723ZGTX_RAM.ld
)

add_link_options(-mfloat-abi=hard -mfpu=fpv5-d16)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m7 -mthumb)
add_link_options(-T ${LINKER_SCRIPT})
add_link_options(-specs=nano.specs -u _printf_float)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")