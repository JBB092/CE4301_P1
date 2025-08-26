#!/bin/bash
# Build script para proyecto TEA (Task 4)

echo "Compilando proyecto TEA..."

# Compilar main.c
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c src/main.c -o main.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de main.c"
    exit 1
fi

# Compilar tea.c
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    -c src/tea.c -o tea.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de tea.c"
    exit 1
fi

# Enlazar objetos en test.elf
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 \
    -gdwarf-4 \
    main.o tea.o \
    -T linker.ld \
    -o test.elf

if [ $? -eq 0 ]; then
    echo "Compilación y enlace exitoso test.elf generado"
    echo "Archivos objeto main.o, tea.o"
else
    echo "Error en el enlace"
    exit 1
fi
