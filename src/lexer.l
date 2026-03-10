%{
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ast.h"
#include "parser.tab.hpp"

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line; \
    yylloc.first_column = yylloc.last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc.last_line++; \
            yylloc.last_column = 1; \
        } \
        else { \
            yylloc.last_column++; \
        } \
    }

extern int yylex();
%}

%option noyywrap
%option yylineno

%%

[ \t\r\n]+          { /* skip whitespace */ }
"//".*              { /* skip comments */ }

"import"            { return IMPORT; }
"struct"            { return STRUCT; }
"impl"              { return IMPL; }
"fn"                { return FN; }
"var"               { return VAR; }
"if"                { return IF; }
"else"              { return ELSE; }
"while"             { return WHILE; }
"return"            { return RETURN; }
"true"              { return TRUE; }
"false"             { return FALSE; }
"as"                { return AS; }

"void"              { return VOID; }
"int"               { return INT; }
"float"             { return FLOAT; }
"bool"              { return BOOL; }
"char"              { return CHAR; }
"string"            { return STRING; }

[0-9]+\.[0-9]+      { yylval.fval = atof(yytext); return FVAL; }
[0-9]+              { yylval.ival = atoll(yytext); return IVAL; }
\"(\\.|[^"\\])*\"  { yylval.sval = new std::string(yytext + 1, strlen(yytext) - 2); return SVAL; }
\'(\\.|[^'\\])\'    { yylval.ival = yytext[1]; return IVAL; } // simplified char

[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = new std::string(yytext); return IDENT; }

"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"%"                 { return '%'; }
"<<"                { return SHL; }
">>"                { return SHR; }
"=="                { return EQ; }
"!="                { return NE; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return '<'; }
">"                 { return '>'; }
"="                 { return '='; }
"&"                 { return '&'; }
"|"                 { return '|'; }
"^"                 { return '^'; }
"!"                 { return '!'; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }
"["                 { return '['; }
"]"                 { return ']'; }
";"                 { return ';'; }
","                 { return ','; }
"."                 { return '.'; }
":"                 { return ':'; }
"->"                { return ARROW; }

.                   { std::cerr << "Unknown character: " << yytext << std::endl; }

%%
