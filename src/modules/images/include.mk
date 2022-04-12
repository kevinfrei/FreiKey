IMG_MODULE_DIR=modules/images/

USER_INCLUDES += -I${IMG_MODULE_DIR} -I${IMG_MODULE_DIR}include
USER_CPP_SRCS += $(addprefix ${IMG_MODULE_DIR}, image.cpp imgdec_pal.cpp imgdec_prle.cpp imgdec_rle.cpp)
USER_CPP_SRCS += $(wildcard ${IMG_MODULE_DIR}bitmaps/*.cpp)

VPATH += ${IMG_MODULE_DIR} ${IMG_MODULE_DIR}bitmaps/
