# Some simple details
ifeq ($(OS),Windows_NT)
	SUF=win
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM4
	RUNTIME_HARDWARE_PATH=c:/PROGRA~2/Arduino/hardware/tools
	CMD_PATH=${RUNTIME_HARDWARE_PATH}
else ifeq ($(shell uname -s), Darwin)
	SUF=mac
	ARD=/Applications/Teensyduino.app/Contents/Java/hardware
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem*401)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
else
  $(error No Linux support yet, but copying the Darwin stuff should be nearly all of the work)
endif

IN_SPEED=600
IN_USB=serialhid
IN_OPT=osstd
IN_KEYS=en-us
EXTRA_TIME_LOCAL=0
BOARD_NAME=teensy41
SERIAL_PORT_LABEL=${SERIAL_PORT}
SERIAL_PORT_PROTOCOL=serial
PROJ_NAME=sd
BUILD_PATH=out/sd

# My custom flags
COMPILER_CPP_EXTRA_FLAGS=
# This causes link errors now :'(
# -flto

# Libraries to use:
LIB_BUSIO=1
LIB_SPI=1
LIB_GFX=1
LIB_8875=1
LIB_WIRE=1
LIB_SD=1
LIB_SDFAT=1

USER_INCLUDES=-Iinclude

USER_CPP_SRCS=\
	test_41.cpp

include tools/teensy.${SUF}
