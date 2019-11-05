#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM_INICIAL 10
#define TAM_REDIMENSION_ARRIBA 2
#define TAM_REDIMENSION_ABAJO 2

/* Definición del struct pila proporcionado por la cátedra.*/
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

bool redimensionar(pila_t* pila, size_t tam_nuevo){

    void** datos_nuevo = realloc(pila->datos, sizeof(void*) * tam_nuevo);
    
    if (!datos_nuevo){
        return false;
    }

    pila->datos = datos_nuevo;
    return true;
}

pila_t* pila_crear(void){

    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL){
        return NULL;
    }

    pila->datos = malloc(sizeof(void*) * TAM_INICIAL);

    if (pila->datos == NULL){
        free(pila);
        return NULL;
    }

    pila->cantidad = 0;
    pila->capacidad = TAM_INICIAL;

    return pila;
}

void pila_destruir(pila_t *pila){

    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){

    if(pila->cantidad == 0){
        return true;
    }
    return false;
}

bool pila_apilar(pila_t *pila, void* valor){

    if (pila->cantidad == pila->capacidad){
    
        bool redimension = redimensionar(pila, (pila->capacidad * TAM_REDIMENSION_ARRIBA));

        if(!redimension){
            return false;
        }
        pila->capacidad = pila->capacidad * TAM_REDIMENSION_ARRIBA;
    }

    pila->datos[pila->cantidad] = valor;
    pila->cantidad ++;
    return true;
}

void* pila_ver_tope(const pila_t *pila){

    if (pila->cantidad == 0){
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){

    if (pila_esta_vacia(pila) == true){
        return NULL;
    }

    void* dato = pila->datos[pila->cantidad-1] ;
    pila->cantidad --; 

    if (pila->cantidad <= (pila->capacidad/4) && pila->capacidad > TAM_INICIAL){
        
        bool redimension = redimensionar(pila, (pila->capacidad / TAM_REDIMENSION_ABAJO));

        if (!redimension){
            return NULL;
        }
        pila->capacidad = pila->capacidad / TAM_REDIMENSION_ABAJO;
    }
    return dato;
}