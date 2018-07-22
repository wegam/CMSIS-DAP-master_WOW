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

/* USB Standard Request Codes */		//��׼�������
#define USB_REQUEST_GET_STATUS                 0		//��ȡ�豸״̬	��������󷵻�ָ����������״̬
#define USB_REQUEST_CLEAR_FEATURE              1		//�������			����������Ǳ�������������һ�����ԡ�
#define USB_REQUEST_SET_FEATURE                3		//�������� 		����������������û�ʹ��һ��ָ��������.
#define USB_REQUEST_SET_ADDRESS                5		//���õ�ַ 		���������Ϊ����δ�����豸���������豸��ַ
#define USB_REQUEST_GET_DESCRIPTOR             6		//ȡ��������		��������󷵻ش��ڵ�������.��ȡ�豸�����������豸���������������������ӿ����������ַ���������
#define USB_REQUEST_SET_DESCRIPTOR             7		//����������		�����������ڸ��»������µ���������.
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

/* bmRequestType Definition */
typedef __packed struct _REQUEST_TYPE {
  U8 Recipient : 5;                     /* D4..0: Recipient */										//D[4:0]-���նˣ�0���豸��1���ӿڣ�2���˵㣬3��������4~31������
  U8 Type      : 2;                     /* D6..5: Type */													//D[6:5]-���ͣ�0����׼��1��Ⱥ�飬2����Ӧ��3������
  U8 Dir       : 1;                     /* D7:    Data Phase Txsfer Direction */	//D7-���ݴ��䷽��0���������豸��1���豸������
} REQUEST_TYPE;

/* USB Default Control Pipe Setup Packet */
typedef __packed struct _USB_SETUP_PACKET {
  REQUEST_TYPE bmRequestType;           /* bmRequestType */	//USB�豸��������
  U8  bRequest;                         /* bRequest */			//������������������
  __packed union {											//�Ǹ��ݲ�ͬ����������ò�ͬ��ֵ��һ����Ǵ��Ͳ������豸��������ʲô����
    U16        wValue;                  /* wValue *///wValueֵ������ĸ��ֽ���01����ô�������豸�������ˡ����ֽ���00����ô�����Ǳ�ʾ��ƫ�Ƶ�ַ0��ʼ��ȡ�豸���������������������������кܶ����ã����Ե��ֽ�������Ϳ�������ʶ���ȡͬ�����͵���������ͬ�����á�
    __packed struct {
      U8         wValueL;
      U8         wValueH;
    };
  };
  __packed union {											//
    U16        wIndex;                  /* wIndex */	//wIndex�Ǹ��ݲ�ͬ����������ò�ͬ��ֵ��һ������˵���˵�Ż���˵���ӿڱ�ʶ���ڻ�ȡ�����������Ϊ0������������ID����������͵����������������Ϊ00 00��
    __packed struct {
      U8         wIndexL;
      U8         wIndexH;
    };
  };
  U16          wLength;                 /* wLength */	//wLength�Ǹ���������������һ�׶η������ݵĳ��ȡ�
} USB_SETUP_PACKET;


/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE                  1			//�豸������	���豸������������USB�豸��һ����Ϣ����������豸�������豸������ȫ�����õ���Ϣ��һ��USB�豸ֻ����һ���豸������.
#define USB_CONFIGURATION_DESCRIPTOR_TYPE           2			//����������	������������������һ�豸���õ���Ϣ������������һ��b Configuration Value����SetConfiguration(  )��ʱ������������������������ .
#define USB_STRING_DESCRIPTOR_TYPE                  3			//�ַ�����������
#define USB_INTERFACE_DESCRIPTOR_TYPE               4			//�ӿ�������	������������һ�������ڸ���һ���ӿڵ���Ϣ�����һ������֧�ֲ�ֹһ���ӿڣ��˽ڵ������������ڽӿ��������󱻷��أ��ӿ�������������Ϊ������������һ���ֱ����ء�
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
  U8  bLength;						//�����豸�����������ֽ���
  U8  bDescriptorType;		//�����������ͣ�Ϊ0X01���������豸��������
  U16 bcdUSB;							//����豸���ݵ�USB�豸�汾��
  U8  bDeviceClass;				//�豸���룺����USB Э��涨�ģ��������ǽӿ�����ʵ�ֵĹ��ܡ�������Ϊ0ʱ���������Ҳ����Ϊ0����Ϊ0XFF��ʾ���ǳ����Զ����豸��
  U8  bDeviceSubClass;		//��������룺�����ֵ����˼�Ǹ����豸�������������豸����Ϊ�㣬���ֶ�ҲҪ�㣬���豸����Ϊ0XFF�����������ֵ������	
  U8  bDeviceProtocol;		//Э���룺��Щ���ֵ���豸�����������ֵ�����������ֶ�Ϊ0�ǣ���ʾ�豸��ʹ�����������Э�飬 �����ֶε�ֵΪ0XFFʱ����ʾʹ���豸�����Զ����Э��	
  U8  bMaxPacketSize0;		//�˵�0���ܻ����������ݰ���С
  U16 idVendor;						//�����豸���ҵı�־����USB �����֯���ģ�
  U16 idProduct;					//��Ʒ��־���������ĳ����Լ�����ţ�
  U16 bcdDevice;					//�豸�İ汾��
  U8  iManufacturer;			//���������豸���ҵ���Ϣ���ַ���������������ֵ��
  U8  iProduct;						//������ʹ���豸��Ʒ����Ϣ���ִ�������������ֵ��
  U8  iSerialNumber;			//�����豸��Ʒ�����к���Ϣ���ִ�������������ֵ��
  U8  bNumConfigurations;	//�豸�ж���������
} USB_DEVICE_DESCRIPTOR;

