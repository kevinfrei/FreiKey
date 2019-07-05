# This is a make file for a setup where the left & right are both
# BLE UART clients, talking to a central BLE UART host, which also
# has a USB connection. Basically: BLE for HID KEY seems unreliable and
# annoying, at least for my particular Mac and my particular PC, so I'm
# abandoning it, and switching to the AdaFruit nRF52 Feather Express as "dongle"

# Initially, this is just a simple dongle. I'm going to add a display eventually

# Some simple details
C_OUT=out_3piece_c
M_OUT=out_3piece_m

# AdaFruit library installation location/version malarkey
# Arduino Version
ARDUINO_VER=10808
# AdaFruit Software Version
ADA_DOT_VER=0.11.0
# Master/Client "Soft Device" version
M_SD_VER=140
C_SD_VER=132
# "Soft Device" subversion
SDS_DOT_VER=6.1.1
SDS_VER=611
C_LINKER_SCRIPT=nrf52832_s${M_SD_VER}_v6.ld
M_LINKER_SCRIPT=nrf52840_s${C_SD_VER}_v6.ld

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
MPORT=/dev/cu.usbmodem141201
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

COMMON_DEFINES=-DSTATUS_DUMP \
-DF_CPU=64000000 \
-DARDUINO=${ARDUINO_VER} \
-DSOFTDEVICE_PRESENT \
-DARDUINO_FEATHER52 \
-DARDUINO_NRF52_ADAFRUIT \
-DNRF52_SERIES \
-DARDUINO_NRF52_FEATHER \
-DLFS_NAME_MAX=64 \
-DARDUINO_ARCH_NRF52 \
-DARDUINO_BSP_VERSION=\"${ADA_DOT_VER}\" \
-DNRF5 \
-DNRF52 \
-DS${SD_VER} \
-DSD_VER=${SDS_VER} \
-DADAFRUIT \
-DCFG_DEBUG=0

M_DEFINES=-DNRF52840_XXAA \
-DARDUINO_NRF52840_FEATHER \
-DUSBCON \
-DUSE_TINYUSB \
-DUSB_VID=0x239A \
-DUSB_PID=0x8029 \
-DUSB_MANUFACTURER=\"Adafruit LLC\" \
-DUSB_PRODUCT=\"Feather nRF52840 Express\" \
-DSOFTDEVICE_PRESENT

C_DEFINES=-DNRF52832_XXAA \
-DARDUINO_NRF52832_FEATHER

TARGET=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CODEGEN=-nostdlib --param max-inline-insns-single=500 -ffunction-sections -fdata-sections
FLAGS=-g -Wall -u _printf_float -MMD
CPPLANG=-std=gnu++11 -w -x c++ -fno-rtti -fno-exceptions -fno-threadsafe-statics
CLANG=-std=gnu11
SLANG=-x assembler-with-cpp
OPT=-Os

COMMON_INCLUDES=-Iinclude \
	"-I${AFROOT}/cores/nRF5/cmsis/include"\
	"-I${AFROOT}/cores/nRF5/nordic"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/hal"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/mdk"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/soc"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/drivers/include"\
	"-I${AFROOT}/cores/nRF5/nordic/nrfx/drivers/src"

M_INCLUDES_1=\
	"-I${AFROOT}/cores/nRF5/nordic/softdevice/s${M_SD_VER}_nrf52_${SDS_DOT_VER}_API/include"

C_INCLUDES_1=\
	"-I${AFROOT}/cores/nRF5/nordic/softdevice/s${C_SD_VER}_nrf52_${SDS_DOT_VER}_API/include"

COMMON_INCLUDES_2 =\
	"-I${AFROOT}/cores/nRF5/freertos/Source/include"\
	"-I${AFROOT}/cores/nRF5/freertos/config"\
	"-I${AFROOT}/cores/nRF5/freertos/portable/GCC/nrf52"\
	"-I${AFROOT}/cores/nRF5/freertos/portable/CMSIS/nrf52"\
	"-I${AFROOT}/cores/nRF5/sysview/SEGGER"\
	"-I${AFROOT}/cores/nRF5/sysview/Config"\
	"-I${AFROOT}/cores/nRF5/Adafruit_TinyUSB_Core"\
	"-I${AFROOT}/cores/nRF5/Adafruit_TinyUSB_Core/tinyusb/src"\
	"-I${AFROOT}/cores/nRF5"

