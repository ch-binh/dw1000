#include "dw1000_dbg.h"

#include <string.h>
#include <stdio.h>

extern dw1000_dev_t __dw_dev;
/* ###########################################################################
 * #### Pretty printed device information ####################################
 * ######################################################################### */

void dw1000_dbg_get_msg_dev_id(char *msg_buf)
{
    dw1000_read_dev_id();
    sprintf(msg_buf, "Device ID: Rev: 0x%02X - Ver: 0x%02X - Model: 0x%02X - RIDTAG: 0x%04X\n",
            __dw_dev.id.rev, __dw_dev.id.ver, __dw_dev.id.model, __dw_dev.id.ridtag);
}

void dw1000_dbg_get_msg_dev_uuid(char *msg_buf)
{
    dw1000_read_dev_uuid();
    sprintf(msg_buf, "UUID: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
            __dw_dev.addr.uuid[7], __dw_dev.addr.uuid[6], 
            __dw_dev.addr.uuid[5], __dw_dev.addr.uuid[4],
            __dw_dev.addr.uuid[3], __dw_dev.addr.uuid[2], 
            __dw_dev.addr.uuid[1], __dw_dev.addr.uuid[0]);
}

void dw1000_dbg_get_msg_dev_pan_id_short_add(char *msg_buf)
{
    dw1000_read_dev_pan_id_short_addr();
    sprintf(msg_buf, "Pan ID: 0x%04X - Short Address: 0x%04X\n",
            __dw_dev.addr.pan_id, __dw_dev.addr.short_addr);
}

/* ###########################################################################
 * #### DEBUG TEST CASE ... ##################################################
 * ######################################################################### */

int dw1000_check_dev_id(void)
{
    if (__dw_dev.id.rev != DEF_DEV_ID_REV)
        return -1;
    if (__dw_dev.id.ver != DEF_DEV_ID_VER)
        return -1;
    if (__dw_dev.id.model != DEF_DEV_ID_MODEL)
        return -1;
    if (__dw_dev.id.ridtag != DEF_DEV_ID_RIDTAG)
        return -1;
    return 0;
}
