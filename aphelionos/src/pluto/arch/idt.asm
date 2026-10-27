bits 32

global idt_load
extern isr_handler

%macro ISR_NOERRCODE 1
    global isr_%1
    isr_%1:
        push byte 0
        push byte %1
        jmp idt_common_stub
%endmacro

%macro ISR_ERRCODE 1
    global isr_%1
    isr_%1:
        push byte %1
        jmp idt_common_stub
%endmacro

idt_common_stub:
    pushad
    mov eax, esp
    push eax
    call isr_handler
    add esp, 4
    popad
    add esp, 8
    iret

ISR_NOERRCODE 0
ISR_NOERRCODE 1