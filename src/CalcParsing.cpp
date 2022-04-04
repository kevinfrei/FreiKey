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
  FVal,
  String,
  Eof,
  Error
};

class Token {
 public:
  Token(TokenID t, uint16_t s, uint16_t e) : tok(t), start(s), end(e) {}
  TokenID tok;
  uint16_t start, end;
};

enum class TState { NewToken, MaybeInt, String, Frac, StartExp, Exp };

inline uint16_t addToken(TokenID tk,
                         std::vector<Token>& res,
                         uint16_t s,
                         uint16_t e) {
  res.push_back(Token{tk, s, e});
  return e;
}

std::vector<Token> Tokenize(const std::string& str) {
  std::vector<Token> res;
  uint16_t start, end;
  TState state = TState::NewToken;

  // Paranoia...
  if (str.size() > 0xfffe) {
    res.push_back(Token{TokenID::Error, 0xffff, 0});
    return res;
  }
  uint16_t sz = str.size();
  /* States:
   *  NewToken:
   *    digits -> MaybeInt
   *    '.' -> Frac
   *    letters/_ -> String
   *    space -> skip
   *    operators, etc... -> MakeOper, NewToken
   *    Anything else -> Error
   *  MaybeInt:
   *    digits -> MaybeInt
   *    e -> StartExp
   *    . -> Frac
   *    Anything else -> MakeInt, NewToken
   *  Frac:
   *    digits -> Frac
   *    e -> StartExp
   *    Anything else -> MakeFloat, NewToken
   *  StartExp:
   *    +/- -> Exp
   *    Digits -> Exp(back up)
   *    Anything else -> Error
   *  Exp:
   *    digits -> Exp
   *    Anything else -> MakeFloat, NewToken
   *  String:
   *    letters/numbers/_ -> String
   *    Anything else -> MakeString, NewToken
   */
  for (start = 0, end = 1; end <= sz; end++) {
    char cur = str[end - 1];
    switch (state) {
      case TState::NewToken:
        // Look at start to see what new token to start:
        switch (cur) {
          case '+':
            start = addToken(TokenID::Add, res, start, end);
            continue;
          case '-':
            start = addToken(TokenID::Sub, res, start, end);
            continue;
          case '*':
            start = addToken(TokenID::Mul, res, start, end);
            continue;
          case '/':
            start = addToken(TokenID::Div, res, start, end);
            continue;
          case '=':
            start = addToken(TokenID::Assign, res, start, end);
            continue;
          case '%':
            start = addToken(TokenID::Mod, res, start, end);
            continue;
          case '!':
            start = addToken(TokenID::Fact, res, start, end);
            continue;
          case '(':
            start = addToken(TokenID::OParen, res, start, end);
            continue;
          case ')':
            start = addToken(TokenID::CParen, res, start, end);
            continue;
          case '^':
            start = addToken(TokenID::Exp, res, start, end);
            continue;
          case '.':
            state = TState::Frac;
            continue;
          case ' ':
            // Just skip spaces
            start++;
            continue;
          default:
            break;
        }
        // Okay, let's see what state to switch to, yeah?
        if (isdigit(cur)) {
          state = TState::MaybeInt;
          continue;
        } else if (isalpha(cur)) {
          state = TState::String;
          continue;
        }
        res.push_back(Token{TokenID::Error, start, end});
        return res;
      case TState::MaybeInt:
        if (isdigit(cur)) {
          continue;
        } else if (cur == 'e' || cur == 'E') {
          state = TState::StartExp;
          continue;
        } else if (cur == '.') {
          state = TState::Frac;
          continue;
        }
        start = addToken(TokenID::IVal, res, start, --end);
        state = TState::NewToken;
        continue;
      case TState::Frac:
        if (isdigit(cur)) {
          continue;
        } else if (cur == 'e' || cur == 'E') {
          state = TState::StartExp;
          continue;
        }
        start = addToken(TokenID::FVal, res, start, --end);
        state = TState::NewToken;
        continue;
      case TState::StartExp:
        if (cur == '+' || cur == '-') {
          state = TState::Exp;
          continue;
        }
        if (isdigit(cur)) {
          end--;
          state = TState::Exp;
          continue;
        }
        res.push_back(Token{TokenID::Error, start, end});
        return res;
      case TState::Exp:
        if (isdigit(cur)) {
          continue;
        }
        start = addToken(TokenID::FVal, res, start, --end);
        state = TState::NewToken;
        continue;
      case TState::String:
        if (isalnum(cur) || cur == '_') {
          continue;
        }
        start = addToken(TokenID::String, res, start, --end);
        state = TState::NewToken;
        continue;
    }
  }
  // Finish off the current token
  switch (state) {
    case TState::String:
      addToken(TokenID::String, res, start, end);
      break;
    case TState::MaybeInt:
      addToken(TokenID::IVal, res, start, end);
      break;
    case TState::Frac:
    case TState::Exp:
      addToken(TokenID::FVal, res, start, end);
      break;
    case TState::NewToken:
      break;
    default:
      addToken(TokenID::Error, res, start, end);
      return res;
      break;
  }
  addToken(TokenID::Eof, res, end, end);
  return res;
}

#if defined(TEST_TOKENIZATION)
void Calculate(const std::string& str) {
  for (auto& token : Tokenize(str)) {
    switch (token.tok) {
      case TokenID::Add:
        std::cout << "Add: ";
        break;
      case TokenID::Sub:
        std::cout << "Sub: ";
        break;
      case TokenID::Mul:
        std::cout << "Mul: ";
        break;
      case TokenID::Div:
        std::cout << "Div: ";
        break;
      case TokenID::Mod:
        std::cout << "Mod: ";
        break;
      case TokenID::Exp:
        std::cout << "Exp: ";
        break;
      case TokenID::Fact:
        std::cout << "Fact: ";
        break;
      case TokenID::OParen:
        std::cout << "OParen: ";
        break;
      case TokenID::CParen:
        std::cout << "CParen: ";
        break;
      case TokenID::Assign:
        std::cout << "Assign: ";
        break;
      case TokenID::IVal:
        std::cout << "IVal: ";
        break;
      case TokenID::FVal:
        std::cout << "FVal: ";
        break;
      case TokenID::String:
        std::cout << "String: ";
        break;
      case TokenID::Error:
        if (token.start > token.end)
          std::cout << "Narsty Error!" << std::endl;
        else
          std::cout << "Error: ";
        break;
      case TokenID::Eof:
        std::cout << "EOF" << std::endl;
        continue;
    }
    std::cout << str.substr(token.start, token.end - token.start) << std::endl;
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
#endif