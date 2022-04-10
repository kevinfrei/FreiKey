include ../standalone.mk

.PHONY: clean

DESTDIR = ../../out/edit/
IMAGE = ${DESTDIR}edit${SFX}

edit: out out/edit ${IMAGE}

out out/edit:
	-@mkdir $(call MKDIRPATH,${DESTDIR}) > ${devnull} 2>&1

${DESTDIR}%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -I. -Iinclude -I../../include -DSTANDALONE ${STDNUM} -c  $< ${OBJFLAG}$@

ED_SRC = editline.cpp

CPP_OBJS = $(addprefix ${DESTDIR}, $(patsubst %.cpp, %.${OSUFFIX}, ${ED_SRC}))

${IMAGE}: ${CPP_OBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^

clean: 
	-rm ${CPP_OBJS} ${IMAGE}

