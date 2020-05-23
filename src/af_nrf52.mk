# First, add some errors for undefined values
ifndef PROJ_NAME
  $(error PROJ_NAME is not defined!)
endif
ifndef BOARD_NAME
  $(error BOARD_NAME is not defined!)
endif
ifndef IN_SOFTDEVICE
  $(error IN_SOFTDEVICE is not defined!)
endif
ifndef IN_DEBUG
  $(error IN_DEBUG is not defined!)
endif
ifndef RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH
  $(error RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH is not defined!)
endif
ifndef BUILD_PATH
  $(error BUILD_PATH is not defined!)
endif
ifndef SERIAL_PORT
  $(error SERIAL_PORT is not defined!)
endif
ifndef BUILD_ARCH
  $(error BUILD_ARCH is not defined!)
endif

# Check for some source files
ifeq (${USER_C_SRCS}${USER_CPP_SRCS}${USER_S_SRCS},)
  $(error You must define USER_C_SRCS, USER_CPP_SRCS, or USER_S_SRCS)
endif

# And here are all the definitions
ifeq ($(OS), Windows_NT)
  RUNTIME_OS=windows
else
  uname=$(shell uname -s)
  ifeq ($(uname), Darwin)
    RUNTIME_OS=macosx
  endif
endif
RUNTIME_OS?=linux
RUNTIME_PLATFORM_PATH=/Users/freik/src/FreiKey/src/libs/Adafruit
RUNTIME_IDE_VERSION=10808
IDE_VERSION=10808
BUILD_PROJECT_NAME=${PROJ_NAME}
ifeq (${BOARD_NAME}, feather52832)
  BUILD_LDSCRIPT=nrf52832_s132_v6.ld
  BUILD_EXTRA_FLAGS=-DNRF52832_XXAA -DNRF52
  BUILD_VARIANT=feather_nrf52832
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52832_FEATHER
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=52224
  UPLOAD_MAXIMUM_SIZE=290816
  UPLOAD_NATIVE_USB=false
  UPLOAD_WAIT_FOR_UPLOAD_PORT=false
  UPLOAD_USE_1200BPS_TOUCH=false
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  NAME=Adafruit Feather nRF52832
  ifeq (${IN_SOFTDEVICE}, s132v6)
    BUILD_SD_FWID=0x00B7
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s132
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, feather52840)
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x802A
  PID_2=0x002A
  PID_1=0x0029
  PID_0=0x8029
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Adafruit Feather nRF52840 Express
  BUILD_PID=0x8029
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_VARIANT=feather_nrf52840_express
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_FEATHER
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  BUILD_USB_PRODUCT="Feather nRF52840 Express"
  BUILD_USB_MANUFACTURER="Adafruit LLC"
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, feather52840sense)
  BUILD_PID=0x8087
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="Feather nRF52840 Sense"
  BUILD_USB_MANUFACTURER="Adafruit LLC"
  BUILD_VARIANT=feather_nrf52840_sense
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_FEATHER_SENSE
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x8088
  PID_2=0x0088
  PID_1=0x0087
  PID_0=0x8087
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Adafruit Feather Bluefruit Sense
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, itsybitsy52840)
  BUILD_PID=0x8051
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="ItsyBitsy nRF52840 Express"
  BUILD_USB_MANUFACTURER="Adafruit LLC"
  BUILD_VARIANT=itsybitsy_nrf52840_express
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_ITSYBITSY
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x8052
  PID_2=0x0052
  PID_1=0x0051
  PID_0=0x8051
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Adafruit ItsyBitsy nRF52840 Express
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, cplaynrf52840)
  BUILD_PID=0x8045
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="Circuit Playground Bluefruit"
  BUILD_USB_MANUFACTURER="Adafruit LLC"
  BUILD_VARIANT=circuitplayground_nrf52840
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_CIRCUITPLAY
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x8046
  PID_2=0x0046
  PID_1=0x0045
  PID_0=0x8045
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Adafruit Circuit Playground Bluefruit
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, cluenrf52840)
  BUILD_PID=0x8071
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="CLUE"
  BUILD_USB_MANUFACTURER="Adafruit LLC"
  BUILD_VARIANT=clue_nrf52840
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_CLUE
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x8071
  PID_2=0x0071
  PID_1=0x0072
  PID_0=0x8072
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Adafruit CLUE
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, metro52840)
  BUILD_PID=0x803F
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="Metro nRF52840 Express"
  BUILD_USB_MANUFACTURER="Adafruit LLC"
  BUILD_VARIANT=metro_nrf52840_express
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_METRO
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x8040
  PID_2=0x0040
  PID_1=0x003F
  PID_0=0x803F
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Adafruit Bluefruit Metro nRF52840 Express
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, pca10056)
  BUILD_PID=0x8029
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="nRF52840 DK"
  BUILD_USB_MANUFACTURER="Nordic"
  BUILD_VARIANT=pca10056
  BUILD_CORE=nRF5
  BUILD_BOARD=NRF52840_PCA10056
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  NAME=Nordic nRF52840DK (PCA10056)
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, particle_xenon)
  BUILD_PID=0x8029
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="Particle Xenon"
  BUILD_USB_MANUFACTURER="Particle Industries"
  BUILD_VARIANT=particle_xenon
  BUILD_CORE=nRF5
  BUILD_BOARD=PARTICLE_XENON
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x802A
  PID_2=0x002A
  PID_1=0x0029
  PID_0=0x8029
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Particle Xenon
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
else ifeq (${BOARD_NAME}, mdbt50qrx)
  BUILD_PID=0x8029
  BUILD_VID=0x239A
  BUILD_LDSCRIPT=nrf52840_s140_v6.ld
  BUILD_USB_PRODUCT="Raytac MDBT50Q - RX"
  BUILD_USB_MANUFACTURER="Raytac Corporation"
  BUILD_VARIANT=raytac_mdbt50q_rx
  BUILD_CORE=nRF5
  BUILD_BOARD=MDBT50Q_RX
  BUILD_F_CPU=64000000
  BUILD_MCU=cortex-m4
  UPLOAD_MAXIMUM_DATA_SIZE=237568
  UPLOAD_MAXIMUM_SIZE=815104
  UPLOAD_WAIT_FOR_UPLOAD_PORT=true
  UPLOAD_USE_1200BPS_TOUCH=true
  UPLOAD_PROTOCOL=nrfutil
  UPLOAD_TOOL=nrfutil
  BOOTLOADER_TOOL=bootburn
  PID_3=0x802A
  PID_2=0x002A
  PID_1=0x0029
  PID_0=0x8029
  VID_3=0x239A
  VID_2=0x239A
  VID_1=0x239A
  VID_0=0x239A
  NAME=Raytac MDBT50Q-RX Dongle
  ifeq (${IN_SOFTDEVICE}, s140v6)
    BUILD_SD_FWID=0x00B6
    BUILD_SD_VERSION=6.1.1
    BUILD_SD_NAME=s140
  endif
  ifeq (${IN_DEBUG}, l0)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
  else ifeq (${IN_DEBUG}, l1)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=1
  else ifeq (${IN_DEBUG}, l2)
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=2
  else ifeq (${IN_DEBUG}, l3)
    BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=1
    BUILD_DEBUG_FLAGS=-DCFG_DEBUG=3
  endif
