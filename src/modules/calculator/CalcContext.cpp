#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <cstring>

#include "CalcContext.h"
#include "CalcExpr.h"
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

void Context::assign(const char* var, const CalcExpr& ce) {
  const char* itrd = intern(const_cast<char*>(var));
  vars.emplace(itrd, ce);
}

CalcExpr Context::getVal(const char* var, const CalcExpr& ce) {
  auto res = interned.find(const_cast<char*>(var));
  if (res == interned.end()) {
    return ce;
  }
  auto val = vars.find(res->second);
  if (val == vars.end()) {
    return ce;
  }
  return val->second;
}

CalcExpr Context::invoke(const char* var, const CalcExpr& ce) const {
  auto res = interned.find(const_cast<char*>(var));
  if (res == interned.end()) {
    return ce;
  }
  auto fn = funcs.find(res->second);
  if (fn == funcs.end()) {
    return ce;
  }
  auto func = fn->second;
  return func(ce);
}

CalcExpr sqrtFn(const CalcExpr& ce) {
  return CalcExpr{std::sqrt(ce.asFloat())};
}

CalcExpr sinFn(const CalcExpr& ce) {
  return CalcExpr{std::sin(ce.asFloat())};
}

CalcExpr cosFn(const CalcExpr& ce) {
  return CalcExpr{std::cos(ce.asFloat())};
}

CalcExpr tanFn(const CalcExpr& ce) {
  return CalcExpr{std::tan(ce.asFloat())};
}

CalcExpr asinFn(const CalcExpr& ce) {
  return CalcExpr{std::asin(ce.asFloat())};
}

CalcExpr acosFn(const CalcExpr& ce) {
  return CalcExpr{std::acos(ce.asFloat())};
}

CalcExpr atanFn(const CalcExpr& ce) {
  return CalcExpr{std::atan(ce.asFloat())};
}

CalcExpr logFn(const CalcExpr& ce) {
  return CalcExpr{std::log10(ce.asFloat())};
}

CalcExpr lnFn(const CalcExpr& ce) {
  return CalcExpr{std::log(ce.asFloat())};
}

const char* names[] = {
  "pi", "e", "sqrt", "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln"};

void Context::clear() {
  for (auto& val : interned) {
    delete[] val.first;
  }
  interned.clear();
  funcs.clear();
  vars.clear();
  // TODO: Create the functions & variables we need
  // vars: pi, e
  // sqrt, sin, cos, tan, asin, acos, atan, log, ln
  for (const char* name : names) {
    interned.emplace(const_cast<char*>(name), name);
  }
  vars.emplace(names[0], CalcExpr{3.141592653589793});
  vars.emplace(names[1], CalcExpr(2.718281828459045));
  funcs.emplace(names[2], sqrtFn);
  funcs.emplace(names[3], sinFn);
  funcs.emplace(names[4], cosFn);
  funcs.emplace(names[5], tanFn);
  funcs.emplace(names[6], asinFn);
  funcs.emplace(names[7], acosFn);
  funcs.emplace(names[8], atanFn);
  funcs.emplace(names[9], logFn);
  funcs.emplace(names[10], lnFn);
}

} // namespace calc