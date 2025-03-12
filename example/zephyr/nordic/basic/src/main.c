/* Zephyr lib */
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
/* Application specific submodules */
#include "main.h"
#include "hal_spi.h"

/* Application common lib */

/* Sensor driver lib */
#include "dw1000.h"

extern struct spi_dt_spec spispec;

void hal_hw_dw1000_init(void)
{
	dw1000_ops_t ops = {
		.write = hal_spi_write,
		.write_read = hal_spi_write_read};
	dw1000_set_hw_spec(&ops);
}

int main(void)
{
	printk("[%s] Initializing...\n", __func__);

	hal_spi_init();
	hal_hw_dw1000_init();

	k_sleep(K_SECONDS(1)); // wait for dw1000 to start up

	dw1000_dev_id_t dev_id;
	dev_id = dw1000_read_dev_id();
	printk("device ID: %d-%d-%d-%d\n",
		   dev_id.rev, dev_id.ver, dev_id.model, dev_id.ridtag);
	if (dw1000_check_dev_id(dev_id) < 0)
	{
		printk("Wrong device ID\n");
	}
	dw1000_set_ind_leds();
	
	while (1)
	{
		k_sleep(K_FOREVER);
	}

	return 0;
}
