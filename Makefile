exec : main.o 
	gcc -o exec main.o


main.o : main.c struct.h
	gcc -c main.c

