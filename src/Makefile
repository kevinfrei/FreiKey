# Let's try this, because Arduino is kind of a PITA
# I basically just copied the crap out of the build output and dumped it here

# Some simple details
OUT=out

# AdaFruit library installation location/version malarkey
VER=0.8.4
ifeq ($(OS),Windows_NT)
	uname:=Windows
else
	uname:=$(shell uname -s)
endif

AFROOT=../../Adafruit_nRF52_Arduino
SSD1306_ROOT=../../Adafruit_SSD1306
GFX_ROOT=../../Adafruit-GFX-Library
ifeq ($(uname), Windows)
ADAFRUIT=${HOME}/AppData/Local/Arduino15/packages/adafruit
RPORT=COM6
LPORT=COM3
DPORT=COM9
NRFUTIL=${AFROOT}/tools/nrfutil-0.5.2/binaries/win32/nrfutil
RMFILES=del /q
RMDIR=rmdir /s /q
DIV=$(strip \ )
else
ADAFRUIT=${HOME}/Library/Arduino15/packages/adafruit
LPORT=/dev/cu.SLAB_USBtoUART
RPORT=/dev/cu.SLAB_USBtoUART
DPORT=/dev/cu.SLAB_USBtoUART
NRFUTIL=/usr/local/bin/nrfutil
RMFILES=rm
RMDIR=rm -rf
DIV=/
endif
TOOLS=${ADAFRUIT}/tools/gcc-arm-none-eabi/5_2-2015q4

# Tools (probably don't need to change these at all)
CC=${TOOLS}/bin/arm-none-eabi-gcc
CPP=${TOOLS}/bin/arm-none-eabi-g++
OBJCOPY=${TOOLS}/bin/arm-none-eabi-objcopy
AR=${TOOLS}/bin/arm-none-eabi-ar

# Flags for compilation
# First, DEBUG and STATUS_DUMP configuration flags (then everything else)
DEFINES=-DDEBUG -DSTATUS_DUMP \
-DF_CPU=64000000 \
-DARDUINO=10805 \
-DARDUINO_NRF52_FEATHER \
-DARDUINO_ARCH_NRF52 \
-DARDUINO_BSP_VERSION=\"${VER}\" \
-DARDUINO_FEATHER52 \
-DARDUINO_NRF52_ADAFRUIT \
-DNRF5 \
-DNRF52 \
-DNRF52832_XXAA \
-DUSE_LFXO \
-DS132 \
-DSD_VER=510 \
-DCFG_DEBUG=0
TARGET=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CODEGEN=-nostdlib --param max-inline-insns-single=500 -ffunction-sections -fdata-sections
FLAGS=-g -Wall -u _printf_float -MMD
CPPLANG=-std=gnu++11 -w -x c++ -fno-rtti -fno-exceptions -fno-threadsafe-statics
CLANG=-std=gnu11 -DSOFTDEVICE_PRESENT
SLANG=-x assembler-with-cpp
OPT=-Os

SHARED_SRC = dbgcfg.cpp hardware.cpp led_states.cpp boardio.cpp debounce.cpp \
	sleepstate.cpp battery.cpp
RIGHT_SRC = status_dump.cpp globals.cpp right-master.cpp callbacks.cpp \
	scanner.cpp
LEFT_SRC = left-slave.cpp
DISP_SRC = display.cpp disp_uart.cpp
USER_SRC = ${SHARED_SRC} ${RIGHT_SRC} ${LEFT_SRC} ${DISP_SRC}

