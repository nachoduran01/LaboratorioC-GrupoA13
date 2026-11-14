#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "interfaz.h"

#define ANCHO_TRAYECTORIA 48
#define ANCHO_BARRA 30
#define CANTIDAD_PASOS 48
#define RETARDO_ANIMACION_MS 65
#define ANCHO_CUADRO 66

/* Dibuja el borde superior o inferior de un cuadro. */
static void dibujar_borde(void)
{
    int i;

    putchar('+');
    for (i = 0; i < ANCHO_CUADRO; i++) {
        putchar('-');
    }
    puts("+");
}

/* Dibuja un encabezado con texto ASCII. */
static void dibujar_fila(const char *texto)
{
    /* 64 caracteres de texto mas un espacio a cada lado = 66 interiores. */
    printf("| %-*.*s |\n", ANCHO_CUADRO - 2, ANCHO_CUADRO - 2, texto);
}

static void dibujar_encabezado(const char *titulo)
{
    dibujar_borde();
    dibujar_fila(titulo);
    dibujar_borde();
}

/* Pausa breve usando clock(), disponible en la biblioteca estandar C. */
static void esperar_milisegundos(unsigned int milisegundos)
{
    clock_t inicio;
    clock_t actual;
    clock_t ticks_espera;

    inicio = clock();
    if (inicio == (clock_t)-1) {
        return;
    }

    ticks_espera = (clock_t)((double)milisegundos * CLOCKS_PER_SEC / 1000.0);
    do {
        actual = clock();
        if (actual == (clock_t)-1) {
            return;
        }
    } while (actual - inicio < ticks_espera);
}

/*
 * Convierte la distancia real al punto de equilibrio en una posicion
 * dentro de la linea ASCII Tierra-Luna.
 * Devuelve -1 si los datos no permiten ubicar el punto.
 */
static int calcular_posicion_equilibrio(const Mision_t *mision)
{
    double distancia;
    double distancia_equilibrio;
    double proporcion;

    if (mision == NULL) {
        return -1;
    }

    distancia = mision->parametros.dist_tierra_luna;
    distancia_equilibrio = mision->resultados.r_equilibrio;

    if (!isfinite(distancia) || !isfinite(distancia_equilibrio) || distancia <= 0.0) {
        return -1;
    }

    proporcion = distancia_equilibrio / distancia;

    /* Evita dibujar el marcador fuera del recorrido. */
    if (proporcion < 0.0) {
        proporcion = 0.0;
    } else if (proporcion > 1.0) {
        proporcion = 1.0;
    }

    return (int)(proporcion * ANCHO_TRAYECTORIA + 0.5);
}

/* Dibuja la linea Tierra-Luna y ubica Orion y el punto de equilibrio. */
static void dibujar_trayectoria(int posicion_orion, int posicion_equilibrio)
{
    int i;
    char simbolo;

    puts("TIERRA [E] ------------------------------------------------ [L] LUNA");
    putchar(' ');
    putchar(' ');

    for (i = 0; i <= ANCHO_TRAYECTORIA; i++) {
        simbolo = '-';

        if (i == posicion_orion && i == posicion_equilibrio) {
            simbolo = '@'; /* Orion coincide con el punto de equilibrio. */
        } else if (i == posicion_orion) {
            simbolo = 'O'; /* Posicion animada de Orion. */
        } else if (i == posicion_equilibrio) {
            simbolo = '|'; /* Punto de equilibrio calculado. */
        }

        putchar(simbolo);
    }

    puts("");
    puts("Leyenda: O = Orion | = equilibrio gravitatorio @ = coincidencia");
}

/* Dibuja una barra proporcional a un valor no negativo. */
static void dibujar_barra(const char *etiqueta, double valor, double escala_maxima)
{
    int i;
    int llenos = 0;

    if (valor > 0.0 && escala_maxima > 0.0 && isfinite(valor)) {
        llenos = (int)((valor / escala_maxima) * ANCHO_BARRA);
        if (llenos > ANCHO_BARRA) {
            llenos = ANCHO_BARRA;
        }
    }

    printf("%-27s [", etiqueta);
    for (i = 0; i < ANCHO_BARRA; i++) {
        putchar(i < llenos ? '#' : '-');
    }
    printf("] %.3e J\n", valor);
}

/* Muestra las magnitudes energeticas calculadas por el modulo simulador. */
static void dibujar_energia(const Mision_t *mision)
{
    double energia_cinetica;
    double trabajo_extra_total;
    double escala_maxima;

    energia_cinetica = mision->resultados.energia_cinetica;
    trabajo_extra_total = mision->resultados.trabajo_extra * mision->parametros.masa_orion;

    escala_maxima = energia_cinetica;
    if (trabajo_extra_total > escala_maxima) {
        escala_maxima = trabajo_extra_total;
    }
    if (!isfinite(escala_maxima) || escala_maxima <= 0.0) {
        escala_maxima = 1.0;
    }

    dibujar_borde();
    dibujar_fila("COMPARACION DE ENERGIA");
    dibujar_borde();

    dibujar_barra("K inicial", energia_cinetica, escala_maxima);

    if (trabajo_extra_total > 0.0) {
        dibujar_barra("Trabajo externo requerido", trabajo_extra_total, escala_maxima);
    } else {
        printf("%-27s [", "Trabajo externo requerido");
        {
            int i;
            for (i = 0; i < ANCHO_BARRA; i++) {
                putchar('-');
            }
        }
        printf("] %.3e J\n", trabajo_extra_total);
        puts("Segun el modelo, no se necesita trabajo externo adicional positivo.");
    }

    printf("Trabajo adicional por unidad de masa: %.3e J/kg\n",
           mision->resultados.trabajo_extra);
    puts("Nota: la barra compara K inicial con el trabajo externo adicional total.");
}

