#!/bin/bash
# Run QEMU with GDB server for baremetal-printf

echo "Starting QEMU with GDB server on port 1234..."
echo "In another terminal, run: gdb-multiarch test.elf"
echo "Then in GDB: target remote :1234"
echo ""
echo "Useful GDB commands:"
echo "  break main            - break at program start"
echo "  info registers        - show register values"
echo "  x/s g_buffer          - examine output buffer (if any)"

qemu-system-riscv32 \
    -machine virt \
    -nographic \
    -bios none \
    -kernel test.elf \
    -S \
    -gdb tcp::1234
