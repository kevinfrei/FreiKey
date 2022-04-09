
#if defined(STANDALONE)
#include <iostream>
#else
#include "Arduino.h"
#endif

#include "CalcExpr.h"

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

CalcExpr CalcExpr::invoke(const CalcExpr& v) const {
// TODO: Lookup the function and invoke it
#if defined(STANDALONE)
  std::cout << "Invoking " << *this << " on " << v << std::endl;
#else
  this->print("Invoking ");
  v.println(" on ");
#endif
  return v;
}

void CalcExpr::assignVal(const CalcExpr& v) const {
  // TODO: Record the CalcExpr in the variable mape
#if defined(STANDALONE)
  std::cout << "Assigning " << v << " to " << *this << std::endl;
#else
  v.print("Assigning ");
  this->println(" to ");
#endif
}

#if defined(STANDALONE)

std::ostream& operator<<(std::ostream& o, const CalcExpr& e) {
  if (e.isInt()) {
    return o << e.asInt();
  }
  if (e.isFloat()) {
    return o << e.asFloat();
  }
  if (e.isText()) {
    return o << e.asText();
  }
  if (e.isError()) {
    return o << e.asError();
  }
  return o << "Unknown type for expression";
}

#else

void CalcExpr::print(const char* header) const {
  if (header) {
    Serial.print(header);
  }
  if (isInt()) {
    Serial.print(asInt());
  } else if (isFloat()) {
    Serial.print(asFloat());
  } else if (isText()) {
    Serial.print(asText());
  } else if (isError()) {
    Serial.print(asError());
  } else {
    Serial.print("Unknown CalcExpr type");
  }
}

void CalcExpr::println(const char* header) const {
  this->print(header);
  Serial.println();
}

#endif

void CalcExpr::show() const {
#if defined(STANDALONE)
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
