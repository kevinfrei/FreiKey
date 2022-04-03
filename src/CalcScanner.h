#pragma once
#ifndef YY_CALCSCANNER_H
#define YY_CALCSCANNER_H

#include "CalcParser.h"

namespace calc { // note: depends upon FlexLexer.h and CalcParser.h

class Scanner : public yyFlexLexer {
 public:
  Scanner(std::istream& arg_yyin, std::ostream& arg_yyout)
    : yyFlexLexer(arg_yyin, arg_yyout) {}
  Scanner(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr)
    : yyFlexLexer(arg_yyin, arg_yyout) {}
  int lex(Parser::semantic_type* yylval); // note: this is the prototype we need
};

} // namespace calc

#endif