#include <zephyr/kernel.h>
#include <zephyr/drivers/spi.h>

#include "hal_spi.h"

struct spi_dt_spec spispec = SPI_DT_SPEC_GET(DT_NODELABEL(dw1000), SPIOP, 0);

int hal_spi_init(void)
{
    if (!device_is_ready(spispec.bus))
    {
        return -1;
    }
    return 0;
}

int hal_spi_deinit(void)
{
    return 0;
}

int hal_spi_write_reg(uint8_t reg, uint8_t value)
{
    uint8_t tx_buf[] = {(reg | 0x80), value};
    struct spi_buf tx_spi_buf = {.buf = tx_buf, .len = sizeof(tx_buf)};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};

    int err = spi_write_dt(&spispec, &tx_spi_buf_set);
    if (err < 0)
    {
        return err;
    }

    return 0;
}

int hal_spi_write(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size)
{
    uint8_t tx_buf[reg_size + size]; // Buffer for register + data
    
    reg[0] |= 0x80; // write bit

    if (reg_size == 2) // if main reg + 1 sub reg, bit 6 of main reg is 1
    {
        reg[0] |= 0x40;
    }
    else if (reg_size == 3) // if main reg + 2 sub regs, bit 6 of main and bit 7 of sub reg 1 = 1
    {
        reg[0] |= 0x40;
        reg[1] |= 0x80;
    }

    memcpy(tx_buf, reg, reg_size);         // Copy register address first
    memcpy(tx_buf + reg_size, data, size); // Copy data after register

    struct spi_buf tx_spi_buf = {.buf = tx_buf, .len = reg_size + size};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};

    int err = spi_write_dt(&spispec, &tx_spi_buf_set);
    if (err < 0)
    {
        return err;
    }

    return 0;
}

int hal_spi_write_read(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size)
{   
    uint8_t tx_buffer[reg_size];      // Adjust buffer size based on register size
    if (reg_size == 2) // if main reg + 1 sub reg, bit 6 of main reg is 1
    {
        reg[0] |= 0x40;
    }
    else if (reg_size == 3) // if main reg + 2 sub regs, bit 6 of main and bit 7 of sub reg 1 = 1
    {
        reg[0] |= 0x40;
        reg[1] |= 0x80;
    }

    
    memcpy(tx_buffer, reg, reg_size); // Copy multi-byte register address

    struct spi_buf tx_spi_buf = {.buf = (void *)&tx_buffer, .len = reg_size};
    struct spi_buf_set tx_spi_buf_set = {.buffers = &tx_spi_buf, .count = 1};

    struct spi_buf rx_spi_bufs = {.buf = data, .len = size};
    struct spi_buf_set rx_spi_buf_set = {.buffers = &rx_spi_bufs, .count = 1};

    int err = spi_transceive_dt(&spispec, &tx_spi_buf_set, &rx_spi_buf_set);
    if (err < 0)
    {
        return err;
    }

    return 0;
}
