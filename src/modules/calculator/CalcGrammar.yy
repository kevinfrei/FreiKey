%{
#include <cmath>

// Using my own scanner, because flex is incredibly 'stdio.h-centric' which hates Arduino
#include "CalcExpr.h"
int yyerror(const char *s);
int yylex(void);

%}

%require "3.7.4"

%no-lines

%defines "include/CalcParser.h"
%output "CalcParser.cpp"

%code requires {
#include "CalcExpr.h"
}

%define api.value.type yystype

%token          EOL LPAREN RPAREN
%token <self()>    INT
%token <self()>    FLT
%token <self()>    VAR

%nterm <self()>    exp

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
