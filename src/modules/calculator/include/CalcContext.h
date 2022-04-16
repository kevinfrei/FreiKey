#pragma once

// MSVC, LKG6, bad memories. Very. Bad. Memories.
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <vector>

#include "CalcParser.h"

namespace calc {

struct StrCompare {
  bool operator()(const char* const str1, const char* const str2) const {
    return std::strcmp(str1, str2) < 0;
  }
};

class Context {
  // I need/want to intern strings
  std::map<char*, const char*, StrCompare> interned;
  // Then I need a function map
  std::map<const char*, CalcExpr (*)(const CalcExpr&)> funcs;
  // And I need a variable map
  std::map<const char*, CalcExpr> vars;

 public:
  const char* intern(char*);
  void assign(const char*, const CalcExpr&);
  CalcExpr getVal(const char*, const CalcExpr&);
  CalcExpr invoke(const char*, const CalcExpr&) const;
  void clear();
};

extern Context context;

} // namespace calc