clang -target x86_64-unknown-windows \
      -ffreestanding \
      -fshort-wchar \
      -mno-red-zone \
      -nostdlib \
      -Wl,-entry:efi_main \
      -Wl,-subsystem:efi_application \
      -fuse-ld=lld \
      boot.c -o esp/EFI/BOOT/BOOTX64.EFI
