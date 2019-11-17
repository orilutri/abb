#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.



/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void crear_arreglo_desordenado(char** arreglo) {
    char str[50];
    int j = 7;
    int k = 12;
    for (int i = 0; i < 1000; i++) {
        sprintf(str, "%i", j);
        arreglo[i] = strdup(str);
        i++;
        sprintf(str, "%i", k);
        arreglo[i] = strdup(str);
        j+=2;
        k+=4;
    }
}

void prueba_abb_vacio() {
    printf("\n~~PRUEBA ABB VACÍO~~\n");
    /* Declaro Variables */
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de pruebas */
    print_test("La cantidad es 0", abb_cantidad(abb) == 0);
    print_test("La clave A no percenece", !abb_pertenece(abb, "A"));
    print_test("No se puede borrar la clave A", abb_borrar(abb, "A") == NULL);
    abb_destruir(abb);
    
}

void prueba_iterar_abb_vacio() {
    printf("\n~~PRUEBA ITERAR ABB VACÍO~~\n");
    /*Declaro Variables */
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    /* Inicio de Pruebas */
    print_test("Iter está al final", abb_iter_in_al_final(iter));
    print_test("Iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Iter ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void prueba_abb_guardar() {
    printf("\n~~PRUEBA ABB GUARDAR~~\n");
    /* Declaro Variables */
    int a = 1;
    int b = 2;
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de pruebas*/
    print_test("Guardar un elemento", abb_guardar(abb, "a", &a));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == &a);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Obtener clave 'b' es NULL", abb_obtener(abb, "b") == NULL);
    print_test("Clave 'b' no pertenece", !abb_pertenece(abb, "b"));
    print_test("Guardar clave 'b'", abb_guardar(abb, "b", &b));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener clave 'b' da el valor correcto", abb_obtener(abb, "b") == &b);
    print_test("Clave 'b' pertenece al abb", abb_pertenece(abb, "b"));
    abb_destruir(abb);
}

void prueba_abb_reemplazar() {
    printf("\n~~PRUEBA ABB REEMPLAZAR~~\n");
    /* Declaro Variables */
    int a = 1;
    int b = 2;
    int c = 3;
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de pruebas */
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", &a));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == &a);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", &b));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == &b);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", &c));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == &c);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    abb_destruir(abb);
}

void prueba_abb_reemplazar_destruir() {
    printf("\n~~PRUEBA ABB REEMPLAZAR DESTRUIR~~\n");
    /* Declaro Variables */
    int* a = malloc(sizeof(int));
    *a = 1;
    int* b = malloc(sizeof(int));
    *b = 2;
    int* c = malloc(sizeof(int));
    *c = 3;
    int* d = malloc(sizeof(int));
    *d = 4;
    int* e = malloc(sizeof(int));
    *e = 5;
    abb_t* abb = abb_crear(strcmp, free);

    /* Inicio de pruebas */
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", a));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == a);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", d));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == d);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", e));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == e);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'b'", abb_guardar(abb, "b", b));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener clave 'b' da el valor correcto", abb_obtener(abb, "b") == b);
    print_test("Clave 'b' pertenece al abb", abb_pertenece(abb, "b"));
    print_test("Guardar clave 'c'", abb_guardar(abb, "c", c));
    print_test("La cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Obtener clave 'c' da el valor correcto", abb_obtener(abb, "c") == c);
    print_test("Clave 'c' pertenece al abb", abb_pertenece(abb, "c"));
    abb_destruir(abb);
}

