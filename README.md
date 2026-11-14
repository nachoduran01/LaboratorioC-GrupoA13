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

---

### Uso de Inteligencia Artificial (Gemini)

#### Módulo Principal (`main.c`) — Orquestación, Menú e Integración

**Contexto de uso:** La arquitectura del menú interactivo y la coordinación entre los módulos `simulador.h` y `validaciones.h` fueron diseñadas manualmente. Se utilizó Gemini de forma puntual como apoyo técnico en tres etapas: confirmar la organización limpia de `main.c`, revisar el reinicio de estados mediante punteros y resolver un error de enlazado al compilar los archivos fuente juntos.

**Prompt 1 (Consulta de diseño modular):** Estoy armando el archivo `main.c` para un simulador modular en C de la Situación 3 de Artemis (Inyección Translunar - TLI). Para mantener el código limpio y desacoplado, ¿conviene declarar las variables de estado dentro de `main()` y pasarlas por referencia a las funciones de `simulador.h`, o usar variables globales entre archivos?

**Validación y Adaptación:** La IA recomendó evitar variables globales y declarar la estructura principal `Mision_t` de forma local dentro de `main()`, pasándola por referencia (`&mision`) a cada módulo. Se aplicó este enfoque para mantener la encapsulación y facilitar el seguimiento de datos entre `validaciones.h` y `simulador.h`.

**Prompt 2 (Revisión de flujo y punteros):** Ya tengo implementado el menú en un bucle `do-while` llamando a `ejecutar_simulacion(&mision)` y `mostrar_reporte(&mision)`. ¿Es seguro reutilizar la misma estructura `&mision` en cada iteración o conviene limpiar los resultados antes de cargar datos personalizados?

**Validación y Adaptación:** La IA señaló que, si el usuario ejecuta primero la simulación nominal y luego ingresa valores personalizados, podrían quedar datos residuales en `Resultados_t` si alguna rama condicional no los sobrescribe. A partir de esa observación, se incorporó el reinicio explícito de los campos antes de cada nueva carga de parámetros y se ajustaron los mensajes de consola.

**Prompt 3 (Depuración de compilación en GCC):** Al compilar `main.c` junto con `simulador.c` y `validaciones.c` en GCC me arroja `undefined reference to sqrt` y advertencias de declaración implícita. ¿A qué se debe este error en la etapa de enlazado?

**Validación y Adaptación:** La IA explicó que las funciones de `<math.h>` requieren enlazar explícitamente la librería matemática con el flag `-lm` al final del comando de compilación (`gcc main.c simulador.c validaciones.c -o artemis -lm`) y verificar que los prototipos en los `.h` coincidan exactamente con las firmas en los `.c`. Se verificó la compilación limpia sin advertencias (`-Wall -Wextra`).
