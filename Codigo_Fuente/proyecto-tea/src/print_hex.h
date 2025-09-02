/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#ifndef PRINT_HEX_H
#define PRINT_HEX_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Imprime un arreglo de bytes en formato hexadecimal precedido por una etiqueta.
 * 
 * @param label Etiqueta que se imprime antes de los datos hexadecimales.
 * @param data Puntero al arreglo de bytes a imprimir.
 * @param len  Cantidad de bytes a imprimir desde el arreglo.
 */
void print_hex(const char *label, const uint8_t *data, size_t len);

#endif // PRINT_HEX_H
