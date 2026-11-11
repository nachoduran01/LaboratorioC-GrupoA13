#ifndef VALIDACIONES_H
#define VALIDACIONES_H
// funciones de validacion, decimal de dos numeros y entero
double leer_decimal(const char* texto, double min, double max);
int leer_entero(const char* texto, int min, int max);
#endif

#ifndef SIMULADOR_H
#define SIMULADOR_H

#define MASA_ORION_KG 26000.0
#define VELOCIDAD_TLI_MS 10900.0

double calcularEnergiaCinetica(double masa, double velocidad);

#endif