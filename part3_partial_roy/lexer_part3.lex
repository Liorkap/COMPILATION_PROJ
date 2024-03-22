/* Definitions */

%{
#include <stdio.h>
#include <iostream>
#include <string>
#include "part3_header.hpp"
#include "bison_part3.tab.hpp"
%}

%option yylineno
%option noyywrap

/* Regex patterns */
id            ([A-Za-z])([A-Za-z0-9_])*
integernum    ([0-9])+
realnum       ([0-9])+\.([0-9])+
str           \"([^\"\\\r\n]|\\(\"|n|t))*\"
relop         (==|<>|<|<=|>|>=)
addop         (\+|\-)
mulop         (\*|\/)
assign        (=)
and           (&&)
or            (\|\|)
not           (!)

%%

 /* For each token we match, the semantic value that is passed to Bison 
    NOTE: the part2 helpers like makeNode are not neccesary anymore 
   we instead just return the string for each token, yylval.str = yytext */


int                     {  return INT; }

float                   {  return FLOAT; }

void                    {  return VOID; }

write                   {  return WRITE; }

read                    {  return READ; }

optional                {  return OPTIONAL; }

while 	                {  return WHILE; }

do                      {  return DO; }

if                      {  return IF; }

then                    {  return THEN; }

else                    {  return ELSE; }

return                  {  return RETURN; }

[(]                     {  return OPENBRACKET_B; }

[)]                     {  return CLOSEDBRACKET_B; }

[{]                     {  return OPENBRACKET_A; }

[}]	                {  return CLOSEDBRACKET_A; }

[,]	                {  return COMMA; }

[;]                     {  return SEMICOLON; }

[:]                     {  return COLON; }
                                                         
{id}                    { yylval.str = strdup(yytext); return ID; }

{integernum}            { yylval.str = strdup(yytext); return INTEGERNUM; }

{realnum}               { yylval.str = strdup(yytext); return REALNUM; }

{relop}                 { yylval.str =  strdup(yytext); return RELOP; }

{addop}                 { yylval.str =  strdup(yytext); return ADDOP; }

{mulop}                 { yylval.str =  strdup(yytext); return MULOP; }

{assign}                { yylval.str =  strdup(yytext); return ASSIGN; }

{and}                   { yylval.str =  strdup(yytext); return AND; }

{or}                    { yylval.str =  strdup(yytext); return OR; }

{not}                   { yylval.str =  strdup(yytext); return NOT; }

{str}                   { yytext[yyleng-1] = '\0'; yylval.str = strdup((yytext+1)); return STR; }

#([^\r\n])*             /* eat up comments */

[ \t\r\n]+              /* ignore spaces */

.                       {
                            printf("Lexical error: '%s' in line number %d\n",yytext,yylineno);
                            exit(1);
                        }
%%
