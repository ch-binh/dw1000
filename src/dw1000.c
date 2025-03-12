#include "dw1000.h"

dw1000_dev_t __dw_dev;

/* copy instance */

dw1000_dev_t dw1000_copy_dev_inst(void)
{
    return __dw_dev;
}

/* ###########################################################################
 * ############################## SYSTEM CONFIGURATION #######################
 * ######################################################################### */
/* ======================= 1. SET ============================*/

int dw1000_set_sys_ctrl(sys_mode_e mode)
{
    if (mode < DW_IDLE_MODE || mode > DW_TX_MODE)
        return -1; // Error: Invalid mode

    __dw_dev.sysctrl.mode = mode;
    return 0;
}

/* ================ 2. WRITE AND READ ========================*/
int dw1000_cfg_sys_idle(void)
{
    uint8_t tx_buf[4] = {0x00, 0x00, 0x00, 0x00};
    dw1000_write(REG_SYS_CFG, 1, tx_buf, sizeof(tx_buf));
    return 0;
}

/* ###########################################################################
 * ############################## GPIO INDENTITY #############################
 * ######################################################################### */

int dw1000_set_gpio_mode() {}

int dw1000_set_ind_leds(void)
{
    const uint8_t reg_size = 2, data_size = 4;
    uint8_t reg[reg_size];
    uint8_t data[data_size];
    reg[0] = REG_GPIO;

    /* Set GPIO Mode */
    reg[1] = SREG_GPIO_MODE;
    // Enable led indicators GPIO 0,1,2,3 as RXOK, SFD, RX, TX
    uint8_t mode_data[4] = {0x40, 0x15, 0x00, 0x00};
    memcpy(data, mode_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

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

int dw1000_set_leds_high(void)
{
    const uint8_t reg_size = 2, data_size = 4;
    uint8_t reg[reg_size];
    uint8_t data[data_size];
    reg[0] = REG_GPIO;

    /* Set GPIO Direction */
    reg[1] = SREG_GPIO_DIR;
    // Turn off write protect, Set GPIOs to be OUTPUT
    uint8_t dir_data[] = {0xF0, 0x00, 0x00, 0x00};
    memcpy(data, dir_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

    /* Set GPIO Direction */
    reg[1] = SREG_GPIO_DOUT;
    // Turn of write protect, Set GPIOs to be HIGH
    uint8_t dout_data[] = {0xFF, 0x00, 0x00, 0x00};
    memcpy(data, dout_data, data_size);
    dw1000_write(reg, reg_size, data, data_size);

    return 0;
}

void dw1000_read_gpio(void)
{

    uint8_t reg_buffer[] = {REG_GPIO, SREG_GPIO_DOUT};
    const uint8_t reg_size = sizeof(reg_buffer);
    const uint8_t data_size = 4 + reg_size;
    uint8_t data_buf[data_size];

    dw1000_write_read(reg_buffer, reg_size, data_buf, data_size);
}

/* ###########################################################################
 * ############################## DEVICE INDENTITY ###########################
 * ######################################################################### */

/* ======================= 1. SET ============================*/
int dw1000_set_dev_id(uint8_t *buf)
{
    if (buf == NULL)
    {
        return -1;
    }
    __dw_dev.id.rev = buf[0] & 0x0F;
    __dw_dev.id.ver = (buf[0] >> 4) & 0x0F;
    __dw_dev.id.model = buf[1];
    __dw_dev.id.ridtag = buf[2] | (buf[3] << 8);
    return 0;
}

int dw1000_set_dev_uuid(uint8_t *uuid)
{
    if (uuid == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < LEN_EUUID; i++)
    {
        __dw_dev.addr.uuid[i] = uuid[i];
    }
    return 0;
}

int dw1000_set_pan_id_and_short_addr(uint16_t pan_id, uint16_t short_addr)
{
    if (pan_id == 0 || short_addr == 0)
    {
        return -1;
    }
    __dw_dev.addr.pan_id = pan_id;
    __dw_dev.addr.short_addr = short_addr;
    return 0;
}

/* =================== 2. WRITE AND READ*/
int dw1000_read_dev_id()
{
    const uint8_t data_size = 5;
    uint8_t data_buf[data_size];
    const uint8_t reg_size = 1;
    uint8_t reg_buffer[reg_size];
    reg_buffer[0] = REG_DEV_ID;

    dw1000_write_read(reg_buffer, reg_size, data_buf, data_size);

    uint8_t *set_buf = (uint8_t *)data_buf + 1; // move up one element as buf[0] is dummy data
    dw1000_set_dev_id(set_buf);

    return 0;
}

int dw1000_write_dev_uuid(void)
{
    uint8_t reg[] = {REG_EXT_UUID};

    dw1000_write(reg, sizeof(reg), __dw_dev.addr.uuid, LEN_EUUID);

    return 0;
}

int dw1000_read_dev_uuid(void)
{
    uint8_t reg_buffer[] = {REG_EXT_UUID};
    const uint8_t reg_size = sizeof(reg_buffer);
    const uint8_t data_size = LEN_EUUID + reg_size;
    uint8_t data_buf[data_size];

    dw1000_write_read(reg_buffer, reg_size, data_buf, data_size);

    uint8_t *set_buf = (uint8_t *)data_buf + 1; // move up one element as buf[0] is dummy data
    dw1000_set_dev_uuid(set_buf);

    return 0;
}

int dw1000_write_pan_id_and_short_addr(void)
{
    uint8_t reg[] = {REG_PAN_ID_AND_SHORT_ADDR};
    uint8_t data[] = {(__dw_dev.addr.short_addr) & 0xFF,
                      (__dw_dev.addr.short_addr >> 8) & 0xFF,
                      (__dw_dev.addr.pan_id) & 0xFF,
                      (__dw_dev.addr.pan_id >> 8) & 0xFF};

    /* Store settings */
    dw1000_write(reg, sizeof(reg), data, sizeof(data));

    return 0;
}

int dw1000_read_dev_pan_id_short_addr(void)
{
    uint8_t reg_buffer[] = {REG_PAN_ID_AND_SHORT_ADDR};
    const uint8_t reg_size = sizeof(reg_buffer);
    const uint8_t data_size = 4 + reg_size;
    uint8_t data_buf[data_size];

    dw1000_write_read(reg_buffer, reg_size, data_buf, data_size);

    dw1000_set_pan_id_and_short_addr(data_buf[1] | (data_buf[2] << 8),
                                     data_buf[3] | (data_buf[4] << 8));

    return 0;
}
