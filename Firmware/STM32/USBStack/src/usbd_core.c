/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "RTL.h"
#include "rl_usb.h"
#include "string.h"
#include "usb_for_lib.h"

U16               USBD_DeviceStatus;
U8                USBD_DeviceAddress;
U8                USBD_Configuration;					//USBD_Configuration==0,未配置，USBD_Configuration!=0,已配置
U32               USBD_EndPointMask;
U32               USBD_EndPointHalt;
U32               USBD_EndPointStall;          /* EP must stay stalled */
U8                USBD_NumInterfaces;
U8                USBD_HighSpeed;
U8                USBD_ZLP;

USBD_EP_DATA      USBD_EP0Data;
USB_SETUP_PACKET  USBD_SetupPacket;

#ifdef __RTX
OS_TID            USBD_RTX_DevTask;            /* USB Device Task ID */
OS_TID            USBD_RTX_EPTask[16];         /* USB Endpoint Task ID's */
OS_TID            USBD_RTX_CoreTask;           /* USB Core Task ID */
#endif


__asm void $$USBD$$version (void) {
   /* Export a version number symbol for a version control. */

                EXPORT  __RL_USBD_VER

__RL_USBD_VER   EQU     0x470
}


/*
 *  Init USB Device Core and Hardware
 *    Parameters:      None
 *    Return Value:    None
 */

void usbd_init (void)
{
  USBD_HighSpeed     = __FALSE;

  usbd_class_init();			//USB类初始化 ，包括CDC端口配置和HID参数设置为默认值
  USBD_RTX_TaskInit();		//操作系统初始化--未使用

  USBD_Init();						//打开时钟、USB中断和使能USB连接
}


/*
 *  USB Device Connect/Disconnect Function
 *   Called by the User to Connect/Disconnect USB Device
 *    Parameters:      con:   Connect/Disconnect
 *    Return Value:    None
 */
void usbd_connect (BOOL con)
{
    USBD_Connect (con);
}

/*******************************************************************************
*函数名			:	usbd_reset_core
*功能描述		:	复位USB的一些数据标志
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Reset USB Device Core
 *    Parameters:      None
 *    Return Value:    None
 */

void usbd_reset_core (void) {

  USBD_DeviceStatus  = usbd_power;		//默认为总线供电,因为我们的USB现在不都是插在电脑上才能工作的么  
  USBD_DeviceAddress = 0;							//在枚举之初地址是0 
  USBD_Configuration = 0;							//配置描述符的标识从1开始,这里也先置为0 
  USBD_EndPointMask  = 0x00010001;		//目前使用的是端点０
  USBD_EndPointHalt  = 0x00000000;		//没有停止的端点
  USBD_EndPointStall = 0x00000000;
}


/*
 *  USB Device Configured Function
 *   Called by the User to check id USB Device is configured
 *    Parameters:
 *    Return Value:    Configurated state (FALSE = unconfigured, TRUE = configured)
 */

BOOL usbd_configured (void) {

  if (USBD_Configuration)
    return (__TRUE);

  return (__FALSE);
}

/*******************************************************************************
*函数名			:	USBD_SetupStage
*功能描述		:	建立阶段,读取建立数据包
*输入				: 
*返回值			:	USBD_EndPoint0 (U32 event)
*******************************************************************************/
/*
 *  USB Device Request - Setup Stage
 *    Parameters:      None
 *    Return Value:    None
 */

void USBD_SetupStage (void)
{
  USBD_ReadEP(0x00, (U8 *)&USBD_SetupPacket);
}


/*
 *  USB Device Request - Data In Stage	数据阶段(数据准备和发送)
 *    Parameters:      None
 *    Return Value:    None
 */

void USBD_DataInStage (void)
{
  U32 cnt;

  if (USBD_EP0Data.Count > usbd_max_packet0)		//#define USBD_MAX_PACKET0 	64
	{
    cnt = usbd_max_packet0;			//最大包容量
  }
	else
	{
    cnt = USBD_EP0Data.Count;		//实际大小
  }
  if (!cnt)
		USBD_ZLP = 0;
	cnt = USBD_WriteEP(0x80, USBD_EP0Data.pData, cnt);	//向主机发送数据，返回已发送数据	//D7-数据传输方向：0＝主机至设备，1＝设备至主机
  USBD_EP0Data.pData += cnt;		//结构体	USBD_EP_DATA	忆发送数据
  USBD_EP0Data.Count -= cnt;		//结构体	USBD_EP_DATA	剩余待发送数据
}


