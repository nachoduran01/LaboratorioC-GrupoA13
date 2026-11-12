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

**Prompt Inicial:** Estoy desarrollando el simulador de la misión Artemis. Necesito que actúes como asistente técnico para resolver dudas puntuales sobre manejo del buffer en C y comandos colaborativos de Git, sin que me escribas el código completo del trabajo.

**Prompt 1:** Te comparto las funciones de validación numérica que armé. Quiero que analices el código, intentes romperlo y me indiques si encontrás alguna falla o brecha.

**Adaptación:** La IA analizó la lógica y detectó una vulnerabilidad crítica: si el usuario ingresa una señal de fin de archivo (Ctrl+Z o EOF), la limpieza del buffer falla y el programa colapsa en un bucle infinito. Siguiendo su analisis, rehice el módulo abandonando `scanf`. Implementamos `fgets` para capturar la línea completa de forma segura, `sscanf` para extraer el dato, y `clearerr(stdin)` para limpiar el estado de error ante un EOF, logrando un código robusto y a prueba de fallos.
