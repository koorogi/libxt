%include "asm/stack.asm"

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

    bits    16
    segment code

    global quat_conj_asm_
    ; input  = [sp+2]
    ; output = [ds:si]
quat_conj_asm_:
    xpush   dx, di, bp
    mov     bp, sp

    mov     ax, ds
    mov     es, ax
    mov     di, si
    lea     si, [bp+8]
    conjugate

    xpop    dx, di, bp
    ret     8
