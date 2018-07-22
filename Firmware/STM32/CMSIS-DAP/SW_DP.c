/******************************************************************************
 * @file	 SW_DP.c
 * @brief	CMSIS-DAP SW DP I/O
 * @version  V1.00
 * @date	 31. May 2012
 *
 * @note
 * Copyright (C) 2012 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include "CMSIS_Conf.H"
#include "DAP.h"
#include "SW_DP.h"

#include "oled.h"


// Generate SWJ Sequence	//连接请求--数据高电平，给51个时钟，总线复位
//	count:  sequence bit count
//	data:	pointer to sequence bit data
//	return: none
#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
void SWJ_Sequence (uint32_t count, uint8_t *data)
{
	uint8_t val;
	uint8_t n = 0;

	DEBUG("DATA:");
	while (count != 0)
	{
		count--;
		if (n == 0)
		{
			val = *data++;
			DEBUG(" %02X", val);
			n = 8;
		}
		if (val & 1)
		{
			PIN_SWDIO_TMS_SET();
		}
		else
		{
			SWD_WOW_DIOL();
		}
		SW_CLOCK_CYCLE();
		val >>= 1;
		n--;
	}
	DEBUG("\n");
}
#endif


#if (DAP_SWD != 0)

// SWD Transfer I/O
//	request: A[3:2] RnW APnDP
//	data:	DATA[31:0]
//	return:  ACK[2:0]
//#define SWD_TransferFunction(speed)	/*SWD读写数据操作*/																																
uint8_t SWD_Transfer(uint8_t request, uint32_t *data)																													
{																																																											
	uint8_t ack;																																																				
	uint8_t bit;																																																				
	uint32_t val;																																																				
	uint8_t parity;																																																			
	uint8_t n;																																																					
																																																											
	/* Packet Request */																																																
	parity = 0;						//奇偶校验																																																			
	SW_WRITE_BIT(1);			/* Start Bit *//*起始位：值为1*/																																
																																																											
	bit = request >> 0;																																																	
	SW_WRITE_BIT(bit);		/* APnDP Bit *//*端口：表示访问的是DPACC-调试端口访问（值为0）还是APACC-数据端口访问（值为1）*/	//APACC(Access Port to access)	
	parity += bit;																																																			
																																																											
	bit = request >> 1;																																																	
	SW_WRITE_BIT(bit);		/* RnW Bit *//*读/写：表示是读访问还是写访问，0-写访问，1-读访问*/																
	parity += bit;	

	//_________________________________ADDR[2:3]
	//ADDR[2:3]说明：由A[3:2]定义32位调试接口寄存器地址
	//	0X00-00	：	调试端口ID寄存器	（DPIDR/IDCODE)---只读
	//
	//	0X04-01	：	DP SELECT寄存器--用来选择当前的访问端口和有效的4字长寄存器窗口
	//							- Bits31:24：APSEL 选择当前AP
	//							- Bits23:8：未定义
	//							- Bits7:4：APBANKSEL：在当前AP上选择4字长寄存器窗口
	//							- Bits3:0：未定义
	//
	//	0X08-10	：	DP CTRL/STAT 寄存器
	//							- 请求一个系统或调试的上电操作
	//							- 配置AP访问的操作模式
	//							- 控制比较，校验操作
	//							- 读取一些状态位(溢出，上电响应)
	//							
	//	0X0C-11	：	DP RDBUFF寄存器--用来使调试器获得前一次操作的最终结果(不用再请求一个新的JTAG-DP操作)
																																																											
	bit = request >> 2;																																																	
	SW_WRITE_BIT(bit);		/* A2 Bit *//*介绍参见下一条内容说明*/	
	parity += bit;																																						
																																																										
	bit = request >> 3;																																																
	SW_WRITE_BIT(bit);		/* A3 Bit *//*ADDR[2:3]:给出DP或者AP寄存器的地址域ADDR[3:2],低位在前*/												
	parity += bit;																																																			
																																																											
	SW_WRITE_BIT(parity);	/* Parity Bit */	/*为前面数据包提供单一的奇偶校验*/																					
	SW_WRITE_BIT(0);			/* Stop Bit */		/*停止位，在同步的SWD协议中，该位始终为0*/																				
	SW_WRITE_BIT(1);			/* Park Bit */		/*停止位，*/																																						
																																																										
	/* Turnaround */																																																		
	PIN_SWDIO_OUT_DISABLE();		/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/														
	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															
	{																																																								
		SW_CLOCK_CYCLE();																																																	
	}																																																										
																																																												
	/* Acknowledge response *//*一个3位的值对主机的响应，低位在前出现*/																											
	SW_READ_BIT(bit);																																																		
	ack  = bit << 0;																																																		
																																																										
	SW_READ_BIT(bit);																																																	
	ack |= bit << 1;																																																	
																																																								
	SW_READ_BIT(bit);																																														
	ack |= bit << 2;																																														
	/*判断应答是否成功*/																																											
	if (ack == DAP_TRANSFER_OK)		/*应答成功*/		/*#define DAP_TRANSFER_OK		(1 << 0)*/											
	{	/* OK response */									/*应答成功*/																													
		/* Data transfer */								/*数据传输*/																													
		if (request & DAP_TRANSFER_RnW)		/*读数据请求*/																										
		{	/* Read data */									/*读数据**/																											
			val = 0;																																											
			parity = 0;																																									
			for (n = 32; n; n--)						/*读32位数据*/																						
			{																																													
				SW_READ_BIT(bit);	/* Read RDATA[0:31] */									
				parity += bit;																					
				val >>= 1;																							
				val  |= bit << 31;																				
			}																														
			SW_READ_BIT(bit);		/* Read Parity */	/*读奇偶校验*/			
			if ((parity ^ bit) & 1)		/*奇偶校验*/										
			{																														
				ack = DAP_TRANSFER_ERROR;	/*校验错误*/											
			}																																																				
			if (data)																																																	
				*data = val;		/*更新读取的数据*/																																		
			/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/						
			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																				
			{																																												
				SW_CLOCK_CYCLE();																																			
			}																																													
																																													
			PIN_SWDIO_OUT_ENABLE();		/*SWD_DIO引脚功能修改为输出*/															
		}																																											
		else													/*写数据请求*/																						
		{																																												
			/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/					
			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																		
			{																																											
				SW_CLOCK_CYCLE();																																			
			}																																													
																																																		
			PIN_SWDIO_OUT_ENABLE();	/*SWD_DIO引脚功能修改为输出*/																	
			/* Write data */																																	
			val = *data;						/*待写入数据*/	
//			OLED_ShowNum(0,4,val,10,16);//显示ASCII字符的码值			
			parity = 0;							/*清零奇偶校验*/																			
			for (n = 32; n; n--) 		/*写32位数据*/																					
			{																																								
				SW_WRITE_BIT(val);	/* Write WDATA[0:31] */																			
				parity += val;																																		
				val >>= 1;																																				
			}																																										
			SW_WRITE_BIT(parity);	/* Write Parity Bit */	/*写奇偶校验*/												
		}																																											
		/* Idle cycles */				/* 空闲周期 */																								
		n = DAP_Data.transfer.idle_cycles;																											
		if (n != 0)																																							
		{																																															
			SWD_WOW_DIO=0;																														
			for (; n != 0; n--)																															
			{																																						
				SW_CLOCK_CYCLE();																														
			}																																									
		}																																											
		SWD_WOW_DIO=1;																																		
		return (ack);		/*返回应答状态退出此函数*/																			
	}																																										
	/*应答非OK--还不能进行数据传输，需要等待或者重试*/														
	if (ack == DAP_TRANSFER_WAIT || ack == DAP_TRANSFER_FAULT)														
	{																																											
		/* WAIT or FAULT response */																														
		if (DAP_Data.swd_conf.data_phase && (request & DAP_TRANSFER_RnW) != 0)							
		{																																													
			for (n = 32+1; n; n--)																																						
			{																																														
				SW_CLOCK_CYCLE();	/* Dummy Read RDATA[0:31] + Parity */																	
			}																																													
		}																																															
		/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/								
		for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																								
		{																																																			
			SW_CLOCK_CYCLE();																																				
		}																																																	
																																																		
		PIN_SWDIO_OUT_ENABLE();																																	
		if (DAP_Data.swd_conf.data_phase && (request & DAP_TRANSFER_RnW) == 0)										
		{																																												
			SWD_WOW_DIO=0;																																				
			for (n = 32 + 1; n != 0; n--)																																		
			{																																											
				SW_CLOCK_CYCLE();	/* Dummy Write WDATA[0:31] + Parity */											
			}																																										
		}																																										
		SWD_WOW_DIO=1;																																		
		return (ack);																																				
	}																																										
																																												
	/* Protocol error */																																		
	for (n = DAP_Data.swd_conf.turnaround + 32 + 1; n != 0; n--)																		
	{																																												
		SW_CLOCK_CYCLE();	/* Back off data phase */																				
	}																																											
																																												
	SWD_WOW_DIO=1;																																		
	return (ack);																																							
}