INCLUDES=-Iinclude \
	"-I${AFROOT}/cores/nRF5/SDK/components/toolchain/"\
	"-I${AFROOT}/cores/nRF5/SDK/components/toolchain/cmsis/include"\
	"-I${AFROOT}/cores/nRF5/SDK/components/toolchain/gcc/"\
	"-I${AFROOT}/cores/nRF5/SDK/components/device/"\
	"-I${AFROOT}/cores/nRF5/SDK/components/drivers_nrf/delay/"\
	"-I${AFROOT}/cores/nRF5/SDK/components/drivers_nrf/hal/"\
	"-I${AFROOT}/cores/nRF5/SDK/components/libraries/util/"\
	"-I${AFROOT}/cores/nRF5/softdevice/s132/5.1.0/headers/"\
	"-I${AFROOT}/cores/nRF5/freertos/source/include"\
	"-I${AFROOT}/cores/nRF5/freertos/config"\
	"-I${AFROOT}/cores/nRF5/freertos/portable/GCC/nrf52"\
	"-I${AFROOT}/cores/nRF5/freertos/portable/CMSIS/nrf52"\
	"-I${AFROOT}/cores/nRF5/sysview/SEGGER"\
	"-I${AFROOT}/cores/nRF5/sysview/Config"\
	"-I${AFROOT}/libraries/nffs/src/fs/nffs/include"\
	"-I${AFROOT}/libraries/nffs/src/fs/fs/include"\
	"-I${AFROOT}/libraries/nffs/src/fs/disk/include"\
	"-I${AFROOT}/libraries/nffs/src/util/crc/include"\
	"-I${AFROOT}/libraries/nffs/src/kernel/os/include"\
	"-I${AFROOT}/libraries/nffs/src/kernel/os/include/os/arch/cortex_m4"\
	"-I${AFROOT}/libraries/nffs/src/hw/hal/include"\
	"-I${AFROOT}/libraries/nffs/src/sys/flash_map/include"\
	"-I${AFROOT}/libraries/nffs/src/sys/defs/include"\
	"-I${AFROOT}/cores/nRF5"\
	"-I${AFROOT}/variants/feather52"\
	"-I${AFROOT}/libraries/Bluefruit52Lib/src"\
	"-I${AFROOT}/libraries/nffs/src"\
	"-I${AFROOT}/libraries/SPI"\
	"-I${AFROOT}/libraries/Wire"\
	"-I${GFX_ROOT}"\
	"-I${SSD1306_ROOT}"

CPPFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CPPLANG} ${DEFINES} ${OPT} ${INCLUDES}
CFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${CLANG} ${DEFINES} ${OPT} ${INCLUDES}
SFLAGS=${TARGET} ${FLAGS} ${CODEGEN} ${SLANG} ${DEFINES} ${OPT} ${INCLUDES}

BFLIB_SRCS =\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEAdvertising.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLECentral.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLECharacteristic.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEClientCharacteristic.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEClientService.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEDiscovery.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEGap.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEGatt.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEScanner.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEService.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/BLEUuid.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/bluefruit.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/clients/BLEAncs.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/clients/BLEClientCts.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/clients/BLEClientDis.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/clients/BLEClientUart.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEBas.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEBeacon.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEDfu.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEDis.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEHidAdafruit.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEHidGeneric.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEMidi.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/BLEUart.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/bonding.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/services/EddyStone.cpp\
	${AFROOT}/libraries/Bluefruit52Lib/src/utility/bootloader_util.c\
	${AFROOT}/libraries/Bluefruit52Lib/src/utility/AdaMsg.cpp

BFLIB_DIR = ${AFROOT}/libraries/Bluefruit52Lib/src
BFLIB_DIRCLIENTS = ${BFLIB_DIR}/clients
BFLIB_DIRSERVICES = ${BFLIB_DIR}/services
BFLIB_DIRUTILITY = ${BFLIB_DIR}/utility

BFLIB_OBJS = \
	$(addprefix ${OUT}/, \
		$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${BFLIB_SRCS}))))

