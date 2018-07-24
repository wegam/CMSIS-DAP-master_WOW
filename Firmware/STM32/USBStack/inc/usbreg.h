/*----------------------------------------------------------------------------
 *      RL-ARM - USB
 *----------------------------------------------------------------------------
 *      Name:    usbreg.h
 *      Purpose: Hardware Layer Definitions for ST STM32F10x
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __USBREG_H
#define __USBREG_H


#define REG(x)  (*((volatile unsigned int *)(x)))

#define USB_BASE_ADDR   0x40005C00  /* USB Registers Base Address */
#define USB_PMA_ADDR    0x40006000  /* USB Packet Memory Area Address */


/* Common Registers */
#define CNTR    REG(USB_BASE_ADDR + 0x40)   /* Control Register */
#define ISTR    REG(USB_BASE_ADDR + 0x44)   /* Interrupt Status Register */
#define FNR     REG(USB_BASE_ADDR + 0x48)   /* Frame Number Register */
#define DADDR   REG(USB_BASE_ADDR + 0x4C)   /* Device Address Register */
#define BTABLE  REG(USB_BASE_ADDR + 0x50)   /* Buffer Table Address Register */

/* CNTR: Control Register Bit Definitions */
#define CNTR_CTRM       0x8000      /* Correct Transfer Interrupt Mask */
#define CNTR_PMAOVRM    0x4000      /* Packet Memory Aerea Over/underrun Interrupt Mask */
#define CNTR_ERRM       0x2000      /* Error Interrupt Mask */
#define CNTR_WKUPM      0x1000      /* Wake-up Interrupt Mask */
#define CNTR_SUSPM      0x0800      /* Suspend Mode Interrupt Mask  */
#define CNTR_RESETM     0x0400      /* USB Reset Interrupt Mask   */
#define CNTR_SOFM       0x0200      /* Start of Frame Interrupt Mask */
#define CNTR_ESOFM      0x0100      /* Expected Start of Frame Interrupt Mask */
#define CNTR_RESUME     0x0010      /* Resume Request */
#define CNTR_FSUSP      0x0008      /* Force Suspend */
#define CNTR_LPMODE     0x0004      /* Low-power Mode */
#define CNTR_PDWN       0x0002      /* Power Down */
#define CNTR_FRES       0x0001      /* Force USB Reset */	//强制USB复位

/* ISTR: Interrupt Status Register Bit Definitions */					//USB中断状态寄存器(USB_ISTR)
#define ISTR_CTR        0x8000      /* Correct Transfer */										//正确的传输 (Correct transfer)此位在端点正确完成一次数据传输后由硬件置位。
#define ISTR_PMAOVR     0x4000      /* Packet Memory Aerea Over/underrun */		//数据溢出/分组缓冲区溢出
#define ISTR_ERR        0x2000      /* Error */																//错误，无应答/CRC错误/数据位错误或者帧格式错误
#define ISTR_WKUP       0x1000      /* Wake-up */															//唤醒请求
#define ISTR_SUSP       0x0800      /* Suspend Mode */												//挂起模块请求
#define ISTR_RESET      0x0400      /* USB Reset */														//USB复位请求
#define ISTR_SOF        0x0200      /* Start of Frame */											//帧首标志
#define ISTR_ESOF       0x0100      /* Expected Start of Frame */							//期望帧首标识位 (Expected start of frame)
#define ISTR_DIR        0x0010      /* Direction of Transaction */						//传输方向
#define ISTR_EP_ID      0x000F      /* EndPoint Identifier */									//端点ID

/* FNR: Frame Number Register Bit Definitions */
#define FNR_RXDP        0x8000      /* D+ Data Line Status */
#define FNR_RXDM        0x4000      /* D- Data Line Status */
#define FNR_LCK         0x2000      /* Locked */
#define FNR_LSOF        0x1800      /* Lost SOF */
#define FNR_FN          0x07FF      /* Frame Number */

/* DADDR: Device Address Register Bit Definitions */
#define DADDR_EF        0x0080      /* Enable Function */
#define DADDR_ADD       0x007F      /* Device Address */


