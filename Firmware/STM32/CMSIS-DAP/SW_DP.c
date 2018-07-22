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


// Generate SWJ Sequence	//��������--���ݸߵ�ƽ����51��ʱ�ӣ����߸�λ
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
//#define SWD_TransferFunction(speed)	/*SWD��д���ݲ���*/																																
uint8_t SWD_Transfer(uint8_t request, uint32_t *data)																													
{																																																											
	uint8_t ack;																																																				
	uint8_t bit;																																																				
	uint32_t val;																																																				
	uint8_t parity;																																																			
	uint8_t n;																																																					
																																																											
	/* Packet Request */																																																
	parity = 0;						//��żУ��																																																			
	SW_WRITE_BIT(1);			/* Start Bit *//*��ʼλ��ֵΪ1*/																																
																																																											
	bit = request >> 0;																																																	
	SW_WRITE_BIT(bit);		/* APnDP Bit *//*�˿ڣ���ʾ���ʵ���DPACC-���Զ˿ڷ��ʣ�ֵΪ0������APACC-���ݶ˿ڷ��ʣ�ֵΪ1��*/	//APACC(Access Port to access)	
	parity += bit;																																																			
																																																											
	bit = request >> 1;																																																	
	SW_WRITE_BIT(bit);		/* RnW Bit *//*��/д����ʾ�Ƕ����ʻ���д���ʣ�0-д���ʣ�1-������*/																
	parity += bit;	

	//_________________________________ADDR[2:3]
	//ADDR[2:3]˵������A[3:2]����32λ���ԽӿڼĴ�����ַ
	//	0X00-00	��	���Զ˿�ID�Ĵ���	��DPIDR/IDCODE)---ֻ��
	//
	//	0X04-01	��	DP SELECT�Ĵ���--����ѡ��ǰ�ķ��ʶ˿ں���Ч��4�ֳ��Ĵ�������
	//							- Bits31:24��APSEL ѡ��ǰAP
	//							- Bits23:8��δ����
	//							- Bits7:4��APBANKSEL���ڵ�ǰAP��ѡ��4�ֳ��Ĵ�������
	//							- Bits3:0��δ����
	//
	//	0X08-10	��	DP CTRL/STAT �Ĵ���
	//							- ����һ��ϵͳ����Ե��ϵ����
	//							- ����AP���ʵĲ���ģʽ
	//							- ���ƱȽϣ�У�����
	//							- ��ȡһЩ״̬λ(������ϵ���Ӧ)
	//							
	//	0X0C-11	��	DP RDBUFF�Ĵ���--����ʹ���������ǰһ�β��������ս��(����������һ���µ�JTAG-DP����)
																																																											
	bit = request >> 2;																																																	
	SW_WRITE_BIT(bit);		/* A2 Bit *//*���ܲμ���һ������˵��*/	
	parity += bit;																																						
																																																										
	bit = request >> 3;																																																
	SW_WRITE_BIT(bit);		/* A3 Bit *//*ADDR[2:3]:����DP����AP�Ĵ����ĵ�ַ��ADDR[3:2],��λ��ǰ*/												
	parity += bit;																																																			
																																																											
	SW_WRITE_BIT(parity);	/* Parity Bit */	/*Ϊǰ�����ݰ��ṩ��һ����żУ��*/																					
	SW_WRITE_BIT(0);			/* Stop Bit */		/*ֹͣλ����ͬ����SWDЭ���У���λʼ��Ϊ0*/																				
	SW_WRITE_BIT(1);			/* Park Bit */		/*ֹͣλ��*/																																						
																																																										
	/* Turnaround */																																																		
	PIN_SWDIO_OUT_DISABLE();		/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/														
	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															
	{																																																								
		SW_CLOCK_CYCLE();																																																	
	}																																																										
																																																												
	/* Acknowledge response *//*һ��3λ��ֵ����������Ӧ����λ��ǰ����*/																											
	SW_READ_BIT(bit);																																																		
	ack  = bit << 0;																																																		
																																																										
	SW_READ_BIT(bit);																																																	
	ack |= bit << 1;																																																	
																																																								
	SW_READ_BIT(bit);																																														
	ack |= bit << 2;																																														
	/*�ж�Ӧ���Ƿ�ɹ�*/																																											
	if (ack == DAP_TRANSFER_OK)		/*Ӧ��ɹ�*/		/*#define DAP_TRANSFER_OK		(1 << 0)*/											
	{	/* OK response */									/*Ӧ��ɹ�*/																													
		/* Data transfer */								/*���ݴ���*/																													
		if (request & DAP_TRANSFER_RnW)		/*����������*/																										
		{	/* Read data */									/*������**/																											
			val = 0;																																											
			parity = 0;																																									
			for (n = 32; n; n--)						/*��32λ����*/																						
			{																																													
				SW_READ_BIT(bit);	/* Read RDATA[0:31] */									
				parity += bit;																					
				val >>= 1;																							
				val  |= bit << 31;																				
			}																														
			SW_READ_BIT(bit);		/* Read Parity */	/*����żУ��*/			
			if ((parity ^ bit) & 1)		/*��żУ��*/										
			{																														
				ack = DAP_TRANSFER_ERROR;	/*У�����*/											
			}																																																				
			if (data)																																																	
				*data = val;		/*���¶�ȡ������*/																																		
			/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/						
			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																				
			{																																												
				SW_CLOCK_CYCLE();																																			
			}																																													
																																													
			PIN_SWDIO_OUT_ENABLE();		/*SWD_DIO���Ź����޸�Ϊ���*/															
		}																																											
		else													/*д��������*/																						
		{																																												
			/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/					
			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																		
			{																																											
				SW_CLOCK_CYCLE();																																			
			}																																													
																																																		
			PIN_SWDIO_OUT_ENABLE();	/*SWD_DIO���Ź����޸�Ϊ���*/																	
			/* Write data */																																	
			val = *data;						/*��д������*/	
//			OLED_ShowNum(0,4,val,10,16);//��ʾASCII�ַ�����ֵ			
			parity = 0;							/*������żУ��*/																			
			for (n = 32; n; n--) 		/*д32λ����*/																					
			{																																								
				SW_WRITE_BIT(val);	/* Write WDATA[0:31] */																			
				parity += val;																																		
				val >>= 1;																																				
			}																																										
			SW_WRITE_BIT(parity);	/* Write Parity Bit */	/*д��żУ��*/												
		}																																											
		/* Idle cycles */				/* �������� */																								
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
		return (ack);		/*����Ӧ��״̬�˳��˺���*/																			
	}																																										
	/*Ӧ���OK--�����ܽ������ݴ��䣬��Ҫ�ȴ���������*/														
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
		/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/								
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

// SWD Transfer I/O		//SWD���ݶ�д
//	request: A[3:2] RnW APnDP
//	data:	DATA[31:0]
//	return:  ACK[2:0]	//����3λӦ��
//uint8_t  SWD_Transfer(uint8_t request, uint32_t *data)
//{
//	if (DAP_Data.fast_clock)
//		return SWD_TransferFast(request, data);
//	else
//		return SWD_TransferSlow(request, data);		//uint8_t SWD_Transfer##speed (uint8_t request, uint32_t *data)
//}


//------------------------------------------ԭ�ļ�����----------------------------------------------------

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

//// Generate SWJ Sequence	//��������--���ݸߵ�ƽ����51��ʱ�ӣ����߸�λ
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
//#define SWD_TransferFunction(speed)	/*SWD��д���ݲ���*/																																\
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
//	SW_WRITE_BIT(1);			/* Start Bit *//*��ʼλ��ֵΪ1*/																																\
//																																																											\
//	bit = request >> 0;																																																	\
//	SW_WRITE_BIT(bit);		/* APnDP Bit *//*�˿ڣ���ʾ���ʵ���DPACC-���Զ˿ڷ��ʣ�ֵΪ0������APACC-���ݶ˿ڷ��ʣ�ֵΪ1��*/		\
//	parity += bit;																																																			\
//																																																											\
//	bit = request >> 1;																																																	\
//	SW_WRITE_BIT(bit);		/* RnW Bit *//*��/д����ʾ�Ƕ����ʻ���д���ʣ�0-д���ʣ�1-������*/																\
//	parity += bit;																																																			\
//																																																											\
//	bit = request >> 2;																																																	\
//	SW_WRITE_BIT(bit);		/* A2 Bit *//*���ܲμ���һ������˵��*/																													\
//	parity += bit;																																																			\
//																																																											\
//	bit = request >> 3;																																																	\
//	SW_WRITE_BIT(bit);		/* A3 Bit *//*ADDR[2:3]:����DP����AP�Ĵ����ĵ�ַ��ADDR[3:2],��λ��ǰ*/													\
//	parity += bit;																																																			\
//																																																											\
//	SW_WRITE_BIT(parity);	/* Parity Bit *//*Ϊǰ�����ݰ��ṩ��һ����żУ��*/																							\
//	SW_WRITE_BIT(0);			/* Stop Bit *//*ֹͣλ����ͬ����SWDЭ���У���λʼ��Ϊ0*/																						\
//	SW_WRITE_BIT(1);			/* Park Bit */																																									\
//																																																											\
//	/* Turnaround */																																																		\
//	PIN_SWDIO_OUT_DISABLE();		/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/																\
//	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																																	\
//	{																																																										\
//		SW_CLOCK_CYCLE();																																																	\
//	}																																																										\
//																																																											\
//	/* Acknowledge response *//*һ��3λ��ֵ����������Ӧ����λ��ǰ����*/																										\
//	SW_READ_BIT(bit);																																																		\
//	ack  = bit << 0;																																																		\
//																																																											\
//	SW_READ_BIT(bit);																																																		\
//	ack |= bit << 1;																																																		\
//																																																											\
//	SW_READ_BIT(bit);																																																		\
//	ack |= bit << 2;																																																		\
//	/*�ж�Ӧ���Ƿ�ɹ�*/																																																	\
//	if (ack == DAP_TRANSFER_OK)		/*Ӧ��ɹ�*/		/*#define DAP_TRANSFER_OK		(1 << 0)*/																	\
//	{	/* OK response */									/*Ӧ��ɹ�*/																																			\
//		/* Data transfer */								/*���ݴ���*/																																			\
//		if (request & DAP_TRANSFER_RnW)		/*����������*/																																		\
//		{	/* Read data */									/*������**/																																			\
//			val = 0;																																																				\
//			parity = 0;																																																			\
//			for (n = 32; n; n--)						/*��32λ����*/																																		\
//			{																																																								\
//				SW_READ_BIT(bit);	/* Read RDATA[0:31] */																																			\
//				parity += bit;																																																\
//				val >>= 1;																																																		\
//				val  |= bit << 31;																																														\
//			}																																																								\
//			SW_READ_BIT(bit);		/* Read Parity */	/*����żУ��*/																															\
//			if ((parity ^ bit) & 1)		/*��żУ��*/																																						\
//			{																																																								\
//				ack = DAP_TRANSFER_ERROR;	/*У�����*/																																					\
//			}																																																								\
//			if (data)																																																				\
//				*data = val;		/*���¶�ȡ������*/																																							\
//			/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/																			\
//			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															\
//			{																																																								\
//				SW_CLOCK_CYCLE();																																															\
//			}																																																								\
//																																																											\
//			PIN_SWDIO_OUT_ENABLE();		/*SWD_DIO���Ź����޸�Ϊ���*/																													\
//		}																																																									\
//		else													/*д��������*/																																				\
//		{																																																									\
//			/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/																			\
//			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															\
//			{																																																								\
//				SW_CLOCK_CYCLE();																																															\
//			}																																																								\
//																																																											\
//			PIN_SWDIO_OUT_ENABLE();	/*SWD_DIO���Ź����޸�Ϊ���*/																														\
//			/* Write data */																																																\
//			val = *data;						/*��д������*/																																						\
//			parity = 0;							/*������żУ��*/																																					\
//			for (n = 32; n; n--) 		/*д32λ����*/																																						\
//			{																																																								\
//				SW_WRITE_BIT(val);	/* Write WDATA[0:31] */																																		\
//				parity += val;																																																\
//				val >>= 1;																																																		\
//			}																																																								\
//			SW_WRITE_BIT(parity);	/* Write Parity Bit */	/*д��żУ��*/																											\
//		}																																																									\
//		/* Idle cycles */				/* �������� */																																							\
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
//		return (ack);		/*����Ӧ��״̬�˳��˺���*/																																					\
//	}																																																										\
//	/*Ӧ���OK--�����ܽ������ݴ��䣬��Ҫ�ȴ���������*/																																			\
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
//		/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/																				\
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

//// SWD Transfer I/O		//SWD���ݶ�д
////	request: A[3:2] RnW APnDP
////	data:	DATA[31:0]
////	return:  ACK[2:0]	//����3λӦ��
//uint8_t  SWD_Transfer(uint8_t request, uint32_t *data)
//{
//	if (DAP_Data.fast_clock)
//		return SWD_TransferFast(request, data);
//	else
//		return SWD_TransferSlow(request, data);		//uint8_t SWD_Transfer##speed (uint8_t request, uint32_t *data)
//}

#endif  /* (DAP_SWD != 0) */
