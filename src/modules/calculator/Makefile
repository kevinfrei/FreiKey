MODNAME = calculator
PARSE = CalcParser.cpp include/CalcParser.h
CPP_SRC = CalcParser.cpp CalcLexer.cpp Calculator.cpp CalcExpr.cpp CalcContext.cpp
MORE_CLEAN = ${PARSE}

include ../standalone.mk

${PARSE}: CalcGrammar.yy
	${BISON} $<