/* EndPoint Registers */		//端点寄存器
#define EPxREG(x)       REG(USB_BASE_ADDR + 4*(x))

/* EPxREG: EndPoint Registers Bit Definitions */								//端点寄存器
#define EP_CTR_RX       0x8000      /* Correct RX Transfer */		//正确接收标志位 (Correct Transfer for reception)
#define EP_DTOG_RX      0x4000      /* RX Data Toggle */				//用于数据接收的数据翻转位 (Data Toggle, for reception transfers)
#define EP_STAT_RX      0x3000      /* RX Status */							//用于数据接收的状态位 (Status bits, for reception transfers)			查看	EP_STAT_RX: RX Status
#define EP_SETUP        0x0800      /* EndPoint Setup */				//SETUP分组传输完成标志位 (Setup transaction completed)
#define EP_TYPE         0x0600      /* EndPoint Type */					//端点类型位 (Endpoint type),查看	EP_TYPE: EndPoint Types
#define EP_KIND         0x0100      /* EndPoint Kind */					//端点特殊类型位 (Endpoint kind)	查看	EP_KIND: EndPoint Kind
#define EP_CTR_TX       0x0080      /* Correct TX Transfer */		//正确发送标志位 (Correct transfer for transmission)
#define EP_DTOG_TX      0x0040      /* TX Data Toggle */				//发送数据翻转位 (Data Toggle, for transmission transfers)
#define EP_STAT_TX      0x0030      /* TX Status */							//用于发送数据的状态位 (Status bits, for transmission transfers)	查看	EP_STAT_TX: TX Status
#define EP_EA           0x000F      /* EndPoint Address */			//端点地址 (Endpoint address)

/* EndPoint Register Mask (No Toggle Fields) */
#define EP_MASK         (EP_CTR_RX|EP_SETUP|EP_TYPE|EP_KIND|EP_CTR_TX|EP_EA)

/* EP_TYPE: EndPoint Types */
#define EP_BULK         0x0000      /* BULK EndPoint */					//批量端点
#define EP_CONTROL      0x0200      /* CONTROL EndPoint */			//控制端点
#define EP_ISOCHRONOUS  0x0400      /* ISOCHRONOUS EndPoint */	//同步端点
#define EP_INTERRUPT    0x0600      /* INTERRUPT EndPoint */		//中断端点

/* EP_KIND: EndPoint Kind */
#define EP_DBL_BUF      EP_KIND     /* Double Buffer for Bulk Endpoint */		//DBL_BUF：双缓冲端点
#define EP_STATUS_OUT   EP_KIND     /* Status Out for Control Endpoint */		//STATUS_OUT

/* EP_STAT_TX: TX Status */
#define EP_TX_DIS       0x0000      /* Disabled */		//端点忽略所有的发送请求。
#define EP_TX_STALL     0x0010      /* Stalled */			//端点以STALL分组响应所有的发送请求。
#define EP_TX_NAK       0x0020      /* NAKed */				//端点以NAK分组响应所有的发送请求。
#define EP_TX_VALID     0x0030      /* Valid */				//端点可用于发送。

/* EP_STAT_RX: RX Status */
#define EP_RX_DIS       0x0000      /* Disabled */		//端点忽略所有的接收请求。
#define EP_RX_STALL     0x1000      /* Stalled */			//端点以STALL分组响应所有的接收请求。
#define EP_RX_NAK       0x2000      /* NAKed */				//端点以NAK分组响应所有的接收请求。
#define EP_RX_VALID     0x3000      /* Valid */				//端点可用于接收。


/* Endpoint Buffer Descriptor */
typedef struct _EP_BUF_DSCR {
  U32 ADDR_TX;
  U32 COUNT_TX;
  U32 ADDR_RX;
  U32 COUNT_RX;
} EP_BUF_DSCR;

#define EP_ADDR_MASK    0xFFFE      /* Address Mask */
#define EP_COUNT_MASK   0x03FF      /* Count Mask */


#endif  /* __USBREG_H */