#undef  PIN_DELAY
#define PIN_DELAY()		PIN_DELAY_FAST()
//SWD_TransferFunction(Fast);

#undef  PIN_DELAY
#define PIN_DELAY()		PIN_DELAY_SLOW(DAP_Data.clock_delay)
//SWD_TransferFunction(Slow);

// SWD Transfer I/O		//SWD数据读写
//	request: A[3:2] RnW APnDP
//	data:	DATA[31:0]
//	return:  ACK[2:0]	//返回3位应答
//uint8_t  SWD_Transfer(uint8_t request, uint32_t *data)
//{
//	if (DAP_Data.fast_clock)
//		return SWD_TransferFast(request, data);
//	else
//		return SWD_TransferSlow(request, data);		//uint8_t SWD_Transfer##speed (uint8_t request, uint32_t *data)
//}


//------------------------------------------原文件备份----------------------------------------------------

//#include "DAP_config.h"
//#include "DAP.h"
//#include "SW_DP.h"



//// SW Macros

//#define PIN_SWCLK_SET()		PIN_SWCLK_TCK_SET()
//#define PIN_SWCLK_CLR()		PIN_SWCLK_TCK_CLR()

//#define SW_CLOCK_CYCLE()		\
//		PIN_SWCLK_CLR();		\
//		PIN_DELAY();			\
//		PIN_SWCLK_SET();		\
//		PIN_DELAY()

