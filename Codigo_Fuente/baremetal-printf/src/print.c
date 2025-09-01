#include <stdarg.h>
#include <stdint.h>
#include "uart.h"

static void print_uint(unsigned int value, int base) {
    char buf[32];
    const char *digits = "0123456789abcdef";
    int i = 30;
    buf[31] = '\0';

    if (value == 0) {
        uart_putc('0');
        return;
    }

    while (value && i) {
        buf[i--] = digits[value % base];
        value /= base;
    }
    uart_puts(&buf[i + 1]);
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': {
                    char *str = va_arg(args, char*);
                    uart_puts(str);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    uart_putc(c);
                    break;
                }
                case 'd': {
                    int val = va_arg(args, int);
                    if (val < 0) {
                        uart_putc('-');
                        val = -val;
                    }
                    print_uint((unsigned int)val, 10);
                    break;
                }
                case 'x': {
                    unsigned int val = va_arg(args, unsigned int);
                    uart_puts("0x");
                    print_uint(val, 16);
                    break;
                }
                case '%': {
                    uart_putc('%');
                    break;
                }
                default: {
                    uart_putc('%');
                    uart_putc(*fmt);
                    break;
                }
            }
        } else {
            uart_putc(*fmt);
        }
        fmt++;
    }

    va_end(args);
    return 0;
}
