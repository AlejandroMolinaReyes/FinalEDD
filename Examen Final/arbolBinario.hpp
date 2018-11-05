#ifndef ARBOLBINARIO_HPP_INCLUDED
#define ARBOLBINARIO_HPP_INCLUDED


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

void recorridoArbolRecursiva(nodoBinario* nodo,FILE* archivo){


    if(nodo==0)return;

    fprintf(archivo, "%s %i %s %i %s %i %s\n","\t",nodo->id,"[label=\"<p0>|", nodo->id,"\\nNivel:",nodo->nivel,"|<p1>\"];");

    if(nodo->izq!=0){
    	fprintf(archivo, "%s %i %s %i %s\n","\t",nodo->id , ":p0 -> " ,nodo->izq->id,";");
    }

    if(nodo->der!=0){
    	fprintf(archivo, "%s %i %s %i %s\n","\t",nodo->id , ":p1 -> " ,nodo->der->id,";");
    }

    recorridoArbolRecursiva(nodo->izq,archivo);
    recorridoArbolRecursiva(nodo->der,archivo);

}

void recorridoArbol(arbolBinario* arbol){
	remove("arbolSPL.dot");
	FILE* archivo;
	archivo = fopen("arbolSPL.dot","a");
	fprintf(archivo, "%s\n","digraph g {" );
	fprintf(archivo, "%s\n","\tnode [shape=record,height=.08,fontsize=11];" );
    recorridoArbolRecursiva(arbol->raiz,archivo);
    fprintf(archivo, "%s\n","}" );
    fclose(archivo);
    system("dot -Tjpg -O  arbolSPL.dot");
    system("arbolSPL.dot.jpg");
    
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

struct nodoBinario* rotacionesNodoBinario(nodoBinario* nodo, int id){
    if(nodo==0){
        return 0;
    }

    if(nodo->id<id){
        // der
        nodo->der = rotacionesNodoBinario(nodo->der,id);
        nodoBinario* nodoAux = nodo->der;
        nodoBinario* nodoAuxIzq = nodo->der->izq;
        nodoAux->izq = nodo;
        nodo->der = nodoAuxIzq;
        nodo  = nodoAux;
    }else if(nodo->id>id){
        // izq
        nodo->izq = rotacionesNodoBinario(nodo->izq,id);
        nodoBinario* nodoAux = nodo->izq;
        nodoBinario* nodoAuxDer = nodo->izq->der;
        nodoAux->der = nodo;
        nodo->izq = nodoAuxDer;
        nodo  = nodoAux;
    }
    return nodo;
}

void rotacionesArbolBinario(arbolBinario* arbol, int id){
    if(arbol->raiz==0){
        return;
    }
    
    if(arbol->raiz->id<id){
        // der
        arbol->raiz->der = rotacionesNodoBinario(arbol->raiz->der,id);
        nodoBinario* nodoAux = arbol->raiz->der;
        nodoBinario* nodoAuxIzq = arbol->raiz->der->izq;
        nodoAux->izq = arbol->raiz;
        arbol->raiz->der = nodoAuxIzq;
        arbol->raiz  = nodoAux;

    }else if(arbol->raiz->id>id){
        // izq
        arbol->raiz->izq = rotacionesNodoBinario(arbol->raiz->izq,id);
        nodoBinario* nodoAux = arbol->raiz->izq;
        nodoBinario* nodoAuxDer = arbol->raiz->izq->der;
        nodoAux->der = arbol->raiz;
        arbol->raiz->izq = nodoAuxDer;
        arbol->raiz  = nodoAux;
    }else{
        //break

    }
}

struct nodoBinario* arbolRemplazaNodo(nodoBinario* raiz, nodoBinario* nodo){
    if(nodo==0){
        return 0;
    }
    if(nodo->der==0){
        printf("%i %i \n",raiz->id,nodo->id);
        raiz->id = nodo->id;
        return nodo->izq;
    }
    nodo->der = arbolRemplazaNodo(raiz,nodo->der);
    return nodo;
}

struct nodoBinario* arbolEliminarNodo(nodoBinario* nodo,int id){

    if(nodo==0){
        return 0;
    }

    if(nodo->id<id){

        if(nodo->der==0){
            return 0;
        }else{
            // metodo recursivo
            nodo->der = arbolEliminarNodo(nodo->der,id);
            return nodo;
        }

    }else if(nodo->id>id){
        if(nodo->izq==0){
            return 0;
        }else{
            // metodo recursivo
            nodo->izq = arbolEliminarNodo(nodo->izq,id);
            return nodo;
        }
    }else{
        if(nodo->izq!=0){
            nodo->izq = arbolRemplazaNodo(nodo,nodo->izq);
        }else{
            nodo = nodo->der;
        }
        return nodo;
    }
    

}

void arbolEliminar(arbolBinario* arbol, int id){
    if(arbol->raiz==0){
        return;
    }

    if(arbol->raiz->id<id){

        if(arbol->raiz->der==0){
            return;
        }else{
            // metodo recursivo
            arbol->raiz->der = arbolEliminarNodo(arbol->raiz->der,id);
        }

    }else if(arbol->raiz->id>id){
        if(arbol->raiz->izq==0){
            return;
        }else{
            // metodo recursivo
            arbol->raiz->izq = arbolEliminarNodo(arbol->raiz->izq,id);
        }
    }else{
        if(arbol->raiz->izq!=0){
            arbol->raiz->izq = arbolRemplazaNodo(arbol->raiz,arbol->raiz->izq);
        }else{
            arbol->raiz = arbol->raiz->der;
        }
         
    }
}

#endif // ARBOLBINARIO_HPP_INCLUDED