endif
BUILD_CORE_PATH=${RUNTIME_PLATFORM_PATH}/cores/${BUILD_CORE}
NORDIC_PATH=${BUILD_CORE_PATH}/nordic
RTOS_PATH=${BUILD_CORE_PATH}/freertos
BUILD_FLAGS_USB= -DUSBCON -DUSE_TINYUSB -DUSB_VID=${BUILD_VID} -DUSB_PID=${BUILD_PID} '-DUSB_MANUFACTURER=${BUILD_USB_MANUFACTURER}' '-DUSB_PRODUCT=${BUILD_USB_PRODUCT}'
ifeq (${BOARD_NAME}, feather52840)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, feather52840sense)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, itsybitsy52840)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA -DARDUINO_NRF52_ITSYBITSY ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, cplaynrf52840)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, cluenrf52840)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, metro52840)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, pca10056)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, particle_xenon)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
else ifeq (${BOARD_NAME}, mdbt50qrx)
  BUILD_EXTRA_FLAGS=-DNRF52840_XXAA ${BUILD_FLAGS_USB}
endif
BUILD_SYSVIEW_FLAGS=-DCFG_SYSVIEW=0
BUILD_LOGGER_FLAGS=-DCFG_LOGGER=1
BUILD_FLAGS_NRF= -DSOFTDEVICE_PRESENT -DARDUINO_NRF52_ADAFRUIT -DNRF52_SERIES -DLFS_NAME_MAX=64 -Ofast ${BUILD_DEBUG_FLAGS} ${BUILD_LOGGER_FLAGS} ${BUILD_SYSVIEW_FLAGS} "-I${BUILD_CORE_PATH}/cmsis/include" "-I${NORDIC_PATH}" "-I${NORDIC_PATH}/nrfx" "-I${NORDIC_PATH}/nrfx/hal" "-I${NORDIC_PATH}/nrfx/mdk" "-I${NORDIC_PATH}/nrfx/soc" "-I${NORDIC_PATH}/nrfx/drivers/include" "-I${NORDIC_PATH}/nrfx/drivers/src" "-I${NORDIC_PATH}/softdevice/${BUILD_SD_NAME}_nrf52_${BUILD_SD_VERSION}_API/include" "-I${RTOS_PATH}/Source/include" "-I${RTOS_PATH}/config" "-I${RTOS_PATH}/portable/GCC/nrf52" "-I${RTOS_PATH}/portable/CMSIS/nrf52" "-I${BUILD_CORE_PATH}/sysview/SEGGER" "-I${BUILD_CORE_PATH}/sysview/Config" "-I${BUILD_CORE_PATH}/TinyUSB" "-I${BUILD_CORE_PATH}/TinyUSB/Adafruit_TinyUSB_ArduinoCore" "-I${BUILD_CORE_PATH}/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src"
BUILD_DEBUG_FLAGS=-DCFG_DEBUG=0
BUILD_FLOAT_FLAGS=-mfloat-abi=hard -mfpu=fpv4-sp-d16 -u _printf_float
COMPILER_SIZE_CMD=arm-none-eabi-size
COMPILER_LDFLAGS=-mcpu=${BUILD_MCU} -mthumb ${BUILD_FLOAT_FLAGS} -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align --specs=nano.specs --specs=nosys.specs
COMPILER_ELF2HEX_CMD=arm-none-eabi-objcopy
COMPILER_ELF2HEX_FLAGS=-O ihex
COMPILER_ELF2BIN_CMD=arm-none-eabi-objcopy
COMPILER_ELF2BIN_FLAGS=-O binary
COMPILER_OBJCOPY_EEP_FLAGS=-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0
COMPILER_OBJCOPY_CMD=arm-none-eabi-objcopy
COMPILER_AR_FLAGS=rcs
COMPILER_AR_CMD=arm-none-eabi-ar
COMPILER_CPP_CMD=arm-none-eabi-g++
COMPILER_S_FLAGS=-c -g -x assembler-with-cpp
COMPILER_S_CMD=arm-none-eabi-gcc
COMPILER_C_ELF_FLAGS=-Ofast -Wl,--gc-sections -save-temps
COMPILER_C_ELF_CMD=arm-none-eabi-gcc
COMPILER_C_CMD=arm-none-eabi-gcc
COMPILER_PATH=${RUNTIME_TOOLS_ARM_NONE_EABI_GCC_PATH}/bin/
COMPILER_WARNING_FLAGS=-w
COMPILER_CPP_FLAGS=-mcpu=${BUILD_MCU} -mthumb -c -g ${COMPILER_WARNING_FLAGS} ${BUILD_FLOAT_FLAGS} -std=gnu++11 -ffunction-sections -fdata-sections -fno-threadsafe-statics -nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD
COMPILER_C_FLAGS=-mcpu=${BUILD_MCU} -mthumb -c -g ${COMPILER_WARNING_FLAGS} ${BUILD_FLOAT_FLAGS} -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD
COMPILER_WARNING_FLAGS_ALL=-Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-pointer-arith
COMPILER_WARNING_FLAGS_MORE=-Wall
COMPILER_WARNING_FLAGS_NONE=-w
VERSION=0.20.1
NAME=Adafruit nRF52 Boards
ifeq (${RUNTIME_OS}, macosx)
  TOOLS_NRFUTIL_CMD=${RUNTIME_PLATFORM_PATH}/tools/adafruit-nrfutil/macos/adafruit-nrfutil
