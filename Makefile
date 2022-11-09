all : exec clean run

exec : reseau.o main.o 
	gcc -o exec main.o reseau.o

main.o : main.c struct.h reseau.h
	gcc -c main.c

reseau.o : reseau.c struct.h reseau.h
	gcc -c reseau.c

clean :
	rm -f *.o

run :
	./exec