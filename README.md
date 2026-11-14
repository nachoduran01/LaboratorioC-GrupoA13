<div align="center">

# UNIVERSIDAD TECNOLÓGICA NACIONAL
### Facultad Regional Resistencia
**Ingeniería en Sistemas de Información**  
**Cátedra:** Algoritmos y Estructuras de Datos  
**Ciclo Lectivo:** 2026

---

# LABORATORIO DE LENGUAJE C
## Simulador de Misiones Artemis
### Situación - Problema 3: Inyección Translunar (TLI) e Inercia en Trayectoria Libre

---

### Datos de la Comisión y Equipo de Desarrollo
**Comisión:** K1.1 &nbsp;|&nbsp; **Grupo:** A13

| N.° | Integrante |
| :---: | :--- |
| **1** | **Bois, Cristian Gabriel** |
| **2** | **Comisso Bentz, Matias Gabriel** |
| **3** | **Ferreyra, Valentino** |
| **4** | **Medina Duran Cantón, Jose Ignacio** |

---

</div>

---

## Descripción del Escenario

### Situación 3: Inyección Translunar (TLI) e Inercia en Trayectoria Libre
El sistema simula la fase posterior al impulso de la etapa ICPS en órbita terrestre baja (LEO), donde la nave Orion ingresa a una trayectoria de retorno libre hacia la Luna sin propulsión activa, gobernada por la inercia y los campos gravitatorios de la Tierra y la Luna.

### Reglas y Dinámica de la Simulación
* **Modo de Operación:** Simulación interactiva por consola con menú principal.
* **Ingreso de Parámetros:** Permite trabajar con los datos nominales de la misión Artemis o ingresar valores personalizados (masa de la nave, altitud orbital, velocidad $v_{TLI}$).
* **Condición de Éxito:** Alcanzar y superar el punto de equilibrio gravitatorio Tierra-Luna ($L_1$) para asegurar la captura gravitatoria lunar en trayectoria de retorno libre.
* **Condición de Falla:** Impulso $v_{TLI}$ insuficiente o desvío crítico que cause el reingreso prematuro o la caída hacia la Tierra antes de alcanzar el punto neutro.

### Uso de Inteligencia Artificial (Gemini)

Prompt Inicial: Estoy realizando un laboratorio en C. Quiero que analices el trabajo que te voy a compartir y focalices principalmente en dos cosas. La primera es el punto 4, como verás hay varios escenarios propuestos. Lo que vamos a hacer es trabajar con el tercero: Inyección Translunar — TLI e Inercia en Trayectoria Libre (1.ª Ley de Newton y Energía). Lo segundo en lo que vas a focalizar es el punto 6, el uso de la inteligencia artificial. No pretendo que me resuelvas nada, yo te iré realizando consultas sobre dudas que vaya teniendo. Por lo que quiero que esperes a que yo te realice las preguntas para responder. 

Prompt 1: Al tener datos y variables muy precisas por números decimales. ¿Conviene usar el tipo float o double?

Adaptación: En este caso la IA recomendó que se usara el tipo double ya que tiene un límite de precisión más alto que float (64 bits frente a 32 bits). Este se implementó en el archivo de simulador.h para definir las constantes físicas universales (como la masa terrestre y la constante de gravitación) y las variables de los structs Entradas_t y Resultados_t.

Prompt 2: Como habrás visto, entre tantas otras cosas tengo que calcular la energía cinética y hacer cálculos de proporciones de masas con raíces cuadradas. ¿Qué librería estándar de C debo incluir para resolver potencias y raíces? Explicame exactamente qué funciones usar para estos dos casos puntuales,ycómo implementarlas.

Adaptación: La IA indicó que debíamos incluir <math.h> y utilizar las funciones pow(base, exponente) y sqrt(valor). Además, nos advirtió que para evitar errores en la etapa de enlazado (linking), el comando de compilación en GCC debe incluir obligatoriamente la bandera -lm al final (gcc main.c simulador.c validaciones.c -o artemis -lm).


Prompt 3: Necesito armar una función void mostrar_reporte(Mision_t *mision) que imprima por consola un reporte ordenado de los resultados. Necesito que la función responda a las preguntas del escenario 3 mediante printf.

Adaptación: La IA generó correctamente la estructura de los printf y proporcionó justificaciones físicas muy sólidas para la Ley de Inercia (inciso a) y la asimetría de combustible (inciso d). Para los incisos b y c, reemplazamos los nombres de las variables sugeridas por la IA para que coincidan exactamente con los structs que nuestro equipo ya había definido en el proyecto.

