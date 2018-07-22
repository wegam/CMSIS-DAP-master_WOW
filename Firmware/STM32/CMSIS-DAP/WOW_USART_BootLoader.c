#include "WOW_USART_BootLoader.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

//#include "STM32F10x_BitBand.h"


/*******************************************************************************
* ������		:	WOW_USART_BT_Configuration
* ��������	: ��ȡ��ǰ�Ծٳ���汾������ʹ�õ�����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_Configuration(void)
{
	//1)**********�������	
	USART_InitTypeDef USART_InitStructure;				//USART�ṹ��	
	GPIO_InitTypeDef 	GPIO_InitStructure;					//GPIO�ṹ��
	
	//2)******************************�������GPIO/����ʱ�Ӵ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1ʱ�ӿ���
	RCC_APB1PeriphClockCmd(USART_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(USART_BT0_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(USART_RESET_RCC,ENABLE);
	
	
	//3)**********��ʼ������
	//3.1)**********��ʼ��BOOT0����
	GPIO_InitStructure.GPIO_Pin = USART_BT0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_BT0_PORT,&GPIO_InitStructure);
	//3.1)**********��ʼ��RESET����
	GPIO_InitStructure.GPIO_Pin = USART_RESET_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_RESET_PORT,&GPIO_InitStructure);
	
	//3.1)**********��ʼ��TXD����
	GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_GPIO,&GPIO_InitStructure);

	//3.2)**********��ʼ��RXD����
	GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//��������
	GPIO_Init(USART_GPIO,&GPIO_InitStructure);
	
	//3.3)**********��ʼ�����ڲ���
	USART_DeInit(USART_PORT);
	USART_InitStructure.USART_BaudRate = 115200; 																			//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;												//����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;														//ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ; 															//��żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//����
	USART_Init(USART_PORT, &USART_InitStructure);																			//��ʼ������
	
	USART_Cmd(USART_PORT, ENABLE);
}
/*******************************************************************************
* ������		:	WOW_USART_BT_Get
* ��������	: ��ȡ��ǰ�Ծٳ���汾������ʹ�õ�����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_Start(void)
{
	uint32_t time=500;	
	uint32_t time2=0;
	
	USART_Target_BT0=0;
	USART_Target_RESET=0;
	time=2000;
	while(time--);
	USART_Target_BT0=1;
	USART_Target_RESET=1;
	time=2000;
	while(time--);
	
	USART_SendData(USART_PORT, (unsigned char)0x7F);// USART1 ���Ի��� USART2 ��
	while(!(USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == SET));
	while((USART_ReceiveData(USART_PORT)!=UBT_ACK)&&(time2++<5000))
	{
		time=10000;
		while(time--);
		USART_SendData(USART_PORT, (unsigned char)0x7F);// USART1 ���Ի��� USART2 ��
		while(!(USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == SET));
	};
	USART_GetFlagStatus(USART_PORT, USART_FLAG_RXNE);
	USART_ClearFlag(USART_PORT, USART_FLAG_RXNE);
	time=2000;
	USART_Target_BT0=0;
	USART_Target_RESET=0;
	while(time--);
	USART_Target_BT0=0;
	USART_Target_RESET=1;
}
/*******************************************************************************
* ������		:	WOW_USART_BT_Get
* ��������	: ��ȡ��ǰ�Ծٳ���汾������ʹ�õ�����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_Get(void)
{
	uint32_t time=500;	
	uint32_t time2=0;
	
	USART_Target_BT0=0;
	USART_Target_RESET=0;
	time=2000;
	while(time--);
	USART_Target_BT0=1;
	USART_Target_RESET=1;
	time=400;
	while(time--);
	while((USART_ReceiveData(USART_PORT)!=UBT_ACK)&&(time2++<5000))
//	while(time2++<5000)
	{
//		USART_Target_BT0=0;
//		USART_Target_RESET=0;
//		time=500;
//		while(time--);
//		USART_Target_BT0=1;
//		USART_Target_RESET=1;
		time=1000;
		while(time--);
		USART_SendData(USART_PORT, (unsigned char)0x00);// USART1 ���Ի��� USART2 ��
		while(!(USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == SET));
		USART_SendData(USART_PORT, (unsigned char)0xFF);// USART1 ���Ի��� USART2 ��
		while(!(USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == SET));
	};
	time=2000;
	USART_Target_BT0=0;
	USART_Target_RESET=0;
	while(time--);
	USART_Target_BT0=0;
	USART_Target_RESET=1;
}
/*******************************************************************************
* ������		:	WOW_USART_BT_GVRP
* ��������	: Get Version & Read Protection Status
							��ȡ�Ծٳ���汾�� Flash �Ķ�����״̬
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_GVRP(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_GetID
* ��������	: ��ȡоƬ ID
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_GetID(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_RM
* ��������	: Read Memory
							��Ӧ�ó���ָ���ĵ�ַ��ʼ��ȡ��� 256 ���ֽڵĴ洢���ռ�
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_RM(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_Go
* ��������	: ��ת���ڲ� Flash �� SRAM �ڵ�Ӧ�ó������
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_Go(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_WM
* ��������	: Write Memory
							��Ӧ�ó���ָ���ĵ�ַ��ʼ����� 256 ���ֽڵ�����д�� RAM �� Flash
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_WM(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_Erase
* ��������	: ����һ����ȫ�� Flash ҳ��
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_Erase(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_eErase
* ��������	: Extended Erase
							ʹ��˫�ֽ�Ѱַģʽ����һ����ȫ�� Flash ҳ��
						��������v3.0 usart �Ծٳ���汾�����ϰ汾����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_eErase(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_WP
* ��������	: Write Protect
							ʹ��ĳЩ������д����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_WP(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_WUP
* ��������	: Write Unprotect
							��ֹ���� Flash ������д����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_WUP(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_RP
* ��������	: Readout Protect
							ʹ�ܶ�����
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_RP(void)
{

}
/*******************************************************************************
* ������		:	WOW_USART_BT_RUP
* ��������	: Readout Unprotect
							��ֹ������
* ����			: void
* ����ֵ		: void
*******************************************************************************/
void WOW_USART_BT_RUP(void)
{

}

