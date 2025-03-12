#include "dw1000.h"

/* =================== GPIO SETTINGS ================ */

int dw1000_set_gpio_mode() {}

int dw1000_set_ind_leds(void)
{
    const uint8_t reg_size = 2, data_size = 4;
    uint8_t reg[reg_size];
    uint8_t data[data_size];
    reg[0] = REG_GPIO;

    /* Set GPIO Mode */
    reg[1] = SREG_GPIO_MODE;
    // Enable led indicators GPIO 0,1,2,3,
    uint8_t mode_data[4] = {0x40, 0x15, 0x00, 0x00};
    memcpy(data, mode_data, data_size);
    // dw1000_write(reg, reg_size, data, data_size);

    /* Set GPIO Direction */
    reg[1] = SREG_GPIO_DIR;
    // Turn off write protect, Set GPIOs to be OUTPUT
    uint8_t dir_data[4] = {0xF0, 0x00, 0x00, 0x00};
    memcpy(data, dir_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

    /* Set GPIO Direction */
    reg[1] = SREG_GPIO_DOUT;
    //
    uint8_t dout_data[4] = {0xFF, 0x00, 0x00, 0x00};
    memcpy(data, dout_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

    return 0;
}

/* =================== COMUNICATION CHECK ================ */

dw1000_dev_id_t dw1000_get_dev_id(void)
{
    dw1000_dev_id_t dev_id;
    const uint8_t data_size = 5;
    uint8_t data_buffer[data_size];
    const uint8_t reg_size = 1;
    uint8_t reg_buffer[reg_size];
    reg_buffer[0] = REG_DEV_ID;

    dw1000_write_read(reg_buffer, reg_size, data_buffer, data_size);
    dev_id.rev = data_buffer[1] & 0x0F;
    dev_id.ver = (data_buffer[1] >> 4) & 0x0F;
    dev_id.model = data_buffer[2];
    dev_id.ridtag = data_buffer[3] | (data_buffer[4] << 8);

    return dev_id;
}

int dw1000_check_dev_id(dw1000_dev_id_t dev_id)
{
    if (dev_id.rev != DEF_DEV_ID_REV)
        return -1;
    if (dev_id.ver != DEF_DEV_ID_VER)
        return -1;
    if (dev_id.model != DEF_DEV_ID_MODEL)
        return -1;
    if (dev_id.ridtag != DEF_DEV_ID_RIDTAG)
        return -1;
    return 0;
}

int dw1000_set_leds_high(void)
{
    const uint8_t reg_size = 2, data_size = 4;
    uint8_t reg[reg_size];
    uint8_t data[data_size];
    reg[0] = REG_GPIO;

    /* Set GPIO Direction */
    reg[1] = SREG_GPIO_DIR;
    // Turn off write protect, Set GPIOs to be OUTPUT
    uint8_t dir_data[4] = {0xF0, 0x00, 0x00, 0x00};
    memcpy(data, dir_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

    /* Set GPIO Direction */
    reg[1] = SREG_GPIO_DOUT;
    // Turn of write protect, Set GPIOs to be HIGH
    uint8_t dout_data[4] = {0xFF, 0x00, 0x00, 0x00};
    memcpy(data, dout_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

    return 0;
}

void dw1000_read_gpio(void)
{
    
    uint8_t reg_buffer[] = {REG_GPIO, SREG_GPIO_DOUT};
    const uint8_t reg_size = sizeof(reg_buffer);
    const uint8_t data_size =  4 +  reg_size;
    uint8_t data_buffer[data_size];

    dw1000_write_read(reg_buffer, reg_size, data_buffer, data_size);
}