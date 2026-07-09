; BYO-OS - GDT Initialization (pure assembly)

section .data
align 4
gdt_entries:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
    dq 0x00CFFA000000FFFF
    dq 0x00CFF2000000FFFF

gdt_ptr:
    dw 40 - 1
    dd gdt_entries

section .text
global gdt_init_asm

gdt_init_asm:
    lgdt [gdt_ptr]
    jmp 0x08:.reload_cs
.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits