#include <stdio.h>
#include <stdlib.h>
#include "arbolBinario.hpp"


int main()
{
	
	int seleccion = 0;
        do{
        	printf("**************** Seleccione una opcion *******************\n");
        	printf("1.insertar\n");
        	printf("2.eliminar\n");
        	printf("3.modificar\n");
        	printf("4.graficar\n");
        	printf("0.Exit");
        	scanf("%d", &seleccion);

        	switch(seleccion){
				case 0: 
					printf("Adios :(");
			    break;
			    case 1: 
			    break;
			    case 2: 
			    break;
			    case 3: 
			    break;
			    case 4: 
			    break;
			    default:
			    break;
			}

        }while(seleccion!=0);

        return 0;
}
