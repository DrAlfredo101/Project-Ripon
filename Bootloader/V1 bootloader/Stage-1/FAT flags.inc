  jmp short boot_start ; first 3 bytes are for jumping to the main code
  db 0 ; but only 2 bytes are used to jump so a 0 must be used to pad

; add name to drive

os_name: ; bytes 3-10 (8 bytes)
  db "RPN0.0.0"

; reserve space for FAT32 information and add labels for easy access during boot

bytes_per_sector: ; bytes 11-12 (2 bytes)
  dw 0
sectors_per_cluster: ; byte 13
  db 0
reserved_sector_count: ; bytes 14-15 (2 bytes)
  dw 0
number_of_FATs: ; byte 16
  db 0
root_entry_count: ; bytes 17-18 (2 bytes)
  dw 0
total_sectors_16_bit: ; bytes 19-20
  dw 0
media_descriptor: ; byte 21
  db 0
FAT_size_16_bit: ; bytes 22-23 (2 bytes)
  dw 0
sectors_per_track: ; bytes 24-25 (2 bytes)
  dw 0
numbers_of_heads: ; bytes 26-27 (2 bytes)
  dw 0
hidden_sectors_number: ; bytes 28-31 (4 bytes)
  dd 0
total_sectors_32_bit: ; bytes 32-35 (4 bytes)
  dd 0
FAT_size_32_bit: ; bytes 36-39 (4 bytes)
  dd 0
extended_flags: ; bytes 40-41 (2 bytes)
  dw 0
fs_version: ; bytes 42-43 (2 bytes)
  dw 0
root_cluster_number: ; bytes 44-47 (4 bytes)
  dd 0
fsinfo_sector_number: ; bytes 48-49 (2 bytes)
  dw 0
backup_boot_sector: ; bytes 50-51 (2 bytes)
  dw 0
reserved: ; bytes 52-63 (12 bytes)
  dd 0,0,0
drive_number: ; byte 64
  db 0
windowsNT_reserved: ; byte 65
  db 0
boot_signature: ; byte 66
  db 0
volume_id: ; bytes 67-70 (4 bytes)
  dd 0
volume_label: ; bytes 71-81 (11 bytes)
  dd 0,0
  db 0,0,0
file_system_type: ; bytes 82-89
  dd 0,0