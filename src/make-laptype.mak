# Some simple details
THIS_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
ifeq ($(OS),Windows_NT)
	SUF=win
	ARD=${USERPROFILE}/AppData/Local/Arduino15
	SERIAL_PORT=COM8
# RUNTIME_HARDWARE_PATH=c:/PROGRA~2/Arduino/hardware/tools
	RUNTIME_TOOLS_TEENSY_TOOLS_PATH=${ARD}/packages/teensy/tools/teensy-tools/1.57.2
# RUNTIME_TOOLS_TEENSY_COMPILE_PATH=${THIS_DIR}../local_tools/arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi
	RUNTIME_TOOLS_TEENSY_COMPILE_PATH=${ARD}/packages/teensy/tools/teensy-compile/5.4.1
	CMD_PATH=${RUNTIME_HARDWARE_PATH}
	BISON=bison
else ifeq ($(shell uname -s), Darwin)
	SUF=mac
	ARD=/Applications/Teensyduino.app/Contents/Java/hardware
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem*501)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
	ifeq ($(shell uname -p), i386)
		BISON=/usr/local/opt/bison/bin/bison
	else
		BISON=/opt/homebrew/opt/bison/bin/bison
	endif
else ifeq ($(shell uname -s), Linux)
	SUF=lin
	ARD=${HOME}/Apps/arduino-1.8.19/hardware
# grab the *first* serial port we see
	SERIAL_PORT=$(shell ls /dev/ttyACM* | head -1)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
	BISON=/bin/bison
else 
  $(error No idea what platform you're running on...)
endif

# At only 24MHz, the screen is dramatically slower, but at 150MHz
# things are buttery smooth, so not running at 600MHz helps overheating, right?
IN_SPEED=150
# For debug:
# IN_USB=serialhid
# For optimized:
IN_USB=keyboard
IN_OPT=osstd
IN_KEYS=en-us
EXTRA_TIME_LOCAL=0
BOARD_NAME=teensy40
SERIAL_PORT_LABEL=${SERIAL_PORT}
SERIAL_PORT_PROTOCOL=serial
PROJ_NAME=laptype
BUILD_PATH=out/laptype

# My custom flags
COMPILER_CPP_EXTRA_FLAGS=-gsplit-dwarf
# COMPILER_CPP_EXTRA_FLAGS=-flto -gsplit-dwarf
# COMPILER_ELF_EXTRA_FLAGS=-Wl,--gdb-index
# -DDEBUG=1

# Libraries to use (Updated for Arduino2Make v0.6)
LIB_ADAFRUIT_BUSIO=1
LIB_SPI=1
LIB_ADAFRUIT_GFX_LIBRARY=1
LIB_ADAFRUIT_ST7735_AND_ST7789_LIBRARY=1
LIB_WIRE=1
LIB_EEPROM=1

USER_INCLUDES=-Iinclude/laptype -Iinclude/localscan -Iinclude/teensy -Iinclude

USER_CPP_SRCS=\
	dbgcfg.cpp \
	kbreporter.cpp \
	mainloop.cpp \
	scanning.cpp \
	localscan.cpp \
	modulekeyboard.cpp \
	laptype.cpp 

include modules/display/include.mk
include modules/calculator/include.mk
include modules/images/include.mk
include modules/editline/include.mk
include modules/tetris/maketetris.mk
include modules/menu/include.mk

include tools/teensy.${SUF}

