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

    global xt_quat_conj_
    ; input  = [sp+2]
    ; output = [ds:si]
xt_quat_conj_:
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
