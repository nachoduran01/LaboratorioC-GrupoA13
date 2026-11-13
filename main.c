#include <stdio.h>

int main(void) {
    int opcion;

    do {
        printf("\n=== SIMULADOR MISION ARTEMIS (TLI) ===\n");
        printf("1. Ejecutar simulacion nominal\n");
        printf("2. Ejecutar simulacion personalizada\n");
        printf("3. Salir\n");

        opcion = leer_entero("Seleccione una opcion", 1, 3);

        switch (opcion) {
            case 1:
                printf("\n[En desarrollo] Simulacion nominal...\n");
                break;
            case 2:
                printf("\n[En desarrollo] Simulacion personalizada...\n");
                break;
            case 3:
                printf("\nSaliendo del programa...\n");
                break;
        }

    } while (opcion != 3);

    return 0;
}
