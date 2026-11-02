bits 64

global idt_load
extern isr_handler

%macro ISR_NOERRCODE 1
    global isr_%1
    isr_%1:
        push qword 0    ;dummeh error code
        push qword %1   ;interrupt gru vector number
        jmp idt_common_stub
%endmacro

%macro ISR_ERRCODE 1
    global isr_%1
    isr_%1:
        push qword %1   ;interrupt vector number (error code already pushed by CPU)
        jmp idt_common_stub
%endmacro

idt_common_stub:
    ;save all general-purpose registers
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ;pass pointer to the stack frame as the first argument (RDI)
    mov rdi, rsp
    call isr_handler

    ;restore general-purpose registers
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ;clean up the pushed vector number and dummeh error code (2 * 8 bytes = 16 bytes)
    add rsp, 16
    iretq

ISR_NOERRCODE 0
ISR_NOERRCODE 1