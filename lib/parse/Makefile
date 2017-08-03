AR = ar
CC = gcc
LD = gcc

OBJECTS = parse.o lex.o

nfv_parse.a: nfv_lexe.l nfv_parse.y
	lex nfv_lexe.l
	yacc -d nfv_parse.y
	gcc -c -Wall -Werror --pedantic lex.yy.c -o lex.o
	gcc -c -Wall -Werror --pedantic y.tab.c -o parse.o
	$(AR) r nfv_parse.a $(OBJECTS)

clean:
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.h
	rm -rf *.o
	rm -rf nfv_parse.a
