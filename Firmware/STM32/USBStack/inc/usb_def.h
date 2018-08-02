/*------------------------------------------------------------------------------
 *      RL-ARM - USB
 *------------------------------------------------------------------------------
 *      Name:    usb_def.h
 *      Purpose: USB Definitions
 *      Rev.:    V4.70
 *------------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __USB_DEF_H__
#define __USB_DEF_H__

#include "stdint.h"
#pragma anon_unions


/* bmRequestType.Dir */						//���ݴ��䷽��0���������豸��1���豸������
#define REQUEST_HOST_TO_DEVICE     0			//0���������豸
#define REQUEST_DEVICE_TO_HOST     1			//1���豸������

/* bmRequestType.Type */
#define REQUEST_STANDARD           0			//��׼����
#define REQUEST_CLASS              1			//�豸������
#define REQUEST_VENDOR             2			//��Ӧ��
#define REQUEST_RESERVED           3			//����

/* bmRequestType.Recipient */
#define REQUEST_TO_DEVICE          0
#define REQUEST_TO_INTERFACE       1
#define REQUEST_TO_ENDPOINT        2
#define REQUEST_TO_OTHER           3

/* bmRequestType Definition */
typedef __packed struct _REQUEST_TYPE {
  uint8_t Recipient : 5;                     /* D4..0: Recipient */										//D[4:0]-���նˣ�0���豸��1���ӿڣ�2���˵㣬3��������4~31������
  uint8_t Type      : 2;                     /* D6..5: Type */													//D[6:5]-���ͣ�0����׼��1��Ⱥ�飬2����Ӧ��3������
  uint8_t Dir       : 1;                     /* D7:    Data Phase Txsfer Direction */	//D7-���ݴ��䷽��0���������豸��1���豸������
} REQUEST_TYPE;

/* USB Standard Request Codes */		//��׼�������
#define USB_REQUEST_GET_STATUS                 0		//��ȡ�豸״̬	��������󷵻�ָ����������״̬
#define USB_REQUEST_CLEAR_FEATURE              1		//�������			����������Ǳ�������������һ�����ԡ�
#define USB_REQUEST_SET_FEATURE                3		//�������� 		����������������û�ʹ��һ��ָ��������.
#define USB_REQUEST_SET_ADDRESS                5		//���õ�ַ 		���������Ϊ����δ�����豸���������豸��ַ
#define USB_REQUEST_GET_DESCRIPTOR             6		//ȡ��������		��������󷵻ش��ڵ�������.��ȡ�豸�����������豸���������������������ӿ����������ַ���������
#define USB_REQUEST_SET_DESCRIPTOR             7		//����������		�����������ڸ��»�����µ��������.
#define USB_REQUEST_GET_CONFIGURATION          8		//ȡ������			��������󷵻ص�ǰ�豸������ֵ.
#define USB_REQUEST_SET_CONFIGURATION          9		//��������			��������������豸������
#define USB_REQUEST_GET_INTERFACE              10		//ȡ�ýӿ�			�����������ָ���ӿڷ���ѡ�еı����豸.
#define USB_REQUEST_SET_INTERFACE              11		//���ýӿ�			�����������������Ϊָ���Ľӿ�ѡ����һ������.
#define USB_REQUEST_SYNC_FRAME                 12		//ͬ��֡				����������������úͱ���˵��ͬ��֡

/* USB GET_STATUS Bit Values */
#define USB_GETSTATUS_SELF_POWERED             0x01
#define USB_GETSTATUS_REMOTE_WAKEUP            0x02
#define USB_GETSTATUS_ENDPOINT_STALL           0x01

/* USB Standard Feature selectors */
#define USB_FEATURE_ENDPOINT_STALL             0
#define USB_FEATURE_REMOTE_WAKEUP              1		//Զ�̻���

/* USB Default Control Pipe Setup Packet */
typedef __packed struct _USB_SETUP_PACKET
{
  REQUEST_TYPE bmRequestType;           /* bmRequestType */	//USB�豸��������
  uint8_t  bRequest;                         /* bRequest */			//�ض�����
  __packed union
	{
    uint16_t        wValue;                  /* wValue */
    __packed struct
		{
      uint8_t         wValueL;
      uint8_t         wValueH;
    };
  };
  __packed union
	{
    uint16_t        wIndex;                  /* wIndex */
    __packed struct
		{
      uint8_t         wIndexL;
      uint8_t         wIndexH;
    };
  };
  uint16_t          wLength;                 /* wLength */
} USB_SETUP_PACKET;


