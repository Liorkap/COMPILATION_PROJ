/*Definitions*/

%{
#include <stdio.h>
#include <iostream>
#include "part2_helpers.h"
#include "bison_part2.tab.hpp"

%}


%option yylineno
%option noyywrap

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

int        {yylval = makeNode(yytext,NULL,NULL); return INT;}
float      {yylval = makeNode(yytext,NULL,NULL); return FLOAT;}
void       {yylval = makeNode(yytext,NULL,NULL); return VOID;}
write      {yylval = makeNode(yytext,NULL,NULL); return WRITE;}
read       {yylval = makeNode(yytext,NULL,NULL); return READ;}
optional   {yylval = makeNode(yytext,NULL,NULL); return OPTIONAL;}
while 	   {yylval = makeNode(yytext,NULL,NULL); return WHILE;}
do         {yylval = makeNode(yytext,NULL,NULL); return DO;}
if         {yylval = makeNode(yytext,NULL,NULL); return IF;}
then       {yylval = makeNode(yytext,NULL,NULL); return THEN;}
else       {yylval = makeNode(yytext,NULL,NULL); return ELSE;}
return     {yylval = makeNode(yytext,NULL,NULL); return RETURN;}

[(]        {yylval = makeNode(yytext,NULL,NULL); return OPENBRACKET_B;}
[)]        {yylval = makeNode(yytext,NULL,NULL); return CLOSEDBRACKET_B;}
[{]          {yylval = makeNode(yytext,NULL,NULL); return OPENBRACKET_A;}
[}]	   {yylval = makeNode(yytext,NULL,NULL); return CLOSEDBRACKET_A;}
[,]	   {yylval = makeNode(yytext,NULL,NULL); return COMMA;}
[;]        {yylval = makeNode(yytext,NULL,NULL); return SEMICOLON;}
[:]          {yylval = makeNode(yytext,NULL,NULL); return COLON;}
                                                         

{id}                                                                {yylval = makeNode("id",yytext,NULL); return ID;}

{integernum}                                                        {yylval = makeNode("integernum",yytext,NULL); return INTEGERNUM;}

{realnum}                                                           {yylval = makeNode("realnum",yytext,NULL); return REALNUM;}

{relop}                                                             {yylval = makeNode("relop",yytext,NULL); return RELOP;}

{addop}                                                             {yylval = makeNode("addop",yytext,NULL); return ADDOP;}

{mulop}                                                             {yylval = makeNode("mulop",yytext,NULL); return MULOP;}

{assign}                                                            {yylval = makeNode("assign",yytext,NULL); return ASSIGN;}

{and}                                                               {yylval = makeNode("and",yytext,NULL); return AND;}

{or}                                                                {yylval = makeNode("or",yytext,NULL); return OR;}

{not}                                                               {yylval = makeNode("not",yytext,NULL); return NOT;}

{str}                                                                {
yytext[yyleng-1] = '\0';
yylval = makeNode("str",yytext+1,NULL); return STR;             }

#([^\r\n])*                                                         /*eat up comments*/

[ \t\r\n]+                                                          /*ignore spaces*/

.                                                                   {
                                                                    printf("Lexical error: '%s' in line number %d\n",yytext,yylineno);
                                                                    exit(1);
                                                                    }


%%