else ifeq (${RUNTIME_OS}, windows)
  TOOLS_NRFUTIL_CMD=${RUNTIME_PLATFORM_PATH}/tools/adafruit-nrfutil/win32/adafruit-nrfutil.exe
endif
TOOLS_NRFUTIL_CMD?=adafruit-nrfutil
ifeq (${UPLOAD_USE_1200BPS_TOUCH}, true)
  UPLOAD_EXTRA_FLAGS=--touch 1200
endif
ifeq (${UPLOAD_TOOL}, nrfutil)
  UPLOAD_PATTERN="${TOOLS_NRFUTIL_CMD}" ${UPLOAD_VERBOSE} dfu serial -pkg "$(abspath ${BUILD_PATH})/${BUILD_PROJECT_NAME}.zip" -p ${SERIAL_PORT} -b 115200 --singlebank
endif
ifeq (${BUILD_CORE}, nRF5)
  C_SYS_SRCS+=libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/cdc/cdc_device.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/hid/hid_device.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/midi/midi_device.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/msc/msc_device.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/usbtmc/usbtmc_device.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/vendor/vendor_device.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/common/tusb_fifo.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/device/usbd.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/device/usbd_control.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/espressif/esp32s2/dcd_esp32s2.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/microchip/samd/dcd_samd.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/microchip/samg/dcd_samg.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nordic/nrf5x/dcd_nrf5x.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nuvoton/nuc120/dcd_nuc120.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nuvoton/nuc121/dcd_nuc121.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc17_40/dcd_lpc17_40.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc17_40/hcd_lpc17_40.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc18_43/hcd_lpc18_43.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc_ip3511/dcd_lpc_ip3511.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/transdimension/dcd_transdimension.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/sony/cxd56/dcd_cxd56.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/st/synopsys/dcd_synopsys.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/ti/msp430x5xx/dcd_msp430x5xx.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/valentyusb/eptri/dcd_eptri.c \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/tusb.c \
    libs/Adafruit/cores/nRF5/WInterrupts.c \
    libs/Adafruit/cores/nRF5/avr/dtostrf.c \
    libs/Adafruit/cores/nRF5/delay.c \
    libs/Adafruit/cores/nRF5/freertos/Source/croutine.c \
    libs/Adafruit/cores/nRF5/freertos/Source/event_groups.c \
    libs/Adafruit/cores/nRF5/freertos/Source/list.c \
    libs/Adafruit/cores/nRF5/freertos/Source/portable/MemMang/heap_3.c \
    libs/Adafruit/cores/nRF5/freertos/Source/queue.c \
    libs/Adafruit/cores/nRF5/freertos/Source/stream_buffer.c \
    libs/Adafruit/cores/nRF5/freertos/Source/tasks.c \
    libs/Adafruit/cores/nRF5/freertos/Source/timers.c \
    libs/Adafruit/cores/nRF5/freertos/portable/CMSIS/nrf52/port_cmsis.c \
    libs/Adafruit/cores/nRF5/freertos/portable/CMSIS/nrf52/port_cmsis_systick.c \
    libs/Adafruit/cores/nRF5/freertos/portable/GCC/nrf52/port.c \
    libs/Adafruit/cores/nRF5/hooks.c \
    libs/Adafruit/cores/nRF5/itoa.c \
    libs/Adafruit/cores/nRF5/nordic/nrfx/drivers/src/nrfx_power.c \
    libs/Adafruit/cores/nRF5/nordic/nrfx/drivers/src/nrfx_qspi.c \
    libs/Adafruit/cores/nRF5/nordic/nrfx/drivers/src/nrfx_spim.c \
    libs/Adafruit/cores/nRF5/nordic/nrfx/mdk/system_nrf52.c \
    libs/Adafruit/cores/nRF5/nordic/nrfx/mdk/system_nrf52840.c \
    libs/Adafruit/cores/nRF5/pulse.c \
    libs/Adafruit/cores/nRF5/sysview/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c \
    libs/Adafruit/cores/nRF5/sysview/SEGGER/SEGGER_RTT.c \
    libs/Adafruit/cores/nRF5/sysview/SEGGER/SEGGER_RTT_printf.c \
    libs/Adafruit/cores/nRF5/sysview/SEGGER/SEGGER_SYSVIEW.c \
    libs/Adafruit/cores/nRF5/sysview/SEGGER_SYSVIEW_FreeRTOS.c \
    libs/Adafruit/cores/nRF5/utility/AdaCallback.c \
    libs/Adafruit/cores/nRF5/utility/utilities.c \
    libs/Adafruit/cores/nRF5/wiring.c \
    libs/Adafruit/cores/nRF5/wiring_analog_nRF52.c \
    libs/Adafruit/cores/nRF5/wiring_digital.c \
    libs/Adafruit/cores/nRF5/wiring_private.c \
    libs/Adafruit/cores/nRF5/wiring_shift.c
  CPP_SYS_SRCS+=libs/Adafruit/cores/nRF5/HardwarePWM.cpp \
    libs/Adafruit/cores/nRF5/IPAddress.cpp \
    libs/Adafruit/cores/nRF5/Print.cpp \
    libs/Adafruit/cores/nRF5/RingBuffer.cpp \
    libs/Adafruit/cores/nRF5/Stream.cpp \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/Adafruit_USBD_CDC.cpp \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/Adafruit_USBD_Device.cpp \
    libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_nRF.cpp \
    libs/Adafruit/cores/nRF5/Tone.cpp \
    libs/Adafruit/cores/nRF5/Uart.cpp \
    libs/Adafruit/cores/nRF5/WMath.cpp \
    libs/Adafruit/cores/nRF5/WString.cpp \
    libs/Adafruit/cores/nRF5/abi.cpp \
    libs/Adafruit/cores/nRF5/main.cpp \
    libs/Adafruit/cores/nRF5/new.cpp \
    libs/Adafruit/cores/nRF5/rtos.cpp \
    libs/Adafruit/cores/nRF5/utility/SoftwareTimer.cpp \
    libs/Adafruit/cores/nRF5/utility/adafruit_fifo.cpp \
    libs/Adafruit/cores/nRF5/utility/debug.cpp \
    libs/Adafruit/cores/nRF5/wiring_analog.cpp
  S_SYS_SRCS+=libs/Adafruit/cores/nRF5/linker/gcc_startup_nrf52.S \
    libs/Adafruit/cores/nRF5/linker/gcc_startup_nrf52840.S \
    libs/Adafruit/cores/nRF5/pulse_asm.S \
    libs/Adafruit/cores/nRF5/sysview/SEGGER/SEGGER_RTT_ASM_ARMv7M.S
  SYS_INCLUDES+= -Ilibs/Adafruit/cores/nRF5
  VPATH_CORE+=libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/cdc:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/hid:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/midi:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/msc:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/usbtmc:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/class/vendor:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/common:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/device:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/espressif/esp32s2:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/microchip/samd:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/microchip/samg:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nordic/nrf5x:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nuvoton/nuc120:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nuvoton/nuc121:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nuvoton/nuc505:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc17_40:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc18_43:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/lpc_ip3511:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/nxp/transdimension:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/sony/cxd56:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/st/stm32_fsdev:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/st/synopsys:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/ti/msp430x5xx:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src/portable/valentyusb/eptri:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore/tinyusb/src:libs/Adafruit/cores/nRF5:libs/Adafruit/cores/nRF5/avr:libs/Adafruit/cores/nRF5/freertos/Source:libs/Adafruit/cores/nRF5/freertos/Source/portable/MemMang:libs/Adafruit/cores/nRF5/freertos/portable/CMSIS/nrf52:libs/Adafruit/cores/nRF5/freertos/portable/GCC/nrf52:libs/Adafruit/cores/nRF5/nordic/nrfx/drivers/src:libs/Adafruit/cores/nRF5/nordic/nrfx/mdk:libs/Adafruit/cores/nRF5/sysview/Config:libs/Adafruit/cores/nRF5/sysview/SEGGER:libs/Adafruit/cores/nRF5/sysview:libs/Adafruit/cores/nRF5/utility:libs/Adafruit/cores/nRF5/TinyUSB/Adafruit_TinyUSB_ArduinoCore:libs/Adafruit/cores/nRF5/TinyUSB:libs/Adafruit/cores/nRF5/linker
