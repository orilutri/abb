#include "abb.h"


typedef enum tipo_hijo {HIJO_DER, HIJO_IZQ, RAIZ} tipo_hijo_t;

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
void* buscar_nodo(nodo_t *raiz, const char* clave, abb_comparar_clave_t abb_comparar_clave);
void enlazar_nodos(nodo_t* padre, nodo_t* hijo, tipo_hijo_t posicion);
nodo_t* buscar_padre(nodo_t* raiz, const char* clave_hijo, abb_comparar_clave_t abb_comparar_clave);


/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

/*funciones cátedra */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

}

void *abb_borrar(abb_t *arbol, const char *clave) {
  nodo_t* padre = buscar_padre(arbol->raiz, clave, arbol->abb_comparar_clave);
  if (!padre && !arbol->raiz) return NULL;
  nodo_t* nodo;
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
    nodo_t* reemplazante = nodo->der;
    while (reemplazante->izq) reemplazante = reemplazante->izq;
    const char* clave_reemp = reemplazante->clave;
    void* dato_reemp = abb_borrar(arbol, reemplazante->clave);
    nodo->clave = clave_reemp;
    nodo->dato = dato_reemp;
  }
  return dato;

}

void *abb_obtener(const abb_t *arbol, const char *clave){

}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  return buscar_nodo(arbol->raiz, clave, arbol->abb_comparar_clave) != NULL;
}

size_t abb_cantidad(abb_t *arbol){
  return arbol->cont;
}

void abb_destruir(abb_t *arbol){

}

/*funciones nuestras*/

void* buscar_nodo(nodo_t *raiz, const char* clave, abb_comparar_clave_t abb_comparar_clave) {
  if (!raiz) return NULL;
  if (abb_comparar_clave(clave, raiz->clave) < 0) return buscar_nodo(raiz->izq, clave, abb_comparar_clave);
  if (abb_comparar_clave(clave, raiz->clave) == 0) return raiz;
  buscar_nodo(raiz->der, clave, abb_comparar_clave);
}

void enlazar_nodos(nodo_t* padre, nodo_t* hijo, tipo_hijo_t posicion) {
  if (posicion == HIJO_IZQ) padre->izq = hijo;
  else padre->der = hijo;
  return;
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
