#include <stdint.h>
#include <vector>

#include "CalcParser.h"
#include "Calculator.h"
#include "enumtypes.h"

inline uint16_t addToken(calc::Parser::token_kind_type tk,
                         std::vector<Token>& res,
                         uint16_t s,
                         uint16_t e) {
  res.push_back(Token{tk, s, e});
  return e;
}

// Float: \d*.?\d+(e+/-\d+)?
std::vector<Token> Tokenize(const std::string& str) {
  std::vector<Token> res;
  uint16_t start, end;
  TState state = TState::NewToken;
  bool isFloat;
  // Paranoia...
  if (str.size() > 0xfffe) {
    res.push_back(Token{calc::Parser::token::YYerror, 0xffff, 0});
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
            start =
              addToken(calc::Parser::token::PLUS, res, start, end);
            continue;
          case '-':
            start =
              addToken(calc::Parser::token::MINUS, res, start, end);
            continue;
          case '*':
            start =
              addToken(calc::Parser::token::MULTIPLY, res, start, end);
            continue;
          case '/':
            start =
              addToken(calc::Parser::token::DIVIDE, res, start, end);
            continue;
          case '=':
            start =
              addToken(calc::Parser::token::ASSIGN, res, start, end);
            continue;
          case '%':
            start =
              addToken(calc::Parser::token::MODULO, res, start, end);
            continue;
          case '!':
            start =
              addToken(calc::Parser::token::FACTORIAL, res, start, end);
            continue;
          case '(':
            start =
              addToken(calc::Parser::token::LPAREN, res, start, end);
            continue;
          case ')':
            start =
              addToken(calc::Parser::token::RPAREN, res, start, end);
            continue;
          case '^':
            start =
              addToken(calc::Parser::token::EXPONENT, res, start, end);
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
        res.push_back(Token{calc::Parser::token::YYerror, start, end});
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
        start =
          addToken(calc::Parser::token::INT, res, start, --end);
        state = TState::NewToken;
        continue;
      case TState::Frac:
        if (isdigit(cur)) {
          continue;
        } else if (cur == 'e' || cur == 'E') {
          state = TState::StartExp;
          continue;
        }
        start = addToken(calc::Parser::token::FLT, res, start, --end);
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
        res.push_back(Token{calc::Parser::token::YYerror, start, end});
        return res;
      case TState::Exp:
        if (isdigit(cur)) {
          continue;
        }
        start = addToken(calc::Parser::token::FLT, res, start, --end);
        state = TState::NewToken;
        continue;
      case TState::String:
        if (isalnum(cur) || cur == '_') {
          continue;
        }
        isFloat = islower(str[start]);
        start = addToken(isFloat ? calc::Parser::token::FLTVAR
                                 : calc::Parser::token::INTVAR,
                         res,
                         start,
                         --end);
        state = TState::NewToken;
        continue;
    }
  }
  // Finish off the current token
  switch (state) {
    case TState::String:
      isFloat = islower(str[start]);
      addToken(isFloat ? calc::Parser::token::FLTVAR
                       : calc::Parser::token::INTVAR,
               res,
               start,
               end);
      break;
    case TState::MaybeInt:
      addToken(calc::Parser::token::INT, res, start, end);
      break;
    case TState::Frac:
    case TState::Exp:
      addToken(calc::Parser::token::FLT, res, start, end);
      break;
    case TState::NewToken:
      break;
    default:
      addToken(calc::Parser::token::YYerror, res, start, end);
      return res;
      break;
  }
  addToken(calc::Parser::token::EOL, res, end, end);
  return res;
}
