org 0x0
bits 16


%define ENDL 0x0D, 0x0A


start:
    ;print message
    mov si, msg_hello
    call puts

.halt:
    cli
    hlt

;print a string to the screen
;params:
;dsi:si points to string

puts:
    ;save registers ill modify
    push si
    push ax
    push bx

.loop:
    lodsb           ;loads next character in al
    or al, al       ;verify if next character is null?
    jz .done

    mov ah, 0x0e    ;call bios interrupt
    mov bh, 0       ;set page number to zero
    int 0x10

    jmp .loop

.done:
    pop bx
    pop ax
    pop si
    ret


msg_hello: db 'Hello world from the kernel!', ENDL, 0
