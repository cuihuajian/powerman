#ifndef __I2C_EE_H
#define	__I2C_EE_H
#include "sys.h"
#include "stm32f10x.h"
#include "stdlib.h"	  

#define HTU21ADDR 0x80

void I2C_EE_Init(void);
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);
void I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr);
void I2C_EE_PageWrite(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite);
u16 Htu21D_read(void);
void I2C_EE_WaitEepromStandbyState(void);

#endif /* __I2C_EE_H */
