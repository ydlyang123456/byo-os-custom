; =============================================================================
; BYO-OS - 64-bit Context Switch (System V AMD64 ABI)
; void ctx_switch(uint64_t* old_sp, uint64_t new_sp);
;   rdi = old_sp   (pointer to save current rsp)
;   rsi = new_sp   (value to restore as rsp)
;
; Compiled with: nasm -f elf64 ctx_switch64.asm
; =============================================================================

[BITS 64]

section .text
global ctx_switch

ctx_switch:
    ; -- save callee-saved registers (System V ABI: rbx, rbp, r12-r15) --
    push rbp
    push rbx
    push r12
    push r13
    push r14
    push r15

    ; -- save current stack pointer to *old_sp --
    mov [rdi], rsp

    ; -- switch to new stack --
    mov rsp, rsi

    ; -- restore callee-saved registers from new stack --
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp

    ret

section .note.GNU-stack noalloc noexec nowrite progbits