%include "macro.asm"

    [bits    16]
    [section .text]

    global sqrt_turkowski_
    ; www.realitypixels.com/turk/computergraphics/InverseSqrt.pdf
    ; input  = ax
    ; output = ax
sqrt_turkowski_:
    ; ax = remLo
    ; bx = remHi
    ; cx = root
    ; dx = testDiv
    xpush   bx, cx, dx

    xor     bx, bx
    xor     cx, cx
%rep 8 + (8/2)
    call    turkowski_iteration
%endrep

    mov     ax, cx
    xpop    bx, cx, dx
    ret

turkowski_iteration:
    ; remHi = (remHi << 2) | (remLo >> 14); remLo <<= 2;
    rcl     ax, 1
    rcl     bx, 1
    rcl     ax, 1
    rcl     bx, 1

    ; root <<= 1;
    shl     cx, 1

    ; testDiv = (root << 1) + 1;
    ; if (remHi >= testDiv) { remHi -= testDiv; root++; }
    mov     dx, bx
    sub     dx, cx
    sub     dx, cx
    dec     dx
    jl      turkowski_iter_done
    mov     bx, dx
    inc     cx

turkowski_iter_done:
    ret

%macro arm_iter     2
    ;dx = delta * (2 * root + delta)
    mov     dx, cx
    shl     dx, 1
    add     dx, bx
    %1      dx, %2
    cmp     ax, dx
    jle     %%skip

    sub     ax, dx
    add     cx, bx

%%skip:
    shr     bx, 1
%endmacro

    global sqrt_arm_
    ; https://groups.google.com/d/msg/comp.sys.arm/E-FYsVPD8aA/v6g09oDEHn0J
    ; input  = ax
    ; output = ax
sqrt_arm_:
    ; ax = M
    ; bx = delta
    ; cx = root
    ; dx = tmp
    xpush   bx, cx, dx

    mov     bx, 0x0800
    xor     cx, cx

    arm_iter    xshl, 3     ; delta = 8
    arm_iter    xshl, 2     ; delta = 4
    arm_iter    xshl, 1     ; delta = 2
    arm_iter    xshl, 0     ; delta = 1
    arm_iter    xshr, 1     ; delta = 1/2
    arm_iter    xshr, 2     ; delta = 1/4
    arm_iter    xshr, 3     ; delta = 1/8
    arm_iter    xshr, 4     ; delta = 1/16
    arm_iter    xshr, 5     ; delta = 1/32
    arm_iter    xshr, 6     ; delta = 1/64
    arm_iter    xshr, 7     ; delta = 1/128
    arm_iter    xshr, 8     ; delta = 1/256

    mov     ax, cx
    xpop    bx, cx, dx
    ret