/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>

/**
 * @brief Imprime una cadena formateada por UART.
 * 
 * Implementación reducida de printf para sistemas baremetal.
 * Soporta %s, %d, %x, %c y %%.
 * 
 * @param fmt Cadena de formato.
 * @param ... Argumentos variables según el formato.
 */
void print(const char *fmt, ...);

#endif // PRINT_H
