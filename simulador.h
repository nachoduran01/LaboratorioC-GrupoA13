#ifndef SIMULADOR_H
#define SIMULADOR_H

// 1. Constantes
#define G 6.674e-11          
#define MASA_TIERRA 5.972e24 
#define MASA_LUNA 7.342e22   
#define RADIO_TIERRA 6371000.0 

// 2. Estructura de Entradas
typedef struct {
    double masa_orion;       
    double v_tli;            
    double h_orbita;         
    double dist_tierra_luna; 
} Entradas_t;

// 3. Estructura de Resultados
typedef struct {
    double energia_cinetica; 
    double r_equilibrio;     
    double trabajo_extra;    
} Resultados_t;

// 4. Estructura Principal
typedef struct {
    int id_simulacion;
    Entradas_t parametros;
    Resultados_t resultados;
} Mision_t;

// 5. Prototipos de funciones
void ejecutar_simulacion(Mision_t *mision);
void mostrar_reporte(Mision_t *mision);

#endif