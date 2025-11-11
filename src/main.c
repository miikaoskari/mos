#include <stdint.h>
#include <libfdt.h>
#include "driver.h"

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

void kmain(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
    void *fdt = (void *)(uintptr_t)dtb_ptr32;

    probe_all_drivers_from_fdt(fdt);

    for(;;) {
        // loop forever!
    }
}
