#include "pa2m.h"
#include "abb.h"

void destructor_enteros (void* entero) {
    free(entero);
}

int comparar_enteros (void* entero1, void* entero2) {
    if (*(int*)entero1 > *(int*)entero2){
        return 1;
    } else if (*(int*)entero1 < *(int*)entero2){
        return -1;
    } else {
        return 0;
    }
}

void pruebas_creacion(){
    pa2m_nuevo_grupo ("   Pruebas de creacion   ");
    abb_t* arbol = NULL;

    pa2m_afirmar((arbol = arbol_crear (NULL, destructor_enteros)) == NULL, "No puedo crear un arbol sin funcion de comparacion");

    pa2m_afirmar((arbol = arbol_crear (comparar_enteros, NULL)) != NULL, "Puedo crear un arbol sin funcion de destruccion");
    pa2m_afirmar((*arbol).nodo_raiz == NULL, "El nodo raiz es NULL");
    pa2m_afirmar((*arbol).comparador == comparar_enteros, "La funcion de comparacion es correcta");
    pa2m_afirmar((*arbol).destructor == NULL, "La funcion de destruccion es NULL");
    free (arbol);
    
    pa2m_afirmar((arbol = arbol_crear (comparar_enteros, destructor_enteros)) != NULL, "Puedo crear un arbol con ambas funciones");
    pa2m_afirmar((*arbol).nodo_raiz == NULL, "El nodo raiz es NULL");
    pa2m_afirmar((*arbol).comparador == comparar_enteros, "La funcion de comparacion es correcta");
    pa2m_afirmar((*arbol).destructor == destructor_enteros, "La funcion de destruccion es correcta");
    free (arbol);
}

int main (){
    pruebas_creacion ();
    pa2m_mostrar_reporte ();
}