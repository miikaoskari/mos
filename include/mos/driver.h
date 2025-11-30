#ifndef DRIVER_H
#define DRIVER_H

#include <libfdt.h>

#define MAX_DRIVERS 64

struct device_s;
struct driver_s;

typedef enum device_type_enum {
    DRIVER_TYPE_SERIAL,
    DRIVER_TYPE_IRQ,
    DRIVER_TYPE_BLOCK,
} device_type_t;

typedef struct driver_s
{
    void (*init)(struct device_s *dev);
    const char *name;
    const char *compatible;

    int (*probe)(struct device_s *dev);

    device_type_t type;
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

void register_all_drivers(void);
const driver_t *find_driver(const char *compatible);
void probe_all_drivers_from_fdt(void *fdt);
void register_new_driver(const driver_t *driver);


#endif // DRIVER_H
