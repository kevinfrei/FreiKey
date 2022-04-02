# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM8
	RUNTIME_HARDWARE_PATH=c:/PROGRA~2/Arduino/hardware/tools
	CMD_PATH=${RUNTIME_HARDWARE_PATH}
else ifeq ($(shell uname -s), Darwin)
	ARD=/Applications/Teensyduino.app/Contents/Java/hardware
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem1047*)
	TOOLS_PATH=${ARD}/tools
	RUNTIME_HARDWARE_PATH=${TOOLS_PATH}
	CMD_PATH=${TOOLS_PATH}
else
  $(error No Linux support yet)
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

# Libraries to use:
LIB_BUSIO=1
LIB_SPI=1
LIB_GFX=1
LIB_ST77XX=1
LIB_WIRE=1
# With NEW_CONFIG, this is where the configuration stuff lives
# No more changing the makefile :)
USER_INCLUDES=-Iinclude/laptype -Iinclude/localscan -Iinclude/teensy -Iinclude

USER_CPP_SRCS=\
	dbgcfg.cpp \
	kbreporter.cpp \
	mainloop.cpp \
	scanning.cpp \
	localscan.cpp \
	laptype.cpp \
	image.cpp \
	imgdec_rle.cpp \
	imgdec_pal.cpp \
	imgdec_prle.cpp \
	bitmaps/amy.cpp \
	bitmaps/batman.cpp \
	bitmaps/win.cpp \
	bitmaps/linux.cpp \
	bitmaps/mac.cpp \
	bitmaps/haha.cpp \
	bitmaps/hug.cpp \
	bitmaps/like.cpp \
	bitmaps/love.cpp \
	bitmaps/mad.cpp \
	bitmaps/sad.cpp \
	bitmaps/wow.cpp

VPATH:=bitmaps

ifeq ($(OS),Windows_NT)
include tools/teensy.win
else
include tools/teensy.mk
endif

