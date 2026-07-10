; =============================================================================
; BYO-OS - SMP AP Startup Trampoline
; Executes at physical address 0x8000 in 16-bit real mode.
; Transitions: 16-bit -> 32-bit protected mode -> 64-bit long mode
; Calls ap_main(cpu_number) in the kernel.
;
; Assembled as flat binary: nasm -f bin boot/smp_trampoline.asm
;
; Info block at trampoline offset 0xE0 (filled in by BSP before STARTUP IPI):
;   +0x00: info_cr3      (4 bytes) - BSP's CR3 page table base
;   +0x04: info_stack_top (8 bytes) - AP's stack pointer
;   +0x0C: info_cpu_num   (8 bytes) - AP's CPU number
;   +0x14: info_ap_main   (8 bytes) - ap_main() function address
; =============================================================================

[ORG 0x8000]
[BITS 16]

; ===== 16-bit Real Mode Entry =====
_start:
    cli
    cld

    ; Set up segments & stack
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7FF0              ; stack just below trampoline

    ; Enable A20 gate
    call .enable_a20

    ; Load GDT (null + 32-bit code + data + 64-bit code)
    lgdt [gdt_ptr - _start + 0x8000]

    ; Enable protected mode
    mov eax, cr0
    or  al, 1
    mov cr0, eax

    ; Far jump to 32-bit code (flush prefetch queue)
    jmp dword 0x08:(.prot_mode - _start + 0x8000)

.enable_a20:
    in al, 0x64
    test al, 2
    jnz .enable_a20
    mov al, 0xD1
    out 0x64, al
.wait_kbc:
    in al, 0x64
    test al, 2
    jnz .wait_kbc
    mov al, 0xDF
    out 0x60, al
    ret

; ===== 32-bit Protected Mode Entry =====
[BITS 32]
.prot_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7FF0

    ; Enable PAE and PGE
    mov eax, cr4
    or  eax, (1 << 5) | (1 << 7)   ; PAE + PGE
    mov cr4, eax

    ; Load page table base (BSP's CR3)
    mov eax, [info_cr3 - _start + 0x8000]
    mov cr3, eax

    ; Enable Long Mode (EFER.LME = 1)
    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr

    ; Enable paging (CR0.PG = 1)
    mov eax, cr0
    or  eax, (1 << 31) | (1 << 0)   ; PG + PE
    mov cr0, eax

    ; Far jump to 64-bit long mode (selector 0x18 = 64-bit code)
    jmp dword 0x18:(.long_mode - _start + 0x8000)

; ===== 64-bit Long Mode Entry =====
[BITS 64]
.long_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    xor ax, ax
    mov fs, ax
    mov gs, ax

    ; Restore RSP from info block
    mov rsp, [info_stack_top - _start + 0x8000]

    ; Load CPU number
    mov rax, [info_cpu_num - _start + 0x8000]

    ; Call ap_main(cpu_number)
    mov rdi, rax
    mov rax, [info_ap_main - _start + 0x8000]
    call rax

.halt:
    cli
    hlt
    jmp .halt

; ===== GDT =====
align 8
gdt:
    dq 0                                   ; 0x00: Null
    ; 0x08: 32-bit code segment
    dw 0xFFFF, 0x0000
    db 0x00, 10011010b, 11001111b, 0x00
    ; 0x10: 32-bit data segment (usable in long mode too)
    dw 0xFFFF, 0x0000
    db 0x00, 10010010b, 11001111b, 0x00
    ; 0x18: 64-bit code segment
    dw 0xFFFF, 0x0000
    db 0x00, 10011010b, 10101111b, 0x00
gdt_end:

gdt_ptr:
    dw gdt_end - gdt - 1
    dd gdt                      ; GDT physical address (32-bit, < 0x10000)

; ===== Info Block (at fixed offset 0xE0 from trampoline start) =====
; Pad to offset 0xE0
times (0xE0 - ($ - $$)) db 0

info_cr3:       dd 0            ; +0xE0: CR3 page table base address
info_stack_top: dq 0            ; +0xE4: AP stack top
info_cpu_num:   dq 0            ; +0xEC: CPU number
info_ap_main:   dq 0            ; +0xF4: ap_main() entry point

trampoline_end: