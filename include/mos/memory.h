#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define PAGE_SIZE 4096UL
#define RAM_START 0x40000000ULL
#define RAM_SIZE 0x08000000ULL
#define MAX_ORDER 11U
#define MIN_ORDER 0

struct page {
    struct page* next;
    unsigned int order;
};

void phys_mem_init(uint64_t phys_ram_start, uint64_t phys_ram_size, uint64_t kernel_start_addr, uint64_t kernel_end_addr);
struct page* alloc_pages(const unsigned int order);
void free_pages(struct page* page);

#endif // MEMORY_H
