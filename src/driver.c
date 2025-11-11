#include "driver.h"

static const struct driver_s *registered_drivers[MAX_DRIVERS];
static int driver_count = 0;

const driver_t *find_driver(const char *compatible)
{
    for (size_t i = 0; i < driver_count; i++)
    {
        if (strcmp(compatible, registered_drivers[i]->compatible))
        {
            return registered_drivers[i];
        }
    }
    return NULL;
}

void probe_all_drivers_from_fdt(void *fdt)
{
    if (fdt_check_header(fdt) != 0)
    {
        return;
    }

    int node_offset = 0;
    int depth = 0;

    while (node_offset >= 0)
    {
        int len;
        const char *compatible = fdt_getprop(fdt, node_offset, "compatible", &len);

        if (compatible)
        {
            const driver_t *driver = find_driver(compatible);

            if (driver)
            {

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
