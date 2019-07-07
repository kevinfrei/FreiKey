# Let's try this, because Arduino is kind of a PITA
# I basically just copied the crap out of the build output and dumped it here

# Some simple details
OUT=out

# AdaFruit library installation location/version malarkey
# Arduino Version
ARDUINO_VER=10808
# AdaFruit Software Version
ADA_DOT_VER=0.10.2
# "Soft Device" version
SD_VER=132
# "Soft Device" subversion
SDS_DOT_VER=6.1.1
SDS_VER=611
LINKER_SCRIPT=nrf52832_s${SD_VER}_v6.ld

ifeq ($(OS),Windows_NT)
	uname:=Windows
else
	uname:=$(shell uname -s)
endif

# External dependency locations
AFROOT=Adafruit
SSD1306_ROOT=SSD1306
GFX_ROOT=GFX

ifeq ($(uname), Windows)
TOOLSROOT=${HOME}/AppData/Local/Arduino15/packages/arduino
RPORT=COM6
LPORT=COM3
DPORT=COM9
NRFUTIL=${AFROOT}/tools/nrfutil-0.5.2/binaries/win32/nrfutil
RMFILES=del /q
RMDIR=rmdir /s /q
DIV=$(strip \ )
else
TOOLSROOT=${HOME}/Library/Arduino15/packages/arduino
LPORT=/dev/cu.SLAB_USBtoUART
RPORT=/dev/cu.SLAB_USBtoUART
DPORT=/dev/cu.SLAB_USBtoUART
NRFUTIL=${AFROOT}/tools/adafruit-nrfutil/macos/adafruit-nrfutil
RMFILES=rm
RMDIR=rm -rf
DIV=/
endif
TOOLS=${TOOLSROOT}/tools/arm-none-eabi-gcc/7-2017q4

# Tools (probably don't need to change these at all)
CC=${TOOLS}/bin/arm-none-eabi-gcc
CPP=${TOOLS}/bin/arm-none-eabi-g++
OBJCOPY=${TOOLS}/bin/arm-none-eabi-objcopy
AR=${TOOLS}/bin/arm-none-eabi-ar

# Flags for compilation
# First, DEBUG and STATUS_DUMP configuration flags (then everything else)
# -DDEBUG
# -DDEBUG=2
DEFINES=-DSTATUS_DUMP -DDEBUG=2 \
-DF_CPU=64000000 \
-DARDUINO=${ARDUINO_VER} \
-DARDUINO_NRF52_FEATHER \
-DARDUINO_ARCH_NRF52 \
-DARDUINO_BSP_VERSION=\"${ADA_DOT_VER}\" \
-DARDUINO_FEATHER52 \
-DARDUINO_NRF52_ADAFRUIT \
-DNRF5 \
-DNRF52 \
-DNRF52832_XXAA \
-DS${SD_VER} \
-DSD_VER=${SDS_VER} \
-DADAFRUIT \
-DCFG_DEBUG=0
TARGET=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CODEGEN=-nostdlib --param max-inline-insns-single=500 -ffunction-sections -fdata-sections
FLAGS=-g -Wall -u _printf_float -MMD
CPPLANG=-std=gnu++11 -w -x c++ -fno-rtti -fno-exceptions -fno-threadsafe-statics
CLANG=-std=gnu11 -DSOFTDEVICE_PRESENT
SLANG=-x assembler-with-cpp
OPT=-Os

