# Target OS: Docs say to set this to "Generic" but I kinda want to call it "Arduino" ??
# Automatically sets CMAKE_CROSSCOMPILING to True (use that mostly, not this value?)
set(CMAKE_SYSTEM_NAME Generic)

# Docs say "anything I want" and is used to load a
# ${CMAKE_SYSTEM_NAME}-COMPILER_ID-${CMAKE_SYSTEM_PROCESSOR}.cmake file
# So I guess I could factor things nicely into pieces, enabling this set of stuff to be
# generated & installed in a global (or user-global) location, right?
set(CMAKE_SYSTEM_PROCESSOR Teensy40)

# You can use CMAKE_HOST_* (SYSTEM/SYSTEM_NAME/SYST EM_VERSION/SYSTEM_PROCESSOR/WIN32/UNIX/APPLE)
# for host dependent stuff in here if you want...
if(CMAKE_HOST_WIN32)
  message(NOTICE "Selecting Windows globally installed ARM EABI None toolchain")
  set(TOOLCHAIN_ROOT_LOCATION "c:/program files (x86)/Arm GNU Toolchain arm-none-eabi/11.2 2022.02/bin")
  set(HOST_EXE_SUFFIX .exe)
  set(A2CM_RUNTIME_PLATFORM_PATH "c:/program files (x86)/Arduino/hardware/teensy/avr")
elseif(CMAKE_HOST_APPLE)
  set(TOOLCHAIN_ROOT_LOCATION "$ENV{HOME}/Library/Arduino15/packages/adafruit/tools/arm-none-eabi-gcc/9-2019q4/bin")
  # This is wrong:
  set(A2CM_RUNTIME_PLATFORM_PATH "/Applications/Teensyduino.app/Contents/MacOS/Arduino/hardware/teensy/avr")
elseif(CMAKE_HOST_UNIX)
  # Definitely wrong currently
  set(TOOLCHAIN_ROOT_LOCATION "$ENV{HOME}/.arduino")
else()
  message(FATAL_ERROR "Unknown host platform: Sorry!")
endif()

set(CMAKE_ASM_COMPILER "${TOOLCHAIN_ROOT_LOCATION}/arm-none-eabi-gcc${HOST_EXE_SUFFIX}")
set(CMAKE_C_COMPILER "${TOOLCHAIN_ROOT_LOCATION}/arm-none-eabi-gcc${HOST_EXE_SUFFIX}")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT_LOCATION}/arm-none-eabi-g++${HOST_EXE_SUFFIX}")

# This prevents the compile test from trying to link
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
# KBF: I think this shouldn't be "NEVER" because a number of programs are host-only things
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# And now, the initial compiler flags to be used
set(A2CM_ASM_FLAGS
  -x assembler-with-cpp
)
string(JOIN " " CMAKE_ASM_FLAGS_INIT ${A2CM_ASM_FLAGS})
set(A2CM_CXX_FLAGS
  -fno-exceptions
  -fpermissive
  -fno-rtti
  -fno-threadsafe-statics
  -felide-constructors
  -Wno-error=narrowing
)
string(JOIN " " CMAKE_CXX_FLAGS_INIT ${A2CM_CXX_FLAGS})
set(A2CM_C_FLAGS
  -Wno-error=narrowing
)
string(JOIN " " CMAKE_C_FLAGS_INIT ${A2CM_C_FLAGS})
#set(A2CM_EXE_LINKER_FLAGS  
#  \"-T${A2CM_RUNTIME_PLATFORM_PATH}cores/teensy4/imxrt1062_mm.ld\"
#)
set(CMAKE_EXE_LINKER_FLAGS_INIT -Wl,--gc-sections,--relax)
