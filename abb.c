#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#include <stdio.h>

typedef enum tipo_hijo {HIJO_DER, HIJO_IZQ, RAIZ} tipo_hijo_t;

/*definición del struct nodo */
typedef struct n_abb{
    struct n_abb* izq;
    struct n_abb* der;
    void* dato;
    char* clave;
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
    pila_t* pila;
    const abb_t* abb;
};

/*prototipos de funciones nuestras*/
n_abb_t* crear_nodo(char* clave,void*dato);
n_abb_t* abb_buscar(n_abb_t* raiz, abb_comparar_clave_t abb_comparar_clave, const char* clave);
void enlazar_nodos(abb_t* arbol, n_abb_t* padre, n_abb_t* hijo, tipo_hijo_t posicion);
n_abb_t* buscar_padre(n_abb_t* raiz, n_abb_t* padre, const char* clave, abb_comparar_clave_t abb_comparar_clave);
bool _abb_guardar(abb_t* arbol, n_abb_t* raiz, const char* clave, void* dato, n_abb_t* padre);
void _abb_destruir(n_abb_t* raiz, abb_t* arbol);

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

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    if (!arbol) return false;
    return _abb_guardar(arbol, arbol->raiz, clave, dato, NULL);
}

bool _abb_guardar(abb_t* arbol, n_abb_t* raiz, const char* clave, void* dato, n_abb_t* padre) {
    if (!raiz) { // Caso nuevo nodo
        n_abb_t* aux = crear_nodo(strdup(clave), dato);
        if (!aux) return false;
        if (!padre) arbol->raiz = aux; // Caso raíz
        else if (arbol->abb_comparar_clave(clave, padre->clave) > 0) padre->der = aux; // Caso mayor que su padre
        else padre->izq = aux; // Caso menor que su padre
        arbol->cant++;
        return true;
    }
    if (arbol->abb_comparar_clave(raiz->clave, clave) == 0) { // Caso reemplazar
        if (arbol->abb_destruir_dato) arbol->abb_destruir_dato(raiz->dato);
        raiz->dato = dato;
        return true;
    }
    if (arbol->abb_comparar_clave(raiz->clave, clave) < 0) return _abb_guardar(arbol, raiz->der, clave, dato, raiz);
    return _abb_guardar(arbol, raiz->izq, clave, dato, raiz);
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    if (!abb_pertenece(arbol, clave)) return NULL;
    n_abb_t* padre = buscar_padre(arbol->raiz, NULL, clave, arbol->abb_comparar_clave);
    n_abb_t* nodo;
    tipo_hijo_t tipo_hijo;
    if (!padre) {
        nodo = arbol->raiz;
        tipo_hijo = RAIZ;
    } else if (padre->izq && arbol->abb_comparar_clave(padre->izq->clave, clave) == 0) {
        nodo = padre->izq;
        tipo_hijo = HIJO_IZQ;
    } else {
        nodo = padre->der;
        tipo_hijo = HIJO_DER;
    }
    void* dato = nodo->dato;

    /* Caso sin hijos */
    if (!nodo->izq && !nodo->der) {
        enlazar_nodos(arbol, padre, NULL, tipo_hijo);
        free(nodo->clave);
        free(nodo);
        arbol->cant--;
    }

    /* Caso con un hijo */
    else if((!nodo->izq && nodo->der) || (nodo->izq && !nodo->der)) {
        if (nodo->izq) enlazar_nodos(arbol, padre, nodo->izq, tipo_hijo);
        else enlazar_nodos(arbol, padre, nodo->der, tipo_hijo);
        free(nodo->clave);
        free(nodo);
        arbol->cant--;

    /* Caso dos hijos */
    } else {
        n_abb_t* reemplazante = nodo->der;
        while (reemplazante->izq) reemplazante = reemplazante->izq;
        char* clave_reemp = strdup(reemplazante->clave);
        void* dato_reemp = abb_borrar(arbol, reemplazante->clave);
        free(nodo->clave);
        nodo->clave = clave_reemp;
        nodo->dato = dato_reemp;
    }
    return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
    if (!arbol) return NULL;
    n_abb_t* nodo = abb_buscar(arbol->raiz, arbol->abb_comparar_clave, clave);
    if (nodo) return nodo->dato;
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if (!arbol) return false;
    return abb_buscar(arbol->raiz, arbol->abb_comparar_clave, clave) != NULL;
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}

