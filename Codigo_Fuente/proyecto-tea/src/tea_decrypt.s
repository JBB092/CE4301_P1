    .section .text
    .globl  tea_decrypt_asm
    .p2align 2

# void tea_decrypt_asm(uint32_t v[2], const uint32_t key[4])
# a0 = v
# a1 = key

tea_decrypt_asm:
    # Cargar bloque v
    lw      t0, 0(a0)          # t0 = v0
    lw      t1, 4(a0)          # t1 = v1

    # Cargar clave
    lw      t2, 0(a1)          # t2 = key0
    lw      t3, 4(a1)          # t3 = key1
    lw      t4, 8(a1)          # t4 = key2
    lw      t5, 12(a1)         # t5 = key3

    # Constantes y estado
    li      t6, 0x9e3779b9     # DELTA
    li      a2, 0xC6EF3720     # sum = DELTA * 32 (mod 2^32)
    li      a3, 32             # rounds

1:  # loop_decrypt
    # v1 -= ((v0<<4)+k2) ^ (v0+sum) ^ ((v0>>5)+k3)
    sll     a4, t0, 4
    add     a4, a4, t4         # + key2
    add     a5, t0, a2         # (v0 + sum)
    xor     a4, a4, a5
    srl     a5, t0, 5
    add     a5, a5, t5         # + key3
    xor     a4, a4, a5
    sub     t1, t1, a4         # v1 -= expr

    # v0 -= ((v1<<4)+k0) ^ (v1+sum) ^ ((v1>>5)+k1)
    sll     a4, t1, 4
    add     a4, a4, t2         # + key0
    add     a5, t1, a2         # (v1 + sum)
    xor     a4, a4, a5
    srl     a5, t1, 5
    add     a5, a5, t3         # + key1
    xor     a4, a4, a5
    sub     t0, t0, a4         # v0 -= expr

    sub     a2, a2, t6         # sum -= DELTA

    addi    a3, a3, -1
    bnez    a3, 1b

    sw      t0, 0(a0)
    sw      t1, 4(a0)
    ret
