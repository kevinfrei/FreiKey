# First, add some errors for undefined values
ifndef PROJ_NAME
  $(error PROJ_NAME is not defined!)
endif
ifndef BOARD_NAME
  $(error BOARD_NAME is not defined!)
endif
ifndef IN_USB
  $(error IN_USB is not defined!)
endif
ifndef IN_SPEED
  $(error IN_SPEED is not defined!)
endif
ifndef IN_OPT
  $(error IN_OPT is not defined!)
endif
ifndef IN_KEYS
  $(error IN_KEYS is not defined!)
endif
ifndef EXTRA_TIME_LOCAL
  $(error EXTRA_TIME_LOCAL is not defined!)
endif
ifndef RUNTIME_HARDWARE_PATH
  $(error RUNTIME_HARDWARE_PATH is not defined!)
endif
ifndef CMD_PATH
  $(error CMD_PATH is not defined!)
endif
ifndef BUILD_PATH
  $(error BUILD_PATH is not defined!)
endif
ifndef SERIAL_PORT
  $(error SERIAL_PORT is not defined!)
endif
ifndef SERIAL_PORT_LABEL
  $(error SERIAL_PORT_LABEL is not defined!)
endif
ifndef SERIAL_PORT_PROTOCOL
  $(error SERIAL_PORT_PROTOCOL is not defined!)
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
RUNTIME_PLATFORM_PATH=/Users/freik/src/Teensyduino-149-b4/hardware/teensy/avr
RUNTIME_IDE_VERSION=10808
IDE_VERSION=10808
BUILD_PROJECT_NAME=${PROJ_NAME}
ifeq (${BOARD_NAME}, teensy40)
  SERIAL_RESTART_CMD=false
  BUILD_FLAGS_LIBS=-larm_cortexM7lfsp_math -lm -lstdc++
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-std=gnu++14 -fno-exceptions -fpermissive -fno-rtti -fno-threadsafe-statics -felide-constructors -Wno-error=narrowing
  BUILD_FLAGS_DEFS=-D__IMXRT1062__ -DTEENSYDUINO=149
  BUILD_FLAGS_CPU=-mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections -nostdlib
  BUILD_COMMAND_SIZE=arm-none-eabi-size
  BUILD_COMMAND_LINKER=arm-none-eabi-gcc
  BUILD_COMMAND_OBJDUMP=arm-none-eabi-objdump
  BUILD_COMMAND_OBJCOPY=arm-none-eabi-objcopy
  BUILD_COMMAND_AR=arm-none-eabi-gcc-ar
  BUILD_COMMAND_G__=arm-none-eabi-g++
  BUILD_COMMAND_GCC=arm-none-eabi-gcc
  BUILD_TOOLCHAIN=arm/bin/
  BUILD_WARN_DATA_PERCENTAGE=99
  BUILD_MCU=imxrt1062
  BUILD_CORE=teensy4
  BUILD_BOARD=TEENSY40
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=524288
  UPLOAD_MAXIMUM_SIZE=2031616
  NAME=Teensy 4.0
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, keyboard)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_KEYBOARDONLY
  else ifeq (${IN_USB}, touch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_TOUCHSCREEN
  else ifeq (${IN_USB}, hidtouch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID_TOUCHSCREEN
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, midi4)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI4
  else ifeq (${IN_USB}, midi16)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI16
  else ifeq (${IN_USB}, serialmidi)
    BUILD_USBTYPE=USB_MIDI_SERIAL
  else ifeq (${IN_USB}, serialmidi4)
    BUILD_USBTYPE=USB_MIDI4_SERIAL
  else ifeq (${IN_USB}, serialmidi16)
    BUILD_USBTYPE=USB_MIDI16_SERIAL
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  endif
  ifeq (${IN_SPEED}, 600)
    BUILD_FCPU=600000000
  else ifeq (${IN_SPEED}, 528)
    BUILD_FCPU=528000000
  else ifeq (${IN_SPEED}, 450)
    BUILD_FCPU=450000000
  else ifeq (${IN_SPEED}, 396)
    BUILD_FCPU=396000000
  else ifeq (${IN_SPEED}, 150)
    BUILD_FCPU=150000000
  else ifeq (${IN_SPEED}, 24)
    BUILD_FCPU=24000000
  else ifeq (${IN_SPEED}, 720)
    BUILD_FCPU=720000000
  else ifeq (${IN_SPEED}, 816)
    BUILD_FCPU=816000000
  else ifeq (${IN_SPEED}, 912)
    BUILD_FCPU=912000000
  else ifeq (${IN_SPEED}, 960)
    BUILD_FCPU=960000000
  else ifeq (${IN_SPEED}, 1008)
    BUILD_FCPU=1000000000
  endif
  ifeq (${IN_OPT}, o2std)
    BUILD_FLAGS_OPTIMIZE=-O2
  else ifeq (${IN_OPT}, o1std)
    BUILD_FLAGS_OPTIMIZE=-O1
  else ifeq (${IN_OPT}, o3std)
    BUILD_FLAGS_OPTIMIZE=-O3
  else ifeq (${IN_OPT}, ogstd)
    BUILD_FLAGS_OPTIMIZE=-Og
  else ifeq (${IN_OPT}, osstd)
    BUILD_FLAGS_OPTIMIZE=-Os --specs=nano.specs
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensy36)
  SERIAL_RESTART_CMD=false
  BUILD_FLAGS_LIBS=-larm_cortexM4lf_math -lm
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++14 -Wno-error=narrowing -fno-rtti
  BUILD_FLAGS_DEFS=-D__MK66FX1M0__ -DTEENSYDUINO=149
  BUILD_FLAGS_CPU=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections -nostdlib
  BUILD_COMMAND_SIZE=arm-none-eabi-size
  BUILD_COMMAND_LINKER=arm-none-eabi-gcc
  BUILD_COMMAND_OBJDUMP=arm-none-eabi-objdump
  BUILD_COMMAND_OBJCOPY=arm-none-eabi-objcopy
  BUILD_COMMAND_AR=arm-none-eabi-gcc-ar
  BUILD_COMMAND_G__=arm-none-eabi-g++
  BUILD_COMMAND_GCC=arm-none-eabi-gcc
  BUILD_TOOLCHAIN=arm/bin/
  BUILD_WARN_DATA_PERCENTAGE=99
  BUILD_MCU=mk66fx1m0
  BUILD_CORE=teensy3
  BUILD_BOARD=TEENSY36
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=262144
  UPLOAD_MAXIMUM_SIZE=1048576
  NAME=Teensy 3.6
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, keyboard)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_KEYBOARDONLY
  else ifeq (${IN_USB}, touch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_TOUCHSCREEN
  else ifeq (${IN_USB}, hidtouch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID_TOUCHSCREEN
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, midi4)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI4
  else ifeq (${IN_USB}, midi16)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI16
  else ifeq (${IN_USB}, serialmidi)
    BUILD_USBTYPE=USB_MIDI_SERIAL
  else ifeq (${IN_USB}, serialmidi4)
    BUILD_USBTYPE=USB_MIDI4_SERIAL
  else ifeq (${IN_USB}, serialmidi16)
    BUILD_USBTYPE=USB_MIDI16_SERIAL
  else ifeq (${IN_USB}, audio)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_AUDIO
  else ifeq (${IN_USB}, serialmidiaudio)
    BUILD_USBTYPE=USB_MIDI_AUDIO_SERIAL
  else ifeq (${IN_USB}, serialmidi16audio)
    BUILD_USBTYPE=USB_MIDI16_AUDIO_SERIAL
  else ifeq (${IN_USB}, mtp)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MTPDISK
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  else ifeq (${IN_USB}, flightsimjoystick)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM_JOYSTICK
  else ifeq (${IN_USB}, everything)
    BUILD_USBTYPE=USB_EVERYTHING
  else ifeq (${IN_USB}, disable)
    BUILD_USBTYPE=USB_DISABLED
  endif
  ifeq (${IN_SPEED}, 180)
    BUILD_FCPU=180000000
  else ifeq (${IN_SPEED}, 168)
    BUILD_FCPU=168000000
  else ifeq (${IN_SPEED}, 144)
    BUILD_FCPU=144000000
  else ifeq (${IN_SPEED}, 120)
    BUILD_FCPU=120000000
  else ifeq (${IN_SPEED}, 96)
    BUILD_FCPU=96000000
  else ifeq (${IN_SPEED}, 72)
    BUILD_FCPU=72000000
  else ifeq (${IN_SPEED}, 48)
    BUILD_FCPU=48000000
  else ifeq (${IN_SPEED}, 24)
    BUILD_FCPU=24000000
  else ifeq (${IN_SPEED}, 16)
    BUILD_FCPU=16000000
  else ifeq (${IN_SPEED}, 8)
    BUILD_FCPU=8000000
  else ifeq (${IN_SPEED}, 4)
    BUILD_FCPU=4000000
  else ifeq (${IN_SPEED}, 2)
    BUILD_FCPU=2000000
  else ifeq (${IN_SPEED}, 192)
    BUILD_FCPU=192000000
  else ifeq (${IN_SPEED}, 216)
    BUILD_FCPU=216000000
  else ifeq (${IN_SPEED}, 240)
    BUILD_FCPU=240000000
  else ifeq (${IN_SPEED}, 256)
    BUILD_FCPU=256000000
  endif
  ifeq (${IN_OPT}, o2std)
    BUILD_FLAGS_OPTIMIZE=-O2
  else ifeq (${IN_OPT}, o2lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O2 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o1std)
    BUILD_FLAGS_OPTIMIZE=-O1
  else ifeq (${IN_OPT}, o1lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O1 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3std)
    BUILD_FLAGS_OPTIMIZE=-O3
  else ifeq (${IN_OPT}, o3purestd)
    BUILD_FLAGS_OPTIMIZE=-O3 -mpure-code -D__PURE_CODE__
  else ifeq (${IN_OPT}, o3lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3purelto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -mpure-code -D__PURE_CODE__ -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, ogstd)
    BUILD_FLAGS_OPTIMIZE=-Og
  else ifeq (${IN_OPT}, oglto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Og -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, osstd)
    BUILD_FLAGS_OPTIMIZE=-Os --specs=nano.specs
  else ifeq (${IN_OPT}, oslto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Os -flto -fno-fat-lto-objects --specs=nano.specs
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensy35)
  SERIAL_RESTART_CMD=false
  BUILD_FLAGS_LIBS=-larm_cortexM4lf_math -lm
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++14 -Wno-error=narrowing -fno-rtti
  BUILD_FLAGS_DEFS=-D__MK64FX512__ -DTEENSYDUINO=149
  BUILD_FLAGS_CPU=-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections -nostdlib
  BUILD_COMMAND_SIZE=arm-none-eabi-size
  BUILD_COMMAND_LINKER=arm-none-eabi-gcc
  BUILD_COMMAND_OBJDUMP=arm-none-eabi-objdump
  BUILD_COMMAND_OBJCOPY=arm-none-eabi-objcopy
  BUILD_COMMAND_AR=arm-none-eabi-gcc-ar
  BUILD_COMMAND_G__=arm-none-eabi-g++
  BUILD_COMMAND_GCC=arm-none-eabi-gcc
  BUILD_TOOLCHAIN=arm/bin/
  BUILD_WARN_DATA_PERCENTAGE=98
  BUILD_MCU=mk64fx512
  BUILD_CORE=teensy3
  BUILD_BOARD=TEENSY35
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=262136
  UPLOAD_MAXIMUM_SIZE=524288
  NAME=Teensy 3.5
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, keyboard)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_KEYBOARDONLY
  else ifeq (${IN_USB}, touch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_TOUCHSCREEN
  else ifeq (${IN_USB}, hidtouch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID_TOUCHSCREEN
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, midi4)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI4
  else ifeq (${IN_USB}, midi16)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI16
  else ifeq (${IN_USB}, serialmidi)
    BUILD_USBTYPE=USB_MIDI_SERIAL
  else ifeq (${IN_USB}, serialmidi4)
    BUILD_USBTYPE=USB_MIDI4_SERIAL
  else ifeq (${IN_USB}, serialmidi16)
    BUILD_USBTYPE=USB_MIDI16_SERIAL
  else ifeq (${IN_USB}, audio)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_AUDIO
  else ifeq (${IN_USB}, serialmidiaudio)
    BUILD_USBTYPE=USB_MIDI_AUDIO_SERIAL
  else ifeq (${IN_USB}, serialmidi16audio)
    BUILD_USBTYPE=USB_MIDI16_AUDIO_SERIAL
  else ifeq (${IN_USB}, mtp)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MTPDISK
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  else ifeq (${IN_USB}, flightsimjoystick)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM_JOYSTICK
  else ifeq (${IN_USB}, everything)
    BUILD_USBTYPE=USB_EVERYTHING
  else ifeq (${IN_USB}, disable)
    BUILD_USBTYPE=USB_DISABLED
  endif
  ifeq (${IN_SPEED}, 120)
    BUILD_FCPU=120000000
  else ifeq (${IN_SPEED}, 96)
    BUILD_FCPU=96000000
  else ifeq (${IN_SPEED}, 72)
    BUILD_FCPU=72000000
  else ifeq (${IN_SPEED}, 48)
    BUILD_FCPU=48000000
  else ifeq (${IN_SPEED}, 24)
    BUILD_FCPU=24000000
  else ifeq (${IN_SPEED}, 16)
    BUILD_FCPU=16000000
  else ifeq (${IN_SPEED}, 8)
    BUILD_FCPU=8000000
  else ifeq (${IN_SPEED}, 4)
    BUILD_FCPU=4000000
  else ifeq (${IN_SPEED}, 2)
    BUILD_FCPU=2000000
  else ifeq (${IN_SPEED}, 144)
    BUILD_FCPU=144000000
  else ifeq (${IN_SPEED}, 168)
    BUILD_FCPU=168000000
  endif
  ifeq (${IN_OPT}, o2std)
    BUILD_FLAGS_OPTIMIZE=-O2
  else ifeq (${IN_OPT}, o2lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O2 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o1std)
    BUILD_FLAGS_OPTIMIZE=-O1
  else ifeq (${IN_OPT}, o1lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O1 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3std)
    BUILD_FLAGS_OPTIMIZE=-O3
  else ifeq (${IN_OPT}, o3purestd)
    BUILD_FLAGS_OPTIMIZE=-O3 -mpure-code -D__PURE_CODE__
  else ifeq (${IN_OPT}, o3lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3purelto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -mpure-code -D__PURE_CODE__ -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, ogstd)
    BUILD_FLAGS_OPTIMIZE=-Og
  else ifeq (${IN_OPT}, oglto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Og -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, osstd)
    BUILD_FLAGS_OPTIMIZE=-Os --specs=nano.specs
  else ifeq (${IN_OPT}, oslto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Os -flto -fno-fat-lto-objects --specs=nano.specs
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensy31)
  PID_4=0x0476
  PID_3=0x048A
  PID_2=0x0489
  PID_1=0x0487
  PID_0=0x0483
  VID_4=0x16C0
  VID_3=0x16C0
  VID_2=0x16C0
  VID_1=0x16C0
  VID_0=0x16C0
  SERIAL_RESTART_CMD=false
  BUILD_FLAGS_LIBS=-larm_cortexM4l_math -lm
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++14 -Wno-error=narrowing -fno-rtti
  BUILD_FLAGS_DEFS=-D__MK20DX256__ -DTEENSYDUINO=149
  BUILD_FLAGS_CPU=-mthumb -mcpu=cortex-m4 -fsingle-precision-constant
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections -nostdlib
  BUILD_COMMAND_SIZE=arm-none-eabi-size
  BUILD_COMMAND_LINKER=arm-none-eabi-gcc
  BUILD_COMMAND_OBJDUMP=arm-none-eabi-objdump
  BUILD_COMMAND_OBJCOPY=arm-none-eabi-objcopy
  BUILD_COMMAND_AR=arm-none-eabi-gcc-ar
  BUILD_COMMAND_G__=arm-none-eabi-g++
  BUILD_COMMAND_GCC=arm-none-eabi-gcc
  BUILD_TOOLCHAIN=arm/bin/
  BUILD_WARN_DATA_PERCENTAGE=97
  BUILD_MCU=mk20dx256
  BUILD_CORE=teensy3
  BUILD_BOARD=TEENSY31
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=65536
  UPLOAD_MAXIMUM_SIZE=262144
  NAME=Teensy 3.2 / 3.1
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, keyboard)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_KEYBOARDONLY
  else ifeq (${IN_USB}, touch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_TOUCHSCREEN
  else ifeq (${IN_USB}, hidtouch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID_TOUCHSCREEN
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, midi4)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI4
  else ifeq (${IN_USB}, midi16)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI16
  else ifeq (${IN_USB}, serialmidi)
    BUILD_USBTYPE=USB_MIDI_SERIAL
  else ifeq (${IN_USB}, serialmidi4)
    BUILD_USBTYPE=USB_MIDI4_SERIAL
  else ifeq (${IN_USB}, serialmidi16)
    BUILD_USBTYPE=USB_MIDI16_SERIAL
  else ifeq (${IN_USB}, audio)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_AUDIO
  else ifeq (${IN_USB}, serialmidiaudio)
    BUILD_USBTYPE=USB_MIDI_AUDIO_SERIAL
  else ifeq (${IN_USB}, serialmidi16audio)
    BUILD_USBTYPE=USB_MIDI16_AUDIO_SERIAL
  else ifeq (${IN_USB}, mtp)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MTPDISK
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  else ifeq (${IN_USB}, flightsimjoystick)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM_JOYSTICK
  else ifeq (${IN_USB}, everything)
    BUILD_USBTYPE=USB_EVERYTHING
  else ifeq (${IN_USB}, disable)
    BUILD_USBTYPE=USB_DISABLED
  endif
  ifeq (${IN_SPEED}, 96)
    BUILD_FCPU=96000000
  else ifeq (${IN_SPEED}, 72)
    BUILD_FCPU=72000000
  else ifeq (${IN_SPEED}, 48)
    BUILD_FCPU=48000000
  else ifeq (${IN_SPEED}, 24)
    BUILD_FCPU=24000000
  else ifeq (${IN_SPEED}, 16)
    BUILD_FCPU=16000000
  else ifeq (${IN_SPEED}, 8)
    BUILD_FCPU=8000000
  else ifeq (${IN_SPEED}, 4)
    BUILD_FCPU=4000000
  else ifeq (${IN_SPEED}, 2)
    BUILD_FCPU=2000000
  else ifeq (${IN_SPEED}, 120)
    BUILD_FCPU=120000000
  else ifeq (${IN_SPEED}, 168)
    BUILD_FCPU=168000000
  else ifeq (${IN_SPEED}, 144)
    BUILD_FCPU=144000000
  endif
  ifeq (${IN_OPT}, o2std)
    BUILD_FLAGS_OPTIMIZE=-O2
  else ifeq (${IN_OPT}, o2lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O2 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o1std)
    BUILD_FLAGS_OPTIMIZE=-O1
  else ifeq (${IN_OPT}, o1lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O1 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3std)
    BUILD_FLAGS_OPTIMIZE=-O3
  else ifeq (${IN_OPT}, o3purestd)
    BUILD_FLAGS_OPTIMIZE=-O3 -mpure-code -D__PURE_CODE__
  else ifeq (${IN_OPT}, o3lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3purelto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -mpure-code -D__PURE_CODE__ -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, ogstd)
    BUILD_FLAGS_OPTIMIZE=-Og
  else ifeq (${IN_OPT}, oglto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Og -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, osstd)
    BUILD_FLAGS_OPTIMIZE=-Os --specs=nano.specs
  else ifeq (${IN_OPT}, oslto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Os -flto -fno-fat-lto-objects --specs=nano.specs
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensy30)
  SERIAL_RESTART_CMD=false
  BUILD_FLAGS_LIBS=-larm_cortexM4l_math -lm
  BUILD_FLAGS_LDSPECS=--specs=nano.specs
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++14 -Wno-error=narrowing -fno-rtti
  BUILD_FLAGS_DEFS=-D__MK20DX128__ -DTEENSYDUINO=149
  BUILD_FLAGS_CPU=-mthumb -mcpu=cortex-m4 -fsingle-precision-constant
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections -nostdlib
  BUILD_COMMAND_SIZE=arm-none-eabi-size
  BUILD_COMMAND_LINKER=arm-none-eabi-gcc
  BUILD_COMMAND_OBJDUMP=arm-none-eabi-objdump
  BUILD_COMMAND_OBJCOPY=arm-none-eabi-objcopy
  BUILD_COMMAND_AR=arm-none-eabi-gcc-ar
  BUILD_COMMAND_G__=arm-none-eabi-g++
  BUILD_COMMAND_GCC=arm-none-eabi-gcc
  BUILD_TOOLCHAIN=arm/bin/
  BUILD_WARN_DATA_PERCENTAGE=94
  BUILD_MCU=mk20dx128
  BUILD_CORE=teensy3
  BUILD_BOARD=TEENSY30
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=16384
  UPLOAD_MAXIMUM_SIZE=131072
  NAME=Teensy 3.0
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, keyboard)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_KEYBOARDONLY
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, touch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_TOUCHSCREEN
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, midi4)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI4
  else ifeq (${IN_USB}, serialmidi)
    BUILD_USBTYPE=USB_MIDI_SERIAL
  else ifeq (${IN_USB}, serialmidi4)
    BUILD_USBTYPE=USB_MIDI4_SERIAL
  else ifeq (${IN_USB}, audio)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_AUDIO
  else ifeq (${IN_USB}, serialmidiaudio)
    BUILD_USBTYPE=USB_MIDI_AUDIO_SERIAL
  else ifeq (${IN_USB}, mtp)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MTPDISK
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  else ifeq (${IN_USB}, disable)
    BUILD_USBTYPE=USB_DISABLED
  endif
  ifeq (${IN_SPEED}, 96)
    BUILD_FCPU=96000000
  else ifeq (${IN_SPEED}, 48)
    BUILD_FCPU=48000000
  else ifeq (${IN_SPEED}, 24)
    BUILD_FCPU=24000000
  endif
  ifeq (${IN_OPT}, o2std)
    BUILD_FLAGS_OPTIMIZE=-O2
  else ifeq (${IN_OPT}, o2lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O2 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o1std)
    BUILD_FLAGS_OPTIMIZE=-O1
  else ifeq (${IN_OPT}, o1lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O1 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3std)
    BUILD_FLAGS_OPTIMIZE=-O3
  else ifeq (${IN_OPT}, o3lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, ogstd)
    BUILD_FLAGS_OPTIMIZE=-Og
  else ifeq (${IN_OPT}, oglto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Og -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, osstd)
    BUILD_FLAGS_OPTIMIZE=-Os --specs=nano.specs
  else ifeq (${IN_OPT}, oslto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Os -flto -fno-fat-lto-objects --specs=nano.specs
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensyLC)
  SERIAL_RESTART_CMD=false
  BUILD_FLAGS_LIBS=-larm_cortexM0l_math -lm
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++14 -Wno-error=narrowing -fno-rtti
  BUILD_FLAGS_DEFS=-D__MKL26Z64__ -DTEENSYDUINO=149
  BUILD_FLAGS_CPU=-mthumb -mcpu=cortex-m0plus -fsingle-precision-constant
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections -nostdlib
  BUILD_COMMAND_SIZE=arm-none-eabi-size
  BUILD_COMMAND_LINKER=arm-none-eabi-gcc
  BUILD_COMMAND_OBJDUMP=arm-none-eabi-objdump
  BUILD_COMMAND_OBJCOPY=arm-none-eabi-objcopy
  BUILD_COMMAND_AR=arm-none-eabi-gcc-ar
  BUILD_COMMAND_G__=arm-none-eabi-g++
  BUILD_COMMAND_GCC=arm-none-eabi-gcc
  BUILD_TOOLCHAIN=arm/bin/
  BUILD_WARN_DATA_PERCENTAGE=88
  BUILD_MCU=mkl26z64
  BUILD_CORE=teensy3
  BUILD_BOARD=TEENSYLC
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=8192
  UPLOAD_MAXIMUM_SIZE=63488
  NAME=Teensy LC
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, keyboard)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_KEYBOARDONLY
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, touch)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_TOUCHSCREEN
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, midi4)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI4
  else ifeq (${IN_USB}, serialmidi)
    BUILD_USBTYPE=USB_MIDI_SERIAL
  else ifeq (${IN_USB}, serialmidi4)
    BUILD_USBTYPE=USB_MIDI4_SERIAL
  else ifeq (${IN_USB}, mtp)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MTPDISK
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  else ifeq (${IN_USB}, disable)
    BUILD_USBTYPE=USB_DISABLED
  endif
  ifeq (${IN_SPEED}, 48)
    BUILD_FCPU=48000000
  else ifeq (${IN_SPEED}, 24)
    BUILD_FCPU=24000000
  endif
  ifeq (${IN_OPT}, osstd)
    BUILD_FLAGS_OPTIMIZE=-Os --specs=nano.specs
  else ifeq (${IN_OPT}, oslto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Os -flto -fno-fat-lto-objects --specs=nano.specs
  else ifeq (${IN_OPT}, ogstd)
    BUILD_FLAGS_OPTIMIZE=-Og
  else ifeq (${IN_OPT}, oglto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-Og -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o3std)
    BUILD_FLAGS_OPTIMIZE=-O3
  else ifeq (${IN_OPT}, o3lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O3 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o2std)
    BUILD_FLAGS_OPTIMIZE=-O2
  else ifeq (${IN_OPT}, o2lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O2 -flto -fno-fat-lto-objects
  else ifeq (${IN_OPT}, o1std)
    BUILD_FLAGS_OPTIMIZE=-O1
  else ifeq (${IN_OPT}, o1lto)
    BUILD_FLAGS_LDSPECS=-fuse-linker-plugin
    BUILD_FLAGS_OPTIMIZE=-O1 -flto -fno-fat-lto-objects
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensypp2)
  SERIAL_RESTART_CMD=true
  BUILD_SERIAL_NUMBER=true
  BUILD_FLAGS_LIBS=-lm
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++11
  BUILD_FLAGS_DEFS=-DTEENSYDUINO=149 -DARDUINO_ARCH_AVR
  BUILD_FLAGS_CPU=-mmcu=at90usb1286
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections
  BUILD_COMMAND_SIZE=avr-size
  BUILD_COMMAND_LINKER=avr-gcc
  BUILD_COMMAND_OBJDUMP=avr-objdump
  BUILD_COMMAND_OBJCOPY=avr-objcopy
  BUILD_COMMAND_AR=avr-ar
  BUILD_COMMAND_G__=avr-g++
  BUILD_COMMAND_GCC=avr-gcc
  BUILD_TOOLCHAIN=avr/bin/
  BUILD_WARN_DATA_PERCENTAGE=94
  BUILD_MCU=at90usb1286
  BUILD_CORE=teensy
  BUILD_BOARD=TEENSY2PP
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=8192
  UPLOAD_MAXIMUM_SIZE=130048
  NAME=Teensy++ 2.0
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, int_disk)
    FAKE_SERIAL=teensy_gateway
    BUILD_ELFPATCH=mktinyfat
    BUILD_USBTYPE=USB_DISK
  else ifeq (${IN_USB}, sd_disk)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_DISK_SDFLASH
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  endif
  ifeq (${IN_SPEED}, 16)
    BUILD_FCPU=16000000L
  else ifeq (${IN_SPEED}, 8)
    BUILD_FCPU=8000000L
  else ifeq (${IN_SPEED}, 4)
    BUILD_FCPU=4000000L
  else ifeq (${IN_SPEED}, 2)
    BUILD_FCPU=2000000L
  else ifeq (${IN_SPEED}, 1)
    BUILD_FCPU=1000000L
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
else ifeq (${BOARD_NAME}, teensy2)
  SERIAL_RESTART_CMD=true
  BUILD_SERIAL_NUMBER=true
  BUILD_FLAGS_LIBS=-lm
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax
  BUILD_FLAGS_S=-x assembler-with-cpp
  BUILD_FLAGS_CPP=-fno-exceptions -fpermissive -felide-constructors -std=gnu++11
  BUILD_FLAGS_DEFS=-DTEENSYDUINO=149 -DARDUINO_ARCH_AVR
  BUILD_FLAGS_CPU=-mmcu=atmega32u4
  BUILD_FLAGS_OPTIMIZE=-Os
  BUILD_FLAGS_DEP=-MMD
  BUILD_FLAGS_COMMON=-g -Wall -ffunction-sections -fdata-sections
  BUILD_COMMAND_SIZE=avr-size
  BUILD_COMMAND_LINKER=avr-gcc
  BUILD_COMMAND_OBJDUMP=avr-objdump
  BUILD_COMMAND_OBJCOPY=avr-objcopy
  BUILD_COMMAND_AR=avr-ar
  BUILD_COMMAND_G__=avr-g++
  BUILD_COMMAND_GCC=avr-gcc
  BUILD_TOOLCHAIN=avr/bin/
  BUILD_WARN_DATA_PERCENTAGE=80
  BUILD_MCU=atmega32u4
  BUILD_CORE=teensy
  BUILD_BOARD=TEENSY2
  UPLOAD_PROTOCOL=halfkay
  UPLOAD_TOOL=teensyloader
  UPLOAD_MAXIMUM_DATA_SIZE=2560
  UPLOAD_MAXIMUM_SIZE=32256
  NAME=Teensy 2.0
  ifeq (${IN_USB}, serial)
    BUILD_USBTYPE=USB_SERIAL
  else ifeq (${IN_USB}, hid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_HID
  else ifeq (${IN_USB}, serialhid)
    BUILD_USBTYPE=USB_SERIAL_HID
  else ifeq (${IN_USB}, int_disk)
    FAKE_SERIAL=teensy_gateway
    BUILD_ELFPATCH=mktinyfat
    BUILD_USBTYPE=USB_DISK
  else ifeq (${IN_USB}, sd_disk)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_DISK_SDFLASH
  else ifeq (${IN_USB}, midi)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_MIDI
  else ifeq (${IN_USB}, rawhid)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_RAWHID
  else ifeq (${IN_USB}, flightsim)
    FAKE_SERIAL=teensy_gateway
    BUILD_USBTYPE=USB_FLIGHTSIM
  endif
  ifeq (${IN_SPEED}, 16)
    BUILD_FCPU=16000000L
  else ifeq (${IN_SPEED}, 8)
    BUILD_FCPU=8000000L
  else ifeq (${IN_SPEED}, 4)
    BUILD_FCPU=4000000L
  else ifeq (${IN_SPEED}, 2)
    BUILD_FCPU=2000000L
  else ifeq (${IN_SPEED}, 1)
    BUILD_FCPU=1000000L
  endif
  ifeq (${IN_KEYS}, en-us)
    BUILD_KEYLAYOUT=US_ENGLISH
  else ifeq (${IN_KEYS}, fr-ca)
    BUILD_KEYLAYOUT=CANADIAN_FRENCH
  else ifeq (${IN_KEYS}, xx-ca)
    BUILD_KEYLAYOUT=CANADIAN_MULTILINGUAL
  else ifeq (${IN_KEYS}, cz-cz)
    BUILD_KEYLAYOUT=CZECH
  else ifeq (${IN_KEYS}, da-da)
    BUILD_KEYLAYOUT=DANISH
  else ifeq (${IN_KEYS}, fi-fi)
    BUILD_KEYLAYOUT=FINNISH
  else ifeq (${IN_KEYS}, fr-fr)
    BUILD_KEYLAYOUT=FRENCH
  else ifeq (${IN_KEYS}, fr-be)
    BUILD_KEYLAYOUT=FRENCH_BELGIAN
  else ifeq (${IN_KEYS}, fr-ch)
    BUILD_KEYLAYOUT=FRENCH_SWISS
  else ifeq (${IN_KEYS}, de-de)
    BUILD_KEYLAYOUT=GERMAN
  else ifeq (${IN_KEYS}, de-dm)
    BUILD_KEYLAYOUT=GERMAN_MAC
  else ifeq (${IN_KEYS}, de-ch)
    BUILD_KEYLAYOUT=GERMAN_SWISS
  else ifeq (${IN_KEYS}, is-is)
    BUILD_KEYLAYOUT=ICELANDIC
  else ifeq (${IN_KEYS}, en-ie)
    BUILD_KEYLAYOUT=IRISH
  else ifeq (${IN_KEYS}, it-it)
    BUILD_KEYLAYOUT=ITALIAN
  else ifeq (${IN_KEYS}, no-no)
    BUILD_KEYLAYOUT=NORWEGIAN
  else ifeq (${IN_KEYS}, pt-pt)
    BUILD_KEYLAYOUT=PORTUGUESE
  else ifeq (${IN_KEYS}, pt-br)
    BUILD_KEYLAYOUT=PORTUGUESE_BRAZILIAN
  else ifeq (${IN_KEYS}, rs-rs)
    BUILD_KEYLAYOUT=SERBIAN_LATIN_ONLY
  else ifeq (${IN_KEYS}, es-es)
    BUILD_KEYLAYOUT=SPANISH
  else ifeq (${IN_KEYS}, es-mx)
    BUILD_KEYLAYOUT=SPANISH_LATIN_AMERICA
  else ifeq (${IN_KEYS}, sv-se)
    BUILD_KEYLAYOUT=SWEDISH
  else ifeq (${IN_KEYS}, tr-tr)
    BUILD_KEYLAYOUT=TURKISH
  else ifeq (${IN_KEYS}, en-gb)
    BUILD_KEYLAYOUT=UNITED_KINGDOM
  else ifeq (${IN_KEYS}, usint)
    BUILD_KEYLAYOUT=US_INTERNATIONAL
  endif
endif
BUILD_CORE_PATH=${RUNTIME_PLATFORM_PATH}/cores/${BUILD_CORE}
ifeq (${BOARD_NAME}, teensy40)
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax "-T${BUILD_CORE_PATH}/imxrt1062.ld"
else ifeq (${BOARD_NAME}, teensy36)
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax,--defsym=__rtc_localtime=${EXTRA_TIME_LOCAL} "-T${BUILD_CORE_PATH}/mk66fx1m0.ld" -lstdc++
else ifeq (${BOARD_NAME}, teensy35)
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax,--defsym=__rtc_localtime=${EXTRA_TIME_LOCAL} "-T${BUILD_CORE_PATH}/mk64fx512.ld" -lstdc++
else ifeq (${BOARD_NAME}, teensy31)
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax,--defsym=__rtc_localtime=${EXTRA_TIME_LOCAL} "-T${BUILD_CORE_PATH}/mk20dx256.ld" -lstdc++
else ifeq (${BOARD_NAME}, teensy30)
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax,--defsym=__rtc_localtime=${EXTRA_TIME_LOCAL} "-T${BUILD_CORE_PATH}/mk20dx128.ld" -lstdc++
else ifeq (${BOARD_NAME}, teensyLC)
  BUILD_FLAGS_LD=-Wl,--gc-sections,--relax,--defsym=__rtc_localtime=${EXTRA_TIME_LOCAL} "-T${BUILD_CORE_PATH}/mkl26z64.ld" -lstdc++
endif
DISCOVERY_TEENSY_PATTERN="${RUNTIME_HARDWARE_PATH}/../tools/teensy_ports" -J2
COMPILER_ELF2HEX_FLAGS=-O ihex -R .eeprom
COMPILER_OBJCOPY_EEP_FLAGS=-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0
COMPILER_PATH=${RUNTIME_HARDWARE_PATH}/../tools/
REWRITING=disabled
VERSION=1.8.5
NAME=Teensyduino
ifeq (${UPLOAD_USE_1200BPS_TOUCH}, true)
  UPLOAD_EXTRA_FLAGS=--touch 1200
endif
ifeq (${UPLOAD_TOOL}, teensyloader)
  UPLOAD_PATTERN="${CMD_PATH}/teensy_post_compile" "-file=${BUILD_PROJECT_NAME}" "-path=$(abspath ${BUILD_PATH})" "-tools=${CMD_PATH}" "-board=${BUILD_BOARD}" -reboot "-port=${SERIAL_PORT}" "-portlabel=${SERIAL_PORT_LABEL}" "-portprotocol=${SERIAL_PORT_PROTOCOL}"
endif
ifeq (${BUILD_CORE}, teensy4)
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/analog.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/bootdata.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/clockspeed.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/debugprintf.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/delay.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/digital.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/eeprom.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/interrupt.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/keylayouts.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/nonstd.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/pwm.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/rtc.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/startup.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/tempmon.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_desc.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_joystick.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_keyboard.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_midi.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_mouse.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_rawhid.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_seremu.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_serial.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_touch.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/AudioStream.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/DMAChannel.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/EventResponder.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial1.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial4.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial5.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial6.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial7.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/HardwareSerial8.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/IPAddress.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/IntervalTimer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/Print.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/Stream.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/Tone.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/WMath.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/WString.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/main.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/new.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/usb_inst.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/yield.cpp
  S_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/memcpy-armv7m.S \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4/memset.S
  SYS_INCLUDES+= -I../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4
  VPATH_CORE+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy4
else ifeq (${BUILD_CORE}, teensy3)
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/analog.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/eeprom.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/keylayouts.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/math_helper.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/mk20dx128.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/nonstd.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/pins_teensy.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/ser_print.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial1.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial2.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial3.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial4.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial5.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial6.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/serial6_lpuart.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/touch.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_desc.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_dev.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_joystick.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_keyboard.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_mem.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_midi.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_mouse.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_mtp.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_rawhid.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_seremu.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_serial.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_touch.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/AudioStream.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/DMAChannel.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/EventResponder.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/HardwareSerial1.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/HardwareSerial2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/HardwareSerial3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/HardwareSerial4.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/HardwareSerial5.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/HardwareSerial6.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/IPAddress.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/IntervalTimer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/Print.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/Stream.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/Tone.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/WMath.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/WString.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/avr_emulation.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/main.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/new.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_audio.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_flightsim.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/usb_inst.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/yield.cpp
  S_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/memcpy-armv7m.S \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3/memset.S
  SYS_INCLUDES+= -I../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3
  VPATH_CORE+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy3
else ifeq (${BUILD_CORE}, teensy)
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/WInterrupts.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/keylayouts.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/malloc.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/pins_teensy.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/usb.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/wiring.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/HardwareSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/IPAddress.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/Print.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/Stream.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/Tone.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/WMath.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/WString.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/main.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/new.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/usb_api.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy/yield.cpp
  SYS_INCLUDES+= -I../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy
  VPATH_CORE+=../../Teensyduino-149-b4/hardware/teensy/avr/cores/teensy
endif
ifdef LIB_ADC
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ADC/ADC.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ADC/ADC_Module.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ADC/RingBuffer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ADC/RingBufferDMA.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ADC
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ADC
endif
ifdef LIB_ACCELSTEPPER
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AccelStepper/src/AccelStepper.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AccelStepper/src/MultiStepper.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AccelStepper/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AccelStepper/src
endif
ifdef LIB_ADAFRUIT_CC3000
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/Adafruit_CC3000.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/Adafruit_CC3000_Server.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/ccspi.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/cc3000_common.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/debug.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/evnt_handler.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/hci.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/netapp.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/nvmem.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/security.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/socket.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility/wlan.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_CC3000/utility
endif
ifdef LIB_ADAFRUIT_GFX
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX/fontconvert/fontconvert.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX/glcdfont.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX/Adafruit_GFX.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX/Adafruit_SPITFT.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX/Fonts
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX/fontconvert:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_GFX
endif
ifdef LIB_ADAFRUIT_NEOPIXEL
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_NeoPixel/esp8266.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_NeoPixel
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_NeoPixel
endif
ifdef LIB_ADAFRUIT_RA8875
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_RA8875/Adafruit_RA8875.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_RA8875
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_RA8875
endif
ifdef LIB_ADAFRUIT_STMPE610
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_STMPE610/Adafruit_STMPE610.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_STMPE610
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Adafruit_STMPE610
endif
ifdef LIB_ALTSOFTSERIAL
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AltSoftSerial/AltSoftSerial.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AltSoftSerial \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AltSoftSerial/config
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/AltSoftSerial
endif
ifdef LIB_AUDIO
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/data_spdif.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/data_ulaw.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/data_waveforms.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/data_windows.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/extras/miditones/miditones.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/extras/wav2sketch/wav2sketch.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/utility/sqrt_integer.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_fft1024.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_fft256.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_notefreq.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_peak.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_print.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_rms.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/analyze_tonedetect.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/control_ak4558.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/control_cs42448.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/control_cs4272.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/control_sgtl5000.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/control_tlv320aic3206.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/control_wm8731.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_bitcrusher.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_chorus.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_combine.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_delay.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_delay_ext.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_envelope.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_fade.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_flange.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_freeverb.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_granular.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_midside.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_multiply.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_reverb.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/effect_waveshaper.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/filter_biquad.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/filter_fir.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/filter_variable.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_adc.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_adcs.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_i2s.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_i2s2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_i2s_quad.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_pdm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_tdm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/input_tdm2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/mixer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_adat.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_dac.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_dacs.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_i2s.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_i2s2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_i2s_quad.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_mqs.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_pt8211.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_pt8211_2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_pwm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_spdif.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_spdif2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_spdif3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_tdm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/output_tdm2.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/play_memory.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/play_queue.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/play_sd_raw.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/play_sd_wav.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/play_serialflash_raw.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/record_queue.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/spi_interrupt.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_dc.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_karplusstrong.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_pinknoise.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_pwm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_simple_drum.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_sine.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_tonesweep.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_waveform.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_wavetable.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/synth_whitenoise.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/utility/imxrt_hw.cpp
  S_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/memcpy_audio.S
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/extras/miditones:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/extras/wav2sketch:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Audio/utility
endif
ifdef LIB_BOUNCE2
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Bounce2/Bounce2.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Bounce2
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Bounce2
endif
ifdef LIB_CAPACITIVESENSOR
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CapacitiveSensor/CapacitiveSensor.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CapacitiveSensor
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CapacitiveSensor
endif
ifdef LIB_CRYPTOACCEL
  S_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src/mmcau_aes_functions.S \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src/mmcau_des_functions.S \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src/mmcau_md5_functions.S \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src/mmcau_sha1_functions.S \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src/mmcau_sha256_functions.S
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/CryptoAccel/src
endif
ifdef LIB_DS1307RTC
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/DS1307RTC/DS1307RTC.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/DS1307RTC
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/DS1307RTC
endif
ifdef LIB_DMXSIMPLE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/DmxSimple/DmxSimple.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/DmxSimple
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/DmxSimple
endif
ifdef LIB_EEPROM
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/EEPROM/EEPROM.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/EEPROM
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/EEPROM
endif
ifdef LIB_ENCODER
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Encoder/Encoder.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Encoder \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Encoder/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Encoder
endif
ifdef LIB_ETHERNET
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/Dhcp.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/Dns.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/Ethernet.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/EthernetClient.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/EthernetServer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/EthernetUdp.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/socket.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/utility/w5100.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Ethernet/src/utility
endif
ifdef LIB_FASTCRC
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastCRC/FastCRChw.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastCRC/FastCRCsw.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastCRC
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastCRC
endif
ifdef LIB_FASTLED
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/FastLED.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/bitswap.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/colorpalettes.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/colorutils.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/hsv2rgb.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/lib8tion.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/noise.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/power_mgt.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/wiring.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/lib8tion \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/common \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/d21 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/d51 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/k20 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/k66 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/kl26 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/mxrt1062 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/nrf51 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/nrf52 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/sam \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/arm/stm32 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/avr \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/esp/32 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED/platforms/esp/8266
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FastLED
endif
ifdef LIB_FLEXITIMER2
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FlexiTimer2/FlexiTimer2.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FlexiTimer2
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FlexiTimer2
endif
ifdef LIB_FREQCOUNT
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqCount/FreqCount.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqCount \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqCount/util
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqCount
endif
ifdef LIB_FREQMEASURE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasure/FreqMeasure.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasure \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasure/util
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasure
endif
ifdef LIB_FREQMEASUREMULTI
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasureMulti/FreqMeasureMulti.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasureMulti
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FreqMeasureMulti
endif
ifdef LIB_FREQUENCYTIMER2
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FrequencyTimer2/FrequencyTimer2.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FrequencyTimer2
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/FrequencyTimer2
endif
ifdef LIB_ILI9341_T3
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3/extras/bdf_to_ili9341.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3/font_Arial.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3/font_ArialBold.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3/glcdfont.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3/ILI9341_t3.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3/extras:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9341_t3
endif
ifdef LIB_ILI9488_T3
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3/glcdfont.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3/ili9488_t3_font_Arial.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3/ili9488_t3_font_ArialBold.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3/ili9488_t3_font_ComicSansMS.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3/ILI9488_t3.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ILI9488_t3
endif
ifdef LIB_IRREMOTE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/IRremote.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/irPronto.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/irRecv.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/irSend.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Aiwa.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Denon.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Dish.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_JVC.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_LG.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Lego_PF.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Mitsubishi.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_NEC.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Panasonic.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_RC5_RC6.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Samsung.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Sanyo.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Sharp.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Sony.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Template.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote/ir_Whynter.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/IRremote
endif
ifdef LIB_KEYPAD
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Keypad/src/Key.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Keypad/src/Keypad.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Keypad/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Keypad/src
endif
ifdef LIB_LEDCONTROL
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LedControl/src/LedControl.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LedControl/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LedControl/src
endif
ifdef LIB_LEDDISPLAY
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LedDisplay/LedDisplay.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LedDisplay
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LedDisplay
endif
ifdef LIB_LIQUIDCRYSTAL
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LiquidCrystal/LiquidCrystal.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LiquidCrystal/src/LiquidCrystal.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LiquidCrystal \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LiquidCrystal/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LiquidCrystal:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/LiquidCrystal/src
endif
ifdef LIB_MFRC522
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MFRC522/src/MFRC522.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MFRC522/src/MFRC522Debug.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MFRC522/src/MFRC522Extended.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MFRC522/src/MFRC522Hack.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MFRC522/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MFRC522/src
endif
ifdef LIB_MIDI
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/src/MIDI.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/mocks/test-mocks.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/mocks/test-mocks_SerialMock.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_MidiInput.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_MidiInputCallbacks.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_MidiMessage.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_MidiOutput.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_MidiThru.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_MidiUsb.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_SerialMock.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_Settings.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests/unit-tests_SysExCodec.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/unit-tests.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/doc \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/src \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/mocks \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/src:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/mocks:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests/tests:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MIDI/test/unit-tests
endif
ifdef LIB_MSTIMER2
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MsTimer2/MsTimer2.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MsTimer2
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/MsTimer2
endif
ifdef LIB_NXPMOTIONSENSE
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/NXPMotionSense/matrix.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/NXPMotionSense/NXPMotionSense.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/NXPMotionSense/SensorFusion.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/NXPMotionSense \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/NXPMotionSense/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/NXPMotionSense
endif
ifdef LIB_OSC
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/OSCMatch.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/OSCBundle.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/OSCData.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/OSCMessage.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/OSCTiming.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/SLIPEncodedSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/SLIPEncodedUSBSerial.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/test/OSCBundle_test \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC/test/OSCMessage_encode_decode_test
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OSC
endif
ifdef LIB_OCTOWS2811
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OctoWS2811/extras/VideoSDcard/addaudio/addaudio.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OctoWS2811/OctoWS2811.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OctoWS2811
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OctoWS2811/extras/VideoSDcard/addaudio:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OctoWS2811
endif
ifdef LIB_ONEWIRE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OneWire/OneWire.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OneWire \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OneWire/util
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/OneWire
endif
ifdef LIB_PS2KEYBOARD
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PS2Keyboard/PS2Keyboard.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PS2Keyboard \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PS2Keyboard/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PS2Keyboard
endif
ifdef LIB_PWMSERVO
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PWMServo/PWMServo.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PWMServo
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PWMServo
endif
ifdef LIB_PULSEPOSITION
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PulsePosition/PulsePosition.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PulsePosition/PulsePositionIMXRT.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PulsePosition
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/PulsePosition
endif
ifdef LIB_QUADENCODER
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/QuadEncoder/QuadEncoder.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/QuadEncoder
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/QuadEncoder
endif
ifdef LIB_RA8875
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/Rubic_36.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/SquareOne_14.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/SquareOne_24.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/aerial_22.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/aerial_48.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/akashiSquared_36.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/akashi_36.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/bin_22.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/block_22.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/designerBlock_36.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/dubstreptix_14.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/genow_22.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/heydings_36.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/indieutka_22.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/minipixel_24.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/modo_36.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/orbitron_16.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/squarefont_14.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts/squarefuture_20.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/RA8875.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/_includes \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/_settings
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875/fonts:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/RA8875
endif
ifdef LIB_RESPONSIVEANALOGREAD
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ResponsiveAnalogRead/src/ResponsiveAnalogRead.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ResponsiveAnalogRead/src
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ResponsiveAnalogRead/src
endif
ifdef LIB_SD
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/File.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/SD.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/cache_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/card_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/dir_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/fat_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/file_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/init_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/utility/NXP_SDHC.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/utility/Sd2Card.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/utility/SdFile.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/utility/SdVolume.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SD/utility
endif
ifdef LIB_SPI
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SPI/SPI.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SPI
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SPI
endif
ifdef LIB_ST7735_T3
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/docs/st7735_t3_font_Arial.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/glcdfont.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/st7735_t3_font_Arial.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/st7735_t3_font_ComicSansMS.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/ST7735_t3.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/ST7789_t3.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/docs
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3/docs:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ST7735_t3
endif
ifdef LIB_SERIALFLASH
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SerialFlash/SerialFlashChip.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SerialFlash/SerialFlashDirectory.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SerialFlash \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SerialFlash/util
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SerialFlash
endif
ifdef LIB_SERVO
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Servo/Servo.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Servo
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Servo
endif
ifdef LIB_SNOOZE
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/hal.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/hal.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/hal.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_40/hal.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/hal.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/Snooze.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/SnoozeBlock.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeAlarm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeAudio.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeCompare.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeDigital.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeSPI.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeTimer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeTouch.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/SnoozeUSBSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32/Snoozelc5vBuffer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeAlarm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeAudio.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeCompare.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeDigital.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeSPI.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeTimer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeTouch.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/SnoozeUSBSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35/Snoozelc5vBuffer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeAlarm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeAudio.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeCompare.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeDigital.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeSPI.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeTimer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeTouch.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/SnoozeUSBSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36/Snoozelc5vBuffer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeAlarm.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeAudio.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeCompare.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeDigital.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeSPI.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeTimer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeTouch.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/SnoozeUSBSerial.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC/Snoozelc5vBuffer.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_40 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_32:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_35:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_36:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_40:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src/hal/TEENSY_LC:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Snooze/src
endif
ifdef LIB_SOFTPWM
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SoftPWM/SoftPWM.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SoftPWM
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SoftPWM
endif
ifdef LIB_SOFTWARESERIAL
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SoftwareSerial/SoftwareSerial.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SoftwareSerial
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/SoftwareSerial
endif
ifdef LIB_TFT_ILI9163C
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TFT_ILI9163C/TFT_ILI9163C.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TFT_ILI9163C \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TFT_ILI9163C/_settings
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TFT_ILI9163C
endif
ifdef LIB_TALKIE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Talkie/Talkie.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Talkie
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Talkie
endif
ifdef LIB_TEENSYTHREADS
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TeensyThreads/TeensyThreads.cpp
  S_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TeensyThreads/TeensyThreads-asm.S
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TeensyThreads
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TeensyThreads
endif
ifdef LIB_TIME
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Time/DateStrings.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Time/Time.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Time
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Time
endif
ifdef LIB_TIMEALARMS
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimeAlarms/TimeAlarms.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimeAlarms
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimeAlarms
endif
ifdef LIB_TIMERONE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerOne/TimerOne.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerOne \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerOne/config
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerOne
endif
ifdef LIB_TIMERTHREE
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerThree/TimerThree.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerThree \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerThree/config
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/TimerThree
endif
ifdef LIB_TLC5940
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Tlc5940/Tlc5940.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Tlc5940 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Tlc5940/pinouts
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Tlc5940
endif
ifdef LIB_USBHOST_T36
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/antplus.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/bluetooth.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/digitizer.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/ehci.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/enumeration.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/hid.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/hub.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/joystick.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/keyboard.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/keyboardHIDExtras.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/memory.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/midi.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/mouse.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/print.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/rawhid.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/serial.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36 \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/USBHost_t36
endif
ifdef LIB_WIRE
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire/utility/twi.c
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire/Wire.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire/WireIMXRT.cpp \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire/WireKinetis.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire/utility
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire/utility:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/Wire
endif
ifdef LIB_XPT2046_TOUCHSCREEN
  CPP_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/XPT2046_Touchscreen/XPT2046_Touchscreen.cpp
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/XPT2046_Touchscreen
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/XPT2046_Touchscreen
endif
ifdef LIB_SSD1351
  C_SYS_SRCS+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ssd1351/fontconvert/fontconvert.c \
    ../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ssd1351/glcdfont.c
  SYS_INCLUDES+=-I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ssd1351/Fonts \
    -I../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ssd1351
  VPATH_MORE+=../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ssd1351/fontconvert:../../Teensyduino-149-b4/hardware/teensy/avr/libraries/ssd1351
endif
ifdef LIB_GFX
  C_SYS_SRCS+=libs/GFX/fontconvert/fontconvert.c \
    libs/GFX/glcdfont.c
  CPP_SYS_SRCS+=libs/GFX/Adafruit_GFX.cpp \
    libs/GFX/Adafruit_SPITFT.cpp
  SYS_INCLUDES+=-Ilibs/GFX \
    -Ilibs/GFX/Fonts
  VPATH_MORE+=libs/GFX/fontconvert:libs/GFX
endif
ifdef LIB_SSD1306
  CPP_SYS_SRCS+=libs/SSD1306/Adafruit_SSD1306.cpp
  SYS_INCLUDES+=-Ilibs/SSD1306
  VPATH_MORE+=libs/SSD1306
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
${PROJ_NAME}: ${BUILD_PATH}/${PROJ_NAME}.hex

# Add a 'flash' target
flash: ${BUILD_PATH}/${PROJ_NAME}.flash

# And finally, create the director
# TODO: This no worky on Windows fer sure
${BUILD_PATH}:
	test -d "$@" || mkdir "$@"

# Now, on to the actual rules

${BUILD_PATH}/%.S.o : %.S
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_GCC}" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_S} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_S_EXTRA_FLAGS} "$<" -o "$@"

