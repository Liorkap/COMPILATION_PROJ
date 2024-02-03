/*Definitions*/

%{
#include <stdio.h>
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

int|float|void|write|read|optional|while|do|if|then|else|return     printf("<%s>",yytext);

[(){},;:]                                                           printf("%s",yytext);

{id}                                                                printf("<id,%s>",yytext);
{integernum}                                                        printf("<integernum,%s>",yytext);
{realnum}                                                           printf("<realnum,%s>",yytext);
{relop}                                                             printf("<relop,%s>",yytext);
{addop}                                                             printf("<addop,%s>",yytext);
{mulop}                                                             printf("<mulop,%s>",yytext);
{assign}                                                            printf("<assign,%s>",yytext);
{and}                                                               printf("<and,%s>",yytext);
{or}                                                                printf("<or,%s>",yytext);
{not}                                                               printf("<not,%s>",yytext);
{str}                                                               printf("<str,%.*s>",(int)yyleng-2,yytext+1);
              
#([^\r\n])*                                                           /*eat up comments*/

[ \t\r\n]+                                                          printf("%s",yytext);

.                                                                   {
                                                                    printf("\nLexical error: '%s' in line number %d\n",yytext,yylineno);
                                                                    yyterminate();
                                                                    return 1;
                                                                    }


%%











