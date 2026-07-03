sh compile.sh
sudo umount /dev/sdb
sudo dd if=boot.img of=/dev/sdb
sudo mount /dev/sdb
sudo umount /dev/sdb
sudo qemu-system-x86_64 /dev/sdb -monitor stdio