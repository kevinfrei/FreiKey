#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

#include "Calculator.h"
#include "enumtypes.h"

class CalcValue {
  bool isFlt;
  double fVal;
  int64_t iVal;
  const char* err;

 public:
  CalcValue(double d) : isFlt(true), fVal(d), iVal(0), err(nullptr) {}
  CalcValue(int64_t i) : isFlt(false), fVal(0.0), iVal(i), err(nullptr) {}
  CalcValue(int i) : isFlt(false), fVal(0.0), iVal(i), err(nullptr) {}
  CalcValue(uint64_t i) : isFlt(false), fVal(0.0), iVal(i), err(nullptr) {}
  CalcValue(int8_t i) : isFlt(false), fVal(0.0), iVal(i), err(nullptr) {}
  CalcValue(uint8_t i) : isFlt(false), fVal(0.0), iVal(i), err(nullptr) {}
  CalcValue(const char* e = nullptr)
    : isFlt(true), fVal(0), iVal(-1LL), err(e) {}
  bool isError() const {
    return isFlt && (iVal == -1LL || err != nullptr);
  }
  double asDouble() const {
    return isFlt ? fVal : static_cast<double>(iVal);
  }
  int64_t asInt() const {
    return isFlt ? static_cast<double>(fVal) : iVal;
  }
  bool isFloat() const {
    return isFlt;
  }
  const char* message() const {
    return err;
  }
  CalcValue operator-() const {
    if (isError())
      return *this;
    return isFlt ? CalcValue{-fVal} : CalcValue{-iVal};
  }
  CalcValue operator+(const CalcValue& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFlt || v.isFlt) {
      return CalcValue{this->asDouble() + v.asDouble()};
    }
    return CalcValue{this->asInt() + v.asInt()};
  }
  CalcValue operator-(const CalcValue& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFlt || v.isFlt) {
      return CalcValue{this->asDouble() - v.asDouble()};
    }
    return CalcValue{this->asInt() - v.asInt()};
  }
};

using CalcFunction = std::function<CalcValue(CalcValue)>;

/*
 * A little recursive-descent parser
 *
 * The Grammar it all it's EBNF-ish glory:
 *
 * line := expr EOF | assign EOF
 * expr := prod | expr ADD prod | expr SUB prod
 * prod := val | val MUL prod | val DIV prod | val MOD prod
 * numish := NUM | func | VAR | OPAREN expr CPAREN | MINUS numish | numish EXP
 * numish | numish FACT func := VAR OPAREN expr CPAREN assign := VAR EQU expr
 *
 */
class CalculatorState {
  // Do something goofy with pi, i, and e, probably.
  // Everything is lowercase, cuz...
  std::map<std::string, CalcValue> vars;
  std::map<std::string, CalcFunction> funcs;

  const std::string* buffer;
  std::vector<Token> tokens;
  size_t cur;

  std::string getStr(const Token& t) {
    return buffer->substr(t.start, t.end - t.start);
  }

  const Token& token() const {
    return tokens[cur];
  }

  const Token& peek() const {
    return tokens[cur + 1];
  }

  bool next() {
    if (cur >= tokens.size()) {
      return false;
    }
    cur++;
    return true;
  }

  bool back() {
    if (cur == 0) {
      return false;
    }
    cur--;
    return true;
  }

  CalcValue toIval(const Token& t) {
    if (t.tok == TokenID::IVal) {
      return CalcValue{std::stoll(getStr(t))};
    } else if (t.tok == TokenID::FVal) {
      return CalcValue{static_cast<int64_t>(std::stod(getStr(t)))};
    }
    return CalcValue{"Invalid Integer Value"};
  }

  CalcValue toFval(const Token& t) {
    if (t.tok == TokenID::IVal) {
      return CalcValue{static_cast<double>(std::stoll(getStr(t)))};
    } else if (t.tok == TokenID::FVal) {
      return CalcValue{std::stod(getStr(t))};
    }
    return CalcValue{"Invalid Float Value"};
  }

