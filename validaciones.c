#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

// Función para validar números con decimales (double)
double leer_decimal(const char* mensaje, double min, double max) {
    double valor;
    char buffer[100];
    int leidos;

    do {
        printf("%s (Rango: %.2f - %.2f): ", mensaje, min, max);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

            leidos = sscanf(buffer, "%lf", &valor);

            if (leidos == 1 && valor >= min && valor <= max) {
                return valor; // Salida de la funcion devolviendo el valor en cuyo caso sea correcto y cumpla las condiciones.
            }
        } else {
            clearerr(stdin);
            printf("\n");
        }
        printf("Error: Ingrese un valor numerico valido dentro del rango.\n");

    } while (1);  // Bucle infinito hasta que se ingrese un valor correcto
}

// Función para validar números enteros (int)
int leer_entero(const char* mensaje, int min, int max) {
    int valor;
    char buffer[100];
    int leidos;

    do {
        printf("%s (Rango: %d - %d): ", mensaje, min, max);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {

            leidos = sscanf(buffer, "%d", &valor);

            if (leidos == 1 && valor >= min && valor <= max) {
                return valor; // Salida de la funcion devolviendo el valor en cuyo caso sea correcto y cumpla las condiciones.
            }
        } else {
            clearerr(stdin);
            printf("\n");
        }

        printf("Error: Ingrese un valor entero valido dentro del rango.\n");

    } while (1); // Bucle infinito hasta que se ingrese un valor correcto
}