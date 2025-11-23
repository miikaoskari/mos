.macro kernel_ventry, el:req, ht:req, regsize:req, lable:req
.align 7
b \label
.endm

.align 11
vectors:
    kernel_ventry	1, t, 64, sync // Synchronous EL1t
    kernel_ventry	1, t, 64, irq // IRQ EL1t
    kernel_ventry	1, t, 64, fiq // FIQ EL1t
    kernel_ventry	1, t, 64, error // Error EL1t

    kernel_ventry	1, h, 64, sync // Synchronous EL1h
    kernel_ventry	1, h, 64, irq // IRQ EL1h
    kernel_ventry	1, h, 64, fiq // FIQ EL1h
    kernel_ventry	1, h, 64, error // Error EL1h

    kernel_ventry	0, t, 64, sync // Synchronous 64-bit EL0
    kernel_ventry	0, t, 64, irq // IRQ 64-bit EL0
    kernel_ventry	0, t, 64, fiq // FIQ 64-bit EL0
    kernel_ventry	0, t, 64, error // Error 64-bit EL0

    kernel_ventry	0, t, 32, sync // Synchronous 32-bit EL0
    kernel_ventry	0, t, 32, irq // IRQ 32-bit EL0
    kernel_ventry	0, t, 32, fiq // FIQ 32-bit EL0
    kernel_ventry	0, t, 32, error // Error 32-bit EL0



irq_vector_init:
    adr x0, vectors
    msr vbar_el1, x0
    ret
