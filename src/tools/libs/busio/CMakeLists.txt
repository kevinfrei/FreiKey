cmake_minimum_required(VERSION 3.12)

add_arduino_library(
  Adafruit_BusIO
  ${A2CM_BusIO_LIB_PATH}
  ${A2CM_BusIO_LIB_PATH}/Adafruit_BusIO_Register.cpp
  ${A2CM_BusIO_LIB_PATH}/Adafruit_I2CDevice.cpp
  ${A2CM_BusIO_LIB_PATH}/Adafruit_SPIDevice.cpp
)
target_link_libraries(Adafruit_BusIO_lib PUBLIC Wire_lib SPI_lib)