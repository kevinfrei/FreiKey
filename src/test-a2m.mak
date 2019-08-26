# Some simple details
ifeq ($(OS),Windows_NT)
	uname:=Windows
else
	uname:=$(shell uname -s)
endif
INPUT_BOARD=feather52840
INPUT_SOFTDEVICE=s140v6
INPUT_DEBUG=l0
BUILD_ARCH=nrf52
ifeq ($(uname), Windows)
ARD=${HOME}/AppData/Local/Arduino15/packages/arduino
SERIAL_PORT=COM9
else
ARD=${HOME}/Library/Arduino15/packages/arduino
SERIAL_PORT=$(shell ls /dev/cu.usbmodem14*)
endif
RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH=${ARD}/tools/arm-none-eabi-gcc/7-2017q4
PROGRAM_BURN_PATTERN=nyi
CMD=nyi
BUILD_PATH=master-out
BUILD_PROJECT_NAME=usb-master

# External dependency locations: These were just symlinks.
# Now they're git submodules. I do hate those things, but
# they appear to solve the problem I'm trying to solve relatively well
# Read up on them here:
# https://medium.com/@porteneuve/mastering-git-submodules-34c65e940407
AFROOT=./libs/Adafruit
SSD1306_ROOT=./libs/SSD1306
GFX_ROOT=./libs/GFX
TUSB_ROOT=./libs/TinyUSB
NEOPIX_ROOT=./libs/NeoPixel

COMPILER_CPP_EXTRA_FLAGS=-DUSB_MASTER -DDEBUG=2

INCLUDES=-Iinclude -I${AFROOT}/cores/nRF5 -I${AFROOT}/variants/feather_nrf52840_express
USER_CPP_SRCS=\
	dbgcfg.cpp \
 	comm.cpp \
	hardware.cpp \
	usb-master.cpp \
	scanner.cpp \
	dongle.cpp

include adafruit.mk

.PHONY: ${BUILD_PROJECT_NAME}
# flashl flashr flashm

all: "${BUILD_PATH}" ${BUILD_PROJECT_NAME}

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
	-@mkdir "$@"
