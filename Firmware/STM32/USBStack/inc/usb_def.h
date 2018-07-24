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


/* bmRequestType.Dir */						//数据传输方向：0＝主机至设备，1＝设备至主机
#define REQUEST_HOST_TO_DEVICE     0			//0＝主机至设备
#define REQUEST_DEVICE_TO_HOST     1			//1＝设备至主机

/* bmRequestType.Type */
#define REQUEST_STANDARD           0			//标准请求
#define REQUEST_CLASS              1			//设备类请求
#define REQUEST_VENDOR             2			//供应商
#define REQUEST_RESERVED           3			//保留

/* bmRequestType.Recipient */
#define REQUEST_TO_DEVICE          0
#define REQUEST_TO_INTERFACE       1
#define REQUEST_TO_ENDPOINT        2
#define REQUEST_TO_OTHER           3

/* bmRequestType Definition */
typedef __packed struct _REQUEST_TYPE {
  U8 Recipient : 5;                     /* D4..0: Recipient */										//D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
  U8 Type      : 2;                     /* D6..5: Type */													//D[6:5]-类型：0＝标准，1＝群组，2＝供应商3＝保留
  U8 Dir       : 1;                     /* D7:    Data Phase Txsfer Direction */	//D7-数据传输方向：0＝主机至设备，1＝设备至主机
} REQUEST_TYPE;

/* USB Standard Request Codes */		//标准请求代码
#define USB_REQUEST_GET_STATUS                 0		//获取设备状态	：这个请求返回指定接收器的状态
#define USB_REQUEST_CLEAR_FEATURE              1		//清除特性			：这个请求是被用来清除或禁能一个特性。
#define USB_REQUEST_SET_FEATURE                3		//设置特性 		：这个请求用于设置或使能一个指定的特性.
#define USB_REQUEST_SET_ADDRESS                5		//设置地址 		：这个请求为所有未来的设备访问设置设备地址
#define USB_REQUEST_GET_DESCRIPTOR             6		//取得描述符		：这个请求返回存在的描述符.获取设备描述，包括设备描述符，配置描述符，接口描述符，字符串描述符
#define USB_REQUEST_SET_DESCRIPTOR             7		//设置描述符		：此请求用于更新或添加新的描述表符.
#define USB_REQUEST_GET_CONFIGURATION          8		//取得配置			：这个请求返回当前设备的配置值.
#define USB_REQUEST_SET_CONFIGURATION          9		//设置配置			：这个请求设置设备的配置
#define USB_REQUEST_GET_INTERFACE              10		//取得接口			：这个请求向指定接口返回选中的备用设备.
#define USB_REQUEST_SET_INTERFACE              11		//设置接口			：这个请求允许主机为指定的接口选择另一个设置.
#define USB_REQUEST_SYNC_FRAME                 12		//同步帧				：这个请求用于设置和报告端点的同步帧

/* USB GET_STATUS Bit Values */
#define USB_GETSTATUS_SELF_POWERED             0x01
#define USB_GETSTATUS_REMOTE_WAKEUP            0x02
#define USB_GETSTATUS_ENDPOINT_STALL           0x01

/* USB Standard Feature selectors */
#define USB_FEATURE_ENDPOINT_STALL             0
#define USB_FEATURE_REMOTE_WAKEUP              1		//远程唤醒

/* USB Default Control Pipe Setup Packet */
typedef __packed struct _USB_SETUP_PACKET {
  REQUEST_TYPE bmRequestType;           /* bmRequestType */	//USB设备请求类型
  U8  bRequest;                         /* bRequest */			//特定请求
  __packed union {
    U16        wValue;                  /* wValue */
    __packed struct {
      U8         wValueL;
      U8         wValueH;
    };
  };
  __packed union {
    U16        wIndex;                  /* wIndex */
    __packed struct {
      U8         wIndexL;
      U8         wIndexH;
    };
  };
  U16          wLength;                 /* wLength */
} USB_SETUP_PACKET;


