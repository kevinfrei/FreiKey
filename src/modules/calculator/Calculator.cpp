#if defined(NATIVE)
#include <iostream>
#include <string>
#else
#include "Arduino.h"
#endif

#include "CalcExpr.h"

#include "CalcParser.h"
#include "Calculator.h"

namespace calc {

double CalcExpr::asFloat() const {
  switch (type) {
    case ValType::Float:
      return fVal;
    case ValType::Int:
      return static_cast<double>(iVal);
    default:
      return 0.0;
  }
}

int64_t CalcExpr::asInt() const {
  switch (type) {
    case ValType::Float:
      return static_cast<double>(fVal);
    case ValType::Int:
      return iVal;
    default:
      return 0;
  }
}

const char* CalcExpr::asError() const {
  return (type == ValType::Err) ? txt : "Not an error";
}

const char* CalcExpr::asText() const {
  return (type == ValType::Text) ? txt : "Not a name";
}

CalcExpr CalcExpr::operator-() const {
  if (isError())
    return *this;
  return isFloat() ? CalcExpr{-this->asFloat()} : CalcExpr{-this->asInt()};
}

CalcExpr CalcExpr::operator+(const CalcExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return CalcExpr{this->asFloat() + v.asFloat()};
  }
  return CalcExpr{this->asInt() + v.asInt()};
}

CalcExpr CalcExpr::operator-(const CalcExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return CalcExpr{this->asFloat() - v.asFloat()};
  }
  return CalcExpr{this->asInt() - v.asInt()};
}

CalcExpr CalcExpr::operator*(const CalcExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return CalcExpr{this->asFloat() * v.asFloat()};
  }
  return CalcExpr{this->asInt() * v.asInt()};
}

CalcExpr CalcExpr::operator/(const CalcExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return CalcExpr{this->asFloat() / v.asFloat()};
  }
  return CalcExpr{this->asInt() / v.asInt()};
}

CalcExpr CalcExpr::operator%(const CalcExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return CalcExpr{fmod(this->asFloat(), v.asFloat())};
  }
  return CalcExpr{this->asInt() % v.asInt()};
}

CalcExpr CalcExpr::factorial() const {
  if (isError())
    return *this;
  int64_t end = this->asInt();
  if (end < 0)
    return CalcExpr{1};
  if (end > 20) {
    double val = 1;
    for (double i = 2.0; i <= end; i++) {
      val *= i;
    }
    return CalcExpr{val};
  } else {
    int64_t val = 1;
    for (int64_t i = 2; i <= end; i++) {
      val *= i;
    }
    return CalcExpr{val};
  }
}

CalcExpr CalcExpr::power(const CalcExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  // TODO: Make this lookup the CalcExpr for the variable of txt
  return CalcExpr{pow(this->asFloat(), v.asFloat())};
}

CalcExpr CalcExpr::getVal() const {
  if (isError())
    return *this;
  // TODO: Make this lookup the CalcExpr for the variable of txt
  return CalcExpr{1.0};
}

void CalcExpr::assignVal(const CalcExpr& v) const {
  // TODO: Record the CalcExpr in the variable mape
}

void CalcExpr::show() const {
#if defined(NATIVE)
  switch (type) {
    case ValType::Int:
      std::cout << asInt() << "_i" << std::endl;
      return;
    case ValType::Float:
      std::cout << asFloat() << "_d" << std::endl;
      return;
    case ValType::Err:
      std::cout << txt << "__!__" << std::endl;
      return;
    case ValType::Text:
      std::cout << "'" << txt << "'" << std::endl;
  }
#else
  switch (type) {
    case ValType::Int:
      Serial.printf("%lld_i\n", asInt());
      return;
    case ValType::Float:
      Serial.printf("%f_d\n", asFloat());
      return;
    case ValType::Err:
      Serial.printf("%s__!__\n", txt);
      return;
    case ValType::Text:
      Serial.printf("'%s'\n", txt);
  }
#endif
}
} // namespace calc

// This stuff is all for the bison parser

const char* errors = nullptr;
calc::Lexer* scan;

int yyerror(const char* msg) {
#if defined(NATIVE)
  std::cerr << "Error:" << msg << std::endl;
#endif
  errors = msg;
  return 1;
}

int yylex() {
  return scan->lex();
}

void Parse(const char* str) {
  errors = nullptr;
  calc::Lexer scanner{str};
  scan = &scanner;
  yyparse();
  if (errors != nullptr) {
#if defined(NATIVE)
    std::cerr << errors << std::endl;
#else
    Serial.println(errors);
#endif
  }
}

#if defined(NATIVE)
int main(int argc, const char* argv[]) {
  std::string input;
  std::cout.precision(10);
  do {
    std::cout << "Enter some stuff:" << std::endl;
    std::getline(std::cin, input);
    std::cout << "'" << input << "'" << std::endl;
    Parse(input.c_str());
    std::cout << "====" << std::endl;
  } while (!input.empty());
  return 0;
}
#endif
