cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locations other parts of the system require...
if(CMAKE_HOST_WIN32)
  set(TEENSY4_LIB_ROOT_DIR "C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4")
  set(A2CM_DEFAULT_LIB_PATH "C:/PROGRA~2/Arduino/hardware/teensy/avr/libraries")
  set(A2CM_TEENSY4_LIB_ROOT_DIR ${TEENSY4_LIB_ROOT_DIR})
elseif(CMAKE_HOST_APPLE)
  set(TEENSY4_LIB_ROOT_DIR "/Applications/Teensyduino.app/Contents/Java/hardware/teensy/avr/cores/teensy4")
  set(A2CM_DEFAULT_LIB_PATH "/Applications/Teensyduino.app/Contents/Java/hardware/teensy/avr/libraries")
  set(A2CM_TEENSY4_LIB_ROOT_DIR ${TEENSY4_LIB_ROOT_DIR})
elseif(CMAKE_HOST_UNIX)
  message(FATAL_ERROR "Not implemented for Unix yet")
else()
  message(FATAL_ERROR "Unknown host machine")
endif()

set(A2CM_ST77XX_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/ST77xx")
set(A2CM_BusIO_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/BusIO")
set(A2CM_GFX_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/GFX")

# This should be generated by Arduino2CMake
include(tools/teensy/teensy40/arduino_config.cmake)

project(Laptype)

# Configure the 'menu' stuff
teensy40_menu_selections(keyboard 600 o2std en-us)
set(A2CM_SERIAL_PORT COM8:)

# Add the board library - Generated by Arduino2CMake
add_subdirectory(tools/teensy/teensy40)

# Add any additional arduino libraries for the target
# Again, generated. Probably need a 'extra deps' addition to cover
# Arduino-installed-by-default library dependencies
add_subdirectory(tools/libs/busio)
add_subdirectory(tools/libs/wire)
add_subdirectory(tools/libs/eeprom)
add_subdirectory(tools/libs/spi)
add_subdirectory(tools/libs/gfx)
add_subdirectory(tools/libs/st77xx)

macro(add_custom_module modname hdrPath)
  project(module_${modname})
  add_library(module_${modname} OBJECT ${ARGN})
  target_include_directories(module_${modname} PUBLIC ${hdrPath})
  target_include_directories(
    module_${modname}
    PRIVATE
    ../../include
    ../../include/laptype
    ../../include/teensy
  )
  target_link_libraries(module_${modname} PUBLIC teensy4_syslib)
endmacro()

# Add my own local libraries, too
# These are just object libraries
add_subdirectory(modules/display)
add_subdirectory(modules/calculator)
add_subdirectory(modules/images)
add_subdirectory(modules/editline)
add_subdirectory(modules/tetris)
add_subdirectory(modules/menu)

#[=[
# ^Multi-line comment: Neato...
# Non-menu stuff that's specific to Teensy:
set(A2CM_EXTRA_TIME_LOCAL 0) # TODO: Make this dynamically calculated at compile time?
set(A2CM_SERIAL_PORT COM18) # TODO: Can we look for it?
set(A2CM_SERIAL_PORT_LABEL ${CMKARD_SERIAL_PORT})
set(A2CM_SERIAL_PORT_PROTOCOL serial)
]=]

# Not quite sufficient: Need to post-process the binary
# And, if -Dflash is called, flash the thing, right?
add_arduino_executable(
  laptype.elf
  dbgcfg.cpp
  kbreporter.cpp
  mainloop.cpp
  scanning.cpp
  localscan.cpp
  modulekeyboard.cpp
  laptype.cpp
)
target_include_directories(
  laptype.elf
  AFTER
  PRIVATE
  include
  include/teensy
  include/laptype
  include/localscan
)
target_link_libraries(
  laptype.elf
  PRIVATE

  # The core system library
  teensy4_syslib

  # The Arduino libraries
  Adafruit_BusIO_lib
  SPI_lib
  Adafruit_GFX_Library_lib
  Adafruit_ST77XX_lib
  Wire_lib
  EEPROM_lib

  # My keyboard adding modules
  # They're handled just like arduino libraries...
  module_display
  module_editline
  module_calculator
  module_images
  module_tetris
  module_menu
)

# This makes .ino files compile as C++ files:
# set_source_files_properties(${MY_SOURCE_FILES} PROPERTIES LANGUAGE CXX)
# add_definitions("-x c++")
# It's annoying that youcan't configure ino files as C++ in the toolchain file