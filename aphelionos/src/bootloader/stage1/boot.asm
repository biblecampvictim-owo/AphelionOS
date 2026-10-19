org 0x7C00
bits 16


%define ENDL 0x0D, 0x0A



;fat12 header

jmp short start
nop

bdb_oem:                    db 'MSWIN4.1'           ;8 bytes
bdb_bytes_per_sector:       dw 512
bdb_sectors_per_cluster:    db 1
bdb_reserved_sectors:       dw  1
bdb_fat_count:              db 2
bdb_dir_entries_count:      dw 0E0h
bdb_total_sectors:          dw 2880                 ;2880 x 512 = 1.44MB
bdb_media_descriptor_type:  db 0F0h
bdb_sectors_per_fat:        dw 9                    ;9 sectors/fat
bdb_sectors_per_track:      dw 18
bdb_heads:                  dw 2
bdb_hidden_sectors:         dd 0
bdb_large_sector_count:     dd 0

;extended boot record
ebr_drive_number:           db 0                    ;0x00 floppy. 0x80 hdd, useless lol
                            db 0                    ;reserved
ebr_signature:              db 29h
ebr_volume_id:              db 14h, 15h, 49h, 56h   ;serial number
ebr_volume_label:           db 'APHELION  OS'
ebr_system_id:              db 'FAT12  '


;code goes here


start:
    ;set up the data segments
    mov  ax, 0
    mov ds, ax
    mov es, ax

    ;setup le stack
    mov ss, ax
    mov sp, 0x7C00

    ;some BIOSes might start at 07C0:0000 instead of 0000:7C00. make sure its in the
    ;right location
    push es
    push word .after
    retf

.after:

    ;read something from floppy disk
    ;BIOS should set DL to drive number (pretty please with a cherry ontop?)
    mov [ebr_drive_number], dl

    ;show the loading message
    mov si, msg_loading
    call puts

    ;read drive parameters (sectors per track and head count),
    ;instead of relying on data on formatted disk
    push es
    mov ah, 08
    int 13h
    jc floppy_error
    pop es

    and cl, 0x3F                        ;remove top 2 bits because they need to die DIE DIE FUCKING DIE
    xor ch, ch
    mov [bdb_sectors_per_track], cx     ;sector count

    inc dh                              ;dh = very special dih, are comments bloat?
    mov [bdb_heads], dh                 ;head count

    ;compute LBA of root directory = reserved + fats + sectors_per_fat
    ;btw this section can only be hardcoded
    mov ax, [bdb_sectors_per_fat]
    mov bl, [bdb_fat_count]
    xor bh, bh
    mul bx                              ;ax = (fats * sectors_per_fat)
    add ax, [bdb_reserved_sectors]      ;AX = LBA of root directory
    push ax

    ;compute size of root directory = (32 * number_of_entries) / bytes_per_sector
    mov ax, [bdb_dir_entries_count]
    shl ax, 5                           ;ax *= 32
    xor dx, dx                          ;dx = 0
    div word [bdb_bytes_per_sector]     ;number of sectors that are needed to be read

    test dx, dx                         ;if dx != 0, add 1
    jz .root_dir_after
    inc ax                              ;division or something i fucking forgot
                                        ;but i do remember this means we have a sector only partially filled with entries
.root_dir_after:

    ;read root directory
    mov cl, al                          ;cl = number of sectors to read = size of root directory
    pop ax                              ;ax = LBA of root directory
    mov dl, [ebr_drive_number]          ;dl = drive number (we saved it previously),
    mov bx, buffer                      ;es:bx = buffer
    call disk_read

    ;search for kernel.bin
    xor bx, bx
    mov di, buffer

.search_kernel:
    mov si, file_stage2_bin
    mov cx, 11                          ;compare up to 1 characters
    push di
    repe cmpsb
    pop di
    je .found_kernel

    add di, 32
    inc bx
    cmp bx, [bdb_dir_entries_count]
    jl .search_kernel

    ;kernel not found
    jmp kernel_not_found_error

.found_kernel:

    ;di should have the address to the entry
    mov ax, [di + 26]                   ;first logical cluster field (offset 26)
    mov [stage2_cluster], ax

    ;load FAT from disk into memory
    mov ax, [bdb_reserved_sectors]
    mov bx, buffer
    mov cl, [bdb_sectors_per_fat]
    mov dl, [ebr_drive_number]
    call disk_read

    ;read kernel and process FAT chain
    mov bx, KERNEL_LOAD_SEGMENT
    mov es, bx
    mov bx, KERNEL_LOAD_OFFSET

