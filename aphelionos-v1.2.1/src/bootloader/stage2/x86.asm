bits 16

section _TEXT class=CODE


;
;u4d
;
;operation:      unsigned 4 byte divide
;inputs:         dx;ax   dividend
;                cx;bx   divisor
;outputs:        dx;ax   quotient
;                cx;bx   remainder
;volatile:       none
;
global __U4D
__U4D:
    shl edx, 16         ;dx to upper half of edx
    mov dx, ax          ;edx - dividend
    mov eax, edx        ;eax - divdend
    xor edx, edx

    shl ecx, 16         ;cx to upper half of ecx
    mov cx, bx          ;ecx - divisor

    div ecx             ;eax - quot, edx - remainder
    mov ebx, edx
    mov ecx, edx
    shr ecx, 16

    mov edx, eax
    shr edx, 16

    ret


;
;u4m
;operation:      integer four byte multiply
;inputs:         dx;ax   integer m1
;                cx;bx   integer m2
;outputs:        dx;ax   product
;volatile:       cx, bx destroyed
;
global __U4M
__U4M:
    shl edx, 16         ;dx to upper half of edx
    mov dx, ax          ;m1 in edx
    mov eax, edx        ;m1 in eax

    shl ecx, 16         ;cx to upper half of ecx
    mov cx, bx          ;m2 in ecx

    mul ecx             ;result in edx:eax (we only need eax)
    mov edx, eax        ;move upper half to dx
    shr edx, 16

    ret

;
;void _cdecl x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotientout, uint32_t* remainderout);
;
global _x86_div64_32
_x86_div64_32:

    ;make new call frame
    push bp             ;save old call frame
    mov bp, sp          ;initialize new call frame

    push bx

    ;divide upper 32 bits
    mov eax, [bp + 8]   ;eax <- upper 32 bits of dividend
    mov ecx, [bp + 12]  ;ecx <- divisor
    xor edx, edx
    div ecx             ;eax - quot, edx - remainder

    ;store upper 32 bits of quotient
    mov bx, [bp + 16]
    mov [bx + 4], eax

    ;divide lower 32 bits
    mov eax, [bp + 4]   ;eax <- lower 32 bits of dividend
                        ;edx <- old remainder
    div ecx

    ;store results
    mov [bx], eax
    mov bx, [bp + 18]
    mov [bx], edx

    pop bx

    ;restore old call frame
    mov sp, bp
    pop bp
    ret

;
;int 10h ah=0eh
;args: character, page
;
global _x86_Video_WriteCharTeletype
_x86_Video_WriteCharTeletype:
    
    ;make new call frame
    push bp             ;save old call frame
    mov bp, sp          ;initialize new call frame

    ;save bx
    push bx

    ;[bp + 0] - old call frame
    ;[bp + 2] - return address (small memory model => 2 bytes)
    ;[bp + 4] - first argument (character)
    ;[bp + 6] - second argument (page)
    ;note: bytes are converted to words (you cant push a single byte on the stack)
    mov ah, 0eh
    mov al, [bp + 4]
    mov bh, [bp + 6]

    int 10h

    ;restore bx
    pop bx

    ;restore old call frame
    mov sp, bp
    pop bp
    ret


;
;bool _cdecl x86_disk_reset(uint8_t drive);
;
global _x86_Disk_Reset
_x86_Disk_Reset:

    ;make new call frame
    push bp             ;save old call frame
    mov bp, sp          ;initialize new call frame

    mov ah, 0
    mov dl, [bp + 4]    ;dl - drive
    stc
    int 13h

    mov ax, 1
    sbb ax, 0           ;1 on success, 0 on fail   

    ;restore old call frame
    mov sp, bp
    pop bp
    ret


;
;bool _cdecl x86_disk_read(uint8_t drive,
;                          uint16_t cylinder,
;                          uint16_t sector,
;                          uint16_t head,
;                          uint8_t count,
;                          void far * dataout);
;
global _x86_Disk_Read
_x86_Disk_Read:

    ;make new call frame
    push bp             ;save old call frame
    mov bp, sp          ;initialize new call frame

    ;save modified regs
    push bx
    push es

    ;setup args
    mov dl, [bp + 4]    ;dl - drive

    mov ch, [bp + 6]    ;ch - cylinder (lower 8 bits)
    mov cl, [bp + 7]    ;cl - cylinder to bits 6-7
    shl cl, 6
    
    mov al, [bp + 8]    ;cl - sector to bits 0-5
    and al, 3fh
    or cl, al

    mov dh, [bp + 10]   ;dh - head

    mov al, [bp + 12]   ;al - count

    mov bx, [bp + 16]   ;es:bx - far pointer to data out
    mov es, bx
    mov bx, [bp + 14]

    ;call int13h
    mov ah, 02h
    stc
    int 13h

    ;set return value
    mov ax, 1
    sbb ax, 0           ;1 on success, 0 on fail   

    ;restore regs
    pop es
    pop bx

    ;restore old call frame
    mov sp, bp
    pop bp
    ret


