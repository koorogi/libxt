; calculate conjugate of quaternion at [ds:si] and store at [es:di]
; clobbers ax
%macro  conjugate   0
    lodsw
    stosw
    %rep    3
        lodsw
        neg     ax
        stosw
    %endrep
%endmacro

    [bits    16]
    [section .text]

    global quat_conj_asm_
    ; input  = [sp+2]
    ; output = [ds:si]
quat_conj_asm_:
    push    dx
    push    di
    push    bp
    mov     bp, sp

    mov     ax, ds
    mov     es, ax
    mov     di, si
    lea     si, [bp+8]
    conjugate

    pop     bp
    pop     di
    pop     dx
    ret     8
