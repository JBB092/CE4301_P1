#ifndef TEA_H
#define TEA_H

#include <stdint.h>

#define DELTA 0x9e3779b9
#define NUM_ROUNDS 32

void tea_encrypt(uint32_t v[2], const uint32_t key[4]);
void tea_decrypt(uint32_t v[2], const uint32_t key[4]);

#endif
