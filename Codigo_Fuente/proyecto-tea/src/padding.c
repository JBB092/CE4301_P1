#include "padding.h"

/**
 * @brief Aplica PKCS#7 padding a un mensaje.
 *
 * Ejemplo con block=8:
 *   Mensaje: "HOLA" (4 bytes)
 *   → Output: "HOLA\x04\x04\x04\x04"
 *
 * Ejemplo con mensaje exacto de 8 bytes:
 *   "HOLA1234" → "HOLA1234\x08\x08\x08\x08\x08\x08\x08\x08"
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

/**
 * @brief Elimina PKCS#7 padding de un mensaje descifrado.
 *
 * Verifica el último byte y elimina esa cantidad.
 * Ejemplo:
 *   "HOLA\x04\x04\x04\x04" → "HOLA"
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
