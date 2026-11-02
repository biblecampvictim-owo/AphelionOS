bits 64
global keyboard_isr_stub        
extern keyboard_handler
;Created on ~ Oct 29 2026 
keyboard_isr_stub:    
    ;in perfect order of course!!         
    push rax
    push rbx
    push rbp
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    cld
    call keyboard_handler
    
    ;you think its O'Block the way registers are getting pushed and then popped
    ;aaannndd we go backwards!
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbp
    pop rbx
    pop rax
    iretq