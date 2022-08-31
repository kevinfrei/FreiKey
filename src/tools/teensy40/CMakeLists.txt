cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Must be before the project command:
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/Toolchain-Teensy40.cmake)

project(teensy4corelib)

set(CORE_SOURCE_FILES
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/AudioStream.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/CrashReport.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/DMAChannel.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/EventResponder.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial1.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial2.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial3.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial4.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial5.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial6.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial7.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/HardwareSerial8.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/IntervalTimer.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/IPAddress.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/main.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/new.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/Print.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent1.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent2.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent3.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent4.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent5.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent6.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent7.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEvent8.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEventUSB1.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/serialEventUSB2.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/Stream.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/Time.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/Tone.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/usb_audio.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/usb_flightsim.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/usb_inst.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/WMath.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/WString.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/yield.cpp
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/memcpy-armv7m.S
  C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4/memset.S)

add_library(teensy4corelib STATIC ${CORE_SOURCE_FILES})
target_include_directories(teensy4corelib PUBLIC C:/PROGRA~2/Arduino/hardware/teensy/avr/cores/teensy4)