M_INCLUDES_2=\
  "-I${AFROOT}/variants/feather_nrf52840_express"\
	"-I${AFROOT}/libraries/SPI"\
	"-I${AFROOT}/libraries/Wire"\
	"-I${AFROOT}/libraries/Bluefruit52Lib/src"\
  "-I${AFROOT}/libraries/FileSystem/src"\
	"-I${GFX_ROOT}"\
	"-I${SSD1306_ROOT}"

C_INCLUDES_2="-I${AFROOT}/variants/feather_nrf52832"

M_INCLUDES=${COMMON_INCLUDES} ${M_INCLUDES_1} ${COMMON_INCLUDES_2} \
	${M_INCLUDES_2}
C_INCLUDES=${COMMON_INCLUDES} ${C_INCLUDES_1} ${COMMON_INCLUDES_2} ${C_INCLUDES_2}
M_CPPFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CPPLANG} ${DEFINES} ${OPT} ${M_INCLUDES}
M_CFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CLANG} ${DEFINES} ${OPT} ${M_INCLUDES}
M_SFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${SLANG} ${DEFINES} ${OPT} ${M_INCLUDES}

SHARED_SRC = dbgcfg.cpp hardware.cpp led_states.cpp boardio.cpp debounce.cpp \
	sleepstate.cpp battery.cpp
R_SRC = r-client.cpp
L_SRC = l-client.cpp
M_SRC = \
	usb-master.cpp status_dump.cpp globals.cpp  callbacks.cpp scanner.cpp

CORE_DIR = ${AFROOT}/cores/nRF5
CORE_VPATH=${CORE_DIR}:\
${CORE_DIR}/avr:\
${CORE_DIR}/flash:\
${CORE_DIR}/freertos/Source:\
${CORE_DIR}/freertos/Source/portable/MemMang:\
${CORE_DIR}/freertos/portable/CMSIS/nrf52:\
${CORE_DIR}/freertos/portable/GCC/nrf52:\
${CORE_DIR}/linker:\
${CORE_DIR}/nordic/nrfx/drivers/src:\
${CORE_DIR}/nordic/nrfx/hal:\
${CORE_DIR}/nordic/nrfx/mdk:\
${CORE_DIR}/sysview:\
${CORE_DIR}/sysview/Config:\
${CORE_DIR}/sysview/SEGGER:\
${CORE_DIR}/usb:\
${CORE_DIR}/usb/tinyusb/src:\
${CORE_DIR}/usb/tinyusb/src/class/cdc:\
${CORE_DIR}/usb/tinyusb/src/class/custom:\
${CORE_DIR}/usb/tinyusb/src/class/hid:\
${CORE_DIR}/usb/tinyusb/src/class/msc:\
${CORE_DIR}/usb/tinyusb/src/common:\
${CORE_DIR}/usb/tinyusb/src/device:\
${CORE_DIR}/usb/tinyusb/src/osal:\
${CORE_DIR}/usb/tinyusb/src/portable/nordic/nrf5x:\
${CORE_DIR}/utility:\
${AFROOT}/variants/feather_nrf52832

CORE_SRCS = \
	HardwarePWM.cpp\
	IPAddress.cpp\
	Print.cpp\
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
	hooks.c \
	itoa.c \
	main.cpp \
	new.cpp \
	pulse.c \
	pulse_asm.S \
	rtos.cpp \
	variant.cpp \
	wiring.c \
	wiring_analog.cpp \
	wiring_analog_nRF52.c \
	wiring_digital.c \
	wiring_private.c \
	wiring_shift.c \
	syscall_newlib.c \
	flash_cache.c \
	flash_nrf5x.c \
	flash_qspi.c \
	croutine.c \
	event_groups.c \
	list.c \
	queue.c \
	stream_buffer.c \
	tasks.c \
	timers.c \
	heap_3.c \
	port_cmsis.c \
	port_cmsis_systick.c \
	port.c \
	gcc_startup_nrf52.S \
	gcc_startup_nrf52840.S \
	nrfx_power.c \
	nrfx_qspi.c \
	nrf_ecb.c \
	nrf_nvmc.c \
	system_nrf52.c \
	system_nrf52840.c \
	SEGGER_SYSVIEW_FreeRTOS.c \
	SEGGER_SYSVIEW_Config_FreeRTOS.c \
	SEGGER_RTT.c \
	SEGGER_SYSVIEW.c \
	USBSerial.cpp \
	usb.c \
	usb_desc.c \
	usb_msc_flash.c \
	tusb.c \
	cdc_device.c \
	custom_device.c \
	hid_device.c \
	msc_device.c \
	tusb_fifo.c \
	usbd.c \
	usbd_auto_desc.c \
	osal.c \
	dcd_nrf5x.c \
	hal_nrf5x.c \
	AdaCallback.c \
	adafruit_fifo.cpp \
	debug.cpp \
	utilities.c