NFFS_SRCS =\
	${AFROOT}/libraries/nffs/src/Nffs.cpp\
	${AFROOT}/libraries/nffs/src/NffsDir.cpp\
	${AFROOT}/libraries/nffs/src/NffsDirEntry.cpp\
	${AFROOT}/libraries/nffs/src/NffsFile.cpp\
	${AFROOT}/libraries/nffs/src/fs/disk/src/disk.c\
	${AFROOT}/libraries/nffs/src/fs/fs/src/fs_cli.c\
	${AFROOT}/libraries/nffs/src/fs/fs/src/fs_dirent.c\
	${AFROOT}/libraries/nffs/src/fs/fs/src/fs_file.c\
	${AFROOT}/libraries/nffs/src/fs/fs/src/fs_mkdir.c\
	${AFROOT}/libraries/nffs/src/fs/fs/src/fs_mount.c\
	${AFROOT}/libraries/nffs/src/fs/fs/src/fsutil.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_area.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_block.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_cache.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_config.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_crc.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_dir.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_file.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_flash.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_format.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_gc.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_hash.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_inode.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_misc.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_path.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_restore.c\
	${AFROOT}/libraries/nffs/src/fs/nffs/src/nffs_write.c\
	${AFROOT}/libraries/nffs/src/hw/hal/src/hal_flash.c\
	${AFROOT}/libraries/nffs/src/kernel/os/src/os_mempool.c\
	${AFROOT}/libraries/nffs/src/sys/flash_map/src/flash_map.c\
	${AFROOT}/libraries/nffs/src/util/crc/src/crc16.c\
	${AFROOT}/libraries/nffs/src/util/crc/src/crc8.c

NFFS_DIR = ${AFROOT}/libraries/nffs/src
NFFS_DIR_DISK = ${NFFS_DIR}/fs/disk/src
NFFS_DIR_FS = ${NFFS_DIR}/fs/fs/src
NFFS_DIR_NFFS = ${NFFS_DIR}/fs/nffs/src
NFFS_DIR_HAL = ${NFFS_DIR}/hw/hal/src
NFFS_DIR_KRNL = ${NFFS_DIR}/kernel/os/src
NFFS_DIR_FLASH = ${NFFS_DIR}/sys/flash_map/src
NFFS_DIR_CRC = ${NFFS_DIR}/util/crc/src

NFFS_OBJS = $(addprefix ${OUT}/, \
	$(patsubst %.c, %.c.o, $(patsubst %.cpp, %.cpp.o, $(notdir ${NFFS_SRCS}))))

CORE_SRCS = \
	${AFROOT}/variants/feather52/variant.cpp\
	${AFROOT}/cores/nRF5/gcc_startup_nrf52.S\
	${AFROOT}/cores/nRF5/pulse_asm.S\
	${AFROOT}/cores/nRF5/WInterrupts.c\
	${AFROOT}/cores/nRF5/delay.c\
	${AFROOT}/cores/nRF5/hooks.c\
	${AFROOT}/cores/nRF5/itoa.c\
	${AFROOT}/cores/nRF5/nrf52_flash.c\
	${AFROOT}/cores/nRF5/pulse.c\
	${AFROOT}/cores/nRF5/syscall_newlib.c\
	${AFROOT}/cores/nRF5/wiring.c\
	${AFROOT}/cores/nRF5/wiring_analog_nRF52.c\
	${AFROOT}/cores/nRF5/wiring_digital.c\
	${AFROOT}/cores/nRF5/wiring_private.c\
	${AFROOT}/cores/nRF5/wiring_shift.c\
	${AFROOT}/cores/nRF5/SDK/components/libraries/util/app_util_platform.c\
	${AFROOT}/cores/nRF5/SDK/components/toolchain/system_nrf52.c\
	${AFROOT}/cores/nRF5/avr/dtostrf.c\
	${AFROOT}/cores/nRF5/freertos/portable/CMSIS/nrf52/port_cmsis.c\
	${AFROOT}/cores/nRF5/freertos/portable/CMSIS/nrf52/port_cmsis_systick.c\
	${AFROOT}/cores/nRF5/freertos/portable/GCC/nrf52/port.c\
	${AFROOT}/cores/nRF5/freertos/source/croutine.c\
	${AFROOT}/cores/nRF5/freertos/source/event_groups.c\
	${AFROOT}/cores/nRF5/freertos/source/list.c\
	${AFROOT}/cores/nRF5/freertos/source/queue.c\
	${AFROOT}/cores/nRF5/freertos/source/tasks.c\
	${AFROOT}/cores/nRF5/freertos/source/timers.c\
	${AFROOT}/cores/nRF5/freertos/source/portable/MemMang/heap_3.c\
	${AFROOT}/cores/nRF5/sysview/SEGGER_SYSVIEW_Config_FreeRTOS.c\
	${AFROOT}/cores/nRF5/sysview/SEGGER_SYSVIEW_FreeRTOS.c\
	${AFROOT}/cores/nRF5/sysview/SEGGER/SEGGER_RTT.c\
	${AFROOT}/cores/nRF5/sysview/SEGGER/SEGGER_SYSVIEW.c\
	${AFROOT}/cores/nRF5/utility/AdaCallback.c\
	${AFROOT}/cores/nRF5/utility/utilities.c\
	${AFROOT}/cores/nRF5/HardwarePWM.cpp\
	${AFROOT}/cores/nRF5/IPAddress.cpp\
	${AFROOT}/cores/nRF5/Print.cpp\
	${AFROOT}/cores/nRF5/RingBuffer.cpp\
	${AFROOT}/cores/nRF5/Stream.cpp\
	${AFROOT}/cores/nRF5/Uart.cpp\
	${AFROOT}/cores/nRF5/WMath.cpp\
	${AFROOT}/cores/nRF5/WString.cpp\
	${AFROOT}/cores/nRF5/abi.cpp\
	${AFROOT}/cores/nRF5/debug.cpp\
	${AFROOT}/cores/nRF5/main.cpp\
	${AFROOT}/cores/nRF5/new.cpp\
	${AFROOT}/cores/nRF5/rtos.cpp\
	${AFROOT}/cores/nRF5/wiring_analog.cpp\
	${AFROOT}/cores/nRF5/utility/adafruit_fifo.cpp

