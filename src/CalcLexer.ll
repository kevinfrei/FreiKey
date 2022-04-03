%{
#include "CalcParser.h"
#include "CalcScanner.h"
#define YY_DECL int calc::Scanner::lex(calc::Parser::semantic_type *yylval)
// workaround for bug in flex 2.6.4
#define yypanic(X) (void)(X)
%}

%option c++ interactive noyywrap noyylineno nodefault nounistd outfile="CalcScanner.cpp"

dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)

integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))
intvar          ([[:upper:]])
fltvar          ([[:lower:]])

%%

{integer}       yylval->emplace<long long>(strtoll(YYText(), nullptr, 10)); return Parser::token::INT;
{float}         yylval->emplace<double>(strtod(YYText(), nullptr)); return Parser::token::FLT;
{intvar}        yylval->emplace<char>(YYText()[0]); return Parser::token::INTVAR;
{fltvar}        yylval->emplace<char>(YYText()[0]); return Parser::token::FLTVAR;
"+"             return Parser::token::PLUS;
"-"             return Parser::token::MINUS;
"*"             return Parser::token::MULTIPLY;
"/"             return Parser::token::DIVIDE;
"%"             return Parser::token::MODULO;
"!"             return Parser::token::FACTORIAL;
"^"             return Parser::token::EXPONENT;
"("             return Parser::token::LPAREN;
")"             return Parser::token::RPAREN;
"="             return Parser::token::ASSIGN;
\n              return Parser::token::EOL;
<<EOF>>         return Parser::token::YYEOF;
.               /* no action on unmatched input */

%%

int yyFlexLexer::yylex() {
    throw std::runtime_error("Invalid call to yyFlexLexer::yylex()");
}

int main() {
    calc::Scanner scanner{ std::cin, std::cerr };
    calc::Parser parser{ &scanner };
    std::cout.precision(10);
    parser.parse();
}