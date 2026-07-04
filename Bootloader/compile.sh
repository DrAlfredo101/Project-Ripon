# compiles the bootloader then injects the bytes from the partition into it too
nasm mbr.asm -f bin -o mbr.bin -l mbr.lst
dd if=/dev/zero of=boot.img bs=1M count=1
mkfs.vfat -F 32 boot.img
python fat_injector.py
dd if=tmp.bin of=boot.img conv=notrunc
rm tmp.bin