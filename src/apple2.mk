APPLE_MODULE_DIR = libs/apple2/
USER_INCLUDES += -I${APPLE_MODULE_DIR}inc
USER_CPP_SRCS += $(patsubst ${APPLE_MODULE_DIR}src/%,%,$(wildcard ${APPLE_MODULE_DIR}src/*.cpp))
VPATH += ${APPLE_MODULE_DIR}src
# By default, optimize the executable.
# CFLAGS := -Wall -flto -Os -ansi -c -std=c++11
# LFLAGS := -flto

# ifdef DEBUG
# CFLAGS := -O0 -ggdb -ansi -c -finstrument-functions -std=c++11 -Wno-write-strings -Werror
# endif
