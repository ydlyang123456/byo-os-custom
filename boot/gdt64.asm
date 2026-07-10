; =============================================================================
; BYO-OS - 64-bit Global Descriptor Table
; Loaded by boot_entry_64.asm before jumping into long mode
; =============================================================================

[BITS 32]

section .rodata
align 4

; --- GDT entries -------------------------------------------------------------
gdt64_start:
    ; Null descriptor (index 0x00)
    dq 0

    ; 64-bit Code Segment (index 0x08)
    ;   Base  = 0, Limit = 0 (ignored in long mode)
    ;   Access: Present=1, Ring=0, Type=Code, Readable=1
    ;   Flags:  L=1 (64-bit), D=0 (must be 0 in long mode), Granularity=0
    ;   L=1, D=0 means "64-bit long mode code"
    dw 0xFFFF           ; Limit 0:15
    dw 0x0000           ; Base 0:15
    db 0x00             ; Base 16:23
    db 10011010b        ; Access: P=1, DPL=00, S=1, Type=1010 (Code: Exec/Read)
    db 10101111b        ; Flags (4b): G=1, D=0, L=1, reserved=0
                         ; Limit 16:19 = 0xF
    db 0x00             ; Base 24:31

    ; 64-bit Data Segment (index 0x10)
    ;   Access: Present=1, Ring=0, Type=Data, Writable=1
    ;   L/D irrelevant for data segments in long mode
    dw 0xFFFF           ; Limit 0:15
    dw 0x0000           ; Base 0:15
    db 0x00             ; Base 16:23
    db 10010010b        ; Access: P=1, DPL=00, S=1, Type=0010 (Data: Read/Write)
    db 11001111b        ; Flags: G=1, D/B=1, L=0, reserved=0
                         ; Limit 16:19 = 0xF
    db 0x00             ; Base 24:31
gdt64_end:

; --- GDT pointer -------------------------------------------------------------
gdt64_ptr:
    dw gdt64_end - gdt64_start - 1   ; Size (limit) of GDT - 1
    dd gdt64_start                     ; Linear address of GDT

; Export for use by C code if needed
global gdt64_ptr
