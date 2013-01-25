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

%define QUAT1(offset)   [bp + offset + 14]
%define QUAT2(offset)   [bp + offset + 22]
%define RET(offset)     [si + offset]

%define W       0
%define X       2
%define Y       4
%define Z       6

; calculates:
;   cx = q1.SRC1a * q2.SRC2a OP1 q1.SRC1b * q2.SRC2b
;   bx = q1.SRC1a * q2.SRC2b OP2 q1.SRC1b * q2.SRC2a
; where %1 = SRC1a, %2 = SRC1b, %3 = SRC2a, %4 = SRC2b, %5 = OP1, %6 = OP2
; NOTE: %2 is just for consistency, it's actually unused. The caller must load
;       q1.SRC1b into es before calling this macro
; clobbers ax, bx, cx, dx, di
%macro qmult_stage  6
    ; cx = q1.SRC1a * q2.SRC2a
    mov     ax, QUAT1(%1)   ; ax = di = q1.SRC1a
    mov     di, ax
    mov     bx, QUAT2(%3)   ; bx = q2.SRC2a
    mult8x8 cx, bx

    ; ax = q1.SRC1a * q2.SRC2b
    ; cx = q1.SRC1a * q2.SRC2a
    mov     ax, di          ; ax = q1.SRC1a
    mov     dx, QUAT2(%4)   ; dx = di = q2.SRC2b
    mov     di, dx
    mult8x8 ax, dx

    ; ax = q1.SRC1b * q2.SRC2a
    ; bx = q1.SRC1a * q2.SRC2b
    ; cx = q1.SRC1a * q2.SRC2a
    xchg    ax, bx          ; ax = q2.SRC2a; bx = q1.SRC1a * q2.SRC2b
    mov     dx, es          ; dx = es = q1.SRC1b
    mult8x8 ax, dx

    ; bx = q1.SRC1a * q2.SRC2b OP2 q1.SRC1b * q2.SRC2a
    ; cx = q1.SRC1a * q2.SRC2a
    %6      bx, ax

    ; ax = q1.SRC1b * q2.SRC2b
    ; bx = q1.SRC1a * q2.SRC2b OP1 q1.SRC1b * q2.SRC2a
    ; cx = q1.SRC1a * q2.SRC2a
    mov     ax, di          ; ax = q2.SRC2b
    mov     dx, es          ; dx = q1.SRC1b
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

    mov         ax, QUAT1(X)
    mov         es, ax

    qmult_stage W, X, W, X, sub, add
    mov         RET(W), cx
    mov         RET(X), bx

    qmult_stage W, X, Y, Z, sub, add
    mov         RET(Y), cx
    mov         RET(Z), bx

    mov         ax, QUAT1(Z)
    mov         es, ax

    qmult_stage Y, Z, Y, Z, add, sub
    sub         RET(W), cx
    add         RET(X), bx

    qmult_stage Y, Z, W, X, add, sub
    add         RET(Y), cx
    sub         RET(Z), bx

    xpop        ax, bx, cx, dx, di, bp
    ret         16

%define ROTATE(offset)  [bp + offset + 18]
%define VECTOR(offset)  [bp + offset + 26]

%define A   0
%define B   2
%define C   4

    global xt_quat_rotate_vect_
    ; input  : rotate = [sp+2], vect = [sp+10]
    ; output : [ds:si]
    ;   ret = rotate * (0, vector) * conjugate(rotate)
    ; which works out to (assuming rotate = w,x,y,z; vector = a,b,c)
    ;   ret.a = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b + 2(xz+wy)*c
    ;   ret.b = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a              + 2(yz-wx)*c
    ;   ret.c = (w^2-x^2-y^2+z^2)*c              + 2(xz-wy)*a + 2(yz+wx)*b
