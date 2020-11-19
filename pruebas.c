#include "pa2m.h"
#include "abb.h"
#include <string.h>

#define MANZANA_ROJA "Roja"
#define MANZANA_VERDE "Verde"
#define MAX_COLOR 5

typedef struct manzana {
    int peso;
    char color[MAX_COLOR];
} manzana_t;

manzana_t* crear_manzana (int peso, char* color) {
    manzana_t* manzana = malloc (sizeof(manzana_t));
    if(manzana){
        (*manzana).peso = peso;
        strcpy((*manzana).color, color);
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

int comparar_caracteres (void* entero1, void* entero2){
    if (*(char*) entero1 > *(char*) entero2){
        return 1;
    } else if (*(char*) entero1 < *(char*) entero2){
        return -1;
    } else {
        return 0;
    }
}

void pruebas_creacion () {
    printf("\n");
    pa2m_nuevo_grupo ("   Pruebas de creacion   ");
    printf("\n");
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

void pruebas_insertar (abb_t* arbol) {
    
    pa2m_nuevo_grupo ("   Pruebas de insertar   ");

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
}

void pruebas_buscar_y_raiz (abb_t* arbol) {

    pa2m_nuevo_grupo ("   Pruebas de busqueda   ");

    abb_t* arbol_vacio = arbol_crear (comparar_manzanas, destructor_manzanas);
    manzana_t* manzana_aux = crear_manzana (513, MANZANA_VERDE);
    pa2m_afirmar(strcmp((*(manzana_t*)(arbol_raiz(arbol))).color, MANZANA_ROJA) == 0 && (*(manzana_t*)(arbol_raiz(arbol))).peso == 52, "La raiz del arbol es la correcta");
    pa2m_afirmar(arbol_raiz(NULL) == NULL, "No puedo ver la raiz de un arbol inexistente");
    pa2m_afirmar(arbol_raiz(arbol_vacio) == NULL, "Un arbol vacio no tiene raiz");
    pa2m_afirmar(arbol_buscar(NULL, manzana_aux) == NULL, "No puedo buscar en un arbol inexistente");
    pa2m_afirmar(arbol_buscar(arbol, NULL) == NULL, "No puedo buscar sin un elemento de busqueda");
    pa2m_afirmar(arbol_buscar(arbol, manzana_aux) != NULL, "Puedo encontrar una manzana verde (513g)");
    strcpy((*manzana_aux).color, MANZANA_ROJA);
    (*manzana_aux).peso = 3;
    pa2m_afirmar(arbol_buscar(arbol, manzana_aux) == NULL, "No puedo encontrar una manzana roja (3g) porque no esta en el arbol");
    (*manzana_aux).peso = 21;
    pa2m_afirmar(arbol_buscar(arbol, manzana_aux) != NULL, "Puedo encontrar una manzana roja (21g)");
    pa2m_afirmar(arbol_buscar(arbol_vacio, manzana_aux) == NULL, "No puedo buscar en un arbol vacio");
    destructor_manzanas(manzana_aux);
    arbol_destruir(arbol_vacio);

}

void pruebas_borrar (abb_t* arbol) {

    pa2m_nuevo_grupo("   Pruebas de borrado   ");
    manzana_t *manzana_aux = crear_manzana (9999, MANZANA_ROJA);
    pa2m_afirmar(arbol_borrar(NULL, manzana_aux) == -1, "No puedo borrar un elemento que no esta en el arbol");
    strcpy((*manzana_aux).color, MANZANA_ROJA);
    (*manzana_aux).peso = 52;
    pa2m_afirmar(arbol_borrar(NULL, manzana_aux) == -1, "No puedo borrar en una arbol NULL");
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar la raiz");
    strcpy((*manzana_aux).color, MANZANA_ROJA);
    (*manzana_aux).peso = 1;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar una hoja");

    manzana_t* manzanas[10];
    size_t cantidad = arbol_recorrido_postorden(arbol, (void**)manzanas, 10);
    bool son_todos_correctos = (*manzanas[0]).peso == 15 && (*manzanas[1]).peso == 90 && (*manzanas[2]).peso == 76 && (*manzanas[3]).peso == 513 &&
                               (*manzanas[4]).peso == 122 && (*manzanas[5]).peso == 21;
    pa2m_afirmar(cantidad == 6, "Quedan 6 manzanas");
    pa2m_afirmar(son_todos_correctos,"Todas las manzanas restantes son correctas, probando con recorrido postorden");

    strcpy((*manzana_aux).color, MANZANA_VERDE);
    (*manzana_aux).peso = 76;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar un nodo con un hijo");
    strcpy((*manzana_aux).color, MANZANA_VERDE);
    (*manzana_aux).peso = 122;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar un nodo con dos hijos");

    cantidad = arbol_recorrido_preorden(arbol, (void**)manzanas, 10);
    son_todos_correctos = (*manzanas[0]).peso == 21 && (*manzanas[1]).peso == 15 && (*manzanas[2]).peso == 90 && (*manzanas[3]).peso == 513;
    pa2m_afirmar(cantidad == 4, "Quedan 4 manzanas");
    pa2m_afirmar(son_todos_correctos,"Todas las manzanas restantes son correctas, probando con recorrido preorden");

    strcpy((*manzana_aux).color, MANZANA_ROJA);
    (*manzana_aux).peso = 21;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar la raiz");
    strcpy((*manzana_aux).color, MANZANA_VERDE);
    (*manzana_aux).peso = 513;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar una hoja");
    strcpy((*manzana_aux).color, MANZANA_VERDE);
    (*manzana_aux).peso = 90;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar otra hoja");
    strcpy((*manzana_aux).color, MANZANA_VERDE);
    (*manzana_aux).peso = 15;
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == 0, "Puedo borrar el ultimo elemento");
    pa2m_afirmar(arbol_borrar(arbol, manzana_aux) == -1, "No puedo borrar en un arbol vacio");
    cantidad = arbol_recorrido_inorden(arbol, (void**)manzanas, 10);
    pa2m_afirmar(cantidad == 0, "Quedan 0 manzanas");
    pa2m_afirmar(arbol_vacio (arbol), "El arbol esta vacio");
    destructor_manzanas (manzana_aux);
}

void pruebas_funcionamiento_general () {
    
    printf("\n");
    pa2m_nuevo_grupo ("   Pruebas de funcionamiento general   ");
    printf("\n");
    abb_t* arbol = arbol_crear (comparar_manzanas, destructor_manzanas);
    pruebas_insertar (arbol);
    pruebas_buscar_y_raiz (arbol);
    pruebas_borrar (arbol);
    arbol_destruir(arbol);
}

bool copiar_a_string (void* elemento, void* salida) {
    if (elemento) {
        char buffer[100] = "";
        sprintf (buffer, "%s - %i | ", (*(manzana_t*)elemento).color, (*(manzana_t*)elemento).peso);
        strcat ((char*) salida, buffer);
    }
    return false;
}

bool copiar_a_string_hasta_5 (void* elemento, void* salida) {
    if (elemento) {
        int cantidad_leida = -1;
        int i = 0;
        while (((char*)salida)[i]) {
            if (((char*)salida)[i] == '|') {
                cantidad_leida ++;
            }
            i++;
        }
        if (cantidad_leida >= 5) {
            return true;
        }
        char buffer[100] = "";
        sprintf (buffer, "%s - %i | ", (*(manzana_t*)elemento).color, (*(manzana_t*)elemento).peso);
        strcat ((char*) salida, buffer);
    }
    return false;
}

bool copiar_a_string_hasta_3_verdes (void* elemento, void* salida) {
    
    int manzanas_verdes = 0;
    int i = 0;
    while (((char*)salida)[i]) {
        if ((((char*)salida)[i] == 'V')) {
            manzanas_verdes ++;
        }
        i++;
    }
    if (manzanas_verdes == 3) {
        return true;
    }

    if (elemento) {
        char buffer[100] = "";
        sprintf (buffer, "%s - %i | ", (*(manzana_t*)elemento).color, (*(manzana_t*)elemento).peso);
        strcat ((char*) salida, buffer);
    }
    return false;
}

void pruebas_iterador_interno () {

    printf("\n");
    pa2m_nuevo_grupo("   Pruebas iterador interno   ");
    printf("\n");

    abb_t* arbol = arbol_crear (comparar_manzanas, destructor_manzanas);
    abb_t* arbol_vacio = arbol_crear (comparar_manzanas, destructor_manzanas);
    char salida[1000] = "| ";
    char esperado[1000] = "";
    manzana_t* manzana_aux;
    size_t cantidad;
    manzana_aux = crear_manzana (258, MANZANA_ROJA);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (120, MANZANA_VERDE);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (425, MANZANA_VERDE);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (535, MANZANA_ROJA);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (122, MANZANA_ROJA);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (222, MANZANA_VERDE);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (99, MANZANA_VERDE);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (112, MANZANA_VERDE);
    arbol_insertar(arbol, manzana_aux);
    manzana_aux = crear_manzana (87, MANZANA_ROJA);
    arbol_insertar(arbol, manzana_aux);

    pa2m_afirmar (abb_con_cada_elemento (NULL, ABB_RECORRER_INORDEN, copiar_a_string, salida) == 0, "No puedo recorrer un arbol inexistente");
    pa2m_afirmar (abb_con_cada_elemento (arbol, 4, copiar_a_string, salida) == 0, "No puedo recorrer con un recorrido invalido");
    pa2m_afirmar (abb_con_cada_elemento (arbol, ABB_RECORRER_INORDEN, NULL, salida) == 0, "No puedo recorrer sin funcion de iteracion");
    pa2m_afirmar (abb_con_cada_elemento (arbol_vacio, ABB_RECORRER_INORDEN, copiar_a_string, salida) == 0, "Recorrer un arbol vacio devuelve 0 elemento");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_INORDEN, copiar_a_string, salida);
    strcpy (esperado, "| Roja - 87 | Verde - 99 | Verde - 112 | Verde - 120 | Roja - 122 | Verde - 222 | Roja - 258 | Verde - 425 | Roja - 535 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 9, "Recorrido inorden del arbol completo correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_PREORDEN, copiar_a_string, salida);
    strcpy (esperado, "| Roja - 258 | Verde - 120 | Verde - 99 | Roja - 87 | Verde - 112 | Roja - 122 | Verde - 222 | Verde - 425 | Roja - 535 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 9, "Recorrido preorden del arbol completo correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_POSTORDEN, copiar_a_string, salida);
    strcpy (esperado, "| Roja - 87 | Verde - 112 | Verde - 99 | Verde - 222 | Roja - 122 | Verde - 120 | Roja - 535 | Verde - 425 | Roja - 258 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 9, "Recorrido postorden del arbol completo correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_INORDEN, copiar_a_string_hasta_5, salida);
    strcpy (esperado, "| Roja - 87 | Verde - 99 | Verde - 112 | Verde - 120 | Roja - 122 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 5, "Recorrido inorden del arbol hasta 5 elementos correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_PREORDEN, copiar_a_string_hasta_5, salida);
    strcpy (esperado, "| Roja - 258 | Verde - 120 | Verde - 99 | Roja - 87 | Verde - 112 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 5, "Recorrido preorden del arbol hasta 5 elementos correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_POSTORDEN, copiar_a_string_hasta_5, salida);
    strcpy (esperado, "| Roja - 87 | Verde - 112 | Verde - 99 | Verde - 222 | Roja - 122 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 5, "Recorrido postorden del arbol hasta 5 elementos correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_INORDEN, copiar_a_string_hasta_3_verdes, salida);
    strcpy (esperado, "| Roja - 87 | Verde - 99 | Verde - 112 | Verde - 120 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 4, "Recorrido inorden del arbol hasta encontrar 3 manzanas verdes correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_PREORDEN, copiar_a_string_hasta_3_verdes, salida);
    strcpy (esperado, "| Roja - 258 | Verde - 120 | Verde - 99 | Roja - 87 | Verde - 112 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 5, "Recorrido preorden del arbol hasta encontrar 3 manzanas verdes correcto");
    strcpy (salida, "| ");

    cantidad = abb_con_cada_elemento (arbol, ABB_RECORRER_POSTORDEN, copiar_a_string_hasta_3_verdes, salida);
    strcpy (esperado, "| Roja - 87 | Verde - 112 | Verde - 99 | Verde - 222 | ");
    pa2m_afirmar (strcmp (esperado, salida) == 0 && cantidad == 4, "Recorrido postorden del arbol hasta encontrar 3 manzanas verdes correcto");
    strcpy (salida, "| ");

    arbol_destruir (arbol);
    arbol_destruir (arbol_vacio);

}

int main (){
    pruebas_creacion ();
    pruebas_funcionamiento_general ();
    pruebas_iterador_interno ();
    pa2m_mostrar_reporte ();
}