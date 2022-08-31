cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Select stuff before setting the toolchain file

# Stuff that's specific to Teensy:
set(CMKARD_IN_USB keyboard) # how is the Teensy USB stack configured?
set(CMKARD_IN_SPEED 600) # the frequency to clock the CPU at
set(CMKARD_IN_OPT osstd) # compilation flags
set(CMKARD_IN_KEYS en-us) # keyboard layout (for typing strings)
set(CMKARD_EXTRA_TIME_LOCAL 0) # TODO: Make this dynamically calculated for build time?
set(CMKARD_SERIAL_PORT COM18) # TODO: Can we look for it?
set(CMKARD_SERIAL_PORT_LABEL ${CMKARD_SERIAL_PORT})
set(CMKARD_SERIAL_PORT_PROTOCOL serial)

# Must be before the project command:
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/tools/Toolchain-Teensy40.cmake)

project(Laptype)

set(MY_SOURCE_FILES
  dbgcfg.cpp
  kbreporter.cpp
  mainloop.cpp
  scanning.cpp
  localscan.cpp
  modulekeyboard.cpp
  laptype.cpp
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools/teensy40)

# It's annoying that I can't configure this in the toolchain file
# This makes .ino files compile as C++ files
# set_source_files_properties(${MY_SOURCE_FILES} PROPERTIES LANGUAGE CXX)
# add_definitions("-x c++")
add_executable(Laptype ${MY_SOURCE_FILES})
target_include_directories(Laptype
  AFTER PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include/teensy
  ${CMAKE_CURRENT_SOURCE_DIR}/include/laptype
  ${CMAKE_CURRENT_SOURCE_DIR}/include/localscan
)
target_link_libraries(Laptype PRIVATE teensy4corelib)
