#pragma once
#include <cmath>
#include <cstdint>

#if defined(NATIVE)
#include <iostream>
#else
#include "Arduino.h"
#endif

namespace calc {

enum class ValType : uint8_t { Err, Int, Float, Text };

class ValExpr {
  ValType type;
  union {
    double fVal;
    int64_t iVal;
    const char* txt;
  };

 public:
  ValExpr(double d) : type(ValType::Float), fVal(d) {}
  ValExpr(int64_t i) : type(ValType::Int), iVal(i) {}
  ValExpr(int i) : type(ValType::Int), iVal(i) {}
  ValExpr(uint64_t i) : type(ValType::Int), iVal(i) {}
  ValExpr(int8_t i) : type(ValType::Int), iVal(i) {}
  ValExpr(uint8_t i) : type(ValType::Int), iVal(i) {}
  ValExpr(const char* e = nullptr) : type(ValType::Err), txt(e) {}
  ValExpr(int, const char* text) : type(ValType::Text), txt(text) {}

  bool isError() const {
    return type == ValType::Err;
  }

  bool isFloat() const {
    return type == ValType::Float;
  }

  double asFloat() const {
    switch (type) {
      case ValType::Float:
        return fVal;
      case ValType::Int:
        return static_cast<double>(iVal);
      default:
        return 0.0;
    }
  }

  int64_t asInt() const {
    switch (type) {
      case ValType::Float:
        return static_cast<double>(fVal);
      case ValType::Int:
        return iVal;
      default:
        return 0;
    }
  }

  const char* asError() const {
    return (type == ValType::Err) ? txt : "Not an error";
  }

  ValExpr operator-() const {
    if (isError())
      return *this;
    return isFloat() ? ValExpr{-this->asFloat()} : ValExpr{-this->asInt()};
  }

  ValExpr operator+(const ValExpr& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFloat() || v.isFloat()) {
      return ValExpr{this->asFloat() + v.asFloat()};
    }
    return ValExpr{this->asInt() + v.asInt()};
  }

  ValExpr operator-(const ValExpr& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFloat() || v.isFloat()) {
      return ValExpr{this->asFloat() - v.asFloat()};
    }
    return ValExpr{this->asInt() - v.asInt()};
  }

  ValExpr operator*(const ValExpr& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFloat() || v.isFloat()) {
      return ValExpr{this->asFloat() * v.asFloat()};
    }
    return ValExpr{this->asInt() * v.asInt()};
  }

  ValExpr operator/(const ValExpr& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFloat() || v.isFloat()) {
      return ValExpr{this->asFloat() / v.asFloat()};
    }
    return ValExpr{this->asInt() / v.asInt()};
  }

  ValExpr operator%(const ValExpr& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    if (isFloat() || v.isFloat()) {
      return ValExpr{fmod(this->asFloat(), v.asFloat())};
    }
    return ValExpr{this->asInt() % v.asInt()};
  }

  ValExpr factorial() const {
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

  ValExpr power(const ValExpr& v) const {
    if (isError())
      return *this;
    if (v.isError())
      return v;
    // TODO: Make this lookup the ValExpr for the variable of txt
    return ValExpr{pow(this->asFloat(), v.asFloat())};
  }

  ValExpr getVal() const {
    if (isError())
      return *this;
    // TODO: Make this lookup the ValExpr for the variable of txt
    return ValExpr{1.0};
  }

  void assignVal(const ValExpr& v) const {
    // TODO: Record the ValExpr in the variable mape
  }

  void show() const {
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
};

} // namespace calc

#if !defined(YYSTYLE)
#define YYSTYPE MyYYSType
#define YYSTYPE_IS_DECLARED
struct MyYYSType {
  calc::ValExpr val;
};
#endif