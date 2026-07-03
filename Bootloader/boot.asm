org 0x7e00
  jmp start
  db 'J' ; is for testing as it will show up at 0x7e04 since long jump
  %include "print.inc"

start:
  mov si, msg
  call print

hang:
  jmp $

  msg db "Alfie Smells and is FAT32", 0
  numbers db "0123456789"