${BUILD_PATH}/s_compile_commands.json: $(USER_S_SRCS) $(S_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_GCC}\\\" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_S} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_S_EXTRA_FLAGS} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/%.c.o : %.c
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_GCC}" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_C} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_C_EXTRA_FLAGS} "$<" -o "$@"

${BUILD_PATH}/c_compile_commands.json: $(USER_C_SRCS) $(C_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_GCC}\\\" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_C} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_C_EXTRA_FLAGS} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/%.cpp.o : %.cpp
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_G__}" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_CPP} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} "-I${BUILD_PATH}/pch" ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_CPP_EXTRA_FLAGS} "$<" -o "$@"

${BUILD_PATH}/cpp_compile_commands.json: $(USER_CPP_SRCS) $(CPP_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_G__}\\\" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_CPP} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} \\\"-I${BUILD_PATH}/pch\\\" ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_CPP_EXTRA_FLAGS} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/system.a : ${SYS_OBJS}
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_AR}" rcs "$@" $^

${BUILD_PATH}/${BUILD_PROJECT_NAME}.elf : ${BUILD_PATH}/system.a ${USER_OBJS}
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_LINKER}" ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_LD} ${BUILD_FLAGS_LDSPECS} ${BUILD_FLAGS_CPU} -o "$@" ${USER_OBJS} "${BUILD_PATH}/system.a" "-L${BUILD_PATH}" ${BUILD_FLAGS_LIBS}

${BUILD_PATH}/${BUILD_PROJECT_NAME}.hex : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.elf
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_OBJCOPY}" ${COMPILER_ELF2HEX_FLAGS} "$<" "$@"

${BUILD_PATH}/${BUILD_PROJECT_NAME}.flash : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.hex
	${UPLOAD_PATTERN} ${UPLOAD_EXTRA_FLAGS}

${BUILD_PATH}/compile_commands.json: ${BUILD_PATH}/s_compile_commands.json ${BUILD_PATH}/c_compile_commands.json ${BUILD_PATH}/cpp_compile_commands.json
	echo "[" > $@.tmp
	cat $^ >> $@.tmp
	echo "]" >> $@.tmp
	sed -e ':a' -e 'N' -e '$$!ba' -e 's/},\n]/}]/g' $@.tmp > $@

compile_commands: ${BUILD_PATH}/compile_commands.json
