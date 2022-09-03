cmake_minimum_required(VERSION 3.12)

add_arduino_library(
  Adafruit_ST77XX
  ${A2CM_ST77XX_LIB_PATH}/
  ${A2CM_ST77XX_LIB_PATH}/Adafruit_ST7735.cpp
  ${A2CM_ST77XX_LIB_PATH}/Adafruit_ST7789.cpp
  ${A2CM_ST77XX_LIB_PATH}/Adafruit_ST77xx.cpp
)
target_link_libraries(Adafruit_ST77XX_lib PUBLIC Adafruit_GFX_Library_lib)