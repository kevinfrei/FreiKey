# Some simple details
ifeq ($(OS),Windows_NT)
	uname:=Windows
	ARD=${HOME}/AppData/Local/Arduino15/packages/arduino
	SERIAL_PORT=COM4
else
	uname:=$(shell uname -s)
	ifeq ($(uname), Darwin)
		ARD=${HOME}/Library/Arduino15/packages/arduino
		SERIAL_PORT=/dev/cu.SLAB_USBtoUART
	else
		$(error No Linux support yet)
	endif
endif
INPUT_BOARD=feather52832
INPUT_SOFTDEVICE=s132v6
INPUT_DEBUG=l0
BUILD_ARCH=nrf52
RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH=${ARD}/tools/arm-none-eabi-gcc/7-2017q4
BUILD_PATH=client-out
BUILD_PROJECT_NAME=left-client

# These should go away once I have flashing working
PROGRAM_BURN_PATTERN=nyi
CMD=nyi

# This is how to add new flags
COMPILER_CPP_EXTRA_FLAGS=-DUART_CLIENT -DDEBUG=2

# This is how to add libraries (They currently have to be defined to 1)
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_LITTLEFS=1
# This is my favoritist typo. It always takes me too long to figure out :/
LIB_INTERNALFILESYTEM=1

USER_INCLUDES=-Iinclude
USER_CPP_SRCS=\
	dbgcfg.cpp \
 	comm.cpp \
	hardware.cpp \
  debounce.cpp \
  sleepstate.cpp \
  kbclient.cpp \
  boardio.cpp \
  l-client.cpp

.PHONY: ${BUILD_PROJECT_NAME}

all: "${BUILD_PATH}" ${BUILD_PROJECT_NAME}

include af_nrf52.mk

#DEPS = $(M_CORE_OBJS:.o=.d) $(C_CORE_OBJS:.o=.d) $(NFFS_OBJS:.o=.d) \
#	$(BFLIB_OBJS:.o=.d) $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d) $(WIRE_OBJS:.o=.d)

#-include ${DEPS}

#flashr: ${C_OUT}/r-client.zip
#	${NRFUTIL} --verbose dfu serial -pkg $< -p ${RPORT} -b 115200 --singlebank

#flashm: ${M_OUT}/usb-master.zip
#	${NRFUTIL} --verbose dfu serial -pkg $< -p ${MPORT} -b 115200 --singlebank --touch 1200

${BUILD_PROJECT_NAME}: ${BUILD_PATH}/${BUILD_PROJECT_NAME}.zip

# Make us rebuild just my own source if I change the makefile
# $(USER_OBJS) : Makefile

"${BUILD_PATH}":
	test -d "$@" || mkdir "$@"

# External dependency locations: These were just symlinks.
# Now they're git submodules. I do hate those things, but
# they appear to solve the problem I'm trying to solve relatively well
# Read up on them here:
# https://medium.com/@porteneuve/mastering-git-submodules-34c65e940407
# ADAFRUIT_ROOT=./libs/Adafruit
# SSD1306_ROOT=./libs/SSD1306
# GFX_ROOT=./libs/GFX
# TUSB_ROOT=./libs/TinyUSB
# NEOPIX_ROOT=./libs/NeoPixel
