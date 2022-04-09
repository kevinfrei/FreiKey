#pragma once
#include <cmath>
#include <cstdint>

#if defined(STANDALONE)
#include <iostream>
#else
#include "Arduino.h"
#endif

namespace calc {

enum class ValType : uint8_t { Err, Int, Float, Text };

class CalcExpr {
  ValType type;
  union {
    double fVal;
    int64_t iVal;
    const char* txt;
  };

 public:
  CalcExpr(double d) : type(ValType::Float), fVal(d) {}
  CalcExpr(int64_t i) : type(ValType::Int), iVal(i) {}
  CalcExpr(int i) : type(ValType::Int), iVal(i) {}
  CalcExpr(uint64_t i) : type(ValType::Int), iVal(i) {}
  CalcExpr(int8_t i) : type(ValType::Int), iVal(i) {}
  CalcExpr(uint8_t i) : type(ValType::Int), iVal(i) {}
  CalcExpr(const char* e = nullptr) : type(ValType::Err), txt(e) {}
  CalcExpr(int, const char* text) : type(ValType::Text), txt(text) {}
  CalcExpr(const CalcExpr& ce) : type(ce.type) {
    switch (type) {
      case ValType::Int:
        iVal = ce.iVal;
        break;
      case ValType::Float:
        fVal = ce.fVal;
        break;
      default:
        txt = ce.txt;
        break;
    }
  }
  CalcExpr& self() {
    return *this;
  }
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
  CalcExpr operator-() const;
  CalcExpr operator+(const CalcExpr& v) const;
  CalcExpr operator-(const CalcExpr& v) const;
  CalcExpr operator*(const CalcExpr& v) const;
  CalcExpr operator/(const CalcExpr& v) const;
  CalcExpr operator%(const CalcExpr& v) const;
  CalcExpr operator&(const CalcExpr& v) const;
  CalcExpr operator|(const CalcExpr& v) const;
  CalcExpr operator~() const;
  CalcExpr factorial() const;
  CalcExpr power(const CalcExpr& v) const;
  CalcExpr getVal() const;
  CalcExpr invoke(const CalcExpr& v) const;
  void assignVal(const CalcExpr& v) const;
  void show() const;
#if defined(STANDALONE)
  friend std::ostream& operator<<(std::ostream&, const CalcExpr&);
#else
  void print(const char* header = nullptr) const;
  void println(const char* header = nullptr) const;
#endif
};

} // namespace calc

// This is the thing I use in Bison:
#define YYSTYPE calc::CalcExpr
#define YYSTYPE_IS_DECLARED
