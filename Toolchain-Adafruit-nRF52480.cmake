# Documentation: https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html

# Target OS: Docs say to set this to "Generic" but I kinda want to call it "Arduino" ??
# Automatically sets CMAKE_CROSSCOMPILING to True (use that mostly, not this value?)
set(CMAKE_SYSTEM_NAME Generic)

# Arduino IDE Version, maybe?
# Described as "the version of your target system"
set(CMAKE_SYSTEM_VERSION 1.8.19)

# Docs say "anything I want" and is used to load a
# ${CMAKE_SYSTEM_NAME}-COMPILER_ID-${CMAKE_SYSTEM_PROCESSOR}.cmake file
# So I guess I could factor things nicely into pieces, enabling this set of stuff to be
# generated & installed in a global (or user-global) location, right?
set(CMAKE_SYSTEM_PROCESSOR Adafruit-nRF52480)

set(triple arm-none-eabi)

# You can use CMAKE_HOST_* (SYSTEM/SYSTEM_NAME/SYST EM_VERSION/SYSTEM_PROCESSOR/WIN32/UNIX/APPLE)
# for host dependent stuff in here if you want...

# Compiler names

# *Prepended* to the search directories
if(CMAKE_HOST_WIN32)
  set(CMAKE_FIND_ROOT_PATH "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi" "c:/program files (x86)/Arduino/hardware/tools/arm")
  set(CMAKE_C_COMPILER "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02/bin/arm-none-eabi-gcc.exe")
  set(CMAKE_CXX_COMPILER "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02/bin/arm-none-eabi-g++.exe")
  set(ARDUINO_ADAFRUIT_DIR "$ENV{HOME}/AppData/Local/Arduino15/packages/adafruit")
# Docs say this is unnecessary for GNU toolchains...
# set (CMAKE_CXX_COMPILER g++)
elseif(CMAKE_HOST_APPLE)
  # Definitely wrong currently
  set(CMAKE_FIND_ROOT_PATH "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc")
  set(CMAKE_C_COMPILER "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/9-2019q4/bin/arm-none-eabi-gcc")
  set(CMAKE_CXX_COMPILER "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/9-2019q4/bin/arm-none-eabi-g++")
  set(ARDUINO_ADAFRUIT_DIR "$ENV{HOME}/Library/Arduino15/packages/adafruit")
  elseif(CMAKE_HOST_UNIX)
  # Definitely wrong currently
  set(CMAKE_FIND_ROOT_PATH "/usr/local/bin" "/usr/bin")
endif()
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER_TARGET ${triple})

# Skip tests for now, because the test requires not just compilation, but *linking*
# and since in order to link, you need to build some of the hardware support libraries
# it won't link, so the *compiler* test fails.
# BRILLIANT!
set(CMAKE_C_COMPILER_WORKS 1 CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS 1 CACHE INTERNAL "")

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
# KBF: I think this shouldn't be "NEVER" because a number of programs are host-only things
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Sure would be nice if I could do this and have it stick:
# set (CMAKE_CXX_SOURCE_FILE_EXTNEIONS c++;cc;cpp;cxx;ino;C;CPP;CXX)

# Need to add some flags, yeah?
set(BUILD_CORE_PATH "${ARDUINO_ADAFRUIT_DIR}/hardware/nrf52/1.3.0/cores/nRF5/")
set(BUILD_MCU cortex-m4)
set(BUILD_FLOAT_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16 -u _printf_float")
set(BUILD_ARCH NRF52)
set(BUILD_F_CPU 64000000)
set(NORDIC_PATH "${BUILD_CORE_PATH}/nordic")
set(COMPILER_LDFLAGS "-mcpu=${BUILD_MCU} -mthumb ${BUILD_FLOAT_FLAGS} -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--wrap=malloc -Wl,--wrap=free --specs=nano.specs --specs=nosys.specs")
set(RUNTIME_TOOLS_CMSIS_5_7_0_PATH "${ARDUINO_ADAFRUIT_DIR}/tools/CMSIS/5.7.0")
set(COMPILER_ARM_CMSIS_LDFLAGS "-L${RUNTIME_TOOLS_CMSIS_5_7_0_PATH}/CMSIS/DSP/Lib/GCC/ -larm_cortexM4lf_math")
set(COMPILER_CPP_FLAGS "-mcpu=${BUILD_MCU} -mthumb -g ${COMPILER_WARNING_FLAGS} ${BUILD_FLOAT_FLAGS} -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD")
set(BUILD_FLAGS_NRF "-DSOFTDEVICE_PRESENT -DARDUINO_NRF52_ADAFRUIT -DNRF52_SERIES -DDX_CC_TEE -DLFS_NAME_MAX=64 ${COMPILER_OPTIMIZATION_FLAG} ${BUILD_DEBUG_FLAGS} ${BUILD_LOGGER_FLAGS} ${BUILD_SYSVIEW_FLAGS} ${COMPILER_ARM_CMSIS_C_FLAGS} -I${NORDIC_PATH} -I${NORDIC_PATH}/nrfx -I${NORDIC_PATH}/nrfx/hal -I${NORDIC_PATH}/nrfx/mdk -I${NORDIC_PATH}/nrfx/soc -I${NORDIC_PATH}/nrfx/drivers/include -I${NORDIC_PATH}/nrfx/drivers/src -I${NORDIC_PATH}/softdevice/${BUILD_SD_NAME}_nrf52_${BUILD_SD_VERSION}_API/include -I${NORDIC_PATH}/softdevice/${BUILD_SD_NAME}_nrf52_${BUILD_SD_VERSION}_API/include/nrf52 -I${RTOS_PATH}/Source/include -I${RTOS_PATH}/config -I${RTOS_PATH}/portable/GCC/nrf52 -I${RTOS_PATH}/portable/CMSIS/nrf52 -I${BUILD_CORE_PATH}/sysview/SEGGER -I${BUILD_CORE_PATH}/sysview/Config -I${RUNTIME_PLATFORM_PATH}/libraries/Adafruit_TinyUSB_Arduino/src/arduino")

add_compile_definitions(
  F_CPU=${BUILD_F_CPU}
  ARDUINO=1819
  ARDUINO_NRF52840_ITSYBITSY
  ARDUINO_NRF52_ITSYBITSY
  ARDUINO_ARCH_${BUILD_ARCH}
  ARDUINO_BSP_VERSION="1.2.0")
set(CMAKE_CPP_FLAGS "${COMPILER_CPP_FLAGS} ${BUILD_FLAGS_NRF}")
include_directories(AFTER SYSTEM ${BUILD_CORE_PATH} ${BUILD_CORE_PATH}/../../variants/itsybitsy_nrf52840_express)
# ${COMPILER_CPP_FLAGS}
# ${BUILD_FLAGS_NRF} ${SYS_INCLUDES}
set(CMAKE_EXE_LINKER_FLAGS
  "-Ofast -Wl,--gc-sections -save-temps -L${BUILD_CORE_PATH}/linker -Tnrf52840_s140_v6.ld -Wl,-Map,ye-old-map-file.map ${COMPILER_LDFLAGS} -lm -Wl,--start-group ${COMPILER_ARM_CMSIS_LDFLAGS} -Wl,--end-group")

# "${BUILD_PATH}/system.a"
# ${COMPILER_LIBRARIES_LDFLAGS}
# -Wl,--end-group
