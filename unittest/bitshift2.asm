%include "asm/bitshift.asm"

%macro define_shift 1
    global asm_shl %+ %1 %+ _
    global asm_shr %+ %1 %+ _
    global asm_sar_ax %+ %1 %+ _
    global asm_sar_bx %+ %1 %+ _

asm_shl %+ %1 %+ _:
    xshl    ax, %1
    ret

asm_shr %+ %1 %+ _:
    xshr    ax, %1
    ret

asm_sar_ax %+ %1 %+ _:
    xsar    ax, %1
    ret

asm_sar_bx %+ %1 %+ _:
    push    bx
    mov     bx, ax
    xsar    bx, %1
    mov     ax, bx
    pop     bx
    ret

%endmacro

    bits    16
    segment code

define_shift  1
define_shift  2
define_shift  3
define_shift  4
define_shift  5
define_shift  6
define_shift  7
define_shift  8
define_shift  9
define_shift 10
define_shift 11
define_shift 12
define_shift 13
define_shift 14
define_shift 15
define_shift 16
