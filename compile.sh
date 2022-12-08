cd src
i686-elf-as boot.s -o ../bin/boot.o
i686-elf-as functions.s -o ../bin/functions.o
i686-elf-gcc -c kernel.c -o ../bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c disk.c -o ../bin/disk.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c ustar.c -o ../bin/ustar.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c vga.c -o ../bin/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c serial.c -o ../bin/serial.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c strings.c -o ../bin/strings.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c memory.c -o ../bin/memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
cd ../bin/
i686-elf-gcc -T ../linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o functions.o kernel.o disk.o serial.o strings.o ustar.o vga.o memory.o -lgcc
cd ..
cp ./bin/os.bin isodir/boot/os.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o os.iso isodir