;
;bool _cdecl x86_disk_getdriveparams(uint8_t drive,
;                                    uint8_t* drivetypeout,
;                                    uint16_t* cylindersout,
;                                    uint16_t* sectorsout,
;                                    uint16_t* headsout);
;
global _x86_Disk_GetDriveParams
_x86_Disk_GetDriveParams:

    ;make new call frame
    push bp             ;asve old call frame
    mov bp, sp          ;initialize new call frame

    ;save the gay reggies
    push es
    push bx
    push si             ;omg yes pop me!!!~~~
    push di
    ;trust me ill be the one to fight for u when things are wrong
    ;call int13h
    mov dl, [bp + 4]    ;dl - disk drive
    mov ah, 08h
    mov di, 0           ;es:di - 0000:0000
    mov es, di
    stc
    int 13h

    ;return
    mov ax, 1
    sbb ax, 0

    ;out params
    mov si, [bp + 6]    ;drive type from bl
    mov [si], bl

    mov bl, ch          ;cylinders - lower bits in ch
    mov bh, cl          ;cylinders - upper bits in cl (6-7 hahaha 67)
    shr bh, 6
    mov si, [bp + 8]
    mov [si], bx

    xor ch, ch          ;sectors - lower 5 bits in cl
    and cl, 3fh
    mov si, [bp + 10]
    mov [si], cx

    mov cl, dh          ;heads - dh (dih)
    mov si, [bp + 12]
    mov [si], cx

    ;restore regs
    pop di
    pop si
    pop bx
    pop es

    ;restore old call frame
    mov sp, bp
    pop bp
    ret


;
;32-bit protected mode switch
;

;
;void _cdecl x86_enablea20(void);
;
global _x86_EnableA20
_x86_EnableA20:
    mov ax, 2401h
    int 15h
    ret

;
;void _cdecl x86_enterprotectedmode(void);
;
global _x86_EnterProtectedMode
_x86_EnterProtectedMode:
    cli                     ;disable interrupts!

    ;calculate linear base address of ds (ds * 16)
    xor eax, eax
    mov ax, ds
    shl eax, 4
    mov ebx, eax

    ;calculate linear address of gdt descriptor
    add eax, g_GDT
    mov [g_GDTDescriptor + 2], eax

    ;calculate linear target address for protected mode entry
    mov eax, ebx
    add eax, stage3_entry
    mov [g_Stage3Ptr], eax

    ;load gdt
    lgdt [g_GDTDescriptor]

    ;enable protected mnode bit in cr0
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ;far jump to stage3_entry using dynamic 32-bit offset pointer
    jmp dword far [g_Stage3Ptr]

bits 32
stage3_entry:
    ;reload segment registers with 0x10 (data selector)
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;set 32-bit stack pointer
    mov esp, 0x90000

    ;jump to kernel physiscal entry point at 0x30000
    mov eax, 0x30000
    jmp eax


;global descriptor table (gdt) (lowk lit fam)
align 8
g_GDT:
    ;null descriptor (0x00)
    dq 0

    ;32-bit code segment descriptor (0x08)
    dw 0xffff       ;limit 0:15
    dw 0x0000       ;base 0:15
    db 0x00         ;base 16:23
    db 0x9a         ;access: present, ring 0, code, readable
    db 0xcf         ;granularity 4kb, 32-bit mode, limit 16:19
    db 0x00         ;base 24:31

    ;32-bit data segment descriptor (0x10)
    dw 0xffff       ;limit 0:15
    dw 0x0000       ;base 0:15
    db 0x00         ;base 16:23
    db 0x92         ;access: present, ring 0, data, writable
    db 0xcf         ;granularity 4kb, 32-bit mode, limit 16:19? i think i hope i think
    db 0x00         ;base 24:31

g_GDTDescriptor:
    dw (3 * 8) - 1          
    dd 0                    ;Base address (patched dynamically at runtime)

g_Stage3Ptr:
    dd 0                    ;32-bit offset
    dw 0x08                 ;code selector