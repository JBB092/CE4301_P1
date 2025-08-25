#!/bin/bash
# Build script para proyecto TEA (solo compila tea.c por ahora)

echo "Compilando TEA en C..."

# Compilar tea.c en objeto
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g \
    -c src/tea.c -o tea.o

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa: se generó tea.o"
else
    echo "Error en la compilación de tea.c"
    exit 1
fi
