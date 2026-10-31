
bits 32

section .text
global kernel_entry
extern kmain
                                    
kernel_entry:                       ;all comments go here
    cli
    cld

    mov dword [0xB8000], 0x074B0753 ;write to vga o algo

    mov eax, cr0
    and eax, ~(1 << 31)
    mov cr0, eax                    ;disable the paging

    mov edi, 0x400000
    xor eax, eax
    mov ecx, 4096
    rep stosd                       

    mov dword [0x400000], 0x401003
    mov dword [0x401000], 0x402003
    mov edi, 0x402000
    mov eax, 0x00000083
    mov ecx, 5

.map_pages:
    mov dword [edi], eax
    add eax, 0x00200000
    add edi, 8
    loop .map_pages                 ;identity map the first 10 mib

    mov eax, 0x400000
    mov cr3, eax                    ;load

    mov eax, cr4
    or eax, (1 << 5)
    mov cr4, eax                    ;enable

    mov ecx, 0xC0000080
    rdmsr
    or eax, (1 << 8)
    wrmsr                           ;enable long mode (why do i pronounce this as worm es ar in my head)

    mov eax, cr0
    or eax, (1 << 31) | (1 << 0)
    mov cr0, eax                    

    lgdt [g_GDT64.pointer]          
    jmp 0x08:long_mode_c_entry      

;64 bit tuff mode activated
bits 64

long_mode_c_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax                      ;load the kernel data seg

    mov rsp, 0xA00000
    mov rbp, 0xA00000                

    call kmain                       

.hang:
    cli
    hlt
    jmp .hang                        

section .data
align 8

g_GDT64:
    dq 0                             

.code: equ $ - g_GDT64
    dq 0x00af9a000000ffff            ;64 bit kernel code seg

.data: equ $ - g_GDT64
    dq 0x00cf92000000ffff            

.pointer:
    dw $ - g_GDT64 - 1
    dq g_GDT64                       ;gdt descriptor
