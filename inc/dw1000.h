// Write must be called after set, Read automatically Set

#ifndef DW1000_H
#define DW1000_H

#include "dw1000_hw.h"
#include "dw1000_reg.h"
#include "dw1000_const.h"
#include "dw1000_dbg.h"

#include <stdint.h>
#include <string.h>

typedef enum
{
    DW_IDLE_MODE,
    DW_RX_MODE,
    DW_TX_MODE,
} sys_mode_e;

typedef struct
{
    struct
    {
        uint8_t rev;
        uint8_t ver;
        uint8_t model;
        uint16_t ridtag;
    } id;

    struct
    {
        uint8_t uuid[LEN_EUUID];
        uint16_t short_addr;
        uint16_t pan_id;
    } addr;

    uint8_t syscfg[LEN_SYSCFG];
    uint8_t sysctrl[LEN_SYSCTRL]

} dw1000_dev_t;

dw1000_dev_t dw1000_copy_dev_inst(void);

/* ###########################################################################
 * ############################## SYSTEM CONFIGURATION #######################
 * ######################################################################### */
/* ================ BASIC OPERATIONS ========================*/
void dw1000_read_syscfg(uint8_t *result);
void dw1000_modify_syscfg(uint8_t *bit_mask);
int dw1000_write_syscfg(void);

void dw1000_read_syctrl(uint8_t *result);
void dw1000_modify_sysctrl(uint8_t *bit_mask);
int dw1000_write_sysctrl(void);
/* ---------------------- HANDY FUNCTIONS ---------------------------------*/
int dw1000_cfg_sysctrl_idle(void);
int dw1000_cfg_sysctrl_tx_start(void);
/* ###########################################################################
 * ############################## GPIO SETTINGS ##############################
 * ######################################################################### */

int dw1000_set_gpio_mode();

/* ---------------------- HANDY FUNCTIONS ---------------------------------*/
int dw1000_set_ind_leds(void);

int dw1000_set_leds_high(void);
void dw1000_read_gpio(void);

/* ###########################################################################
 * ############################## DEVICE INDENTITY ###########################
 * ######################################################################### */

/* ======================= 1. 0x00 DEVICE ID ============================*/
void dw1000_read_dev_id(uint8_t *result);
int dw1000_set_dev_id(uint8_t *buf);

/* ======================= 2. 0x01 DEVICE EXTENDED UUID ============================*/
void dw1000_read_dev_uuid(uint8_t *result);
int dw1000_modify_dev_uuid(uint8_t *uuid);
int dw1000_write_dev_uuid(void);

/* ======================= 2. 0x03 PAN ID AND SHORT ADDRESS ============================*/
void dw1000_read_dev_pan_id_short_addr(uint8_t *result);
int dw1000_modify_pan_id_and_short_addr(uint16_t pan_id, uint16_t short_addr);
int dw1000_write_pan_id_and_short_addr(void);

#endif // DW1000_H