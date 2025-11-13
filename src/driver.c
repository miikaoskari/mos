#include "driver.h"
#include "pl011.h"

static const struct driver_s *registered_drivers[MAX_DRIVERS];
static int driver_count = 0;

const driver_t *find_driver(const char *compatible)
{
    for (size_t i = 0; i < driver_count; i++)
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
    pl011_driver_init();
}

void probe_all_drivers_from_fdt(void *fdt)
{
    if (fdt_check_header(fdt) != 0)
    {
        return;
    }

    int node_offset = 0;
    int depth = 0;

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
                    .name = fdt_get_name(fdt, node_offset, NULL),
                    .compatible = compatible,
                    .driver = driver
                };

                const fdt32_t *reg = fdt_getprop(fdt, node_offset, "reg", &len);


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
