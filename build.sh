#!/bin/bash

i386-elf-gcc -ffreestanding -m32 -c kmain.c -o kmain.bin 
i386-elf-ld -o kernel.bin -Tlinker.ld bootloader.bin kmain.bin --oformat binary
qemu-system-x86_64 -drive file=kernel.bin,index=0,media=disk,format=raw -vga std