/*
 *  USB Device Request - Data Out Stage
 *    Parameters:      None
 *    Return Value:    None
 */

void USBD_DataOutStage (void)
{
  U32 cnt;

  cnt = USBD_ReadEP(0x00, USBD_EP0Data.pData);
  USBD_EP0Data.pData += cnt;
  USBD_EP0Data.Count -= cnt;
}


/*
 *  USB Device Request - Status In Stage
 *    Parameters:      None
 *    Return Value:    None
 */

void USBD_StatusInStage (void)
{
  USBD_WriteEP(0x80, NULL, 0);
}


/*
 *  USB Device Request - Status Out Stage
 *    Parameters:      None
 *    Return Value:    None
 */

void USBD_StatusOutStage (void)
{
  USBD_ReadEP(0x00, USBD_EP0Buf);
}


/*
 *  Get Status USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqGetStatus (void)
{
	U32 n, m;
  switch (USBD_SetupPacket.bmRequestType.Recipient)		//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_DEVICE:		//设备
      USBD_EP0Data.pData = (U8 *)&USBD_DeviceStatus;
      break;
    case REQUEST_TO_INTERFACE:	//接口
      if ((USBD_Configuration != 0) && (USBD_SetupPacket.wIndexL < USBD_NumInterfaces))
			{
        *((__packed U16 *)USBD_EP0Buf) = 0;
        USBD_EP0Data.pData = USBD_EP0Buf;
      }
			else
			{
        return (__FALSE);
      }
      break;
    case REQUEST_TO_ENDPOINT:		//端点
      n = USBD_SetupPacket.wIndexL & 0x8F;
      m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
      if (((USBD_Configuration != 0) || ((n & 0x0F) == 0)) && (USBD_EndPointMask & m))
			{
        *((__packed U16 *)USBD_EP0Buf) = (USBD_EndPointHalt & m) ? 1 : 0;
        USBD_EP0Data.pData = USBD_EP0Buf;
      }
			else
			{
        return (__FALSE);
      }
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqSetClrFeature
*功能描述		:	设置/清除设备特征
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Set/Clear Feature USB Device Request
 *    Parameters:      sc:    0 - Clear, 1 - Set
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqSetClrFeature (U32 sc)
{
  U32 n, m;

  switch (USBD_SetupPacket.bmRequestType.Recipient)	//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_DEVICE:
      if (USBD_SetupPacket.wValue == USB_FEATURE_REMOTE_WAKEUP)		//远程唤醒
			{
        if (sc)			//设置
				{
          USBD_WakeUpCfg(__TRUE);
          USBD_DeviceStatus |=  USB_GETSTATUS_REMOTE_WAKEUP;			//
        }
				else
				{
          USBD_WakeUpCfg(__FALSE);
          USBD_DeviceStatus &= ~USB_GETSTATUS_REMOTE_WAKEUP;
        }
			}
			else
			{
        return (__FALSE);
      }
      break;
    case REQUEST_TO_INTERFACE:
      return (__FALSE);
    case REQUEST_TO_ENDPOINT:
      n = USBD_SetupPacket.wIndexL & 0x8F;
      m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
      if ((USBD_Configuration != 0) && ((n & 0x0F) != 0) && (USBD_EndPointMask & m))
			{
        if (USBD_SetupPacket.wValue == USB_FEATURE_ENDPOINT_STALL)
				{
          if (sc)
					{
            USBD_SetStallEP(n);
            USBD_EndPointHalt |=  m;
          }
					else
					{
            if ((USBD_EndPointStall & m) != 0)
						{
              return (__TRUE);
            }
            USBD_ClrStallEP(n);
            USBD_ReqClrFeature_MSC (n);
            USBD_EndPointHalt &= ~m;
          }
        }
				else
				{
          return (__FALSE);
        }
      }
			else
			{
        return (__FALSE);
      }
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqSetAddress
*功能描述		:	设置设备地址
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Set Address USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqSetAddress (void)
{

  switch (USBD_SetupPacket.bmRequestType.Recipient)		//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_DEVICE:
      USBD_DeviceAddress = 0x80 | USBD_SetupPacket.wValueL;
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqGetDescriptor
*功能描述		:	获取设备描述符
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Get Descriptor USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqGetDescriptor (void)		//获取设备描述符
{
  U8  *pD;
  U32  len, n;

  switch (USBD_SetupPacket.bmRequestType.Recipient) 	//判断接收端口	：D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_DEVICE:														//A设备类请求
      switch (USBD_SetupPacket.wValueH) 							//判断请求类型
			{
				//类型 01 设备描述符	：设备描述符给出了USB设备的一般信息。这包括对设备及所有设备配置起全程作用的信息。一个USB设备只能有一个设备描述符.
				case USB_DEVICE_DESCRIPTOR_TYPE:							
          USBD_EP0Data.pData = (U8 *)USBD_DeviceDescriptor;			//usb_lib.c 设备描述符
          len = USB_DEVICE_DESC_SIZE;														//描述设备描述符的总字节数
          break;
				
        case USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE:			// 06 //设备限定符	：设备限定描述符说明了呢功能进行高速操作的设备在其他速度操作时产生的变化信息.
          if ((!usbd_hs_enable) && (USBD_HighSpeed == __TRUE)) 
					{
            return (__FALSE);  /* High speed request but high-speed not enabled */
          }
          if (USBD_HighSpeed == __FALSE) 
					{
            USBD_EP0Data.pData = (U8 *)USBD_DeviceQualifier;
          }
					else 
					{
            USBD_EP0Data.pData = (U8 *)USBD_DeviceQualifier_HS;
          }
          len = USB_DEVICE_QUALI_SIZE;
          break;
				// 类型 02 配置描述符	：配置描述表给出了一设备配置的信息，描述表包括一个b Configuration Value域，在SetConfiguration(  )请时被用作参数来设置所需配置 .
        case USB_CONFIGURATION_DESCRIPTOR_TYPE:								
          if ((!usbd_hs_enable) && (USBD_HighSpeed == __TRUE)) 
					{
            return (__FALSE);  /* High speed request but high-speed not enabled */
          }
          if (USBD_HighSpeed == __FALSE) 
					{
            pD = (U8 *)USBD_ConfigDescriptor;			//usb_lib.c 配置描述符
          }
					else 
					{
            pD = (U8 *)USBD_ConfigDescriptor_HS;
          }
          for (n = 0; n != USBD_SetupPacket.wValueL; n++) 
					{
            if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength != 0) 
						{
              pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
            }
          }
          if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength == 0) 
					{
            return (__FALSE);
          }
          USBD_EP0Data.pData = pD;
          len = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
          break;
				// 07 其他速度配置：说明了能进行高速操作的设备在其他可能的速度下操作配置.其他速度配置的结构与配置描述符一样.	
        case USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE:			
          if ((!usbd_hs_enable) && (USBD_HighSpeed == __TRUE)) 
					{
            return (__FALSE);  /* High speed request but high-speed not enabled */
          }
          if (USBD_HighSpeed == __FALSE) 
					{
            pD = (U8 *)USBD_OtherSpeedConfigDescriptor;
          } else {
            pD = (U8 *)USBD_OtherSpeedConfigDescriptor_HS;
          }
          for (n = 0; n != USBD_SetupPacket.wValueL; n++) 
					{
            if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength != 0) 
						{
              pD += ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
            }
          }
          if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength == 0) 
					{
            return (__FALSE);
          }
          USBD_EP0Data.pData = pD;
          len = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
          break;
				// 类型03 字符串描述符类型	
        case USB_STRING_DESCRIPTOR_TYPE:			
          pD = (U8 *)USBD_StringDescriptor;		//usb_lib.c->usb_config.c 字符串描述符