CORE_DIR = ${AFROOT}/cores/nRF5
CORE_DIR_VAR = ${AFROOT}/variants/feather52
CORE_DIR_UTIL = ${CORE_DIR}/utility
CORE_DIR_SDKUTIL = ${CORE_DIR}/SDK/components/libraries/util
CORE_DIR_TOOLCHAIN = ${CORE_DIR}/SDK/components/toolchain
CORE_DIR_AVR = ${CORE_DIR}/avr
CORE_DIR_RTOS_CMSIS = ${CORE_DIR}/freertos/portable/CMSIS/nrf52
CORE_DIR_RTOS_GCC = ${CORE_DIR}/freertos/portable/GCC/nrf52
CORE_DIR_RTOS = ${CORE_DIR}/freertos/source
CORE_DIR_RTOS_MEM = ${CORE_DIR}/freertos/source/portable/MemMang
CORE_DIR_SYSVIEW = ${CORE_DIR}/sysview
CORE_DIR_SV_SEG = ${CORE_DIR}/sysview/SEGGER

CORE_OBJS = \
	$(addprefix ${OUT}/, \
		$(patsubst %.c, %.c.o, \
			$(patsubst %.cpp, %.cpp.o, \
				$(patsubst %.S, %.S.o, $(notdir ${CORE_SRCS})))))

GFX_SRCS = \
	${SSD1306_ROOT}/Adafruit_SSD1306.cpp \
	${GFX_ROOT}/Adafruit_GFX.cpp \
	${GFX_ROOT}/Adafruit_SPITFT.cpp

GFX_OBJS = \
	$(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${GFX_SRCS})))

SER_SRCS = \
	${AFROOT}/libraries/SPI/SPI.cpp\
	${AFROOT}/libraries/Wire/Wire_nRF52.cpp

SER_OBJS = \
	$(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, $(notdir ${SER_SRCS})))

ALL_LIBS = ${OUT}/core.a ${OUT}/nffs.a ${OUT}/bflib.a
SHARED_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${SHARED_SRC}))
RIGHT_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${RIGHT_SRC}))
LEFT_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${LEFT_SRC}))
DISP_OBJS = $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${DISP_SRC}))
USER_OBJS =  $(addprefix ${OUT}/, $(patsubst %.cpp, %.cpp.o, ${USER_SRC}))

ELF_FLAGS = ${OPT} ${TARGET} -save-temps \
-L${AFROOT}/cores/nRF5/linker \
-L${OUT} \
"-Tbluefruit52_s132_5.1.0.ld" \
-u _printf_float \
-Wl,--cref \
-Wl,--check-sections \
-Wl,--gc-sections \
-Wl,--unresolved-symbols=report-all \
-Wl,--warn-common \
-Wl,--warn-section-align \
--specs=nano.specs \
--specs=nosys.specs

