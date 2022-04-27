CALC_MODULE_DIR=modules/calculator/

CALC_PARSER_FILES=${CALC_MODULE_DIR}CalcParser.cpp ${CALC_MODULE_DIR}include/CalcParser.h

USER_CLEAN = ${USER_CLEAN} ${CALC_PARSER_FILES}

${CALC_PARSER_FILES}: ${CALC_MODULE_DIR}CalcGrammar.yy
	cd ${CALC_MODULE_DIR} && ${BISON} CalcGrammar.yy

# one minor dependency...
${CALC_MODULE_DIR}CalcLexer.cpp : ${CALC_MODULE_DIR}include/CalcParser.h

USER_INCLUDES += -Imodules/calculator -Imodules/calculator/include
USER_CPP_SRCS += $(addprefix ${CALC_MODULE_DIR}, CalcLexer.cpp CalcParser.cpp Calculator.cpp CalcExpr.cpp CalcContext.cpp CalcHandler.cpp)

VPATH += ${CALC_MODULE_DIR}
