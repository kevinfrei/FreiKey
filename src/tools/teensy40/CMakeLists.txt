cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must be before the project command:
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/Toolchain-Teensy40-bare.cmake)

project(teensy4corelib)

if(CMAKE_HOST_WIN32)
set(TEENSY4_LIB_ROOT_DIR "c:/program files (x86)/Arduino/hardware/teensy/avr/cores/teensy4")
elseif(CMAKE_HOST_APPLE)
elseif(CMAKE_HOST_UNIX)
else()
  message(FATAL_ERROR "Unknown host machine")
endif()

add_library(teensy4corelib
  STATIC
  ${TEENSY4_LIB_ROOT_DIR}/AudioStream.cpp
  ${TEENSY4_LIB_ROOT_DIR}/CrashReport.cpp
  ${TEENSY4_LIB_ROOT_DIR}/DMAChannel.cpp
  ${TEENSY4_LIB_ROOT_DIR}/EventResponder.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial1.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial2.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial3.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial4.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial5.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial6.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial7.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial8.cpp
  ${TEENSY4_LIB_ROOT_DIR}/IntervalTimer.cpp
  ${TEENSY4_LIB_ROOT_DIR}/IPAddress.cpp
  ${TEENSY4_LIB_ROOT_DIR}/main.cpp
  ${TEENSY4_LIB_ROOT_DIR}/new.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Print.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent1.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent2.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent3.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent4.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent5.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent6.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent7.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent8.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEventUSB1.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEventUSB2.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Stream.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Time.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Tone.cpp
  ${TEENSY4_LIB_ROOT_DIR}/usb_audio.cpp
  ${TEENSY4_LIB_ROOT_DIR}/usb_flightsim.cpp
  ${TEENSY4_LIB_ROOT_DIR}/usb_inst.cpp
  ${TEENSY4_LIB_ROOT_DIR}/WMath.cpp
  ${TEENSY4_LIB_ROOT_DIR}/WString.cpp
  ${TEENSY4_LIB_ROOT_DIR}/yield.cpp
  ${TEENSY4_LIB_ROOT_DIR}/memcpy-armv7m.S
  ${TEENSY4_LIB_ROOT_DIR}/memset.S)

target_include_directories(teensy4corelib PUBLIC ${TEENSY4_LIB_ROOT_DIR})