//#define SW_WRITE_BIT(bit)		\
//		PIN_SWDIO_OUT(bit);		\
//		PIN_SWCLK_CLR();		\
//		PIN_DELAY();			\
//		PIN_SWCLK_SET();		\
//		PIN_DELAY()

//#define SW_READ_BIT(bit)		\
//		PIN_SWCLK_CLR();		\
//		PIN_DELAY();			\
//		bit = PIN_SWDIO_IN();	\
//		PIN_SWCLK_SET();		\
//		PIN_DELAY()

//#define PIN_DELAY()		PIN_DELAY_SLOW(DAP_Data.clock_delay)

//// Generate SWJ Sequence	//连接请求--数据高电平，给51个时钟，总线复位
////	count:  sequence bit count
////	data:	pointer to sequence bit data
////	return: none
//#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
//void SWJ_Sequence (uint32_t count, uint8_t *data)
//{
//	uint8_t val;
//	uint8_t n = 0;

//	DEBUG("DATA:");
//	while (count != 0)
//	{
//		count--;
//		if (n == 0)
//		{
//			val = *data++;
//			DEBUG(" %02X", val);
//			n = 8;
//		}
//		if (val & 1)
//		{
//			PIN_SWDIO_TMS_SET();
//		}
//		else
//		{
//			SWD_WOW_DIOL();
//		}
//		SW_CLOCK_CYCLE();
//		val >>= 1;
//		n--;
//	}
//	DEBUG("\n");
//}
//#endif


//#if (DAP_SWD != 0)

