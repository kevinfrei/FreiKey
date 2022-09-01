set(CMKARD_BUILD_MCU imxrt1062)
set(CMKARD_BUILD_CORE teensy4)
add_compile_definitions(__IMXRT1062__ TEENSYDUINO=156)

set(CMKARD_BUILD_FLAGS_CPU -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16)
set(CMKARD_BUILD_FLAGS_OPTIMIZE -Os)
set(CMKARD_BUILD_FLAGS_COMMON -g -Wall -ffunction-sections -fdata-sections -nostdlib)
set(CMKARD_BUILD_BOARD TEENSY40)
set(CMKARD_NAME "Teensy 4.0")
set(CMKARD_BUILD_CORE_PATH ${CMKARD_RUNTIME_PLATFORM_PATH}/cores/${CMKARD_BUILD_CORE})
set(CMKARD_BUILD_FLAGS_LD -Wl,--gc-sections,--relax -T${CMKARD_BUILD_CORE_PATH}/imxrt1062.ld)
set(CMKARD_DISCOVERY_TEENSY_PATTERN ${CMKARD_RUNTIME_HARDWARE_PATH}/../tools/teensy_ports -J2)
set(CMKARD_COMPILER_ELF2HEX_FLAGS -O ihex -R .eeprom)
set(CMKARD_COMPILER_OBJCOPY_EEP_FLAGS -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0)
set(CMKARD_COMPILER_PATH ${CMKARD_RUNTIME_HARDWARE_PATH}/../tools/)
set(CMKARD_REWRITING disabled)
set(CMKARD_VERSION 1.8.5)
set(CMKARD_NAME Teensyduino)
if (CMKARD_UPLOAD_USE_1200BPS_TOUCH EQUAL true)
  set(CMKARD_UPLOAD_EXTRA_FLAGS "--touch 1200")
endif()
if (CMKARD_UPLOAD_TOOL EQUAL teensyloader)
  set(CMKARD_UPLOAD_PATTERN "${CMKARD_CMD_PATH}/teensy_post_compile -file=${CMKARD_BUILD_PROJECT_NAME} -path=$(abspath ${CMKARD_BUILD_PATH}) -tools=${CMKARD_CMD_PATH} -board=${CMKARD_BUILD_BOARD} -reboot -port=${CMKARD_SERIAL_PORT} -portlabel=${CMKARD_SERIAL_PORT_LABEL} -portprotocol=${CMKARD_SERIAL_PORT_PROTOCOL}")
endif()

add_compile_definitions(
  ARDUINO=${CMKARD_RUNTIME_IDE_VERSION}
  ARDUINO_${CMKARD_BUILD_BOARD}
  F_CPU=${CMKARD_BUILD_FCPU}
  ${CMKARD_BUILD_USBTYPE}
  LAYOUT_${CMKARD_BUILD_KEYLAYOUT}
)

# link_directories(AFTER  ${BUILD_CORE_PATH}/linker  ${RUNTIME_TOOLS_CMSIS_5_7_0_PATH}/CMSIS/DSP/Lib/GCC/)

# ${COMPILER_CPP_FLAGS}
# ${BUILD_FLAGS_NRF} ${SYS_INCLUDES}
# set(CMAKE_EXE_LINKER_FLAGS  "-Ofast -Wl,--gc-sections -save-temps -Tnrf52840_s140_v6.ld -Wl,-Map,ye-old-map-file.map ${COMPILER_LDFLAGS} -lm -Wl,--start-group ${COMPILER_ARM_CMSIS_LDFLAGS} -Wl,--end-group")

# "${BUILD_PATH}/system.a"
# ${COMPILER_LIBRARIES_LDFLAGS}
# -Wl,--end-group
