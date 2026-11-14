#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"
#include "interfaz.h"

#define MAX_HISTORIAL 10

int main(void) {
    Mision_t historial[MAX_HISTORIAL];
    int total_simulaciones = 0;
    int opcion;

    do {
        printf("\n======================================================================\n");
        printf("         SIMULADOR MISION ARTEMIS - INYECCION TRANSLUNAR (TLI)        \n");
        printf("======================================================================\n");
        printf("1. Ejecutar simulacion con parametros nominales de Artemis\n");
        printf("2. Ejecutar simulacion con parametros personalizados\n");
        printf("3. Ver historial de simulaciones realizadas (%d/%d)\n", total_simulaciones, MAX_HISTORIAL);
        printf("4. Salir\n");
        printf("----------------------------------------------------------------------\n");

        opcion = leer_entero("Seleccione una opcion", 1, 4);

        switch (opcion) {
            case 1: {
                if (total_simulaciones >= MAX_HISTORIAL) {
                    printf("\n[Aviso] Se alcanzo el limite maximo de simulaciones en el historial (%d).\n", MAX_HISTORIAL);
                    break;
                }

                Mision_t nueva_mision;
                nueva_mision.id_simulacion = total_simulaciones + 1;

                // Valores nominales del enunciado
                nueva_mision.parametros.masa_orion = 26000.0;
                nueva_mision.parametros.v_tli = 10900.0;
                nueva_mision.parametros.h_orbita = 192000.0;
                nueva_mision.parametros.dist_tierra_luna = 384000000.0;

                ejecutar_simulacion(&nueva_mision);

                interfaz_mostrar_mision(&nueva_mision);

                mostrar_reporte(&nueva_mision);

                historial[total_simulaciones] = nueva_mision;
                total_simulaciones++;
                break;
            }

            case 2: {
                if (total_simulaciones >= MAX_HISTORIAL) {
                    printf("\n[Aviso] Se alcanzo el limite maximo de simulaciones en el historial (%d).\n", MAX_HISTORIAL);
                    break;
                }

                Mision_t nueva_mision;
                nueva_mision.id_simulacion = total_simulaciones + 1;

                printf("\n--- INGRESO DE PARAMETROS DE LA MISION ---\n");
                nueva_mision.parametros.masa_orion = leer_decimal(
                    "Ingrese masa de la nave Orion en kg", 1000.0, 100000.0);
                
                nueva_mision.parametros.v_tli = leer_decimal(
                    "Ingrese velocidad de inyeccion TLI en m/s", 1000.0, 20000.0);
                
                nueva_mision.parametros.h_orbita = leer_decimal(
                    "Ingrese altitud de orbita baja (LEO) en metros", 100000.0, 2000000.0);
                
                nueva_mision.parametros.dist_tierra_luna = leer_decimal(
                    "Ingrese distancia Tierra-Luna en metros", 300000000.0, 450000000.0);

                ejecutar_simulacion(&nueva_mision);

                interfaz_mostrar_mision(&nueva_mision);

                mostrar_reporte(&nueva_mision);

                // Evaluacion de viabilidad de la mision
                if (nueva_mision.resultados.trabajo_extra > 0) {
                    printf("[ALERTA DE MISION] La velocidad inicial es insuficiente para alcanzar\n");
                    printf("el punto de equilibrio gravitatorio por inercia. Se requiere trabajo\n");
                    printf("externo adicional (%.2e J/kg) o la nave caera hacia la Tierra.\n",
                           nueva_mision.resultados.trabajo_extra);
                } else {
                    printf("[MISION EXITOSA] La nave posee energia cinetica suficiente para\n");
                    printf("superar el punto de equilibrio gravitatorio hacia la Luna.\n");
                }

                historial[total_simulaciones] = nueva_mision;
                total_simulaciones++;
                break;
            }

                case 3: {

                    interfaz_mostrar_historial(
                         historial,
                         total_simulaciones
                     );

                    break;
                 }

            case 4:
                printf("\nFinalizando simulador Artemis. Hasta luego.\n");
                break;
        }

    } while (opcion != 4);

    return 0;
}