endif
ifeq (${BUILD_VARIANT}, feather_nrf52832)
  CPP_SYS_SRCS+=libs/Adafruit/variants/feather_nrf52832/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/feather_nrf52832
  VPATH_CORE+=libs/Adafruit/variants/feather_nrf52832
else ifeq (${BUILD_VARIANT}, feather_nrf52840_express)
  CPP_SYS_SRCS+=libs/Adafruit/variants/feather_nrf52840_express/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/feather_nrf52840_express
  VPATH_CORE+=libs/Adafruit/variants/feather_nrf52840_express
else ifeq (${BUILD_VARIANT}, feather_nrf52840_sense)
  CPP_SYS_SRCS+=libs/Adafruit/variants/feather_nrf52840_sense/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/feather_nrf52840_sense
  VPATH_CORE+=libs/Adafruit/variants/feather_nrf52840_sense
else ifeq (${BUILD_VARIANT}, itsybitsy_nrf52840_express)
  CPP_SYS_SRCS+=libs/Adafruit/variants/itsybitsy_nrf52840_express/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/itsybitsy_nrf52840_express
  VPATH_CORE+=libs/Adafruit/variants/itsybitsy_nrf52840_express
else ifeq (${BUILD_VARIANT}, circuitplayground_nrf52840)
  CPP_SYS_SRCS+=libs/Adafruit/variants/circuitplayground_nrf52840/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/circuitplayground_nrf52840
  VPATH_CORE+=libs/Adafruit/variants/circuitplayground_nrf52840