void prueba_abb_borrar() {
    printf("\n~~PRUEBA ABB BORRAR~~\n");
    /* Declaro variables */
    abb_t* abb = abb_crear(strcmp, NULL);
    int a = 1;
    int a2 = 2;
    int b = 2;
    int b2 = 3;
    int c = 3;

    /* Inicio de pruebas */
    print_test("Guardar clave 'b'", abb_guardar(abb, "b", &b));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'b' da el valor correcto", abb_obtener(abb, "b") == &b);
    print_test("Clave 'b' pertenece al abb", abb_pertenece(abb, "b"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", &a));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == &a);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Borrar clave 'a' devuelve el valor correcto", abb_borrar(abb, "a") == &a);
    print_test("Clave 'a' no pertenece al abb", !abb_pertenece(abb, "a"));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Guardar clave 'c'", abb_guardar(abb, "c", &c));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener clave 'c' da el valor correcto", abb_obtener(abb, "c") == &c);
    print_test("Clave 'c' pertenece al abb", abb_pertenece(abb, "c"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", &a));
    print_test("La cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == &a);
    print_test("'a', 'b' y 'c' pertenecen", abb_pertenece(abb, "a") && abb_pertenece(abb, "b") && abb_pertenece(abb, "c"));
    print_test("Cambiar valor de 'a'", abb_guardar(abb, "a", &a2));
    print_test("Se actualizó el valor", abb_obtener(abb, "a") == &a2);
    print_test("Cambiar valor de 'b'", abb_guardar(abb, "b", &b2));
    print_test("Se actualizó el valor", abb_obtener(abb, "b") == &b2);
    print_test("Clave 'c' da el valor correcto", abb_obtener(abb, "c") == &c);
    print_test("Borrar clave 'a' da el valor correcto", abb_borrar(abb, "a") == &a2);
    print_test("Borrar clave 'a' es NULL", abb_borrar(abb, "a") == NULL);
    print_test("La cantidad de elemetos es 2", abb_cantidad(abb) == 2);
    print_test("Borrar clave 'a' es NULL", abb_borrar(abb, "a") == NULL);
    print_test("Borrar clave 'a' es NULL", abb_borrar(abb, "a") == NULL);
    print_test("Borrar clave 'a' es NULL", abb_borrar(abb, "a") == NULL);
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);
    abb_destruir(abb);
}

void prueba_abb_clave_vacia() {
    printf("\n~~PRUEBA ABB CLAVE VACÍA~~\n");
    /* Declaro Variables */
    int a = 1;
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de Pruebas */
    print_test("Prueba guardar clave vacía", abb_guardar(abb, "", &a));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave '' da el valor correcto", abb_obtener(abb, "") == &a);
    print_test("Clave '' pertenece al abb", abb_pertenece(abb, ""));
    print_test("Borrar clave '' devuelve el valor correcto", abb_borrar(abb, "") == &a);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

void prueba_abb_valor_null() {
    printf("\n~~PRUEBA ABB VALOR NULL~~\n");
    /* Declaro variables */
    int* a = NULL;
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de Pruebas */
    print_test("Prueba guardar clave vacía", abb_guardar(abb, "", a));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave '' da el valor correcto", abb_obtener(abb, "") == a);
    print_test("Clave '' pertenece al abb", abb_pertenece(abb, ""));
    print_test("Borrar clave '' devuelve el valor correcto", abb_borrar(abb, "") == a);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    abb_destruir(abb);
}

void prueba_volumen() {
    printf("\n~~PRUEBA ABB VOLUMEN~~\n");
    /* Declaro variables */
    char* arreglo[1000];
    int aux = 0;
    abb_t* abb = abb_crear(strcmp, NULL);
    crear_arreglo_desordenado(arreglo);

    /* Inicio de pruebas */
    for (int i = 0; i < 1000; i ++) {
        abb_guardar(abb, arreglo[i], arreglo[i]);
    }
    print_test("La cantidad de elementos es 1000", abb_cantidad(abb) == 1000);
    for (int i = 999; i >= 0; i--) {
        if (!abb_pertenece(abb, arreglo[i])) {
            print_test("El elemento pertenece", false);
            aux = -1;
            break;
        }
        if (abb_obtener(abb, arreglo[i]) != arreglo[i]) {
            print_test("El valor obtenido es correcto", false);
            aux = -1;
            break;
        }
        if (abb_borrar(abb, arreglo[i]) != arreglo[i]) {
            print_test("El valor borrado es correcto", false);
            aux = -1;
            break;
        }
        if (abb_pertenece(abb, arreglo[i])) {
            print_test("El valor fue borrado correctamente", false);
            aux = -1;
            break;
        }
        if (abb_cantidad(abb) != i) {
            print_test("La cantidad es correcta", false);
            aux = -1;
            break;
        }
    }
    print_test("Se cumple la invariante para 1000 casos", aux == 0);
    print_test("El arbol está vacío", abb_cantidad(abb) == 0);
    for (int i = 0; i < 1000; i++) free(arreglo[i]);
    abb_destruir(abb);
}

void prueba_iterar() {
    printf("\n~~PRUEBA ITERAR ABB~~\n");
    /* Declaro Variables */
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de pruebas*/
    print_test("Guardar clave a", abb_guardar(abb, "a", &a));
    print_test("Guardar clave d", abb_guardar(abb, "d", &d));
    print_test("Guardar clave b", abb_guardar(abb, "b", &b));
    print_test("Guardar clave e", abb_guardar(abb, "e", &e));
    print_test("Guardar clave c", abb_guardar(abb, "c", &c));   
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("El iterador está en la raíz", strcmp(abb_iter_in_ver_actual(iter), "a") == 0);
    print_test("El iterador no está al final", !abb_iter_in_al_final(iter));
    print_test("El iterador avanza correctamente", abb_iter_in_avanzar(iter));
    print_test("El actual es b", strcmp(abb_iter_in_ver_actual(iter), "b") == 0);
    print_test("El iterador no está al final", !abb_iter_in_al_final(iter));
    print_test("El iterador avanza correctamente", abb_iter_in_avanzar(iter));
    print_test("El actual es c", strcmp(abb_iter_in_ver_actual(iter), "c") == 0);
    print_test("El iterador no está al final", !abb_iter_in_al_final(iter));
    print_test("El iterador avanza correctamente", abb_iter_in_avanzar(iter));
    print_test("El actual es d", strcmp(abb_iter_in_ver_actual(iter), "d") == 0);
    print_test("El iterador no está al final", !abb_iter_in_al_final(iter));
    print_test("El iterador avanza correctamente", abb_iter_in_avanzar(iter));
    print_test("El actual es e", strcmp(abb_iter_in_ver_actual(iter), "e") == 0);
    print_test("El iterador no está al final", !abb_iter_in_al_final(iter));
    print_test("El iterador avanza correctamente", abb_iter_in_avanzar(iter));
    print_test("El iterador está al final", abb_iter_in_al_final(iter));
    print_test("Ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);
    print_test("Avanzar es false", !abb_iter_in_avanzar(iter));
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void prueba_iterar_volumen() {
    printf("\n~~PRUEBA ABB ITERAR VOLUMEN~~\n");

    /* Declaro variables */
    char* arreglo[1000];
    crear_arreglo_desordenado(arreglo);
    abb_t* abb = abb_crear(strcmp, NULL);
    int aux = 0;
    for (int i = 0; i < 1000; i ++) abb_guardar(abb, arreglo[i], arreglo[i]);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    /* Inicio de pruebas */
    char* clave_anterior = strdup(abb_iter_in_ver_actual(iter));
    abb_iter_in_avanzar(iter);
    while (!abb_iter_in_al_final(iter)) {
        if (strcmp(abb_iter_in_ver_actual(iter), clave_anterior) < 0) {
            aux = -1;
            break;
        }
        free(clave_anterior);
        clave_anterior = strdup(abb_iter_in_ver_actual(iter));
        abb_iter_in_avanzar(iter);
    }
    free(clave_anterior);
    print_test("El árbol se recorre correctamente inorder", aux == 0);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    for (int i = 0; i < 1000; i++) free(arreglo[i]);
}

bool multiplicar_por_dos_hasta(const char *clave, void *dato, void *extra) {
    if (strcmp(clave, (char*)extra) == 0) return false;
    *(int*)dato *= 2;
    return true;
}

void prueba_iterador_interno() {
    printf("\n~~PRUEBA ITERADOR EXTERNO~~\n");

    /*Declaro Variables */
    abb_t* abb = abb_crear(strcmp, NULL);
    int a = 4;
    int b = 1;
    int c = 2;
    int d = 3;
    char* extra = "c";
    abb_guardar(abb, "a", &a);
    abb_guardar(abb, "c", &c);
    abb_guardar(abb, "b", &b);
    abb_guardar(abb, "d", &d);

    /* Inicio de pruebas */
    abb_in_order(abb, multiplicar_por_dos_hasta, extra);
    print_test("'a' tiene el valor correcto", *(int*)abb_obtener(abb, "a") == 8);
    print_test("'b' tiene el valor correcto", *(int*)abb_obtener(abb, "b") == 2);
    print_test("'c' tiene el valor correcto", *(int*)abb_obtener(abb, "c") == 2);
    print_test("'d' tiene el valor correcto", *(int*)abb_obtener(abb, "d") == 3);
    abb_destruir(abb);
}

void prueba_borrar_raiz() {
    printf("\n~~~PRUEBA BORRAR RAÍZ~~\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    int a = 1;
    int b = 2;
    int c = 3;
    abb_guardar(abb, "2", &b);
    abb_guardar(abb, "1", &a);
    abb_guardar(abb, "3", &c);
    abb_borrar(abb, "2");
    print_test("La cantidad es 2", abb_cantidad(abb) == 2);
    abb_destruir(abb);

    abb = abb_crear(strcmp, NULL);
    abb_guardar(abb, "1", &a);
    abb_guardar(abb, "2", &a);
    abb_guardar(abb, "4", &a);
    abb_guardar(abb, "3", &a);
    abb_guardar(abb, "5", &a);
    abb_guardar(abb, "6", &a);
    abb_borrar(abb, "1");
    abb_borrar(abb, "4");
    print_test("La cantidad es 4", abb_cantidad(abb) == 4);
    abb_destruir(abb);

    abb = abb_crear(strcmp, NULL);
    abb_guardar(abb, "1", &a);
    abb_guardar(abb, "2", &a);
    abb_guardar(abb, "4", &a);
    abb_guardar(abb, "3", &a);
    abb_guardar(abb, "5", &a);
    abb_guardar(abb, "6", &a);
    abb_borrar(abb, "1");
    abb_borrar(abb, "2");
    abb_borrar(abb, "4");
    print_test("La cantidad es 3", abb_cantidad(abb) == 3);
    abb_destruir(abb);

    abb = abb_crear(strcmp, NULL);
    abb_guardar(abb, "1", &a);
    abb_guardar(abb, "2", &a);
    abb_guardar(abb, "4", &a);
    abb_guardar(abb, "3", &a);
    abb_guardar(abb, "5", &a);
    abb_guardar(abb, "6", &a);
    abb_guardar(abb, "7", &a);
    abb_borrar(abb, "1");
    abb_borrar(abb, "4");
    print_test("La cantidad es 5", abb_cantidad(abb) == 5);
    abb_destruir(abb);

}

bool print(const char* clave, void* dato, void* extra) {
    printf("%s\n", clave);
    return true;
}

void prueba_iterar_param() {
    printf("\nITERAR CON PARÁMETROS\n");
    abb_t* abb = abb_crear(strcmp, NULL);
    int a = 0;
    abb_guardar(abb, "d", &a);
    abb_guardar(abb, "b", &a);
    abb_guardar(abb, "a", &a);
    abb_guardar(abb, "c", &a);
    abb_guardar(abb, "g", &a);
    abb_guardar(abb, "f", &a);
    abb_guardar(abb, "e", &a);
    abb_guardar(abb, "h", &a);
    char* min = "b";
    char* max = "g";
    abb_in_order_param(abb, print, min, max);
    abb_destruir(abb);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_abb_alumno(void) {
    /* Ejecuta todas las pruebas unitarias. */
    prueba_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_guardar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_destruir();
    prueba_abb_borrar();
    prueba_borrar_raiz();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_volumen();
    prueba_iterador_interno();
    prueba_iterar();
    prueba_iterar_volumen();
    prueba_iterar_param();
}