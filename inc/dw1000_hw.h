#ifndef DW1000_HW_H
#define DW1000_HW_H

#include <stdint.h>

#define DEF_UUID {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77}

typedef struct
{
    int (*write)(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size);
    int (*write_read)(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size);
} dw1000_ops_t;

void dw1000_set_hw_spec(dw1000_ops_t *ops);

int dw1000_write(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size);
int dw1000_write_read(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size);


#endif // DW1000_HW_H