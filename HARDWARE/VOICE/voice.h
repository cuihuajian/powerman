#ifndef __VOICE_H
#define	__VOICE_H

#include "stm32f10x.h"
#include "sys.h"
#include "stdlib.h"	

#define VOICE_RESET PAout(8)
#define VOICE_DATA PAout(9)
#define VOICE_BUSY PAout(10)

void VOICE_Init(void);
void Send_oneline(unsigned char addr);

#endif /* __VOICE_H */
