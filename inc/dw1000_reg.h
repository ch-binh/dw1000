#ifndef DW1000_REG_H
#define DW1000_REG_H

/*========= DEVICE ID ==========*/
#define REG_DEV_ID 0x00
#define REG_EXT_UUID 0x01

#define REG_PAN_ID_AND_SHORT_ADDR 0x03
/*========= SYSTEM CONFIGURATION ==========*/

#define REG_SYS_CFG 0x04


#define REG_SYS_CTRL 0x0D

/*========= GPIO CONTROL ==========*/
#define REG_GPIO 0x26
#define SREG_GPIO_MODE 0x00
#define SREG_GPIO_DIR 0x08
#define SREG_GPIO_DOUT 0x0C
#define SREG_GPIO_IRQE 0x10
#define SREG_GPIO_ISEN 0x14
#define SREG_GPIO_IMODE 0x18
#define SREG_GPIO_IBES 0x1C
#define SREG_GPIO_ICLR 0x20
#define SREG_GPIO_IDBE 0x24
#define SREG_GPIO_RAW 0x28





#endif