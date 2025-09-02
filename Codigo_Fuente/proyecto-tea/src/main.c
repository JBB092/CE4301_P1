/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/

#include <stdint.h>
#include <stddef.h>
#include "tea.h"
#include "padding.h"  

#include "print.h"
#include "print_hex.h"

/* Cambiar aquí el mensaje de prueba */
static const uint8_t MSG[] = "Hola profe desde QEMU";   // cambiar mensaje por cualquiera
static const size_t MSG_LEN = sizeof(MSG) - 1; // quitar '\0'

/* Clave de 128 bits (4 x 32 bits) */
static const uint32_t KEY[4] = {
    0x12345678u, 0x9ABCDEF0u, 0xFEDCBA98u, 0x76543210u
};

/* VARIABLES GLOBALES */
volatile uint8_t g_plain[32];       // mensaje original con padding (máx 32 bytes de prueba)
volatile uint8_t g_encrypted[32];   // mensaje cifrado
volatile uint8_t g_decrypted[32];   // mensaje descifrado (con padding)
volatile uint8_t g_unpadded[32];    // mensaje final después de quitar padding
volatile uint32_t g_ok;             // bandera de verificación

/* FUNCIONES AUXILIARES */

/* Empaqueta 4 bytes en un uint32_t en orden little-endian */
static inline uint32_t pack_le(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
    return  ((uint32_t)b0)
          | ((uint32_t)b1 << 8)
          | ((uint32_t)b2 << 16)
          | ((uint32_t)b3 << 24);
}

/* Desempaqueta un uint32_t a 4 bytes (LE) */
static inline void unpack_le(uint32_t w, uint8_t *out) {
    out[0] = (uint8_t)(w & 0xFF);
    out[1] = (uint8_t)((w >> 8) & 0xFF);
    out[2] = (uint8_t)((w >> 16) & 0xFF);
    out[3] = (uint8_t)((w >> 24) & 0xFF);
}

/* PROGRAMA PRINCIPAL */

int main(void) {
    /* Aplicar padding */
    size_t padded_len = pkcs7_pad(MSG, MSG_LEN, 8, (uint8_t*)g_plain);

    /* Cifrar bloque por bloque (8 bytes = 2 words de 32 bits) */
    for (size_t i = 0; i < padded_len; i += 8) {
        uint32_t v[2];
        v[0] = pack_le(g_plain[i], g_plain[i+1], g_plain[i+2], g_plain[i+3]);
        v[1] = pack_le(g_plain[i+4], g_plain[i+5], g_plain[i+6], g_plain[i+7]);

        tea_encrypt_asm(v, KEY);

        unpack_le(v[0], &((uint8_t*)g_encrypted)[i]);
        unpack_le(v[1], &((uint8_t*)g_encrypted)[i+4]);
    }

    /* Descifrar bloque por bloque */
    for (size_t i = 0; i < padded_len; i += 8) {
        uint32_t w[2];
        w[0] = pack_le(g_encrypted[i], g_encrypted[i+1], g_encrypted[i+2], g_encrypted[i+3]);
        w[1] = pack_le(g_encrypted[i+4], g_encrypted[i+5], g_encrypted[i+6], g_encrypted[i+7]);

        tea_decrypt_asm(w, KEY);

        unpack_le(w[0], &((uint8_t*)g_decrypted)[i]);
        unpack_le(w[1], &((uint8_t*)g_decrypted)[i+4]);
    }

    /* Remover padding */
    size_t unpadded_len = pkcs7_unpad((uint8_t*)g_decrypted, padded_len, 8, (uint8_t*)g_unpadded);

    /* Verificación */
    g_ok = 0xDEADDEADu; // asume error por defecto
    if (unpadded_len == MSG_LEN) {
        g_ok = 0x600D600Du;   // "GOOD"
    }

    print("Mensaje inicial: %s\n", MSG);

    print("g_ok como texto: %d\n", g_ok);
    print_hex("g_plain (HEX): ", (const uint8_t*)g_plain, padded_len);
    print_hex("g_encrypted (HEX): ", (const uint8_t*)g_encrypted, padded_len);
    print_hex("g_decrypted (HEX): ", (const uint8_t*)g_decrypted, padded_len);
    print_hex("g_unpadded (HEX): ", (const uint8_t*)g_unpadded, unpadded_len);

    print("Mensaje final (g_unpadded): %s\n", g_unpadded);

    /* Loop infinito para poder inspeccionar con GDB */
    for (;;);

}
