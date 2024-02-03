CC = gcc
CFLAGS = -Wall -ll
EXEC = part1

all: $(EXEC)

lex.yy.c: part1.lex
	flex part1.lex

$(EXEC): lex.yy.c
	$(CC) $(CFLAGS) -o $(EXEC) lex.yy.c

clean:
	rm -f $(EXEC) lex.yy.c