%ifndef CPU_ASM
%define CPU_ASM

%define V20     1
%define V30     2

;%define CPU     8088
;%define CPU     8086
;%define CPU     80188
;%define CPU     80186
%define CPU     V20
;%define CPU     v30

; CPU_INSN_80186 = true iff processor supports 80186 instruction set
%if CPU == V20 || CPU == V30 || CPU == 80188 || CPU == 80186
    %define CPU_INSN_80186  1
%else
    %define CPU_INSN_80186  0
%endif

%endif