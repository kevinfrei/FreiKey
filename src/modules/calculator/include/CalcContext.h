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
  bool operator()(char* str1, char* str2) {
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
  void assign(const CalcExpr&);
  CalcExpr invoke(const char*, const CalcExpr&) const;
};

} // namespace calc