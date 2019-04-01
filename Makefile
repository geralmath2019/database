#esto compila el programa principal
main: main.o funciones.o
	gcc main.o funciones.o -o main

#aqui se compilan los archivos objetos o dependencias necesarias
main.o: main.c prototipos.h
	gcc -c main.c

funciones.o: funciones.c prototipos.h
	gcc -c funciones.c

clean:
	rm *.o main
