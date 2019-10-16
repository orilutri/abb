#include "abb.h"
#include <stdlib.h>

/* Definición del struct nodo */
typedef struct nodo {
    struct nodo* izq;
    struct nodo* der;
    void* dato;
    const char* clave;
} nodo_t;

/* Definición del struct ab.*/
struct abb {
    nodo_t* raiz;
    abb_comparar_clave_t abb_comparar_clave;
    abb_destruir_dato_t abb_destruir_dato;
    size_t cont;
};

/* Definición del struct iterador.*/
struct abb_iter{

};

/* Prototipos de funciones nuestras*/



/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

/*funciones cátedra */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

}

void *abb_borrar(abb_t *arbol, const char *clave) {
  
}

void *abb_obtener(const abb_t *arbol, const char *clave){

}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  return buscar_dato(arbol->raiz, clave) != NULL;
}

size_t abb_cantidad(abb_t *arbol){
  return arbol->cont;
}

void abb_destruir(abb_t *arbol){

}

/*funciones nuestras*/

void* buscar_nodo(nodo_t *raiz, char* clave, abb_comparar_clave_t abb_comparar_clave) {
  if (!raiz) return NULL;
  if (abb_comparar_clave(clave, raiz->clave) == 0) return raiz;
  if (abb_comparar_clave(clave, raiz->clave) < 0) return buscar_nodo(raiz->izq, clave);
  return buscar_nodo(raiz->der, clave);
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
