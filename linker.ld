ENTRY(_start)
SECTIONS {
    . = 0x40100000; /* RAM starts at 0x40000000 but if we ask to load the kernel there, QEMU will not load a DTB */
    __kernel_start = .;
    .startup . : { *boot*.o(.text) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss COMMON) }

    .drivers : {
        __drivers_start = .;
        KEEP(*(.drivers))
        __drivers_end = .;
    }

    . = ALIGN(16);
    . += 0x4000; /* 16kB of stack memory */
    stack_top = .;

    __kernel_end = .;
}
