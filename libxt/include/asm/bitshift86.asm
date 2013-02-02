%include "asm/regs.asm"

; helpers for shifting by a fixed number of bits.
; optimized for 8088/8086

; first argument is the register, second is the number of bits.
; only needs to worry about <= 7 bits (asm/bitshift.asm handles higher)
; cycle counts for logical shifts:
;   1 bit  ->  2 cycles      2 bits ->  4 cycles
;   3 bits ->  6 cycles      4 bits ->  8 cycles
;   5 bits -> 10 cycles      6 bits -> 12 cycles
;   7 bits -> 10 cycles
%macro xshr_intl 2
    %if %2 >= 7
        xchg    lowbyte(%1),  highbyte(%1)
        times   (8 - %2) rol %1, 1
        and     %1, 0xffff >> %2
    %else
        times   %2 shr %1, 1
    %endif
%endmacro

%macro xshl_intl 2
    %if %2 >= 7
        xchg    lowbyte(%1),  highbyte(%1)
        times   (8 - %2) ror %1, 1
        and     %1, (0xffff << %2) & 0xffff
    %else
        times   %2 shl %1, 1
    %endif
%endmacro

; arithmetic shift right. cycle counts:
;   1 bit  ->  2 cycles      2 bits ->  4 cycles
;   3 bits ->  6 cycles      4 bits ->  8 cycles
;   5 bits -> 10 cycles      6 bits -> 12 cycles
;   7 bits -> 14 cycles
%macro xsar_intl 2
    times   %2 sar %1, 1
%endmacro

; rotates. cycles counts:
;   1 bit  ->  2 cycles      2 bits ->  4 cycles
;   3 bits ->  6 cycles      4 bits ->  8 cycles
;   5 bits -> 10 cycles      6 bits -> 12 cycles
;   7 bits -> 14 cycles
%macro xrol_intl 2
    times   %2 rol %1, 1
%endmacro

%macro xror_intl 2
    times   %2 ror %1, 1
%endmacro
