TETRIS_MODULE_DIR=modules/tetris/

USER_INCLUDES += -I${TETRIS_MODULE_DIR}
USER_CPP_SRCS += $(addprefix ${TETRIS_MODULE_DIR}, tetris.cpp board.cpp disp_stuff.cpp)

VPATH += ${TETRIS_MODULE_DIR}
