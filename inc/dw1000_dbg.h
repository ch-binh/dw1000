#ifndef DW1000_DBG_H
#define DW1000_DBG_H

#include "dw1000.h"

void dw1000_dbg_get_msg_dev_id(char *msg_buf);
void dw1000_dbg_get_msg_dev_uuid(char *msg_buf);
void dw1000_dbg_get_msg_dev_pan_id_short_add(char *msg_buf);

int dw1000_check_dev_id(void);
#endif // DW1000_DEBUG_H