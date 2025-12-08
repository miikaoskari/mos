#include "mos/driver.h"

int pl011_probe(device_t* dev)
{
    return 0;
}

void pl011_driver_init(device_t* dev)
{
    return;
}

ASSING_DRIVER driver_t pl011_driver = {
    .init = pl011_driver_init,
    .name = "pl011",
    .compatible = "arm,pl011",
    .probe = pl011_probe,
    .type = DRIVER_TYPE_SERIAL,
};
