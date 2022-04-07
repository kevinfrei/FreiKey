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
  bool isInt() const {
    return type == ValType::Int;
  }
  bool isError() const {
    return type == ValType::Err;
  }
  bool isFloat() const {
    return type == ValType::Float;
  }
  bool isText() const {
    return type == ValType::Text;
  }
  double asFloat() const;
  int64_t asInt() const;
  const char* asError() const;
  const char* asText() const;
  ValExpr operator-() const;
  ValExpr operator+(const ValExpr& v) const;
  ValExpr operator-(const ValExpr& v) const;
  ValExpr operator*(const ValExpr& v) const;
  ValExpr operator/(const ValExpr& v) const;
  ValExpr operator%(const ValExpr& v) const;
  ValExpr factorial() const;
  ValExpr power(const ValExpr& v) const;
  ValExpr getVal() const;
  void assignVal(const ValExpr& v) const;
  void show() const;
};

} // namespace calc

#if !defined(YYSTYLE)
#define YYSTYPE MyYYSType
#define YYSTYPE_IS_DECLARED
struct MyYYSType {
  calc::ValExpr val;
};
#endif