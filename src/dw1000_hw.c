#include "dw1000.h"

static dw1000_ops_t hw_ops;

void dw1000_set_hw_spec(dw1000_ops_t *ops)
{
    hw_ops = *ops; // Copy the function pointers
}

int dw1000_write(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size)
{
    if (hw_ops.write)
    {
        hw_ops.write(reg,reg_size, data, size);
        return 0;
    }
    return -1; // Error: function not set
}

int dw1000_write_read(uint8_t *reg, uint8_t reg_size, uint8_t *data, uint8_t size)
{
    if (hw_ops.write_read)
    {
        return hw_ops.write_read(reg, reg_size, data, size);
    }
    return -1; // Error: function not set
}

