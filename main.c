#include <stdio.h>
#include "simulador.h"

int main() {

    double energia;

    energia = calcularEnergiaCinetica(MASA_ORION_KG, VELOCIDAD_TLI_MS);

    printf("SIMULADOR DE MISIONES ARTEMIS\n");
    printf("----------------------------\n");
    printf("Energia cinetica inicial de Orion: %.2e Joules\n", energia);

    return 0;
}