cmake_minimum_required(VERSION 3.12)

# This lets CMake work with stuff that's not updated to at least version 3.12
# Probably don't need it for my arduino stuff
# cmake_policy(SET CMP0074 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must be before the project command:
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../Toolchain-Adafruit-nRF52480.cmake)

project(LeftKeyboardClientWire)

set(MY_SOURCE_FILES WiredSketchLeft.ino)

# It's annoying that I can't configure this in the toolchain file
# This makes .ino files compile as C++ files
set_source_files_properties(${MY_SOURCE_FILES} PROPERTIES LANGUAGE CXX)
add_definitions("-x c++")

add_executable(leftFirmware ${MY_SOURCE_FILES})
