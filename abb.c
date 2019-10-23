#include "abb.h"
#include <stdlib.h>

/*definición del struct nodo */
typedef struct n_abb{
    struct n_abb* izq;
    struct n_abb* der;
    void* dato;
    const char* clave;
}n_abb_t; 

/* Definición del struct ab.*/
struct abb {
    n_abb_t* raiz;
    abb_comparar_clave_t abb_comparar_clave;
    abb_destruir_dato_t abb_destruir_dato;
    size_t cant;
};

/*Definición del struct iterador.*/
struct abb_iter{

};

/*prototipos de funciones nuestras*/
n_abb_t* crear_nodo(const char* clave,void*dato);
bool abb_buscar(const abb_t* arbol, const char* clave);

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

/*funciones cátedra */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;

    abb->raiz = NULL;
    abb->abb_comparar_clave = cmp;
    abb->abb_destruir_dato = destruir_dato;
    abb->cant = 0;

    return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

    if(!arbol){
        n_abb_t* nuevo_nodo = crear_nodo(clave, dato);
        if(!nuevo_nodo) return false;
        arbol->raiz = nuevo_nodo;
    }else{
        const char* raiz = arbol->raiz->clave;
        if(arbol->abb_comparar_clave(raiz, clave) == 0){
            arbol->abb_destruir_dato(arbol->raiz->dato);
            arbol->raiz->dato = dato;
        }else if(arbol->abb_comparar_clave(raiz, clave) > 0){
            abb_guardar(arbol->raiz->izq, clave, dato);
        }else{
            abb_guardar(arbol->raiz->der, clave, dato);
        }
    }
    arbol->cant++;
    return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){

}

void *abb_obtener(const abb_t *arbol, const char *clave){

    if(!arbol) return NULL;
    if(abb_buscar(arbol, clave)) return arbol->raiz->dato;
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){

    if (!arbol) return false;
    if (!abb_buscar(arbol, clave)) return true;
    return false;
}

size_t abb_cantidad(abb_t *arbol){
    
    return arbol->cant;
}

void abb_destruir(abb_t *arbol){

    if (!arbol) return NULL;
    if (!arbol->raiz->izq && !arbol->raiz->der){
        arbol->abb_destruir_dato(arbol->raiz->dato);
        abb_borrar(arbol, arbol->raiz); //ESTO ESTA BIEN???
        free(arbol); //ESTO VA???
    }else if (arbol->raiz->izq){
        abb_destruir(arbol->raiz->izq);
    }else{
        abb_destruir(arbol->raiz->der);
    }
}

/*funciones nuestras*/
n_abb_t* crear_nodo(const char* clave,void*dato){

    n_abb_t* nuevo_nodo = malloc(sizeof(n_abb_t));
    if (! nuevo_nodo) return NULL;

    nuevo_nodo->clave = clave;
    nuevo_nodo->dato = dato;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->der = NULL;

    return nuevo_nodo; 
}

bool abb_buscar(const abb_t* arbol, const char* clave){

    if(!arbol) return false;
    if (arbol->abb_comparar_clave(arbol->raiz->clave, clave) == 0) return true;
    else if (arbol->abb_comparar_clave(arbol->raiz->clave, clave) > 0){
        return abb_buscar(arbol->raiz->clave, clave);   
    }else{
        return abb_buscar(arbol->raiz->der, clave);
    }
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

}

bool abb_iter_in_avanzar(abb_iter_t *iter){

}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

}

bool abb_iter_in_al_final(const abb_iter_t *iter){

}

void abb_iter_in_destruir(abb_iter_t* iter){

}