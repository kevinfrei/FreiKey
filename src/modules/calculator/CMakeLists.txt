cmake_minimum_required(VERSION 3.12)

find_package(BISON) 
BISON_TARGET(
  CalcParser
  CalcGrammar.yy
  ${CMAKE_CURRENT_BINARY_DIR}/CalcParser.cpp
  DEFINES_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/CalcParser.h
)
add_custom_module(
  calculator
  include
  calculator.cpp
  CalcLexer.cpp
  Calculator.cpp
  CalcExpr.cpp
  CalcContext.cpp
  CalcHandler.cpp
  ${BISON_CalcParser_OUTPUTS}
)
target_include_directories(
  module_calculator
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  headers
)
target_link_libraries(module_calculator PUBLIC Adafruit_ST77XX_lib module_display module_editline)