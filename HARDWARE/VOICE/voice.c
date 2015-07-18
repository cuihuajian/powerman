/******************** (C) COPYRIGHT 2015 崔鹏 ********************
 * 硬件连接：-----------------
 *          |                 |
 *          |  PB10-I2C2_SCL		|
 *          |  PB11-I2C2_SDA   |
 *          |                 |
 *           -----------------
**********************************************************************************/
#include "stdlib.h"	 
#include "delay.h"
#include "voice.h"

static void VOICE_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

  /* 使能与 I2C1 有关的时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
    
  /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // 开漏输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9);
}

static void VOICE_Mode_Configu(void)
{
  Send_oneline(0xE7);
}

void VOICE_Init(void)
{

  VOICE_GPIO_Config(); 
 
  VOICE_Mode_Configu();
}

/*
 * 函数名：I2C_Configuration
 * 描述  ：I2C 工作模式配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
void Send_oneline(unsigned char addr) 
{ 
	int i;
	VOICE_RESET = 0; /* 对芯片进行复位  */ 
	delay_ms(5);   /*  复位信号保持低电平 5ms */ 
	VOICE_RESET = 1; 
	delay_ms(17);  /*  复位信号保持高电平 17ms */ 
	
	VOICE_DATA = 0; 
	delay_ms(5);   /*  数据信号置于低电平 5ms */ 

	for(i=0;i<8;i++) {
		VOICE_DATA = 1; 
		
		if(addr & 1) {
			delay_us(600);  /*  高电平比低电平为 600us：200us，表示发送数据 1 */ 
			VOICE_DATA = 0; 
			delay_us(200);
		}
		else{ 
			delay_us(200);  /*  高电平比低电平为 200us：600us，表示发送数据 0 */ 
			VOICE_DATA = 0; 
			delay_us(600);
		} 
		addr >>= 1; 
		VOICE_DATA = 1;
	}
}
/******************** (C) COPYRIGHT 2011 迷你嵌入式开发工作室 ********************/