//// SWD Transfer I/O
////	request: A[3:2] RnW APnDP
////	data:	DATA[31:0]
////	return:  ACK[2:0]
//#define SWD_TransferFunction(speed)	/*SWD读写数据操作*/																																\
//uint8_t SWD_Transfer##speed (uint8_t request, uint32_t *data)																													\
//{																																																											\
//	uint8_t ack;																																																				\
//	uint8_t bit;																																																				\
//	uint32_t val;																																																				\
//	uint8_t parity;																																																			\
//	uint8_t n;																																																					\
//																																																											\
//	/* Packet Request */																																																\
//	parity = 0;																																																					\
//	SW_WRITE_BIT(1);			/* Start Bit *//*起始位：值为1*/																																\
//																																																											\
//	bit = request >> 0;																																																	\
//	SW_WRITE_BIT(bit);		/* APnDP Bit *//*端口：表示访问的是DPACC-调试端口访问（值为0）还是APACC-数据端口访问（值为1）*/		\
//	parity += bit;																																																			\
//																																																											\
//	bit = request >> 1;																																																	\
//	SW_WRITE_BIT(bit);		/* RnW Bit *//*读/写：表示是读访问还是写访问，0-写访问，1-读访问*/																\
//	parity += bit;																																																			\
//																																																											\
//	bit = request >> 2;																																																	\
//	SW_WRITE_BIT(bit);		/* A2 Bit *//*介绍参见下一条内容说明*/																													\
//	parity += bit;																																																			\
//																																																											\
//	bit = request >> 3;																																																	\
//	SW_WRITE_BIT(bit);		/* A3 Bit *//*ADDR[2:3]:给出DP或者AP寄存器的地址域ADDR[3:2],低位在前*/													\
//	parity += bit;																																																			\
//																																																											\
//	SW_WRITE_BIT(parity);	/* Parity Bit *//*为前面数据包提供单一的奇偶校验*/																							\
//	SW_WRITE_BIT(0);			/* Stop Bit *//*停止位，在同步的SWD协议中，该位始终为0*/																						\
//	SW_WRITE_BIT(1);			/* Park Bit */																																									\
//																																																											\
//	/* Turnaround */																																																		\
//	PIN_SWDIO_OUT_DISABLE();		/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/																\
//	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																																	\
//	{																																																										\
//		SW_CLOCK_CYCLE();																																																	\
//	}																																																										\
//																																																											\
//	/* Acknowledge response *//*一个3位的值对主机的响应，低位在前出现*/																										\
//	SW_READ_BIT(bit);																																																		\
//	ack  = bit << 0;																																																		\
//																																																											\
//	SW_READ_BIT(bit);																																																		\
//	ack |= bit << 1;																																																		\
//																																																											\
//	SW_READ_BIT(bit);																																																		\
//	ack |= bit << 2;																																																		\
//	/*判断应答是否成功*/																																																	\
//	if (ack == DAP_TRANSFER_OK)		/*应答成功*/		/*#define DAP_TRANSFER_OK		(1 << 0)*/																	\
//	{	/* OK response */									/*应答成功*/																																			\
//		/* Data transfer */								/*数据传输*/																																			\
//		if (request & DAP_TRANSFER_RnW)		/*读数据请求*/																																		\
//		{	/* Read data */									/*读数据**/																																			\
//			val = 0;																																																				\
//			parity = 0;																																																			\
//			for (n = 32; n; n--)						/*读32位数据*/																																		\
//			{																																																								\
//				SW_READ_BIT(bit);	/* Read RDATA[0:31] */																																			\
//				parity += bit;																																																\
//				val >>= 1;																																																		\
//				val  |= bit << 31;																																														\
//			}																																																								\
//			SW_READ_BIT(bit);		/* Read Parity */	/*读奇偶校验*/																															\
//			if ((parity ^ bit) & 1)		/*奇偶校验*/																																						\
//			{																																																								\
//				ack = DAP_TRANSFER_ERROR;	/*校验错误*/																																					\
//			}																																																								\
//			if (data)																																																				\
//				*data = val;		/*更新读取的数据*/																																							\
//			/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/																			\
//			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															\
//			{																																																								\
//				SW_CLOCK_CYCLE();																																															\
//			}																																																								\
//																																																											\
//			PIN_SWDIO_OUT_ENABLE();		/*SWD_DIO引脚功能修改为输出*/																													\
//		}																																																									\
//		else													/*写数据请求*/																																				\
//		{																																																									\
//			/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/																			\
//			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															\
//			{																																																								\
//				SW_CLOCK_CYCLE();																																															\
//			}																																																								\
//																																																											\
//			PIN_SWDIO_OUT_ENABLE();	/*SWD_DIO引脚功能修改为输出*/																														\
//			/* Write data */																																																\
//			val = *data;						/*待写入数据*/																																						\
//			parity = 0;							/*清零奇偶校验*/																																					\
//			for (n = 32; n; n--) 		/*写32位数据*/																																						\
//			{																																																								\
//				SW_WRITE_BIT(val);	/* Write WDATA[0:31] */																																		\
//				parity += val;																																																\
//				val >>= 1;																																																		\
//			}																																																								\
//			SW_WRITE_BIT(parity);	/* Write Parity Bit */	/*写奇偶校验*/																											\
//		}																																																									\
//		/* Idle cycles */				/* 空闲周期 */																																							\
//		n = DAP_Data.transfer.idle_cycles;																																								\
//		if (n != 0)																																																				\
//		{																																																									\
//			PIN_SWDIO_OUT(0);																																																\
//			for (; n != 0; n--)																																															\
//			{																																																								\
//				SW_CLOCK_CYCLE();																																															\
//			}																																																								\
//		}																																																									\
//		PIN_SWDIO_OUT(1);																																																	\
//		return (ack);		/*返回应答状态退出此函数*/																																					\
//	}																																																										\
//	/*应答非OK--还不能进行数据传输，需要等待或者重试*/																																			\
//	if (ack == DAP_TRANSFER_WAIT || ack == DAP_TRANSFER_FAULT)																													\
//	{																																																										\
//		/* WAIT or FAULT response */																																											\
//		if (DAP_Data.swd_conf.data_phase && (request & DAP_TRANSFER_RnW) != 0)																						\
//		{																																																									\
//			for (n = 32+1; n; n--)																																													\
//			{																																																								\
//				SW_CLOCK_CYCLE();	/* Dummy Read RDATA[0:31] + Parity */																												\
//			}																																																								\
//		}																																																									\
//		/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/																				\
//		for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																																\
//		{																																																									\
//			SW_CLOCK_CYCLE();																																																\
//		}																																																									\
//																																																											\
//		PIN_SWDIO_OUT_ENABLE();																																														\
//		if (DAP_Data.swd_conf.data_phase && (request & DAP_TRANSFER_RnW) == 0)																						\
//		{																																																									\
//			PIN_SWDIO_OUT(0);																																																\
//			for (n = 32 + 1; n != 0; n--)																																										\
//			{																																																								\
//				SW_CLOCK_CYCLE();	/* Dummy Write WDATA[0:31] + Parity */																											\
//			}																																																								\
//		}																																																									\
//		PIN_SWDIO_OUT(1);																																																	\
//		return (ack);																																																			\
//	}																																																										\
//																																																											\
//	/* Protocol error */																																																\
//	for (n = DAP_Data.swd_conf.turnaround + 32 + 1; n != 0; n--)																												\
//	{																																																										\
//		SW_CLOCK_CYCLE();	/* Back off data phase */																																				\
//	}																																																										\
//																																																											\
//	PIN_SWDIO_OUT(1);																																																		\
//	return (ack);																																																				\
//}


//#undef  PIN_DELAY
//#define PIN_DELAY()		PIN_DELAY_FAST()
//SWD_TransferFunction(Fast);

//#undef  PIN_DELAY
//#define PIN_DELAY()		PIN_DELAY_SLOW(DAP_Data.clock_delay)
//SWD_TransferFunction(Slow);

//// SWD Transfer I/O		//SWD数据读写
////	request: A[3:2] RnW APnDP
////	data:	DATA[31:0]
////	return:  ACK[2:0]	//返回3位应答
//uint8_t  SWD_Transfer(uint8_t request, uint32_t *data)
//{
//	if (DAP_Data.fast_clock)
//		return SWD_TransferFast(request, data);
//	else
//		return SWD_TransferSlow(request, data);		//uint8_t SWD_Transfer##speed (uint8_t request, uint32_t *data)
//}

#endif  /* (DAP_SWD != 0) */
