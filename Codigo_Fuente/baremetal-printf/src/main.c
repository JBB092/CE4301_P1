#include "print.h"

int main(void) {
    uart_init();
    print("Hola baremetal!\n");
    print("Numero decimal: %d\n", 1234);
    print("Numero hexadecimal: %x\n", 0xBEEF);
    print("Caracter: %c\n", 'A');
    print("Cadena: %s\n", "Embebidos");
    return 0;
}
