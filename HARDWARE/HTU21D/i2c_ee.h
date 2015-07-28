#ifndef __I2C_EE_H
#define	__I2C_EE_H
#include "sys.h"
#include "stm32f10x.h"
#include "stdlib.h"	  

#define HTU21ADDR 0x80
#define HTU21_RD_TEMP 0xe3
#define HTU21_RD_HUMI 0xe5

void I2C_EE_Init(void);
u16 Htu21D_read(u8 cmd);

#endif /* __I2C_EE_H */
