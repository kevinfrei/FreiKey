
#if defined(STANDALONE)
#include <iostream>
#else
#include "Arduino.h"
#endif

#include "CalcContext.h"
#include "CalcExpr.h"

namespace calc {

char showBuffer[128] = {0};

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
  // TODO: Make this work properly for integers
  return CalcExpr{pow(this->asFloat(), v.asFloat())};
}

CalcExpr CalcExpr::getVal() const {
  if (isError() || !isText())
    return *this;
  return context.getVal(asText(), CalcExpr{"Undefined"});
}

CalcExpr CalcExpr::invoke(const CalcExpr& v) const {
  if (isError() || !isText())
    return *this;
  return context.invoke(asText(), v);
}

void CalcExpr::assignVal(const CalcExpr& v) const {
  if (isError() || !isText()) {
    return;
  }
  context.assign(asText(), v);
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
    case ValType::Int: {
      // Arduino doesn't support int64 dumping. Bring on the interview question:
      int64_t val = asInt();
      bool neg = (val < 0);
      uint8_t pos = 0;
      if (neg) {
        showBuffer[pos++] = '-';
        val = -val;
      }
      do {
        showBuffer[pos++] = val % 10 + '0';
        val /= 10;
      } while (val != 0);
      showBuffer[pos] = 0;
      // Now reverse the whole thing
      uint8_t start = neg ? 1 : 0;
      for (pos--; pos > start; pos--, start++) {
        char sb = showBuffer[start];
        showBuffer[start] = showBuffer[pos];
        showBuffer[pos] = sb;
      };
      return;
    }
    case ValType::Float:
      // Wow, this is *really* bad. I should just make CalcExpr's be an actual
      // data type
      dtostrf(asFloat(), 1, 8, showBuffer);
      // Trim trailing 0's if there's a '.'
      if (strchr(showBuffer, '.')) {
        size_t len = strlen(showBuffer);
        if (len-- <= 1) {
          return;
        }
        do {
          char c = showBuffer[len--];
          if (c == '0') {
            showBuffer[len + 1] = 0;
          } else if (c == '.') {
            showBuffer[len + 1] = 0;
            break;
          } else {
            break;
          }
        } while (true);
      }
      Serial.println(showBuffer);
      return;
    case ValType::Err:
    case ValType::Text:
      strcpy(showBuffer, txt);
      Serial.println(showBuffer);
      return;
  }
#endif
}
} // namespace calc
