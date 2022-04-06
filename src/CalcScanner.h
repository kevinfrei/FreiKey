#pragma once
#ifndef YY_CALCSCANNER_H
#define YY_CALCSCANNER_H

#include "CalcParser.h"
#include "Calculator.h"

namespace calc {

class Scanner {
  std::vector<Token> tokens;
  const std::string& str;
  size_t cur;

 public:
  Scanner(const std::string& str) : str(str) {
    tokens = Tokenize(str);    
    cur = 0;
  }
  // This is the interface
  int lex(Parser::semantic_type* yylval) {
    // I still need to fill in the semantic_type
    auto& t = tokens[cur++];
    calc::Parser::token_kind_type tok = t.tok;
    switch (tok) {
      case calc::Parser::token::LPAREN: // LPAREN
      case calc::Parser::token::RPAREN: // RPAREN
      case calc::Parser::token::ASSIGN: // ASSIGN
      case calc::Parser::token::PLUS: // PLUS
      case calc::Parser::token::MINUS: // MINUS
      case calc::Parser::token::MULTIPLY: // MULTIPLY
      case calc::Parser::token::DIVIDE: // DIVIDE
      case calc::Parser::token::MODULO: // MODULO
      case calc::Parser::token::UMINUS: // UMINUS
      case calc::Parser::token::FACTORIAL: // FACTORIAL
      case calc::Parser::token::EXPONENT: // EXPONENT
        break;
      case calc::Parser::token::INT: // INT
        yylval->emplace<int64_t>(
          std::stoi(str.substr(t.start, t.end - t.start)));
        break;
      case calc::Parser::token::FLT: // FLT
        yylval->emplace<double>(
          std::stod(str.substr(t.start, t.end - t.start)));
        break;
      case calc::Parser::token::FLTVAR: // FLTVAR
      case calc::Parser::token::INTVAR: // INTVAR
        yylval->emplace<char>(str[t.start]);
        break;
      default:
        break;
    }
    return static_cast<int>(tok);
  }
};

} // namespace calc

#endif