#if 0
            // added by sam to send unique id string descriptor
          if (USBD_SetupPacket.wValueL == 3) 
					{
              USBD_EP0Data.pData = get_uid_string_interface();
              len = get_len_string_interface();
              break;
          }
#endif

          for (n = 0; n != USBD_SetupPacket.wValueL; n++) 
					{
            if (((USB_STRING_DESCRIPTOR *)pD)->bLength != 0) 
						{
              pD += ((USB_STRING_DESCRIPTOR *)pD)->bLength;
            }
          }
          if (((USB_STRING_DESCRIPTOR *)pD)->bLength == 0) 
					{
            return (__FALSE);
          }
          USBD_EP0Data.pData = pD;
          len = ((USB_STRING_DESCRIPTOR *)pD)->bLength;
          break;
        default:
          return (__FALSE);
      }
      break;
			
    case REQUEST_TO_INTERFACE:				//B接口类请求
      if (!USBD_ReqGetDescriptor_HID(&pD, &len))		//HID描述符，包括设备描述符，报告描述符，物理特性描述符
        return (__FALSE);
      break;
    default:
      return (__FALSE);
  }

  if (USBD_EP0Data.Count > len)
	{
    USBD_EP0Data.Count = len;
    if (!(USBD_EP0Data.Count & (usbd_max_packet0 - 1)))
			USBD_ZLP = 1;
  }

  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqGetConfiguration
