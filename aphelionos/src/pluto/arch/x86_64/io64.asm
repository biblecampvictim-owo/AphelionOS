[bits 64]

global x86_outb
global x86_inb
global outb
global inb

x86_outb:
outb:
    ;rdi = port (uint16_t), sil = value (uint8_t)
    mov dx, di
    mov al, sil
    out dx, al
    ret

x86_inb:
inb:
    ;rdi = port (uint16_t)
    mov dx, di
    xor eax, eax
    in al, dx
    ret