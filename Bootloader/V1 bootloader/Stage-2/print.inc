do_char:
  call cprint ; print a character and then go back to sprint
sprint: 
  lodsb ; puts the current character pointed to by si into al then increments si to point to the next character in the string
  cmp al, 0 ; check for end of string
  jne do_char ; if not end of string print the character and go back to the start of sprint
  add byte [ypos], 1 ; end of string so move on to the next line
  mov byte [xpos], 0 ; and reset to the start of the line
  xor ax, ax ; set ax to 0 for es
  mov es, ax ; set es to 0 so other stuff dont break or something
  ret

print:
  mov ax, 0xb800 ; 0xb800 into ax for es
  mov es, ax ; 0xb800 into es as that is what lets us print stuff
  jmp sprint ; now we can start actually printing stuff

cprint:
  mov ah,0x0D ; tell the magic screen to print in a certain format (green on black) also known as the attribute
  mov cx,ax ; save the character and attribute (ax) temporarily in cx
  movzx ax, byte [ypos] ; store the y position in al (second byte of ax) and 0s for ah
  mov dx, 160 ; store 160 in dx (each character has 2 bytes(the character and its attribute) and each row has 80 characters, multiply to find most of offset)
  mul dx ; multiply dx by ax and store in ax (only works for low enough ax but max for this is 80 which is fine otherwise it overflows into dx)
  movzx bx, byte [xpos] ; store the x position in bl (second byte of bx) and 0s for bh
  shl bx, 1 ; left shift b by 1 (times 2), this adds the final bit of offset for the video memory for the column
  
  mov di, 0 ; set the offset to 0
  add di, ax ; add row offset to di
  add di, bx ; add column offset to di, di now points to the place on screen to display the charcater

  mov ax,cx ; get the character and attribute cx back into ax ready for printing
  stosw ; copy ax to es:di which currently points to the position in the video memory for printing the character
  add byte [xpos], 1 ; increment xpos so it points at the next position to print to

  ret

print_reg16:
  mov di, outstr16 ; points di to the start of outstr16 to go through and update with the correct values
  mov ax, [reg16] ; puts the contents of reg16 into ax
  mov si, hexstr ; changes si to point to the start of hexstr
  mov cx, 4 ; puts 4 in cx, acting as a count controlled loop
hexloop:
  rol ax, 4 ; cicular left shift of ax 4 places moving leftmost 4 bits to the rightmost 4 bits
  mov bx, ax; copy ax into bx to preserve ax for the next loop
  and bx, 0x0f, ; clears upper 12 bits and leaves lower 4 bits resulting in bx storing the rightmost 4 bits of ax which is the leftmost of video mem 1
  mov bl, [si+bx] ; changes bl to be the value of the hex lookup + offset so it points to the correct character representing the 4 bits
  mov [di], bl ; change the char pointed to by di which is in the outstr16 to the correct char which is in bl
  inc di ; move to the next char in outstr16
  dec cx ; only needs to happen 4 times
  jnz hexloop ; loop back if not finished

  mov si, outstr16 ; once outstr16 contains the data in string hex format, put it in si ready for printing
  call print ; print outstr16

  ret


  xpos db 0 ; position along the rows for the video memory
  ypos db 0 ; how many rows down for video memory
  hexstr db '0123456789ABCDEF'
  outstr16 db '0000', 0 ; empty initialised string to print the first character in hex
  reg16 dw 0 ; initialise 2 bytes for reg16