*功能描述		:	获取设备配置信息
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Get Configuration USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqGetConfiguration (void)
{

  switch (USBD_SetupPacket.bmRequestType.Recipient)	//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_DEVICE:
      USBD_EP0Data.pData = &USBD_Configuration;
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqSetConfiguration
*功能描述		:	设置设备配置信息
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Set Configuration USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqSetConfiguration (void)
{				//配置USB
  USB_CONFIGURATION_DESCRIPTOR *pD;
  U32                           alt = 0;
  U32                           n, m;

  switch (USBD_SetupPacket.bmRequestType.Recipient)	//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_DEVICE:

      if (USBD_SetupPacket.wValueL) {
        if ((!usbd_hs_enable) && (USBD_HighSpeed == __TRUE))
				{
          return (__FALSE);  /* High speed request but high-speed not enabled */
        }
        if (USBD_HighSpeed == __FALSE)
				{
          pD = (USB_CONFIGURATION_DESCRIPTOR *)USBD_ConfigDescriptor;
        }
				else
				{
          pD = (USB_CONFIGURATION_DESCRIPTOR *)USBD_ConfigDescriptor_HS;
        }
        while (pD->bLength)
				{
          switch (pD->bDescriptorType)
					{
            case USB_CONFIGURATION_DESCRIPTOR_TYPE:
              if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bConfigurationValue == USBD_SetupPacket.wValueL)
							{
                USBD_Configuration = USBD_SetupPacket.wValueL;			//USB配置完成标志
                USBD_NumInterfaces = ((USB_CONFIGURATION_DESCRIPTOR *)pD)->bNumInterfaces;
                for (n = 0; n < usbd_if_num; n++)
								{
                  USBD_AltSetting[n] = 0;
                }
                for (n = 1; n < 16; n++)
								{
                  if (USBD_EndPointMask & (1 << n))
									{
                    USBD_DisableEP(n);
                  }
                  if (USBD_EndPointMask & ((1 << 16) << n))
									{
                    USBD_DisableEP(n | 0x80);
                  }
                }
                USBD_EndPointMask = 0x00010001;
                USBD_EndPointHalt = 0x00000000;
                USBD_EndPointStall= 0x00000000;
                USBD_Configure(__TRUE);
                if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bmAttributes & USB_CONFIG_POWERED_MASK)
								{
                  USBD_DeviceStatus |=  USB_GETSTATUS_SELF_POWERED;
                }
								else
								{
                  USBD_DeviceStatus &= ~USB_GETSTATUS_SELF_POWERED;
                }
              }
							else
							{
                pD = (USB_CONFIGURATION_DESCRIPTOR *)((U8 *)pD + ((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength);
                continue;
              }
              break;
            case USB_INTERFACE_DESCRIPTOR_TYPE:
              alt = ((USB_INTERFACE_DESCRIPTOR *)pD)->bAlternateSetting;
              break;
            case USB_ENDPOINT_DESCRIPTOR_TYPE:
              if (alt == 0)
							{
                n = ((USB_ENDPOINT_DESCRIPTOR *)pD)->bEndpointAddress & 0x8F;
                m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
                USBD_EndPointMask |= m;
                USBD_ConfigEP((void *)pD);
                USBD_EnableEP(n);
                USBD_ResetEP(n);
              }
              break;
          }
          pD = (USB_CONFIGURATION_DESCRIPTOR *)((U8 *)pD + pD->bLength);
        }
      }
      else
			{
        USBD_Configuration = 0;
        for (n = 1; n < 16; n++)
				{
          if (USBD_EndPointMask & (1 << n))
					{
            USBD_DisableEP(n);
          }
          if (USBD_EndPointMask & ((1 << 16) << n))
					{
            USBD_DisableEP(n | 0x80);
          }
        }
        USBD_EndPointMask  = 0x00010001;
        USBD_EndPointHalt  = 0x00000000;
        USBD_EndPointStall = 0x00000000;
        USBD_Configure(__FALSE);
      }

      if (USBD_Configuration != USBD_SetupPacket.wValueL)
			{
        return (__FALSE);
      }
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqGetInterface
*功能描述		:	获取接口信息
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Get Interface USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqGetInterface (void)
{

  switch (USBD_SetupPacket.bmRequestType.Recipient)		//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_INTERFACE:
      if ((USBD_Configuration != 0) && (USBD_SetupPacket.wIndexL < USBD_NumInterfaces))
			{
        USBD_EP0Data.pData = USBD_AltSetting + USBD_SetupPacket.wIndexL;
      }
			else
			{
        return (__FALSE);
      }
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}

/*******************************************************************************
*函数名			:	USBD_ReqSetInterface
*功能描述		:	设置接口信息
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Set Interface USB Device Request
 *    Parameters:      None
 *    Return Value:    TRUE - Success, FALSE - Error
 */

__inline BOOL USBD_ReqSetInterface (void)
{
  USB_COMMON_DESCRIPTOR *pD;
  U32                    ifn = 0, alt = 0, old = 0, msk = 0;
  U32                    n, m;
  BOOL                   set;

  switch (USBD_SetupPacket.bmRequestType.Recipient)		//判断请求端口 //D[4:0]-接收端：0＝设备，1＝接口，2＝端点，3＝其他，4~31＝保留
	{
    case REQUEST_TO_INTERFACE:
      if (USBD_Configuration == 0) return (__FALSE);
      set = __FALSE;
      if ((!usbd_hs_enable) && (USBD_HighSpeed == __TRUE))
			{
        return (__FALSE);  /* High speed request but high-speed not enabled */
      }
      if (USBD_HighSpeed == __FALSE)
			{
        pD = (USB_COMMON_DESCRIPTOR *)USBD_ConfigDescriptor;
      }
			else
			{
        pD = (USB_COMMON_DESCRIPTOR *)USBD_ConfigDescriptor_HS;
      }
      while (pD->bLength)
			{
        switch (pD->bDescriptorType)
				{
          case USB_CONFIGURATION_DESCRIPTOR_TYPE:
            if (((USB_CONFIGURATION_DESCRIPTOR *)pD)->bConfigurationValue != USBD_Configuration)
						{
              pD = (USB_COMMON_DESCRIPTOR *)((U8 *)pD+((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength);
              continue;
            }
            break;
          case USB_INTERFACE_DESCRIPTOR_TYPE:
            ifn = ((USB_INTERFACE_DESCRIPTOR *)pD)->bInterfaceNumber;
            alt = ((USB_INTERFACE_DESCRIPTOR *)pD)->bAlternateSetting;
            msk = 0;
            if ((ifn == USBD_SetupPacket.wIndexL) && (alt == USBD_SetupPacket.wValueL))
						{
              set = __TRUE;
              old = USBD_AltSetting[ifn];
              USBD_AltSetting[ifn] = (U8)alt;
            }
            break;
          case USB_ENDPOINT_DESCRIPTOR_TYPE:
            if (ifn == USBD_SetupPacket.wIndexL)
						{
              n = ((USB_ENDPOINT_DESCRIPTOR *)pD)->bEndpointAddress & 0x8F;
              m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
              if (alt == USBD_SetupPacket.wValueL)
							{
                USBD_EndPointMask |=  m;
                USBD_EndPointHalt &= ~m;
                USBD_ConfigEP((USB_ENDPOINT_DESCRIPTOR *)pD);
                USBD_EnableEP(n);
                USBD_ResetEP(n);
                msk |= m;
              }
              else if ((alt == old) && ((msk & m) == 0))
							{
                USBD_EndPointMask &= ~m;
                USBD_EndPointHalt &= ~m;
                USBD_DisableEP(n);
              }
            }
           break;
        }
        pD = (USB_COMMON_DESCRIPTOR *)((U8 *)pD + pD->bLength);
      }
      break;
    default:
      return (__FALSE);
  }

  return (set);
}

/*******************************************************************************
*函数名			:	USBD_EndPoint0
*功能描述		:	USB设备端点0事件回调函数
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  USB Device Endpoint 0 Event Callback
 *    Parameters:      event
 *    Return Value:    none
 */

void USBD_EndPoint0 (U32 event)
{
  if (event & USBD_EVT_SETUP) 			//#define USBD_EVT_SETUP	(1 <<  1)  /* Setup Packet */		//Setup包，控制传输
	{					//setup包
    USBD_SetupStage();							//建立阶段,读取建立数据包
    USBD_DirCtrlEP(USBD_SetupPacket.bmRequestType.Dir);		//设置端点方向--空函数
    USBD_EP0Data.Count = USBD_SetupPacket.wLength;       /* Number of bytes to transfer */	//获取字节数

    switch (USBD_SetupPacket.bmRequestType.Type) 		//数据包类型/请求类型	//结构体：USB_SETUP_PACKET->REQUEST_TYPE->Type:D[6:5]-类型：0＝标准，1＝群组，2＝供应商3＝保留
		{	
      case REQUEST_STANDARD:									// 00 标准请求
        switch (USBD_SetupPacket.bRequest)		//特定请求	//结构体：USB_SETUP_PACKET->bRequest：
				{
					case USB_REQUEST_GET_STATUS:				// 00 获取设备状态：这个请求返回指定接收器的状态
							if (!USBD_ReqGetStatus())				//返回结果失败， 
							{			//获取状态---
								goto stall;										//状态未准备好---进入清除状态
							}
							USBD_DataInStage();							//数据阶段(数据准备和发送)
					break;

          case USB_REQUEST_CLEAR_FEATURE:			// 01 清除特性		：这个请求是被用来清除或禁能一个特性。
							if (!USBD_ReqSetClrFeature(0)) 	//设置/清除设备特征
							{
								goto stall;										//未清除特征---进入清除状态
							}
							USBD_StatusInStage();						//数据阶段(数据准备和发送)
						#ifdef __RTX			//---未启用
							if (__rtx)
							{
								if (USBD_RTX_CoreTask)
								{
									usbd_os_evt_set(USBD_EVT_CLR_FEATURE, USBD_RTX_CoreTask);
								}
							}
							else
							{
						#endif
              if (USBD_P_Feature_Event)
							{
                USBD_P_Feature_Event();
              }
						#ifdef __RTX			//---未启用
							}
						#endif
            break;
          case USB_REQUEST_SET_FEATURE:				// 03 设置特性	：这个请求用于设置或使能一个指定的特性.
            if (!USBD_ReqSetClrFeature(1))		//	设置/清除设备特征
						{
              goto stall;
            }
            USBD_StatusInStage();
						#ifdef __RTX			//---未启用
							if (__rtx)
							{
								if (USBD_RTX_CoreTask)
								{
									usbd_os_evt_set(USBD_EVT_SET_FEATURE, USBD_RTX_CoreTask);
								}
							} 
							else
							{
						#endif
              if (USBD_P_Feature_Event)
							{
                USBD_P_Feature_Event();
              }
						#ifdef __RTX			//---未启用
							}
						#endif
            break;

          case USB_REQUEST_SET_ADDRESS:				// 05 设置地址 	：这个请求为所有未来的设备访问设置设备地址
            if (!USBD_ReqSetAddress())
						{
              goto stall;
            }
            USBD_SetAddress(USBD_DeviceAddress & 0x7F, 1);
            USBD_StatusInStage();
            break;

          case USB_REQUEST_GET_DESCRIPTOR:		// 06 取得描述符		：这个请求返回存在的描述符.获取设备描述，包括设备描述符，配置描述符，接口描述符，字符串描述符
            if (!USBD_ReqGetDescriptor())			//获取设备描述符
						{
              goto stall;
            }
            USBD_DataInStage();
            break;

          case USB_REQUEST_SET_DESCRIPTOR:		// 07 设置描述符	：此请求用于更新或添加新的描述表符.
            goto stall;

          case USB_REQUEST_GET_CONFIGURATION:	// 08 取得配置		：这个请求返回当前设备的配置值.
            if (!USBD_ReqGetConfiguration())
						{
              goto stall;
            }
            USBD_DataInStage();
            break;

          case USB_REQUEST_SET_CONFIGURATION:	// 09 设置配置		：这个请求设置设备的配置
            if (!USBD_ReqSetConfiguration())
						{
              goto stall;
            }
            USBD_StatusInStage();
						#ifdef __RTX			//---未启用
							if (__rtx) 
							{
								if (USBD_RTX_CoreTask) 
								{
									usbd_os_evt_set(USBD_EVT_SET_CFG, USBD_RTX_CoreTask);
								}
							} 
							else 
							{
						#endif
              if (USBD_P_Configure_Event)			//USBD_HID_Configure_Event ();
							{	
                USBD_P_Configure_Event();			//USBD_HID_Configure_Event ();
              }
						#ifdef __RTX			//---未启用
							}
						#endif
            break;

          case USB_REQUEST_GET_INTERFACE:	// 0A 取得接口		：这个请求向指定接口返回选中的备用设备.
            if (!USBD_ReqGetInterface())
						{
              goto stall;
            }
            USBD_DataInStage();
            break;

          case USB_REQUEST_SET_INTERFACE:	// 0B 设置接口			：这个请求允许主机为指定的接口选择另一个设置.
            if (!USBD_ReqSetInterface())
						{
              goto stall;
            }
            USBD_StatusInStage();
						#ifdef __RTX			//---未启用
							if (__rtx)
							{
								if (USBD_RTX_CoreTask)
								{
									usbd_os_evt_set(USBD_EVT_SET_IF, USBD_RTX_CoreTask);
								}
							} 
							else
							{
						#endif
              if (USBD_P_Interface_Event)
							{
                USBD_P_Interface_Event();
              }
						#ifdef __RTX			//---未启用
							}
						#endif
            break;

          default:
            goto stall;
        }
        break;  /* end case REQUEST_STANDARD */

      case REQUEST_CLASS:										//群组请求
        switch (USBD_SetupPacket.bmRequestType.Recipient)
				{
          case REQUEST_TO_DEVICE:
            goto stall;                                                  /* not supported */

          case REQUEST_TO_INTERFACE:			//接口类
            if (USBD_EndPoint0_Setup_HID_ReqToIF())
              goto setup_class_ok;
            if (USBD_EndPoint0_Setup_MSC_ReqToIF())
              goto setup_class_ok;
            if (USBD_EndPoint0_Setup_CDC_ReqToIF())			//CDC控制传输请求		Setup Request To Interface
              goto setup_class_ok;
            goto stall;                                                  /* not supported */
            /* end case REQUEST_TO_INTERFACE */

          case REQUEST_TO_ENDPOINT:			//端点类
            goto stall;
            /* end case REQUEST_TO_ENDPOINT */

          default:
            goto stall;
        }
      
setup_class_ok:                                                          /* request finished successfully */
        break;  /* end case REQUEST_CLASS */

      default:
stall:  if ((USBD_SetupPacket.bmRequestType.Dir == REQUEST_HOST_TO_DEVICE) &&
            (USBD_SetupPacket.wLength != 0))
				{
          USBD_SetStallEP(0x00);		//主机到设备//OUT Endpoint//清除标志
        }
				else
				{
          USBD_SetStallEP(0x80);		//设备到主机//IN Endpoint//清除标志
        }
        USBD_EP0Data.Count = 0;
        break;
    }
  }
	//*****************************END OF	USBD_EVT_SETUP*****************************//

  if (event & USBD_EVT_OUT) 				//#define USBD_EVT_OUT	(1 <<  2)  /* OUT Packet                         */
	{			//输出包事件
    if (USBD_SetupPacket.bmRequestType.Dir == REQUEST_HOST_TO_DEVICE)						//数据传输方向：0＝主机至设备，1＝设备至主机				
		{
      if (USBD_EP0Data.Count)										/* still data to receive ? */		//仍接收数据
			{                                          
        USBD_DataOutStage();               			/* receive data */							//接收数据
        if (USBD_EP0Data.Count == 0)						/* data complete ? */						//接收完成
				{                                   
          switch (USBD_SetupPacket.bmRequestType.Type)
					{
            case REQUEST_STANDARD:
              goto stall_i;                                              /* not supported */

            case REQUEST_CLASS:
              switch (USBD_SetupPacket.bmRequestType.Recipient)
							{
                case REQUEST_TO_DEVICE:
                  goto stall_i;                                          /* not supported */

                case REQUEST_TO_INTERFACE:
                  if (USBD_EndPoint0_Out_HID_ReqToIF())
                    goto out_class_ok;
                  if (USBD_EndPoint0_Out_CDC_ReqToIF())									//设置串口,设置波特率等其它参数,返回TRUE---请求成功，返回FALSE---请求失败或者不支持
                    goto out_class_ok;
                  goto stall_i;
                  /* end case REQUEST_TO_INTERFACE */

                case REQUEST_TO_ENDPOINT:
                  goto stall_i;
                  /* end case REQUEST_TO_ENDPOINT */

                default:
                  goto stall_i;
              }
out_class_ok:                                                            /* request finished successfully */
              break; /* end case REQUEST_CLASS */

            default:
stall_i:      USBD_SetStallEP(0x80);			//清除标志
              USBD_EP0Data.Count = 0;
              break;
          }
        }
      }
    } 
		else
		{
      USBD_StatusOutStage();                                             /* receive Acknowledge */
    }
  }
	//*****************************END OF	USBD_EVT_OUT*****************************//

  if (event & USBD_EVT_IN)					//#define USBD_EVT_IN 	(1 <<  3)  /*  IN Packet                         */
	{		//输入包
    if (USBD_SetupPacket.bmRequestType.Dir == REQUEST_DEVICE_TO_HOST)
		{
      if (USBD_EP0Data.Count || USBD_ZLP) USBD_DataInStage();            /* send data */
    }
		else
		{
      if (USBD_DeviceAddress & 0x80)
			{
        USBD_DeviceAddress &= 0x7F;
        USBD_SetAddress(USBD_DeviceAddress, 0);
      }
    }
  }
	//*****************************END OF	USBD_EVT_IN*****************************//

  if (event & USBD_EVT_OUT_STALL)		//#define USBD_EVT_OUT_STALL 	(1 <<  6)  /* OUT Packet - Stalled               */
	{		//输出延迟/等待
    USBD_ClrStallEP(0x00);
  }
	//*****************************END OF	USBD_EVT_OUT_STALL*****************************//

  if (event & USBD_EVT_IN_STALL)		//#define USBD_EVT_IN_STALL    (1 <<  7)  /*  IN Packet - Stalled               */
	{		//输入延迟/等待
    USBD_ClrStallEP(0x80);
  }
	//*****************************END OF	USBD_EVT_IN_STALL*****************************//
}


/*
 *  USB Device Endpoint 0 RTX Task
 *    Parameters:      none
 *    Return Value:    none
 */

#ifdef __RTX
__task void USBD_RTX_EndPoint0 (void)
{

  if (__rtx)
	{
    for (;;)
		{
      usbd_os_evt_wait_or (0xFFFF, 0xFFFF);
      USBD_EndPoint0 (usbd_os_evt_get());
    }
  }
}
#endif
