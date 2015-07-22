#include "IRDA.H"
#include "usart.h"
void TIM2_IRQHandler(void);

czx_vu32 data2[73]=
{
	4520, 4400, 560, 540, 620, 1620, 580, 1660, 580, 
	1680, 560, 560, 620, 500, 580, 560, 560, 560, 560, 
	560, 620, 1640, 560, 1660, 580, 1660, 580, 560, 560, 
	560, 620, 500, 580, 540, 620, 1620, 620, 1620, 620, 
	1620, 580, 1660, 620, 520, 560, 560, 580, 540, 580, 
	560, 560, 560, 620, 500, 620, 520, 560, 560, 560, 
	1680, 620, 1620, 560, 1680, 620, 1620, 580, 46260, 
	4540, 4380, 560, 1680, 560
};

czx_vu32	irda_delay_10us	=	FALSE;

void IRDA_GPIO_INIT(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
      
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB,GPIO_Pin_6);
}

void   TIME_INIT(void){//10us中断
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
	TIM_TimeBaseStructure.TIM_Period = 179;
	TIM_TimeBaseStructure.TIM_Prescaler = 3;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	//启动此通道的中断
	NVIC_Init(&NVIC_InitStructure);
  
	TIM_Cmd(TIM2,ENABLE);
}

void IRDA_INIT(void)
{
	IRDA_GPIO_INIT();
	TIME_INIT();
}

void TIM2_IRQHandler(void)
{   
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
	  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	  if(irda_delay_10us)irda_delay_10us--;
  }
}

void IRDA_delay_10us(czx_vu32 t){//延时10us
	irda_delay_10us	=	t;
	while(irda_delay_10us);
}

void IRDA_tx_data(czx_vu32 *d,czx_vu32 len)
{
	czx_vu32 i = 0;
	
	IR_DATA = 1;
	delay_ms(1);
	for(i=0;i<len;i++) {
		IR_DATA = !IR_DATA;
		IRDA_delay_10us(d[i]/10);
	}
	IR_DATA = 1;
}