else ifeq (${BUILD_VARIANT}, clue_nrf52840)
  CPP_SYS_SRCS+=libs/Adafruit/variants/clue_nrf52840/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/clue_nrf52840
  VPATH_CORE+=libs/Adafruit/variants/clue_nrf52840
else ifeq (${BUILD_VARIANT}, metro_nrf52840_express)
  CPP_SYS_SRCS+=libs/Adafruit/variants/metro_nrf52840_express/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/metro_nrf52840_express
  VPATH_CORE+=libs/Adafruit/variants/metro_nrf52840_express
else ifeq (${BUILD_VARIANT}, pca10056)
  CPP_SYS_SRCS+=libs/Adafruit/variants/pca10056/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/pca10056
  VPATH_CORE+=libs/Adafruit/variants/pca10056
else ifeq (${BUILD_VARIANT}, particle_xenon)
  CPP_SYS_SRCS+=libs/Adafruit/variants/particle_xenon/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/particle_xenon
  VPATH_CORE+=libs/Adafruit/variants/particle_xenon
else ifeq (${BUILD_VARIANT}, raytac_mdbt50q_rx)
  CPP_SYS_SRCS+=libs/Adafruit/variants/raytac_mdbt50q_rx/variant.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/variants/raytac_mdbt50q_rx
  VPATH_CORE+=libs/Adafruit/variants/raytac_mdbt50q_rx
endif
ifdef LIB_ADAFRUIT_LITTLEFS
  C_SYS_SRCS+=libs/Adafruit/libraries/Adafruit_LittleFS/src/littlefs/lfs.c \
    libs/Adafruit/libraries/Adafruit_LittleFS/src/littlefs/lfs_util.c
  CPP_SYS_SRCS+=libs/Adafruit/libraries/Adafruit_LittleFS/src/Adafruit_LittleFS.cpp \
    libs/Adafruit/libraries/Adafruit_LittleFS/src/Adafruit_LittleFS_File.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/Adafruit_LittleFS/src \
    -Ilibs/Adafruit/libraries/Adafruit_LittleFS/src/littlefs
  VPATH_MORE+=libs/Adafruit/libraries/Adafruit_LittleFS/src/littlefs:libs/Adafruit/libraries/Adafruit_LittleFS/src
