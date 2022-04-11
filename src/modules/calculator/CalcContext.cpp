#include <cstring>

#include "CalcContext.h"

namespace calc {

Context context;

const char* Context::intern(char* str) {
  auto res = interned.find(str);
  if (res != interned.end()) {
    return res->second;
  }
  // Okay, we haven't seen this string yet,
  // so allocate a copy and intern that copy
  char* buf = new char[std::strlen(str) + 1];
  std::strcpy(buf, str);
  interned.emplace(buf, buf);
  return buf;
}

void Context::assign(const char* var, const CalcExpr& ce) {}
CalcExpr Context::getVal(const char* var, const CalcExpr& ce) {
  return ce;
}
CalcExpr Context::invoke(const char* var, const CalcExpr& ce) const {
  return ce;
}

} // namespace calc