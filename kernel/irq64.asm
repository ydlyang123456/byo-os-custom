; =============================================================================
; BYO-OS - 64-bit IRQ Handler Stubs
; IRQ0-15 mapped to INT 32-47 after PIC remap.
; Sends EOI to PIC (master/slave) before calling C irq_handler.
; Compiled with: nasm -f elf64 irq64.asm
; =============================================================================

[BITS 64]

extern irq_handler

; ---------------------------------------------------------------------------
; PIC I/O ports
; ---------------------------------------------------------------------------
%define PIC1_CMD    0x20
%define PIC1_DATA   0x21
%define PIC2_CMD    0xA0
%define PIC2_DATA   0xA1
%define PIC_EOI     0x20

; ---------------------------------------------------------------------------
; Macro: IRQ_STUB  interrupt_number
; Pushes dummy error code + int number, sends EOI, then calls C handler.
; ---------------------------------------------------------------------------
%macro IRQ_STUB 1
global irq%1
irq%1:
    push qword 0            ; dummy error code
    push qword %1           ; interrupt number

    ; -- send EOI to PIC --
    ; If IRQ >= 40 (slave PIC), send EOI to slave first
    cmp qword [rsp], 40
    jl .irq%1_master_only
    mov al, PIC_EOI
    out PIC2_CMD, al
.irq%1_master_only:
    ; Always send EOI to master PIC
    mov al, PIC_EOI
    out PIC1_CMD, al

    ; -- build regs pointer and call C handler --
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rdi
    push rsi
    push rbp
    push rdx
    push rcx
    push rbx
    push rax

    mov ax, 0x10
    mov ds, ax
    mov es, ax

    mov rdi, rsp            ; regs_t64* = pointer to saved registers
    call irq_handler

    mov ax, 0x10
    mov ds, ax
    mov es, ax

    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rbp
    pop rsi
    pop rdi
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15

    add rsp, 16             ; discard int_no + err_code
    iretq
%endmacro

; ---------------------------------------------------------------------------
; IRQ0-15  ->  INT 32-47
; ---------------------------------------------------------------------------
IRQ_STUB 32                 ; IRQ0  - PIT Timer
IRQ_STUB 33                 ; IRQ1  - Keyboard
IRQ_STUB 34                 ; IRQ2  - Cascade
IRQ_STUB 35                 ; IRQ3  - COM2
IRQ_STUB 36                 ; IRQ4  - COM1
IRQ_STUB 37                 ; IRQ5  - LPT2
IRQ_STUB 38                 ; IRQ6  - Floppy
IRQ_STUB 39                 ; IRQ7  - LPT1 / Spurious
IRQ_STUB 40                 ; IRQ8  - RTC
IRQ_STUB 41                 ; IRQ9  - ACPI / Redirected
IRQ_STUB 42                 ; IRQ10 - Open
IRQ_STUB 43                 ; IRQ11 - Open
IRQ_STUB 44                 ; IRQ12 - PS/2 Mouse
IRQ_STUB 45                 ; IRQ13 - FPU
IRQ_STUB 46                 ; IRQ14 - Primary ATA
IRQ_STUB 47                 ; IRQ15 - Secondary ATA

section .note.GNU-stack noalloc noexec nowrite progbits