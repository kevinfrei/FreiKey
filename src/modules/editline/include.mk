ifeq ($(OS),Windows_NT)
	BISON=win_bison
else ifeq ($(shell uname -s), Darwin)
	BISON=/opt/homebrew/opt/bison/bin/bison
else
  $(error No Linux support yet, but copying the Darwin stuff should be nearly all of the work)
endif

EDIT_MODULE_DIR=modules/editline/

USER_INCLUDES += -I${EDIT_MODULE_DIR} -I${EDIT_MODULE_DIR}include
USER_CPP_SRCS += $(addprefix ${EDIT_MODULE_DIR}, editline.cpp)

VPATH += ${EDIT_MODULE_DIR}
