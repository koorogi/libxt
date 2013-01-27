%include "macro.asm"

    bits    16
    segment code

    global xt_fixed_8x8_
    ; ax = number1
    ; dx = number2
    ; return in ax
xt_fixed_8x8_:
    mult8x8 ax, dx
    ret

    global xt_fixed_8d8_
    ; ax = numerator
    ; bx = denominator
    ; return in ax, clobber dx
xt_fixed_8d8_:
    mov     dx, ax
    ; large arithmetic right shifts are much faster on ax than dx
    xsar    ax, 8
    xsal    dx, 8
    xchg    ax, dx
    idiv    bx
    ret

%macro sqrtapprox 1
    xshr    ax, %1
    xlat
    xshl    ax, %1 / 2
%endmacro

    global xt_fixed_sqrt_
    ; input  = ax
    ; output = ax
xt_fixed_sqrt_:
    xpush   bx

    mov     bx, sqrttable

    test    ah, ah
    jz      smallsqrt

    test    ah, 0xf0
    jz      mediumsqrt

largesqrt:
    sqrtapprox 8
    xpop    bx
    ret

mediumsqrt:
    sqrtapprox 4
    xpop    bx
    ret

smallsqrt:
    sqrtapprox 0
    xpop    bx
    ret

    group   dgroup data
    segment data
sqrttable:
    db      0x00, 0x10, 0x17, 0x1c, 0x20, 0x24, 0x27, 0x2a
    db      0x2d, 0x30, 0x33, 0x35, 0x37, 0x3a, 0x3c, 0x3e
    db      0x40, 0x42, 0x44, 0x46, 0x48, 0x49, 0x4b, 0x4d
    db      0x4e, 0x50, 0x52, 0x53, 0x55, 0x56, 0x58, 0x59
    db      0x5b, 0x5c, 0x5d, 0x5f, 0x60, 0x61, 0x63, 0x64
    db      0x65, 0x66, 0x68, 0x69, 0x6a, 0x6b, 0x6d, 0x6e
    db      0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x76, 0x77
    db      0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f
    db      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87
    db      0x88, 0x89, 0x8a, 0x8b, 0x8b, 0x8c, 0x8d, 0x8e
    db      0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x94, 0x95
    db      0x96, 0x97, 0x98, 0x99, 0x99, 0x9a, 0x9b, 0x9c
    db      0x9d, 0x9e, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa2
    db      0xa3, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9
    db      0xa9, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xae, 0xaf
    db      0xaf, 0xb0, 0xb1, 0xb1, 0xb2, 0xb3, 0xb4, 0xb4
    db      0xb5, 0xb6, 0xb6, 0xb7, 0xb8, 0xb9, 0xb9, 0xba
    db      0xbb, 0xbb, 0xbc, 0xbd, 0xbd, 0xbe, 0xbf, 0xbf
    db      0xc0, 0xc1, 0xc1, 0xc2, 0xc3, 0xc3, 0xc4, 0xc5
    db      0xc5, 0xc6, 0xc7, 0xc7, 0xc8, 0xc8, 0xc9, 0xca
    db      0xca, 0xcb, 0xcc, 0xcc, 0xcd, 0xce, 0xce, 0xcf
    db      0xcf, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0xd3, 0xd4
    db      0xd4, 0xd5, 0xd5, 0xd6, 0xd7, 0xd7, 0xd8, 0xd8
    db      0xd9, 0xda, 0xda, 0xdb, 0xdb, 0xdc, 0xdd, 0xdd
    db      0xde, 0xde, 0xdf, 0xdf, 0xe0, 0xe1, 0xe1, 0xe2
    db      0xe2, 0xe3, 0xe3, 0xe4, 0xe5, 0xe5, 0xe6, 0xe6
    db      0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 0xea, 0xea, 0xeb
    db      0xeb, 0xec, 0xec, 0xed, 0xed, 0xee, 0xee, 0xef
    db      0xef, 0xf0, 0xf1, 0xf1, 0xf2, 0xf2, 0xf3, 0xf3
    db      0xf4, 0xf4, 0xf5, 0xf5, 0xf6, 0xf6, 0xf7, 0xf7
    db      0xf8, 0xf8, 0xf9, 0xf9, 0xfa, 0xfa, 0xfb, 0xfb
    db      0xfc, 0xfc, 0xfd, 0xfd, 0xfe, 0xfe, 0xff, 0xff