/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE                  1			//�豸������	���豸������������USB�豸��һ����Ϣ����������豸�������豸������ȫ�����õ���Ϣ��һ��USB�豸ֻ����һ���豸������.
#define USB_CONFIGURATION_DESCRIPTOR_TYPE           2			//����������	�����������������һ�豸���õ���Ϣ�����������һ��b Configuration Value����SetConfiguration(  )��ʱ������������������������ .
#define USB_STRING_DESCRIPTOR_TYPE                  3			//�ַ�����������
#define USB_INTERFACE_DESCRIPTOR_TYPE               4			//�ӿ�������	������������һ�������ڸ���һ���ӿڵ���Ϣ�����һ������֧�ֲ�ֹһ���ӿڣ��˽ڵ�����������ڽӿ�������󱻷��أ��ӿ�������������Ϊ�����������һ���ֱ����ء�
#define USB_ENDPOINT_DESCRIPTOR_TYPE                5			//�˵�������	��
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE        6			//�豸�޶���	���豸�޶�������˵�����ع��ܽ��и��ٲ������豸�������ٶȲ���ʱ�����ı仯��Ϣ.
																													//						����,����豸��ǰ��ȫ���²���,�豸�޶�������������ڸ��ٲ�������Ϣ�����෴.
#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE      7			//�����ٶ����ã�˵�����ܽ��и��ٲ������豸���������ܵ��ٶ��²�������.�����ٶ����õĽṹ������������һ��.
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE         8			//
#define USB_OTG_DESCRIPTOR_TYPE                     9
#define USB_DEBUG_DESCRIPTOR_TYPE                  10
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE  11 		//IAD����������	//USB�����豸һ����Interface Association Descriptor��IAD��ʵ�֣�������Ҫ�ϲ��Ľӿ�ǰ����IAD��������

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED              0x00
#define USB_DEVICE_CLASS_AUDIO                 0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS        0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE       0x03
#define USB_DEVICE_CLASS_MONITOR               0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE    0x05
#define USB_DEVICE_CLASS_POWER                 0x06
#define USB_DEVICE_CLASS_PRINTER               0x07
#define USB_DEVICE_CLASS_STORAGE               0x08
#define USB_DEVICE_CLASS_HUB                   0x09
#define USB_DEVICE_CLASS_MISCELLANEOUS         0xEF
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC       0xFF

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_POWERED_MASK                0x40
#define USB_CONFIG_BUS_POWERED                 0x80
#define USB_CONFIG_SELF_POWERED                0xC0
#define USB_CONFIG_REMOTE_WAKEUP               0x20

/* bMaxPower in Configuration Descriptor */
#define USB_CONFIG_POWER_MA(mA)                ((mA)/2)

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK            0x80
#define USB_ENDPOINT_OUT(addr)                 ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)                  ((addr) | 0x80)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK                 0x03
#define USB_ENDPOINT_TYPE_CONTROL              0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS          0x01
#define USB_ENDPOINT_TYPE_BULK                 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT            0x03
#define USB_ENDPOINT_SYNC_MASK                 0x0C
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION   0x00
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS         0x04
#define USB_ENDPOINT_SYNC_ADAPTIVE             0x08
#define USB_ENDPOINT_SYNC_SYNCHRONOUS          0x0C
#define USB_ENDPOINT_USAGE_MASK                0x30
#define USB_ENDPOINT_USAGE_DATA                0x00
#define USB_ENDPOINT_USAGE_FEEDBACK            0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK   0x20
#define USB_ENDPOINT_USAGE_RESERVED            0x30

