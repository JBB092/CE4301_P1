/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#include "print_hex.h"
#include "print.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Imprime un arreglo de bytes en formato hexadecimal precedido por una etiqueta.
 * 
 * Esta función imprime la etiqueta proporcionada seguida de los datos en formato hexadecimal,
 * separados por espacios. Cada byte se representa con dos dígitos hexadecimales en mayúsculas.
 * 
 * @param label Etiqueta que se imprime antes de los datos hexadecimales.
 * @param data Puntero al arreglo de bytes a imprimir.
 * @param len  Cantidad de bytes a imprimir desde el arreglo.
 */
void print_hex(const char *label, const uint8_t *data, size_t len) {
    static const char HEX[] = "0123456789ABCDEF";
    print("%s", label);
    for (size_t i = 0; i < len; i++) {
        char buf[3];
        buf[0] = HEX[(data[i] >> 4) & 0xF];
        buf[1] = HEX[data[i] & 0xF];
        buf[2] = '\0';
        print("%s ", buf);
    }
    print("\n");
}
