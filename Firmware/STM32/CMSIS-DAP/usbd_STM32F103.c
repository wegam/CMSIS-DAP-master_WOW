/*----------------------------------------------------------------------------
 *	  RL-ARM - USB
 *----------------------------------------------------------------------------
 *	  Name:	usbd_STM32F103.c
 *	  Purpose: Hardware Layer module for ST STM32F103
 *	  Rev.:	V4.70
 *----------------------------------------------------------------------------
 *	  This code is part of the RealView Run-Time Library.
 *	  Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

/* Double Buffering is not yet supported									  */

#define __STM32

#include "RTL.h"
#include "rl_usb.h"
#include "usbreg.h"
#include "stm32f10x.h"

#include "CMSIS_Conf.H"

#define __NO_USB_LIB_C
#include "usb_config.c"

#define USB_DBL_BUF_EP	0x0000

#define EP_BUF_ADDR		(sizeof(EP_BUF_DSCR) * (USBD_EP_NUM + 1))	/* Endpoint Buf Adr */
// Ptr to EP Buf Desc
EP_BUF_DSCR *pBUF_DSCR = (EP_BUF_DSCR *)USB_PMA_ADDR;
// Endpoint Free Buffer Address
U16 FreeBufAddr;

/**
 * @brief	Reset Endpoint
 * @params	EPNum:	Endpoint Number
 *					EPNum.0..3: Address
 *					EPNum.7:	Dir
 * @return	None
 */
void EP_Reset (U32 EPNum)
{
	U32 num, val;

	num = EPNum & 0x0F;
	val = EPxREG(num);

	if (EPNum & 0x80)
	{	// IN Endpoint
		EPxREG(num) = val & (EP_MASK | EP_DTOG_TX);
	}
	else
	{	// OUT Endpoint
		EPxREG(num) = val & (EP_MASK | EP_DTOG_RX);
	}
}

/**
 * @brief	Set Endpoint Status
 * @perems	EPNum:	Endpoint Number
 *					EPNum.0..3: Address
 *					EPNum.7:	Dir
 *			stat:	New Status
 * @return	None
 */
void EP_Status (U32 EPNum, U32 stat)
{
	U32 num, val;

	num = EPNum & 0x0F;		//
	val = EPxREG(num);
	if (EPNum & 0x80)
	{	/* IN Endpoint						*/	//端点0
		EPxREG(num) = (val ^ (stat & EP_STAT_TX)) & (EP_MASK | EP_STAT_TX);
	}
	else
	{	/* OUT Endpoint						*/	//端点0
		EPxREG(num) = (val ^ (stat & EP_STAT_RX)) & (EP_MASK | EP_STAT_RX);
	}
}

/**
 * @brief	USB Device Interrupt enable
 *			Called by USBD_Init to enable the USB Interrupt
 * @return	None
 */
