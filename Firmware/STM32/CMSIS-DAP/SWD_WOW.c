#include "SWD_WOW.h"

#include "CMSIS_Conf.H"
#include "DAP.h"

//#include "STM32F10x_BitBand.h"

/*1,所有的SWD 传输都是LSB 在先*/

/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_DELAY(uint32_t time)
{
//		uint32_t	time=200;
	uint32_t	temp=time;
	while(temp--);
//	__NOP();
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_DISABLE()
{
	PIN_SWDIO_OUT_DISABLE();
	PIN_SWCLK_OUT_DISABLE();
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_ENABLE()
{
	PIN_SWDIO_OUT_ENABLE();
	PIN_SWCLK_OUT_ENABLE();	
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_CLOCK_CYCLE()
{
	SWD_WOW_CLKL();
	SWD_WOW_DELAY(1);
	SWD_WOW_CLKH();	
}
/*******************************************************************************
* 函数名		:	Idle_Cycles
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_CLOCK_Idle_Cycles(uint8_t num)
{
//	SWD_WOW_ENABLE();
//	SWD_WOW_CLKL();
//	SWD_WOW_DIOL();
//	PIN_SWDIO_OUT_ENABLE();	
//	SWD_WOW_DIOL();
	while(num--)
	{
		SWD_WOW_CLKH();
		SWD_WOW_DELAY(1);
		SWD_WOW_CLKL();
		SWD_WOW_DELAY(1);		
	}
	SWD_WOW_DIOH();
}
/*******************************************************************************
* 函数名		:	SWD_WOW_Request
* 功能描述	: 阐述操作时的关键词
* 输入			: void
* 返回值		: void
*******************************************************************************/
uint8_t SWD_WOW_Request(uint8_t request)
{
	uint8_t ack=0;
	uint8_t bit=0;
	uint8_t parity=0;

	SWD_WOW_ENABLE();	
	/* Packet Request */																																																
	parity = 0;						//奇偶校验																																																			
	SWD_WOW_WRITE_BIT(1);			/* Start Bit *//*起始位：值为1*/																																
																																																											
	bit = request >> 0;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* APnDP Bit *//*端口：表示访问的是DPACC-调试端口访问（值为0）还是APACC-数据端口访问（值为1）*/	//APACC(Access Port to access)	
	parity += bit;																																																			
																																																											
	bit = request >> 1;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* RnW Bit *//*读/写：表示是读访问还是写访问，0-写访问，1-读访问*/																
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
	SWD_WOW_WRITE_BIT(bit);			/* A2 Bit *//*介绍参见下一条内容说明*/	
	parity += bit;																																						
																																																										
	bit = request >> 3;																																																
	SWD_WOW_WRITE_BIT(bit);			/* A3 Bit *//*ADDR[2:3]:给出DP或者AP寄存器的地址域ADDR[3:2],低位在前*/												
	parity += bit;																																																			
																																																											
	SWD_WOW_WRITE_BIT(parity);	/* Parity Bit */	/*为前面数据包提供单一的奇偶校验*/																					
	SWD_WOW_WRITE_BIT(0);				/* Stop Bit */		/*停止位，在同步的SWD协议中，该位始终为0*/																				
	SWD_WOW_WRITE_BIT(1);				/* Park Bit */		/*停止位，*/																																						
	
//	SWD_WOW_DELAY(1);	
	/* Turnaround */																																																		
	PIN_SWDIO_OUT_DISABLE();		/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定,掉转周期的长度由线控制寄存器中的TURNROUND 区域控制，
																默认掉转周期的精确值为一个串行时钟周期*/														
//	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															
//	{																																																								
//		SWD_WOW_CLOCK_CYCLE();																																																	
//	}
	SWD_WOW_CLOCK_CYCLE();

	SWD_WOW_DELAY(2);	
	/* Acknowledge response *//*一个3位的值对主机的响应，低位在前出现*/																											
	SWD_WOW_READ_BIT(&bit);																																																		
	ack  = bit << 0;																																																		
																																																								
	SWD_WOW_READ_BIT(&bit);																																																	
	ack |= bit << 1;																																																	
																																																								
	SWD_WOW_READ_BIT(&bit);																																														
	ack |= bit << 2;	
	return ack;
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_WRITE_BIT(uint8_t bit)
{
	SWD_WOW_CLKL();
	SWD_WOW_DIO=bit;
	SWD_WOW_DELAY(1);	
	SWD_WOW_CLKH();
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_READ_BIT(uint8_t *bit)
{
	SWD_WOW_CLKL();
	*bit = SWD_WOW_DIOIN();
	SWD_WOW_CLKH();

}
/*******************************************************************************
* 函数名		:	SWD_WOW_WDATA
* 功能描述	: 32 位写数据，从主机到目标。+奇偶校验
							WDATA[0:31]的值在线上以LSB 在先的方式发送。
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_WDATA(uint32_t bit)
{
}
/*******************************************************************************
* 函数名		:	SWD_WOW_RDATA
* 功能描述	: 32 位读数据，从目标到主机。+奇偶校验
							RDATA[0:31]的值在线上以LSB 在先的方式发送。
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_WOW_RDATA(uint32_t bit)
{
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
// SWD Transfer I/O
//	request: A[3:2] RnW APnDP
//	data:	DATA[31:0]
//	return:  ACK[2:0]
//#define SWD_TransferFunction(speed)	/*SWD读写数据操作*/																																
uint8_t SWD_WOW_Transfer(uint8_t request, uint32_t *data)																													
{																																																											
	uint8_t ack;																																																				
	uint8_t bit;																																																				
	uint32_t val;																																																				
	uint8_t parity;																																																			
	uint8_t n;																																																					
//	PIN_SWDIO_OUT_ENABLE();	
	SWD_WOW_ENABLE();	
	/* Packet Request */																																																
	parity = 0;						//奇偶校验																																																			
	SWD_WOW_WRITE_BIT(1);			/* Start Bit *//*起始位：值为1*/																																
																																																											
	bit = request >> 0;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* APnDP Bit *//*端口：表示访问的是DPACC-调试端口访问（值为0）还是APACC-数据端口访问（值为1）*/	//APACC(Access Port to access)	
	parity += bit;																																																			
																																																											
	bit = request >> 1;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* RnW Bit *//*读/写：表示是读访问还是写访问，0-写访问，1-读访问*/																
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
	SWD_WOW_WRITE_BIT(bit);		/* A2 Bit *//*介绍参见下一条内容说明*/	
	parity += bit;																																						
																																																										
	bit = request >> 3;																																																
	SWD_WOW_WRITE_BIT(bit);		/* A3 Bit *//*ADDR[2:3]:给出DP或者AP寄存器的地址域ADDR[3:2],低位在前*/												
	parity += bit;																																																			
																																																											
	SWD_WOW_WRITE_BIT(parity);	/* Parity Bit */	/*为前面数据包提供单一的奇偶校验*/																					
	SWD_WOW_WRITE_BIT(0);			/* Stop Bit */		/*停止位，在同步的SWD协议中，该位始终为0*/																				
	SWD_WOW_WRITE_BIT(1);			/* Park Bit */		/*停止位，*/																																						
	
//	SWD_WOW_DELAY(1);	
	/* Turnaround */																																																		
	PIN_SWDIO_OUT_DISABLE();		/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定,掉转周期的长度由线控制寄存器中的TURNROUND 区域控制，
																默认掉转周期的精确值为一个串行时钟周期*/														
//	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															
//	{																																																								
//		SWD_WOW_CLOCK_CYCLE();																																																	
//	}
	SWD_WOW_CLOCK_CYCLE();

	SWD_WOW_DELAY(2);	
	/* Acknowledge response *//*一个3位的值对主机的响应，低位在前出现*/																											
	SWD_WOW_READ_BIT(&bit);																																																		
	ack  = bit << 0;																																																		
																																																								
	SWD_WOW_READ_BIT(&bit);																																																	
	ack |= bit << 1;																																																	
																																																								
	SWD_WOW_READ_BIT(&bit);																																														
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
				SWD_WOW_READ_BIT(&bit);	/* Read RDATA[0:31] */									
				parity += bit;																					
				val >>= 1;																							
				val  |= bit << 31;																				
			}																														
			SWD_WOW_READ_BIT(&bit);		/* Read Parity */	/*读奇偶校验*/			
			if ((parity ^ bit) & 1)		/*奇偶校验*/										
			{																														
				ack = DAP_TRANSFER_ERROR;	/*校验错误*/	
				return (ack);				
			}																																																				
			if (data)																																																	
				*data = val;		/*更新读取的数据*/	
			
			/* Idle cycles */				/* 空闲周期 */
//			SWD_WOW_CLOCK_Idle_Cycles(2);
//			SWD_WOW_DIOL();
//			SWD_WOW_CLKL();
//			SWD_WOW_CLKH();
//			SWD_WOW_CLKL();
//			SWD_WOW_CLKH();
//			SWD_WOW_CLKL();
//			SWD_WOW_CLKH();
			
			SWD_WOW_CLOCK_CYCLE();
			SWD_WOW_CLOCK_CYCLE();
			SWD_WOW_CLOCK_CYCLE();
			
			
			SWD_WOW_DISABLE();		/*SWD_DIO引脚功能修改为输出*/															
		}																																											
		else													/*写数据请求*/																						
		{																																												
//			/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/					
//			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																		
//			{																																											
//				SW_CLOCK_CYCLE();																																			
//			}																																													
//																																																		
//			PIN_SWDIO_OUT_ENABLE();	/*SWD_DIO引脚功能修改为输出*/																	
//			/* Write data */																																	
//			val = *data;						/*待写入数据*/	
////			OLED_ShowNum(0,4,val,10,16);//显示ASCII字符的码值			
//			parity = 0;							/*清零奇偶校验*/																			
//			for (n = 32; n; n--) 		/*写32位数据*/																					
//			{																																								
//				SW_WRITE_BIT(val);	/* Write WDATA[0:31] */																			
//				parity += val;																																		
//				val >>= 1;																																				
//			}																																										
//			SW_WRITE_BIT(parity);	/* Write Parity Bit */	/*写奇偶校验*/												
		}																																											
		/* Idle cycles */				/* 空闲周期 */																								
//		n = DAP_Data.transfer.idle_cycles;																											
//		if (n != 0)																																							
//		{																																															
//			PIN_SWDIO_OUT(0);																														
//			for (; n != 0; n--)																															
//			{																																						
//				SW_CLOCK_CYCLE();																														
//			}																																									
//		}																																											
//		PIN_SWDIO_OUT(1);
		SWD_WOW_DISABLE();		
		return (ack);		/*返回应答状态退出此函数*/																			
	}																																										
	/*应答非OK--还不能进行数据传输，需要等待或者重试*/														
	if (ack == DAP_TRANSFER_WAIT || ack == DAP_TRANSFER_FAULT)														
	{																																											
//		/* WAIT or FAULT response */																														
//		if (DAP_Data.swd_conf.data_phase && (request & DAP_TRANSFER_RnW) != 0)							
//		{																																													
//			for (n = 32+1; n; n--)																																						
//			{																																														
//				SWD_WOW_CLOCK_CYCLE();	/* Dummy Read RDATA[0:31] + Parity */																	
//			}																																													
//		}																																															
//		/* Turnaround */	/*调转周期，在该周期中，不对总线进行驱动，且线的状态不确定*/								
//		for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																								
//		{																																																			
//			SWD_WOW_CLOCK_CYCLE();																																				
//		}																																																	
//																																																		
//		PIN_SWDIO_OUT_ENABLE();																																	
//		if (DAP_Data.swd_conf.data_phase && (request & DAP_TRANSFER_RnW) == 0)										
//		{																																												
//			PIN_SWDIO_OUT(0);																																				
//			for (n = 32 + 1; n != 0; n--)																																		
//			{																																											
//				SW_CLOCK_CYCLE();	/* Dummy Write WDATA[0:31] + Parity */											
//			}																																										
//		}																																										
//		PIN_SWDIO_OUT(1);																																		
//		return (ack);																																				
	}																																										
																																												
	/* Protocol error */																																		
//	for (n = DAP_Data.swd_conf.turnaround + 32 + 1; n != 0; n--)																		
//	{																																												
//		SW_CLOCK_CYCLE();	/* Back off data phase */																				
//	}	
//	for (n = 35; n != 0; n--)																		
//	{																																												
//		SWD_WOW_CLOCK_CYCLE();	/* Back off data phase */																				
//	}	
//	SW_CLOCK_CYCLE();	/* Back off data phase */	
//	SWD_WOW_CLOCK_CYCLE();	/* Back off data phase */
//	PIN_SWDIO_TMS_SET();
//	SWD_WOW_DIOL();

//	SWD_WOW_CLKH();
//	SWD_WOW_DELAY(200);
//		SWD_WOW_DISABLE();
//		SWD_WOW_DELAY(200);	
//		SWD_Line_RESET();
//		SWD_Read_IDCODE();
	return (ack);																																							
}
/*******************************************************************************
* 函数名		:	SWD_Line_RESET
* 功能描述	: M3的SWJ-DP接口上电后默认为JTAG-DP，
						:	需要先发送JTAG到SWD的切换命令：至少50个时钟的1，
							然后是16bit的切换序列0xE79E（低位在前），
							继续发送至少50个时钟的1，令SWD进入线复位状态（line reset），
							(0x6DB7-老版本ARM的强制切换,为了兼容，两种切换方式都发）
							最后再发送至少2个0(idle周期)。
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_Line_RESET(void)
{
//	uint8_t	count = 0;
//	uint16_t	SWD_Request=0xE79E;
//	
//	SWD_WOW_ENABLE();
//	//1,需要先发送JTAG到SWD的切换命令：至少50个时钟的1，
//	while(count++<51)
//	{
//		SWD_WOW_CLKL();
//		SWD_WOW_CLKH();
//	}	
//	//2,然后是16bit的切换序列0xE79E（低位在前）强制切换到SWD模式，
//	count=0;
//	SWD_WOW_CLKL();
//	while(count++<16)
//	{
//		SWD_WOW_WRITE_BIT((uint8_t)SWD_Request&0x01);
//		SWD_Request>>=1;
//	}
//	//3,继续发送至少50个时钟的1，令SWD进入线复位状态（line reset），
//	count=0;
//	while(count++<51)
//	{
//		SWD_WOW_CLKL();
//		SWD_WOW_CLKH();
//	}
//	SWD_WOW_CLKL();
//	SWD_WOW_DIOL();
//	//4,最后再发送至少2个0(idle周期)。
//	count=0;
//	while(count++<16)
//	{
//		SWD_WOW_CLKL();
//		SWD_WOW_CLKH();
//	}	
//	SWD_WOW_CLKL();
//	SWD_WOW_DISABLE();

//**************JLINK
	uint8_t	count = 0;
	uint16_t	SWD_Request=0xE79E;
	
	SWD_WOW_ENABLE();
	//1,需要先发送JTAG到SWD的切换命令：至少50个时钟的1，
	while(count++<51)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}	
	//2,然后是16bit的切换序列0xE79E（低位在前）强制切换到SWD模式，
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<16)
	{
		SWD_WOW_WRITE_BIT((uint8_t)SWD_Request&0x01);
		SWD_Request>>=1;
	}
	//3,继续发送至少50个时钟的1，令SWD进入线复位状态（line reset），
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<51)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}
	//2.1,然后是16bit的切换序列0x6DB7（低位在前）老版本ARM强制切换到SWD模式，
	count=0;	
	SWD_Request=0x6DB7;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<16)
	{
		SWD_WOW_WRITE_BIT((uint8_t)SWD_Request&0x01);
		SWD_Request>>=1;
	}
	//3.1,继续发送至少50个时钟的1，令SWD进入线复位状态（line reset），
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<51)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}	
	//4,最后再发送至少2个0(idle周期)。
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOL();			//把DIO拉低
	while(count++<16)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}	
	SWD_WOW_CLKL();
	SWD_WOW_DISABLE();
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
uint32_t SWD_Read_IDCODE(void)
{
	uint32_t data=0;		
	SWD_WOW_Transfer(0x02, &data);
	return 0;
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_CSW(void)
{
}
/*******************************************************************************
* 函数名		:	function
* 功能描述	: 函数功能说明
* 输入			: void
* 返回值		: void
*******************************************************************************/
void SWD_CTL_STAT(void)
{
}




