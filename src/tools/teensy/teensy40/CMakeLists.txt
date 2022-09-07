cmake_minimum_required(VERSION 3.12)

# Must be before the project command:
# Do I need to set this in here too?
project(teensy4_syslib)

if(CMAKE_HOST_WIN32)
  set(A2CM_TEENSY4_LIB_ROOT_DIR "c:/program files (x86)/Arduino/hardware/teensy/avr/cores/teensy4")
elseif(CMAKE_HOST_APPLE)
  set(A2CM_TEENSY4_LIB_ROOT_DIR "/Applications/Teensyduino.app/Contents/Java/hardware/teensy/avr/cores/teensy4")
elseif(CMAKE_HOST_UNIX)
  message(FATAL_ERROR "Not implemented for Unix yet")
else()
  message(FATAL_ERROR "Unknown host machine")
endif()

# I guess I could make a static library, but OBJECT feels consistent...
add_library(
  teensy4_syslib
  STATIC
  ${TEENSY4_LIB_ROOT_DIR}/analog.c
  ${TEENSY4_LIB_ROOT_DIR}/bootdata.c
  ${TEENSY4_LIB_ROOT_DIR}/clockspeed.c
  ${TEENSY4_LIB_ROOT_DIR}/debugprintf.c
  ${TEENSY4_LIB_ROOT_DIR}/delay.c
  ${TEENSY4_LIB_ROOT_DIR}/digital.c
  ${TEENSY4_LIB_ROOT_DIR}/eeprom.c
  ${TEENSY4_LIB_ROOT_DIR}/extmem.c
  ${TEENSY4_LIB_ROOT_DIR}/fuse.c
  ${TEENSY4_LIB_ROOT_DIR}/interrupt.c
  ${TEENSY4_LIB_ROOT_DIR}/keylayouts.c
  ${TEENSY4_LIB_ROOT_DIR}/nonstd.c
  ${TEENSY4_LIB_ROOT_DIR}/pwm.c
  ${TEENSY4_LIB_ROOT_DIR}/rtc.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_alloc_valid.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_calloc.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_free.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_hash.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_malloc.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_malloc_stats.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_pool.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_realloc.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_realloc_i.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_realloc_move.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_szalloc.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_util.c
  ${TEENSY4_LIB_ROOT_DIR}/sm_zalloc.c
  ${TEENSY4_LIB_ROOT_DIR}/startup.c
  ${TEENSY4_LIB_ROOT_DIR}/tempmon.c
  ${TEENSY4_LIB_ROOT_DIR}/usb.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_desc.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_joystick.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_keyboard.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_midi.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_mouse.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_mtp.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_rawhid.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_seremu.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_serial.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_serial2.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_serial3.c
  ${TEENSY4_LIB_ROOT_DIR}/usb_touch.c
  ${TEENSY4_LIB_ROOT_DIR}/AudioStream.cpp
  ${TEENSY4_LIB_ROOT_DIR}/CrashReport.cpp
  ${TEENSY4_LIB_ROOT_DIR}/DMAChannel.cpp
  ${TEENSY4_LIB_ROOT_DIR}/EventResponder.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial1.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial2.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial3.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial4.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial5.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial6.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial7.cpp
  ${TEENSY4_LIB_ROOT_DIR}/HardwareSerial8.cpp
  ${TEENSY4_LIB_ROOT_DIR}/IntervalTimer.cpp
  ${TEENSY4_LIB_ROOT_DIR}/IPAddress.cpp
  ${TEENSY4_LIB_ROOT_DIR}/main.cpp
  ${TEENSY4_LIB_ROOT_DIR}/new.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Print.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent1.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent2.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent3.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent4.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent5.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent6.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent7.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEvent8.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEventUSB1.cpp
  ${TEENSY4_LIB_ROOT_DIR}/serialEventUSB2.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Stream.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Time.cpp
  ${TEENSY4_LIB_ROOT_DIR}/Tone.cpp
  ${TEENSY4_LIB_ROOT_DIR}/usb_audio.cpp
  ${TEENSY4_LIB_ROOT_DIR}/usb_flightsim.cpp
  ${TEENSY4_LIB_ROOT_DIR}/usb_inst.cpp
  ${TEENSY4_LIB_ROOT_DIR}/WMath.cpp
  ${TEENSY4_LIB_ROOT_DIR}/WString.cpp
  ${TEENSY4_LIB_ROOT_DIR}/yield.cpp
  ${TEENSY4_LIB_ROOT_DIR}/memcpy-armv7m.S
  ${TEENSY4_LIB_ROOT_DIR}/memset.S
)

