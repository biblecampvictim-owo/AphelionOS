bits 16

section _ENTRY class=CODE

extern _cstart_
global _start

_start:
    cli
    ; Align DS, ES, and SS with CS
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x0000
    sti

    ; Pass boot drive (DL) in AX (__watcall) and stack (__cdecl)
    mov al, dl
    xor ah, ah
    push ax

    call _cstart_

    cli
    hlt