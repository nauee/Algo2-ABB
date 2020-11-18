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

void pruebas_insercion_y_borrado () {
    pa2m_nuevo_grupo ("   Pruebas de insercion y borrado   ");
    abb_t* arbol = arbol_crear (comparar_manzanas, destructor_manzanas);
    manzana_t* manzana_aux;
    manzana_aux = crear_manzana(52, MANZANA_ROJA);
    pa2m_afirmar(arbol_insertar(NULL, manzana_aux) == -1, "No puedo insertar en un arbol NULL");
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana roja (52g)");
    manzana_aux = crear_manzana(122, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana verde (122g)");
    manzana_aux = crear_manzana(513, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana verde (513g)");
    manzana_aux = crear_manzana(21, MANZANA_ROJA);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana roja (21g)");
    manzana_aux = crear_manzana(15, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana verde (15g)");
    manzana_aux = crear_manzana(76, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana verde (76g)");
    manzana_aux = crear_manzana(1, MANZANA_ROJA);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana roja (1g)");
    manzana_aux = crear_manzana(90, MANZANA_VERDE);
    pa2m_afirmar(arbol_insertar(arbol, manzana_aux) == 0, "Puedo insertar una manzana roja (90g)");

    manzana_t* manzanas[10];
    size_t cantidad = arbol_recorrido_inorden(arbol, (void**)manzanas, 10);
    bool son_todos_correctos = (*manzanas[0]).peso == 1 && (*manzanas[1]).peso == 15 && (*manzanas[2]).peso == 21 && (*manzanas[3]).peso == 52 &&
                               (*manzanas[4]).peso == 76 && (*manzanas[5]).peso == 90 && (*manzanas[6]).peso == 122 && (*manzanas[7]).peso == 513;
    pa2m_afirmar(cantidad == 8, "Hay 8 manzanas");
    pa2m_afirmar(son_todos_correctos,"Todas las manzanas son correctas, probando con recorrido inorden");
    
    manzana_aux = crear_manzana (9999, MANZANA_ROJA);
    pa2m_afirmar(arbol_borrar(NULL, manzana_aux) == -1, "No puedo borrar un elemento que no esta en el arbol");
    (*manzana_aux).color = MANZANA_ROJA;
    (*manzana_aux).peso = 52;
    pa2m_afirmar(arbol_borrar(NULL, manzana_aux) == -1, "No puedo borrar en una arbol NULL");
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar la raiz");
    (*manzana_aux).color = MANZANA_ROJA;
    (*manzana_aux).peso = 1;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar una hoja");
    (*manzana_aux).color = MANZANA_VERDE;
    (*manzana_aux).peso = 76;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar un nodo con un hijo");
    (*manzana_aux).color = MANZANA_VERDE;
    (*manzana_aux).peso = 122;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar un nodo con dos hijos");

    cantidad = arbol_recorrido_preorden(arbol, (void**)manzanas, 10);
    son_todos_correctos = (*manzanas[0]).peso == 21 && (*manzanas[1]).peso == 15 && (*manzanas[2]).peso == 90 && (*manzanas[3]).peso == 513;
    pa2m_afirmar(cantidad == 4, "Quedan 4 manzanas");
    pa2m_afirmar(son_todos_correctos,"Todas las manzanas restantes son correctas, probando con recorrido preorden");

    (*manzana_aux).color = MANZANA_ROJA;
    (*manzana_aux).peso = 21;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar la raiz");
    (*manzana_aux).color = MANZANA_VERDE;
    (*manzana_aux).peso = 513;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar una hoja");
    (*manzana_aux).color = MANZANA_VERDE;
    (*manzana_aux).peso = 90;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar otra hoja");
    (*manzana_aux).color = MANZANA_VERDE;
    (*manzana_aux).peso = 15;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar el ultimo elemento");
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == -1, "No puedo borrar en un arbol vacio");
    cantidad = arbol_recorrido_inorden(arbol, (void**)manzanas, 10);
    pa2m_afirmar(cantidad == 0, "Quedan 0 manzanas");
    pa2m_afirmar(arbol_vacio (arbol), "El arbol esta vacio");
    destructor_manzanas (manzana_aux);
    arbol_destruir(arbol);
}

int main (){
    pruebas_creacion ();
    pruebas_insercion_y_borrado ();
    pa2m_mostrar_reporte ();
}