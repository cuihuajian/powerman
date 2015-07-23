#include "IRDA.H"
#include "usart.h"
void TIM2_IRQHandler(void);
#define KEY_NUMBS 2
#define POWER_KEY 0
czx_vu32 data2[KEY_NUMBS][73]=
{
	{4500, 4420, 580, 520, 600, 1640, 600, 1660, 580, 
	 1660, 580, 540, 580, 540, 560, 560, 600, 540, 580, 
	 540, 560, 1680, 560, 1680, 560, 1680, 600, 520, 580, 
	 560, 560, 560, 560, 560, 620, 500, 620, 520, 600, 
	 1640, 560, 1680, 620, 500, 620, 500, 620, 500, 620, 
	 520, 620, 1620, 620, 1620, 560, 560, 580, 560, 600, 
	 1640, 560, 1680, 560, 1680, 560, 1680, 560, 46300, 
	 4500, 4400, 640, 1620, 600},
	
	 {4520, 4400, 560, 540, 620, 1620, 580, 1660, 580, 
	1680, 560, 560, 620, 500, 580, 560, 560, 560, 560, 
	560, 620, 1640, 560, 1660, 580, 1660, 580, 560, 560, 
	560, 620, 500, 580, 540, 620, 1620, 620, 1620, 620, 
	1620, 580, 1660, 620, 520, 560, 560, 580, 540, 580, 
	560, 560, 560, 620, 500, 620, 520, 560, 560, 560, 
	1680, 620, 1620, 560, 1680, 620, 1620, 580, 46260, 
	4540, 4380, 560, 1680, 560},
	
};

czx_vu32	irda_delay_10us	=	FALSE;

void IRDA_GPIO_MODE_CHANGE(u32 mode) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
    
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = mode ? GPIO_Mode_AF_PP : GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	
	if(!mode) GPIO_ResetBits(GPIOB,GPIO_Pin_6);
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
	//IRDA_GPIO_INIT();
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
	for (i = 0;i < len; i++) {
		if ( i%2 ) {
			TIM_Cmd(TIM4, DISABLE);
			IRDA_GPIO_MODE_CHANGE(PWM_DISABLE);	
		}
		else {
			IRDA_GPIO_MODE_CHANGE(PWM_ENABLE);
			TIM_Cmd(TIM4, ENABLE);			
		}
		IRDA_delay_10us(d[i]/10);
	}
	TIM_Cmd(TIM4, DISABLE);
	IRDA_GPIO_MODE_CHANGE(PWM_DISABLE);
}
