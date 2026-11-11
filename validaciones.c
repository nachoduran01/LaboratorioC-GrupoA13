#include <stdio.h>
#include "validaciones.h"

double leer_decimal(const char* mensaje, double min, double max) {
    double valor;
    int leidos;
    do {
        printf("%s (Rango: %.2f - %.2f): ", mensaje, min, max);
        leidos = scanf("%lf", &valor);
        while(getchar() != '\n'); // Limpiar buffer
        if (leidos != 1 || valor < min || valor > max) {
            printf("Error: Ingrese un valor numérico válido dentro del rango.\n");
        }
    } while (leidos != 1 || valor < min || valor > max);
    return valor;
}
