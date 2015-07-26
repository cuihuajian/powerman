/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptors for Joystick Mouse Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize 64*/
    0x83,                       /*idVendor (0x0483)*/
    0x88,
    0x10,                       /*idProduct = 0x5710*/
    0x11,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    1,                          /*Index of string descriptor describing
                                                  manufacturer */
    2,                          /*Index of string descriptor describing
                                                 product*/
    3,                          /*Index of string descriptor describing the
                                                 device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* Joystick_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
  {
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    JOYSTICK_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /*bNumInterfaces: 1 interface*/
    0x01,         /*bConfigurationValue: Configuration value*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                     the configuration*/
    0xE0,         /*bmAttributes: Self powered */
    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size*/
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
    0x00,         /*bInterfaceNumber: Number of Interface*/
    0x00,         /*bAlternateSetting: Alternate setting*/
    0x02,         /*bNumEndpoints*/
    0x03,         /*bInterfaceClass: HID*/
    0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0,            /*iInterface: Index of string descriptor*/
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,         /*bLength: HID Descriptor size*/
    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
    0x10,         /*bcdHID: HID Class Spec release number*/
    0x01,
    0x00,         /*bCountryCode: Hardware target country*/
    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
    0x22,         /*bDescriptorType*/
    JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
    0x00,
    /******************** Descriptor of Joystick Mouse endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x81,          /*bEndpointAddress: Endpoint Address (IN)*/
    0x03,          /*bmAttributes: Interrupt endpoint*/
    0x23,          /*wMaxPacketSize: 4 Byte max */
    0x00,
    0x20,          /*bInterval: Polling Interval (32 ms)*/
    /* 34 */
	0x07,      /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: */
                     /*    Endpoint descriptor type */
    0x02,      /* bEndpointAddress: */
                     /*    Endpoint Address (OUT) */
    0x03,      /* bmAttributes: Interrupt endpoint */
    0x02,//0x02,   /* wMaxPacketSize: 20 Bytes max  */
    0x00,
    0x10,   
  }
  ; /* MOUSE_ConfigDescriptor */
const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] =
  {
	0x05, 0xff, /* USAGE_PAGE (ST Page) */ 
	0x09, 0xff, /* USAGE (Demo Kit) */
    0xA1, 0x01, /*Collection(Logical)*/
    // The Input report	
    0x05, 0x01,                      // USAGE_PAGE(1)
    0x15, 0x00,         //LOGICAL_MINIMUM (0)
    0x25, 0xFF,         //LOGICAL_MAXIMUM (255)
    0x19, 0x00,         //USAGE_MINIMUM (1)	  
	0x29, 0xff,         //USAGE_MAXIMUM (8) 
    /* 24 */
    0x95,0x23,          //REPORT_COUNT (8)
    0x75,0x08,          //REPORT_SIZE (8)
    0x81,0x02,         //INPUT (Data,Var,Abs)
    // The Output report
    0x05, 0x02,                      // USAGE_PAGE(2)
    0x19, 0x00,                      //   USAGE_MINIMUM (0)
    0x29, 0xFF,                      //   USAGE_MAXIMUM (255)
    0x15, 0x00,                      //   LOGICAL_MINIMUM (0)
    0x25, 0xFF,                      //   LOGICAL_MAXIMUM (255)
    0x95, 0x02,                      //   REPORT_SIZE (8)
    0x75, 0x08,                      //   REPORT_COUNT (64) ---PC Read/Write TAG+63BYTE        =64Byte
    0x91, 0x02,                      //   OUTPUT (Data,Var,Abs)
    
	0xc0
  }
  ; /* Joystick_ReportDescriptor */

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const u8 Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =	    
{
	JOYSTICK_SIZ_STRING_VENDOR, /* Size of manufaturer string */
	0x03,           /* bDescriptorType = String descriptor */
	/* Manufacturer: "����������ӿƼ����޹�˾" */
	0X7F,0X5E,//��
	0XDE,0X5D,//��
	0X1F,0X66,//��
	0XFC,0X7F,//��
	0X35,0X75,//��
	0X50,0X5B,//��
	0XD1,0X79,//��
	0X62,0X80,//��
	0X09,0X67,//��
	0X50,0X96,//��
	0X6C,0X51,//��
	0XF8,0X53,//˾	  
};
//ʹ��UNICODE����
const u8 Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
{
	JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	'Z', 0, 'T', 0, 'E', 0,//ALIENTEK
	' ', 0, 
	0X7a,0X66,//��
	0Xfd,0X80,//��
	0Xb6,0X5b,//��
	0X45,0X5c,//�� 
};
uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
  {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

