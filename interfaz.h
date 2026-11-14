#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "simulador.h"

/* Muestra la animacion y los resultados de una mision ya calculada. */
void interfaz_mostrar_mision(const Mision_t *mision);

/* Muestra en pantalla las misiones guardadas en el arreglo historial. */
void interfaz_mostrar_historial(const Mision_t historial[], int cantidad);

/* Utilidades de consola portables. */
void interfaz_limpiar_pantalla(void);
void interfaz_pausar(void);

#endif
