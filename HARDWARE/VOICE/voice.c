/******************** (C) COPYRIGHT 2015 ���� ********************
 * Ӳ�����ӣ�-----------------
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

  /* ʹ���� I2C1 �йص�ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
    
  /* PB6-I2C1_SCL��PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	       // ��©���
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
 * ��������I2C_Configuration
 * ����  ��I2C ����ģʽ����
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void Send_oneline(unsigned char addr) 
{ 
	int i;
	VOICE_RESET = 0; /* ��оƬ���и�λ  */ 
	delay_ms(5);   /*  ��λ�źű��ֵ͵�ƽ 5ms */ 
	VOICE_RESET = 1; 
	delay_ms(17);  /*  ��λ�źű��ָߵ�ƽ 17ms */ 
	
	VOICE_DATA = 0; 
	delay_ms(5);   /*  �����ź����ڵ͵�ƽ 5ms */ 

	for(i=0;i<8;i++) {
		VOICE_DATA = 1; 
		
		if(addr & 1) {
			delay_us(600);  /*  �ߵ�ƽ�ȵ͵�ƽΪ 600us��200us����ʾ�������� 1 */ 
			VOICE_DATA = 0; 
			delay_us(200);
		}
		else{ 
			delay_us(200);  /*  �ߵ�ƽ�ȵ͵�ƽΪ 200us��600us����ʾ�������� 0 */ 
			VOICE_DATA = 0; 
			delay_us(600);
		} 
		addr >>= 1; 
		VOICE_DATA = 1;
	}
}
/******************** (C) COPYRIGHT 2011 ����Ƕ��ʽ���������� ********************/
