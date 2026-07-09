; BYO-OS - Context Switch (x86)
; void context_switch(cpu_state_t* prev, cpu_state_t* next)

section .text
global context_switch

context_switch:
    ; Save current CPU state to prev
    mov [esp + 4], eax
    mov [esp + 8], ebx
    mov [esp + 12], ecx
    mov [esp + 16], edx
    mov [esp + 20], esi
    mov [esp + 24], edi
    mov [esp + 28], ebp

    ; Save EIP (return address)
    mov eax, [esp]
    mov [esp + 36], eax

    ; Save EFLAGS
    pushfd
    pop eax
    mov [esp + 40], eax

    ; Save segment registers
    mov ax, cs
    mov [esp + 44], eax
    mov ax, ss
    mov [esp + 48], eax
    mov ax, ds
    mov [esp + 52], eax
    mov ax, es
    mov [esp + 56], eax
    mov ax, fs
    mov [esp + 60], eax
    mov ax, gs
    mov [esp + 64], eax

    ; Save ESP
    lea eax, [esp + 4]
    mov [esp + 32], eax

    ; Load next CPU state
    mov ebx, [esp + 8]     ; next pointer

    ; Load segment registers
    mov ax, [ebx + 48]     ; ss
    mov ss, ax
    mov ax, [ebx + 52]     ; ds
    mov ds, ax
    mov ax, [ebx + 56]     ; es
    mov es, ax
    mov ax, [ebx + 60]     ; fs
    mov fs, ax
    mov ax, [ebx + 64]     ; gs
    mov gs, ax

    ; Load ESP
    mov esp, [ebx + 32]

    ; Load EFLAGS
    push dword [ebx + 40]
    popfd

    ; Load EIP via ret
    push dword [ebx + 36]
    ret

section .note.GNU-stack noalloc noexec nowrite progbits