#ifdef __RTX
void __svc(1) USBD_IntrEna	(void);
void __SVC_1				(void)
{
#else
void		  USBD_IntrEna (void)
{
#endif
	NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
}
/*******************************************************************************
*函数名			:	USBD_Init
*功能描述		:	打开时钟、USB中断和使能USB连接
*输入				: 
*返回值			:	无
*******************************************************************************/
/**
 * @brief	USB Device Initialize Function
 *			Called by the User to initialize USB
 * @return	None
 */
void USBD_Init (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USBEN;			//打开USB时钟

	USBD_IntrEna ();			/* Enable USB Interrupts */	//打开USB中断
//	USB_CONNECTED_SETUP();			//使能USB连接--PNP三极管打开
}

/*
 *  USB Device Connect Function
 *	Called by the User to Connect/Disconnect USB Device
 *	Parameters:	  con:	Connect/Disconnect
 *	Return Value:	None
 */
void USBD_Connect (BOOL con)
{
	if (con)			//连接USB
	{
		CNTR = CNTR_FRES;				/* Force USB Reset						*/		//强制USB复位CNTR_FRES==1
		CNTR = 0;
		ISTR = 0;						/* Clear Interrupt Status				*/			//清除USB中断标志
		CNTR = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM;	/* USB Interrupt Mask	*/

		UsbConnectedOn();			//使能PNP连接
	}
	else					//关闭USB连接
	{
		CNTR = CNTR_FRES | CNTR_PDWN;					/* Switch Off USB Device			  */
		UsbConnectedOff();		//断开PNP连接
	}
}

/*
 *  USB Device Reset Function
 *	Called automatically on USB Device Reset
 *	Return Value:	None
 */
void USBD_Reset (void)
{
	/* Double Buffering is not yet supported	*/

	ISTR = 0;	/* Clear Interrupt Status		*/			//清除中断标志

	CNTR = CNTR_CTRM | CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM			//控制寄存器
#ifdef __RTX
			| ((USBD_RTX_DevTask	!= 0) ? CNTR_ERRM	: 0)
			| ((USBD_RTX_DevTask	!= 0) ? CNTR_PMAOVRM : 0)
			| ((USBD_RTX_DevTask	!= 0) ? CNTR_SOFM	: 0)
			| ((USBD_RTX_DevTask	!= 0) ? CNTR_ESOFM	: 0);
#else
			| ((USBD_P_Error_Event != 0) ? CNTR_ERRM	: 0)
			| ((USBD_P_Error_Event != 0) ? CNTR_PMAOVRM : 0)
			| ((USBD_P_SOF_Event	!= 0) ? CNTR_SOFM	: 0)
			| ((USBD_P_SOF_Event	!= 0) ? CNTR_ESOFM	: 0);
#endif

	FreeBufAddr = EP_BUF_ADDR;			//端点地址

	BTABLE = 0x00;	/* set BTABLE Address		*/

	/* Setup Control Endpoint 0 */
	pBUF_DSCR->ADDR_TX = FreeBufAddr;
	FreeBufAddr += USBD_MAX_PACKET0;

	pBUF_DSCR->ADDR_RX = FreeBufAddr;
	FreeBufAddr += USBD_MAX_PACKET0;

	if (USBD_MAX_PACKET0 > 62)
	{
		pBUF_DSCR->COUNT_RX = ((USBD_MAX_PACKET0 << 5) - 1) | 0x8000;
	}
	else
	{
		pBUF_DSCR->COUNT_RX =	USBD_MAX_PACKET0 << 9;
	}
	EPxREG(0) = EP_CONTROL | EP_RX_VALID;

	DADDR = DADDR_EF | 0;	/* Enable USB Default Address	*/	//使能USB默认地址
}

/*
 *  USB Device Suspend Function
 *	Called automatically on USB Device Suspend
 *	Return Value:	None
 */
void USBD_Suspend (void)
{
	CNTR |= CNTR_FSUSP;		/* Force Suspend	*/		//控制挂起/待机
	CNTR |= CNTR_LPMODE;	/* Low Power Mode	*/		//设置为低功耗模式
}

/*
 *  USB Device Resume Function
 *	Called automatically on USB Device Resume
 *	Return Value:	None
 */
void USBD_Resume (void)
{
	/* Performed by Hardware	*/
}

/*
 *  USB Device Remote Wakeup Function
 *	Called automatically on USB Device Remote Wakeup
 *	Return Value:	None
 */
void USBD_WakeUp (void)
{
	CNTR &= ~CNTR_FSUSP;	/* Clear Suspend	*/		//清除挂起/待机标志
}

/*
 *  USB Device Remote Wakeup Configuration Function
 *	Parameters:	  cfg:	Device Enable/Disable
 *	Return Value:	None
 */
void USBD_WakeUpCfg (BOOL cfg)
{
	/* Not needed */
}

/*
 *  USB Device Set Address Function
 *	Parameters:		adr:	USB Device Address
 *					setup: Called in setup stage (!=0), else after status stage
 *	Return Value:	None
 */
void USBD_SetAddress (U32 adr, U32 setup)
{
	if (setup)
		return;
	DADDR = DADDR_EF | adr;
}

/*
 *  USB Device Configure Function
 *	Parameters:		cfg:	Device Configure/Deconfigure
 *	Return Value:	None
 */
void USBD_Configure (BOOL cfg)
{
	if (cfg == __FALSE)
	{
		FreeBufAddr  = EP_BUF_ADDR;
		FreeBufAddr += 2 * USBD_MAX_PACKET0;	/* reset Buffer address	*/
	}
}


/*
 *  Configure USB Device Endpoint according to Descriptor
 *	Parameters:	  pEPD:  Pointer to Device Endpoint Descriptor
 *	Return Value:	None
 */
void USBD_ConfigEP (USB_ENDPOINT_DESCRIPTOR *pEPD)
{
	/* Double Buffering is not yet supported									*/
	U32 num, val;

	num = pEPD->bEndpointAddress & 0x0F;

	val = pEPD->wMaxPacketSize;
	if (pEPD->bEndpointAddress & USB_ENDPOINT_DIRECTION_MASK)
	{
		(pBUF_DSCR + num)->ADDR_TX = FreeBufAddr;
		val = (val + 1) & ~1;
	}
	else
	{
		(pBUF_DSCR + num)->ADDR_RX = FreeBufAddr;
		if (val > 62)
		{
			val = (val + 31) & ~31;
			(pBUF_DSCR + num)->COUNT_RX = ((val << 5) - 1) | 0x8000;
		}
		else
		{
			val = (val + 1)  & ~1;
			(pBUF_DSCR + num)->COUNT_RX =	val << 9;
		}
	}
	FreeBufAddr += val;

	switch (pEPD->bmAttributes & USB_ENDPOINT_TYPE_MASK)
	{
	case USB_ENDPOINT_TYPE_CONTROL:
		val = EP_CONTROL;
		break;
	case USB_ENDPOINT_TYPE_ISOCHRONOUS:
		val = EP_ISOCHRONOUS;
		break;
	case USB_ENDPOINT_TYPE_BULK:
		val = EP_BULK;
		if (USB_DBL_BUF_EP & (1 << num))
		{
			val |= EP_KIND;
		}
		break;
	case USB_ENDPOINT_TYPE_INTERRUPT:
		val = EP_INTERRUPT;
		break;
	}
	val |= num;
	EPxREG(num) = val;
}

/*
 *  Set Direction for USB Device Control Endpoint
 *	Parameters:		dir:	Out (dir == 0), In (dir <> 0)
 *	Return Value:	None
 */
void USBD_DirCtrlEP (U32 dir)
{
	/* Not needed */
}

/*
 *  Enable USB Device Endpoint
 *	Parameters:		EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *	Return Value:	None
 */
void USBD_EnableEP (U32 EPNum)
{
	EP_Status(EPNum, EP_TX_NAK | EP_RX_VALID);	/* EP is able to receive */
}

/*
 *  Disable USB Endpoint
 *	Parameters:		EPNum: Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *	Return Value:	None
 */
void USBD_DisableEP (U32 EPNum)
{
	EP_Status(EPNum, EP_TX_DIS | EP_RX_DIS);
}

/*
 *  Reset USB Device Endpoint
 *	Parameters:		EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *	Return Value:	None
 */
void USBD_ResetEP (U32 EPNum)
{
	EP_Reset(EPNum);
}

/*******************************************************************************
*函数名			:	USBD_SetStallEP
*功能描述		:	USB设备端点设置摊位
*输入				: 
*返回值			:	无
*******************************************************************************/
/*
 *  Set Stall for USB Device Endpoint
 *	Parameters:		EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *	Return Value:	None
 */
void USBD_SetStallEP (U32 EPNum)
{
	EP_Status(EPNum, EP_TX_STALL | EP_RX_STALL);
}

/*
 *  Clear Stall for USB Device Endpoint
 *	Parameters:		EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *	Return Value:	None
 */
void USBD_ClrStallEP (U32 EPNum)
{
	EP_Reset(EPNum);	/* reset DTog Bits	*/
	EP_Status(EPNum, EP_TX_VALID | EP_RX_VALID);
}


/*
 *  Clear USB Device Endpoint Buffer
 *	Parameters:		EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *	Return Value:	None
 */
void USBD_ClearEPBuf (U32 EPNum)
{
	;
}
/*******************************************************************************
* 函数名		:	USBD_ReadEP
* 功能描述	: 读取端点EPNum并响应主机，数据存入pData，返回接收计数值
* 输入			: void
* 返回值		: void
*******************************************************************************/
/*
 *  Read USB Device Endpoint Data
 *	Parameters:		EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *						pData: Pointer to Data Buffer
 *	Return Value:	Number of bytes read
 */
U32 USBD_ReadEP (U32 EPNum, U8 *pData)
{
	/* Double Buffering is not yet supported	*/
	U32 num, cnt, *pv, n;

	num = EPNum & 0x0F;

	pv  = (U32 *)(USB_PMA_ADDR + 2 * ((pBUF_DSCR + num)->ADDR_RX));
	cnt = (pBUF_DSCR + num)->COUNT_RX & EP_COUNT_MASK;		//计算接收到的数据个数
	for (n = 0; n < (cnt + 1) / 2; n++)
	{
		*((__packed U16 *)pData) = *pv++;			//将接收到的数据存入pData
		pData += 2;
	}
	EP_Status(EPNum, EP_RX_VALID);		//设置端点可用于接收。

	return (cnt);		//返回接收到的数据个数
}


/*
 *  Write USB Device Endpoint Data
 *	Parameters:	  EPNum: Device Endpoint Number
 *						EPNum.0..3: Address
 *						EPNum.7:	Dir
 *					 pData: Pointer to Data Buffer
 *					 cnt:	Number of bytes to write
 *	Return Value:	Number of bytes written
 */

U32 USBD_WriteEP (U32 EPNum, U8 *pData, U32 cnt)
{
	/* Double Buffering is not yet supported									*/
	U32 num, *pv, n;
	U16 statusEP;

	num = EPNum & 0x0F;

	pv  = (U32 *)(USB_PMA_ADDR + 2 * ((pBUF_DSCR + num)->ADDR_TX));
	for (n = 0; n < (cnt + 1) / 2; n++)
	{
		*pv++ = *((__packed U16 *)pData);
		pData += 2;
	}
	(pBUF_DSCR + num)->COUNT_TX = cnt;

	statusEP = EPxREG(num);
	if ((statusEP & EP_STAT_TX) != EP_TX_STALL)
	{	/* do not make EP valid if stalled */
		EP_Status(EPNum, EP_TX_VALID);		//端点可用于发送。
	}

	return (cnt);
}

/*
 *  Get USB Device Last Frame Number
 *	Parameters:		None
 *	Return Value:	Frame Number
 */
U32 USBD_GetFrame (void)
{
	return (FNR & FNR_FN);
}

#ifdef __RTX
U32 LastError;						  /* Last Error						 */

/*
 *  Get USB Last Error Code
 *	Parameters:	  None
 *	Return Value:	Error Code
 */
U32 USBD_GetError (void)
{
	return (LastError);
}
#endif

/*
 *  USB Device Interrupt Service Routine
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	U32 istr, num, val;

	istr = ISTR;									//中断状态寄存器

	if (istr & ISTR_RESET)				//复位中断请求--复位USB数据，//复位串口为默认状态9600
	{	/* USB Reset Request */
		USBD_Reset();						//复位
		usbd_reset_core();			//复位USB的一些数据标志
#ifdef __RTX		//---未定义
		if (USBD_RTX_DevTask)
		{
			isr_evt_set(USBD_EVT_RESET, USBD_RTX_DevTask);
		}
#else
		if (USBD_P_Reset_Event)
		{
			USBD_P_Reset_Event();			//复位串口为默认状态9600
		}
#endif
		ISTR = ~ISTR_RESET;					//清除复位中断标志
	}

	if (istr & ISTR_SUSP)					//挂起模块请求
	{	/* USB Suspend Request */
		USBD_Suspend();			//进入待机状态，设置为低功耗模式
#ifdef __RTX		//---未定义
		if (USBD_RTX_DevTask)
		{
			isr_evt_set(USBD_EVT_SUSPEND, USBD_RTX_DevTask);
		}
#else
		if (USBD_P_Suspend_Event)
		{
			USBD_P_Suspend_Event();			//空函数
		}
#endif
		ISTR = ~ISTR_SUSP;
	}

	if (istr & ISTR_WKUP)					//唤醒请求
	{	/* USB Wakeup */
		USBD_WakeUp();		//清除挂起/待机标志--控制寄存器
#ifdef __RTX		//---未定义
		if (USBD_RTX_DevTask)
		{
			isr_evt_set(USBD_EVT_RESUME,  USBD_RTX_DevTask);
		}
#else
		if (USBD_P_Resume_Event)
		{
			USBD_P_Resume_Event();		//空函数	
		}
#endif
		ISTR = ~ISTR_WKUP;
	}

	if (istr & ISTR_SOF)					//帧首(SOF)中断标志
	{	/* Start of Frame */
#ifdef __RTX		//---未定义
		if (USBD_RTX_DevTask)
		{
			isr_evt_set(USBD_EVT_SOF, USBD_RTX_DevTask);
		}
#else
		if (USBD_P_SOF_Event)
		{
			USBD_P_SOF_Event();			//--帧首
		}
#endif
		ISTR = ~ISTR_SOF;			//清除中断标志
	}

	if (istr & ISTR_PMAOVR)				//数据溢出/分组缓冲区溢出
	{
#ifdef __RTX		//---未定义
		LastError = 2;
		if (USBD_RTX_DevTask)
		{	/* PMA Over/underrun */
			isr_evt_set(USBD_EVT_ERROR, USBD_RTX_DevTask);
		}
#else
		if (USBD_P_Error_Event)
		{
			USBD_P_Error_Event(2);		//断开连接，重启设备--参数无用
		}
#endif
		ISTR = ~ISTR_PMAOVR;		//清除标志
	}

	if (istr & ISTR_ERR)					//错误，无应答/CRC错误/数据位错误或者帧格式错误
	{	/* Error: No Answer, CRC Error, Bit Stuff Error, Frame Format Error */
#ifdef __RTX		//---未定义
		LastError = 1;
		if (USBD_RTX_DevTask)
		{
			isr_evt_set(USBD_EVT_ERROR, USBD_RTX_DevTask);
		}
#else
		if (USBD_P_Error_Event)
		{
			USBD_P_Error_Event(1);	//USB连接时错误断开连接，重启设备--参数无用
		}
#endif
		ISTR = ~ISTR_ERR;		//清除错误标志
	}
	if (istr & ISTR_ESOF)					//期望帧首标识位 (Expected start of frame)
	{	
//		//此位在USB模块未收到期望的SOF分组时由硬件置位。主机应该每毫秒都发送SOF分组，
//		//但如果USB模块没有收到，挂起定时器将触发此中断。如果连续发生3次ESOF中断，
//		//也就是连续3次未收到SOF分组，将产生SUSP中断。即使在挂起定时器未被锁定时发生SOF
//		//分组丢失，此位也会被置位。
//		//此位应用程序可读可写，但只有写0有效，写1无效。	
		ISTR = ~ISTR_ESOF;			//清除错误标志--
//     _SetISTR((u16)CLR_ESOF);
     /* resume handling timing is made with ESOFs */
//     Resume(RESUME_ESOF); 	/* request without change of the machine state */

//		 #ifdef ESOF_CALLBACK
//				 ESOF_Callback();
//		 #endif
	}

	if((istr = ISTR) & ISTR_CTR)		//正确的传输 (Correct transfer)此位在端点正确完成一次数据传输后由硬件置位。
	{	/* Endpoint Interrupts */
		ISTR = ~ISTR_CTR;									//清除中断标志		

		num = istr & ISTR_EP_ID;					//获取端点号

		val = EPxREG(num);								//读取端点寄存器
		if (val & EP_CTR_RX)							//正确接收标志位 (Correct Transfer for reception)
		{
						EPxREG(num) = val & ~EP_CTR_RX & EP_MASK;		//清除端点相关标志
			#ifdef __RTX		//---未定义
						if (USBD_RTX_EPTask[num])
						{
							isr_evt_set((val & EP_SETUP) ? USBD_EVT_SETUP : USBD_EVT_OUT, USBD_RTX_EPTask[num]);
						}
			#else
						if (USBD_P_EP[num])				//判断有无相应端点处理程序然后进入相应端点处理程序
						{
							USBD_P_EP[num]((val & EP_SETUP) ? USBD_EVT_SETUP : USBD_EVT_OUT);			//传输事件类型
						}
						else
						{
//							while(1);
						}
			#endif
		}
		if (val & EP_CTR_TX)							//正确发送标志位 (Correct transfer for transmission)
		{
						EPxREG(num) = val & ~EP_CTR_TX & EP_MASK;		//清除端点相关标志
			#ifdef __RTX		//---未定义
						if (USBD_RTX_EPTask[num])
						{
							isr_evt_set(USBD_EVT_IN,  USBD_RTX_EPTask[num]);
						}
			#else
						if (USBD_P_EP[num])				//判断有无相应端点处理程序然后进入相应端点处理程序
						{
							USBD_P_EP[num](USBD_EVT_IN);	//#define USBD_EVT_IN          (1 <<  3)  /*  IN Packet                         */
						}
						else
						{
							while(1);
						}
			#endif
		}
	}
	else
	{
//		while(1);
	}
}
