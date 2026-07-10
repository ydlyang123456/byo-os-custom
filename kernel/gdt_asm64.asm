; =============================================================================
; BYO-OS - 64-bit GDT Initialization (pure assembly)
; Loads a 64-bit GDT with null, code, and data segments.
; Compiled with: nasm -f elf64 gdt_asm64.asm
; =============================================================================

[BITS 64]

section .rodata
align 4

gdt64_entries:
    ; Null descriptor (index 0x00)
    dq 0

    ; 64-bit Code Segment (index 0x08)
    ;   Base = 0, Limit = 0 (ignored in long mode)
    ;   Access: P=1, DPL=00, S=1, Type=Code Exec/Read (1010b)
    ;   Flags:  G=1, D=0, L=1 (64-bit long mode), reserved=0
    dw 0xFFFF           ; Limit 0:15
    dw 0x0000           ; Base 0:15
    db 0x00             ; Base 16:23
    db 10011010b        ; Access: Present, Ring 0, Code, Exec/Read
    db 10101111b        ; Flags: G=1 D=0 L=1 + Limit 16:19=0xF
    db 0x00             ; Base 24:31

    ; 64-bit Data Segment (index 0x10)
    ;   Access: P=1, DPL=00, S=1, Type=Data Read/Write (0010b)
    dw 0xFFFF           ; Limit 0:15
    dw 0x0000           ; Base 0:15
    db 0x00             ; Base 16:23
    db 10010010b        ; Access: Present, Ring 0, Data, Read/Write
    db 11001111b        ; Flags: G=1 D/B=1 L=0 + Limit 16:19=0xF
    db 0x00             ; Base 24:31

gdt64_entries_end:

section .data
align 4

gdt64_ptr:
    dw gdt64_entries_end - gdt64_entries - 1   ; limit
    dq gdt64_entries                           ; base (64-bit)

section .text
global gdt_init_asm

gdt_init_asm:
    lgdt [gdt64_ptr]

    ; Reload CS via far return (can't mov cs in long mode)
    push qword 0x08                   ; code segment selector
    lea rax, [rel .reload_cs]
    push rax
    retfq                             ; far return -> loads CS

.reload_cs:
    mov ax, 0x10                      ; data segment selector
    mov ds, ax
    mov es, ax
    mov ss, ax
    xor ax, ax
    mov fs, ax
    mov gs, ax
    ret

section .note.GNU-stack noalloc noexec nowrite progbits