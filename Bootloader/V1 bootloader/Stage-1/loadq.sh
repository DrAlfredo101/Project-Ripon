# DO NOT USE THIS CODE AS IT IS ONLY CONFIGURED TO WORK ON ONE MACHINE WITH SDB
# trys to do the jiggery pokery i do manually but it hasnt quite figured it out yet
sh compile.sh
sudo umount /dev/sdb
sudo dd if=boot.img of=/dev/sdb
sudo mount /dev/sdb
sudo cp boot.bin /dev/sdb
sudo umount /dev/sdb
sudo qemu-system-x86_64 /dev/sdb -monitor stdio