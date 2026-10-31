[bits 64]

global outb
outb:
    ;rdi = port (uint16_t), sil = value (uint8_t)
    mov dx, di
    mov al, sil
    out dx, al
    ret

global inb
inb:
    ;rdi = port (uint16_t)
    mov dx, di
    in al, dx
    ret
