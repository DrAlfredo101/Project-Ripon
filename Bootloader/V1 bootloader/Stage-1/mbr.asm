  org 0x7c00
  %include "FAT flags.inc" ; leave space for fat32 metadata and add flags for it

boot_start:
  xor eax, eax ; setup the registers that need to be certain values
  mov edx, eax
  mov ds, ax
  mov es, ax
  mov ss, ax
  mov sp, 0x7c00

  movzx eax, byte [number_of_FATs] ; number of fats
  imul eax, dword [FAT_size_32_bit] ; times fat size
  movzx edx, word [reserved_sector_count] 
  add eax, edx ; plus reserved sectors
  mov dword [data_region_start], eax ; equals where the root directory starts
  mov dword [sector_start], eax ; copy that over to where to load from
  mov dword [sector_start+4], 0 ; and fill the blank space with zeros to avoid errors

load_next_sector:
  xor ax, ax
  mov ds, ax ; segment is 0
  mov si, DAP ; offset is at the dap
  mov ah, 0x42 ; mode is extended read
  mov dl, 0x80 ; first hard drive
  int 0x13 ; call the interrupt
  jc read_error ; hopefully this doesnt happen as I dont plan on actually adding anything to it
  xor cx, cx ; set cx to 0 to be the counter to count files in each sector before it needs to be loaded

parse:
  xor bx, bx ; bx = 0
  add bx, cx ; file offset in the sector added to 
  add bx, 0x7e00 ; add the offset in memory to where its stored
  cmp [bx], 0x00 ; end of directory
  je boot_not_found
  cmp [bx], 0xE5 ; file deleted
  je next_file
  add bx, 11 ; move bx to point at the special byte that includes the bit to say if directory or file
  mov ah, [bx]
  test ah, 0x10 ; is a directory so cannot be the boot file
  jne next_file
  sub bx, 11 ; set bx back to the start of the metadata
  mov si, target_name ; si to point at the start of target name or the space in front of it
  mov dh, 0 ; counter for how many characters to check

  char_loop:
  mov dl, [bx] ; cannot dereference 2 registers at the same time
  cmp dl,[si+1] ; this bypasses the extra space and makes it actually work
  jne next_file ; char does not match so move on to the next file
  inc bx ; increment all the pointers and counter
  inc si
  inc dh
  cmp dh, 11 ; if 11 have been checked successfully then it is a match
  jne char_loop ; if 11 havent then check the next char

found:
  sub bx, 11 ; set bx back to the start of the file metadata again
  movzx eax, word [bx+20] ; get the first 2 bytes of cluster number
  shl eax, 16 ; move them to the front of eax
  mov ax, word [bx+26] ; get the second 2 bytes and put them in eax
  mov [boot_cluster_start], eax ; store that in boot cluster start
  sub eax, 2 ; cluster 2 is where data starts
  add eax, [data_region_start] ; this calculates how many sectors into the drive boot.bin data is
  mov [sector_start], eax ; save that in sector start
  mov [sector_start+4], 0 ; ensure that the extra bits are 0 to not corrupt the memory

  mov eax, dword [bx+28] ; get the size of the file
  mov [boot_size], eax ; store that in the size
  mov edx, 0 ; make sure there is nothing in the upper bits of the thing being divided
  mov ecx, 512 ; set the divisor to sector size
  div ecx ; actually do the division
  inc eax ; equvilent to a cieling division to get how many sectors to load
  mov [sector_count], eax ; put that in the dap
  
load_stage_2:
  mov ax, 0x7e00 ; memory must be updated by a register
  mov [load_to], ax ; the address resets for some reason
  mov ah, 0x42 ; set the mode to extended read
  mov dl, 0x80 ; read the first drive
  mov si, DAP ; point to the dap, ds is already 0
  int 0x13 ; do the read
  jmp 0x7e00 ; transfer control to boot.bin and be finished

error:
  mov ah, 0x0e ; prints E so I know theres been an error
  mov al, 'E'
  int 0x10

next_file: ; each file is 32 bytes so need to increment by that
  add cx, 32
  jmp parse

next_sector:
  inc [sector_start] ; never tested but it should just keep loading sectors when they get reset
  jmp load_next_sector

read_error:
  jmp $ ; hang but should be a level of error handling

boot_not_found:
  jmp $ ; same as read error


DAP:
  db 0x10 ; length of dap
  db 0x00 ; 0 for random reason
  sector_count dw 1 ; load 1 sector
  load_to dd 0x00007e00 ; load it directly after the mbr in memory
  sector_start dq 0 ; which sector to load

data_define:
  data_region_start dd 0
  target_name db ' BOOT    BIN' ; yes for some reason the space at the start is required
  boot_cluster_start dd 0
  boot_size dd 0
  times 510-($-$$) db 0 ; fill remaining bytes with 0
  dw 0xAA55 ; boot signature