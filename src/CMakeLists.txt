cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TEENSY4_LIB_ROOT_DIR "C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4")
set(A2CM_DEFAULT_LIB_PATH "C:/PROGRA~2/Arduino/hardware/teensy/avr/libraries")
set(A2CM_ST77XX_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/ST77xx")
set(A2CM_BusIO_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/BusIO")
set(A2CM_GFX_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/GFX")

include(tools/teensy/a2cm_teensy40.cmake)

project(Laptype)

# Must be *before* the project command:
# Configure the 'menu' stuff
#[[
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
]]

# Or, maybe a macro: I kinda like this idea, mostly because it
# involves fewer files, and I can validate it pretty trivially.
# The Subdirectory mechanism is "cleanest" but this is all machine generated
# so do I really care?
teensy40_menu_selections(keyboard 600 o2std en-us)

# Add the board library - this uses those 4 libraries
add_subdirectory(tools/teensy/teensy40)

# Add any additional arduino libraries for the target
# I think some of these dependencies actually belong in the modules
add_subdirectory(tools/libs/busio)
add_subdirectory(tools/libs/wire)
add_subdirectory(tools/libs/eeprom)
add_subdirectory(tools/libs/spi)
add_subdirectory(tools/libs/gfx)
add_subdirectory(tools/libs/st77xx)

# Add my own local libraries, too
# These ought to just be object libraries, not even archives
#add_subdirectory(modules/display)
#add_subdirectory(modules/calculator)
#add_subdirectory(modules/images)
#add_subdirectory(modules/editline)
#add_subdirectory(modules/tetris)
#add_subdirectory(modules/menu)

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
  module_display
  module_calculator
  module_images
  module_editline
  module_tetris
  module_menu
)

# This makes .ino files compile as C++ files:
# set_source_files_properties(${MY_SOURCE_FILES} PROPERTIES LANGUAGE CXX)
# add_definitions("-x c++")
# It's annoying that youcan't configure ino files as C++ in the toolchain file