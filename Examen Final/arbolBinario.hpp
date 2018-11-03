#ifndef ARBOLBINARIO_HPP_INCLUDED
#define ARBOLBINARIO_HPP_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

using namespace std; 

struct nodoBinario{
    struct nodoBinario *izq;
    struct nodoBinario *der;
    int id;
    int fe;
    int altura;
    int nivel;
};

struct arbolBinario{
    struct nodoBinario *raiz;
};

struct arbolBinario* crearArbolBinario(){
    struct arbolBinario* arbol = static_cast<arbolBinario*>(malloc(sizeof(struct arbolBinario)));
    arbol->raiz = 0;
    return arbol;
}

struct nodoBinario* crearNodoBinario(int id){
    struct nodoBinario* nuevoNodo = static_cast<nodoBinario*>(malloc(sizeof(struct nodoBinario)));
    nuevoNodo->izq = 0;
    nuevoNodo->der = 0;
    nuevoNodo->id = id;
    nuevoNodo->fe = 0;
    nuevoNodo->altura = 0;
    nuevoNodo->nivel = 0;

    return nuevoNodo;
}

int insertarNodoBinario(nodoBinario* nodo,int id){
     // 1 insertar nodo
    // 0 si es igual
    if(nodo->id<id){
        if(nodo->der==0){
            struct nodoBinario* nuevo = crearNodoBinario(id);
            nodo->der = nuevo;
            return 1;
        }else{
            // metodo recursivo
            return insertarNodoBinario(nodo->der,id);
        }

    }else if(nodo->id>id){
        if(nodo->izq==0){
            struct nodoBinario* nuevo = crearNodoBinario(id);
            nodo->izq = nuevo;
            return 1;
        }else{
            // metodo recursivo
            return insertarNodoBinario(nodo->izq,id);
        }
    }else{
        return 0;
    }

}

int insertarArbolBinario(arbolBinario* arbol,int id){
    // 1 insertar nodo
    // 0 si es igual
    if(arbol->raiz==0){
        struct nodoBinario* nuevo = crearNodoBinario(id);
        arbol->raiz = nuevo;
        return 1;
    }

    if(arbol->raiz->id<id){

        if(arbol->raiz->der==0){
            struct nodoBinario* nuevo = crearNodoBinario(id);
            arbol->raiz->der = nuevo;
            return 1;
        }else{
            // metodo recursivo
            return insertarNodoBinario(arbol->raiz->der,id);
        }

    }else if(arbol->raiz->id>id){
        if(arbol->raiz->izq==0){
            struct nodoBinario* nuevo = crearNodoBinario(id);
            arbol->raiz->izq = nuevo;
            return 1;
        }else{
            // metodo recursivo
            return insertarNodoBinario(arbol->raiz->izq,id);
        }
    }else{
        return 0;
    }

}

void recorridoArbolRecursiva(nodoBinario* nodo,std::ofstream& archivo){


    if(nodo==0)return;

        archivo << "\t" << nodo->id << "[label=\"<p0>|" << nodo->id  << " \\n Nivel: " << nodo->nivel << "\\n FE: " << nodo->fe << "\\n Altura:" << nodo->altura << "|<p1>\"];" << std::endl;

    if(nodo->izq!=0){
        archivo << "\t" << nodo->id << ":p0 -> " << nodo->izq->id << ";" << std::endl;
    }

    if(nodo->der!=0){
        archivo << "\t" << nodo->id << ":p1 -> " << nodo->der->id << ";" << std::endl;
    }

    recorridoArbolRecursiva(nodo->izq,archivo);
    recorridoArbolRecursiva(nodo->der,archivo);

}

void recorridoArbol(arbolBinario* arbol){
    std::ofstream archivo_salida("arbol.dot");
    archivo_salida << "digraph g {" << std::endl;
    archivo_salida << "\tnode [shape=record,height=.08,fontsize=11];" << std::endl;
    recorridoArbolRecursiva(arbol->raiz,archivo_salida);
    archivo_salida << "}" << std::endl;
    archivo_salida.close();
    system("dot -Tjpg -O  arbol.dot");
}

struct nodoBinario* buscarNodoBinario(nodoBinario* nodo,int id){

     if(nodo==0){
        return 0;
    }

    if(nodo->id<id){

        if(nodo->der==0){
            return 0;
        }else{
            // metodo recursivo
            return buscarNodoBinario(nodo->der,id);
        }

    }else if(nodo->id>id){
        if(nodo->izq==0){
            return 0;
        }else{
            // metodo recursivo
            return buscarNodoBinario(nodo->izq,id);
        }
    }else{
        struct nodoBinario* nodoAux = nodo;
        return nodoAux;
    }

}

struct nodoBinario* buscarArbolBinario(arbolBinario* arbol,int id){

     if(arbol->raiz==0){
        return 0;
    }

    if(arbol->raiz->id<id){

        if(arbol->raiz->der==0){
            return 0;
        }else{
            // metodo recursivo
            return buscarNodoBinario(arbol->raiz->der,id);
        }

    }else if(arbol->raiz->id>id){
        if(arbol->raiz->izq==0){
            return 0;
        }else{
            // metodo recursivo
            return buscarNodoBinario(arbol->raiz->izq,id);
        }
    }else{
        struct nodoBinario* nodo = arbol->raiz;
        return nodo;
    }

}

