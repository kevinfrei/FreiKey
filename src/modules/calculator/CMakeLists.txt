cmake_minimum_required(VERSION 3.12)

if(CMAKE_HOST_APPLE)
  # On macOS, search Homebrew for keg-only versions of Bison (and Flex).
  # Xcode does not provide new enough versions for us to use.
  execute_process(
    COMMAND brew --prefix bison
    RESULT_VARIABLE BREW_BISON
    OUTPUT_VARIABLE BREW_BISON_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  if(BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
    message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
    set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
  endif()
endif()

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