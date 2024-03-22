# Makefile for part2 - parser
all: part3

part3: lex.yy.o bison_part3.tab.o part3_implementation.o
	g++ -std=c++11 -o $@ $^

lex.yy.o: lex.yy.c part3_header.hpp bison_part3.tab.hpp 
	g++ -std=c++11 -c -o $@ lex.yy.c

lex.yy.c: lexer_part3.lex
	flex lexer_part3.lex

bison_part3.tab.o: bison_part3.tab.cpp bison_part3.tab.hpp
	g++ -std=c++11 -c -o $@ bison_part3.tab.cpp

part3_implementation.o: part3_implementation.cpp part3_header.hpp
	g++ -std=c++11 -c -o $@ part3_implementation.cpp

bison_part3.tab.cpp bison_part3.tab.hpp: bison_part3.ypp part3_header.hpp
	bison -d bison_part3.ypp

.PHONY: clean
clean:
	rm -f part3 *.o *.tab.* lex.yy.c
