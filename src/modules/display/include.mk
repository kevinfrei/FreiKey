DISP_MODULE_DIR=modules/display/

USER_INCLUDES += -I${DISP_MODULE_DIR}
USER_CPP_SRCS += $(addprefix ${DISP_MODULE_DIR}, display.cpp)

VPATH += ${DISP_MODULE_DIR}
