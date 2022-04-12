EDIT_MODULE_DIR=modules/editline/

USER_INCLUDES += -I${EDIT_MODULE_DIR} -I${EDIT_MODULE_DIR}include
USER_CPP_SRCS += $(addprefix ${EDIT_MODULE_DIR}, editline.cpp)

VPATH += ${EDIT_MODULE_DIR}
