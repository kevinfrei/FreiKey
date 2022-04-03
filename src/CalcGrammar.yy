%{
#include <iostream>
#include <string>
#include <cmath>
#include <stdint.h>

#include <FlexLexer.h>
%}

%require "3.7.4"
%language "C++"

%defines "include/CalcParser.h"
%output "CalcParser.cpp"

%define api.parser.class {Parser}
%define api.namespace {calc}
%define api.value.type variant

%parse-param {Scanner* scanner}

%code requires
{
    namespace calc {
        class Scanner;
    } // namespace calc
} // %code requires

%code
{
    #include "CalcScanner.h"
    #define yylex(x) scanner->lex(x)
}

%token              EOL LPAREN RPAREN
%token <int64_t>    INT
%token <double>     FLT
%token <char>       INTVAR FLTVAR

%nterm <int64_t>    iexp
%nterm <double>     fexp

%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO
%precedence         UMINUS
%precedence         FACTORIAL
%right              EXPONENT

%code
{
    namespace calc {
        int64_t ivars['Z' - 'A' + 1];
        double fvars['z' - 'a' + 1];

        int64_t factorial(int64_t n) {
          int64_t i;
          for (i = 1; n > 1; n--) {
            i *= n;
          }
          return i;
        }
    } // namespace calc
} // %code

%%

lines   : %empty
        | lines line
        ;

line    : EOL                       { std::cerr << "Read an empty line.\n"; }
        | iexp EOL                  { std::cout << $1 << '\n'; }
        | fexp EOL                  { std::cout << $1 << '\n'; }
        | INTVAR ASSIGN iexp EOL    { ivars[$1 - 'A'] = $3; }
        | FLTVAR ASSIGN fexp EOL    { fvars[$1 - 'a'] = $3; }
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

void calc::Parser::error(const std::string& msg) {
    std::cerr << msg << std::endl;
}