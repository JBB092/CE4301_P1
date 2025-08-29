#include <stdint.h>
#include "tea.h"

/* Clave de 128 bits (4 x 32 bits) */
static const uint32_t KEY[4] = {
    0x12345678u, 0x9ABCDEF0u, 0xFEDCBA98u, 0x76543210u
};

/* Variables globales para inspección con GDB */
volatile uint32_t g_plain[2];     // bloque original (HOLA1234)
volatile uint32_t g_encrypted[2]; // bloque cifrado
volatile uint32_t g_decrypted[2]; // bloque descifrado
volatile uint32_t g_ok;           // bandera de verificación

/* Empaqueta 4 bytes en un uint32_t en orden little-endian */
static inline uint32_t pack_le(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
    return  ((uint32_t)b0)
          | ((uint32_t)b1 << 8)
          | ((uint32_t)b2 << 16)
          | ((uint32_t)b3 << 24);
}

int main(void) {
    /* Mensaje de prueba: "HOLA1234" = 8 bytes = 64 bits */
    const uint8_t msg[8] = { 'H','O','L','A','1','2','3','4' };

    /* Cargar el bloque de 64 bits en dos palabras de 32 bits (LE) */
    g_plain[0] = pack_le(msg[0], msg[1], msg[2], msg[3]);
    g_plain[1] = pack_le(msg[4], msg[5], msg[6], msg[7]);

    /* Copia de trabajo para cifrar */
    uint32_t v[2] = { g_plain[0], g_plain[1] };
    tea_encrypt_asm(v, KEY);              // redirige a ASM si se compila con -DTEA_USE_ASM
    g_encrypted[0] = v[0];
    g_encrypted[1] = v[1];

    /* Copia de trabajo para descifrar */
    uint32_t w[2] = { g_encrypted[0], g_encrypted[1] };
    tea_decrypt_asm(w, KEY);              // redirige a ASM con -DTEA_USE_ASM
    g_decrypted[0] = w[0];
    g_decrypted[1] = w[1];

    /* Verificación: decrypt(encrypt(x)) debe ser igual a x */
    if (g_decrypted[0] == g_plain[0] && g_decrypted[1] == g_plain[1]) {
        g_ok = 0x600D600Du;   // "GOOD"
    } else {
        g_ok = 0xDEADDEADu;   // fallo
    }

    /* Loop infinito para poder inspeccionar con GDB */
    for (;;)
        ;

    // return 0; // nunca llega
}
