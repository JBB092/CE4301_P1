/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#include "padding.h"

/* 
Función: pkcs7_pad
Descripción: 
Aplica el padding PKCS#7 a un mensaje de entrada para que su longitud sea múltiplo del tamaño de bloque especificado.
Parámetros:
- input: const uint8_t* - puntero al mensaje original.
- len: size_t - longitud del mensaje original en bytes.
- block: size_t - tamaño del bloque en bytes.
- output: uint8_t* - puntero al buffer donde se almacena el mensaje con padding.
Return:
- size_t - longitud total del mensaje después de aplicar el padding.
Restricciones:
El buffer de salida debe tener suficiente espacio para almacenar el mensaje original más el padding (hasta block bytes adicionales).
Ejemplo:
size_t padded_len = pkcs7_pad((const uint8_t*)"HOLA", 4, 8, buffer);
// buffer contendrá "HOLA\x04\x04\x04\x04"
Referencias:
https://github.com/GRISHNOV/PKCS7-Padding.git
https://wgallagher86.medium.com/pkcs-7-padding-in-go-6da5d1d14590
*/
size_t pkcs7_pad(const uint8_t *input, size_t len, size_t block, uint8_t *output) {
    // Copiar mensaje original
    for (size_t i = 0; i < len; i++) {
        output[i] = input[i];
    }

    // Calcular número de bytes de padding
    size_t pad_len = block - (len % block);
    if (pad_len == 0) pad_len = block;  // Caso mensaje exacto múltiplo de block

    // Rellenar con el valor pad_len
    for (size_t i = 0; i < pad_len; i++) {
        output[len + i] = (uint8_t)pad_len;
    }

    return len + pad_len;  // Nuevo tamaño
}

/* 
Función: pkcs7_unpad
Descripción: 
Elimina el padding PKCS#7 de un mensaje, verificando que el padding sea válido y devolviendo solo el mensaje original.
Parámetros:
- input: const uint8_t* - puntero al mensaje con padding.
- len: size_t - longitud total del mensaje con padding.
- block: size_t - tamaño del bloque en bytes.
- output: uint8_t* - puntero al buffer donde se almacena el mensaje sin padding.
Return:
- size_t - longitud del mensaje original sin padding. Devuelve 0 si el padding es inválido.
Restricción:
El mensaje de entrada debe tener longitud múltiplo del tamaño de bloque y contener padding válido.
Ejemplo:
size_t msg_len = pkcs7_unpad(buffer, 8, 8, out);
// out contendrá "HOLA" si buffer era "HOLA\x04\x04\x04\x04"
Referencias:
https://github.com/GRISHNOV/PKCS7-Padding.git
https://wgallagher86.medium.com/pkcs-7-padding-in-go-6da5d1d14590
*/
size_t pkcs7_unpad(const uint8_t *input, size_t len, size_t block, uint8_t *output) {
    if (len == 0 || len % block != 0) {
        return 0;  // Error: tamaño inválido
    }

    // Último byte indica cuántos se rellenaron
    uint8_t pad_len = input[len - 1];

    // Validar valor de padding
    if (pad_len == 0 || pad_len > block) {
        return 0;  // Error: padding inválido
    }

    size_t new_len = len - pad_len;

    // Copiar mensaje sin padding
    for (size_t i = 0; i < new_len; i++) {
        output[i] = input[i];
    }

    return new_len;
}
