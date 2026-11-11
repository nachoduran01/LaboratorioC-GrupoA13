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
