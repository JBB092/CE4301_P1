/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#include "print.h"
#include "uart.h"
#include <stdarg.h>
#include <stdint.h>

/**
 * @brief Imprime un número entero decimal por UART.
 * 
 * @param value Valor entero a imprimir.
 */
static void print_dec(int value) {
    char buffer[16];
    int i = 0;

    if (value == 0) {
        uart_putc('0');
        return;
    }

    if (value < 0) {
        uart_putc('-');
        value = -value;
    }

    while (value > 0 && i < (int)sizeof(buffer)) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (--i >= 0) {
        uart_putc(buffer[i]);
    }
}

/**
 * @brief Imprime un número entero sin signo en formato hexadecimal por UART.
 * 
 * @param value Valor entero sin signo a imprimir.
 */
static void print_hex(unsigned int value) {
    const char *hex_chars = "0123456789ABCDEF";
    uart_puts("0x");
    for (int i = (sizeof(value) * 2) - 1; i >= 0; i--) {
        uart_putc(hex_chars[(value >> (i * 4)) & 0xF]);
    }
}

/**
 * @brief Implementación reducida de printf para sistemas baremetal.
 * 
 * Soporta los siguientes especificadores de formato:
 *   %s - Cadena de caracteres
 *   %d - Entero decimal
 *   %x - Entero hexadecimal
 *   %c - Carácter
 *   %% - Símbolo de porcentaje
 * 
 * @param fmt Cadena de formato.
 * @param ... Argumentos variables según el formato.
 */
void print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (const char *p = fmt; *p; p++) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 's': {
                    const char *str = va_arg(args, const char *);
                    uart_puts(str);
                    break;
                }
                case 'd': {
                    int val = va_arg(args, int);
                    print_dec(val);
                    break;
                }
                case 'x': {
                    unsigned int val = va_arg(args, unsigned int);
                    print_hex(val);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    uart_putc(c);
                    break;
                }
                case '%': {
                    uart_putc('%');
                    break;
                }
                default:
                    uart_putc('%');
                    uart_putc(*p);
                    break;
            }
        } else {
            uart_putc(*p);
        }
    }

    va_end(args);
}
