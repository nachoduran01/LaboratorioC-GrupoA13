#include "simulador.h"

double calcularEnergiaCinetica(double masa, double velocidad) {

    double energia;

    energia = 0.5 * masa * velocidad * velocidad;

    return energia;
}