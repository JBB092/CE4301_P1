    .section .text
    .global tea_decrypt_asm
    .align 2

# void tea_decrypt(uint32_t v[2], const uint32_t key[4])
# a0 = v (puntero a bloque de 2 words)
# a1 = key (puntero a clave de 4 words)

tea_decrypt_asm:
    addi sp, sp, -16        # reservar stack frame
    sw   ra, 12(sp)         # guardar return address
    sw   s0, 8(sp)          # guardar s0
    sw   s1, 4(sp)          # guardar s1
    sw   s2, 0(sp)          # guardar s2

    lw   s0, 0(a0)          # v0 = v[0]
    lw   s1, 4(a0)          # v1 = v[1]
    li   t0, 32             # contador = NUM_ROUNDS

    # sum = DELTA * NUM_ROUNDS = 0x9e3779b9 * 32
    li   t6, 0x9e3779b9     # DELTA
    li   s2, 0              # sum = 0
    li   t1, 32
    mul  s2, t6, t1         # sum = DELTA * 32

loop_decrypt:
    # --- v1 update ---
    sll  t1, s0, 4          # (v0 << 4)
    lw   t2, 8(a1)          # key[2]
    add  t1, t1, t2         # (v0 << 4) + key[2]

    add  t2, s0, s2         # (v0 + sum)
    xor  t1, t1, t2

    srl  t2, s0, 5          # (v0 >> 5)
    lw   t3, 12(a1)         # key[3]
    add  t2, t2, t3

    xor  t1, t1, t2
    sub  s1, s1, t1         # v1 -= expr

    # --- v0 update ---
    sll  t1, s1, 4          # (v1 << 4)
    lw   t2, 0(a1)          # key[0]
    add  t1, t1, t2

    add  t2, s1, s2         # (v1 + sum)
    xor  t1, t1, t2

    srl  t2, s1, 5          # (v1 >> 5)
    lw   t3, 4(a1)          # key[1]
    add  t2, t2, t3

    xor  t1, t1, t2
    sub  s0, s0, t1         # v0 -= expr

    sub  s2, s2, t6         # sum -= DELTA

    addi t0, t0, -1         # contador--
    bnez t0, loop_decrypt

    # guardar resultados
    sw   s0, 0(a0)          # v[0] = v0
    sw   s1, 4(a0)          # v[1] = v1

    # restaurar registros
    lw   s2, 0(sp)
    lw   s1, 4(sp)
    lw   s0, 8(sp)
    lw   ra, 12(sp)
    addi sp, sp, 16

    ret
