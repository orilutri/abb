#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.



/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_abb_vacio() {
    printf("\n~~PRUEBA ABB VACÍO~~\n");
    /* Declaro Variables */
    abb_t* abb = abb_crear(strcmp, NULL);

    /* Inicio de pruebas */
    print_test("La cantidad es 0", abb_cantidad(abb) == 0);
    print_test("La clave A no percenece", !abb_pertenece(abb, "A"));
    print_test("No se puede borrar la clave A", abb_borrar(abb, "A") == NULL);
    //abb_iter_t* iter = abb_iter_in_crear(abb);
    //print_test("Iter está al final", abb_iter_in_al_final(iter));
    //print_test("Iter avanzar es false", !abb_iter_in_avanzar(iter));
    //print_test("Iter ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);
    //abb_iter_in_destruir(iter);
    abb_destruir(abb);
    //Probar con abb = NULL
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
    abb_t* abb = abb_crear(strcmp, free);

    /* Inicio de pruebas */
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", a));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == a);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", b));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == b);
    print_test("Clave 'a' pertenece al abb", abb_pertenece(abb, "a"));
    print_test("Guardar clave 'a'", abb_guardar(abb, "a", c));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave 'a' da el valor correcto", abb_obtener(abb, "a") == c);
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
}

char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

void prueba_volumen() {
    printf("\n~~PRUEBA ABB VOLUMEN~~\n");
    /* Declaro variables */
    char* arreglo[1000];
    int aux = 0;
    abb_t* abb = abb_crear(strcmp, NULL);
    int j = 2;
    int k = 4;
    for (int i = 0; i < 1000; i++) {
        arreglo[i] = itoa(j, 10);
        i++;
        arreglo[i] = itoa(k, 10);
        j++;
        k+=2;
    }

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
}


/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_abb_alumno(void) {
    /* Ejecuta todas las pruebas unitarias. */
    prueba_abb_vacio();
    //prueba_iterar_abb_vacio();
    prueba_abb_guardar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_destruir();
    prueba_abb_borrar();
    //prueba_abb_clave_vacia();
    //prueba_abb_valor_null();
    //prueba_volumen();
    //prueba_iterar();
    //prueba_iterar_volumen();
}