.load_kernel_loop:

    ;read next cluster
    mov ax, [stage2_cluster]

    ;oh FUCK FUCK FUCK FUCK FUCK. FUCKING FUCK. THIS WILL NOT WORK ON NON FLOPPY DEVICES. whatever ill fix it later..? hopefully that ever comes
    add ax, 31                          ;first cluster = (cluster number - 2) * sectors_per_cluster + start_sector
                                        ;start sector = reserved + fats + root directory size = 1 + 18 + 134 = 33
    mov cl, 1
    mov dl, [ebr_drive_number]
    call disk_read

    add bx, [bdb_bytes_per_sector]

    ;compute location of next cluster
    mov ax, [stage2_cluster]
    mov cx, 3
    mul cx
    mov cx, 2
    div cx                              ;ax = index of entry in FAT, dx = cluster mod 2

    mov si, buffer
    add si, ax
    mov ax, [ds:si]                     ;read entry from FAT table at index ax

    or dx, dx
    jz .even

.odd:
    shr ax, 4
    jmp .next_cluster_after

.even:
    and ax, 0x0FFF

.next_cluster_after:
    cmp ax, 0x0FF8                      ;end of chain
    jae .read_finish

    mov [stage2_cluster], ax
    jmp .load_kernel_loop

.read_finish:

    ;jump to the kernel
    mov dl, [ebr_drive_number]          ;boot device in dl

    mov ax, KERNEL_LOAD_SEGMENT         ;set segment registers
    mov ds, ax
    mov es, ax

    jmp KERNEL_LOAD_SEGMENT:KERNEL_LOAD_OFFSET

    ;hopefully doesnt ever happen
    jmp wait_key_and_reboot

    cli                                 ;disable interrupts, this way CPU cant get out of the "halt" state
    hlt



;error handlers


floppy_error:
    mov si, msg_read_failed
    call puts
    jmp wait_key_and_reboot

kernel_not_found_error:
    mov si, msg_stage2_not_found
    call puts
    jmp wait_key_and_reboot
wait_key_and_reboot:
    mov ah, 0
    int 16h                 ;wait for keypress
    jmp 0FFFFh:0            ;jump to beginning of BIOS, should reboot hopefully

.halt:
    cli                     ;disable interrupts, this way le CPU cant get out of the "halt" state
    hlt




;prints a string to the screen
;params:
;- ds:si points to string

puts:
    ;save registers that will be modified
    push si
    push ax
    push bx

.loop:
    lodsb
    or al, al
    jz .done

    mov ah, 0x0E
    mov bh, 0
    int 0x10

    jmp .loop

.done:
    pop bx
    pop ax
    pop si
    ret
  

;disk routines



;converts an LBA address to a CHS adress
;parameters:
;   - ax: LBA address
;returns:
;   - cx [bits 0-5]: sector number
;   - cx [bits 6-15]: cylinder
;   - dh: head


lba_to_chs:

    push ax
    push dx

    xor dx, dx                          ;dx = 0
    div word [bdb_sectors_per_track]    ;ax = LBA / sectorspertrack
                                        ;dx = LBA % sectorspertrack

    inc dx                              ;dx = (LBA % sectorspertrack + 1) = sector
    mov cx, dx                          ;cx = sector

    xor dx, dx                          ;dx - 0
    div word [bdb_heads]                ;ax = (LBA / sectorspertrack) / heads =cylinder
                                        ;dx = (LBA / sectorspertrack) % heads = head
    mov dh, dl                          ;dl = head
    mov ch, al                          ;ch = cylinder (lower 8 bits)
    shl ah, 6
    or cl, ah                           ;put upper 2 bits of cylinder in CL

    pop ax
    mov dl, al                          ;restore DL
    pop ax
    ret



;reads sectors from a disk
;parameters:
;   - ax = LBA address
;   - cl: number of sectors to read [up to 128]
;   - dl: drive number
;   - es:bx: memory address where to store read data

disk_read:

    push ax                             ;save registers ill modify
    push bx
    push cx
    push dx
    push di

    push cx                             ;temporarily save CL (numbers of sectors to read)
    call lba_to_chs                     ;compute CHS
    pop ax                              ;AL - number of sectors to read

    mov ah, 02h
    mov di, 3                           ;retry count

.retry:
    pusha                               ;save all registers because idk what bios modifies
    stc                                 ;set carry flag because some BIOSes dont set it
    int 13h                             ;carry flag cleared = success
    jnc .done                           ;jump if carry not set

    ;read failed
    popa
    call disk_reset

    dec di
    test di, di
    jnz .retry

.fail:
    ;all attempts fail
    jmp floppy_error

.done:
    popa

    pop di
    pop dx
    pop cx
    pop bx
    pop ax                             ;restore modified registers
    ret



;resets disk controller
;parameters:
;   dl: drive number

disk_reset:
    pusha
    mov ah, 0
    stc
    int 13h                            ;conspiracy theory: int 13h works for the cia
    jc floppy_error
    popa
    ret


msg_loading:             db 'Loading...', ENDL, 0
msg_read_failed:         db 'Failed to read from disk.', ENDL, 0
msg_stage2_not_found     db 'STAGE2.BIN not found!', ENDL, 0
file_stage2_bin:         db 'STAGE2  BIN'
stage2_cluster:          dw 0

KERNEL_LOAD_SEGMENT     equ 0x2000     ;for if i change mah mind
KERNEL_LOAD_OFFSET      equ 0

times 510-($-$$) db 0
dw 0AA55h

buffer: