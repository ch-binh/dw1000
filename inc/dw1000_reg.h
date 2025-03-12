#ifndef DW1000_REG_H
#define DW1000_REG_H

#define REG_DEV_ID 0x00
#define REG_EXT_UUID 0x01


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


/*========= DEFAULT VALUES ==========*/
#define DEF_DEV_ID_REV 0x00
#define DEF_DEV_ID_VER 0x03
#define DEF_DEV_ID_MODEL 0x01
#define DEF_DEV_ID_RIDTAG 0xDECA


#endif