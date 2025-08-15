set -e

echo Now assembling, compiling, and linking your kernel:
nasm -f elf32 -o kernel.o kernel.asm
#rem Remember this spot here: We will add 'gcc' commands here to compile C sources
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-builtin -Wall -O -nostdinc -I./include -c -o sOS.o sOS.c
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-builtin -Wall -O -nostdinc -I./include -c -o basicIO.o basicIO.c
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-builtin -Wall -O -nostdinc -I./include -c -o string.o string.c

#rem This links all your files. Remember that as you add *.o files, you need to
#rem add them after kernel.o. If you don't add them at all, they won't be in your kernel!
ld -m elf_i386 -T link.ld -o kernel.bin kernel.o sOS.o basicIO.o string.o
echo Done!

IMG=myos.img           # Name of the disk image
SIZE=64M               # Size of disk image
MOUNTDIR=/mnt/myos     # Temporary mount point
KERNEL=kernel.bin      # Path to your compiled kernel binary
GRUB_CFG=grub.cfg      # Path to your GRUB config

#check files exist
if [ ! -f "$KERNEL" ]; then
    echo "Error: Kernel file \"$KERNEL\" not found."
    exit 1
fi
if [ ! -f "$GRUB_CFG" ]; then
    echo "Error: GRUB config \"$GRUB_CFG\" not found."
    exit 1
fi

#create img file
echo "- Creating $IMG of size $SIZE..."
qemu-img create -f raw $IMG $SIZE

#partition img file
echo "- Partitioning image..."
parted $IMG --script mklabel msdos
parted $IMG --script mkpart primary fat32 1MiB 100%
parted $IMG --script set 1 boot on

#setup loop device
echo "- Attaching loop device..."
LOOP=$(sudo losetup --find --show --partscan $IMG)
echo "- Loop device is $LOOP"

#wait for partition device to appear
PART="${LOOP}p1"
while [ ! -b "$PART" ]; do sleep 0.1; done

#format partition
echo "- Formatting partition $PART as FAT32..."
sudo mkfs.vfat -F 32 $PART

#mount and compy files
echo "- Mounting partition..."
sudo mkdir -p $MOUNTDIR
sudo mount $PART $MOUNTDIR

#test if kernel is mboot2 valid
echo "- Testing if kernel is multiboot2 valid"
if grub-file --is-x86-multiboot2 $KERNEL; then
	echo "kernel valid."
else
	echo "kernel invalid."
	exit 1
fi

echo "- Copying kernel and GRUB config..."
sudo mkdir -p $MOUNTDIR/boot/grub
sudo cp $KERNEL $MOUNTDIR/boot/
sudo cp $GRUB_CFG $MOUNTDIR/boot/grub/

#install grub
echo "- Installing GRUB..."
sudo grub-install \
  --target=i386-pc \
  --boot-directory=$MOUNTDIR/boot \
  --modules="normal part_msdos biosdisk fat multiboot2" \
  --recheck $LOOP	

#cleanup
echo "- Unmounting and detaching loop device..."
sudo umount $MOUNTDIR
sudo losetup -d $LOOP

echo "- Disk image file $IMG is ready. qemu commmand:"
echo "qemu-system-x86_64 -hda myos.img -m 512M -boot c"
