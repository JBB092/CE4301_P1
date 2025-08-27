    .section .text.startup
    .globl _start

_start:
    # Inicializar el stack pointer con el símbolo del linker
    la sp, _stack_top

    # Llamar a main
    call main

# Si main retorna, quedarse en loop infinito
hang:
    j hang
