MODNAME=image
IMG_SRC = imgencoder.cpp \
 img_cmdln.cpp \
 imgenc_rle.cpp \
 imgdec_rle.cpp \
 imgenc_pal.cpp \
 imgdec_pal.cpp \
 imgenc_prle.cpp \
 imgdec_prle.cpp
BMP_SRC = $(notdir $(wildcard bitmaps/*.cpp))
CPP_SRC = ${IMG_SRC} ${BMP_SRC}
VPATH += bitmaps

include ../standalone.mk