xt_quat_rotate_vect_:
    xpush   ax, bx, cx, dx, di, bp
    xpush   si, ds

    mov     bp, sp

    ; bx = x^2 + y^2
    ; cx = x^2 - y^2
    ; si = xy
    mov     ax, ROTATE(X)
    mov     si, ax          ; si = x
    mult8x8 bx, ax          ; bx = x^2

    mov     ax, ROTATE(Y)
    mov     di, ax          ; di = y
    mult8x8 ax, ax          ; ax = y^2

    mov     cx, bx
    add     bx, ax          ; bx = x^2 + y^2
    sub     cx, ax          ; cx = x^2 - y^2

    mov     ax, si
    mult8x8 ax, di
    mov     si, ax          ; si = xy

    ; bx = w^2 - x^2 - y^2
    ; cx = x^2 - y^2
    ; si = xy
    ; di = w
    ; ds = w^2
    mov     ax, ROTATE(W)
    mov     di, ax          ; di = w
    mult8x8 ax, ax
    mov     ds, ax          ; ds = w^2
    sub     ax, bx
    mov     bx, ax          ; bx = w^2 - x^2 - y^2

    ; ax = w^2 + x^2 - y^2 - z^2
    ; bx = w^2 - x^2 - y^2 + z^2
    ; dx = w^2 - x^2 + y^2 - z^2
    ; es = z
    ; si = xy
    ; di = w
    mov     ax, ROTATE(Z)
    mov     es, ax          ; es = z
    mult8x8 ax, ax          ; ax = z^2
    add     bx, ax          ; bx = w^2 - x^2 - y^2 + z^2

    mov     dx, ds
    sub     dx, ax          ; dx = w^2 - z^2
    mov     ax, dx
    add     ax, cx          ; ax = w^2 + x^2 - y^2 - z^2
    sub     dx, cx          ; dx = w^2 - x^2 + y^2 - z^2

    ; bx = w^2 + x^2 - y^2 - z^2
    ; cx = w^2 - x^2 + y^2 - z^2
    ; ds = w^2 - x^2 - y^2 + z^2
    ; si = xy - wz
    ; di = xy + wz
    mov     ds, bx
    mov     bx, ax
    mov     cx, dx
    mov     ax, es
    mult8x8 ax, di          ; ax = wz
    mov     di, si
    add     di, ax          ; di = xy + wz
    sub     si, ax          ; si = xy - wz

    ; bx = 2(xy + wz) * a
    ; cx = w^2 - x^2 + y^2 - z^2
    ; ds = w^2 - x^2 - y^2 + z^2
    ; si = xy - wz
    ; di = (w^2 + x^2 - y^2 - z^2) * a
    mov     ax, bx
    mov     bx, VECTOR(A)   ; bx = a
    mult8x8 ax, bx
    xchg    ax, di          ; di = (w^2 + x^2 - y^2 - z^2) * a
    shl     bx, 1
    mult8x8 bx, bx          ; bx = 2(xy + wz) * a

    ; ax = 2(xy - wz) * b
    ; bx = 2(xy + wz) * a
    ; cx = 2b
    ; ds = w^2 - x^2 - y^2 + z^2
    ; si = (w^2 - x^2 + y^2 - z^2) * b
    ; di = (w^2 + x^2 - y^2 - z^2) * a
    mov     ax, cx
    mov     cx, VECTOR(B)   ; cx = b
    mult8x8 ax, cx
    xchg    ax, si          ; si = (w^2 - x^2 + y^2 - z^2) * b
    shl     cx, 1           ; cx = 2b
    mult8x8 ax, cx          ; ax = 2(xy - wz) * b

    ; cx = 2b
    ; ds = w^2 - x^2 - y^2 + z^2
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a
    ; di = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b
    add     di, ax
    add     si, bx

    ; bx = yz - wx
    ; cx = 2b
    ; dx = yz + wx
    ; ds = w^2 - x^2 - y^2 + z^2
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a
    ; di = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b
    mov     ax, ROTATE(Y)
    mov     bx, ROTATE(Z)
    mult8x8 bx, bx          ; bx = yz
    mov     ax, ROTATE(W)
    mov     dx, ROTATE(X)
    mult8x8 ax, dx          ; ax = wx
    mov     dx, bx
    add     dx, ax          ; dx = yz + wx
    sub     bx, ax          ; bx = yz - wx

    ; bx = yz - wx
    ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b
    ; es = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a
    ; di = 2c
    mov     es, di
    mov     ax, cx
    mult8x8 cx, dx          ; cx = 2(yz+wx)*b
    mov     ax, ds
    mov     di, VECTOR(C)   ; di = c
    mult8x8 ax, di          ; ax = (w^2-x^2-y^2+z^2)*c
    add     cx, ax          ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b
    shl     di, 1           ; di = 2c

    ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b
    ; es = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a + 2(yz-wx)*c
    ; di = 2c
    mov     ax, bx
    mult8x8 ax, di          ; ax = 2(yz-wx)*c
    add     si, ax

    ; ax = xz + wy
    ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b
    ; dx = xz - wy
    ; es = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a + 2(yz-wx)*c
    ; di = 2c
    mov     ax, ROTATE(W)
    mov     bx, ROTATE(Y)
    mult8x8 bx, bx          ; bx = wy
    mov     ax, ROTATE(X)
    mov     dx, ROTATE(Z)
    mult8x8 ax, dx          ; ax = xz
    mov     dx, ax
    add     ax, bx          ; ax = xz + wy
    sub     dx, bx          ; dx = xz - wy

    ; ax = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b + 2(xz+wy)*c
    ; bx = xz - wy
    ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a + 2(yz-wx)*c
    mov     bx, dx          ; bx = xz - wy
    mult8x8 ax, di          ; ax = 2(xz+wy)*c
    mov     dx, es
    add     ax, dx          ; ax = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b + 2(xz+wy)*c

    ; bx = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b + 2(xz+wy)*c
    ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b + 2(xz-wy)*a
    ; si = (w^2-x^2+y^2-z^2)*b + 2(xy+wz)*a + 2(yz-wx)*c
    xchg    ax, bx          ; bx = (w^2+x^2-y^2-z^2)*a + 2(xy-wz)*b + 2(xz+wy)*c
    mov     dx, VECTOR(A)
    shl     dx, 1
    mult8x8 ax, dx          ; ax = 2(xz-wy)*a
    add     cx, ax          ; cx = (w^2-x^2-y^2+z^2)*c + 2(yz+wx)*b + 2(xz-wy)*a

    ; store result!
    mov     ax, si
    xpop    si, ds
    mov     RET(A), bx
    mov     RET(B), ax
    mov     RET(C), cx

    ; done
    xpop    ax, bx, cx, dx, di, bp
    ret     14
