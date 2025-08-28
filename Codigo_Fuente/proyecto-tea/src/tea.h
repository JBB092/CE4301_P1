#ifndef TEA_H
#define TEA_H

#include <stdint.h>

#define DELTA 0x9e3779b9u
#define NUM_ROUNDS 32

/* Prototipos en C (implementación de referencia) */
void tea_encrypt(uint32_t v[2], const uint32_t key[4]);
void tea_decrypt(uint32_t v[2], const uint32_t key[4]);

/* Prototipos en ASM (implementaciones RISC-V) */
void tea_encrypt_asm(uint32_t v[2], const uint32_t key[4]);
void tea_decrypt_asm(uint32_t v[2], const uint32_t key[4]);

/*
 * Selector de implementación:
 * - Si compilas con -DTEA_USE_ASM, redirige tea_encrypt/decrypt
 *   a las versiones en ensamblador.
 * - Si NO defines TEA_USE_ASM, usas la versión C (útil para comparar).
 */
#ifdef TEA_USE_ASM
#  undef  tea_encrypt
#  undef  tea_decrypt
#  define tea_encrypt  tea_encrypt_asm
#  define tea_decrypt  tea_decrypt_asm
#endif

#endif /* TEA_H */
