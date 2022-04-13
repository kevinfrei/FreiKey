include ../standalone.mk

.PHONY: clean

DESTDIR = ../../out/calc/
PARSE = CalcParser.cpp include/CalcParser.h
IMAGE = ${DESTDIR}calculator${SFX}

calc: out out/calc ${IMAGE}

${PARSE}: CalcGrammar.yy
	${BISON} $<

out out/calc:
	-@mkdir $(call MKDIRPATH,${DESTDIR}) > ${devnull} 2>&1

${DESTDIR}%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -I. -Iinclude -DSTANDALONE ${STDNUM} -c  $< ${OBJFLAG}$@

CPP_SRC = CalcParser.cpp CalcLexer.cpp Calculator.cpp CalcExpr.cpp CalcContext.cpp

CPP_OBJS = $(addprefix ../../out/calc/, $(patsubst %.cpp, %.${OSUFFIX}, ${CPP_SRC}))

${IMAGE}: ${CPP_OBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^

clean:
	-rm ${CPP_OBJS} ${PARSE} ${IMAGE}