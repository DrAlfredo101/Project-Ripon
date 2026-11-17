clang --target=x86_64-elf -ffreestanding -fno-builtin -fno-stack-protector -fpie -mno-red-zone -nostdlib -fuse-ld=lld -Wl,-T,linker.ld -Wl,--oformat=binary kernel.c -o kernel.bin
