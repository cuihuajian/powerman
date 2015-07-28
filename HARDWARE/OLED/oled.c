#include "oled.h"
#include "stdlib.h"
#include "FONT.H"  	 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//SSD1306 OLED 驱动IC驱动代码
//驱动方式:8080并口/4线串口
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
	
//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	OLED_RS=cmd; //写命令 	  
	for(i=0;i<8;i++)
	{		  
		OLED_SCLK=0;
		if(dat&0x80)OLED_SDIN=1;
		else OLED_SDIN=0;
		OLED_SCLK=1;
		dat<<=1; 
	}	 	  
	OLED_RS=1;   	
}

u32 Pow(u32 num,uchar count)
{
	uchar i;
	u32 result = 0;
	if(count == 0)
	{
		num = 1;
		return num;
	}
	else
	{
		result = num;
		for(i = 0;i<count-1;i++)
		{
			result *= num;	
		}
	}
	return result;
}

#define NUM_TO_CHAR	0x30

void NumToString(u32 num,uchar numbit,uchar *string)
{
	uchar i=0,z=0;
	u32 temp = 0;
	uchar changestart = 0;
	uchar j = numbit-1;

	for(i = 0;i<numbit;i++)
	{
		temp = num/Pow(10,j);

		if(changestart)
		{
			string[z++] = temp+NUM_TO_CHAR;
		}
		if((temp>0)&&(changestart == 0))
		{
			string[z++] = temp+NUM_TO_CHAR;	
			changestart = 1;
		}

		temp = Pow(10,j);
		num %= temp;
		j--;
	}
	string[z] = 0;
}

void DisplayChar_16X08(uchar x,uchar y,uchar *dispdata)
{
	uchar i,j,fontposition,addyl,addyh;
	uchar *databuf;

	while((*dispdata)!=0)
	{
//		if((y>127)||(x>7))	 break;						//判断字符显示的位置是否超出范围
			
		/*获取字符在字库中的位置*/
		fontposition=*dispdata-0x20;					//计算字符在字库中的位置
		databuf=(uchar *)(ASCII_1608+fontposition);
		
		/*计算当前字符显示的起始列地址*/
		addyl=y%16;										//计算列低地址
		addyh=y/16+0x10;								//计算列高地址

		/*显示字符*/		
		for(i=0;i<2;i++)
		{
			OLED_WR_Byte(0xb0+x+i,OLED_CMD);			//设置页地址
			OLED_WR_Byte(addyl,OLED_CMD);				//设置列低地址
			OLED_WR_Byte(addyh,OLED_CMD);				//设置列高地址

			for(j=0;j<8;j++)
			{
				OLED_WR_Byte(*(databuf++),OLED_DATA);	
			}  			
		}

		y+=8;											//列地址自加6
		dispdata++;
	}		
}

/*****************************************************
** 函数名称：DisplayFont_16X16
** 函数功能：显示16*16点阵（本例程主要用来显示已经取模的汉字点阵）
** 参    数：1.x: 字符串显示的起始页地址
			 2.y：字符串显示的起始列地址
			 3.len：点阵数据长度
			 4.*dispdata：指向需要显示的点阵数据指针
** 函数返回：无
** 编写作者：326电子工作室
** 编写时间：2015年5月19日
** 网    址：  ttsemb.taobao.com
** 技术支持群：QQ427165833
******************************************************/
void DisplayFont_16X16(uchar x,uchar y,uint len,uchar *dispdata)
{
	uchar i,j,z,count,addyl,addyh;	

 	count=len/32;

	for(z=0;z<count;z++)
	{
		/*计算当前点阵显示的起始列地址*/
		addyl=y%16;										//计算列低地址
		addyh=y/16+0x10;

		/*显示16*16点阵数据*/
		for(i=0;i<2;i++)
		{
			OLED_WR_Byte(0xb0+x+i,OLED_CMD);			//设置页地址
			OLED_WR_Byte(addyl,OLED_CMD);				//设置列低地址
			OLED_WR_Byte(addyh,OLED_CMD);				//设置列高地址
			for(j=0;j<16;j++)
			{
				OLED_WR_Byte(*(dispdata++),OLED_DATA);	
			}
		}	
		y+=16;		
	}	
}

