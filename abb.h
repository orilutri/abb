#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct abb abb_t;

//tipo de función para comparar dos claves
typedef int (*abb_comparar_clave_t) (const char *, const char *);

// tipo de función para destruir dato
typedef void (*abb_destruir_dato_t) (void *);

typedef struct abb_iter abb_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

/* Crea el abb */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada
 * Post: Se almacenó el par (clave, dato) */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del abb y devuelve el dato asociado. Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura abb fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.*/
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada. */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al abb.
 * Pre: La estructura abb fue inicializada. */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura abb fue inicializada. */
size_t abb_cantidad(abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada.
 * Post: La estructura abb fue destruida. */
void abb_destruir(abb_t *arbol);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

//Recorre el abb y aplica la función visitar a cada uno de los datos de los nodos.
//Pre: el abb fue creado.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador para el abb.
// Post: devuelve un nuevo iterador.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Devuelve verdadero si el iterador avanza a la siguiente posición, false en caso contrario.
// Pre: el iterador fue creado.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve la clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Devuelve verdadero si el iterador está apuntando al final, false en caso contrario.
// Pre: el iterador fue creado.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
void abb_iter_in_destruir(abb_iter_t* iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
void pruebas_lista_alumno(void);

#endif // LISTA_H