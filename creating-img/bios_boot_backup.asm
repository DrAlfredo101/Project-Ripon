    org 0x7c00

boot_start:
    xor eax, eax ; setup the registers that need to be certain values
    mov edx, eax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

save_boot_drive:
    mov [boot_drive], dl ; dl starts with the boot drive number passed by the bios

get_sectors_to_load:
    call load_from_disk ; load the first sector of the bios boot partition into memory
    mov ax, [0x7e00] ; add sectors to load to sectors remaining
    mov [sectors_remaining], ax

load_loop:
    cmp [sectors_remaining], 0x0000 ; check if there are any sectors remaining to load
    je transfer_control ; if not, jump to the loaded code
    call load_from_disk ; load the next sector of the bios boot partition into memory
    add [dap_segment], 0x0020 ; increment the segment to load to by 512 bytes
    sub [sectors_remaining], 0x0001 ; subtract one from the number of sectors remaining
    jmp load_loop ; repeat until all sectors are loaded

transfer_control:
    jmp 0x7e00 ; jump to the loaded code

load_from_disk:
    mov [sectors_to_load], 0x0001 ; in this bootloader only one sector is loaded at a time
    mov ah, 0x42 ; mode is extended read
    mov dl, [boot_drive] ; boot drive number
    mov si, DAP ; offset is at the dap, ds is already 0
    int 0x13 ; call the interrupt
    jc read_error ; hopefully this doesnt happen as I dont plan on actually adding anything to it
    ret

DAP:
    db 0x10 ; size of dap
    db 0x00 ; reserved
    sectors_to_load dw 0x0001 ; number of sectors to read
    dw 0x0000 ; offset to load to
    dap_segment dw 0x07e0 ; segment to load to
    dq 34 ; starting lba

boot_drive: db 0 ; boot drive number

sectors_remaining: dw 0x0000 ; number of sectors remaining to load

times 446-($-$$) db 0 ; fill up to MBR partition table with 0s