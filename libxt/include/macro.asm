; push multiple registers to the stack at once
%macro xpush 1-*
    %rep %0
        push    %1
    %rotate 1
    %endrep
%endmacro

; pop multiple registers from the stack at once, in reverse order
%macro xpop 1-*
    %rep %0
    %rotate -1
        pop     %1
    %endrep
%endmacro

; macros to get the name of the high byte of a register
%define high_ax         ah
%define high_bx         bh
%define high_cx         ch
%define high_dx         dh
%define highbyte(reg)   high_ %+ reg

; macros to get the name of the high byte of a register
%define low_ax          al
%define low_bx          bl
%define low_cx          cl
%define low_dx          dl
%define lowbyte(reg)    low_ %+ reg

; helpers for shifting by a fixed number of bits.
; first argument is the register, second is the number of bits.
; cycle counts for logical shifts:
;   1 bit  ->  2 cycles      2 bits ->  4 cycles
;   3 bits ->  6 cycles      4 bits ->  8 cycles
;   5 bits -> 10 cycles      6 bits -> 12 cycles
;   7 bits -> 10 cycles      8 bits ->  5 cycles
;   9 bits ->  7 cycles     10 bits ->  9 cycles
;  11 bits -> 11 cycles     12 bits -> 12 cycles
;  13 bits -> 10 cycles     14 bits ->  8 cycles
;  15 bits ->  6 cycles     16 bits ->  3 cycles
%macro xshr 2
    %if %2 >= 16
        xor     %1, %1
    %elif %2 >= 12
        times   (16 - %2) rol %1, 1
        and     %1, 0xffff >> %2
    %elif %2 >= 8
        mov     lowbyte(%1),  highbyte(%1)
        xor     highbyte(%1), highbyte(%1)
        times   (%2 - 8) shr %1, 1
    %elif %2 >= 7
        xchg    lowbyte(%1),  highbyte(%1)
        times   (8 - %2) rol %1, 1
        and     %1, 0xffff >> %2
    %else
        times   %2 shr %1, 1
    %endif
%endmacro

%macro xshl 2
    %if %2 >= 16
        xor     %1, %1
    %elif %2 >= 12
        times   (16 - %2) ror %1, 1
        and     %1, (0xffff << %2) & 0xffff
    %elif %2 >= 8
        mov     highbyte(%1), lowbyte(%1)
        xor     lowbyte(%1),  lowbyte(%1)
        times   (%2 - 8) shl %1, 1
    %elif %2 >= 7
        xchg    lowbyte(%1),  highbyte(%1)
        times   (8 - %2) ror %1, 1
        and     %1, (0xffff << %2) & 0xffff
    %else
        times   %2 shl %1, 1
    %endif
%endmacro

; arithmetic shift left is the same as a logical shift left
%macro xsal 2
    xshl    %1, %2
%endmacro

; arithmetic shift right. if 8 <= bits < 15, fastest if performed on ax.
; cycle counts for shifting ax:
;   1 bit  ->  2 cycles      2 bits ->  4 cycles
;   3 bits ->  6 cycles      4 bits ->  8 cycles
;   5 bits -> 10 cycles      6 bits -> 12 cycles
;   7 bits -> 14 cycles      8 bits ->  4 cycles
;   9 bits ->  6 cycles     10 bits ->  8 cycles
;  11 bits -> 10 cycles     12 bits -> 12 cycles
;  13 bits -> 14 cycles     14 bits -> 16 cycles
;  15 bits ->  5 cycles     16 bits ->  5 cycles
; cycle counts for shifting other registers:
;   1 bit  ->  2 cycles      2 bits ->  4 cycles
;   3 bits ->  6 cycles      4 bits ->  8 cycles
;   5 bits -> 10 cycles      6 bits -> 12 cycles
;   7 bits -> 14 cycles      8 bits -> 10 cycles
;   9 bits -> 12 cycles     10 bits -> 14 cycles
;  11 bits -> 16 cycles     12 bits -> 18 cycles
;  13 bits -> 20 cycles     14 bits -> 22 cycles
;  15 bits ->  5 cycles     16 bits ->  5 cycles
%macro xsar 2
    %if %2 >= 15
        rol     highbyte(%1), 1
        sbb     %1, %1
    %elif %2 >= 8
        %ifnidni %1,ax
            xchg    ax, %1
        %endif

        mov     al, ah
        cbw

        %ifnidni %1,ax
            xchg    ax, %1
        %endif

        times   (%2 - 8) sar %1, 1
    %else
        times   %2 sar %1, 1
    %endif
%endmacro
