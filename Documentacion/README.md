# Documentación Proyecto Individual - Arquitectura de Computadores (CE4301)
## Implementación de Cifrado TEA usando C y Ensamblador RISC-V en QEMU

## 1. Introducción

* **1.1 Objetivo del proyecto**
* **1.2 Alcance de la implementación**
* **1.3 Tecnologías y herramientas utilizadas** (C, ensamblador, GDB, QEMU, Makefile, etc.)

---

## 2. Arquitectura del Software

* **2.1 Separación entre capas C y ensamblador**

  * 2.1.1 Rol del código en C
  * 2.1.2 Rol del código en ensamblador
  * 2.1.3 Interacción entre ambos (interfaces y llamadas)
* **2.2 Interfaces utilizadas**

  * 2.2.1 Funciones expuestas desde C hacia ASM (y viceversa)
  * 2.2.2 Manejo de convenciones de llamada (ABI, registros usados)
* **2.3 Decisiones de diseño y justificación**

  * 2.3.1 Elección de qué lógica implementar en C y cuál en ASM
  * 2.3.2 Simplificaciones / optimizaciones realizadas
  * 2.3.3 Posibles alternativas descartadas

---

## 3. Funcionalidades Implementadas

* **3.1 Descripción general de las funcionalidades**
* **3.2 Flujo de ejecución principal**

  * 3.2.1 Entrada de datos
  * 3.2.2 Procesamiento
  * 3.2.3 Salida de resultados
* **3.3 Casos de uso o escenarios de ejemplo**

---

## 4. Evidencias de Ejecución (GDB y QEMU)

* **4.1 Ejecución en QEMU**

  * 4.1.1 Capturas de pantalla o logs de ejecución
  * 4.1.2 Explicación de la salida obtenida
* **4.2 Debugging con GDB**

  * 4.2.1 Ejemplo de sesión GDB paso a paso
  * 4.2.2 Breakpoints utilizados
  * 4.2.3 Validación de resultados (registros, memoria, etc.)

---

## 5. Resultados y Discusión

* **5.1 Resultados generales de la implementación**
* **5.2 Análisis de rendimiento**

  * 5.2.1 Tiempo de ejecución aproximado / eficiencia
  * 5.2.2 Diferencias entre C y ensamblador en el proyecto
* **5.3 Limitaciones actuales**
* **5.4 Posibles mejoras futuras**

---

## 6. Guía de Uso: Compilación, Ejecución y Pruebas

* **6.1 Requisitos previos**

  * Instalación de `gcc`, `make`, `qemu`, `gdb`, etc.
* **6.2 Compilación**

  * Ejemplo de comando con `make` o `gcc`
* **6.3 Ejecución en QEMU**

  * Ejemplo de ejecución básica
* **6.4 Depuración con GDB**

  * Ejemplo de conexión con QEMU (`target remote`)
* **6.5 Ejemplos de uso del sistema**

  * Entrada esperada
  * Salida obtenida

---

## 7. Conclusiones

* **7.1 Principales aprendizajes del proyecto**
* **7.2 Relevancia para la arquitectura de computadores**
* **7.3 Reflexión personal / académica**

---

## 8. Referencias