INCLUDES=-Iinclude \
	"-I${AFROOT}/cores/nRF5/cmsis/include"\
	"-I${AFROOT}/cores/nRF5/nordic"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/hal"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/mdk"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/soc"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/drivers/include"\
	"-I${AFROOT}/cores/nRF5/nordic/softdevice/s${SD_VER}_nrf52_${SDS_DOT_VER}_API/include"\
	"-I${AFROOT}/cores/nRF5/freertos/Source/include"\
	"-I${AFROOT}/cores/nRF5/freertos/config"\
	"-I${AFROOT}/cores/nRF5/freertos/portable/GCC/nrf52"\
	"-I${AFROOT}/cores/nRF5/freertos/portable/CMSIS/nrf52"\
	"-I${AFROOT}/cores/nRF5/sysview/SEGGER"\
	"-I${AFROOT}/cores/nRF5/sysview/Config"\
	"-I${AFROOT}/cores/nRF5/Adafruit_TinyUSB_Core"\
	"-I${AFROOT}/cores/nRF5/Adafruit_TinyUSB_Core/tinyusb/src"\
	"-I${AFROOT}/cores/nRF5"\
	"-I${AFROOT}/variants/feather_nrf52832"\
	"-I${AFROOT}/libraries/SPI"\
	"-I${AFROOT}/libraries/Wire"\
	"-I${AFROOT}/libraries/Bluefruit52Lib/src"\
	"-I${AFROOT}/libraries/Adafruit_LittleFS/src"\
	"-I${AFROOT}/libraries/InternalFileSytem/src"\
	"-I${GFX_ROOT}"\
	"-I${SSD1306_ROOT}"

CPPFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CPPLANG} ${DEFINES} ${OPT} ${INCLUDES}
CFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CLANG} ${DEFINES} ${OPT} ${INCLUDES}
SFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${SLANG} ${DEFINES} ${OPT} ${INCLUDES}

SHARED_SRC = dbgcfg.cpp hardware.cpp led_states.cpp boardio.cpp debounce.cpp \
	sleepstate.cpp battery.cpp
RIGHT_SRC = status_dump.cpp globals.cpp right-master.cpp callbacks.cpp \
	scanner.cpp
LEFT_SRC = left-slave.cpp
DISP_SRC = display.cpp disp_uart.cpp
USER_SRC = ${SHARED_SRC} ${RIGHT_SRC} ${LEFT_SRC} ${DISP_SRC}

CORE_DIR = ${AFROOT}/cores/nRF5
CORE_VPATH=${CORE_DIR}:\
	${CORE_DIR}/Adafruit_TinyUSB_Core:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/class/cdc:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/class/custom:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/class/hid:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/class/midi:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/class/msc:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/common:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/device:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src/portable/nordic/nrf5x:\
	${CORE_DIR}/Adafruit_TinyUSB_Core/tinyusb/src:\
	${CORE_DIR}/avr:\
	${CORE_DIR}/freertos/Source:\
	${CORE_DIR}/freertos/Source/portable/MemMang:\
	${CORE_DIR}/freertos/Source:\
	${CORE_DIR}/freertos/portable/CMSIS/nrf52:\
	${CORE_DIR}/freertos/portable/GCC/nrf52:\
	${CORE_DIR}/linker:\
	${CORE_DIR}/nordic/nrfx/drivers/src:\
	${CORE_DIR}/nordic/nrfx/hal:\
	${CORE_DIR}/nordic/nrfx/mdk:\
	${CORE_DIR}/sysview/Config:\
	${CORE_DIR}/sysview/SEGGER:\
	${CORE_DIR}/sysview:\
	${CORE_DIR}/utility:\
	${AFROOT}/variants/feather_nrf52832

