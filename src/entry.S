.set S_FRAME_SIZE, 288

.macro kernel_ventry, el:req, ht:req, regsize:req, label:req
.align 7
b el\el\ht\()_\regsize\()_\label
.endm // kernel_ventry

.macro	kernel_entry el:req, regsize:req
sub	sp, sp, #S_FRAME_SIZE
stp	x0, x1, [sp, #16 * 0]
stp	x2, x3, [sp, #16 * 1]
stp	x4, x5, [sp, #16 * 2]
stp	x6, x7, [sp, #16 * 3]
stp	x8, x9, [sp, #16 * 4]
stp	x10, x11, [sp, #16 * 5]
stp	x12, x13, [sp, #16 * 6]
stp	x14, x15, [sp, #16 * 7]
stp	x16, x17, [sp, #16 * 8]
stp	x18, x19, [sp, #16 * 9]
stp	x20, x21, [sp, #16 * 10]
stp	x22, x23, [sp, #16 * 11]
stp	x24, x25, [sp, #16 * 12]
stp	x26, x27, [sp, #16 * 13]
stp	x28, x29, [sp, #16 * 14]
str x30, [sp, #16 * 15]

// save exception link reg
mrs x21, elr_el1

// save state
mrs x22, spsr_el1

.if \el == 0
mrs x23, sp_el0
.else
add x23, sp, #S_FRAME_SIZE
.endif

// store pc, pstate and sp
stp x21, x22, [sp, #16 * 16]
str x23, [sp, #16 * 17]
.endm // kernel_entry

.macro	kernel_exit
// load pc, pstate and sp
ldp x21, x22, [sp, #16 * 16]
msr elr_el1, x21
msr spsr_el1, x22

// restore gprs
ldp	x0, x1, [sp, #16 * 0]
ldp	x2, x3, [sp, #16 * 1]
ldp	x4, x5, [sp, #16 * 2]
ldp	x6, x7, [sp, #16 * 3]
ldp	x8, x9, [sp, #16 * 4]
ldp	x10, x11, [sp, #16 * 5]
ldp	x12, x13, [sp, #16 * 6]
ldp	x14, x15, [sp, #16 * 7]
ldp	x16, x17, [sp, #16 * 8]
ldp	x18, x19, [sp, #16 * 9]
ldp	x20, x21, [sp, #16 * 10]
ldp	x22, x23, [sp, #16 * 11]
ldp	x24, x25, [sp, #16 * 12]
ldp	x26, x27, [sp, #16 * 13]
ldp	x28, x29, [sp, #16 * 14]
ldr x30, [sp, #16 * 15]

// restore stack pointer
add sp, sp, #S_FRAME_SIZE
eret
.endm // kernel_exit

.align 11
vectors:
    kernel_ventry 1, t, 64, sync // Synchronous EL1t
    kernel_ventry 1, t, 64, irq // IRQ EL1t
    kernel_ventry 1, t, 64, fiq // FIQ EL1t
    kernel_ventry 1, t, 64, error // Error EL1t

    kernel_ventry 1, h, 64, sync // Synchronous EL1h
    kernel_ventry 1, h, 64, irq // IRQ EL1h
    kernel_ventry 1, h, 64, fiq // FIQ EL1h
    kernel_ventry 1, h, 64, error // Error EL1h

    kernel_ventry 0, t, 64, sync // Synchronous 64-bit EL0
    kernel_ventry 0, t, 64, irq // IRQ 64-bit EL0
    kernel_ventry 0, t, 64, fiq // FIQ 64-bit EL0
    kernel_ventry 0, t, 64, error // Error 64-bit EL0

    kernel_ventry 0, t, 32, sync // Synchronous 32-bit EL0
    kernel_ventry 0, t, 32, irq // IRQ 32-bit EL0
    kernel_ventry 0, t, 32, fiq // FIQ 32-bit EL0
    kernel_ventry 0, t, 32, error // Error 32-bit EL0


.macro entry_handler, el:req, ht:req, regsize:req, label:req
el\el\ht\()_\regsize\()_\label:
    kernel_entry \el, \regsize
    mov x0, sp
    bl el\el\ht\()_\regsize\()_\label\()_handler
    kernel_exit
.endm // entry_handler

entry_handler	1, t, 64, sync
entry_handler	1, t, 64, irq
entry_handler	1, t, 64, fiq
entry_handler	1, t, 64, error

entry_handler	1, h, 64, sync
entry_handler	1, h, 64, irq
entry_handler	1, h, 64, fiq
entry_handler	1, h, 64, error

entry_handler	0, t, 64, sync
entry_handler	0, t, 64, irq
entry_handler	0, t, 64, fiq
entry_handler	0, t, 64, error

entry_handler	0, t, 32, sync
entry_handler	0, t, 32, irq
entry_handler	0, t, 32, fiq
entry_handler	0, t, 32, error

irq_vector_init:
    adr x0, vectors
    msr vbar_el1, x0
    ret
