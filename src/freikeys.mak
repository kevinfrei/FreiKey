# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM9
	# This should be windows/mac/linux specific, I imagine
	TOOLS_PATH=${ARD}/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4
else ifeq ($(shell uname -s), Darwin)
	ARD=${HOME}/Library
	SERIAL_PORT=$(shell ls /dev/cu.usbmodem14*)
	TOOLS_PATH=/usr/local/opt/gcc-arm-none-eabi
else
  $(error No Linux support yet)
endif

# Necessary configuration stuff
BOARD_NAME=feather52840
IN_SOFTDEVICE=s140v6
IN_DEBUG=l0
BUILD_ARCH=nrf52
RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH=${TOOLS_PATH}
BUILD_PATH=out-freikeys
PROJ_NAME=freikeys

# This is how to add new flags
# -DDEBUG=1/2
COMPILER_CPP_EXTRA_FLAGS=-DFREIKEYS -DMASTER -DDEBUG=2

# This is how to add libraries
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_LITTLEFS=1
LIB_NEOPIXEL=1
LIB_INTERNALFILESYTEM=1
LIB_TINYUSB=1
# (Ah, InternalFileSytem, you're my favorite typo)

USER_INCLUDES=-Iinclude/freikeys -Iinclude
USER_CPP_SRCS=\
	dbgcfg.cpp \
	dongle.cpp \
	hardware.cpp \
	kbreporter.cpp \
 	master-comm.cpp \
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
