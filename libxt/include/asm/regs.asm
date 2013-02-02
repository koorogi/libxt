%ifndef REGS_ASM
%define REGS_ASM

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

%endif