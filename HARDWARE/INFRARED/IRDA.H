#ifndef __IRDA_H__
#define __IRDA_H__
#include "DataType.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stdlib.h"
#include "delay.h"

#define	IR_DATA PBout(6)

#define PWM_ENABLE  1
#define PWM_DISABLE 0

void IRDA_tx_data(czx_vu32 *d,czx_vu32 len);
void IRDA_INIT(void);
#endif // __IRDA_H__
