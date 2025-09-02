/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>

/**
 * @brief Inicializa el UART.
 */
void uart_init(void);

/**
 * @brief Envía un carácter por UART.
 * 
 * @param c Carácter a enviar.
 */
void uart_putc(char c);

/**
 * @brief Envía una cadena de caracteres por UART.
 * 
 * @param s Cadena a enviar.
 */
void uart_puts(const char *s);

#endif
