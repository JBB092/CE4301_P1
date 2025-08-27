#!/bin/bash

# Run QEMU with GDB server for TEA project
echo "Starting QEMU with GDB server on port 1234..."
echo "In another terminal, run: gdb-multiarch test.elf"
echo "Then in GDB: target remote :1234"
echo ""
echo "Useful GDB commands:"
echo "  break main            - break at program start"
echo "  info registers        - show register values"
echo "  x/4wx &g_plain        - examine plain text block"
echo "  x/4wx &g_encrypted    - examine encrypted block"
echo "  x/4wx &g_decrypted    - examine decrypted block"
echo "  p/x g_ok              - check verification flag"

qemu-system-riscv32 \
    -machine virt \
    -nographic \
    -bios none \
    -kernel test.elf \
    -S \
    -gdb tcp::1234
