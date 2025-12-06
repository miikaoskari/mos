#ifndef MEMORY_H
#define MEMORY_H

#define PAGE_SIZE 4096UL
#define RAM_START 0x40000000ULL
#define RAM_SIZE 0x08000000ULL
#define MAX_ORDER 11U

void phys_mem_init(uint64_t phys_ram_start, uint64_t phys_ram_size, uint64_t kernel_start_addr, uint64_t kernel_end_addr);

#endif // MEMORY_H