endif
ifdef LIB_BLEADAFRUITSERVICE
  CPP_SYS_SRCS+=libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitAccel.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitAddressablePixel.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitBaro.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitButton.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitColor.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitGesture.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitGyro.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitHumid.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitLightSensor.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitMagnetic.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitProximity.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitQuaternion.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitSensor.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitSound.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitTemperature.cpp \
    libs/Adafruit/libraries/BLEAdafruitService/src/services/BLEAdafruitTone.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/BLEAdafruitService/src \
    -Ilibs/Adafruit/libraries/BLEAdafruitService/src/services
  VPATH_MORE+=libs/Adafruit/libraries/BLEAdafruitService/src/services
endif
ifdef LIB_BLEHOMEKIT
  C_SYS_SRCS+=libs/Adafruit/libraries/BLEHomekit/src/crypto/crypto.c \
    libs/Adafruit/libraries/BLEHomekit/src/crypto/random.c \
    libs/Adafruit/libraries/BLEHomekit/src/crypto/srp/bignum.c \
    libs/Adafruit/libraries/BLEHomekit/src/crypto/srp/memory_buffer_alloc.c \
    libs/Adafruit/libraries/BLEHomekit/src/crypto/srp/platform.c \
    libs/Adafruit/libraries/BLEHomekit/src/crypto/srp/srp.c \
    libs/Adafruit/libraries/BLEHomekit/src/crypto/tweetnacl-modified/tweetnacl.c
  CPP_SYS_SRCS+=libs/Adafruit/libraries/BLEHomekit/src/BLEHomekit.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/HAPCharacteristic.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/HAPProcedure.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/HAPService.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/service/HAPAccessoryInfo.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/service/HAPLightBulb.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/service/HAPPairing.cpp \
    libs/Adafruit/libraries/BLEHomekit/src/service/HAPProtocol.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/BLEHomekit/src \
    -Ilibs/Adafruit/libraries/BLEHomekit/src/crypto \
    -Ilibs/Adafruit/libraries/BLEHomekit/src/crypto/srp \
    -Ilibs/Adafruit/libraries/BLEHomekit/src/crypto/tweetnacl-modified \
    -Ilibs/Adafruit/libraries/BLEHomekit/src/service
  VPATH_MORE+=libs/Adafruit/libraries/BLEHomekit/src/crypto:libs/Adafruit/libraries/BLEHomekit/src/crypto/srp:libs/Adafruit/libraries/BLEHomekit/src/crypto/tweetnacl-modified:libs/Adafruit/libraries/BLEHomekit/src:libs/Adafruit/libraries/BLEHomekit/src/service
endif
ifdef LIB_BLUEFRUIT52LIB
  C_SYS_SRCS+=libs/Adafruit/libraries/Bluefruit52Lib/src/utility/bootloader_util.c
  CPP_SYS_SRCS+=libs/Adafruit/libraries/Bluefruit52Lib/src/BLEAdvertising.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLECentral.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLECharacteristic.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEClientCharacteristic.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEClientService.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEConnection.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEDiscovery.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEGatt.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEPeriph.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEScanner.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEService.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/BLEUuid.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/bluefruit.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/clients/BLEAncs.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/clients/BLEClientBas.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/clients/BLEClientCts.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/clients/BLEClientDis.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/clients/BLEClientHidAdafruit.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/clients/BLEClientUart.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEBas.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEBeacon.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEDfu.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEDis.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEHidAdafruit.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEHidGeneric.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEMidi.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/BLEUart.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/services/EddyStone.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/utility/AdaMsg.cpp \
    libs/Adafruit/libraries/Bluefruit52Lib/src/utility/bonding.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/Bluefruit52Lib/src \
    -Ilibs/Adafruit/libraries/Bluefruit52Lib/src/clients \
    -Ilibs/Adafruit/libraries/Bluefruit52Lib/src/services \
    -Ilibs/Adafruit/libraries/Bluefruit52Lib/src/utility
  VPATH_MORE+=libs/Adafruit/libraries/Bluefruit52Lib/src/utility:libs/Adafruit/libraries/Bluefruit52Lib/src:libs/Adafruit/libraries/Bluefruit52Lib/src/clients:libs/Adafruit/libraries/Bluefruit52Lib/src/services
endif
ifdef LIB_INTERNALFILESYTEM
  C_SYS_SRCS+=libs/Adafruit/libraries/InternalFileSytem/src/flash/flash_cache.c \
    libs/Adafruit/libraries/InternalFileSytem/src/flash/flash_nrf5x.c
  CPP_SYS_SRCS+=libs/Adafruit/libraries/InternalFileSytem/src/InternalFileSystem.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/InternalFileSytem/src \
    -Ilibs/Adafruit/libraries/InternalFileSytem/src/flash
  VPATH_MORE+=libs/Adafruit/libraries/InternalFileSytem/src/flash:libs/Adafruit/libraries/InternalFileSytem/src
