/*
LICENCIA 
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
*/
#include "tea.h"

/*
Función: tea_encrypt
Descripción:
Cifra un bloque de 64 bits (2 palabras de 32 bits) usando el algoritmo TEA (Tiny Encryption Algorithm) con una clave de 128 bits.
Parámetros:
- v: uint32_t[2] - bloque de datos de entrada y salida (se cifra en el lugar).
- key: const uint32_t[4] - clave de cifrado de 128 bits (4 palabras de 32 bits).
Return:
- void - el resultado cifrado se almacena en el arreglo v.
Restricciones:
El arreglo v debe tener exactamente dos elementos de 32 bits. La clave debe tener cuatro elementos de 32 bits.
Ejemplo:
uint32_t bloque[2] = {0x12345678, 0x9abcdef0};
const uint32_t clave[4] = {0xA, 0xB, 0xC, 0xD};
tea_encrypt(bloque, clave);
// bloque ahora contiene el texto cifrado
Referencias:
Tomado del código que adjuntó el profesor en el enunciado del proyecto
*/
void tea_encrypt(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;

    for (int i = 0; i < NUM_ROUNDS; i++) {
        sum += DELTA;
        v0 += ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        v1 += ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
    }

    v[0] = v0;
    v[1] = v1;
}

/*
Función: tea_decrypt
Descripción:
Descifra un bloque de 64 bits (2 palabras de 32 bits) previamente cifrado con TEA, usando la misma clave de 128 bits.
Parámetros:
- v: uint32_t[2] - bloque de datos cifrados de entrada y salida (se descifra en el lugar).
- key: const uint32_t[4] - clave de cifrado de 128 bits (4 palabras de 32 bits).
Return:
- void - el resultado descifrado se almacena en el arreglo v.
Restricciones:
El arreglo v debe tener exactamente dos elementos de 32 bits. La clave debe tener cuatro elementos de 32 bits.
Ejemplo:
uint32_t bloque[2] = {  datos cifrados  };
const uint32_t clave[4] = {0xA, 0xB, 0xC, 0xD};
tea_decrypt(bloque, clave);
// bloque ahora contiene el texto plano original
Referencias:
Tomado del código que adjuntó el profesor en el enunciado del proyecto
*/
void tea_decrypt(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = DELTA * NUM_ROUNDS;

    for (int i = 0; i < NUM_ROUNDS; i++) {
        v1 -= ((v0 << 4) + key[2]) ^ (v0 + sum) ^ ((v0 >> 5) + key[3]);
        v0 -= ((v1 << 4) + key[0]) ^ (v1 + sum) ^ ((v1 >> 5) + key[1]);
        sum -= DELTA;
    }

    v[0] = v0;
    v[1] = v1;
}
