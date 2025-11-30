#include "mos/arch.h"

enable_fp:
    mrs x0, cpacr_el1
    orr x0, x0, #CPACR_EL1_FPEN(CPACR_EL1_FP_TRAP_NONE)
    msr cpacr_el1, x0
    ret

.global _start
_start:
    bl enable_fp
    ldr x30, =stack_top
    mov sp, x30
    mov x0, 0x40000000
    bl kmain
    b .
