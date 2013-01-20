%include "macro.asm"

; calculate conjugate of quaternion at [ds:si] and store at [es:di]
; clobbers ax
%macro  conjugate   0
    lodsw
    stosw
    %rep    3
        lodsw
        neg     ax
        stosw
    %endrep
%endmacro

    [bits    16]
    [section .text]

    global xt_quat_conj_
    ; input  = [sp+2]
    ; output = [ds:si]
xt_quat_conj_:
    xpush   dx, di, bp
    mov     bp, sp

    mov     ax, ds
    mov     es, ax
    mov     di, si
    lea     si, [bp+8]
    conjugate

    xpop    dx, di, bp
    ret     8

%define quat1   bp+14
%define quat2   bp+22

%define W       0
%define X       2
%define Y       4
%define Z       6

; calculates:
;   cx = q1.SRC1a * q2.SRC2a OP1 q1.SRC1b * q2.SRC2b
;   bx = q1.SRC1a * q2.SRC2b OP2 q1.SRC1b * q2.SRC2a
; where %1 = SRC1a, %2 = SRC1b, %3 = SRC2a, %4 = SRC2b, %5 = OP1, %6 = OP2
; clobbers ax, bx, cx, dx, di, es
; TODO: if SRC2a and SRC2b are pre-loaded into di and es, we might be able
;       to avoid a few loads over the course of the entire function
%macro qmult_stage  6
    ; cx = q1.SRC1a * q2.SRC2a
    mov     ax, [quat1 + %1]    ; ax = di = q1.SRC1a
    mov     di, ax
    mov     bx, [quat2 + %3]    ; bx = q2.SRC2a
    mult8x8 cx, bx

    ; ax = q1.SRC1a * q2.SRC2b
    ; cx = q1.SRC1a * q2.SRC2a
    mov     ax, di              ; ax = q1.SRC1a
    mov     dx, [quat2 + %4]    ; dx = di = q2.SRC2b
    mov     di, dx
    mult8x8 ax, dx

    ; ax = q1.SRC1b * q2.SRC2a
    ; bx = q1.SRC1a * q2.SRC2b
    ; cx = q1.SRC1a * q2.SRC2a
    xchg    ax, bx              ; ax = q2.SRC2a; bx = q1.SRC1a * q2.SRC2b
    mov     dx, [quat1 + %2]    ; dx = es = q1.SRC1b
    mov     es, dx
    mult8x8 ax, dx

    ; bx = q1.SRC1a * q2.SRC2b OP2 q1.SRC1b * q2.SRC2a
    ; cx = q1.SRC1a * q2.SRC2a
    %6      bx, ax

    ; ax = q1.SRC1b * q2.SRC2b
    ; bx = q1.SRC1a * q2.SRC2b OP1 q1.SRC1b * q2.SRC2a
    ; cx = q1.SRC1a * q2.SRC2a
    mov     ax, di              ; ax = q2.SRC2b
    mov     dx, es              ; dx = q1.SRC1b
    mult8x8 ax, dx

    ; bx = q1.SRC1a * q2.SRC2b OP1 q1.SRC1b * q2.SRC2a
    ; cx = q1.SRC1a * q2.SRC2a OP1 q1.SRC1b * q2.SRC2b
    %5      cx, ax
%endmacro

    global xt_quat_mult_
    ; input  : q1 = [sp+2], q2 = [sp+10]
    ; output : [ds:si]
    ;   out.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z)
    ;   out.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y)
    ;   out.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x)
    ;   out.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w)
xt_quat_mult_:
    xpush       ax, bx, cx, dx, di, bp
    mov         bp, sp

    qmult_stage W, X, W, X, sub, add
    mov         [si + W], cx
    mov         [si + X], bx

    qmult_stage Y, Z, Y, Z, add, sub
    sub         [si + W], cx
    add         [si + X], bx

    qmult_stage W, X, Y, Z, sub, add
    mov         [si + Y], cx
    mov         [si + Z], bx

    qmult_stage Y, Z, W, X, add, sub
    add         [si + Y], cx
    sub         [si + Z], bx

    xpop        ax, bx, cx, dx, di, bp
    ret         16
