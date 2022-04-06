%{
#include <cmath>
#if defined(NATIVE)
#include <iostream>
#include <string>
#else
#include "Arduino.h"
#endif
// Using my own scanner, because flex has too much FILE crap for Arduino to handle...
#include "Calculator.h"

#if defined(NATIVE) 
#define print(x) std::cout << x << std::endl
#else
#define print Serial.print
#endif

int yyerror(const char *s);
int yylex(void);

%}

%require "3.7.4"

%no-lines

%defines "include/CalcParser.h"
%output "CalcParser.cpp"

%union{
  int		int_val;
  double	dbl_val;
  char str_val;
}

%token              EOL LPAREN RPAREN
%token <int_val>    INT
%token <dbl_val>    FLT
%token <str_val>    FLTVAR INTVAR

%nterm <int_val>    iexp
%nterm <dbl_val>    fexp

%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%code
{
int64_t ivars['Z' - 'A' + 1];
double fvars['z' - 'a' + 1];

int64_t factorial(int64_t n) {
  int64_t i;
  for (i = 1; n > 1; n--) {
    i *= n;
  }
  return i;
}

} // %code

%%

lines   : %empty
        | lines line
        ;

line    : EOL                       { yyerror("Read an empty line.\n"); }
        | iexp EOL                  { print($1); }
        | fexp EOL                  { print($1); }
        | INTVAR ASSIGN iexp EOL    { ivars[$1 - 'A'] = $3; print($3); }
        | FLTVAR ASSIGN fexp EOL    { fvars[$1 - 'a'] = $3; print($3); }
        | error EOL                 { yyerrok; }
        ;

iexp    : INT                       { $$ = $1; }
        | iexp PLUS iexp            { $$ = $1 + $3; }
        | iexp MINUS iexp           { $$ = $1 - $3; }
        | iexp MULTIPLY iexp        { $$ = $1 * $3; }
        | iexp DIVIDE iexp          { $$ = $1 / $3; }
        | iexp MODULO iexp          { $$ = $1 % $3; }
        | MINUS iexp %prec UMINUS   { $$ = -$2; }
        | iexp FACTORIAL            { $$ = factorial($1); }
        | LPAREN iexp RPAREN        { $$ = $2; }
        | INTVAR                    { $$ = ivars[$1 - 'A']; }
        ;

fexp    : FLT                       { $$ = $1; }
        | fexp PLUS fexp            { $$ = $1 + $3; }
        | fexp MINUS fexp           { $$ = $1 - $3; }
        | fexp MULTIPLY fexp        { $$ = $1 * $3; }
        | fexp DIVIDE fexp          { $$ = $1 / $3; }
        | fexp EXPONENT fexp        { $$ = pow($1, $3); }
        | MINUS fexp %prec UMINUS   { $$ = -$2; }
        | LPAREN fexp RPAREN        { $$ = $2; }
        | FLTVAR                    { $$ = fvars[$1 - 'a']; }
        ;

%%
const char *errors = nullptr;
calc::Scanner *scan;

int yyerror(const char *msg) {
  errors = msg;
  return 1;
}

int yylex() {
  return scan->lex();
}

void Parse(const char *str) {
  errors = nullptr;
  calc::Scanner scanner{ str };
  scan = &scanner;
  yyparse();
  if (errors != nullptr) {
    print(errors);
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