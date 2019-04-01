#pragma once
//estructuras

typedef struct {
	char *titulo;
	int edicion;
	char *autor;
	int disp;
	int idUser;
	int ISBN;
}Libro;

typedef struct {
	int id;
	char *nombre;
	char *identificacion;
	char tipo[12];
	int prestados;
}Usuario;

typedef struct {
	int idUser;
	int ISBN_libro;
	char fechaPrestamo[12];
	char fechaDevolucion[12];
}Prestamo;

typedef struct l {
	Libro x;
	struct l *sig;
}listaLibro;

typedef struct l1 {
	Usuario x;
	struct l1 *sig;
}listaUsuario;

typedef struct l2 {
	Prestamo x;
	struct l2 *sig;
}listaPrestamo;

typedef struct {
	listaLibro *lCab;
	listaUsuario *uCab;
	listaPrestamo *pCab;
	int bookCont;
	int UserCont;
	int prestamoCont;
}interaccion;
//----------------
//prototipos de funciones
void agregarLibro(interaccion *booklist,Libro aux);
void agregarUsuario(interaccion *booklist,Usuario aux);
void agregarPrestamo(interaccion *booklist,Prestamo aux);
