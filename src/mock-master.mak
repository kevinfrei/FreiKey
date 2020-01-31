# This is for doing testing without hardware

# Here's all the #define's that my source code cares about
# hardware 'core' stuff:
# TEENSY, ADAFRUIT, ARDUINO_NRF52_ADAFRUIT
# hardware config stuff:
# UART_CLIENT, UART_ONLY, BETTERFLY, USB_MASTER
# hardware 'capabilities' stuff:
# HAS_BATTERY, HAS_LED
# software capabilities:
# DEBUG, LOTSA_BLINKING, STATUS_DUMP, TEST_MASTER

# Necessary configuration stuff
BUILD_PATH=out-mock-master
PROJ_NAME=mock-master

# This is how to add new flags
# -DDEBUG=1/2
COMPILER_CPP_EXTRA_FLAGS=-DUSB_MASTER -DADAFRUIT -DHAS_LED -DDEBUG=1

USER_INCLUDES=-Iinclude
USER_CPP_SRCS=\
 	comm.cpp \
	dbgcfg.cpp \
	dongle.cpp \
	hardware.cpp \
	kbreporter.cpp \
	scanner.cpp \
  sync.cpp \
	usb-master.cpp

include mock.mk
