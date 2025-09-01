    .section .text.init
    .globl  _start
    .p2align 2

_start:
    la      sp, _stack_top

    la      t0, _bss_start
    la      t1, _bss_end
1:
    bgeu    t0, t1, 2f
    sb      zero, 0(t0)
    addi    t0, t0, 1
    j       1b
2:
    call    main

hang:
    j       hang
