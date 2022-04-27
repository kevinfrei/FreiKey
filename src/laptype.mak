# Some simple details
ifeq ($(OS),Windows_NT)
	SUF=win
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM8
	RUNTIME_HARDWARE_PATH=c:/PROGRA~2/Arduino/hardware/tools
	CMD_PATH=${RUNTIME_HARDWARE_PATH}
	BISON=win_bison
else ifeq ($(shell uname -s), Darwin)
	SUF=mac
	ARD=/Applications/Teensyduino.app/Contents/Java/hardware
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem5*)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
	BISON=/opt/homebrew/opt/bison/bin/bison
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
IN_SPEED=600
IN_USB=serialhid
IN_OPT=osstd
IN_KEYS=en-us
EXTRA_TIME_LOCAL=0
BOARD_NAME=teensy40
SERIAL_PORT_LABEL=${SERIAL_PORT}
SERIAL_PORT_PROTOCOL=serial
PROJ_NAME=laptype
BUILD_PATH=out/laptype

# My custom flags
COMPILER_CPP_EXTRA_FLAGS=-flto 
# -DDEBUG=1

# Libraries to use:
LIB_BUSIO=1
LIB_SPI=1
LIB_GFX=1
LIB_ST77XX=1
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
include modules/tetris/include.mk

include tools/teensy.${SUF}

