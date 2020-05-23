# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=${HOME}/AppData/Local
	SERIAL_PORT=COM4
  TOOLS_PATH=${ARD}/Arduino15/packages/arduino/tools/arm-none-eabi-gcc/7-2017q4
else ifeq ($(shell uname -s), Darwin)
  ARD=${HOME}/Library
  SERIAL_PORT=/dev/cu.SLAB_USBtoUART
	TOOLS_PATH=/usr/local/opt/gcc-arm-none-eabi
else
  $(error No Linux support yet)
endif

# Necessary configuration stuff
BOARD_NAME=feather52832
IN_SOFTDEVICE=s132v6
IN_DEBUG=l0
BUILD_ARCH=nrf52
BUILD_PATH=out-rkarbon
PROJ_NAME=right-karbon
RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH=${TOOLS_PATH}

# This is how to add new flags
COMPILER_CPP_EXTRA_FLAGS=-DCLIENT -DRIGHT -DKARBON -DDEBUG=2 -DHAS_BATTERY

# This is how to add libraries (They currently have to be defined to 1)
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_LITTLEFS=1
LIB_INTERNALFILESYTEM=1

USER_INCLUDES=-Iinclude/karbon -Iinclude/adafruit_nrf52 -Iinclude
USER_CPP_SRCS=\
	dbgcfg.cpp \
 	client-comm.cpp \
	hardware.cpp \
  debounce.cpp \
  sleepstate.cpp \
  kbclient.cpp

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
