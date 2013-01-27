    [bits    16]
    [section .text]

    global hercules_fillscreen_asm_
hercules_fillscreen_asm_:
    push        cx          ; save registers
    push        di

    mov         es, ax      ; es:di = target address
    xor         di, di

    mov         al, dl      ; ax = (fill << 8) | fill
    mov         ah, al

    mov         cx, 0x0f4b  ; store lines 0 mod 4
    rep stosw

    add         di, 0x0164  ; store lines 1 mod 4
    mov         cx, 0x0f4b
    rep stosw

    add         di, 0x0164  ; store lines 1 mod 4
    mov         cx, 0x0f4b
    rep stosw

    add         di, 0x0164  ; store lines 1 mod 4
    mov         cx, 0x0f4b
    rep stosw

    pop         di          ; restore registers
    pop         cx
    ret
