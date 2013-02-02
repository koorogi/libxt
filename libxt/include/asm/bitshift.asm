%ifndef BITSHIFT_ASM
%define BITSHIFT_ASM

%include "asm/cpu.asm"
%include "asm/regs.asm"

%if CPU_INSN_80186
    %include "asm/bitshift186.asm"
%else
    %include "asm/bitshift86.asm"
%endif

; the processor-specific implementations only optimize bit shifts up to 7 bits.
; for larger shifts, wer have some generic optimizations we can apply here.

%macro xshr 2
    %if   %2 <= 0
    %elif %2 >= 16
        xor         %1, %1
    %elif %2 >= 12
        xrol_intl   %1, 16 - %2
        and         %1, 0xffff >> %2
    %elif %2 >= 8
        mov         lowbyte(%1),  highbyte(%1)
        xor         highbyte(%1), highbyte(%1)
        xshr_intl   %1, %2 - 8
    %else
        xshr_intl   %1, %2
    %endif
%endmacro

%macro xshl 2
    %if   %2 <= 0
    %elif %2 >= 16
        xor         %1, %1
    %elif %2 >= 12
        xror_intl   %1, 16 - %2
        and         %1, (0xffff << %2) & 0xffff
    %elif %2 >= 8
        mov         highbyte(%1), lowbyte(%1)
        xor         lowbyte(%1),  lowbyte(%1)
        xshl_intl   %1, %2 - 8
    %else
        xshl_intl   %1, %2
    %endif
%endmacro

; arithmetic shift right of >= 8 bits is performed fastest on ax because there
; is an instruction which sign extends al->ax
%macro xsar 2
    %if %2 >= 15
        rol         highbyte(%1), 1
        sbb         %1, %1
    %elif %2 >= 8
        %ifnidni %1,ax
            xchg    ax, %1
        %endif

        mov         al, ah
        cbw

        %ifnidni %1,ax
            xchg    ax, %1
        %endif

        xsar_intl   %1, %2 - 8
    %else
        xsar_intl   %1, %2
    %endif
%endmacro

; arithmetic shift left is the same as a logical shift left
%macro xsal 2
    xshl    %1, %2
%endmacro

%endif