/******************** (C) COPYRIGHT 2015 崔鹏 ********************
 * 硬件连接：-----------------
 *          |                 |
 *          |  PB10-I2C2_SCL		|
 *          |  PB11-I2C2_SDA   |
 *          |                 |
 *           -----------------
**********************************************************************************/
#include "i2c_ee.h"

#define I2C_Speed              400000
#define I2C1_SLAVE_ADDRESS7    0xA0
#define I2C_PageSize           8			/* AT24C02每页有8个字节 */

u16 EEPROM_ADDRESS;

/*
 * 函数名：I2C_GPIO_Config
 * 描述  ：I2C1 I/O配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* 使能与 I2C1 有关的时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);  
    
  /* PB6-I2C1_SCL、PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
}

/*
 * 函数名：I2C_Configuration
 * 描述  ：I2C 工作模式配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void I2C_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C 配置 */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* I2C2 初始化 */
  I2C_Init(I2C2, &I2C_InitStructure);
	
 /* 使能 I2C2 */
  I2C_Cmd(I2C2, ENABLE);
	/*允许1字节1应答模式*/
  I2C_AcknowledgeConfig(I2C2, ENABLE);    
}

/*
 * 函数名：I2C_EE_Init
 * 描述  ：I2C 外设(EEPROM)初始化
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void I2C_EE_Init(void)
{

  I2C_GPIO_Config(); 
 
  I2C_Mode_Configu();
}

/*
 * 函数名：I2C_EE_BufferRead
 * 描述  ：从EEPROM里面读取一块数据。 
 * 输入  ：-pBuffer 存放从EEPROM读取的数据的缓冲区指针。
 *         -WriteAddr 接收数据的EEPROM的地址。 
 *         -NumByteToWrite 要从EEPROM读取的字节数。
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
 */
u16 Htu21D_read(void)
{  
  u8 value[2];
	
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); // Added by Najoua 27/08/2008

  I2C_AcknowledgeConfig(I2C2, ENABLE);
  /* Send START condition */
  I2C_GenerateSTART(I2C2, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
 
  /* Send htd21d address for write */
  I2C_Send7bitAddress(I2C2, HTU21ADDR, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2C2, 0xe3);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STRAT condition a second time */  
  
  I2C_GenerateSTART(I2C2, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for read */
  I2C_Send7bitAddress(I2C2, HTU21ADDR|0x01, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
  value[0] = I2C_ReceiveData(I2C2);   
  
  I2C_AcknowledgeConfig(I2C2, DISABLE);
  I2C_GenerateSTOP(I2C2, ENABLE);   
   
  while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */  
  value[1] = I2C_ReceiveData(I2C2);
  I2C_AcknowledgeConfig(I2C2, ENABLE);
  
  return value[0] <<8 | value[1];
}

/******************** (C) COPYRIGHT 2011 迷你嵌入式开发工作室 ********************/
