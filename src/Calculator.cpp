#if defined(NATIVE)
#include <iostream>
#include <string>
#else
#include "Arduino.h"
#endif

#include "ValExpr.h"

#include "CalcParser.h"
#include "Calculator.h"

const char* errors = nullptr;
calc::Scanner* scan;

int yyerror(const char* msg) {
  #if defined(NATIVE)
  std::cerr << "Error:" << msg << std::endl;
  #endif
  errors = msg;
  return 1;
}

int yylex() {
  return scan->lex();
}

void Parse(const char* str) {
  errors = nullptr;
  calc::Scanner scanner{str};
  scan = &scanner;
  yyparse();
  if (errors != nullptr) {
#if defined(NATIVE)
    std::cerr << errors << std::endl;
#else
    Serial.println(errors);
#endif
  }
}

#if defined(NATIVE)
int main(int argc, const char* argv[]) {
  std::string input;
  std::cout.precision(10);
  do {
    std::cout << "Enter some stuff:" << std::endl;
    std::getline(std::cin, input);
    std::cout << "'" << input << "'" << std::endl;
    Parse(input.c_str());
    std::cout << "====" << std::endl;
  } while (!input.empty());
  return 0;
}
#endif