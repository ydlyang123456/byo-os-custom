; =============================================================================
; BYO-OS - x86_64 Multiboot Boot Entry  
; Uses Multiboot v1 to load 64-bit ELF kernel
; =============================================================================

[BITS 32]

MB_MAGIC    equ 0x1BADB002
MB_MEMINFO  equ 1 << 1
MB_FLAGS    equ MB_MEMINFO
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

; --- GDT (32-bit for boot, loads 64-bit GDT later) ---
section .rodata
align 4
gdt64_entries:
    dq 0                        ; Null descriptor
    ; 64-bit Code Segment (0x08)
    dw 0xFFFF, 0x0000
    db 0x00, 10011010b, 10101111b, 0x00
    ; 64-bit Data Segment (0x10)
    dw 0xFFFF, 0x0000
    db 0x00, 10010010b, 11001111b, 0x00
gdt64_entries_end:

gdt64_ptr:
    dw gdt64_entries_end - gdt64_entries - 1
    dd gdt64_entries

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start32

_start32:
    mov esp, stack_top
    push ebx
    push eax

    cmp eax, MB_MAGIC
    jne .no_multiboot

    ; Enable PAE and PGE
    mov eax, cr4
    or  eax, (1 << 5) | (1 << 7)
    mov cr4, eax

    ; Load PML4 into CR3
    mov edi, pml4_table
    mov cr3, edi

    ; Zero page tables
    xor eax, eax
    mov ecx, (4096 * 3) / 4
    mov edi, pdpt_table
    rep stosd

    ; PML4[0] -> pdpt_table
    mov eax, pdpt_table
    or  eax, 0x03
    mov [pml4_table + 0], eax
    mov dword [pml4_table + 4], 0

    ; PDPT[0..127]: 1GB huge pages
    mov ecx, 128
    mov edi, pdpt_table
    xor eax, eax
.fill_pdpt:
    mov edx, eax
    or  edx, 0x83
    mov [edi], edx
    mov dword [edi + 4], 0
    add eax, 0x40000000
    add edi, 8
    loop .fill_pdpt

    ; Enable Long Mode
    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr

    ; Enable paging
    mov eax, cr0
    or  eax, (1 << 31) | (1 << 0)
    mov cr0, eax

    ; Load GDT and jump to 64-bit
    lgdt [gdt64_ptr]
    jmp 0x08:long_mode_entry

.no_multiboot:
    cli
    hlt
    jmp .no_multiboot

section .data
mb_info_ptr:    dd 0
mb_magic_val:   dd 0

[BITS 64]
long_mode_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, stack_top

    pop rdi
    pop rsi

    ; Call kernel entry
    extern _start64
    call _start64

.hang64:
    cli
    hlt
    jmp .hang64

section .bss
align 4096
pml4_table: resb 4096
pdpt_table: resb 4096

section .note.GNU-stack noalloc noexec nowrite progbits
