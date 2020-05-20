ENTRY(KernelMain)

SECTIONS
{
    . = 0x100000000;
    .text ALIGN(0x1000): {
        *(.text)
}
.data ALIGN(0x1000): {
    *(.data)
}

.rodata : { *(.rodata)
}
.bss :{ *(.bss) }
.got : {
    *(.got)
}
}
