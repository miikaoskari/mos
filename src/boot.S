.global _start
_start:
    ldr x30, =stack_top
    mov sp, x30
    mov x0, 0x40000000
    bl kmain
    b .
