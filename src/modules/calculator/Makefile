include ../standalone.mk

.PHONY: clean

DESTDIR = ../../out/calc/
CALCPARSE = CalcParser.cpp include/CalcParser.h
CALCIMAGE = ${DESTDIR}calculator${SFX}

calc: out out/calc ${CALCIMAGE}

${CALCPARSE}: CalcGrammar.yy
	${BISON} $<

out out/calc:
	-mkdir $(call MKDIRPATH,../../out/calc)

../../out/calc/%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -I. -Iinclude -DNATIVE ${STDNUM} -c  $< ${OBJFLAG}$@

CALCSRC = CalcParser.cpp CalcLexer.cpp Calculator.cpp

CALCOBJS = $(addprefix ../../out/calc/, $(patsubst %.cpp, %.${OSUFFIX}, ${CALCSRC}))

${CALCIMAGE}: ${CALCOBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^

clean: 
	-rm ${CALCOBJS} ${CALCPARSE} ${CALCIMAGE}