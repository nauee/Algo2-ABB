#include "abb.h"

/******************************************************************************************** Arbol_crear ********************************************************************************************/

/*
typedef struct abb{
  nodo_abb_t* nodo_raiz;
  abb_comparador comparador;
  abb_liberar_elemento destructor;
} abb_t;

typedef struct nodo_abb {
  void* elemento;
  struct nodo_abb* izquierda;
  struct nodo_abb* derecha;
} nodo_abb_t;
*/

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    
    if (!comparador) {
        return NULL;
    }

    abb_t* arbol = malloc (sizeof(abb_t));
    if (!arbol) {
        return NULL;
    }

    (*arbol).nodo_raiz = NULL;
    (*arbol).comparador = comparador;
    (*arbol).destructor = destructor;
    return arbol;

}

/****************************************************************************************** Arbol_insertar *******************************************************************************************/

nodo_abb_t* crear_nodo (void* elemento) {

    nodo_abb_t* nodo = calloc (1, sizeof(nodo_abb_t));
    if (!nodo) {
        return NULL;
    } else {
        (*nodo).elemento = elemento;
        (*nodo).izquierda = NULL;
        (*nodo).derecha = NULL;
        return nodo;
    }

}

int insertar_elemento (nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador) {
    
    int comparacion = comparador (elemento, (*nodo_actual).elemento);

    if (comparacion > 0){
        if (!(*nodo_actual).derecha){
            nodo_abb_t* nodo = crear_nodo (elemento);
            if(!nodo){
                return -1;
            }
            (*nodo_actual).derecha = nodo;
            return 0;
        } else {
            return insertar_elemento ((*nodo_actual).derecha, elemento, comparador);
        }
    } else {
        if (!(*nodo_actual).izquierda){
            nodo_abb_t* nodo = crear_nodo (elemento);
            if(!nodo){
                return -1;
            }
            (*nodo_actual).izquierda = nodo;
            return 0;
        } else {
            return insertar_elemento ((*nodo_actual).izquierda, elemento, comparador);
        }
    }

}

int arbol_insertar(abb_t* arbol, void* elemento){
    if (!arbol) {
        return -1;
    }

    if(!(*arbol).nodo_raiz) {
        nodo_abb_t* nodo = crear_nodo (elemento);
        if(!nodo){
            return -1;
        }
        (*arbol).nodo_raiz = nodo;
        return 0;
    }

    return insertar_elemento ((*arbol).nodo_raiz, elemento, (*arbol).comparador);

}

/******************************************************************************************* Arbol_borrar ********************************************************************************************/

int borrar_elemento (nodo_abb_t* padre, nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador, abb_liberar_elemento destructor){

    if(!nodo_actual){
        return -1;
    }

    int comparacion = comparador (elemento, (*nodo_actual).elemento);
    if (comparacion == 0){
        if (!(*nodo_actual).izquierda && !(*nodo_actual).derecha){
            return borrar_nodo_hoja(nodo_actual, elemento, destructor);
        } else if (!(*nodo_actual).izquierda && !(*nodo_actual).derecha)
    }

}

int arbol_borrar(abb_t* arbol, void* elemento){
    if (!arbol || !elemento) {
        return -1;
    }

    return borrar_elemento (NULL, (*arbol).nodo_raiz, elemento, (*arbol).comparador, (*arbol).destructor);

}

/******************************************************************************************* Arbol_buscar ********************************************************************************************/

void* buscar_nodo (nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador) {
    
    if (!nodo_actual){
        return NULL;
    }
    int comparacion = comparador (elemento, (*nodo_actual).elemento);
    if (comparacion == 0){
        return (*nodo_actual).elemento;
    } else if (comparacion > 0){
        return buscar_nodo ((*nodo_actual).derecha, elemento, comparador);
    } else {
        return buscar_nodo ((*nodo_actual).izquierda, elemento, comparador);
    }
    
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol){
        return NULL;
    }
    return buscar_nodo ((*arbol).nodo_raiz, elemento, (*arbol).comparador);
}

/******************************************************************************************** Arbol_raiz *********************************************************************************************/

void* arbol_raiz(abb_t* arbol){
    
    if (!arbol){
        return NULL;
    }
    return (*(*arbol).nodo_raiz).elemento;

}

/******************************************************************************************* Arbol_vacio *********************************************************************************************/

bool arbol_vacio(abb_t* arbol){
    return true;
}

/************************************************************************************* Arbol_recorrido_inorden ***************************************************************************************/

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    return 0;
}

/************************************************************************************ Arbol_recorrido_preorden ***************************************************************************************/

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    return 0;
}

/*********************************************************************************** Arbol_recorrido_postorden ***************************************************************************************/

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    return 0;
}

/****************************************************************************************** Arbol_destruir *******************************************************************************************/

void arbol_destruir(abb_t* arbol){
    return;
}

/************************************************************************************** Abb_con_cada_elemento ****************************************************************************************/

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    return 0;
}
/*****************************************************************************************************************************************************************************************************/