/* USB 2.0 Device Qualifier Descriptor */
typedef __packed struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
  U16 bcdUSB;
  U8  bDeviceClass;
  U8  bDeviceSubClass;
  U8  bDeviceProtocol;
  U8  bMaxPacketSize0;
  U8  bNumConfigurations;
  U8  bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR;

/* USB Standard Configuration Descriptor */
typedef __packed struct _USB_CONFIGURATION_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
  U16 wTotalLength;
  U8  bNumInterfaces;
  U8  bConfigurationValue;
  U8  iConfiguration;
  U8  bmAttributes;
  U8  bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;

/* USB Standard Interface Descriptor */
typedef __packed struct _USB_INTERFACE_DESCRIPTOR {
  U8  bLength;							/* bLength */							//�ӿ����������ֽ�����С
  U8  bDescriptorType;			/* bDescriptorType */			//�ӿ������������ͱ��
  U8  bInterfaceNumber;			/* bInterfaceNumber */		//�ýӿڵı��
  U8  bAlternateSetting;		/* bAlternateSetting */		//���õĽӿ����������
  U8  bNumEndpoints;				/* bNumEndpoints */				//�ýӿ�ʹ�õĶ˵������������˵�0
  U8  bInterfaceClass;			/* bInterfaceClass */			//�ӿ�����
  U8  bInterfaceSubClass;		/* bInterfaceSubClass */	//�ӿ�������
  U8  bInterfaceProtocol;		/* bInterfaceProtocol */	//�ӿ���ѭ��Э��
  U8  iInterface;						/* iInterface */					//�����ýӿڵ��ַ�������ֵ
} USB_INTERFACE_DESCRIPTOR;

/* USB Standard Endpoint Descriptor */
typedef __packed struct _USB_ENDPOINT_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
  U8  bEndpointAddress;
  U8  bmAttributes;
  U16 wMaxPacketSize;
  U8  bInterval;
} USB_ENDPOINT_DESCRIPTOR;

/* USB String Descriptor */
typedef __packed struct _USB_STRING_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
  U16 bString/*[]*/;
} USB_STRING_DESCRIPTOR;

/* USB Common Descriptor */
typedef __packed struct _USB_COMMON_DESCRIPTOR {
  U8  bLength;
  U8  bDescriptorType;
} USB_COMMON_DESCRIPTOR;

/* USB Interface Association Descriptor */	//USB�����豸һ����Interface Association Descriptor��IAD��ʵ�֣�������Ҫ�ϲ��Ľӿ�ǰ����IAD��������
typedef __packed struct _USB_INTERFACE_ASSOCIATION_DESCRIPTOR {
  U8  bLength;							/* bLength */						//��������С
  U8  bDescriptorType;			/* bDescriptorType */		//IAD����������
  U8  bFirstInterface;			/* bFirstInterface */		//��ʼ�ӿ�	
  U8  bInterfaceCount;			/* bInterfaceCount */		//�ӿ���
  U8  bFunctionClass;				/* bFunctionClass */		//���ʹ���
  U8  bFunctionSubclass;		/* bFunctionSubclass */	//�����ʹ���
  U8  bFunctionProtocol;		/* bFunctionProtocol */	//Э�����
  U8  iFunction;						/* iFunction */					//�����ַ�������
} USB_INTERFACE_ASSOCIATION_DESCRIPTOR;


#endif  /* __USB_DEF_H__ */