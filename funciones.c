#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prototipos.h"

void agregarLibro(interaccion *booklist,Libro aux){
		listaLibro *nuevo = (listaLibro*) malloc(sizeof(listaLibro));
		listaLibro *auxP = booklist->lCab;
		if(nuevo==NULL){
			printf("Error asignacion de memoria");
			exit(EXIT_FAILURE);
		}
		nuevo->x.titulo =(char*)malloc(sizeof(char)*(strlen(aux.titulo)+1));
		strcpy(nuevo->x.titulo,aux.titulo);
		
		nuevo->x.edicion=aux.edicion;
		
		nuevo->x.autor=(char*)malloc(sizeof(char)*(strlen(aux.autor)+1));
		strcpy(nuevo->x.autor,aux.autor);
		
		nuevo->x.disp=aux.disp;
		nuevo->x.idUser = aux.idUser;
		
		if(booklist->lCab==NULL){
			nuevo->ant=NULL;
			nuevo->sig=NULL;
			booklist->lCab=nuevo;
		} else {
				while(auxP->sig!=NULL){
					auxP=auxP->sig;
				}
				nuevo->ant=auxP;
				auxP->sig=nuevo;
				nuevo->sig=NULL;
		}
}

void agregarUsuario(interaccion *booklist,usuario aux){
	listaUsuario* nuevo=(listaUsuario*)malloc(sizeof(listaUsuario)),*aux=booklist->uCab;
	if(nuevo==NULL){
		printf("Error asignacion de memoria");
		exit(-1);
		}
	nuevo->x.nombre=(char*)malloc(sizeof(char)*(strlen(aux.nombre)+1));
	strcpy(nuevo->x.nombre,aux.nombre);
	nuevo->x.identificacion=(char*)malloc(sizeof(char)*(strlen(aux.identificacion)+1));
	strcpy(nuevo->x.identificacion,aux.identificacion);
	strcpy(nuevo->x.tipo,aux.tipo);
	nuevo->x.prestados=aux.prestados;
	
	if(booklist->uCab==NULL){
			nuevo->ant=NULL;
			nuevo->sig=NULL;
			booklist->uCab=nuevo;
	} else {
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		nuevo->ant=aux;
		aux->sig=nuevo;
		nuevo->sig=NULL;
	}
}
void agregarPrestamo(interaccion *booklist,prestamo aux){
	listaPrestamo* nuevo=(listaPrestamo*)malloc(sizeof(listaPrestamo)),*aux=booklist->pCab;
	nuevo->x.tituloLibro=(char*)malloc(sizeof(char)*(strlen(aux.tituloLibro)+1));
	strcpy(nuevo->x.tituloLibro,aux.tituloLibro);
	nuevo->x.nombreUsuario=(char*)malloc(sizeof(char)*(strlen(aux.nombreUsuario)+1));
	strcpy(nuevo->x.nombreUsuario,aux.nombreUsuario);
	strcpy(nuevo->x.fechaPrestamo,aux.fechaPrestamo);
	strcpy(nuevo->x.fechaDevolucion,aux.fechaDevolucion);
	
	if(booklist->pCab==NULL){
		nuevo->ant=NULL;
		nuevo->sig=NULL;
		booklist->pCab=nuevo;
		}else{
			while(aux->sig!=NULL){
				aux=aux->sig;
			}
				nuevo->ant=aux;
				aux->sig=nuevo;
				nuevo->sig=NULL;
		}
}
	
void insertarLibro(interaccion *lista){
		FILE *archivo = fopen("Libros.txt","a+");
		char auxTitulo[50],auxAutor[50];
		Libro nuevo;
		memset(&nuevo,0,sizeof(Libro));
		setbuf(stdin,NULL);
		printf("ingrese el titulo del libro: ");
		fgets(auxTitulo,50,stdin);
		strtok(auxTitulo,"\n");
		nuevo.titulo = (char *) malloc(sizeof(char)*(strlen(auxTitulo)+1));
		strcpy(nuevo.titulo,auxTitulo);
		setbuf(stdin,NULL);
		printf("ingrese la edicion del libro: ");
		scanf("%d",&nuevo.edicion);
		setbuf(stdin,NULL);
		printf("ingrese el nombre del autor: ");
		fgets(auxAutor,50,stdin);
		strtok(auxAutor,"\n");
		nuevo.autor = (char *) malloc(sizeof(char)*(strlen(auxAutor)+1));
		strcpy(nuevo.autor,auxAutor);
		nuevo.disp = 0;
		nuevo.idUser = 0;
		fprintf(archivo,"%s/%d/%s/%d/%d\n",nuevo.titulo,nuevo.edicion,nuevo.autor,nuevo.disp,nuevo.idUser);
		fclose(archivo);
		puts("libro agregado....");
		lista->bookCont++;
}

