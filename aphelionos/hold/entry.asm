;moved here because it is problematic during the transition from 32 bit protected to 64 bit long mode
[bits 32]
[extern kernel_main]

global _start
_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000

    call kernel_main

.halt:
    cli
    hlt
    jmp .halt