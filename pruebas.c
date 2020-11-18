#include "pa2m.h"
#include "abb.h"
#include <string.h>

#define MANZANA_ROJA 'R'
#define MANZANA_VERDE 'V'

typedef struct manzana {
    int peso;
    char color;
} manzana_t;

manzana_t* crear_manzana (int peso, char color) {
    manzana_t* manzana = malloc (sizeof(manzana_t));
    if(manzana){
        (*manzana).peso = peso;
        (*manzana).color = color;
    }
    return manzana;
}

void destructor_manzanas (void* manzana) {
    free(manzana);
}

int comparar_manzanas (void* manzana1, void* manzana2) {
    if ((*(manzana_t*) manzana1).peso > (*(manzana_t*) manzana2).peso){
        return 1;
    } else if ((*(manzana_t*) manzana1).peso < (*(manzana_t*) manzana2).peso){
        return -1;
    } else {
        return 0;
    }
}

void pruebas_creacion () {
    pa2m_nuevo_grupo ("   Pruebas de creacion   ");
    abb_t* arbol = NULL;

    pa2m_afirmar((arbol = arbol_crear (NULL, destructor_manzanas)) == NULL, "No puedo crear un arbol sin funcion de comparacion");

    pa2m_afirmar((arbol = arbol_crear (comparar_manzanas, NULL)) != NULL, "Puedo crear un arbol sin funcion de destruccion");
    pa2m_afirmar(arbol_vacio(arbol), "El arbol esta vacio");
    pa2m_afirmar((*arbol).comparador == comparar_manzanas, "La funcion de comparacion es correcta");
    pa2m_afirmar((*arbol).destructor == NULL, "La funcion de destruccion es NULL");
    arbol_destruir (arbol);

    pa2m_afirmar((arbol = arbol_crear (comparar_manzanas, destructor_manzanas)) != NULL, "Puedo crear un arbol con ambas funciones");
    pa2m_afirmar((*arbol).comparador == comparar_manzanas, "La funcion de comparacion es correcta");
    pa2m_afirmar((*arbol).destructor == destructor_manzanas, "La funcion de destruccion es correcta");
    arbol_destruir (arbol);
}

void pruebas_insercion () {
    pa2m_nuevo_grupo ("   Pruebas de insercion   ");
    abb_t* arbol = arbol_crear (comparar_manzanas, destructor_manzanas);
    manzana_t* manzana_insertar;
    manzana_insertar = crear_manzana(52, MANZANA_ROJA);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");
    manzana_insertar = crear_manzana(122, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");
    manzana_insertar = crear_manzana(513, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");
    manzana_insertar = crear_manzana(21, MANZANA_ROJA);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");
    manzana_insertar = crear_manzana(15, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");
    manzana_insertar = crear_manzana(76, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");
    manzana_insertar = crear_manzana(1, MANZANA_ROJA);
    pa2m_afirmar(arbol_insertar(arbol, manzana_insertar) == 0, "Puedo insertar una manzana");

    manzana_t* manzanas[10];

    size_t cantidad = arbol_recorrido_inorden(arbol, (void**)manzanas, 10);
    for(size_t i=0;i<cantidad;i++)
        printf("%i ", (*manzanas[i]).peso);
    printf("\n");
}

int main (){
    pruebas_creacion ();
    pruebas_insercion ();
    pa2m_mostrar_reporte ();
}