#!/bin/bash
cd /mnt/e/aisystem/byo-os
rm -f kernel/*.o kernel/*.bin byo-os.kernel byo-os.iso
rm -rf isodir

echo "=== Assemble x86_64 ==="
nasm -f elf64 boot/boot_entry_64.asm -o kernel/boot_entry_64.o 2>&1
nasm -f elf64 boot/gdt64.asm -o kernel/gdt64.o 2>&1
nasm -f bin boot/smp_trampoline.asm -o kernel/smp_tramp.bin 2>&1 || echo 'SMP trampoline binary skipped (optional)'

for f in kernel/isr64.asm kernel/gdt_asm64.asm kernel/ctx_switch64.asm kernel/irq64.asm; do
    if [ -f "$f" ]; then
        nasm -f elf64 "$f" -o "${f%.asm}.o" 2>&1
    fi
done

echo "=== Compile x86_64 ==="
CFLAGS="-m64 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -fno-stack-protector -fno-exceptions -mcmodel=large -fno-pic -fno-pie -mno-red-zone -Wno-unused-function -Wno-unused-variable -Wno-pointer-sign -Iinclude"

SOURCES=""
for f in kernel/string.c kernel/font.c kernel/vga.c kernel/serial.c kernel/fs.c kernel/journal.c kernel/shell.c kernel/ata.c kernel/rtc.c kernel/pci.c kernel/fat32.c kernel/tcpip.c kernel/sound.c kernel/gfx_enhanced.c kernel/usb.c kernel/vbe.c; do
    [ -f "$f" ] && SOURCES="$SOURCES $f"
done

 for f in kernel/memory64.c kernel/heap64.c kernel/vmm.c kernel/syscall.c kernel/initramfs.c kernel/elf_loader.c; do
    [ -f "$f" ] && SOURCES="$SOURCES $f"
done

for f in kernel/gdt.c kernel/idt.c kernel/irq.c kernel/keyboard.c kernel/timer.c kernel/sound.c kernel/scheduler.c kernel/mouse.c kernel/net.c kernel/ne2000.c kernel/user.c kernel/vga_modes.c kernel/panel.c kernel/main.c kernel/smp.c kernel/procfs.c; do
    [ -f "$f" ] && SOURCES="$SOURCES $f"
done

ERRCOUNT=0
for f in $SOURCES; do
    errs=$(gcc $CFLAGS -c "$f" -o "${f%.c}.o" 2>&1 | grep -i "error:" | head -5)
    if [ -n "$errs" ]; then
        echo "ERROR in $f:"
        echo "$errs"
        ERRCOUNT=$((ERRCOUNT+1))
    fi
done
echo "Done: $(ls kernel/*.o 2>/dev/null | wc -l) object files, $ERRCOUNT errors"

echo "=== Link x86_64 ==="
ld -m elf_x86_64 -T kernel/linker_64.ld -o byo-os.kernel kernel/*.o 2>&1 | head -20
if [ -s byo-os.kernel ]; then
    echo "Kernel: $(stat -c%s byo-os.kernel) bytes"
else
    echo "LINK FAILED"
    exit 1
fi

echo "=== ISO ==="
mkdir -p isodir/boot/grub
cp byo-os.kernel isodir/boot/
cat > isodir/boot/grub/grub.cfg << 'EOF'
set timeout=5
set default=0
menuentry "BYO-OS (x86_64)" {
    multiboot /boot/byo-os.kernel
    boot
}
EOF
grub-mkrescue -o byo-os.iso isodir 2>&1 | tail -1
echo "ISO: $(stat -c%s byo-os.iso) bytes"

echo "=== DONE ==="
