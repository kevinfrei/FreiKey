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
set(CMAKE_SYSTEM_PROCESSOR Teensy40)

# You can use CMAKE_HOST_* (SYSTEM/SYSTEM_NAME/SYST EM_VERSION/SYSTEM_PROCESSOR/WIN32/UNIX/APPLE)
# for host dependent stuff in here if you want...

# Compiler names
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
# Docs say this is unnecessary for GNU toolchains...
# set (CMAKE_CXX_COMPILER g++)

# *Prepended* to the search directories
if(CMAKE_HOST_WIN32)
  set(CMAKE_FIND_ROOT_PATH "c:/program files (x86)/Arm GNU Toolchain arm-non-eabi" "c:/program files (x86)/Arduino/hardware/tools/arm")
elseif(CMAKE_HOST_APPLE)
  # Definitely wrong currently
  set(CMAKE_FIND_ROOT_PATH "/Applications/Teensyduino.app/" "/Applications/Arduino.app")
elseif(CMAKE_HOST_UNIX)
  # Definitely wrong currently
  set(CMAKE_FIND_ROOT_PATH "/usr/local/bin" "/usr/bin")
endif()

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
# KBF: I think this shouldn't be "NEVER" because a number of programs are host-only things
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
