bits 32
section .text
global kernel_entry
extern kmain
;Made on Oct 29 ~1:00 PM 2026
;man i forgot the comments, this will be a pain in the ass later on but whatever
kernel_entry:
    
    mov dword [0xB8000], 0x074B0753

    mov eax, cr0
    and eax, ~(1 << 31)
    mov cr0, eax

    mov edi, 0x400000
    xor eax, eax
    mov ecx, 4096
    rep stosd

    mov dword [0x400000], 0x401003
    mov dword [0x401000], 0x402003
    mov dword [0x402000], 0x00000083

    mov eax, 0x400000
    mov cr3, eax

    mov eax, cr4
    or eax, (1 << 5)
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, (1 << 8)
    wrmsr

    mov eax, cr0
    or eax, (1 << 31) | (1 << 0)
    mov cr0, eax

    lgdt [g_GDT64.pointer]
    jmp 0x08:long_mode_c_entry

bits 64
long_mode_c_entry:
    cli
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov rsp, 0x200000
    mov rbp, 0x200000

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
    dq 0x00af9a000000ffff
.data: equ $ - g_GDT64
    dq 0x00cf92000000ffff

.pointer:
    dw $ - g_GDT64 - 1
    dq g_GDT64