int infoNodoBinario(nodoBinario* nodo, int nivelAnterior){
    if(nodo==0){
        return 0;
    }
    int izq = 0, der = 0, nivel = 0;
    nivel = nivelAnterior + 1;
    nodo->nivel = nivel;
    izq = izq + infoNodoBinario(nodo->izq,nivel);
    der = der + infoNodoBinario(nodo->der,nivel);

    if(izq>der){
        nodo->altura = izq + 1;
        nodo->fe = der - izq;
        return nodo->altura;
    }else if(der>izq){
        nodo->altura = der + 1;
        nodo->fe = der - izq;
        return nodo->altura;
    }else if(izq==der){
        nodo->altura = der + 1;
        nodo->fe = der - izq;
        return nodo->altura;
    }
    return 0;
}

void infoArbolBinario(arbolBinario* arbol){
    if(arbol->raiz==0){
        return;
    }

    int izq = 0, der = 0 ,nivel = 0;
    arbol->raiz->nivel = nivel;
    izq = izq + infoNodoBinario(arbol->raiz->izq,nivel);
    der = der + infoNodoBinario(arbol->raiz->der,nivel);

    if(izq>der){
        arbol->raiz->altura = izq + 1;
        arbol->raiz->fe = der - izq;
    }else if(der>izq){
        arbol->raiz->altura = der + 1;
        arbol->raiz->fe = der - izq;
    }else if(izq==der){
        arbol->raiz->altura = der + 1;
        arbol->raiz->fe = der - izq;
    }
}

struct nodoBinario* rotacionesNodoBinario(nodoBinario* nodo){
    if(nodo==0){
        return 0;
    }

    nodo->izq = rotacionesNodoBinario(nodo->izq);
    nodo->der = rotacionesNodoBinario(nodo->der);

    if(nodo->fe==2){
        if(nodo->der->fe==0||nodo->der->fe==1){
            //simple Derecha
            nodoBinario* auxIzq = nodo->der->izq;
            nodoBinario* auxDer = nodo->der;
            nodo->der = auxIzq;
            auxDer->izq = nodo;
            nodo = auxDer;
            return nodo;
        }else if(nodo->der->fe==-1){
            //Doble Derecha
            nodoBinario* Zizq = nodo->der->izq->izq;
            nodoBinario* ZDer = nodo->der->izq->der;
            nodoBinario* nodoRaiz = nodo->der->izq;
            nodoRaiz->izq = nodo;
            nodoRaiz->der = nodo->der;
            nodoRaiz->izq->der = Zizq;
            nodoRaiz->der->izq = ZDer;
            nodo = nodoRaiz;
            return nodo;
        }
    }else if(nodo->fe==-2){
        if(nodo->izq->fe==0||nodo->izq->fe==-1){
            //Simple Izquierda
            nodoBinario* auxY = nodo->izq;
            nodoBinario* auxYder = nodo->izq->der;
            auxY->der = nodo;
            nodo->izq = auxYder;
            nodo = auxY;
            return nodo;
        }else if(nodo->der->fe==1){
            //Doble Izquierda
            nodoBinario* Zizq = nodo->izq->der->izq;
            nodoBinario* ZDer = nodo->izq->der->der;
            nodoBinario* nodoRaiz = nodo->izq->der;
            nodoRaiz->izq = nodo->izq;
            nodoRaiz->der = nodo;
            nodoRaiz->izq->der = Zizq;
            nodoRaiz->der->izq = ZDer;
            nodo = nodoRaiz;
            return nodo;
        }
    }
    return nodo;


}

void rotacionesArbolBinario(arbolBinario* arbol){
    if(arbol->raiz==0){
        return;
    }

    arbol->raiz->izq = rotacionesNodoBinario(arbol->raiz->izq);
    arbol->raiz->der = rotacionesNodoBinario(arbol->raiz->der);

    if(arbol->raiz->fe==2){
        if(arbol->raiz->der->fe==0||arbol->raiz->der->fe==1){
           //simple Derecha
           nodoBinario* auxIzq = arbol->raiz->der->izq;
           nodoBinario* auxDer = arbol->raiz->der;
           arbol->raiz->der = auxIzq;
           auxDer->izq = arbol->raiz;
           arbol->raiz = auxDer;
        }else if(arbol->raiz->der->fe==-1){
            //Doble Derecha
            nodoBinario* Zizq = arbol->raiz->der->izq->izq;
            nodoBinario* ZDer = arbol->raiz->der->izq->der;
            nodoBinario* nodoRaiz = arbol->raiz->der->izq;
            nodoRaiz->izq = arbol->raiz;
            nodoRaiz->der = arbol->raiz->der;
            nodoRaiz->izq->der = Zizq;
            nodoRaiz->der->izq = ZDer;
            arbol->raiz = nodoRaiz;
        }
    }else if(arbol->raiz->fe==-2){
        if(arbol->raiz->izq->fe==0||arbol->raiz->izq->fe==-1){
            //Simple Izquierda
            nodoBinario* auxY = arbol->raiz->izq;
            nodoBinario* auxYder = arbol->raiz->izq->der;
            auxY->der = arbol->raiz;
            arbol->raiz->izq = auxYder;
            arbol->raiz = auxY;
        }else if(arbol->raiz->izq->fe==1){
            //Doble Izquierda
            nodoBinario* Zizq = arbol->raiz->izq->der->izq;
            nodoBinario* ZDer = arbol->raiz->izq->der->der;
            nodoBinario* nodoRaiz = arbol->raiz->izq->der;
            nodoRaiz->izq = arbol->raiz->izq;
            nodoRaiz->der = arbol->raiz;
            nodoRaiz->izq->der = Zizq;
            nodoRaiz->der->izq = ZDer;
            arbol->raiz = nodoRaiz;
        }
    }
}

#endif // ARBOLBINARIO_HPP_INCLUDED
