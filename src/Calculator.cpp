#if defined(NATIVE)
#include <iostream>
#include <string>
#else
#include "Arduino.h"
#endif

#include "ValExpr.h"

#include "CalcParser.h"
#include "Calculator.h"

namespace calc {

double ValExpr::asFloat() const {
  switch (type) {
    case ValType::Float:
      return fVal;
    case ValType::Int:
      return static_cast<double>(iVal);
    default:
      return 0.0;
  }
}

int64_t ValExpr::asInt() const {
  switch (type) {
    case ValType::Float:
      return static_cast<double>(fVal);
    case ValType::Int:
      return iVal;
    default:
      return 0;
  }
}

const char* ValExpr::asError() const {
  return (type == ValType::Err) ? txt : "Not an error";
}

const char* ValExpr::asText() const {
  return (type == ValType::Text) ? txt : "Not a name";
}

ValExpr ValExpr::operator-() const {
  if (isError())
    return *this;
  return isFloat() ? ValExpr{-this->asFloat()} : ValExpr{-this->asInt()};
}

ValExpr ValExpr::operator+(const ValExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return ValExpr{this->asFloat() + v.asFloat()};
  }
  return ValExpr{this->asInt() + v.asInt()};
}

ValExpr ValExpr::operator-(const ValExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return ValExpr{this->asFloat() - v.asFloat()};
  }
  return ValExpr{this->asInt() - v.asInt()};
}

ValExpr ValExpr::operator*(const ValExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return ValExpr{this->asFloat() * v.asFloat()};
  }
  return ValExpr{this->asInt() * v.asInt()};
}

ValExpr ValExpr::operator/(const ValExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return ValExpr{this->asFloat() / v.asFloat()};
  }
  return ValExpr{this->asInt() / v.asInt()};
}

ValExpr ValExpr::operator%(const ValExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  if (isFloat() || v.isFloat()) {
    return ValExpr{fmod(this->asFloat(), v.asFloat())};
  }
  return ValExpr{this->asInt() % v.asInt()};
}

ValExpr ValExpr::factorial() const {
  if (isError())
    return *this;
  int64_t end = this->asInt();
  if (end < 0)
    return ValExpr{1};
  if (end > 20) {
    double val = 1;
    for (double i = 2.0; i <= end; i++) {
      val *= i;
    }
    return ValExpr{val};
  } else {
    int64_t val = 1;
    for (int64_t i = 2; i <= end; i++) {
      val *= i;
    }
    return ValExpr{val};
  }
}

ValExpr ValExpr::power(const ValExpr& v) const {
  if (isError())
    return *this;
  if (v.isError())
    return v;
  // TODO: Make this lookup the ValExpr for the variable of txt
  return ValExpr{pow(this->asFloat(), v.asFloat())};
}

ValExpr ValExpr::getVal() const {
  if (isError())
    return *this;
  // TODO: Make this lookup the ValExpr for the variable of txt
  return ValExpr{1.0};
}

void ValExpr::assignVal(const ValExpr& v) const {
  // TODO: Record the ValExpr in the variable mape
}

void ValExpr::show() const {
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
calc::Scanner* scan;

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
  calc::Scanner scanner{str};
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