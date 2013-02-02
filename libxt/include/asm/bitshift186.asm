; helpers for shifting by a fixed number of bits.
; optimized for 80188/80186+ (including NEC V20/V30)

; cycle counts are 5 + bits for 80186, and 7 + bits for V20
%macro xshr_intl 2
    shr     %1, %2
%endmacro

%macro xshl_intl 2
    shl     %1, %2
%endmacro

%macro xsar_intl 2
    sar     %1, %2
%endmacro

%macro xrol_intl 2
    rol     %1, %2
%endmacro

%macro xror_intl 2
    ror     %1, %2
%endmacro
