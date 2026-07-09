# BYO-OS Makefile
CC = gcc
NASM = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs \
         -fno-builtin -fno-stack-protector -fno-exceptions \
         -Wall -Wextra -Iinclude -c
NASMFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T kernel/linker.ld -nostdlib

ASM_SOURCES = kernel/boot_entry.asm kernel/isr.asm kernel/gdt_asm.asm
C_SOURCES = kernel/string.c kernel/vga.c kernel/gdt.c kernel/idt.c \
            kernel/irq.c kernel/keyboard.c kernel/timer.c \
            kernel/memory.c kernel/heap.c kernel/serial.c \
            kernel/process.c kernel/syscall.c kernel/shell.c kernel/main.c
ALL_OBJECTS = $(ASM_SOURCES:.asm=.o) $(C_SOURCES:.c=.o)
KERNEL = byo-os.kernel

.PHONY: all clean iso

all: $(KERNEL)

$(KERNEL): $(ALL_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

iso: $(KERNEL)
	mkdir -p isodir/boot/grub
	cp $(KERNEL) isodir/boot/
	printf 'set timeout=0\nset default=0\nmenuentry "BYO-OS" {\n    multiboot /boot/byo-os.kernel\n    boot\n}\n' > isodir/boot/grub/grub.cfg
	grub-mkrescue -o byo-os.iso isodir

clean:
	rm -f $(ALL_OBJECTS) $(KERNEL) byo-os.iso
	rm -rf isodir