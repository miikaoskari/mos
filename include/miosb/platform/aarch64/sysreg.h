#ifndef SYSREG_H
#define SYSREG_H

#define __stringify(x) #x
#define read_sysreg(r) ({                                  \
    u64 __val;                                             \
    asm volatile("mrs %0, " __stringify(r) : "=r"(__val)); \
    __val;                                                 \
})
#define write_sysreg(v, r)                                           \
    do {                                                             \
        u64 __val = (u64)(v);                                        \
        asm volatile("msr " __stringify(r) ", %x0" : : "rZ"(__val)); \
    } while (0)

#endif // SYSREG_H
