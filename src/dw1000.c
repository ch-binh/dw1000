#include "dw1000.h"

dw1000_dev_t __dw_dev;

/* copy instance */

dw1000_dev_t dw1000_copy_dev_inst(void)
{
    return __dw_dev;
}
/* ###########################################################################
 * ############################### INIT FUNCTIONS ############################
 * ######################################################################### */

void dw1000_new_config()
{
    // idle();
    dw1000_read_dev_pan_id_short_addr(NULL);
    dw1000_read_syscfg(NULL);

    // readChannelControlRegister();
    // readTransmitFrameControlRegister();
    // readSystemEventMaskRegister();
}

/* ###########################################################################
 * ######################### SYSTEM CONFIG AND CONTROL #######################
 * ######################################################################### */
/* ================ BASIC OPERATIONS ========================*/
void dw1000_read_syscfg(uint8_t *result)
{
    uint8_t reg_buf[] = {REG_SYS_CFG};
    uint8_t rx_buf[LEN_SYSCFG + sizeof(reg_buf)];

    dw1000_write_read(reg_buf, sizeof(reg_buf), rx_buf, sizeof(rx_buf));
    dw1000_modify_syscfg((uint8_t *)rx_buf + sizeof(reg_buf)); // skip rx_buf[0] as it is reg dummy data
    result = ((uint8_t *)rx_buf + sizeof(reg_buf));
}

void dw1000_modify_syscfg(uint8_t *bit_mask)
{
    for (int i = 0; i < LEN_SYSCFG; i++)
    {
        __dw_dev.syscfg[i] = bit_mask[i];
    }
}

int dw1000_write_syscfg(void)
{
    uint8_t reg_buf[] = {REG_SYS_CFG};
    dw1000_write_read(reg_buf, sizeof(reg_buf), __dw_dev.syscfg, LEN_SYSCFG);

    return 0;
}

void dw1000_read_syctrl(uint8_t *result)
{
    uint8_t reg_buf[] = {REG_SYS_CTRL};
    uint8_t rx_buf[LEN_SYSCFG + sizeof(reg_buf)];

    dw1000_write_read(reg_buf, sizeof(reg_buf), rx_buf, sizeof(rx_buf));
    dw1000_modify_syscfg(rx_buf + 1); // skip rx_buf[0] as it is reg dummy data
    result = rx_buf + 1;
}

void dw1000_modify_sysctrl(uint8_t *bit_mask)
{
    for (int i = 0; i < LEN_SYSCFG; i++)
    {
        __dw_dev.sysctrl[i] = bit_mask[i];
    }
}

int dw1000_write_sysctrl(void)
{
    uint8_t reg_buf[] = {REG_SYS_CFG};
    dw1000_write_read(reg_buf, sizeof(reg_buf), __dw_dev.sysctrl, REG_SYS_CTRL);

    return 0;
}

/* ---------------------- HANDY FUNCTIONS ---------------------------------*/
int dw1000_cfg_sysctrl_idle(void)
{
    uint8_t bit_mask[4];
    dw1000_read_syctrl(bit_mask);
    bit_mask[0] |= 0x06;
    dw1000_modify_sysctrl(bit_mask);
    dw1000_write_sysctrl();
    return 0;
}

int dw1000_cfg_sysctrl_tx_start(void)
{
    uint8_t bit_mask[4];
    dw1000_read_syctrl(bit_mask);
    bit_mask[0] = 0x01;
    dw1000_modify_sysctrl(bit_mask);
    dw1000_write_sysctrl();
    return 0;
}

/* ###########################################################################
 * ############################## GPIO SETTINGS ##############################
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

    uint8_t reg_buf[] = {REG_GPIO, SREG_GPIO_DOUT};
    const uint8_t reg_size = sizeof(reg_buf);
    const uint8_t data_size = 4 + reg_size;
    uint8_t data_buf[data_size];

    dw1000_write_read(reg_buf, reg_size, data_buf, data_size);
}

/* ###########################################################################
 * ############################## DEVICE INDENTITY ###########################
 * ######################################################################### */

/* ======================= 1. 0x00 DEVICE ID ============================*/

void dw1000_read_dev_id(uint8_t *result)
{
    uint8_t reg_buf[] = {REG_DEV_ID};
    uint8_t data_buf[LEN_DEV_ID + sizeof(reg_buf)];

    dw1000_write_read(reg_buf, sizeof(reg_buf), data_buf, sizeof(data_buf));

    dw1000_set_dev_id((uint8_t *)data_buf + sizeof(reg_buf));
    result = (uint8_t *)data_buf + sizeof(reg_buf);
}

int dw1000_set_dev_id(uint8_t *bit_mask)
{
    if (bit_mask == NULL)
    {
        return -1;
    }
    __dw_dev.id.rev = bit_mask[0] & 0x0F;
    __dw_dev.id.ver = (bit_mask[0] >> 4) & 0x0F;
    __dw_dev.id.model = bit_mask[1];
    __dw_dev.id.ridtag = bit_mask[2] | (bit_mask[3] << 8);
    return 0;
}

// no write dev id
/* ======================= 2. 0x01 DEVICE EXTENDED UUID ============================*/

void dw1000_read_dev_uuid(uint8_t *result)
{
    uint8_t reg_buf[] = {REG_EXT_UUID};
    uint8_t data_buf[LEN_EUUID + sizeof(reg_buf)];

    dw1000_write_read(reg_buf, sizeof(reg_buf), data_buf, sizeof(data_buf));

    dw1000_modify_dev_uuid((uint8_t *)data_buf + sizeof(reg_buf)); // move up one element as buf[0] is dummy data

    if (result == NULL)
    {
        return;
    }
    result = ((uint8_t *)data_buf + sizeof(reg_buf));
}

int dw1000_modify_dev_uuid(uint8_t *bit_mask)
{
    if (bit_mask == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < LEN_EUUID; i++)
    {
        __dw_dev.addr.uuid[i] = bit_mask[i];
    }
    return 0;
}

int dw1000_write_dev_uuid(void)
{
    uint8_t reg[] = {REG_EXT_UUID};

    dw1000_write(reg, sizeof(reg), __dw_dev.addr.uuid, LEN_EUUID);

    return 0;
}

/* ======================= 2. 0x03 PAN ID AND SHORT ADDRESS ============================*/

void dw1000_read_dev_pan_id_short_addr(uint8_t *result)
{
    uint8_t reg_buf[] = {REG_PAN_ID_AND_SHORT_ADDR};
    const uint8_t reg_size = sizeof(reg_buf);
    const uint8_t data_size = 4 + reg_size;
    uint8_t data_buf[data_size];

    dw1000_write_read(reg_buf, reg_size, data_buf, data_size);
    dw1000_modify_pan_id_and_short_addr(data_buf[1] | (data_buf[2] << 8),
                                        data_buf[3] | (data_buf[4] << 8));

    result = (uint8_t *)data_buf + 1;
}

int dw1000_modify_pan_id_and_short_addr(uint16_t pan_id, uint16_t short_addr)
{
    if (pan_id == 0 || short_addr == 0)
    {
        return -1;
    }
    __dw_dev.addr.pan_id = pan_id;
    __dw_dev.addr.short_addr = short_addr;
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
