#include <stdio.h>
#include "validaciones.h"

double leer_decimal(const char* mensaje, double min, double max) {
    double valor;
    int leidos;
    do {
        printf("%s (Rango: %.2f - %.2f): ", mensaje, min, max);
        leidos = scanf("%lf", &valor);
        while(getchar() != '\n'); // Limpia el buffer de entrada
        if (leidos != 1 || valor < min || valor > max) {
            printf("Error: Ingrese un valor numérico valido dentro del rango.\n");
        }
    } while (leidos != 1 || valor < min || valor > max);
    return valor;
}

int leer_entero(const char* mensaje, int min, int max) {
    int valor;
    int leidos;
    do {
        printf("%s (Rango: %d - %d): ", mensaje, min, max);
        leidos = scanf("%d", &valor);
        while(getchar() != '\n'); // Limpia el buffer de entrada
        if (leidos != 1 || valor < min || valor > max) {
            printf("Error: Ingrese un valor entero valido dentro del rango.\n");
        }
    } while (leidos != 1 || valor < min || valor > max);
    return valor;
}