/* Muestra las magnitudes de una mision en un cuadro ASCII. */
static void dibujar_datos_mision(const Mision_t *mision)
{
    char fila[128];

    dibujar_borde();
    dibujar_fila("DATOS Y RESULTADOS");
    dibujar_borde();

    (void)snprintf(fila, sizeof(fila), "Mision: %d", mision->id_simulacion);
    dibujar_fila(fila);
    (void)snprintf(fila, sizeof(fila), "Masa Orion: %.2f kg", mision->parametros.masa_orion);
    dibujar_fila(fila);
    (void)snprintf(fila, sizeof(fila), "Velocidad TLI: %.2f m/s", mision->parametros.v_tli);
    dibujar_fila(fila);
    (void)snprintf(fila, sizeof(fila), "Distancia Tierra-Luna: %.2f m",
                   mision->parametros.dist_tierra_luna);
    dibujar_fila(fila);
    (void)snprintf(fila, sizeof(fila), "Energia cinetica inicial: %.3e J",
                   mision->resultados.energia_cinetica);
    dibujar_fila(fila);
    (void)snprintf(fila, sizeof(fila), "Punto de equilibrio desde Tierra: %.3e m",
                   mision->resultados.r_equilibrio);
    dibujar_fila(fila);
    (void)snprintf(fila, sizeof(fila), "Trabajo adicional por unidad de masa: %.3e J/kg",
                   mision->resultados.trabajo_extra);
    dibujar_fila(fila);

    dibujar_borde();
}

/* Limpia la pantalla segun el sistema operativo/terminal. */
void interfaz_limpiar_pantalla(void)
{
#ifdef _WIN32
    (void)system("cls");
#else
    /* Secuencias ANSI: limpian la pantalla y llevan el cursor al origen. */
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}

/* Espera a que el usuario presione ENTER; funciona en Windows, Linux y macOS. */
void interfaz_pausar(void)
{
    int caracter;

    printf("\nPresione ENTER para continuar...");
    fflush(stdout);

    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        /* Descarta cualquier caracter restante de la linea. */
    }
}

/* Presenta la animacion y los resultados de una mision ya calculada. */
void interfaz_mostrar_mision(const Mision_t *mision)
{
    int paso;
    int posicion_equilibrio;

    if (mision == NULL) {
        puts("[ERROR] No se recibio una mision valida para mostrar.");
        interfaz_pausar();
        return;
    }

    posicion_equilibrio = calcular_posicion_equilibrio(mision);

    /* La nave recorre visualmente la linea Tierra-Luna. */
    for (paso = 0; paso <= CANTIDAD_PASOS; paso++) {
        interfaz_limpiar_pantalla();
        dibujar_encabezado("SIMULADOR ARTEMIS - INYECCION TRANSLUNAR (TLI)");
        printf("Mision #%d | Animacion ilustrativa del recorrido Tierra-Luna\n\n",
               mision->id_simulacion);

        if (posicion_equilibrio >= 0) {
            dibujar_trayectoria(paso, posicion_equilibrio);
            printf("Punto de equilibrio: %.3e m desde la Tierra (%.1f%% del recorrido)\n",
                   mision->resultados.r_equilibrio,
                   100.0 * mision->resultados.r_equilibrio /
                       mision->parametros.dist_tierra_luna);
        } else {
            dibujar_trayectoria(paso, -1);
            puts("Punto de equilibrio no disponible: revise los datos de la mision.");
        }

        printf("Progreso visual: %3d%%\n", (paso * 100) / CANTIDAD_PASOS);
        esperar_milisegundos(RETARDO_ANIMACION_MS);
    }

    interfaz_limpiar_pantalla();
    dibujar_encabezado("REPORTE VISUAL DE MISION ARTEMIS");
    dibujar_datos_mision(mision);
    dibujar_energia(mision);
    dibujar_borde();
    dibujar_fila("Animacion ilustrativa; no integra la trayectoria en el tiempo.");
    dibujar_fila("El marcador de equilibrio utiliza el resultado r_equilibrio.");
    dibujar_borde();

    interfaz_pausar();
}

/* Presenta un resumen del arreglo de misiones sin modificarlo. */
void interfaz_mostrar_historial(const Mision_t historial[], int cantidad)
{
    int i;

    interfaz_limpiar_pantalla();
    dibujar_encabezado("HISTORIAL DE MISIONES ARTEMIS");

    if (historial == NULL || cantidad <= 0) {
        puts("No hay simulaciones guardadas.");
        interfaz_pausar();
        return;
    }

    printf("Simulaciones registradas: %d\n\n", cantidad);
    for (i = 0; i < cantidad; i++) {
        printf("Mision #%d | Masa: %.0f kg | v_TLI: %.1f m/s\n",
               historial[i].id_simulacion,
               historial[i].parametros.masa_orion,
               historial[i].parametros.v_tli);
        printf("  K_i: %.3e J | r_equilibrio: %.3e m | W_ext/m: %.3e J/kg\n\n",
               historial[i].resultados.energia_cinetica,
               historial[i].resultados.r_equilibrio,
               historial[i].resultados.trabajo_extra);
    }

    dibujar_borde();
    interfaz_pausar();
}
