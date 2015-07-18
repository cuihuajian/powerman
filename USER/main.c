#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//系统中断分组设置化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/10
//版本：V1.4#include "oled.h"
#include "i2c_ee.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h" 
#include "adc.h"
#include "pwm.h"
#include "voice.h"
#include "oled.h"

//设置USB 连接/断线
//enable:0,断开
//       1,允许连接
extern u16 volatile  AD_Value[N][M]; //用来存放ADC转换结果，也是DMA的目标地址
extern u16 volatile After_filter[M]; //用来存放求平均值之后的结果

void usb_port_set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;	    		  
	}
}  	 

 int main(void)
 {	
	unsigned long temp;
	u16  value[M], i, j, n;
	 
	Stm32_Clock_Init(9); //系统时钟设置
	 
	delay_init();	    	 //延时函数初始化	
    //NVIC_Configuration();//中断分组设置	 
	//uart_init(9600);	 	//串口初始化为9600
	//delay_ms(1800);

	OLED_Init();			//初始化液晶 
	
	 for (j =0; j< 8; j++) {
		OLED_WR_Byte(0xb0+j, OLED_CMD);
		OLED_WR_Byte(0x00, OLED_CMD);
        OLED_WR_Byte(0x10, OLED_CMD);			
		
		for (n = 0; n < 128; n++) {
	    	OLED_WR_Byte(0xff, OLED_DATA);			
		}
	}
	I2C_EE_Init();//温度传感器
	VOICE_Init();
	
 	usb_port_set(0); 	//USB先断开
	delay_ms(300);
   	usb_port_set(1);	//USB再次连接
	
	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();
	USB_Report_init();
	 
    Adc_Init();		   //ADC初始化	 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	DMA_Cmd(DMA1_Channel1, ENABLE);

	while(1)
	{
		delay_ms(1000);
		
		temp = Htu21D_read();
		temp=((long)17572)*temp;
	    temp=temp/((long)65536);
		temp =temp-((long)4685);
		
		USB_Report();
		//printf("\ntemp: %d.%d°c \n", (int)temp/100, (int)temp%100);

		filter();
		for(i=0;i<M;i++) {
			value[i]= GetVolt(After_filter[i]);
			printf("value[%d]:%d.%dv\n",i,(int)value[i]/100,(int)value[i]%100) ;
		delay_ms(100);
		}
		
		//OLED_ShowString(0,52,"hello:",12);  
	}
 }

