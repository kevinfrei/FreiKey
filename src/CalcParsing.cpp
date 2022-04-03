#include <cctype>
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

bool parseNumbr(std::vector<Token>& result,
                const std::string& str,
                uint16_t& start,
                uint16_t& tcur) {
  uint16_t sz = str.size();

  // Get the expression we're sitting on
  // First, scan the numbers:
  while (isdigit(cur) && tcur < sz) {
    tcur++;
    cur = tolower(str[tcur]);
  }
  if (cur != '.' && cur != 'e') {
    // It's just a string of digits, not a float value
    result.push_back(Token{TokenID::IVal, start, tcur});
    start = tcur;
    return true;
  }
  // If we're here, we're parsing a floating point value
  bool seenDec = cur == '.';
  // Eat the rest of the numeric part:
  while (cur != 'e' && (isdigit(cur) || (!seenDec || cur == '.')) &&
         tcur < sz) {
    seenDec = cur == '.';
    tcur++;
    cur = tolower(str[tcur]);
  }
  if (cur != 'e') {
    // We got a string of \d*(.\d*)
    result.push_back(Token{TokenID::FVal, start, tcur});
    start = tcur++;
    return true;
  }
  // Now we're parsing an exponent
  tcur++;
  do {
    if (tcur == sz) {
      break; // Error
    }
    cur = str[tcur];
    // Consume the optional +/-
    if (cur == '-' || cur == '+') {
      tcur++;
      if (tcur == sz) {
        // Error
        break;
      }
      cur = str[tcur];
    }
    // The 'e' must be followed by at least one digit
    if (!isdigit(cur)) {
      // error
      break;
    }
    // Now scan until we have no more digits
    while (isdigit(cur) && tcur < sz) {
      cur = str[tcur];
      tcur++;
    }
    result.push_back(Token{TokenID::FVal, start, tcur});
    start = tcur++;
    return true;
  } while (false);
  result.push_back(Token{TokenID::Error, start, tcur});
  return false;
}

std::vector<Token> Tokenize(const std::string& str) {
  std::vector<Token> result;
  uint16_t start = 0;
  uint16_t tcur = 0;
  enum class TState { Digits, Float, Exp };
  if (str.size() > 0xffff) {
    result.push_back(Token{TokenID::Error, 0xffff, 0});
    return result;
  }
  while (tcur < str.size()) {
    char cur = str[tcur];
    char lcur = tolower(cur);
    if (isdigit(cur) || cur == '.') {
      if (!parseNumber(result, str, start, tcur)) {
        break;
      }
    } else {
      // Not a number
      switch(cur) {
        case '+':
          addToken(TokenID::Add, result, start, tcur);
          continue;
        case '-':
          addToken(TokenID::Sub, result, start, tcur);
          continue;
        case '*':
          addToken(TokenID::Mul, result, start, tcur);
          continue;
        case '/':
          addToken(TokenID::Div, result, start, tcur);
          continue;
        case '=':
          addToken(TokenID::Assign, result, start, tcur);
          continue;
        case '%':
          addToken(TokenID::Mod, result, start, tcur);
          continue;
        case '!':
          addToken(TokenID::Fact, result, start, tcur);
          continue;
        case '(':
          addToken(TokenID::OParen, result, start, tcur);
          continue;
        case ')':
          addToken(TokenID::CParen, result, start, tcur);
          continue;
        case '^':
          addToken(TokenID::Exp, result, start, tcur);
          continue;
        default:
          
      }
    }
  }
  return result;
}

Value Calculate(const std::string& str) {
  for (auto& token : Tokenize(str)) {
  }
}

int main(int argc, const char* argv[]) {}