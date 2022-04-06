#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "CalcParser.h"

class Token {
 public:
  Token(calc::Parser::token_kind_type t, uint16_t s, uint16_t e) : tok(t), start(s), end(e) {}
  calc::Parser::token_kind_type tok;
  uint16_t start, end;
};

std::vector<Token> Tokenize(const std::string& str);