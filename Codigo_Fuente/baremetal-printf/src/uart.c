/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#include "uart.h"

#define UART0_BASE 0x10000000
#define UART_THR   0x00
#define UART_LSR   0x05
#define LSR_THRE   0x20

/**
 * @brief Escribe un valor de 8 bits en un registro UART.
 * 
 * @param addr Dirección del registro.
 * @param val  Valor a escribir.
 */
static inline void write_reg(uint32_t addr, uint8_t val) {
    *(volatile uint8_t*)(addr) = val;
}

/**
 * @brief Lee un valor de 8 bits desde un registro UART.
 * 
 * @param addr Dirección del registro.
 * @return uint8_t Valor leído.
 */
static inline uint8_t read_reg(uint32_t addr) {
    return *(volatile uint8_t*)(addr);
}

/**
 * @brief Inicializa el UART.
 * 
 * Esta implementación es un placeholder y no realiza ninguna acción.
 */
void uart_init(void) {
}

/**
 * @brief Envía un carácter por UART.
 * 
 * Espera a que el transmisor esté listo antes de enviar el carácter.
 * 
 * @param c Carácter a enviar.
 */
void uart_putc(char c) {
    while ((read_reg(UART0_BASE + UART_LSR) & LSR_THRE) == 0);
    write_reg(UART0_BASE + UART_THR, c);
}

/**
 * @brief Envía una cadena de caracteres por UART.
 * 
 * Convierte '\n' en '\r\n' para compatibilidad con terminales.
 * 
 * @param s Cadena a enviar.
 */
void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}
