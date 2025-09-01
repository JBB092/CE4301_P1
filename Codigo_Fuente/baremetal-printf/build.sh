#!/bin/bash
# Build script para baremetal-printf

echo "Limpiando archivos objeto y ejecutable previos..."
rm -f startup.o main.o syscalls.o uart.o print.o test.elf

echo "Compilando proyecto baremetal-printf..."

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

# Compilar main.c
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/main.c -o main.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de main.c"
    exit 1
fi

# Compilar syscalls.c
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/syscalls.c -o syscalls.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de syscalls.c"
    exit 1
fi

# Compilar uart.c
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/uart.c -o uart.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de uart.c"
    exit 1
fi

# Compilar print.c (nuestra implementación de printf)
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/print.c -o print.o
if [ $? -ne 0 ]; then
    echo "Error en la compilación de print.c"
    exit 1
fi

# Enlazar en test.elf
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    startup.o main.o syscalls.o uart.o print.o \
    -T linker.ld \
    -o test.elf

if [ $? -eq 0 ]; then
    echo "Compilación y enlace exitoso: test.elf generado"
    echo "Archivos objeto: startup.o, main.o, syscalls.o, uart.o, print.o"
else
    echo "Error en el enlace"
    exit 1
fi
