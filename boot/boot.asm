; =============================================================================
; BYO-OS - Multiboot Header + Kernel Entry Point
; Loaded by GRUB in 32-bit protected mode
; =============================================================================

; Multiboot constants
MBALIGN  equ 1 << 0            ; Align loaded modules on page boundaries
MEMINFO  equ 1 << 1            ; Provide memory map
FLAGS    equ MBALIGN | MEMINFO
MAGIC    equ 0x1BADB002        ; Multiboot magic number
CHECKSUM equ -(MAGIC + FLAGS)

; Multiboot header (must be in first 8KB)
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Stack (16KB)
section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

; Entry point
section .text
global _start
extern kernel_main

_start:
    ; Set up stack
    mov esp, stack_top

    ; Push Multiboot arguments
    push ebx        ; Multiboot information structure
    push eax        ; Multiboot magic number

    ; Call kernel entry
    call kernel_main

    ; Should never return, but just in case
.hang:
    cli
    hlt
    jmp .hang

section .note.GNU-stack noalloc noexec nowrite progbits