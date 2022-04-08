# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM15
	RUNTIME_HARDWARE_PATH=c:/PROGRA~2/Arduino/hardware/tools
	CMD_PATH=${RUNTIME_HARDWARE_PATH}
	BISON=win_bison
else ifeq ($(shell uname -s), Darwin)
	ARD=/Applications/Teensyduino.app/Contents/Java/hardware
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem5*)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
	BISON=/opt/homebrew/opt/bison/bin/bison
else
  $(error No Linux support yet, but copying the Darwin stuff should be nearly all of the work)
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
COMPILER_CPP_EXTRA_FLAGS=
# This causes link errors now :'(
# -flto

# Libraries to use:
LIB_BUSIO=1
LIB_SPI=1
LIB_GFX=1
LIB_ST77XX=1
LIB_WIRE=1

USER_INCLUDES=-Iinclude/threepiece -Iinclude/remotescan -Iinclude/teensy -Iinclude

BITMAPS=$(wildcard bitmaps/*.cpp)
IMG_DECODERS=$(wildcard imgdec_*.cpp)

USER_CPP_SRCS=\
	dbgcfg.cpp \
	kbreporter.cpp \
	mainloop.cpp \
	scanning.cpp \
	remotescan.cpp \
	threepiece.cpp \
	image.cpp \
	${IMG_DECODERS} \
	${BITMAPS}

VPATH+=bitmaps

include modules/calculator/include.mk

ifeq ($(OS),Windows_NT)
include tools/teensy.win
else
include tools/teensy.mk
endif

