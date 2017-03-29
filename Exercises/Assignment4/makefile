all: prog

prog1: bst.o compare1.o
	gcc -g -Wall -std=c99 -o prog1 bst.o compare1.o

prog2: bst2.o compare2.o
	gcc -g -Wall -std=c99 -o prog2 bst2.o compare2.c

compare1.o: compare1.c
	gcc -g -Wall -std=c99 -c compare1.c

compare2.o: compare2.c
	gcc -g -Wall -std=c99 -c compare2.c
		
bst.o: bst.c bst.h
	gcc -g -Wall -std=c99 -c bst.c

bst2.o: bst2.c bst.h
	gcc -g -Wall -std=c99 -c bst2.c

clean:	
	rm bst.o
	rm bst2.o
	rm compare1.o
	rm compare2.o
	rm prog1
	rm prog2
