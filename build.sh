#!/bin/bash
cd /mnt/e/aisystem/byo-os
rm -f kernel/*.o kernel/*.bin byo-os.kernel byo-os.iso
rm -rf isodir

echo "=== Assemble 32-bit ==="
nasm -f elf32 kernel/boot_entry.asm -o kernel/boot_entry.o
nasm -f elf32 kernel/isr.asm -o kernel/isr.o
nasm -f elf32 kernel/gdt_asm.asm -o kernel/gdt_asm.o
nasm -f elf32 kernel/ctx_switch.asm -o kernel/ctx_switch.o

echo "=== Compile ==="
CFLAGS="-m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -fno-stack-protector -fno-exceptions -Wall -Wextra -Iinclude"
SOURCES="kernel/string.c kernel/font.c kernel/vga.c kernel/gdt.c kernel/idt.c kernel/irq.c kernel/keyboard.c kernel/timer.c kernel/memory.c kernel/heap.c kernel/serial.c kernel/fs.c kernel/scheduler.c kernel/mouse.c kernel/net.c kernel/ne2000.c kernel/user.c kernel/vga_modes.c kernel/panel.c kernel/journal.c kernel/shell.c kernel/main.c"
for f in $SOURCES; do
    errs=$(gcc $CFLAGS -c "$f" -o "${f%.c}.o" 2>&1 | grep -i error)
    if [ -n "$errs" ]; then echo "ERROR in $f:"; echo "$errs"; fi
done
echo "Done: $(ls kernel/*.o | wc -l) object files"

echo "=== Link ==="
ld -m elf_i386 -T kernel/linker.ld -o byo-os.kernel kernel/*.o 2>&1 | head -10
echo "Kernel: $(stat -c%s byo-os.kernel) bytes"

echo "=== ISO ==="
mkdir -p isodir/boot/grub
cp byo-os.kernel isodir/boot/
cat > isodir/boot/grub/grub.cfg << 'GRUBEOF'
set timeout=5
set default=0
menuentry "BYO-OS" {
    multiboot /boot/byo-os.kernel
    boot
}
GRUBEOF
grub-mkrescue -o byo-os.iso isodir 2>&1 | tail -1
echo "ISO: $(stat -c%s byo-os.iso) bytes"

echo "=== DONE ==="