#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main(void) {
    int opcion;
    int contador = 0;

    do {
        printf("\n======================================================================\n");
        printf("         SIMULADOR MISION ARTEMIS - INYECCION TRANSLUNAR (TLI)        \n");
        printf("======================================================================\n");
        printf("1. Ejecutar simulacion con parametros nominales de Artemis\n");
        printf("2. Ejecutar simulacion con parametros personalizados\n");
        printf("3. Salir\n");
        printf("----------------------------------------------------------------------\n");

        opcion = leer_entero("Seleccione una opcion", 1, 3);

        switch (opcion) {
            case 1: {
                contador++;
                Mision_t mision;
                mision.id_simulacion = contador;

                mision.parametros.masa_orion = 26000.0;
                mision.parametros.v_tli = 10900.0;
                mision.parametros.h_orbita = 192000.0;
                mision.parametros.dist_tierra_luna = 384000000.0;

                ejecutar_simulacion(&mision);
                mostrar_reporte(&mision);
                break;
            }

            case 2:
                printf("\nError2...\n");
                break;

            case 3:
                printf("\nError3...\n");
                break;
        }

    } while (opcion != 3);

    return 0;
}
