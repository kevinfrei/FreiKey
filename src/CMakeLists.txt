cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must be *before* the project command:
set(
  CMAKE_TOOLCHAIN_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/teensy/Toolchain.cmake
)

project(Laptype)

# Configure the 'menu' stuff
# I'm not sure if I want to handle this stuff like this
# It only changes when you rebuild the make system, so I
# coudl just use some variables that feed into a subdir or something...
add_subdirectory(tools/teensy/teensy40/menu/in-usb/keyboard)
add_subdirectory(tools/teensy/teensy40/menu/in-speed/600)
add_subdirectory(tools/teensy/teensy40/menu/in-opt/o2std)
add_subdirectory(tools/teensy/teensy40/menu/in-keys/en-us)

# Or, instead, do this:
set(A2CM_MENU_IN_USB keyboard)
set(A2CM_MENU_IN_SPEED 600)
set(A2CM_MENU_IN_OPT o2std)
set(A2CM_MENU_IN_KEYS en-us)

# Or, maybe do this:
# add_subdirectory(tools/teensy/teensy40/menu)
# add_library(menu_in_usb ALIAS in_usb_keyboard)
# add_library(menu_in_speed ALIAS in_speed_600)
# add_library(menu_in_opt ALIAS in_opt_o2std)
# add_library(menu_in_keys ALIAS in_keys_en_us)
# Nah: That sucks. Don't do that :)

# Add the board library - this uses those 4 libraries
add_subdirectory(tools/teensy/teensy40)

# Add any additional libraries for the target
add_subdirectory(tools/libs/busio)
add_subdirectory(tools/libs/spi)
add_subdirectory(tools/libs/gfx)
add_subdirectory(tools/libs/st77xx)
add_subdirectory(tools/libs/wire)
add_subdirectory(tools/libs/eeprom)

#[-[
# ^^ Multi-line comment: Neato...
# Non-menu stuff that's specific to Teensy:
set(A2CM_EXTRA_TIME_LOCAL 0) # TODO: Make this dynamically calculated at compile time?
set(A2CM_SERIAL_PORT COM18) # TODO: Can we look for it?
set(A2CM_SERIAL_PORT_LABEL ${CMKARD_SERIAL_PORT})
set(A2CM_SERIAL_PORT_PROTOCOL serial)
#]-]

# Not quite sufficient: Need to post-process the binary
# And, if -Dflash is called, flash the thing, right?
add_executable(
  Laptype
  dbgcfg.cpp
  kbreporter.cpp
  mainloop.cpp
  scanning.cpp
  localscan.cpp
  modulekeyboard.cpp
  laptype.cpp
)
target_include_directories(
  Laptype
  AFTER
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/teensy
  ${CMAKE_CURRENT_SOURCE_DIR}/include/laptype
  ${CMAKE_CURRENT_SOURCE_DIR}/include/localscan
)
target_link_libraries(
  Laptype
  PRIVATE
  teensy40_syslib
  busio_lib
  spi_lib
  gfx_lib
  st77xx_lib
  wire_lib
  eeprom_lib
)

# This makes .ino files compile as C++ files:
# set_source_files_properties(${MY_SOURCE_FILES} PROPERTIES LANGUAGE CXX)
# add_definitions("-x c++")
# It's annoying that youcan't configure ino files as C++ in the toolchain file
