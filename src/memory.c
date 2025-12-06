#include "mos/memory.h"
#include <stdint.h>

struct buddy_block
{
    struct buddy_block *next;
    int order;
};

void phys_mem_init(uint64_t phys_ram_start, uint64_t phys_ram_size, uint64_t kernel_start_addr, uint64_t kernel_end_addr)
{


}
