#!/bin/bash
# Build script para proyecto TEA (Sprint 2 - Task 4)

# Limpiar archivos objeto y ejecutable previos para evitar mezclas
echo "Limpiando archivos objeto y ejecutable previos..."
rm -f startup.o tea_decrypt.o tea_encrypt.o main.o test.elf

echo "Compilando proyecto TEA con funciones ASM..."

USE_ASM=1   # 1 = usar ASM, 0 = usar implementación en C

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

# Compilar padding.c
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    -c src/padding.c -o padding.o

if [ $? -ne 0 ]; then
    echo "Error en la compilación de padding.c"
    exit 1
fi

# Decidir qué compilar/enlazar según USE_ASM
if [ "${USE_ASM}" -eq 0 ]; then
    echo "Usando implementación en C (tea.c)..."

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

    OBJ_EXTRA="tea.o"

else
    echo "Usando implementación en ASM (tea_encrypt.s y tea_decrypt.s)..."

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

    OBJ_EXTRA="tea_encrypt.o tea_decrypt.o"
fi

# Enlazar objetos en test.elf
riscv64-unknown-elf-gcc \
    -march=rv32im \
    -mabi=ilp32 \
    -nostdlib \
    -ffreestanding \
    -g3 -gdwarf-4 \
    startup.o main.o padding.o ${OBJ_EXTRA} \
    -T linker.ld \
    -o test.elf

if [ $? -eq 0 ]; then
    echo "Compilación y enlace exitoso: test.elf generado"
    echo "Archivos objeto: startup.o, main.o, padding.o, ${OBJ_EXTRA}"
else
    echo "Error en el enlace"
    exit 1
fi
