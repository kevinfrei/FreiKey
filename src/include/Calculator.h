#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "CalcParser.h"

namespace calc {

class Token {
 public:
  Token(yytoken_kind_t t, uint16_t s, uint16_t e) : tok(t), start(s), end(e) {}
  yytoken_kind_t tok;
  uint16_t start, end;
};

class Scanner {
  std::vector<Token> tokens;
  const char* str;
  size_t cur;
  uint16_t addToken(yytoken_kind_t tk, uint16_t s, uint16_t e);
  void Tokenize(const char* str);

 public:
  Scanner(const char* str) : str(str) {
    Tokenize(str);
    cur = 0;
  }
  // This is the (very generic) bison/yacc interface
  int lex() {
    // I still need to fill in the semantic_type
    auto& t = tokens[cur++];
    yytokentype tok = t.tok;
    char* buf = nullptr;
    switch (tok) {
      case LPAREN: // LPAREN
      case RPAREN: // RPAREN
      case ASSIGN: // ASSIGN
      case PLUS: // PLUS
      case MINUS: // MINUS
      case MULTIPLY: // MULTIPLY
      case DIVIDE: // DIVIDE
      case MODULO: // MODULO
      case UMINUS: // UMINUS
      case FACTORIAL: // FACTORIAL
      case EXPONENT: // EXPONENT
        break;
      case INT: // INT
        buf = new char[t.end - t.start + 1];
        strncpy(buf, &str[t.start], t.end - t.start);
        buf[t.end - t.start] = 0;
        yylval.int_val = atoll(buf);
        delete[] buf;
        break;
      case FLT: // FLT
        buf = new char[t.end - t.start + 1];
        strncpy(buf, &str[t.start], t.end - t.start);
        buf[t.end - t.start] = 0;
        yylval.dbl_val = atof(buf);
        delete[] buf;
        break;
      case FLTVAR: // FLTVAR
      case INTVAR: // INTVAR
        yylval.str_val = str[t.start];
        break;
      default:
        break;
    }
    return static_cast<int>(tok);
  }
};

} // namespace calc
