#include "mos/driver.h"
#include "mos/serial.h"

int gicv3_probe(device_t *dev)
{
    return 0;
}


void gicv3_driver_init(device_t *dev)
{
    // enables gic cpu -> gicc_ctlr_b group 0
}

__attribute__((used, section(".drivers")))
driver_t driver = {
    .init = gicv3_driver_init,
    .name = "gic-v3",
    .compatible = "arm,gic-v3",
    .probe = gicv3_probe,
    .type = DRIVER_TYPE_IRQ,
};

