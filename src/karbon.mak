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
	RUNTIME_TOOLS_CMSIS_5_7_0_PATH=${ARD}/Arduino15/packages/adafruit/tools/CMSIS/5.7.0
else
  $(error No Linux support yet)
endif
COMPILER_LIBRARIES_LDFLAGS=-Wl,--cref

# Necessary configuration stuff
BOARD_NAME=feather52840
IN_SOFTDEVICE=s140v6
# l0/l1/l2/l3 for system debug info
# anything else for no system debug logging
IN_DEBUG=none
IN_DEBUG_OUTPUT=serial
BUILD_ARCH=nrf52
RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH=${TOOLS_PATH}
BUILD_PATH=out/karbon
PROJ_NAME=karbon

# This is how to add new flags
COMPILER_CPP_EXTRA_FLAGS=-DKARBON -DBTLE_HOST -DMACRO_PAD -DHAS_DISPLAY -DDEBUG=2

# This is how to add libraries
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_LITTLEFS=1
LIB_NEOPIXEL=1
# Ah, InternalFileSytem, you're my favorite typo
LIB_INTERNALFILESYTEM=1
LIB_TINYUSB=1
LIB_GFX=1
LIB_BUSIO=1
LIB_SSD1306=1
LIB_WIRE=1
LIB_SPI=1
LIB_NRFCRYPTO=1

USER_INCLUDES=-Iinclude/karbon -Iinclude
USER_CPP_SRCS=\
	dbgcfg.cpp \
	dongle.cpp \
	drawing.cpp \
	hardware.cpp \
	kbreporter.cpp \
 	host-comm.cpp \
	scanner.cpp \
  sync.cpp \
	usb-host.cpp

include af_nrf52.mk

