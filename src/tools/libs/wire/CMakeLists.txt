cmake_minimum_required(VERSION 3.12)

add_arduino_library(
  Wire
  ${A2CM_DEFAULT_LIB_PATH}/Wire
  ${A2CM_DEFAULT_LIB_PATH}/Wire/Wire.cpp 
  ${A2CM_DEFAULT_LIB_PATH}/Wire/WireIMXRT.cpp 
  ${A2CM_DEFAULT_LIB_PATH}/Wire/WireKinetis.cpp
)