.PHONY: clean allclean depclean left right flashl flashr display flashd

all: ${OUT} left right display

DEPS = $(CORE_OBJS:.o=.d) $(NFFS_OBJS:.o=.d) $(BFLIB_OBJS:.o=.d) $(USER_OBJS:.o=.d) $(GFX_OBJS:.o=.d) $(SER_OBJS:.o=.d)

-include ${DEPS}

flashl: ${OUT}/left-slave.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${LPORT} -b 115200

flashr: ${OUT}/right-master.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${RPORT} -b 115200

flashd: ${OUT}/display.zip
	${NRFUTIL} --verbose dfu serial -pkg $< -p ${DPORT} -b 115200

left: ${OUT}/left-slave.zip

right: ${OUT}/right-master.zip

display: ${OUT}/display.zip

# Make us rebuild my own source if I change the makefile
$(USER_OBJS) : Makefile

${OUT}/%.zip : ${OUT}/%.hex
	${NRFUTIL} dfu genpkg --dev-type 0x0052 --sd-req 0x00A5 --application $< $@

${OUT}/%.hex : ${OUT}/%.elf
	${OBJCOPY} -O ihex $< $@

${OUT}/left-slave.elf : ${ALL_LIBS}

${OUT}/right-master.elf : ${ALL_LIBS}

${OUT}/display.elf: ${ALL_LIBS}

${OUT}/left-slave.elf : ${LEFT_OBJS} ${SHARED_OBJS}
	${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${OUT}/right-master.elf : ${RIGHT_OBJS} ${SHARED_OBJS}
	${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${OUT}/display.elf : ${DISP_OBJS} ${GFX_OBJS} ${SER_OBJS}
	${CC} ${ELF_FLAGS} "-Wl,-Map,$@.map" -o $@ $^ \
	-Wl,--start-group -lm ${ALL_LIBS} -Wl,--end-group

${OUT}/core.a: ${CORE_OBJS}
	-${RMFILES} $(subst /,${DIV},$@)
	${AR} rcs $@ ${CORE_OBJS}

${OUT}/nffs.a: ${NFFS_OBJS}
	-${RMFILES} $(subst /,${DIV},$@)
	${AR} rcs $@ ${NFFS_OBJS}

${OUT}/bflib.a: ${BFLIB_OBJS}
	-${RMFILES} $(subst /,${DIV},$@)
	${AR} rcs $@ ${BFLIB_OBJS}

${OUT}:
	@-mkdir ${OUT}

allclean:
	@-${RMDIR} ${OUT}

clean:
	@-${RMFILES} $(subst /,${DIV},${USER_OBJS} ${OUT}$*.elf ${OUT}/*.zip ${OUT}/*.hex ${OUT}${DIV}*.map)

depclean:
	@-${RMFILES} ${DEPS}
# And now all the custom subdir rules :/

${OUT}/%.S.o : ${CORE_DIR}/%.S
	${CC} -c ${SFLAGS} -o $@ $<

${OUT}/%.cpp.o : ${CORE_DIR}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.cpp.o : ${CORE_DIR_VAR}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_UTIL}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.cpp.o : ${CORE_DIR_UTIL}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_SDKUTIL}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_TOOLCHAIN}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_AVR}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_RTOS_CMSIS}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_RTOS_GCC}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_RTOS}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_RTOS_MEM}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_SYSVIEW}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o : ${CORE_DIR_SV_SEG}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.cpp.o: %.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${NFFS_DIR}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_DISK}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_FS}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_NFFS}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_HAL}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_KRNL}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_FLASH}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.c.o: ${NFFS_DIR_CRC}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${BFLIB_DIR}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${BFLIB_DIRSERVICES}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${BFLIB_DIRCLIENTS}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${BFLIB_DIRUTILITY}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.c.o: ${BFLIB_DIRUTILITY}/%.c
	${CC} -c ${CFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${GFX_ROOT}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${SSD1306_ROOT}/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${AFROOT}/libraries/SPI/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<

${OUT}/%.cpp.o: ${AFROOT}/libraries/Wire/%.cpp
	${CPP} -c ${CPPFLAGS} -o $@ $<
