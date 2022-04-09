#include <vector>

#include "CalcExpr.h"
#include "CalcParser.h"

// MSVC, LKG6, bad memories. Very. Bad. Memories.
#define _CRT_SECURE_NO_WARNINGS 1


namespace calc {

class Token {
 public:
  Token(yytoken_kind_t t, uint16_t s, uint16_t e) : tok(t), start(s), end(e) {}
  yytoken_kind_t tok;
  uint16_t start, end;
};

class Lexer {
  std::vector<Token> tokens;
  const char* str;
  size_t cur;
  uint16_t addToken(yytoken_kind_t tk, uint16_t s, uint16_t e);
  void Tokenize(const char* str);

 public:
  Lexer(const char* str) : str(str) {
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
        yylval = CalcExpr{atoll(buf)};
        delete[] buf;
        break;
      case FLT: // FLT
        buf = new char[t.end - t.start + 1];
        strncpy(buf, &str[t.start], t.end - t.start);
        buf[t.end - t.start] = 0;
        yylval = CalcExpr{atof(buf)};
        delete[] buf;
        break;
      case VAR: // VAR
        buf = new char[t.end - t.start + 1];
        strncpy(buf, &str[t.start], t.end - t.start);
        buf[t.end - t.start] = 0;
        yylval = CalcExpr{0, buf};
        break;
      default:
        break;
    }
    return static_cast<int>(tok);
  }
};

using CalcFunction = CalcExpr (*)(const CalcExpr&);

} // namespace calc