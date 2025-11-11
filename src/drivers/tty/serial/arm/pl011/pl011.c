#include "driver.h"

void pl011_probe()
{

}

driver_t driver = {
    .name = "pl011",
    .compatible = "arm,pl011",
    .probe = pl011_probe
};

void pl011_driver_init(void)
{
    register_new_driver(&pl011_probe);
}
