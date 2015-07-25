#ifndef __I2C_EE_H
#define	__I2C_EE_H
#include "sys.h"
#include "stm32f10x.h"
#include "stdlib.h"	  

#define HTU21ADDR 0x80

void I2C_EE_Init(void);
u16 Htu21D_read(void);

#endif /* __I2C_EE_H */
