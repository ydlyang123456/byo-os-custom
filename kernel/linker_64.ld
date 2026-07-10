/* BYO-OS - Linker Script for x86_64 ELF Kernel */
ENTRY(_start64)

SECTIONS {
    . = 1M;

    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
        *(.text.*)
    }

    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
        *(.rodata.*)
    }

    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
        *(.data.*)
    }

    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.bss.*)
        __kernel_end = .;
    }

    /DISCARD/ : {
        *(.note.GNU-stack)
        *(.comment)
        *(.eh_frame)
    }
}
