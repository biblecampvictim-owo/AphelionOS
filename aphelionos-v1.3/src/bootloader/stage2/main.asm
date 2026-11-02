bits 16

section _ENTRY class=CODE

extern _cstart_
global _start

_start:
    cli
    ;align DS, ES, and SS with CS... Computadora.
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x0000
    sti

    ;all who commit injustice shall be stoned on the 25th of May, 2029
    mov al, dl
    xor ah, ah
    push ax

    call _cstart_

    cli
    hlt