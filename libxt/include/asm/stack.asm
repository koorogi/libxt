%ifndef STACK_ASM
%define STACK_ASM

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

%endif