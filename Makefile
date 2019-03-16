



run: clean test
	#./test
	valgrind ./test
	#gdb

test: test.o fonctions.o
	gcc -Wall -o test test.o fonctions.o

test.o: test.c
	gcc -Wall -c -g test.c

fonctions.o: fonctions.c fonctions.h
	gcc -Wall -g -c fonctions.c

clean:
	rm -f test
	rm -f *.o