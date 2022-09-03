cmake_minimum_required(VERSION 3.12)

add_arduino_library(
  Adafruit_GFX_Library
  # VERSION
  # 1.11.3
  ${A2CM_GFX_LIB_PATH}/
  # SOURCES
  ${A2CM_GFX_LIB_PATH}/Adafruit_GFX.cpp
  ${A2CM_GFX_LIB_PATH}/Adafruit_GrayOLED.cpp
  ${A2CM_GFX_LIB_PATH}/Adafruit_SPITFT.cpp
  ${A2CM_GFX_LIB_PATH}/glcdfont.c
)
# Add dependency on Adafruit's BusIO library
# I think it's PUBLIC dependency, but object libraries, I'm not certain about...
target_link_libraries(Adafruit_GFX_Library_lib PUBLIC Adafruit_BusIO_lib)
