#!/bin/bash
# Run QEMU directly 
# Para baremetal-printf

if [ ! -f test.elf ]; then
    echo "Error: test.elf no existe. Ejecuta ./build.sh primero."
    exit 1
fi

echo "Ejecutando test.elf en QEMU..."
echo "--------------------------------"
echo ""

qemu-system-riscv32 \
    -machine virt \
    -nographic \
    -bios none \
    -kernel test.elf