/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE                  1			//设备描述符	：设备描述符给出了USB设备的一般信息。这包括对设备及所有设备配置起全程作用的信息。一个USB设备只能有一个设备描述符.
#define USB_CONFIGURATION_DESCRIPTOR_TYPE           2			//配置描述符	：配置描述表给出了一设备配置的信息，描述表包括一个b Configuration Value域，在SetConfiguration(  )请时被用作参数来设置所需配置 .
#define USB_STRING_DESCRIPTOR_TYPE                  3			//字符串描述符：
#define USB_INTERFACE_DESCRIPTOR_TYPE               4			//接口描述符	：此描述表在一个配置内给出一个接口的信息。如果一个配置支持不止一个接口，端节点的描述表会跟在接口描述表后被返回，接口描述表总是作为配置描述表的一部分被返回。
#define USB_ENDPOINT_DESCRIPTOR_TYPE                5			//端点描述符	：
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE        6			//设备限定符	：设备限定描述符说明了呢功能进行高速操作的设备在其他速度操作时产生的变化信息.
																													//						例如,如果设备当前在全速下操作,设备限定符返回它如何在高速操作的信息或者相反.
#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE      7			//其他速度配置：说明了能进行高速操作的设备在其他可能的速度下操作配置.其他速度配置的结构与配置描述符一样.
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE         8			//
#define USB_OTG_DESCRIPTOR_TYPE                     9
#define USB_DEBUG_DESCRIPTOR_TYPE                  10
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE  11 		//IAD描述符类型	//USB复合设备一般用Interface Association Descriptor（IAD）实现，就是在要合并的接口前加上IAD描述符。

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
  U8  bLength;						//描述设备描述符的总字节数
  U8  bDescriptorType;		//描述符的类型（为0X01，这里是设备描述符）
  U16 bcdUSB;							//这个设备兼容的USB设备版本号
  U8  bDeviceClass;				//设备类码：是由USB 协会规定的，描述的是接口所能实现的功能。当此域为0时下面的子类也必须为0，当为0XFF表示的是厂商自定义设备类
  U8  bDeviceSubClass;		//子类代码码：这个码值的意思是根据设备类码来看。如设备类码为零，这字段也要零，如设备类码为0XFF，此域的所有值保留。	
  U8  bDeviceProtocol;		//协议码：这些码的值视设备码和子类代码的值而定。当该字段为0是，表示设备不使用类所定义的协议， 当该字段的值为0XFF时，表示使用设备厂商自定义的协议	
  U8  bMaxPacketSize0;		//端点0的能缓冲的最大数据包大小
  U16 idVendor;						//生产设备厂家的标志（由USB 相关组织给的）
  U16 idProduct;					//产品标志（由生产的厂家自己做编号）
  U16 bcdDevice;					//设备的版本号
  U8  iManufacturer;			//描述生产设备厂家的信息的字符串描述符的索引值。
  U8  iProduct;						//描述所使用设备产品的信息的字串描述符的索引值。
  U8  iSerialNumber;			//描述设备产品的序列号信息的字串描述符的索引值。
  U8  bNumConfigurations;	//设备有多少种配置
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
  U8  bLength;							/* bLength */							//接口描述符的字节数大小
  U8  bDescriptorType;			/* bDescriptorType */			//接口描述符的类型编号
  U8  bInterfaceNumber;			/* bInterfaceNumber */		//该接口的编号
  U8  bAlternateSetting;		/* bAlternateSetting */		//备用的接口描述符编号
  U8  bNumEndpoints;				/* bNumEndpoints */				//该接口使用的端点数，不包括端点0
  U8  bInterfaceClass;			/* bInterfaceClass */			//接口类型
  U8  bInterfaceSubClass;		/* bInterfaceSubClass */	//接口子类型
  U8  bInterfaceProtocol;		/* bInterfaceProtocol */	//接口遵循的协议
  U8  iInterface;						/* iInterface */					//描述该接口的字符串索引值
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

/* USB Interface Association Descriptor */	//USB复合设备一般用Interface Association Descriptor（IAD）实现，就是在要合并的接口前加上IAD描述符。
typedef __packed struct _USB_INTERFACE_ASSOCIATION_DESCRIPTOR {
  U8  bLength;							/* bLength */						//描述符大小
  U8  bDescriptorType;			/* bDescriptorType */		//IAD描述符类型
  U8  bFirstInterface;			/* bFirstInterface */		//起始接口	
  U8  bInterfaceCount;			/* bInterfaceCount */		//接口数
  U8  bFunctionClass;				/* bFunctionClass */		//类型代码
  U8  bFunctionSubclass;		/* bFunctionSubclass */	//子类型代码
  U8  bFunctionProtocol;		/* bFunctionProtocol */	//协议代码
  U8  iFunction;						/* iFunction */					//描述字符串索引
} USB_INTERFACE_ASSOCIATION_DESCRIPTOR;


#endif  /* __USB_DEF_H__ */
