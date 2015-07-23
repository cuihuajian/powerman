#ifndef __IRDA_H__
#define __IRDA_H__
#include "DataType.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "delay.h"

#define	IR_DATA PBout(6)

typedef		volatile	unsigned	long	czx_vu32;

#define KEY_NUMBS 2
#define KEY_LEN   73
#define POWER_KEY 0

#define PWM_ENABLE  1
#define PWM_DISABLE 0

extern czx_vu32 data2[KEY_NUMBS][KEY_LEN];

void IRDA_tx_data(czx_vu32 *d,czx_vu32 len);
void IRDA_INIT(void);
#endif // __IRDA_H__
