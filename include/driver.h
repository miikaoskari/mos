#ifndef DRIVER_H
#define DRIVER_H

#include <libfdt.h>

#define MAX_DRIVERS 64

struct device_s;
struct driver_s;

typedef struct driver_s
{
    void (*init)(void);
    const char *name;
    const char *compatible;

    int (*probe)(struct device_s *dev);
} driver_t;

typedef struct device_s
{
    const char *name;
    const char *compatible;

    uint64_t reg_base;
    uint64_t reg_size;
    int irq;

    void *data;

    const driver_t *driver;
} device_t;

void init_all_drivers(void);
const driver_t *find_driver(const char *compatible);
void probe_all_drivers_from_fdt(void *fdt);
void register_new_driver(const driver_t *driver);


#endif // DRIVER_H
