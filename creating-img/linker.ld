ENTRY(kernelMain)

SECTIONS {
    . = 0x0;

    .text : {
        KEEP(*(.text.kenel_entry))
        *(.text*)
    }

    .rodata : ALIGN(16) {
        *(.rodata*)
    }

    .data : ALIGN(16) {
        *(.data*)
    }

    .bss : ALIGN(16) {
        _bss_start = .;
        *(COMMON)
        *(.bss*)
        _bss_end = .;
    }

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame*)
        *(.note*)
        *(.interp)
    }
}