endif
ifdef LIB_PDM
  CPP_SYS_SRCS+=libs/Adafruit/libraries/PDM/src/PDM.cpp \
    libs/Adafruit/libraries/PDM/src/utility/PDMDoubleBuffer.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/PDM/src \
    -Ilibs/Adafruit/libraries/PDM/src/utility
  VPATH_MORE+=libs/Adafruit/libraries/PDM/src:libs/Adafruit/libraries/PDM/src/utility
endif
ifdef LIB_ROTARYENCODER
  CPP_SYS_SRCS+=libs/Adafruit/libraries/RotaryEncoder/RotaryEncoder.cpp \
    libs/Adafruit/libraries/RotaryEncoder/SwRotaryEncoder.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/RotaryEncoder
  VPATH_MORE+=libs/Adafruit/libraries/RotaryEncoder
endif
ifdef LIB_SPI
  CPP_SYS_SRCS+=libs/Adafruit/libraries/SPI/SPI.cpp \
    libs/Adafruit/libraries/SPI/SPI_nrf52832.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/SPI
  VPATH_MORE+=libs/Adafruit/libraries/SPI
endif
ifdef LIB_SERVO
  CPP_SYS_SRCS+=libs/Adafruit/libraries/Servo/src/nrf52/Servo.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/Servo/src \
    -Ilibs/Adafruit/libraries/Servo/src/nrf52
  VPATH_MORE+=libs/Adafruit/libraries/Servo/src/nrf52
endif
ifdef LIB_SOFTWARESERIAL
  CPP_SYS_SRCS+=libs/Adafruit/libraries/SoftwareSerial/SoftwareSerial.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/SoftwareSerial
  VPATH_MORE+=libs/Adafruit/libraries/SoftwareSerial
endif
ifdef LIB_WIRE
  CPP_SYS_SRCS+=libs/Adafruit/libraries/Wire/Wire_nRF52.cpp
  SYS_INCLUDES+=-Ilibs/Adafruit/libraries/Wire
  VPATH_MORE+=libs/Adafruit/libraries/Wire
endif
ifdef LIB_GFX
  C_SYS_SRCS+=libs/GFX/fontconvert/fontconvert.c \
    libs/GFX/glcdfont.c
  CPP_SYS_SRCS+=libs/GFX/Adafruit_GFX.cpp \
    libs/GFX/Adafruit_MonoOLED.cpp \
    libs/GFX/Adafruit_SPITFT.cpp
  SYS_INCLUDES+=-Ilibs/GFX \
    -Ilibs/GFX/Fonts
  VPATH_MORE+=libs/GFX/fontconvert:libs/GFX
endif
ifdef LIB_NEOPIXEL
  C_SYS_SRCS+=libs/NeoPixel/esp8266.c
  CPP_SYS_SRCS+=libs/NeoPixel/Adafruit_NeoPixel.cpp
  SYS_INCLUDES+=-Ilibs/NeoPixel
  VPATH_MORE+=libs/NeoPixel
endif
ifdef LIB_SSD1306
  CPP_SYS_SRCS+=libs/SSD1306/Adafruit_SSD1306.cpp
  SYS_INCLUDES+=-Ilibs/SSD1306
  VPATH_MORE+=libs/SSD1306
endif
ifdef LIB_TINYUSB
  CPP_SYS_SRCS+=libs/TinyUSB/src/Adafruit_TinyUSB.cpp \
    libs/TinyUSB/src/Adafruit_USBD_HID.cpp \
    libs/TinyUSB/src/Adafruit_USBD_MIDI.cpp \
    libs/TinyUSB/src/Adafruit_USBD_MSC.cpp \
    libs/TinyUSB/src/Adafruit_USBD_WebUSB.cpp
  SYS_INCLUDES+=-Ilibs/TinyUSB/src
  VPATH_MORE+=libs/TinyUSB/src
endif
SYS_SRC=${C_SYS_SRCS} ${CPP_SYS_SRCS} ${S_SYS_SRCS}
USER_SRC=${USER_C_SRCS} ${USER_CPP_SRCS} ${USER_S_SRCS}
ALL_SRC=${SYS_SRC} ${USER_SRC}
VPATH:=${VPATH}:${VPATH_MORE}:${VPATH_CORE}:${VPATH_VAR}
SYS_OBJS=\
  $(addprefix ${BUILD_PATH}/, \
    $(patsubst %.c, %.c.o, \
      $(patsubst %.cpp, %.cpp.o, \
        $(patsubst %.S, %.S.o, $(notdir ${SYS_SRC})))))
USER_OBJS=\
  $(addprefix ${BUILD_PATH}/, \
    $(patsubst %.c, %.c.o, \
      $(patsubst %.cpp, %.cpp.o, \
        $(patsubst %.S, %.S.o, $(notdir ${USER_SRC})))))
