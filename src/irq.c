#include <stdint.h>

typedef struct {
    uint64_t regs[31];
    uint64_t elr;
    uint64_t spsr;
    uint64_t sp;
} pt_regs;

void el1t_64_sync_handler(pt_regs *regs)
{

}

void el1t_64_irq_handler(pt_regs *regs)
{

}

void el1t_64_fiq_handler(pt_regs *regs)
{

}

void el1t_64_error_handler(pt_regs *regs)
{

}

void el1h_64_sync_handler(pt_regs *regs)
{

}

void el1h_64_irq_handler(pt_regs *regs)
{

}

void el1h_64_fiq_handler(pt_regs *regs)
{

}

void el1h_64_error_handler(pt_regs *regs)
{

}

void el0t_64_sync_handler(pt_regs *regs)
{

}

void el0t_64_irq_handler(pt_regs *regs)
{

}

void el0t_64_fiq_handler(pt_regs *regs)
{

}

void el0t_64_error_handler(pt_regs *regs)
{

}

void el0t_32_sync_handler(pt_regs *regs)
{

}

void el0t_32_irq_handler(pt_regs *regs)
{

}

void el0t_32_fiq_handler(pt_regs *regs)
{

}

void el0t_32_error_handler(pt_regs *regs)
{

}
