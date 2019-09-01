# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM4
else ifeq ($(shell uname -s), Darwin)
  ARD=${HOME}/Library
  SERIAL_PORT=/dev/cu.SLAB_USBtoUART
else
  $(error No Linux support yet)
endif

# Necessary configuration stuff
BOARD_NAME=feather52832
SOFTDEVICE=s132v6
DBG_LEVEL=l0
CPU_ARCH=nrf52
TOOLS_PATH=${ARD}/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4
BUILD_DIR=client-out
PROJ_NAME=right-client

# This is how to add new flags
COMPILER_CPP_EXTRA_FLAGS=-DUART_CLIENT -DDEBUG=2

# This is how to add libraries (They currently have to be defined to 1)
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_LITTLEFS=1
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
  r-client.cpp

include af_nrf52.mk

#DEPS = $(M_CORE_OBJS:.o=.d) $(C_CORE_OBJS:.o=.d) $(NFFS_OBJS:.o=.d) \
#	$(BFLIB_OBJS:.o=.d) $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d) $(WIRE_OBJS:.o=.d)

#-include ${DEPS}

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