#include "mos/driver.h"

extern driver_t __drivers_start;
extern driver_t __drivers_end;

static const struct driver_s *registered_drivers[MAX_DRIVERS];
static int driver_count = 0;

const driver_t *find_driver(const char *compatible)
{
    for (int i = 0; i < driver_count; i++)
    {
        if (strcmp(compatible, registered_drivers[i]->compatible) == 0)
        {
            return registered_drivers[i];
        }
    }
    return NULL;
}

void init_all_drivers(void)
{
    for (driver_t *driver = &__drivers_start; driver < &__drivers_end; ++driver)
    {
        if (driver && driver->init)
        {
            driver->init();

            register_new_driver(driver);
        }
    }

    return;
}

void probe_all_drivers_from_fdt(void *fdt)
{
    if (fdt_check_header(fdt) != 0)
    {
        return;
    }

    int node_offset = 0;
    int depth = 0;

    int size_cells = fdt_size_cells(fdt, node_offset);
    int address_cells = fdt_address_cells(fdt, node_offset);

    /* walk through the device tree
     * non-recursive for now */
    while (node_offset >= 0)
    {
        int len;
        const char *compatible = fdt_getprop(fdt, node_offset, "compatible", &len);

        if (compatible)
        {
            const driver_t *driver = find_driver(compatible);

            if (driver)
            {
                device_t device = {
                    .compatible = compatible,
                    .name = fdt_get_name(fdt, node_offset, NULL),
                    .driver = driver,
                    .irq = -1,
                    .reg_base = 0,
                    .reg_size = 0,
                    .data = NULL,
                };

                const fdt32_t *reg = fdt_getprop(fdt, node_offset, "reg", &len);

                if (reg && len > 0)
                {
                    /* we have high 32 bits at location 0 and low 32 bits at location 1 */

                    uint64_t addr = 0;
                    for (int i = 0; i < address_cells; i++)
                    {
                        addr = (addr << 32) | fdt32_to_cpu(reg[i]);
                    }
                    device.reg_base = addr;

                    uint64_t size = 0;
                    for (int i = 0; i < size_cells; i++)
                    {
                        size = (size << 32) | fdt32_to_cpu(reg[address_cells + i]);
                    }
                    device.reg_size = size;
                }

            }
        }
        node_offset = fdt_next_node(fdt, node_offset, &depth);
    }

}

void register_new_driver(const struct driver_s *driver)
{
    if (driver_count < MAX_DRIVERS)
    {
        registered_drivers[driver_count++] = driver;
    }
    return;
}
