#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//SSD1306 OLED ����IC��������
//������ʽ:8080����/4�ߴ���
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
typedef unsigned char uchar;		 
typedef unsigned int uint;	
//-----------------OLED�˿ڶ���----------------  					   
//ʹ��4�ߴ��нӿ�ʱʹ��
#define OLED_RS PBout(14)
#define OLED_SCLK PBout(13)
#define OLED_SDIN PBout(15)
		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
/*SSD1306 ���������*/
#define SET_CONTRAST_CONTROL		0x81		//�Աȶ��������ȡֵ��Χ1-255����λֵ��0x7F
#define SET_DISPLAY_ON				0xAF		//����ʾ����
#define SET_DISPLAY_OFF				0xAE		//����ʾ����
#define ENTIRE_DISPLAY_ON_A4		0xA4		//ȫ����ʾ�ر�
#define ENTIRE_DISPLAY_ON_A5		0xA5		//ȫ����ʾ����
#define NORMAL_DISPLAY				0xA6		//��GDDRAMֵΪ0��Ϩ�����أ���GDDRAMֵΪ1����������
#define INVERSE_DISPLAY				0xA7		//��GDDRAMֵΪ0���������أ���GDDRAMֵΪ1��Ϩ������

/*SSD1306 ������ʾ�����*/
#define HORIZONTAL_SCROLL_SETUP_RIGHT	0x26	//����ˮƽ�ƶ�
#define HORIZONTAL_SCROLL_SETUP_LEFT	0x27	//����ˮƽ�ƶ�
#define HORIZONTAL_SCROLL_SETUP_AE		0x00	//����ˮƽ�ƶ�ʱ����Ҫ�������ֽ�
#define HORIZONTAL_SCROLL_SETUP_F		0xFF	//����ˮƽ�ƶ�ʱ����Ҫ�������ֽ�
#define ACTIVATE_SCROLL					0x2F	//����������ʾ����	
#define DEACTIVATE_SCROLL				0x2E	//�رչ�����ʾ����
#define SET_VERTICAL_SCROLL_AREA		0xA3	//���ô�ֱ������Χ����	
#define HV_SCROLL_SRTEP_RIGHT			0x29	//����ˮƽ�ƶ�
#define HV_SCROLL_SRTEP_LEFT			0x2A	//����ˮƽ�ƶ�

/*SSD1306 ��ַ���������*/
#define SET_MEMORY_ADDR_MODE			0x20	//���õ�ַģʽ��0x00,�е�ַģʽ��0x01,�е�ַģʽ��0x10��ҳ��ַģʽ

/*SSD1306 Ӳ�����������*/
#define SET_SEGMENT_REMAP_A0			0xA0	//�е�ַ0ӳ�䵽SEG0
#define SET_SEGMENT_REMAP_A1			0xA1	//�е�ַ0ӳ�䵽SEG127
#define SET_MULTIPLEX_RATIO				0xA8	//��������·��
#define SET_COM_SCAN_DIRECTION_C0		0xC0	//ɨ�跽���COM0-->COM[N-1]
#define SET_COM_SCAN_DIRECTION_C8		0xC8	//ɨ�跽���COM[N-1]-->COM0
#define SET_DISPLAY_OFFSET				0xD3	//��������ʾƫ��
#define SET_COM_PINS_CONFIG				0xDA	//����COMӲ��������������

/*SSD1306 ��ʾʱ�Ӻ�������������*/
#define SET_DISPLAY_CLOCK				0xD5	//����ʱ�ӷ�Ƶ���ӡ���Ƶ��
#define SET_PRECHARGE_PERIOD			0xD9	//����Ԥ�������
#define SET_VCOMH_DESELECT_L			0xDB	//����VCOMH��Դ����
#define CHARGE_PUMP_SET					0x8D	//��ɱ�����

/*��ʾ�ַ����Ͷ���*/
#define TYPE_12X06						0x01	//��ʾ12*06�ַ�
#define TYPE_16X08						0x02	//��ʾ16*08�ַ�
#define TYPE_16X16						0x03	//��ʾ16*16�ַ�

//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void DisplayFont_16X16(uchar x,uchar y,uint len,uchar *dispdata);
void DisplayChar_16X08(uchar x,uchar y,uchar *dispdata);
void NumToString(u32 num,uchar numbit,uchar *string);
void OledHorizontalDisplay(uchar direction,uchar startpage,uchar endpage,uchar interval);
extern  unsigned char  asc2_1206[95][12];
extern  unsigned char  asc2_1608[95][16];
extern  unsigned char  ASWE[192];
extern  unsigned char  TEMP[64];
extern  unsigned char  HUMI[64];
extern  unsigned char  LIGH[64];
extern  unsigned char  Table3[106];
extern  unsigned char  Table4[256];
extern  unsigned char  Table5[256];
extern  unsigned char  TestUI_Page2[192];
extern  unsigned char  TestUI_Page4[192];
extern  unsigned char  TestUI_Page6[192];
extern  unsigned char  Scroll_Horizontal[128];
extern  unsigned char  Scroll_Vertical[32];
extern  unsigned char  Scroll_VH[32];
extern  unsigned char  Picture[512];
#endif  
	 



