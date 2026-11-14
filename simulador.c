#include <stdio.h>
#include <math.h>
#include "simulador.h"

void ejecutar_simulacion(Mision_t *mision) {
    // Hacemos una copia local de las entradas
    Entradas_t in = mision->parametros;
    
    // Cálculo de la Energía Cinética Inicial (K = 1/2 * m * v^2)
    mision->resultados.energia_cinetica = 0.5 * in.masa_orion * pow(in.v_tli, 2);

    // Cálculo del punto de equilibrio gravitatorio (Fórmula optimizada)
    double relacion_masas = sqrt(MASA_LUNA / MASA_TIERRA);
    mision->resultados.r_equilibrio = in.dist_tierra_luna / (1.0 + relacion_masas);

    // Cálculo del Trabajo adicional mínimo por unidad de masa (W_ext / m)
    // Conservación de la energía: W_ext = Energia Final - Energia Inicial
    // Energía Inicial: Cinética + Potencial
    double radio_orbita = RADIO_TIERRA + in.h_orbita;
    double u_inicial_masa = - (G * MASA_TIERRA) / radio_orbita; 
    double k_inicial_masa = 0.5 * pow(in.v_tli, 2);
    double e_inicial_masa = k_inicial_masa + u_inicial_masa;

    // Energía Final (en el punto de equilibrio la velocidad es 0, asi que solo hay potencial)
    double dist_a_luna = in.dist_tierra_luna - mision->resultados.r_equilibrio;
    double u_final_masa = - (G * MASA_TIERRA) / mision->resultados.r_equilibrio 
                          - (G * MASA_LUNA) / dist_a_luna;

    mision->resultados.trabajo_extra = u_final_masa - e_inicial_masa;
}

void mostrar_reporte(Mision_t *mision) {
    printf("\n======================================================================\n");
    printf(" REPORTE DE MISION #%d - INYECCION TRANSLUNAR (TLI)\n", mision->id_simulacion);
    printf("======================================================================\n");
    
    // Explicación de la 1.ª Ley de Newton
    printf("    1ra Ley de Newton: Ley de Inercia.\n");
    printf("    Al apagar los propulsores (Fuerza de empuje = 0), la nave Orion\n");
    printf("    tiende a mantener su estado de movimiento rectilineo por inercia.\n");
    printf("    Sin embargo, la fuerza de atraccion gravitatoria de la Tierra\n");
    printf("    actua como una fuerza externa neta contraria a su avance, lo que\n");
    printf("    provoca que la nave se desacelere progresivamente.\n\n");

    // Impresión de Energía Cinética
    printf("    Energia Cinetica Inicial (Velocidad = %.1f m/s):\n", mision->parametros.v_tli);
    printf("    -> K = %.2e Joules\n\n", mision->resultados.energia_cinetica);
    
    // Impresión de Trabajo y Equilibrio
    printf("    Analisis Energetico hacia Punto de Equilibrio:\n");
    printf("    -> Distancia de equilibrio (desde centro Tierra): %.2e m\n", mision->resultados.r_equilibrio);
    printf("    -> Trabajo adicional requerido (por unidad de masa): %.2e J/kg\n\n", mision->resultados.trabajo_extra);

    // Explicación de Perspectiva Energética
    printf("    Perspectiva Energetica del Viaje:\n");
    printf("    Se requiere mucha mas masa de combustible para viajar de la Tierra\n");
    printf("    hacia la Luna porque la nave debe vencer un pozo gravitatorio\n");
    printf("    enorme dictado por la gran masa terrestre. Al regreso, el pozo\n");
    printf("    gravitatorio lunar a vencer es significativamente menor, demandando\n");
    printf("    menos energia y combustible para alcanzar la velocidad de escape.\n");
    printf("======================================================================\n");
}