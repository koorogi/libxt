%include "asm/dos.asm"

    bits    16
    org     0x0100

%macro  xrotate 1-*
    %rep %0
        rcl     %1, 1
    %rotate 1
    %endrep
%endmacro

%define BAD         0xff
%define PADDING     '='

    cld

    ; decode 3 output bytes from 4 input bytes
decode3:
    ; zero out the 4-byte input buffer
    xor     ax, ax
    mov     di, buffer
    stosw
    stosw

    ; ask DOS to read 4 bytes from stdin
    mov     ah, 0x3f
    mov     bx, STDIN
    mov     cx, 4
    mov     dx, buffer
    int     0x21
    jc      done    ; quit on error or eof

    ; move number of bytes into dx and keep it there
    mov     dx, ax

    ; strip off any padding characters
    mov     bx, dx
    mov     si, buffer

strip_padding:
    dec     bx
    jl      done_padding
    cmp     byte [si + bx], PADDING
    jne     done_padding
    mov     byte [si + bx], 0
    dec     dx
    jmp     strip_padding

    ; verify that the number of bytes we got is valid (must be 2, 3, or 4)
done_padding:
    cmp     dx, 2
    jl      done

    ; convert each input byte into the 6 bits it represents
    mov     cx, dx
    mov     si, buffer
    mov     di, si
    mov     bx, lut
convert:
    lodsb
    mov     ah, al
    xlat
    cmp     al, BAD
    jz      done

    sub     ah, al
    mov     al, ah
    stosb
    loop    convert

    ; now we compress the 4 input bytes into its 3 output bytes
    mov     si, buffer
    mov     ax, [si  ]
    mov     bx, [si+2]

    times 2 shl bh, 1
    xrotate bh, bl
    xrotate bh, bl
    xrotate bh, bl, ah
    xrotate bh, bl, ah
    xrotate bh, bl, ah, al
    xrotate bh, bl, ah, al

    mov     [si  ], ax
    mov     [si+2], bl

    ; ask DOS nicely to write the data to stdout
    mov     ah, 0x40
    mov     bx, STDOUT
    mov     cx, dx
    dec     cx
    mov     dx, buffer
    int     0x21

    jmp     decode3

done:
    int     0x20

    ; This lookup table cannot directly contain the target values, because the
    ; whole problem base64 solves is that the target values (and hence such a
    ; table) cannot be transmitted.  Instead, the table stores the value to
    ; subtract from its index in order to calculate the target value.  The value
    ; BAD is used for entries which are not valid base64 input bytes.
lut:
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; x00 - x0f
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; x10 - x1f
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  0xed, BAD,  BAD,  BAD,  0xf0  ; x20 - x2f
    db  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; x30 - x3f
    db  BAD,  0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41  ; x40 - x4f
    db  0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, BAD,  BAD,  BAD,  BAD,  BAD   ; x50 - x5f
    db  BAD,  0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47  ; x60 - x6f
    db  0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, BAD,  BAD,  BAD,  BAD,  BAD   ; x70 - x7f
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; x80 - x8f
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; x90 - x9f
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; xa0 - xaf
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; xb0 - xbf
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; xc0 - xcf
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; xd0 - xdf
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; xe0 - xef
    db  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD,  BAD   ; xf0 - xff

buffer: