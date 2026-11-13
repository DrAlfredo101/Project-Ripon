dd if=/dev/zero of=drive.img bs=100M count=1
sudo sgdisk -o drive.img
sgdisk -a 1 -n 1:34:2047 -t 1:ef02 -c 1:"bios_boot" drive.img
sgdisk -n 2:2048:+36M -t 2:ef00 -c 2:"EFI System Partition" drive.img