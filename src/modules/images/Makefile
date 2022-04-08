include ../standalone.mk

.PHONY: clean

DESTDIR = ../../out/img/
IMAGE = ${DESTDIR}image${SFX}

img: out out/img ${IMAGE}

out out/img:
	-mkdir $(call MKDIRPATH,${DESTDIR})

${DESTDIR}%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -I. -Iinclude -DSTANDALONE ${STDNUM} -c  $< ${OBJFLAG}$@

${DESTDIR}%.${OSUFFIX} : bitmaps/%.cpp
	${CXX} ${OPTFLAGS} -I. -Iinclude -DSTANDALONE ${STDNUM} -c  $< ${OBJFLAG}$@

IMG_SRC = imgencoder.cpp \
 img_cmdln.cpp \
 imgenc_rle.cpp \
 imgdec_rle.cpp \
 imgenc_pal.cpp \
 imgdec_pal.cpp \
 imgenc_prle.cpp \
 imgdec_prle.cpp

BMP_SRC = $(notdir $(wildcard bitmaps/*.cpp))
 
CPP_OBJS = $(addprefix ${DESTDIR}, $(patsubst %.cpp, %.${OSUFFIX}, ${IMG_SRC})) \
	$(addprefix ${DESTDIR}, $(patsubst %.cpp, %.${OSUFFIX}, ${BMP_SRC}))

${IMAGE}: ${CPP_OBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^

clean: 
	-rm ${CPP_OBJS} ${IMAGE}

