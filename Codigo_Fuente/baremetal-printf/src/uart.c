#include "uart.h"

#define UART0_BASE 0x10000000
#define UART_THR   0x00
#define UART_LSR   0x05
#define LSR_THRE   0x20

static inline void write_reg(uint32_t addr, uint8_t val) {
    *(volatile uint8_t*)(addr) = val;
}

static inline uint8_t read_reg(uint32_t addr) {
    return *(volatile uint8_t*)(addr);
}

void uart_init(void) {
}

void uart_putc(char c) {
    while ((read_reg(UART0_BASE + UART_LSR) & LSR_THRE) == 0);
    write_reg(UART0_BASE + UART_THR, c);
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n')
            uart_putc('\r');
        uart_putc(*s++);
    }
}