M_CORE_OBJS = \
	$(addprefix ${M_OUT}/, \
		$(patsubst %.c, %.c.o, \
			$(patsubst %.cpp, %.cpp.o, \
				$(patsubst %.S, %.S.o, $(notdir ${CORE_SRCS})))))

C_CORE_OBJS = \
	$(addprefix ${C_OUT}/, \
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

M_BFLIB_OBJS = \
	$(addprefix ${M_OUT}/, \
		$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${BFLIB_SRCS}))))

C_BFLIB_OBJS = \
	$(addprefix ${C_OUT}/, \
		$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${BFLIB_SRCS}))))

FS_DIR = ${AFROOT}/libraries/FileSystem/src
FS_VPATH=${FS_DIR}:${FS_DIR}/fatfs/source:${FS_DIR}/littlefs

FS_SRCS =\
	Bluefruit_FileIO.cpp \
	ExternalFS.cpp \
	InternalFS.cpp \
	diskio.c \
	ff.c \
	ffsystem.c \
	ffunicode.c \
	lfs.c \
	lfs_util.c

M_FS_OBJS = $(addprefix ${M_OUT}/, \
	$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${FS_SRCS}))))
C_FS_OBJS = $(addprefix ${C_OUT}/, \
	$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${FS_SRCS}))))

GFX_VPATH=${SSD1306_ROOT}:${GFX_ROOT}
GFX_SRCS = \
	Adafruit_SSD1306.cpp \
	Adafruit_GFX.cpp \
	Adafruit_SPITFT.cpp
M_GFX_OBJS = \
	$(addprefix ${M_OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${GFX_SRCS})))
C_GFX_OBJS = \
	$(addprefix ${C_OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${GFX_SRCS})))

WIRE_VPATH=${AFROOT}/libraries/SPI:${AFROOT}/libraries/Wire
WIRE_SRCS = SPI.cpp Wire_nRF52.cpp
M_WIRE_OBJS = \
	$(addprefix ${M_OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${WIRE_SRCS})))
C_WIRE_OBJS = \
	$(addprefix ${C_OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${WIRE_SRCS})))

M_LIBS = ${M_OUT}/m_core.a ${M_OUT}/m_ada.a
C_LIBS = ${C_OUT}/c_core.a ${C_OUT}/c_ada.a
M_SHARED_OBJS = $(addprefix ${M_OUT}/, $(patsubst %.cpp, %.cpp.o, ${SHARED_SRC}))
C_SHARED_OBJS = $(addprefix ${C_OUT}/, $(patsubst %.cpp, %.cpp.o, ${SHARED_SRC}))
R_OBJS = $(addprefix ${C_OUT}/, $(patsubst %.cpp, %.cpp.o, ${R_SRC}))
L_OBJS = $(addprefix ${C_OUT}/, $(patsubst %.cpp, %.cpp.o, ${L_SRC}))
M_OBJS = $(addprefix ${M_OUT}/, $(patsubst %.cpp, %.cpp.o, ${M_SRC}))
USER_OBJS =  ${M_SHARED_OBJS} ${C_SHARED_OBJS} ${M_OBJS} ${R_OBJS} ${L_OBJS}

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

.PHONY: clean allclean depclean left right master flashl flashr flashm

all: ${M_OUT} ${C_OUT} left right master

DEPS = $(CORE_OBJS:.o=.d) $(NFFS_OBJS:.o=.d) $(BFLIB_OBJS:.o=.d) $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d) $(WIRE_OBJS:.o=.d)