CORE_SRCS = \
	Adafruit_TinyUSB_Core.cpp \
	Adafruit_USBD_CDC.cpp \
	Adafruit_USBD_Device.cpp \
	cdc_device.c \
	custom_device.c \
	hid_device.c \
	midi_device.c \
	msc_device.c \
	tusb_fifo.c \
	usbd.c \
	usbd_control.c \
	dcd_nrf5x.c \
	hal_nrf5x.c \
	tusb.c \
	HardwarePWM.cpp \
	IPAddress.cpp \
	Print.cpp \
	RingBuffer.cpp \
	Stream.cpp \
	Uart.cpp \
	WInterrupts.c \
	WMath.cpp \
	WString.cpp \
	abi.cpp \
	dtostrf.c \
	delay.c \
	croutine.c \
	event_groups.c \
	list.c \
	heap_3.c \
	queue.c \
	stream_buffer.c \
	tasks.c \
	timers.c \
	port_cmsis.c \
	port_cmsis_systick.c \
	port.c \
	hooks.c \
	itoa.c \
	gcc_startup_nrf52.S \
	gcc_startup_nrf52840.S \
	main.cpp \
	new.cpp \
	nrfx_power.c \
	nrfx_qspi.c \
	nrf_ecb.c \
	nrf_nvmc.c \
	system_nrf52.c \
	system_nrf52840.c \
	pulse.c \
	pulse_asm.S \
	rtos.cpp \
	syscall_newlib.c \
	SEGGER_SYSVIEW_Config_FreeRTOS.c \
	SEGGER_RTT.c \
	SEGGER_SYSVIEW.c \
	SEGGER_SYSVIEW_FreeRTOS.c \
	AdaCallback.c \
	adafruit_fifo.cpp \
	debug.cpp \
	utilities.c \
	wiring.c \
	wiring_analog.cpp \
	wiring_analog_nRF52.c \
	wiring_digital.c \
	wiring_private.c \
	wiring_shift.c \
	variant.cpp

CORE_OBJS = \
	$(addprefix ${OUT}/, \
		$(patsubst %.c, %.c.o, \
			$(patsubst %.cpp, %.cpp.o, \
				$(patsubst %.S, %.S.o, $(notdir ${CORE_SRCS})))))

BFLIB_DIR = ${AFROOT}/libraries/Bluefruit52Lib/src
BF_VPATH=${BFLIB_DIR}:${BFLIB_DIR}/clients:${BFLIB_DIR}/services:${BFLIB_DIR}/utility

BFLIB_SRCS = \
	BLEAdvertising.cpp \
	BLECentral.cpp \
	BLECharacteristic.cpp \
	BLEClientCharacteristic.cpp \
	BLEClientService.cpp \
	BLEConnection.cpp \
	BLEDiscovery.cpp \
	BLEGatt.cpp \
	BLEPeriph.cpp \
	BLEScanner.cpp \
	BLEService.cpp \
	BLEUuid.cpp \
	bluefruit.cpp \
	BLEAncs.cpp \
	BLEClientBas.cpp \
	BLEClientCts.cpp \
	BLEClientDis.cpp \
	BLEClientHidAdafruit.cpp \
	BLEClientUart.cpp \
	BLEBas.cpp \
	BLEBeacon.cpp \
	BLEDfu.cpp \
	BLEDis.cpp \
	BLEHidAdafruit.cpp \
	BLEHidGeneric.cpp \
	BLEMidi.cpp \
	BLEUart.cpp \
	EddyStone.cpp \
	AdaMsg.cpp \
	bonding.cpp \
	bootloader_util.c

BFLIB_OBJS = \
	$(addprefix ${OUT}/, \
		$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${BFLIB_SRCS}))))

IFS_DIR = ${AFROOT}/libraries/InternalFileSytem/src
LFS_DIR = ${AFROOT}/libraries/Adafruit_LittleFS/src
FS_VPATH=${IFS_DIR}:${IFS_DIR}/flash:${LFS_DIR}:${LFS_DIR}/littlefs

FS_SRCS = \
	InternalFileSystem.cpp \
	flash_cache.c \
	flash_nrf5x.c \
	Adafruit_LittleFS.cpp \
	Adafruit_LittleFS_File.cpp \
	lfs.c \
	lfs_util.c

FS_OBJS = $(addprefix ${OUT}/, \
	$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${FS_SRCS}))))

GFX_VPATH=${SSD1306_ROOT}:${GFX_ROOT}
GFX_SRCS = \
	Adafruit_SSD1306.cpp \
	Adafruit_GFX.cpp \
	Adafruit_SPITFT.cpp

GFX_OBJS = \
	$(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${GFX_SRCS})))

WIRE_VPATH=${AFROOT}/libraries/SPI:${AFROOT}/libraries/Wire
WIRE_SRCS = \
	SPI.cpp \
	Wire_nRF52.cpp

