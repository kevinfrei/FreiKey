# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM9
else ifeq ($(shell uname -s), Darwin)
	ARD=/Applications/Arduino.app/Contents/Java/hardware
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem5*)
	TOOLS_PATH=/usr/local/opt/gcc-arm-none-eabi
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
else
  $(error No Linux support yet)
endif

# Teensy weirdess...
# Speeds below 24 mhz are apparently too slow for USB...
# 120(OC), 96(OC), 72, 48, and 24 are acceptable
IN_SPEED=24
IN_USB=serialhid
IN_OPT=osstd
IN_KEYS=en-us
EXTRA_TIME_LOCAL=0
BOARD_NAME=teensy31
SERIAL_PORT_LABEL=${SERIAL_PORT}
SERIAL_PORT_PROTOCOL=serial
PROJ_NAME=betterfly
BUILD_PATH=out-betterfly

# My custom flags
COMPILER_CPP_EXTRA_FLAGS=-DDEBUG=2 -DBETTERFLY -DTEENSY

# Libraries to use:
LIB_WIRE=1
LIB_SPI=1
LIB_GFX=1
LIB_SSD1306=1
USER_INCLUDES=-Iinclude/betterfly -Iinclude/teensy -Iinclude

USER_CPP_SRCS=\
	betterfly.cpp \
	dbgcfg.cpp \
	debounce.cpp \
	globals.cpp \
	hardware.cpp \
	kbreporter.cpp \
	scanner.cpp

include teensy.mk
