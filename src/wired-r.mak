# Some simple details
ifeq ($(OS),Windows_NT)
	ARD=/PROGRA~2/Arduino/hardware
	SERIAL_PORT=COM22
  TOOLS_PATH=${ARD}/tools/arm
	RUNTIME_TOOLS_CMSIS_5_7_0_PATH=${LOCALAPPDATA}/Arduino15/packages/adafruit/tools/CMSIS/5.7.0
else ifeq ($(shell uname -s), Darwin)
  ARD=${HOME}/Library
  SERIAL_PORT=/dev/cu.SLAB_USBtoUART
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
BUILD_PATH=out/module-r
PROJ_NAME=module-right
RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH=${TOOLS_PATH}

# This is how to add new flags
COMPILER_CPP_EXTRA_FLAGS=-DWIREDRIGHT

# This is how to add libraries (They currently have to be defined to 1)
LIB_BLUEFRUIT52LIB=1
LIB_ADAFRUIT_NRFCRYPTO=1
LIB_ADAFRUIT_TINYUSB_ARDUINO=1
LIB_ADAFRUIT_LITTLEFS=1
LIB_INTERNALFILESYTEM=1

USER_INCLUDES=-Iinclude/modules -Iinclude/adafruit_nrf52 -Iinclude
USER_CPP_SRCS=\
	dbgcfg.cpp \
  wired-r.cpp

ifeq ($(OS),Windows_NT)
include af_nrf52.win
else
include af_nrf52.mk
endif
