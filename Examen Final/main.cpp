#include <string>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include "arbolBinario.hpp"

using namespace std; 

int main()
{
	arbolBinario * arbol  = crearArbolBinario();
	int seleccion = 0;
	int valor = 0;
	nodoBinario* nodo = 0;
	// prueba de inserccion
	/*insertarArbolBinario(arbol,10);
	insertarArbolBinario(arbol,5);
	insertarArbolBinario(arbol,4);
	insertarArbolBinario(arbol,13);
	insertarArbolBinario(arbol,7);
	insertarArbolBinario(arbol,12);
	infoArbolBinario(arbol);*/
	// fin la prueba
        do{
        	printf("**************** Seleccione una opcion *******************\n");
        	printf("1.insertar\n");
        	printf("2.eliminar\n");
        	printf("3.Buscar\n");
        	printf("4.graficar\n");
        	printf("5.Exit\n");
        	scanf("%i", &seleccion);

        	switch(seleccion){
			    case 1:
			    	printf("Valor a insertar:\n");
			    	scanf("%i", &valor);
			    	insertarArbolBinario(arbol,valor);
			    	infoArbolBinario(arbol);
					rotacionesArbolBinario(arbol,valor);
			    break;
			    case 2:
					printf("Valor a eliminar:\n");
			    	scanf("%i", &valor);
					rotacionesArbolBinario(arbol,valor);
					arbolEliminar(arbol, valor);
					infoArbolBinario(arbol);
			    break;
			    case 3:
			    	printf("Valor a buscar:\n");
					scanf("%i", &valor);
			    	nodo = buscarArbolBinario(arbol,valor);
			    	if(nodo==0){
			    		printf("El valor no existe\n");
			    	}else{
			    		printf("Valor a buscado %i\n",valor);
						infoArbolBinario(arbol);
						rotacionesArbolBinario(arbol,valor);
			    	}
			    break;
			    case 4:
			    	recorridoArbol(arbol);
			    break;
				case 5: 
					printf("Adios :(\n");
			    break;
			    default:
			    	printf("No es una opcion\n");
			    break;
			}

        }while(seleccion!=5);
        return 0;
}