ALL_OBJS=${USER_OBJS} ${SYS_OBJS}

# And now the build rules!

# First, the phony rules that don't product things
.PHONY: ${PROJ_NAME} flash clean allclean

# Now the default target
all: ${BUILD_PATH} ${PROJ_NAME}

# Some house keeping
clean:
	-rm ${USER_OBJS}

allclean:
	-rm -rf ${BUILD_PATH}

# Make us rebuild user code if the makefile(s) change:
# Needs to be above the deps thing, I think
${USER_OBJS} : $(MAKEFILE_LIST)

# Let's start using the generated .d files...
-include $(ALL_OBJS:.o=.d)

# Next, the project name shortcut, because it's easier
${PROJ_NAME}: ${BUILD_PATH}/${PROJ_NAME}.zip

# Add a 'flash' target
flash: ${BUILD_PATH}/${PROJ_NAME}.flash

# And finally, create the director
# TODO: This no worky on Windows fer sure
${BUILD_PATH}:
	test -d "$@" || mkdir "$@"

# Now, on to the actual rules

${BUILD_PATH}/%.S.o : %.S
	"${COMPILER_PATH}${COMPILER_S_CMD}" ${COMPILER_S_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} ${COMPILER_S_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} "$<" -o "$@"

${BUILD_PATH}/s_compile_commands.json: $(USER_S_SRCS) $(S_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${COMPILER_S_CMD}\\\" ${COMPILER_S_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} ${COMPILER_S_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/%.c.o : %.c
	"${COMPILER_PATH}${COMPILER_C_CMD}" ${COMPILER_C_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} '-DARDUINO_BSP_VERSION="${VERSION}"' ${COMPILER_C_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} "$<" -o "$@"

${BUILD_PATH}/c_compile_commands.json: $(USER_C_SRCS) $(C_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${COMPILER_C_CMD}\\\" ${COMPILER_C_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} -DARDUINO_BSP_VERSION=\\\"${VERSION}\\\" ${COMPILER_C_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/%.cpp.o : %.cpp
	"${COMPILER_PATH}${COMPILER_CPP_CMD}" ${COMPILER_CPP_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} '-DARDUINO_BSP_VERSION="${VERSION}"' ${COMPILER_CPP_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} "$<" -o "$@"

${BUILD_PATH}/cpp_compile_commands.json: $(USER_CPP_SRCS) $(CPP_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${COMPILER_CPP_CMD}\\\" ${COMPILER_CPP_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} -DARDUINO_BSP_VERSION=\\\"${VERSION}\\\" ${COMPILER_CPP_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/system.a : ${SYS_OBJS}
	"${COMPILER_PATH}${COMPILER_AR_CMD}" ${COMPILER_AR_FLAGS} ${COMPILER_AR_EXTRA_FLAGS} "$@" $^

${BUILD_PATH}/${BUILD_PROJECT_NAME}.elf : ${BUILD_PATH}/system.a ${USER_OBJS}
	"${COMPILER_PATH}${COMPILER_C_ELF_CMD}"  "-L${BUILD_PATH}" ${COMPILER_C_ELF_FLAGS} ${COMPILER_C_ELF_EXTRA_FLAGS} "-L${BUILD_CORE_PATH}/linker" "-T${BUILD_LDSCRIPT}" "-Wl,-Map,${BUILD_PATH}/${BUILD_PROJECT_NAME}.map" ${COMPILER_LDFLAGS} -o "$@" ${USER_OBJS} -Wl,--start-group -lm "${BUILD_PATH}/system.a" -Wl,--end-group

${BUILD_PATH}/${BUILD_PROJECT_NAME}.hex : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.elf
	"${COMPILER_PATH}${COMPILER_ELF2HEX_CMD}" ${COMPILER_ELF2HEX_FLAGS} ${COMPILER_ELF2HEX_EXTRA_FLAGS} "$<" "$@"

${BUILD_PATH}/${BUILD_PROJECT_NAME}.zip : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.hex
	"${TOOLS_NRFUTIL_CMD}" dfu genpkg --dev-type 0x0052 --sd-req ${BUILD_SD_FWID} --application "$<" "$@"

${BUILD_PATH}/${BUILD_PROJECT_NAME}.flash : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.zip
	${UPLOAD_PATTERN} ${UPLOAD_EXTRA_FLAGS}

${BUILD_PATH}/compile_commands.json: ${BUILD_PATH}/s_compile_commands.json ${BUILD_PATH}/c_compile_commands.json ${BUILD_PATH}/cpp_compile_commands.json
	echo "[" > $@.tmp
	cat $^ >> $@.tmp
	echo "]" >> $@.tmp
	sed -e ':a' -e 'N' -e '$$!ba' -e 's/},\n]/}]/g' $@.tmp > $@

compile_commands: ${BUILD_PATH}/compile_commands.json
