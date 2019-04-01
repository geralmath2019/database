#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"


int main(){

	int opc;
	
	while(opc!=4){
		opc=0;
		while(opc<1 || opc>4){
			system("clear");
			printf("--Menu Principal--\n1.Libros\n2.Usuarios\n3.Prestamos\n4.salir\n");
			scanf("%d",&opc);
			}
		switch(opc){
			case 1:
				opciones(opc);
				break;
			case 2:
				opciones(opc);
				break;
			case 3:
				opciones(opc);
				break;
			case 4:
				printf("Programa finalizado..");
				break;
			}
		}
	return EXIT_SUCCESS;
}
