%ifndef MATH_ASM
%define MATH_ASM

%include "asm/regs.asm"

; %1 = %2 * ax -- 8.8 * 8.8 -> 8.8
; clobbers ax, dx, but ax can be used as the output %1
%macro mult8x8  2
    imul    %2
    mov     lowbyte(%1),  ah
    mov     highbyte(%1), dl
%endmacro

%endif