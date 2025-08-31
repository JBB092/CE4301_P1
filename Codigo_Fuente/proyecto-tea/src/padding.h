/*
================================== LICENCIA ==============
====================================
MIT License
Copyright (c) 2025 José Bernardo Barquero Bonilla
Consulta el archivo LICENSE para más detalles.
=======================================================
=======================================
*/

#ifndef PADDING_H
#define PADDING_H

#include <stdint.h>
#include <stddef.h>


size_t pkcs7_pad(const uint8_t *input, size_t len, size_t block, uint8_t *output);


size_t pkcs7_unpad(const uint8_t *input, size_t len, size_t block, uint8_t *output);

#endif
