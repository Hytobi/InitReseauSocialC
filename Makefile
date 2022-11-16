all : exec  clean run mrproper

exec : reseau.o parser.o main.o fichier.o navigation.o
	gcc -o exec main.o reseau.o parser.o fichier.o navigation.o

main.o : main.c struct.h reseau.h fichier.h navigation.h parser.h
	gcc -c main.c

reseau.o : reseau.c struct.h reseau.h
	gcc -c reseau.c

parser.o : parser.c struct.h parser.h
	gcc -c parser.c

fichier.o : fichier.c struct.h fichier.h reseau.h
	gcc -c fichier.c

navigation.o : navigation.c struct.h navigation.h
	gcc -c navigation.c

clean :
	rm -f *.o

run :
	./exec

mrproper : clean
	rm -f exec