  CalcValue Prod(CalcValue running, TokenID op = TokenID::Mul) {
    CalcValue err;
    // Prod:
    //    Numish */% Prod
    //  | Numish */% Numish
    
    return err;
  }

  CalcValue Sum(CalcValue running, bool add = true) {
    CalcValue v;
    // Sum:
    //   Numish + Sum
    // | Numish - Sum
    // | Numish + Numish
    // | Numish - Numish
    size_t save1 = cur;
    CalcValue v1 = Numish();
    if (!v1.isError() &&
        (token().tok == TokenID::Add || token().tok == TokenID::Sub)) {
      TokenID t = token().tok;
      next();
      size_t save2 = cur;
      v1 = add ? (running + v1) : (running - v1);
      CalcValue v2 = Sum(v1, t == TokenID::Add);
      if (!v2.isError()) {
        return v2;
      }
      cur = save2;
      v2 = Numish();
      if (!v2.isError()) {
        return (t == TokenID::Add) ? (v1 + v2) : (v1 - v2);
      }
    }
    cur = save1;
    return v;
  }

  CalcValue Numish() {
    CalcValue v;
    // Numish:
    //   IVal/FVal
    // | - Numish
    // | ( Numish )
    if (token().tok == TokenID::IVal) {
      v = toIval(token());
      next();
    } else if (token().tok == TokenID::FVal) {
      v = toFval(token());
      next();
    } else if (token().tok == TokenID::Sub) {
      next();
      v = Numish();
      if (v.isError())
        back();
      else
        v = -v;
    } else if (token().tok == TokenID::OParen) {
      size_t save = cur;
      next();
      v = Numish();
      if (!v.isError() && token().tok == TokenID::CParen) {
        next();
        return v;
      } else {
        v = CalcValue{"Unbalanced Parentheses"};
      }
      cur = save;
    }
    return v;
  }

  CalcValue Line() {
    CalcValue v;
    // Line:
    //   Sum
    // | Numish
    cur = 0;
    v = Sum(CalcValue{0});
    if (v.isError()) {
      cur = 0;
      v = Numish();
    }
    if (!v.isError()) {
      if (token().tok != TokenID::Eof) {
        v = CalcValue{"Extra Stuff"};
      } else {
        if (tokens.size() == 1) {
          v = CalcValue{"Empty!"};
        }
      }
    }
    return v;
  }

 public:
  // Maybe, when CalcValue isn't just an int or double, set FP precision for
  // transcendentals?
  CalculatorState() {
    // Eventually in C++20: std::numbers::pi
    vars["pi"] = CalcValue{3.14159265358979323846};
    // Eventually, std::numbers::e
    vars["e"] = CalcValue{2.71828182845904523536};
    // Nothing in functions just yet...
  }
  CalcValue Parse(const std::string& str) {
    buffer = &str;
    tokens = Tokenize(str);
    CalcValue cv = Line();
    return cv;
  }
};

#if defined(CALC_TEST)
int main(int argc, const char* argv[]) {
  std::string input;
  CalculatorState state;
  do {
    std::cout << "Enter some stuff:" << std::endl;
    std::getline(std::cin, input);
    std::cout << "'" << input << "'" << std::endl;
    CalcValue cv = state.Parse(input);
    if (cv.isError()) {
      std::cout << (cv.message() ? cv.message() : "Unknown error") << std::endl;
    } else if (cv.isFloat()) {
      std::cout << cv.asDouble() << std::endl;
    } else {
      std::cout << cv.asInt() << std::endl;
    }
    std::cout << "====" << std::endl;
  } while (!input.empty());
  return 0;
}
#endif

#if defined(CALC_TEST_TOKENS)
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

/*
 * Silly stuff for much later:
 * The Nilakantha series converges on pi quicker than Leibniz:
 * π = 3 + 4/(2*3*4) - 4/(4*5*6) + 4/(6*7*8) - 4/(8*9*10) + 4/(10*11*12)...
 * Slightly simplified:
 * π = 3 + 1/(1*3*2) - 1/(2*5*3) + 1/(3*7*4) - 1/(4*9*5) + 1/(5*11*6)...
 */