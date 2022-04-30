# Some simple details
ifeq ($(OS),Windows_NT)
	SUF=win
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM15
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
# grab the *last* serial port we see
	SERIAL_PORT=$(shell ls /dev/ttyACM* | tail -1)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
	BISON=/bin/bison
else 
  $(error No idea what platform you're running on...)
endif

# I'm going to run an Apple II emulator on this "soon" so just run it at 600MHz
# I could also pump it up to 720 or 816, but i don't want to slowly destroy the
# cpu either. We'll see how well it runs at 600MHz first.
IN_SPEED=600
IN_USB=serialhid
IN_OPT=osstd
IN_KEYS=en-us
EXTRA_TIME_LOCAL=0
BOARD_NAME=teensy40
SERIAL_PORT_LABEL=${SERIAL_PORT}
SERIAL_PORT_PROTOCOL=serial
PROJ_NAME=threepiece
BUILD_PATH=out/threepiece

# My custom flags
COMPILER_CPP_EXTRA_FLAGS=-DDEBUG=2
# This causes link errors now :'(
# -flto

# Libraries to use:
LIB_BUSIO=1
LIB_SPI=1
LIB_GFX=1
LIB_ST77XX=1
LIB_WIRE=1
LIB_EEPROM=1
LIB_SDFAT=1
LIB_T4_PXP=1
LIB_GFX_BUFFER=1

USER_INCLUDES=-Iinclude/threepiece -Iinclude/remotescan -Iinclude/teensy -Iinclude

USER_CPP_SRCS=\
	dbgcfg.cpp \
	kbreporter.cpp \
	mainloop.cpp \
	scanning.cpp \
	remotescan.cpp \
	modulekeyboard.cpp \
	threepiece.cpp

include modules/display/include.mk
include modules/calculator/include.mk
include modules/images/include.mk
include modules/editline/include.mk
include modules/tetris/include.mk
include modules/menu/include.mk
include apple2.mk

include tools/teensy.${SUF}

