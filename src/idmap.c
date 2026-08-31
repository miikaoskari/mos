#include "miosb/types.h"
#include "miosb/platform/aarch64/mmu.h"
#include "miosb/platform/aarch64/pgtable.h"
#include "miosb/bits.h"
#include "miosb/platform/aarch64/sysreg.h"
#include <platform/aarch64/barrier.h>
#include <stdbool.h>

#define GRANULE_SIZE 4096
#define TABLE_ENTRIES_COUNT 512
#define SZ_2M 0x200000UL

#define PAGE_SHIFT     12
#define TABLE_SHIFT    9
#define PTRS_PER_TABLE (1 << TABLE_SHIFT)

#define L1_SHIFT  (PAGE_SHIFT + 2 * TABLE_SHIFT)   /* 30 — 1GB per entry */
#define L2_SHIFT  (PAGE_SHIFT + TABLE_SHIFT)        /* 21 — 2MB per entry */

#define L1_IDX(va)  (((va) >> L1_SHIFT) & (TABLE_ENTRIES_COUNT - 1))
#define L2_IDX(va)  (((va) >> L2_SHIFT) & (TABLE_ENTRIES_COUNT - 1))

#define ALIGN_DOWN(x, a) ((x) & ~((a) - 1))
#define ALIGN_UP(x, a) (((x) + (a) - 1) & ~((a) - 1))

extern char __kernel_start[];
extern char __kernel_end[];

/* 1GB blocks */
__attribute__((aligned(GRANULE_SIZE)))
u64 l1_table[TABLE_ENTRIES_COUNT];

/* 2MB blocks */
__attribute__((aligned(GRANULE_SIZE)))
u64 l2_table[TABLE_ENTRIES_COUNT];

/* 4KB blocks */
// __attribute__((aligned(GRANULE_SIZE)))
// u64 l3_table[TABLE_ENTRIES_COUNT];

static void enable_mmu(u64 t0sz, u64 ips)
{
    u64 tcr_val = 0;
    tcr_val |= FIELD_PREP(TCR_EL1_T0SZ_MASK, t0sz);
    tcr_val |= FIELD_PREP(TCR_EL1_TG0_MASK, TCR_EL1_TG0_4K);
    tcr_val |= FIELD_PREP(TCR_EL1_SH0_MASK, TCR_EL1_SH0_INNER);
    tcr_val |= FIELD_PREP(TCR_EL1_ORGN0_MASK, TCR_EL1_RGN_WBWA);
    tcr_val |= FIELD_PREP(TCR_EL1_IRGN0_MASK, TCR_EL1_RGN_WBWA);
    tcr_val |= FIELD_PREP(TCR_EL1_IPS_MASK, ips);
    tcr_val |= TCR_EL1_EPD1;

    write_sysreg(tcr_val, tcr_el1);

    u64 sctlr_val = 0;
    sctlr_val |= SCTLR_EL1_M;

    write_sysreg(sctlr_val, sctlr_el1);

    asm volatile("tlbi vmalle1" : : : "memory");
    dsb(ish);
    isb();

    return;
}

static u64 read_aa64mmfr0_parange(void)
{
    u64 mmfr0 = read_sysreg(id_aa64mmfr0_el1);
    u64 parange = FIELD_GET(ID_AA64MMFR0_EL1_PARANGE_MASK, mmfr0);
    return parange;
}


static void build_idmap(void)
{
    u64 kernel_start_addr = ALIGN_DOWN((uptr)__kernel_start, SZ_2M);
    u64 kernel_end_addr = ALIGN_UP((uptr)__kernel_end, SZ_2M);

    l1_table[L1_IDX(kernel_start_addr)] = pte_table((u64)l2_table);

    for (u64 pa = kernel_start_addr; pa < kernel_end_addr; pa += SZ_2M)
    {
        l2_table[L2_IDX(pa)] = pte_block(pa, MT_NORMAL, true);
    }

    return;
}

void init_idmap(void)
{
    build_idmap();

    u64 parange = read_aa64mmfr0_parange();

    enable_mmu(16, parange);

    return;
}
