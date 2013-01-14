    [bits    16]
    [section .text]

    global sqrt_turkowski_
    ; input  = ax
    ; output = ax
sqrt_turkowski_:
    ; ax = remLo
    ; bx = remHi
    ; cx = root
    ; dx = testDiv
    push    bx
    push    cx
    push    dx

    xor     bx, bx
    xor     cx, cx
%rep 8 + (8/2)
    call    turkowski_iteration
%endrep

    mov     ax, cx
    pop     dx
    pop     cx
    pop     bx
    ret

turkowski_iteration:
    ; remHi = (remHi << 2) | (remLo >> 14); remLo <<= 2;
    rcl     ax, 1
    rcl     bx, 1
    rcl     ax, 1
    rcl     bx, 1

    ; root <<= 1;
    shl     cx, 1

    ; testDiv = (root << 1) + 1;
    ; if (remHi >= testDiv) { remHi -= testDiv; root++; }
    mov     dx, bx
    sub     dx, cx
    sub     dx, cx
    dec     dx
    jl      turkowski_iter_done
    mov     bx, dx
    inc     cx

turkowski_iter_done:
    ret
