%{
#include <cmath>

// Using my own scanner, because flex has too much FILE crap for Arduino to handle...
#include "ValExpr.h"

int yyerror(const char *s);
int yylex(void);

%}

%require "3.7.4"

%no-lines

%defines "include/CalcParser.h"
%output "CalcParser.cpp"

%union{
  calc::ValExpr  val;
}

%token          EOL LPAREN RPAREN
%token <val>    INT
%token <val>    FLT
%token <val>    VAR

%nterm <val>    exp

%nonassoc       ASSIGN
%left           PLUS MINUS
%left           MULTIPLY DIVIDE MODULO
%precedence     UMINUS
%precedence     FACTORIAL
%right          EXPONENT

%%

lines   : %empty
        | lines line
        ;

line    : EOL                       { yyerror("Read an empty line.\n"); }
        | exp EOL                   { $1.show(); }
        | VAR ASSIGN exp EOL        { $1.assignVal($3); }
        | error EOL                 { yyerrok; }
        ;

exp     : INT                       { $$ = $1; }
        | FLT                       { $$ = $1; }
        | exp PLUS exp              { $$ = $1 + $3; }
        | exp MINUS exp             { $$ = $1 - $3; }
        | exp MULTIPLY exp          { $$ = $1 * $3; }
        | exp DIVIDE exp            { $$ = $1 / $3; }
        | exp MODULO exp            { $$ = $1 % $3; }
        | exp EXPONENT exp          { $$ = $1.power($3); }
        | MINUS exp %prec UMINUS    { $$ = -$2; }
        | exp FACTORIAL             { $$ = $1.factorial(); }
        | LPAREN exp RPAREN         { $$ = $2; }
        | VAR                       { $$ = $1.getVal(); }
        ;

%%
