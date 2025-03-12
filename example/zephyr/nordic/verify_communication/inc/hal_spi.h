#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "main.h"

#define SPIOP SPI_WORD_SET(8) | SPI_TRANSFER_MSB


extern struct spi_dt_spec spispec;

int hal_spi_init(void);

void hal_hw_rfm_init(void);
int hal_spi_write_reg(uint8_t reg, uint8_t value);
int hal_spi_write(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size);
int hal_spi_write_read(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size);

#endif // HAL_SPI_H