#[[
BUILD_MCU=imxrt1062
BUILD_CORE=teensy4
BUILD_FLAGS_LIBS=-larm_cortexM7lfsp_math -lm -lstdc++
BUILD_FLAGS_S=-x assembler-with-cpp
BUILD_FLAGS_CPP=-std=gnu++17 -fno-exceptions -fpermissive -fno-rtti -fno-threadsafe-statics -felide-constructors -Wno-error=narrowing
BUILD_BOARD=TEENSY40
NAME=Teensy 4.0
BUILD_FLAGS_LD=-Wl,--gc-sections,--relax "-T${BUILD_CORE_PATH}/imxrt1062.ld"
COMPILER_ELF2HEX_FLAGS=-O ihex -R .eeprom
COMPILER_OBJCOPY_EEP_FLAGS=-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0
COMPILER_PATH=${RUNTIME_HARDWARE_PATH}/../tools/
REWRITING=disabled
VERSION=1.8.5
NAME=Teensyduino
]]
target_include_directories(
  teensy4_syslib
  PUBLIC
  ${TEENSY4_LIB_ROOT_DIR}
)
target_compile_definitions(
  teensy4_syslib
  PUBLIC
  __IMXRT1062__
  TEENSYDUINO=156
  ARDUINO=189
  ARDUINO_TEENSY40
  F_CPU=${A2CM_BUILD_FCPU}
  ${A2CM_BUILD_USBTYPE}
  LAYOUT_${A2CM_BUILD_KEYLAYOUT}
)
target_compile_options(
  teensy4_syslib
  PUBLIC
  -Os
  -g
  -Wall
  -ffunction-sections
  -fdata-sections
  -nostdlib
  -MMD
  -mthumb
  -mcpu=cortex-m7
  -mfloat-abi=hard
  -mfpu=fpv5-d16
  ${BUILD_FLAGS_C}
  ${BUILD_FLAGS_CPP}
  ${BUILD_FLAGS_S}
)
target_compile_features(teensy4_syslib PUBLIC cxx_std_14)
target_link_options(
  teensy4_syslib
  PUBLIC
  -mthumb
  -mcpu=cortex-m7
  -mfloat-abi=hard
  -mfpu=fpv5-d16
  -Wl,--gc-sections,--relax
  -fno-exceptions
  -fpermissive
  -fno-rtti
  -fno-threadsafe-statics
  -felide-constructors
  -Wno-error=narrowing
  "-T${A2CM_TEENSY4_LIB_ROOT_DIR}/imxrt1062.ld"
)
find_library(ARM_MATH_LIB arm_cortexM7lfsp_math "${A2CM_RUNTIME_PLATFORM_PATH}/../../tools/arm/arm-none-eabi/lib")
message(NOTICE "Location: ${ARM_MATH_LIB} (from ${A2CM_RUNTIME_PLATFORM_PATH}/../../tools/arm/arm-none-eabi/lib)")
target_link_libraries(
  teensy4_syslib
  PUBLIC
  ${ARM_MATH_LIB}
  m
  stdc++
)

#[[
ifeq (${UPLOAD_USE_1200BPS_TOUCH}, true)
  UPLOAD_EXTRA_FLAGS=--touch 1200
endif
ifeq (${UPLOAD_TOOL}, teensyloader)
  UPLOAD_PATTERN="${CMD_PATH}/teensy_post_compile" "-file=${BUILD_PROJECT_NAME}" "-path=$(abspath ${BUILD_PATH})" "-tools=${CMD_PATH}" "-board=${BUILD_BOARD}" -reboot "-port=${SERIAL_PORT}" "-portlabel=${SERIAL_PORT_LABEL}" "-portprotocol=${SERIAL_PORT_PROTOCOL}"
endif
]]

# Assembly:
# "${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_GCC}" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_S} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_S_EXTRA_FLAGS} "$<" -o "$@"

# C:
# "${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_GCC}" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_C} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_C_EXTRA_FLAGS} "$<" -o "$@"

# C++:
# "${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_G__}" -c ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_COMMON} ${BUILD_FLAGS_DEP} ${BUILD_FLAGS_CPP} ${BUILD_FLAGS_CPU} ${BUILD_FLAGS_DEFS} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DF_CPU=${BUILD_FCPU} -D${BUILD_USBTYPE} -DLAYOUT_${BUILD_KEYLAYOUT} "-I${BUILD_PATH}/pch" ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_CPP_EXTRA_FLAGS} "$<" -o "$@"

#[[ Linking:
${BUILD_PATH}/${BUILD_PROJECT_NAME}.elf : ${BUILD_PATH}/system.a ${USER_OBJS}
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_LINKER}" ${BUILD_FLAGS_OPTIMIZE} ${BUILD_FLAGS_LD} ${BUILD_FLAGS_LDSPECS} ${BUILD_FLAGS_CPU} ${COMPILER_ELF_EXTRA_FLAGS} -o "$@" ${USER_OBJS} "${BUILD_PATH}/system.a" "-L${BUILD_PATH}" ${BUILD_FLAGS_LIBS}

${BUILD_PATH}/${BUILD_PROJECT_NAME}.hex : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.elf
	"${COMPILER_PATH}${BUILD_TOOLCHAIN}${BUILD_COMMAND_OBJCOPY}" ${COMPILER_ELF2HEX_FLAGS} "$<" "$@"

${BUILD_PATH}/${BUILD_PROJECT_NAME}.flash : ${BUILD_PATH}/${BUILD_PROJECT_NAME}.hex
	${UPLOAD_PATTERN} ${UPLOAD_EXTRA_FLAGS}
]]