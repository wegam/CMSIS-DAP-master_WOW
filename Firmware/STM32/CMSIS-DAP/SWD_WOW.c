#include "SWD_WOW.h"

#include "CMSIS_Conf.H"
#include "DAP.h"

//#include "STM32F10x_BitBand.h"

/*1,���е�SWD ���䶼��LSB ����*/

/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_DELAY(uint32_t time)
{
//		uint32_t	time=200;
	uint32_t	temp=time;
	while(temp--);
//	__NOP();
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_DISABLE()
{
	PIN_SWDIO_OUT_DISABLE();
	PIN_SWCLK_OUT_DISABLE();
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_ENABLE()
{
	PIN_SWDIO_OUT_ENABLE();
	PIN_SWCLK_OUT_ENABLE();	
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_CLOCK_CYCLE()
{
	SWD_WOW_CLKL();
	SWD_WOW_DELAY(1);
	SWD_WOW_CLKH();	
}
/*******************************************************************************
* ������		:	Idle_Cycles
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
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
* ������		:	SWD_WOW_Request
* ��������	: ��������ʱ�Ĺؼ���
* ����			: void
* ����ֵ		: void
*******************************************************************************/
uint8_t SWD_WOW_Request(uint8_t request)
{
	uint8_t ack=0;
	uint8_t bit=0;
	uint8_t parity=0;

	SWD_WOW_ENABLE();	
	/* Packet Request */																																																
	parity = 0;						//��żУ��																																																			
	SWD_WOW_WRITE_BIT(1);			/* Start Bit *//*��ʼλ��ֵΪ1*/																																
																																																											
	bit = request >> 0;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* APnDP Bit *//*�˿ڣ���ʾ���ʵ���DPACC-���Զ˿ڷ��ʣ�ֵΪ0������APACC-���ݶ˿ڷ��ʣ�ֵΪ1��*/	//APACC(Access Port to access)	
	parity += bit;																																																			
																																																											
	bit = request >> 1;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* RnW Bit *//*��/д����ʾ�Ƕ����ʻ���д���ʣ�0-д���ʣ�1-������*/																
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
	SWD_WOW_WRITE_BIT(bit);			/* A2 Bit *//*���ܲμ���һ������˵��*/	
	parity += bit;																																						
																																																										
	bit = request >> 3;																																																
	SWD_WOW_WRITE_BIT(bit);			/* A3 Bit *//*ADDR[2:3]:����DP����AP�Ĵ����ĵ�ַ��ADDR[3:2],��λ��ǰ*/												
	parity += bit;																																																			
																																																											
	SWD_WOW_WRITE_BIT(parity);	/* Parity Bit */	/*Ϊǰ�����ݰ��ṩ��һ����żУ��*/																					
	SWD_WOW_WRITE_BIT(0);				/* Stop Bit */		/*ֹͣλ����ͬ����SWDЭ���У���λʼ��Ϊ0*/																				
	SWD_WOW_WRITE_BIT(1);				/* Park Bit */		/*ֹͣλ��*/																																						
	
//	SWD_WOW_DELAY(1);	
	/* Turnaround */																																																		
	PIN_SWDIO_OUT_DISABLE();		/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��,��ת���ڵĳ������߿��ƼĴ����е�TURNROUND ������ƣ�
																Ĭ�ϵ�ת���ڵľ�ȷֵΪһ������ʱ������*/														
//	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															
//	{																																																								
//		SWD_WOW_CLOCK_CYCLE();																																																	
//	}
	SWD_WOW_CLOCK_CYCLE();

	SWD_WOW_DELAY(2);	
	/* Acknowledge response *//*һ��3λ��ֵ����������Ӧ����λ��ǰ����*/																											
	SWD_WOW_READ_BIT(&bit);																																																		
	ack  = bit << 0;																																																		
																																																								
	SWD_WOW_READ_BIT(&bit);																																																	
	ack |= bit << 1;																																																	
																																																								
	SWD_WOW_READ_BIT(&bit);																																														
	ack |= bit << 2;	
	return ack;
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_WRITE_BIT(uint8_t bit)
{
	SWD_WOW_CLKL();
	SWD_WOW_DIO=bit;
	SWD_WOW_DELAY(1);	
	SWD_WOW_CLKH();
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_READ_BIT(uint8_t *bit)
{
	SWD_WOW_CLKL();
	*bit = SWD_WOW_DIOIN();
	SWD_WOW_CLKH();

}
/*******************************************************************************
* ������		:	SWD_WOW_WDATA
* ��������	: 32 λд���ݣ���������Ŀ�ꡣ+��żУ��
							WDATA[0:31]��ֵ��������LSB ���ȵķ�ʽ���͡�
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_WDATA(uint32_t bit)
{
}
/*******************************************************************************
* ������		:	SWD_WOW_RDATA
* ��������	: 32 λ�����ݣ���Ŀ�굽������+��żУ��
							RDATA[0:31]��ֵ��������LSB ���ȵķ�ʽ���͡�
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_WOW_RDATA(uint32_t bit)
{
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
// SWD Transfer I/O
//	request: A[3:2] RnW APnDP
//	data:	DATA[31:0]
//	return:  ACK[2:0]
//#define SWD_TransferFunction(speed)	/*SWD��д���ݲ���*/																																
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
	parity = 0;						//��żУ��																																																			
	SWD_WOW_WRITE_BIT(1);			/* Start Bit *//*��ʼλ��ֵΪ1*/																																
																																																											
	bit = request >> 0;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* APnDP Bit *//*�˿ڣ���ʾ���ʵ���DPACC-���Զ˿ڷ��ʣ�ֵΪ0������APACC-���ݶ˿ڷ��ʣ�ֵΪ1��*/	//APACC(Access Port to access)	
	parity += bit;																																																			
																																																											
	bit = request >> 1;																																																	
	SWD_WOW_WRITE_BIT(bit);		/* RnW Bit *//*��/д����ʾ�Ƕ����ʻ���д���ʣ�0-д���ʣ�1-������*/																
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
	SWD_WOW_WRITE_BIT(bit);		/* A2 Bit *//*���ܲμ���һ������˵��*/	
	parity += bit;																																						
																																																										
	bit = request >> 3;																																																
	SWD_WOW_WRITE_BIT(bit);		/* A3 Bit *//*ADDR[2:3]:����DP����AP�Ĵ����ĵ�ַ��ADDR[3:2],��λ��ǰ*/												
	parity += bit;																																																			
																																																											
	SWD_WOW_WRITE_BIT(parity);	/* Parity Bit */	/*Ϊǰ�����ݰ��ṩ��һ����żУ��*/																					
	SWD_WOW_WRITE_BIT(0);			/* Stop Bit */		/*ֹͣλ����ͬ����SWDЭ���У���λʼ��Ϊ0*/																				
	SWD_WOW_WRITE_BIT(1);			/* Park Bit */		/*ֹͣλ��*/																																						
	
//	SWD_WOW_DELAY(1);	
	/* Turnaround */																																																		
	PIN_SWDIO_OUT_DISABLE();		/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��,��ת���ڵĳ������߿��ƼĴ����е�TURNROUND ������ƣ�
																Ĭ�ϵ�ת���ڵľ�ȷֵΪһ������ʱ������*/														
//	for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																															
//	{																																																								
//		SWD_WOW_CLOCK_CYCLE();																																																	
//	}
	SWD_WOW_CLOCK_CYCLE();

	SWD_WOW_DELAY(2);	
	/* Acknowledge response *//*һ��3λ��ֵ����������Ӧ����λ��ǰ����*/																											
	SWD_WOW_READ_BIT(&bit);																																																		
	ack  = bit << 0;																																																		
																																																								
	SWD_WOW_READ_BIT(&bit);																																																	
	ack |= bit << 1;																																																	
																																																								
	SWD_WOW_READ_BIT(&bit);																																														
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
				SWD_WOW_READ_BIT(&bit);	/* Read RDATA[0:31] */									
				parity += bit;																					
				val >>= 1;																							
				val  |= bit << 31;																				
			}																														
			SWD_WOW_READ_BIT(&bit);		/* Read Parity */	/*����żУ��*/			
			if ((parity ^ bit) & 1)		/*��żУ��*/										
			{																														
				ack = DAP_TRANSFER_ERROR;	/*У�����*/	
				return (ack);				
			}																																																				
			if (data)																																																	
				*data = val;		/*���¶�ȡ������*/	
			
			/* Idle cycles */				/* �������� */
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
			
			
			SWD_WOW_DISABLE();		/*SWD_DIO���Ź����޸�Ϊ���*/															
		}																																											
		else													/*д��������*/																						
		{																																												
//			/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/					
//			for (n = DAP_Data.swd_conf.turnaround; n != 0; n--)																		
//			{																																											
//				SW_CLOCK_CYCLE();																																			
//			}																																													
//																																																		
//			PIN_SWDIO_OUT_ENABLE();	/*SWD_DIO���Ź����޸�Ϊ���*/																	
//			/* Write data */																																	
//			val = *data;						/*��д������*/	
////			OLED_ShowNum(0,4,val,10,16);//��ʾASCII�ַ�����ֵ			
//			parity = 0;							/*������żУ��*/																			
//			for (n = 32; n; n--) 		/*д32λ����*/																					
//			{																																								
//				SW_WRITE_BIT(val);	/* Write WDATA[0:31] */																			
//				parity += val;																																		
//				val >>= 1;																																				
//			}																																										
//			SW_WRITE_BIT(parity);	/* Write Parity Bit */	/*д��żУ��*/												
		}																																											
		/* Idle cycles */				/* �������� */																								
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
		return (ack);		/*����Ӧ��״̬�˳��˺���*/																			
	}																																										
	/*Ӧ���OK--�����ܽ������ݴ��䣬��Ҫ�ȴ���������*/														
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
//		/* Turnaround */	/*��ת���ڣ��ڸ������У��������߽������������ߵ�״̬��ȷ��*/								
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
* ������		:	SWD_Line_RESET
* ��������	: M3��SWJ-DP�ӿ��ϵ��Ĭ��ΪJTAG-DP��
						:	��Ҫ�ȷ���JTAG��SWD���л��������50��ʱ�ӵ�1��
							Ȼ����16bit���л�����0xE79E����λ��ǰ����
							������������50��ʱ�ӵ�1����SWD�����߸�λ״̬��line reset����
							(0x6DB7-�ϰ汾ARM��ǿ���л�,Ϊ�˼��ݣ������л���ʽ������
							����ٷ�������2��0(idle����)��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_Line_RESET(void)
{
//	uint8_t	count = 0;
//	uint16_t	SWD_Request=0xE79E;
//	
//	SWD_WOW_ENABLE();
//	//1,��Ҫ�ȷ���JTAG��SWD���л��������50��ʱ�ӵ�1��
//	while(count++<51)
//	{
//		SWD_WOW_CLKL();
//		SWD_WOW_CLKH();
//	}	
//	//2,Ȼ����16bit���л�����0xE79E����λ��ǰ��ǿ���л���SWDģʽ��
//	count=0;
//	SWD_WOW_CLKL();
//	while(count++<16)
//	{
//		SWD_WOW_WRITE_BIT((uint8_t)SWD_Request&0x01);
//		SWD_Request>>=1;
//	}
//	//3,������������50��ʱ�ӵ�1����SWD�����߸�λ״̬��line reset����
//	count=0;
//	while(count++<51)
//	{
//		SWD_WOW_CLKL();
//		SWD_WOW_CLKH();
//	}
//	SWD_WOW_CLKL();
//	SWD_WOW_DIOL();
//	//4,����ٷ�������2��0(idle����)��
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
	//1,��Ҫ�ȷ���JTAG��SWD���л��������50��ʱ�ӵ�1��
	while(count++<51)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}	
	//2,Ȼ����16bit���л�����0xE79E����λ��ǰ��ǿ���л���SWDģʽ��
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<16)
	{
		SWD_WOW_WRITE_BIT((uint8_t)SWD_Request&0x01);
		SWD_Request>>=1;
	}
	//3,������������50��ʱ�ӵ�1����SWD�����߸�λ״̬��line reset����
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<51)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}
	//2.1,Ȼ����16bit���л�����0x6DB7����λ��ǰ���ϰ汾ARMǿ���л���SWDģʽ��
	count=0;	
	SWD_Request=0x6DB7;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<16)
	{
		SWD_WOW_WRITE_BIT((uint8_t)SWD_Request&0x01);
		SWD_Request>>=1;
	}
	//3.1,������������50��ʱ�ӵ�1����SWD�����߸�λ״̬��line reset����
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOH();
	while(count++<51)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}	
	//4,����ٷ�������2��0(idle����)��
	count=0;
	SWD_WOW_CLKL();
	SWD_WOW_DIOL();			//��DIO����
	while(count++<16)
	{
		SWD_WOW_CLKL();
		SWD_WOW_CLKH();
	}	
	SWD_WOW_CLKL();
	SWD_WOW_DISABLE();
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
uint32_t SWD_Read_IDCODE(void)
{
	uint32_t data=0;		
	SWD_WOW_Transfer(0x02, &data);
	return 0;
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_CSW(void)
{
}
/*******************************************************************************
* ������		:	function
* ��������	: ��������˵��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void SWD_CTL_STAT(void)
{
}




