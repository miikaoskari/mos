#ifndef DRIVER_H
#define DRIVER_H

#include <libfdt.h>

#define MAX_DRIVERS 64

struct device_s;
struct driver_s;

typedef struct driver_s
{
    const char *name;
    const char *compatible;

    int (*probe)(struct device_s *dev);
} driver_t;

typedef struct device_s
{
    /* data */
} device_t;


const driver_t *find_driver(const char *compatible);
void probe_all_drivers();
void probe_all_drivers_from_fdt(void *fdt);
void register_new_driver();


#endif // DRIVER_H
