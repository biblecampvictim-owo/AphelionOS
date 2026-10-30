OUTPUT_FORMAT("elf64-x86-64")
ENTRY(kernel_entry)

SECTIONS
{
    . = 0x30000;

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
        *(.rodata)
    }

    .bss : {
        *(.bss)
    }
}