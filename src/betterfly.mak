# Grabbed some stuff from Teensyduino to modify the stuff I slapped together
# for Adafruit. Initially, I'm only getting it working on MacOS, because reasons

# Some simple details
OUT=out-betterfly

# AdaFruit library installation location/version malarkey
ifeq ($(OS),Windows_NT)
	uname:=Windows
else
	uname:=$(shell uname -s)
endif

SSD1306_ROOT=libs/SSD1306
GFX_ROOT=libs/GFX

ifeq ($(uname), Windows)
PORT=COM7
RMFILES=del /q
RMDIR=rmdir /s /q
DIV=$(strip \ )
else
ARDUINOROOT=/Applications/Arduino.app/Contents/Java
RMFILES=rm
RMDIR=rm -rf
DIV=/
endif

TOOLS=${ARDUINOROOT}/hardware/tools
AVR=${ARDUINOROOT}/hardware/teensy/avr

MCU=MK20DX256
MCU_LD=${AVR}/cores/teensy3/mk20dx256.ld
# Tools (probably don't need to change these at all)
CC=${TOOLS}/arm/bin/arm-none-eabi-gcc
CPP=${TOOLS}/arm/bin/arm-none-eabi-g++
OBJCOPY=${TOOLS}/arm/bin/arm-none-eabi-objcopy
AR=${TOOLS}/arm/bin/arm-none-eabi-ar
SIZE=${TOOLS}/arm/bin/arm-none-eabi-size
TEENSY_FLASH=${TOOLS}/teensy_post_compile
TEENSY_REBOOT=${TOOLS}/teensy_reboot

# Flags for compilation
# First, DEBUG configuration flags (then everything else)
# F_CPU = CPU Frequency. 96, 72, 48, 24 all work
# Docs say if I slow it down to 16, USB stops working...
DEFINES=\
-DDEBUG=2 \
-DBETTERFLY \
-DF_CPU=24000000 \
-DARDUINO=10809 \
-DUSB_SERIAL_HID \
-DLAYOUT_US_ENGLISH \
-D__$(MCU)__ \
-DTEENSYDUINO=147 \
-DTEENSY

TARGET=-mcpu=cortex-m4 -mthumb -fsingle-precision-constant
CODEGEN=-ffunction-sections -fdata-sections
FLAGS=-g -Wall -u _printf_float -MMD
CPPLANG=-std=gnu++14 -nostdlib -w -x c++ -fno-rtti -fno-exceptions -fno-threadsafe-statics -felide-constructors
CLANG=-std=gnu1x
SLANG=-x assembler-with-cpp
OPT=-Os

SHARED_SRC = dbgcfg.cpp hardware.cpp boardio.cpp debounce.cpp
BETTERFLY_SRC = globals.cpp betterfly.cpp scanner.cpp kbreporter.cpp
USER_SRC = ${SHARED_SRC} ${BETTERFLY_SRC}

INCLUDES=-Iinclude \
  "-I${AVR}/cores/teensy3"\
  "-I${AVR}/libraries/SPI"\
  "-I${AVR}/libraries/Wire"\
	"-I${GFX_ROOT}"\
	"-I${SSD1306_ROOT}"

ELF_FLAGS = ${OPT} ${TARGET} -save-temps \
-Wl,--defsym=__rtc_localtime=0 \
-Wl,--cref \
-Wl,--check-sections \
-Wl,--gc-sections \
-Wl,--relax \
-Wl,--unresolved-symbols=report-all \
-Wl,--warn-common \
-Wl,--warn-section-align \
--specs=nano.specs

CPPFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CPPLANG} ${DEFINES} ${OPT} ${INCLUDES}
CFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CLANG} ${DEFINES} ${OPT} ${INCLUDES}
SFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${SLANG} ${DEFINES} ${OPT} ${INCLUDES}

CORE_VPATH = ${AVR}/cores/teensy3:${AVR}/libraries/SPI/:${AVR}/libraries/Wire
CORE_SRCS = $(notdir \
  $(wildcard ${AVR}/cores/teensy3/*.c) \
	$(wildcard ${AVR}/cores/teensy3/*.cpp) \
  $(wildcard ${AVR}/libraries/SPI/*.cpp) \
  $(wildcard ${AVR}/libraries/Wire/*.cpp))

LIB_VPATH=${SSD1306_ROOT}:${GFX_ROOT}

GFX_SRCS = \
	Adafruit_SSD1306.cpp \
	Adafruit_GFX.cpp \
	Adafruit_SPITFT.cpp

CORE_OBJS = \
  $(addprefix ${OUT}/, $(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${CORE_SRCS}))))
GFX_OBJS = \
	$(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${GFX_SRCS})))
SHARED_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${SHARED_SRC}))
USER_OBJS =  $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${USER_SRC}))

# This is magic to make the various subdirectories searchable for fulfillings
# various rules in the dependency tree
VPATH=${CORE_VPATH}:${LIB_VPATH}

.PHONY: clean allclean depclean betterfly flash

all: ${OUT} betterfly

DEPS = $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d)

-include ${DEPS}

flash: ${OUT}/betterfly.hex
	${TEENSY_FLASH} -file=betterfly -path=$(abspath ${OUT}) -tools=${TOOLS}
	${TEENSY_REBOOT}

betterfly: ${OUT}/betterfly.hex

# Make us rebuild my own source if I change the makefile
$(USER_OBJS) : Makefile

${OUT}/%.hex : ${OUT}/%.elf
	@echo "OCOPY $@"
	@${SIZE} $<
	@${OBJCOPY} -O ihex -R .eeprom $< $@

${OUT}/betterfly.elf : ${USER_OBJS} ${GFX_OBJS} ${CORE_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ -T${MCU_LD} \
	-Wl,--start-group -lm -lstdc++ ${ALL_LIBS} -Wl,--end-group

${OUT}:
	@-mkdir ${OUT}

allclean:
	@-${RMDIR} ${OUT}

clean:
	@-${RMFILES} $(subst /,${DIV},${USER_OBJS} ${OUT}$*.elf ${OUT}/*.zip ${OUT}/*.hex ${OUT}${DIV}*.map)

depclean:
	@-${RMFILES} ${DEPS}

# And now all the custom subdir rules :/

${OUT}/%.cpp.o: %.cpp
	@echo "CPP $@"
	@${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o: %.c
	@echo "CC $@"
	@${CC} -c ${CFLAGS} -o $@ $<
