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

static int main_setup(void)
{
	printk("[%s] Initializing...\n", __func__);
	hal_spi_init();
	hal_hw_dw1000_init();

	dw1000_modify_pan_id_and_short_addr(DW_NETWORK_ID, DW_SHORT_ADDR);
	dw1000_write_pan_id_and_short_addr();

	printk("[%s] Setup complete...\n", __func__);
}

int main(void)
{
	main_setup();

	char msg[128];
	dw1000_dbg_get_msg_dev_id(msg);
	printk("%s", msg);
	dw1000_dbg_get_msg_dev_uuid(msg);
	printk("%s", msg);
	dw1000_dbg_get_msg_dev_pan_id_short_add(msg);
	printk("%s", msg);

	if (dw1000_check_dev_id() < 0)
	{
		printk("Wrong device ID\n");
	}
	else
	{
		printk("Correct device ID\n");
	}

	dw1000_set_leds_high();
	// GPIOS 0 1 2 3 should be high

	//dw1000_cfg_sysctrl_tx_start();

	while (1)
	{
		k_sleep(K_FOREVER);
	}

	return 0;
}
