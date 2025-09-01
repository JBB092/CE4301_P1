#include <stdio.h>
#include <stdint.h>
#include "uart.h"

int main(void) {
    uart_init();

    printf("=== Bare-metal printf demo ===\n");
    printf("Hola mundo desde RISC-V bare-metal!\n");

    int numero = 1234;
    printf("Numero decimal: %d\n", numero);
    printf("Numero hexadecimal: 0x%x\n", numero);

    char *mensaje = "UART funcionando con printf";
    printf("Mensaje: %s\n", mensaje);

    while (1) {
        // bucle infinito para que QEMU no termine
    }

    return 0;
}
