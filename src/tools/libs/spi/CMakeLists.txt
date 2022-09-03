cmake_minimum_required(VERSION 3.12)

add_arduino_library(
  SPI
  ${A2CM_DEFAULT_LIB_PATH}/SPI
  ${A2CM_DEFAULT_LIB_PATH}/SPI/SPI.cpp
)