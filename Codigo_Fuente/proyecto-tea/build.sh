#!/bin/bash
# Build script para proyecto TEA (Sprint 2 - Task 4)

echo "Compilando proyecto TEA con funciones ASM..."

# Compilar startup.s
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/startup.s -o startup.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de startup.s"
    exit 1
fi

# Compilar main.c (habilitar integración ASM con -DTEA_USE_ASM)
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -DTEA_USE_ASM \
    -c src/main.c -o main.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de main.c"
    exit 1
fi

# Compilar tea.c (opcional, solo por compatibilidad si TEA_USE_ASM está deshabilitado en algún momento)
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/tea.c -o tea.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de tea.c"
    exit 1
fi

# Compilar tea_encrypt.s
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/tea_encrypt.s -o tea_encrypt.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de tea_encrypt.s"
    exit 1
fi

# Compilar tea_decrypt.s
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/tea_decrypt.s -o tea_decrypt.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de tea_decrypt.s"
    exit 1
fi

# Enlazar objetos en test.elf
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    startup.o main.o tea.o tea_encrypt.o tea_decrypt.o \
    -T linker.ld \
    -o test.elf

if [ $? -eq 0 ]; then
    echo "Compilación y enlace exitoso: test.elf generado"
    echo "Archivos objeto: startup.o, main.o, tea.o, tea_encrypt.o, tea_decrypt.o"
else
    echo "Error en el enlace"
    exit 1
fi
