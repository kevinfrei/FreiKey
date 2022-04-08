#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "CalcExpr.h"

#include "CalcParser.h"
#include "Calculator.h"


// Calculator lexical analysis states
enum class TState { NewToken, MaybeInt, String, Frac, StartExp, Exp };

// TODO: Make this stream, rather than full processing...
// TODO: Add hex/binary modes, plus logic operations

namespace calc {

uint16_t Lexer::addToken(yytoken_kind_t tk, uint16_t s, uint16_t e) {
  tokens.push_back(Token{tk, s, e});
  return e;
}

// Float: \d*.?\d+(e+/-\d+)?
void Lexer::Tokenize(const char* str) {
  tokens.clear();
  uint16_t start, end;
  TState state = TState::NewToken;
  // Paranoia...
  size_t sz = strlen(str);
  if (sz > 0xfffe) {
    tokens.push_back(Token{YYerror, 0xffff, 0});
    return;
  }
  /* States:
   *  NewToken:
   *    0 -> Numberish <<<<<<<<<<<<<<<< NYI
   *    [1-9] -> MaybeInt
   *    '.' -> Frac
   *    letters/_ -> String
   *    space -> skip
   *    operators, etc... -> MakeOper, NewToken
   *    Anything else -> Error
   *  Numberish: <<<<<<<<<< Begin NYI
   *    x -> MaybeHex
   *    b -> MaybeBin
   *    . -> Frac
   *    [0-9] -> MaybeInt
   *    Space -> MakeInt, NewToken
   *    operators -> MakeInt, MakeOper, NewToken
   *    Anything else -> Error
   *  MaybeHex:
   *    [0-9a-F] -> Hex
   *    Anything else -> Error
   *  Hex:
   *    [0-9a-F] -> Hex
   *    Space -> MakeHex, NewToken
   *    Operators -> MakeHex, MakeOper, NewToken
   *    Anything else -> Error
   *  MaybeBin:
   *    0/1 -> Bin
   *    Anything Else -> Error
   *  Bin:
   *    0/1 -> Bin
   *    Space -> MakeBin, NewToken
   *    Operators -> MakeBin, MakeOper, NewToken
   *    Anything else -> Error
   *  <<<<<<<<<< End NYI
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
            start = addToken(PLUS, start, end);
            continue;
          case '-':
            start = addToken(MINUS, start, end);
            continue;
          case '*':
            start = addToken(MULTIPLY, start, end);
            continue;
          case '/':
            start = addToken(DIVIDE, start, end);
            continue;
          case '=':
            start = addToken(ASSIGN, start, end);
            continue;
          case '%':
            start = addToken(MODULO, start, end);
            continue;
          case '!':
            start = addToken(FACTORIAL, start, end);
            continue;
          case '(':
            start = addToken(LPAREN, start, end);
            continue;
          case ')':
            start = addToken(RPAREN, start, end);
            continue;
          case '^':
            start = addToken(EXPONENT, start, end);
            continue;
          case '|': // Bitwise or
          case '&': // Bitwise and
          case '~': // Bitwise negate
            break;
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
        tokens.push_back(Token{YYerror, start, end});
        return;
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
        start = addToken(INT, start, --end);
        state = TState::NewToken;
        continue;
      case TState::Frac:
        if (isdigit(cur)) {
          continue;
        } else if (cur == 'e' || cur == 'E') {
          state = TState::StartExp;
          continue;
        }
        start = addToken(FLT, start, --end);
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
        tokens.push_back(Token{YYerror, start, end});
        return;
      case TState::Exp:
        if (isdigit(cur)) {
          continue;
        }
        start = addToken(INT, start, --end);
        state = TState::NewToken;
        continue;
      case TState::String:
        if (isalnum(cur) || cur == '_') {
          continue;
        }
        start = addToken(VAR, start, --end);
        state = TState::NewToken;
        continue;
    }
  }
  // Finish off the current token
  switch (state) {
    case TState::String:
      addToken(VAR, start, end);
      break;
    case TState::MaybeInt:
      addToken(INT, start, end);
      break;
    case TState::Frac:
    case TState::Exp:
      addToken(FLT, start, end);
      break;
    case TState::NewToken:
      break;
    default:
      addToken(YYerror, start, end);
      return;
  }
  addToken(EOL, end, end);
}

} // namespace calc
