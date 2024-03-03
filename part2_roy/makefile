# Makefile for part2 - parser
all: part2

part2: lex.yy.o bison_part2.tab.o part2_helpers.o
	g++ -o $@ $^

lex.yy.o: lex.yy.c part2_helpers.h bison_part2.tab.hpp 
	g++ -c -o $@ lex.yy.c

lex.yy.c: lexer_part2.lex
	flex lexer_part2.lex

bison_part2.tab.o: bison_part2.tab.cpp bison_part2.tab.hpp
	g++ -c -o $@ bison_part2.tab.cpp

part2_helpers.o: part2_helpers.c part2_helpers.h
	g++ -c -o $@ part2_helpers.c

bison_part2.tab.cpp bison_part2.tab.hpp: bison_part2.ypp part2_helpers.h
	bison -d bison_part2.ypp

.PHONY: clean
clean:
	rm -f part2 *.o *.tab.* lex.yy.c