void abb_destruir(abb_t *arbol){
    if (!arbol) return;
    _abb_destruir(arbol->raiz, arbol);
    free(arbol);
}

void _abb_destruir(n_abb_t* raiz, abb_t* arbol){
    if (!raiz) return;
    _abb_destruir(raiz->izq, arbol);
    _abb_destruir(raiz->der, arbol);
    void* dato = abb_borrar(arbol, raiz->clave);
    if (arbol->abb_destruir_dato) arbol->abb_destruir_dato(dato);   
}

/*funciones nuestras*/
n_abb_t* crear_nodo(char* clave, void* dato) {
    n_abb_t* nuevo_nodo = malloc(sizeof(n_abb_t));
    if (!nuevo_nodo) return NULL;
    nuevo_nodo->clave = clave;
    nuevo_nodo->dato = dato;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->der = NULL;
    return nuevo_nodo; 
}

n_abb_t* abb_buscar(n_abb_t* raiz, abb_comparar_clave_t abb_comparar_clave, const char* clave){
    if (!raiz) return NULL;
    if (abb_comparar_clave(clave, raiz->clave) == 0) return raiz;
    if (abb_comparar_clave(clave, raiz->clave) < 0) return abb_buscar(raiz->izq, abb_comparar_clave, clave);
    return abb_buscar(raiz->der, abb_comparar_clave, clave);
}

void enlazar_nodos(abb_t* arbol, n_abb_t* padre, n_abb_t* hijo, tipo_hijo_t posicion) {
    if (posicion == RAIZ) arbol->raiz = hijo;
    else if (posicion == HIJO_IZQ) padre->izq = hijo;
    else padre->der = hijo;
}
/*
  Precondición: el nodo debe pertenecer al árbol para hallar a su padre.
*/
n_abb_t* buscar_padre(n_abb_t* raiz, n_abb_t* padre, const char* clave, abb_comparar_clave_t abb_comparar_clave) {
    if (!raiz) return NULL;
    if (abb_comparar_clave(clave, raiz->clave) < 0) return buscar_padre(raiz->izq, raiz, clave, abb_comparar_clave);
    if (abb_comparar_clave(clave, raiz->clave) == 0) return padre;
    return buscar_padre(raiz->der, raiz, clave, abb_comparar_clave);
}

void _abb_in_order(n_abb_t* raiz, bool visitar(const char*, void *, void *), void *extra) {
    if (!raiz) return;
    _abb_in_order(raiz->izq, visitar, extra);
    if (!visitar(raiz->clave, raiz->dato, extra)) return;
    _abb_in_order(raiz->der, visitar, extra);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    _abb_in_order(arbol->raiz, visitar, extra);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){

    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;
    iter->pila = pila_crear();
    if (!iter->pila){
        free(iter);
        return NULL;
    }
    iter->abb = arbol;
    if (arbol->raiz) {
        pila_apilar(iter->pila, iter->abb->raiz);
        while (((n_abb_t*)pila_ver_tope(iter->pila))->izq){
            n_abb_t* nodo = ((n_abb_t*)pila_ver_tope(iter->pila))->izq;
            pila_apilar(iter->pila, nodo);
        }
    }
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

    if (pila_esta_vacia(iter->pila)) return false;

    n_abb_t* desapilado = pila_desapilar(iter->pila);
    if (desapilado->der){
        pila_apilar(iter->pila, desapilado->der);
        while(((n_abb_t*)pila_ver_tope(iter->pila))->izq){
            n_abb_t* nodo = ((n_abb_t*)pila_ver_tope(iter->pila))->izq;
            pila_apilar(iter->pila, nodo);
        }
    }
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){

    if (pila_esta_vacia(iter->pila)) return NULL;
    return ((n_abb_t*)pila_ver_tope(iter->pila))->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){

    if (pila_esta_vacia(iter->pila)) return true;
    return false;
}

void abb_iter_in_destruir(abb_iter_t* iter){

    pila_destruir(iter->pila);
    free(iter);
}
