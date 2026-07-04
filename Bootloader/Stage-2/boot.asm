org 0x7e00 ; this is the only line that needs to be here
 ; technically the stack registers are initialised but im not convinced they wont get corrupted
 ; also same for ds and the other ones that need to be made 0
 ; you have free reign from here to write whatever boot code you want just dont be stupid
  jmp start
  %include "print.inc"

start: 
  mov si, msg
  call print

hang:
  jmp $

  msg db "Alfie Smells and is FAT32", 0
  numbers db "0123456789" ; fun fact there are 10 digits in base 10 wow