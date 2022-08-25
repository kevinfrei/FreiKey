cmake_minimum_required(VERSION 3.12)

# What does this do, again?
cmake_policy(SET CMP0074 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must be before the project command:
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../Toolchain-Adafruit-nRF52480.cmake)

project(LeftKeyboardClientWire)

set(MY_SOURCE_FILES WiredSketchLeft.ino)

# A little annoying that I can't configure this globally in the toolchain file, but 
set_source_files_properties(${MY_SOURCE_FILES} PROPERTIES LANGUAGE CXX)
add_definitions("-x c++")

add_executable(leftFirmware ${MY_SOURCE_FILES})