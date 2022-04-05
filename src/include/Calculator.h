#pragma once

#include "enumtypes.h"
#include <stdint.h>
#include <string>
#include <vector>

class Token {
 public:
  Token(TokenID t, uint16_t s, uint16_t e) : tok(t), start(s), end(e) {}
  TokenID tok;
  uint16_t start, end;
};

std::vector<Token> Tokenize(const std::string& str);