-include ${DEPS}

flashl: ${C_OUT}/l-client.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${LPORT} -b 115200 --singlebank

flashr: ${C_OUT}/r-client.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${RPORT} -b 115200 --singlebank

flashm: ${M_OUT}/usb-master.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${MPORT} -b 115200 --singlebank

left: ${C_OUT}/l-client.zip

right: ${C_OUT}/r-client.zip

usb-master: ${OUT}/usb-master.zip

# Make us rebuild just my own source if I change the makefile
$(USER_OBJS) : Makefile

${C_OUT}/%.zip : ${C_OUT}/%.hex
	${NRFUTIL} dfu genpkg --dev-type 0x0052 --sd-req 0x00B7 --application $< $@

${M_OUT}/%.zip : ${M_OUT}/%.hex
	${NRFUTIL} dfu genpkg --dev-type 0x0052 --sd-req 0x00B7 --application $< $@

${C_OUT}/%.hex : ${C_OUT}/%.elf
	@echo "OCOPY $@"
	@${OBJCOPY} -O ihex $< $@

${M_OUT}/%.hex : ${M_OUT}/%.elf
	@echo "OCOPY $@"
	@${OBJCOPY} -O ihex $< $@

${C_OUT}/l-client.elf : ${C_LIBS}

${C_OUT}/r-client.elf : ${C_LIBS}

${M_OUT}/usb-master.elf: ${M_LIBS}

${C_OUT}/l-client.elf : ${L_OBJS} ${C_SHARED_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${C_OUT}/r-client.elf : ${R_OBJS} ${C_SHARED_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${M_OUT}/usb-master.elf : ${M_OBJS} ${GFX_OBJS} ${WIRE_OBJS}
	@echo "LINK $@"
	@${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${C_OUT}/c_core.a: ${CORE_OBJS}
	-@${RMFILES} $(subst /,${DIV},$@)
	@echo "AR $@"
	@${AR} rcs $@ $^

${M_OUT}/m_core.a: ${CORE_OBJS}
	-@${RMFILES} $(subst /,${DIV},$@)
	@echo "AR $@"
	@${AR} rcs $@ $^

${C_OUT}/c_ada.a: ${BFLIB_OBJS} ${FS_OBJS} ${WIRE_OBJS} ${GFX_OBJS}
	-@${RMFILES} $(subst /,${DIV},$@)
	@echo "AR $@"
	@${AR} rcs $@ $^

${M_OUT}/m_ada.a: ${BFLIB_OBJS} ${FS_OBJS} ${WIRE_OBJS} ${GFX_OBJS}
	-@${RMFILES} $(subst /,${DIV},$@)
	@echo "AR $@"
	@${AR} rcs $@ $^

${C_OUT}:
	-@mkdir ${C_OUT}

${M_OUT}:
	-@mkdir ${M_OUT}

allclean:
	@-${RMDIR} ${C_OUT} ${M_OUT}

clean:
	@-${RMFILES} $(subst /,${DIV},${USER_OBJS} ${C_OUT}/*.elf ${M_OUT}/*.elf ${M_OUT}/*.zip ${C_OUT}/*.zip ${C_OUT}/*.hex ${M_OUT}/*.hex ${M_OUT}/*.map ${C_OUT}/*.map)

depclean:
	@-${RMFILES} ${DEPS}

# And now all the custom build rules

${C_OUT}/%.S.o : %.S
	@echo "ASM $@"
	@${CC} -c ${C_SFLAGS} -o $@ $<

${M_OUT}/%.S.o : %.S
	@echo "ASM $@"
	@${CC} -c ${M_SFLAGS} -o $@ $<

${C_OUT}/%.cpp.o : %.cpp
	@echo "CPP $@"
	@${CPP} -c ${C_CPPFLAGS} -o $@ $<

${M_OUT}/%.cpp.o : %.cpp
	@echo "CPP $@"
	@${CPP} -c ${M_CPPFLAGS} -o $@ $<

${C_OUT}/%.c.o : %.c
	@echo "CC $@"
	@${CC} -c ${C_CFLAGS} -o $@ $<

${M_OUT}/%.c.o : %.c
	@echo "CC $@"
	@${CC} -c ${M_CFLAGS} -o $@ $<