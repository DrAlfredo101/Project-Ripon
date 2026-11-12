print: ; setup the print
  mov ah, 0x0E
  mov bh, 0
  mov bl, [colour]

print_char: ; prints what is in the memory address pointed to by si
  lodsb
  cmp al, 0
  je done
  int 0x10
  jmp print_char

done:
  ret


colour db 0x0D