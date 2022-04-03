#include <cctype>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

enum class TokenID {
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Exp,
  Fact,
  OParen,
  CParen,
  Assign,
  IVal,
  IVar,
  FVal,
  FVar,
  Eof,
  Error
};

class Token {
 public:
  Token(TokenID t, uint16_t s, uint16_t e) : tok(t), start(s), end(e) {}
  TokenID tok;
  uint16_t start, end;
};

bool parseNumber(std::vector<Token>& result,
                 const std::string& str,
                 uint16_t& start,
                 uint16_t& end) {
  uint16_t sz = str.size();
  char cur = str[end - 1];
  // Get the expression we're sitting on
  // First, scan the numbers:
  while (isdigit(cur) && end < sz) {
    cur = tolower(str[end++]);
  }
  if (cur != '.' && cur != 'e') {
    // It's just a string of digits, not a float value
    result.push_back(Token{TokenID::IVal, start, end});
    start = end++;
    return true;
  }
  // If we're here, we're parsing a floating point value
  bool seenDec = cur == '.';
  // Eat the rest of the numeric part:
  while (cur != 'e' && (isdigit(cur) || (!seenDec || cur == '.')) && end < sz) {
    seenDec = cur == '.';
    cur = tolower(str[end++]);
  }
  if (cur != 'e') {
    // We got a string of \d*(.\d*)
    result.push_back(Token{TokenID::FVal, start, end});
    start = end++;
    return true;
  }
  // Now we're parsing an exponent
  end++;
  do {
    if (end == sz) {
      break; // Error
    }
    cur = str[end - 1];
    // Consume the optional +/-
    if (cur == '-' || cur == '+') {
      cur = str[end++];
      if (end == sz) {
        // Error
        break;
      }
    }
    // The 'e' must be followed by at least one digit
    if (!isdigit(cur)) {
      // error
      break;
    }
    // Now scan until we have no more digits
    while (isdigit(cur) && end < sz) {
      cur = str[end++];
    }
    result.push_back(Token{TokenID::FVal, start, end});
    start = end++;
    return true;
  } while (false);
  result.push_back(Token{TokenID::Error, start, end});
  return false;
}

inline void addToken(TokenID tk, std::vector<Token>& res, uint16_t s, uint16_t e) {
  res.push_back(Token{tk, s++, e++});
};

std::vector<Token> Tokenize(const std::string& str) {
  std::vector<Token> result;
  uint16_t start = 0;
  uint16_t end = 1;
  enum class TState { Digits, Float, Exp };
  if (str.size() > 0xffff) {
    result.push_back(Token{TokenID::Error, 0xffff, 0});
    return result;
  }
  uint16_t sz = str.size();
  while (end <= sz) {
    char cur = str[end - 1];
    char lcur = tolower(cur);
    if (isdigit(cur) || cur == '.') {
      if (!parseNumber(result, str, start, end)) {
        break;
      }
      start = end;
    } else {
      // Not a number
      switch (cur) {
        case '+':
          addToken(TokenID::Add, result, start, end);
          continue;
        case '-':
          addToken(TokenID::Sub, result, start, end);
          continue;
        case '*':
          addToken(TokenID::Mul, result, start, end);
          continue;
        case '/':
          addToken(TokenID::Div, result, start, end);
          continue;
        case '=':
          addToken(TokenID::Assign, result, start, end);
          continue;
        case '%':
          addToken(TokenID::Mod, result, start, end);
          continue;
        case '!':
          addToken(TokenID::Fact, result, start, end);
          continue;
        case '(':
          addToken(TokenID::OParen, result, start, end);
          continue;
        case ')':
          addToken(TokenID::CParen, result, start, end);
          continue;
        case '^':
          addToken(TokenID::Exp, result, start, end);
          continue;
        default:
          break;
      }
      // Maybe a variable, then yeah?
    }
  }
  return result;
}

void Calculate(const std::string& str) {
  for (auto& token : Tokenize(str)) {
    std::cout << str.substr(token.start, token.end) << std::endl;
  }
}

int main(int argc, const char* argv[]) {
  std::string input;
  do {
    std::cout << "Enter some stuff:" << std::endl;
    std::getline(std::cin, input);
    std::cout << "'" << input << "'" << std::endl;
    Calculate(input);
    std::cout << "====" << std::endl;
  } while (!input.empty());
  return 0;
}