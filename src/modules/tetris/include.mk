IMG_MODULE_DIR=modules/tetris/

USER_INCLUDES += -I${IMG_MODULE_DIR}
# -I${IMG_MODULE_DIR}include
USER_CPP_SRCS += $(addprefix ${IMG_MODULE_DIR}, tetris.cpp)

VPATH += ${IMG_MODULE_DIR}
