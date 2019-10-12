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
    size_t cont;
};

/*Definición del struct iterador.*/
struct abb_iter{

};

/*prototipos de funciones nuestras*/



/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

/*funciones cátedra */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

}

void *abb_borrar(abb_t *arbol, const char *clave){

}

void *abb_obtener(const abb_t *arbol, const char *clave){

}

bool abb_pertenece(const abb_t *arbol, const char *clave){

}

size_t abb_cantidad(abb_t *arbol){

}

void abb_destruir(abb_t *arbol){

}

/*funciones nuestras*/



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