#ifndef DW1000_H
#define DW1000_H

#include "dw1000_hw.h"
#include "dw1000_reg.h"

#include <stdint.h>
#include <string.h>

typedef struct
{
    uint8_t rev;
    uint8_t ver;
    uint8_t model;
    uint16_t ridtag;
} dw1000_dev_id_t;

/* =================== GPIO SETTINGS ================ */

int dw1000_set_gpio_mode();

int dw1000_set_ind_leds(void);

/* =================== COMUNICATION CHECK ================ */
dw1000_dev_id_t dw1000_get_dev_id(void);

/**
 * @brief 0 for correct, negative for fake chip
 */
int dw1000_check_dev_id(dw1000_dev_id_t dev_id);


int dw1000_set_leds_high(void);
void dw1000_read_gpio(void);
#endif // DW1000_H