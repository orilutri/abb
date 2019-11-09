#include "abb.h"
#include <stdlib.h>
#include "pila.h"

typedef enum tipo_hijo {HIJO_DER, HIJO_IZQ, RAIZ} tipo_hijo_t;

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
    pila_t* pila;
    const abb_t* abb;
};

/*prototipos de funciones nuestras*/
n_abb_t* crear_nodo(const char* clave,void*dato);
bool abb_buscar(n_abb_t* raiz, abb_comparar_clave_t abb_comparar_clave, const char* clave);
void enlazar_nodos(n_abb_t* padre, n_abb_t* hijo, tipo_hijo_t posicion);
n_abb_t* buscar_padre(n_abb_t* raiz, n_abb_t* padre, const char* clave, abb_comparar_clave_t abb_comparar_clave);
bool _abb_guardar(n_abb_t* raiz, const char *clave, void *dato, abb_comparar_clave_t abb_comparar_clave, abb_destruir_dato_t abb_destruir_dato, size_t cant);
void _abb_destruir(n_abb_t* raiz, abb_destruir_dato_t abb_destruir_dato, abb_t* arbol);

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

    if(!arbol) return false;
    //ver si tengo que pasar la cantidad como un puntero
    return _abb_guardar(arbol->raiz, clave, dato, arbol->abb_comparar_clave, arbol->abb_destruir_dato, arbol->cant);
}

bool _abb_guardar(n_abb_t* raiz, const char *clave, void *dato, abb_comparar_clave_t abb_comparar_clave, abb_destruir_dato_t abb_destruir_dato, size_t cant){

    if(!raiz){
        n_abb_t* nuevo_nodo = crear_nodo(clave, dato);
        if(!nuevo_nodo) return false;
        raiz = nuevo_nodo;
    }else{
        const char* clave_raiz = raiz->clave;
        if(abb_comparar_clave(clave_raiz, clave) == 0){
            abb_destruir_dato(raiz->dato);
            raiz->dato = dato;
        }else if(abb_comparar_clave(clave_raiz, clave) > 0){
            _abb_guardar(raiz->izq, clave, dato, abb_comparar_clave, abb_destruir_dato, cant);
        }else{
            _abb_guardar(raiz->der, clave, dato, abb_comparar_clave, abb_destruir_dato, cant);
        }
    }
    cant++;
    return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){

    n_abb_t* padre = buscar_padre(arbol->raiz, NULL, clave, arbol->abb_comparar_clave);
    if (!padre && !arbol->raiz) return NULL;
    n_abb_t* nodo;
    tipo_hijo_t tipo_hijo;
    if (!padre) {
        nodo = arbol->raiz;
        tipo_hijo = RAIZ;
    } else if (padre->izq->clave == clave) {
        nodo = padre->izq;
        tipo_hijo = HIJO_IZQ;
    } else {
        nodo = padre->der;
        tipo_hijo = HIJO_DER;
    }
    void* dato = nodo->dato;

    /* Caso sin hijos */
    if (!nodo->izq && !nodo->der) {
        if (!padre) arbol->raiz = NULL;
        else enlazar_nodos(padre, nodo, tipo_hijo);
        free(nodo);
    }

    /* Caso con un hijo */
    if((!nodo->izq && nodo->der) || (nodo->izq && !nodo->der)) {
        if (!padre) {
            if (nodo->izq) arbol->raiz = nodo->izq;
            else arbol->raiz = nodo->der;
        }
        else if (nodo->izq) enlazar_nodos(padre, nodo->izq, tipo_hijo);
        else enlazar_nodos(padre, nodo->der, tipo_hijo);
        free(nodo);

    /* Caso dos hijos */
    } else {
        n_abb_t* reemplazante = nodo->der;
        while (reemplazante->izq) reemplazante = reemplazante->izq;
        const char* clave_reemp = reemplazante->clave;
        void* dato_reemp = abb_borrar(arbol, reemplazante->clave);
        nodo->clave = clave_reemp;
        nodo->dato = dato_reemp;
    }
    return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave){

    if(!arbol) return NULL;
    if(abb_buscar(arbol->raiz, arbol->abb_comparar_clave, clave)) return arbol->raiz->dato;
    return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){

    if (!arbol) return false;
    if (!abb_buscar(arbol->raiz, arbol->abb_comparar_clave, clave)) return true;
    return false;
}

size_t abb_cantidad(abb_t *arbol){
    
    return arbol->cant;
}

void abb_destruir(abb_t *arbol){

    if (!arbol) return;
    _abb_destruir(arbol->raiz, arbol->abb_destruir_dato, arbol);
}

void _abb_destruir(n_abb_t* raiz, abb_destruir_dato_t abb_destruir_dato, abb_t* arbol){

    if (!raiz) return;
    if (!raiz->izq && !raiz->der){
        abb_destruir_dato(raiz->dato);
        abb_borrar(arbol, raiz->clave); //ESTO ESTA BIEN???
        free(arbol); //ESTO VA???
    }else if (raiz->izq){
        _abb_destruir(raiz->izq, abb_destruir_dato, arbol);
    }else{
        _abb_destruir(raiz->der, abb_destruir_dato, arbol);
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

bool abb_buscar(n_abb_t* raiz, abb_comparar_clave_t abb_comparar_clave, const char* clave){

    if(!raiz) return false;
    if (abb_comparar_clave(raiz->clave, clave) == 0) return true;
    else if (abb_comparar_clave(raiz->clave, clave) > 0){
        return abb_buscar(raiz->izq, abb_comparar_clave,clave);   
    }else{
        return abb_buscar(raiz->der, abb_comparar_clave, clave);
    }
}

void enlazar_nodos(n_abb_t* padre, n_abb_t* hijo, tipo_hijo_t posicion) {
    if (posicion == HIJO_IZQ) padre->izq = hijo;
    else padre->der = hijo;
    return;
}

n_abb_t* buscar_padre(n_abb_t* raiz, n_abb_t* padre, const char* clave, abb_comparar_clave_t abb_comparar_clave) {
    if (!raiz || !raiz->izq || !raiz->der) return NULL;
    if (abb_comparar_clave(clave, raiz->clave) < 0) return buscar_padre(raiz->izq,raiz, clave, abb_comparar_clave);
    if (abb_comparar_clave(clave, raiz->clave) == 0) return padre;
    buscar_padre(raiz->der, raiz, clave, abb_comparar_clave);
}

void _abb_in_order(n_abb_t* raiz, bool visitar(const char*, void *, void *), void *extra) {
    if (!raiz) return;
    _abb_in_order(raiz->izq, visitar, extra);
    visitar(raiz->clave, raiz, extra);
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

    pila_apilar(iter->pila, iter->abb->raiz);
    while(((n_abb_t*)pila_ver_tope(iter->pila))->izq){
        n_abb_t* nodo = ((n_abb_t*)pila_ver_tope(iter->pila))->izq;
        pila_apilar(iter->pila, nodo);
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