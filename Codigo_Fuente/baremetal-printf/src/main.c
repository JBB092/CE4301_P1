/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#include "print.h"

/**
 * @brief Función principal del programa de ejemplo.
 * 
 * Inicializa el UART y demuestra el uso de la función print
 * con diferentes tipos de datos y formatos.
 * 
 * @return int Código de salida del programa.
 */
int main(void) {
    uart_init();
    print("Hola baremetal!\n");
    print("Numero decimal: %d\n", 1234);
    print("Numero hexadecimal: %x\n", 0xBEEF);
    print("Caracter: %c\n", 'A');
    print("Cadena: %s\n", "Embebidos");
    return 0;
}
