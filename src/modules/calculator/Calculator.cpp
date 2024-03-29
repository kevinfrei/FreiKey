// MSVC, LKG6, bad memories. Very. Bad. Memories.
#define _CRT_SECURE_NO_WARNINGS 1
#if defined(STANDALONE)
#include <iostream>
#include <string>
#else
#include "Arduino.h"
#endif

#include "CalcContext.h"
#include "CalcLexer.h"
#include "CalcParser.h"
#include "Calculator.h"

// This stuff is all for the bison parser

const char* errors = nullptr;
calc::Lexer* scan;

int yyerror(const char* msg) {
#if defined(STANDALONE)
  std::cerr << "Error:" << msg << std::endl;
#endif
  errors = msg;
  return 1;
}

int yylex() {
  return scan->lex();
}

namespace calc {

void Initialize() {
  std::fill(std::begin(showBuffer), std::end(showBuffer), 0);
  context.clear();
}

const char* Parse(const char* str) {
  errors = nullptr;
  calc::Lexer scanner{str};
  scan = &scanner;
  yyparse();
  // TODO: Return the calculated expression
  return showBuffer;
}

} // namespace calc

#if defined(STANDALONE)
int main(int argc, const char* argv[]) {
  std::string input;
  std::cout.precision(10);
  do {
    std::cout << "Enter some stuff:" << std::endl;
    std::getline(std::cin, input);
    std::cout << "'" << input << "'" << std::endl;
    calc::Parse(input.c_str());
    std::cout << "====" << std::endl;
  } while (!input.empty());
  return 0;
}
#endif
