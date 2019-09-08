# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM9
else ifeq ($(shell uname -s), Darwin)
		ARD=${HOME}/Library
		SERIAL_PORT=$(shell ls /dev/cu.usbmodem14*)
else
  $(error No Linux support yet)
endif

# Necessary configuration stuff
BOARD_NAME=feather52840
SOFTDEVICE=s140v6
DBG_LEVEL=l0
CPU_ARCH=nrf52
TOOLS_PATH=${ARD}/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4
BUILD_DIR=out-master
PROJ_NAME=usb-master

# This is how to add new flags
# -DDEBUG=1/2
COMPILER_CPP_EXTRA_FLAGS=-DUSB_MASTER

# This is how to add libraries
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_LITTLEFS=1
LIB_NEOPIXEL=1
LIB_INTERNALFILESYTEM=1
LIB_TINYUSB=1
# (Ah, InternalFileSytem, you're my favorite typo)

USER_INCLUDES=-Iinclude
USER_CPP_SRCS=\
 	comm.cpp \
	dbgcfg.cpp \
	dongle.cpp \
	hardware.cpp \
	scanner.cpp \
  sync.cpp \
	usb-master.cpp

include af_nrf52.mk

#DEPS = $(M_CORE_OBJS:.o=.d) $(C_CORE_OBJS:.o=.d) $(NFFS_OBJS:.o=.d) \
#	$(BFLIB_OBJS:.o=.d) $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d) $(WIRE_OBJS:.o=.d)

#-include ${DEPS}

# External dependency locations: These were just symlinks.
# Now they're git submodules. I do hate those things, but
# they appear to solve a problem I'm trying to solve relatively well
# Read up on them here:
# https://medium.com/@porteneuve/mastering-git-submodules-34c65e940407
# ADAFRUIT_ROOT=./libs/Adafruit
# SSD1306_ROOT=./libs/SSD1306
# GFX_ROOT=./libs/GFX
# TUSB_ROOT=./libs/TinyUSB
# NEOPIX_ROOT=./libs/NeoPixel
