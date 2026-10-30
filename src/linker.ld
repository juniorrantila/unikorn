ENTRY(_start)

SECTIONS
{
    . = 0x100000; /* Load address at 1MB */
    . += 16K;
    _stack_top = .;

    _kernel_start = .;

    .multiboot : {
        KEEP(*(.multiboot))
    }

    .note : {
        KEEP(*(.note))
        KEEP(*(.note.*))
    }

    .text : ALIGN(4K) {
        *(.text)
        *(.text.*)
    }

    .rodata : ALIGN(4K) {
        *(.rodata)
        *(.rodata.*)
    }

    .data : ALIGN(4K) {
        *(.data)
        *(.data.*)
    }

    .bss : ALIGN(4K) {
        _bss_start = .;
        *(.bss)
        *(.bss.*)
        _bss_end = .;
    }

    . = ALIGN(4K);
    _kernel_end = .;
}
