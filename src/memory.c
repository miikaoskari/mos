#include "mos/memory.h"
#include "string.h"
#include <stdint.h>

struct page {
    struct page* next;
    int order;
};

// mem_map uses some random number. should be ram size / page size
struct page *mem_map[4096];

// free_list[x] contains all free order x
struct page *free_list[MAX_ORDER + 1];

void phys_mem_init(uint64_t phys_ram_start, uint64_t phys_ram_size, uint64_t kernel_start_addr, uint64_t kernel_end_addr)
{
    memset(mem_map, 0, sizeof(mem_map));
    memset(free_list, 0, sizeof(free_list));

    return;
}

struct page* alloc_pages(const unsigned int order)
{
    if (order > MAX_ORDER) {
        return NULL;
    }

    struct page* free_block = NULL;

    // find a page from free_list, if any are available
    free_block = free_list[order];

    if (free_block != NULL) {
        free_list[order] = free_block->next;
        return free_block;
    }

    // no free blocks, we must create one from upper order by splitting
    // find next biggest available block and start splitting it
    for (int current_order = order; current_order <= MAX_ORDER; current_order++)
    {
        free_block = free_list[current_order];

        if (free_block == NULL)
        {
            continue;
        }

        // we have a block lets split it until we have desired order
        free_list[order] = free_block->next;




    }

    return free_block;
}

void free_pages(struct page* page)
{
}
