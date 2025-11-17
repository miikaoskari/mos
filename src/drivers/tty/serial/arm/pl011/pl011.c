#include "driver.h"

int pl011_probe(device_t *dev)
{
    return 0;
}


void pl011_driver_init(void)
{
}

__attribute__((section(".drivers")))
driver_t driver = {
    .init = pl011_driver_init,
    .name = "pl011",
    .compatible = "arm,pl011",
    .probe = pl011_probe,
};