void insertarUsuario(interaccion *lista){
	FILE *archivo = fopen("Usuarios.txt","a+");
	char auxName[40],auxIdent[20];
	int tam;
	listaUsuario aux;
	printf("ingrese el id del usuario: ");
	scanf("%d",&aux.id);
	printf("Ingrese el nombre del usuario: ");
	fgets(auxName,40,stdin);
	strtok(auxName,"\n");
	tam = strlen(auxName) + 1;
	aux.nombre = (char *) malloc(tam * sizeof(char));
	strcpy(aux.nombre,auxName);
	printf("ingrese la identificacion del usuario: ");
	fgets(auxIdent,20,stdin);
	tam = strlen(auxIdent) + 1;
	aux.identificacion = (char *) malloc(tam * sizeof(char));
	strcpy(aux.identificacion,auxIdent);
	printf("Ingrese el tipo de usuario: ");
	fgets(aux.tipo,12,stdin);
	strtok(aux.tipo,"\n");
	aux.prestados = 0;
	fprintf(archivo,"%d/%s/%s/%d/%d*",aux.id,aux.nombre,aux.identificacion,aux.tipo,aux.prestados);
	fclose(archivo);
	lista->userCont++;
}

void insertarPrestamo(interaccion *lista,int auxId,int auxISBN){
	FILE *archivo = fopen("Prestamos.txt","a+");
	Prestamo x;
	
	x.ISBN_libro = auxISBN;
	x.idUser = auxId;
	setbuf(stdin,NULL);
	printf("Ingrese la fecha del prestamo: ");
	fgets(x.fechaPrestamo,12,stdin);
	strtok(x.fechaPrestamo,"\n");
	setbuf(stdin,NULL);
	printf("ingrese la fecha de devolucion: ");
	fgets(x.fechaDevolucion,12,stdin);
	strtok(x.fechaPrestamo,"\n");
}

void verificarPrestamo(interaccion *lista){
	FILE *archivolib = fopen("isbn.txt","rb");
	FILE *archivoID = fopen("verID.txt","rb");
	int id,isbn,i,flag=0;
	printf("ingrese el isbn del libro a prestar: ");
	scanf("%d",&isbn);
	int *array = (int *) malloc(lista->bookCont * sizeof(int));
	fread(array,lista->bookCont,sizeof(int),archivolib);
	for (i=0;i<lista->bookCont;i++){
		if (isbn == array[i]){
			flag = 1;
		}
	}
	if(flag == 0){
		puts("El libro no existe...");
		return;
	}
	flag = 0;
	fclose(archivolib);
	free(array);
	extraerDataLibro(lista);
	listaLibro *aux = lista->lCab;
	while(aux){
		if (isbn == aux->x.ISBN){
			flag = 1;
			break;
		}
		aux=aux->sig;
	}
	if(flag == 0){
		puts("El libro no esta disponible...");
		//liberar(cabeza)
		return;
	}
	flag = 0;
	printf("Ingrese el id del usuario deudor del libro: ");
	scanf("%d",&id);
	array = (int *) malloc(lista->UserCont * sizeof(int));
	fread(array,lista->UserCont,sizeof(int),archivoID);
	for(i=0;i<lista->UserCont;i++){
		if (id == array[i].id){
			flag = 1;
			break;
		}
	}
	free(array);
	fclose(archivoID);
	if (flag == 0){
		puts("El usuario no existe...");
		return;
	}
	char auxleer[300];
	int cont = 0;
	FILE *auxLib = fopen("Libros.txt","r");
	while(cont < i){
		fgets(auxleer,300,auxLib);
		cont++;
	}
	
	
}

void vaciarData(interaccion *lista,listaPrestados *temp, int op){
	
}

void extraerDataLibro(interaccion *lista){
	Libro aux;
	char lect[80],c;
	FILE *archivo = fopen("Libros.txt","r");
	int i=0,k,contCampos=0,tam,numaux;
	for(i=0;i<lista->bookCont && !feof(archivo);i++){
		contCampos = 1;
		while(c != '\n' && contCampos <= 5){
			k=0;
			memset(lect,'\0',80);
			while(c != '/'){
				c = fgetc(archivo);
				if(c == '\n'){
					c = '/';
					continue;
				}
				lect[k]=c;
				k++;
			}
			if (c!='\n'){
				c='\0';
			}
			puts(lect);
			switch(contCampos){
				case 1:
					strtok(lect,"/");
					puts(lect);
					 tam = strlen(lect) + 1;
					 aux.titulo = (char *) malloc(tam * sizeof(char));
					 strcpy(aux.titulo, lect);
				break;
				case 2:
					strtok(lect,"/");
					numaux= atoi(lect);
					aux.edicion = numaux;
				break;
				case 3:
					strtok(lect,"/");
					tam = strlen(lect) + 1;
					aux.autor = (char *) malloc(tam * sizeof(char));
					strcpy(aux.autor,lect);
				break;
				case 4:
					strtok(lect,"/");
					numaux= atoi(lect);
					aux.disp = numaux;
				break;
				case 5:
					strtok(lect,"\n");
					numaux= atoi(lect);
					aux.idUser = numaux;
				break;
			}

			contCampos++;
		}
		agregarLibro(lista,aux);
		free(aux.titulo);
		free(aux.autor);
	}
	fclose(archivo);
	puts("Data extraida...");
}


void extraerDataUsuario(){
}

void extraerDataPrestamos(){
}