/* USB Standard Device Descriptor */
typedef __packed struct _USB_DEVICE_DESCRIPTOR
{
  uint8_t  bLength;						//�����豸�����������ֽ���
  uint8_t  bDescriptorType;		//�����������ͣ�Ϊ0X01���������豸��������
  uint16_t bcdUSB;							//����豸���ݵ�USB�豸�汾��
  uint8_t  bDeviceClass;				//�豸���룺����USB Э��涨�ģ��������ǽӿ�����ʵ�ֵĹ��ܡ�������Ϊ0ʱ���������Ҳ����Ϊ0����Ϊ0XFF��ʾ���ǳ����Զ����豸��
  uint8_t  bDeviceSubClass;		//��������룺�����ֵ����˼�Ǹ����豸�������������豸����Ϊ�㣬���ֶ�ҲҪ�㣬���豸����Ϊ0XFF�����������ֵ������	
  uint8_t  bDeviceProtocol;		//Э���룺��Щ���ֵ���豸�����������ֵ�����������ֶ�Ϊ0�ǣ���ʾ�豸��ʹ�����������Э�飬 �����ֶε�ֵΪ0XFFʱ����ʾʹ���豸�����Զ����Э��	
  uint8_t  bMaxPacketSize0;		//�˵�0���ܻ����������ݰ���С
  uint16_t idVendor;						//�����豸���ҵı�־����USB �����֯���ģ�
  uint16_t idProduct;					//��Ʒ��־���������ĳ����Լ�����ţ�
  uint16_t bcdDevice;					//�豸�İ汾��
  uint8_t  iManufacturer;			//���������豸���ҵ���Ϣ���ַ���������������ֵ��
  uint8_t  iProduct;						//������ʹ���豸��Ʒ����Ϣ���ִ�������������ֵ��
  uint8_t  iSerialNumber;			//�����豸��Ʒ�����к���Ϣ���ִ�������������ֵ��
  uint8_t  bNumConfigurations;	//�豸�ж���������
} USB_DEVICE_DESCRIPTOR;

/* USB 2.0 Device Qualifier Descriptor */
typedef __packed struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint8_t  bNumConfigurations;
  uint8_t  bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR;

/* USB Standard Configuration Descriptor */
typedef __packed struct _USB_CONFIGURATION_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationValue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;

/* USB Standard Interface Descriptor */
typedef __packed struct _USB_INTERFACE_DESCRIPTOR {
  uint8_t  bLength;							/* bLength */							//�ӿ����������ֽ�����С
  uint8_t  bDescriptorType;			/* bDescriptorType */			//�ӿ������������ͱ��
  uint8_t  bInterfaceNumber;		/* bInterfaceNumber */		//�ýӿڵı��
  uint8_t  bAlternateSetting;		/* bAlternateSetting */		//���õĽӿ����������
  uint8_t  bNumEndpoints;				/* bNumEndpoints */				//�ýӿ�ʹ�õĶ˵������������˵�0
  uint8_t  bInterfaceClass;			/* bInterfaceClass */			//�ӿ�����
  uint8_t  bInterfaceSubClass;	/* bInterfaceSubClass */	//�ӿ�������
  uint8_t  bInterfaceProtocol;	/* bInterfaceProtocol */	//�ӿ���ѭ��Э��
  uint8_t  iInterface;					/* iInterface */					//�����ýӿڵ��ַ�������ֵ
} USB_INTERFACE_DESCRIPTOR;

/* USB Standard Endpoint Descriptor */
typedef __packed struct _USB_ENDPOINT_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bEndpointAddress;
  uint8_t  bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t  bInterval;
} USB_ENDPOINT_DESCRIPTOR;

/* USB String Descriptor */
typedef __packed struct _USB_STRING_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bString/*[]*/;
} USB_STRING_DESCRIPTOR;

/* USB Common Descriptor */
typedef __packed struct _USB_COMMON_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
} USB_COMMON_DESCRIPTOR;

/* USB Interface Association Descriptor */	//USB�����豸һ����Interface Association Descriptor��IAD��ʵ�֣�������Ҫ�ϲ��Ľӿ�ǰ����IAD��������
typedef __packed struct _USB_INTERFACE_ASSOCIATION_DESCRIPTOR {
  uint8_t  bLength;							/* bLength */						//��������С
  uint8_t  bDescriptorType;			/* bDescriptorType */		//IAD����������
  uint8_t  bFirstInterface;			/* bFirstInterface */		//��ʼ�ӿ�	
  uint8_t  bInterfaceCount;			/* bInterfaceCount */		//�ӿ���
  uint8_t  bFunctionClass;				/* bFunctionClass */		//���ʹ���
  uint8_t  bFunctionSubclass;		/* bFunctionSubclass */	//�����ʹ���
  uint8_t  bFunctionProtocol;		/* bFunctionProtocol */	//Э�����
  uint8_t  iFunction;						/* iFunction */					//�����ַ�������
} USB_INTERFACE_ASSOCIATION_DESCRIPTOR;


#endif  /* __USB_DEF_H__ */
