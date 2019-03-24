



run: clean test
	#./test
	valgrind ./test
	#gdb

test: test.o attaque.o keySchedule.o fonctions.o 
	gcc -Wall -o test test.o attaque.o keySchedule.o fonctions.o

test.o: test.c attaque.h
	gcc -Wall -c -g test.c

attaque.o: attaque.c attaque.h fonctions.h
	gcc -Wall -g -c attaque.c

keySchedule.o: keySchedule.c
	gcc -Wall -g -c keySchedule.c

fonctions.o: fonctions.c fonctions.h
	gcc -Wall -g -c fonctions.c

clean:
	rm -f test
	rm -f *.o