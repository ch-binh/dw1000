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

    struct
    {
        sys_mode_e mode;
        uint8_t en_sfcst;
        uint8_t tx_delay; 
        uint8_t wait_for_res;

    } sysctrl;

} dw1000_dev_t;

dw1000_dev_t dw1000_copy_dev_inst(void);

/* ###########################################################################
 * ############################## SYSTEM CONFIGURATION #######################
 * ######################################################################### */
/* ======================= 1. SET ============================*/

int dw1000_set_sys_ctrl(sys_mode_e mode);


/* =================== GPIO SETTINGS ================ */

int dw1000_set_gpio_mode();

int dw1000_set_ind_leds(void);

/* ###########################################################################
 * ############################## DEVICE INDENTITY ###########################
 * ######################################################################### */
/* 1. SET*/
int dw1000_set_dev_id(uint8_t *buf);
int dw1000_set_dev_uuid(uint8_t *uuid);
int dw1000_set_pan_id_and_short_addr(uint16_t pan_id, uint16_t short_addr);
/* 2. WRITE AND READ*/

int dw1000_read_dev_id(void);

int dw1000_write_dev_uuid(void);
int dw1000_read_dev_uuid(void);

int dw1000_read_dev_pan_id_short_addr(void);
int dw1000_write_pan_id_and_short_addr(void);

int dw1000_set_leds_high(void);
void dw1000_read_gpio(void);

#endif // DW1000_H