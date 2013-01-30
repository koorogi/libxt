%include "macro.asm"

    bits    16
    segment _TEXT

    extern _xt_hercules_fb_row_offset

    global xtintl_hercules_line_horiz_
    ; Internal helper for drawing a horizontal line. Assumes all inputs are valid.
    ; input : ax = framebuffer segment
    ;         dx = y; bx = x1, cx = x2
xtintl_hercules_line_horiz_:
    xpush   di

    ; [es:di] row = MK_FP(bufseg, xt_hercules_fb_row_offset[y] + (x1 >> 3));
    mov     es, ax

    mov     di, dx
    shl     di, 1
    mov     di, [_xt_hercules_fb_row_offset + di]

    mov     dx, bx
    xshr    dx, 3
    add     di, dx

    ; [cx] count = x2 - x1 + 1;
    ; [bx] skip  = x1 & 7;
    sub     cx, bx
    inc     cx
    and     bx, 7

    ; if (skip) {
    ;     int firstbyte = 8 - skip;
    ;     if (count < firstbyte) {
    ;         *row   |= (0xff & (0xff << (8 - count))) >> skip;
    ;         return;
    ;     } else {
    ;         *row++ |= 0xff >> skip;
    ;         count  -= firstbyte;
    ;     }
    ; }
    jz      skip_done

    mov     ax, 8
    sub     ax, bx              ; ax = firstbyte
    mov     bx, skiptbl - 16    ; bx = skiptbl

    cmp     ax, cx
    jle     full_hline

    xshl    cx, 4
    or      al, cl
    xlat
    or      byte [es:di], al
    jmp     done_hline

full_hline:
    sub     cx, ax
    or      al, 8 << 4
    xlat
    or      byte [es:di], al
    inc     di

skip_done:
    ; [cx] bytes = count >> 3;
    ; [bx] count &= 7;
    ; _fmemset(row, 0xff, bytes);
    ; row += bytes;
    mov     ax, 0xffff
    mov     bx, cx
    and     bx, 7
    xshr    cx, 3

    shr     cx, 1
    rep     stosw
    adc     cx, cx
    rep     stosb

    ; if (count) *row |= (0xff00 >> count) & 0xff;
    xor     al, al
    mov     cx, bx
    shr     ax, cl
    or      byte [es:di], al

done_hline:
    xpop    di
    ret

    global xtintl_hercules_line_vert_
    ; Internal helper for drawing a vertical line. Assumes all inputs are valid.
    ; input : ax = framebuffer segment
    ;         dx = x; bx = y1, cx = y2
xtintl_hercules_line_vert_:
    xpush   di

    mov     es, ax
    sub     cx, bx
    inc     cx

    mov     ax, dx
    xshr    dx, 3
    and     ax, 7
    xor     ax, 7

    mov     di, bx
    mov     bx, skiptbl + 1
    xlat
    mov     bx, di
    shl     bx, 1

vert_loop:
    mov     di, [_xt_hercules_fb_row_offset + bx]
    add     di, dx
    or      [es:di], al
    inc     bx
    inc     bx
    loop    vert_loop

    xpop    di
    ret

    group   DGROUP DATA
    segment DATA

skiptbl:
    ; lookup table for expression (0xff & (0xff << (8 - count))) >> skip
    ; indexed by (count << 4) | (8 - skip)
    ; the first 16 entries in the table are never used, so we omit them.
    ; we use skiptbl-16 as the address of the beginning of the table
    ;db      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    ;db      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40
    db      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60
    db      0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70
    db      0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x07, 0x0f, 0x1e, 0x3c, 0x78
    db      0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3e, 0x7c
    db      0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7e
    db      0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f
    db      0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    db      0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f
    db      0xff
    ; we cut the table short, because the rest is never used
