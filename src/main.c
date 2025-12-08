#include <stdint.h>
#include <libfdt.h>
#include "mos/driver.h"
#include "mos/memory.h"
#include "mos/log.h"

volatile uint8_t *uart = (uint8_t *) 0x09000000;

void putchar(char c) {
    *uart = c;
}

void print(const char *s)
{
    while(*s != '\0') {
        putchar(*s);
        s++;
    }
}

void kmain(uint64_t dtb_ptr32, __unused uint64_t x1, __unused uint64_t x2, __unused uint64_t x3)
{
    void *fdt = (void *)(uintptr_t)dtb_ptr32;

    info("fdt pointer %p", fdt);

    phys_mem_init(9, 9, 9, 9);
    info("physical memory init done");

    struct page *page = alloc_pages(0);

    register_all_drivers();

    probe_all_drivers_from_fdt(fdt);


    for(;;) {
        asm volatile("wfi");
    }
}
