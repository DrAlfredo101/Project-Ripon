dd if=/dev/zero of=drive.img bs=100M count=1
sudo sgdisk -o drive.img
sgdisk -a 1 -n 0:34:2047 -t 0:ef02 -c 0:"bios_boot" drive.img
sgdisk -n 0:0:+36MiB -t 0:ef00 -c 0:"EFI System Partition" drive.img
sgdisk -n 0:0:+36MiB -t 0:8300 -c 0:"Kernel Partition" drive.img
sh format_partitions.sh