void OledClearn(void)
{
	uchar i,j;

	for(i=0;i<8;i++)
	{
		OLED_WR_Byte(0xb0+i,OLED_CMD);				//设置页地址
		OLED_WR_Byte(0x00,OLED_CMD);				//设置列低地址
		OLED_WR_Byte(0x10,OLED_CMD);				//设置列高地址

		for(j=0;j<128;j++)
		{
			OLED_WR_Byte(0x00,OLED_DATA);
		}

	}
}

//初始化SSD1306					    
void OLED_Init(void)
{ 	 				 	 					    
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟 

	GPIOB->CRH &= 0X000FFFFF;		//设置PB12/PB13 为通用推免输出
	GPIOB->CRH |= 0X33300000;
	GPIOB->ODR |= 0XE000;				//置1 PB12/PB13 
								  
	//OLED_RST=0;
	delay_ms(1000);
	//OLED_RST=1; 
	/*关闭OLED显示*/
	OLED_WR_Byte(SET_DISPLAY_OFF,OLED_CMD);
	
	/*设置正当频率、时钟分频因子*/
    OLED_WR_Byte(SET_DISPLAY_CLOCK,OLED_CMD);
    OLED_WR_Byte(0x80,OLED_CMD);
		
	/*设置驱动路数*/
	OLED_WR_Byte(SET_MULTIPLEX_RATIO,OLED_CMD);			  //驱动路数设置命令
	OLED_WR_Byte(0x1F,OLED_CMD);							  //驱动路数值(1/32)

	/*设置行显示偏移*/
	OLED_WR_Byte(SET_DISPLAY_OFFSET,OLED_CMD);				  //显示偏移设置命令
	OLED_WR_Byte(0x00,OLED_CMD);							  //取值范围：0x00-->0x3F

	/*设置显示起始行*/
	OLED_WR_Byte(0x40,OLED_CMD);							  //取值范围：0x40---0x7F
	
	/*设置电荷泵*/
	OLED_WR_Byte(CHARGE_PUMP_SET,OLED_CMD); 				  //电荷泵设置命令
	OLED_WR_Byte(0x14,OLED_CMD);							  //开启电荷泵

	/*设置内存地址模式*/
	OLED_WR_Byte(SET_MEMORY_ADDR_MODE,OLED_CMD);			  //内存地址模式设置命令
	OLED_WR_Byte(0x10,OLED_CMD);							  //设置地址模式值：0x00,列地址模式；0x01,行地址模式；
															  //0x10，页地址模式；
	/*设置列地址映射*/										  
	OLED_WR_Byte(SET_SEGMENT_REMAP_A1,OLED_CMD); 			  //列地址0映射到SEG127

	/*设置行地址映射*/
	OLED_WR_Byte(SET_COM_SCAN_DIRECTION_C8,OLED_CMD); 		  //行地址0映射到COM63
	
	/*设置COM硬件引脚配置*/									  
	OLED_WR_Byte(SET_COM_PINS_CONFIG,OLED_CMD); 			  //设置COM硬件引脚配置命令
	OLED_WR_Byte(0x00,OLED_CMD); 

	/*对比度设置*/
	OLED_WR_Byte(SET_CONTRAST_CONTROL,OLED_CMD); 			   //对比度设置命令
	OLED_WR_Byte(0x8F,OLED_CMD); 							   //对比度值，取值范围1-255
	
	/*设置预充电周期*/
	OLED_WR_Byte(SET_PRECHARGE_PERIOD,OLED_CMD); 
	OLED_WR_Byte(0xF1,OLED_CMD); 
	
	/*设置VCOMH电源倍率*/
	OLED_WR_Byte(SET_VCOMH_DESELECT_L,OLED_CMD); 
	OLED_WR_Byte(0x00,OLED_CMD);

	/*关闭全局显示*/
    OLED_WR_Byte(ENTIRE_DISPLAY_ON_A4,OLED_CMD); 

	/*设置OLED点亮方式*/
	OLED_WR_Byte(NORMAL_DISPLAY,OLED_CMD); 	 				//0：熄灭像素；1：点亮像素

	/*打开OLED显示*/
	OLED_WR_Byte(SET_DISPLAY_ON,OLED_CMD); 
	
	/*清屏操作*/
	OledClearn();
}
