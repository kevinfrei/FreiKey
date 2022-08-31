
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
set(CMAKE_SYSTEM_PROCESSOR Teensy40)

set(targettriple arm-none-eabi)

# You can use CMAKE_HOST_* (SYSTEM/SYSTEM_NAME/SYST EM_VERSION/SYSTEM_PROCESSOR/WIN32/UNIX/APPLE)
# for host dependent stuff in here if you want...
if(CMAKE_HOST_WIN32)
  set(CMAKE_FIND_ROOT_PATH "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi" "c:/program files (x86)/Arduino/hardware/tools/arm")
  set(CMAKE_ASM_COMPILER "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02/bin/arm-none-eabi-gcc.exe")
  set(CMAKE_C_COMPILER "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02/bin/arm-none-eabi-gcc.exe")
  set(CMAKE_CXX_COMPILER "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02/bin/arm-none-eabi-g++.exe")
  set(CMKARD_RUNTIME_OS windows)
  set(CMKARD_RUNTIME_PLATFORM_PATH "c:/program files (x86)/Arduino/hardware/teens/avr")
elseif(CMAKE_HOST_APPLE)
  # Definitely wrong currently
  set(CMAKE_FIND_ROOT_PATH "/Applications/Teensyduino.app/" "/Applications/Arduino.app")
  set(CMAKE_FIND_ROOT_PATH "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc")
  set(CMAKE_C_COMPILER "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/9-2019q4/bin/arm-none-eabi-gcc")
  set(CMAKE_CXX_COMPILER "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/9-2019q4/bin/arm-none-eabi-g++")
  set(ARDUINO_ADAFRUIT_DIR "$ENV{HOME}/Library/Arduino15/packages/adafruit")
elseif(CMAKE_HOST_UNIX)
  # Definitely wrong currently
  set(CMAKE_FIND_ROOT_PATH "/usr/local/bin" "/usr/bin")
endif()

set(CMAKE_C_COMPILER_TARGET ${targettriple})
set(CMAKE_CXX_COMPILER_TARGET ${targettriple})

# Skip tests, because the test requires not just compilation, but *linking*.
# In order to link, you need to build some of the hardware support libraries.
# Thus, it won't link, so the *compiler* test fails.
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