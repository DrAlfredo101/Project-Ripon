with open("boot.img","rb") as f:
  drive_start = f.read(512)

with open("mbr.bin","rb") as f:
  boot_code = bytearray(f.read())

fat32_bpb = drive_start[3:90]

boot_code[3:90] = fat32_bpb
with open("boot.img","rb") as f:
  reserved_region = bytearray(f.read(6*512))

reserved_region[0:512] = boot_code
reserved_region[5*512:6*512] = boot_code

with open("tmp.bin","ab") as f:
  f.write(reserved_region)