WIRE_OBJS = \
	$(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${WIRE_SRCS})))

ALL_LIBS = ${OUT}/core.a ${OUT}/ada.a
SHARED_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${SHARED_SRC}))
RIGHT_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${RIGHT_SRC}))
LEFT_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${LEFT_SRC}))
DISP_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${DISP_SRC}))
USER_OBJS =  $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${USER_SRC}))

ELF_FLAGS = ${OPT} ${TARGET} -save-temps \
-L${AFROOT}/cores/nRF5/linker \
-L${OUT} \
"-T${LINKER_SCRIPT}" \
-u _printf_float \
-Wl,--cref \
-Wl,--check-sections \
-Wl,--gc-sections \
-Wl,--unresolved-symbols=report-all \
-Wl,--warn-common \
-Wl,--warn-section-align \
--specs=nano.specs \
--specs=nosys.specs

# Learned about VPATH for finding targets of rules :D
# Makes all those custom "for this subdir, dump objs' in ${OUT} useless!
VPATH=${BF_VPATH}:${CORE_VPATH}:${FS_VPATH}:${GFX_VPATH}:${WIRE_VPATH}

.PHONY: clean allclean depclean left right flashl flashr display flashd

all: ${OUT} left right display

DEPS = $(CORE_OBJS:.o=.d) $(NFFS_OBJS:.o=.d) $(BFLIB_OBJS:.o=.d) $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d) $(WIRE_OBJS:.o=.d)

-include ${DEPS}

flashl: ${OUT}/left-slave.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${LPORT} -b 115200 --singlebank

flashr: ${OUT}/right-master.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${RPORT} -b 115200 --singlebank

flashd: ${OUT}/display.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${DPORT} -b 115200 --singlebank

left: ${OUT}/left-slave.zip

right: ${OUT}/right-master.zip

display: ${OUT}/display.zip

# Make us rebuild my own source if I change the makefile
$(USER_OBJS) : Makefile

${OUT}/%.zip : ${OUT}/%.hex
	${NRFUTIL} dfu genpkg --dev-type 0x0052 --sd-req 0x00B7 --application $< $@

${OUT}/%.hex : ${OUT}/%.elf
	@echo "OCOPY $@"
	@${OBJCOPY} -O ihex $< $@

${OUT}/left-slave.elf : ${ALL_LIBS}

${OUT}/right-master.elf : ${ALL_LIBS}

${OUT}/display.elf: ${ALL_LIBS}

${OUT}/left-slave.elf : ${LEFT_OBJS} ${SHARED_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${OUT}/right-master.elf : ${RIGHT_OBJS} ${SHARED_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${OUT}/display.elf : ${DISP_OBJS} ${GFX_OBJS} ${WIRE_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${OUT}/core.a: ${CORE_OBJS}
	-@${RMFILES} $(subst /,${DIV},$@)
	@echo "AR $@"
	@${AR} rcs $@ $^

${OUT}/ada.a: ${BFLIB_OBJS} ${FS_OBJS} ${WIRE_OBJS} ${GFX_OBJS}
	-@${RMFILES} $(subst /,${DIV},$@)
	@echo "AR $@"
	@${AR} rcs $@ $^

${OUT}:
	-@mkdir ${OUT}

allclean:
	@-${RMDIR} ${OUT}

clean:
	@-${RMFILES} $(subst /,${DIV},${USER_OBJS} ${OUT}$*.elf ${OUT}/*.zip ${OUT}/*.hex ${OUT}${DIV}*.map)

depclean:
	@-${RMFILES} ${DEPS}

# And now all the custom build rules

${OUT}/%.S.o : %.S
	@echo "ASM $@"
	@${CC} -c ${SFLAGS} -o $@ $<

${OUT}/%.cpp.o : %.cpp
	@echo "CPP $@"
	@${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o : %.c
	@echo "CC $@"
	@${CC} -c ${CFLAGS} -o $@ $<