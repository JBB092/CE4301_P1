    .section .text.startup
    .globl  _start
    .p2align 2

_start:
    # 1. Inicializar stack pointer
    la      sp, _stack_top

    # 2. Limpiar la sección .bss
    la      t0, _bss_start
    la      t1, _bss_end
1:
    bgeu    t0, t1, 2f        # si t0 >= t1 -> salir
    sb      zero, 0(t0)       # escribir 0 en la dirección actual
    addi    t0, t0, 1         # avanzar
    j       1b
2:
    # 3. Llamar a main
    call    main

# 4. Si main retorna, quedarse en loop infinito
hang:
    j       hang
