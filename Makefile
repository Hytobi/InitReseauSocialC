all : exec clean run mrproper

exec : reseau.o parser.o main.o 
	gcc -o exec main.o reseau.o parser.o

main.o : main.c struct.h reseau.h
	gcc -c main.c

reseau.o : reseau.c struct.h reseau.h
	gcc -c reseau.c

parser.o : parser.c struct.h parser.h
	gcc -c parser.c

clean :
	rm -f *.o

run :
	./exec

mrproper : clean
	rm -f exec