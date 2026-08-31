#ifndef BARRIER_H
#define BARRIER_H

#define isb() asm volatile("isb" : : : "memory")
#define dmb(opt) asm volatile("dmb " #opt : : : "memory")
#define dsb(opt) asm volatile("dsb " #opt : : : "memory")
#define wfe() asm volatile("wfe" : : : "memory")
#define wfi() asm volatile("wfi" : : : "memory")
#define sev() asm volatile("sev" : : : "memory")

#endif // BARRIER_H
