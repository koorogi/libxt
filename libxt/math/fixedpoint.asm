%include "macro.asm"

    [bits    16]
    [section .text]

    global xt_fixed_8x8_
    ; ax = number1
    ; dx = number2
    ; return in ax
xt_fixed_8x8_:
    imul    dx
    mov     al, ah
    mov     ah, dl
    ret

    global xt_fixed_8d8_
    ; ax = numerator
    ; bx = denominator
    ; return in ax, clobber dx
xt_fixed_8d8_:
    mov     dx, ax
    ; large arithmetic right shifts are much faster on ax than dx
    xsar    ax, 8
    xsal    dx, 8
    xchg    ax, dx
    idiv    bx
    ret
