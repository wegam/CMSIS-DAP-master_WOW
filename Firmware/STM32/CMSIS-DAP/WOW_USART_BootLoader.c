#include "WOW_USART_BootLoader.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

//#include "STM32F10x_BitBand.h"


/*******************************************************************************
* 函数名		:	WOW_USART_BT_Configuration
* 功能描述	: 获取当前自举程序版本及允许使用的命令
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_Configuration(void)
{
	//1)**********定义变量	
	USART_InitTypeDef USART_InitStructure;				//USART结构体	
	GPIO_InitTypeDef 	GPIO_InitStructure;					//GPIO结构体
	
	//2)******************************配置相关GPIO/串口时钟打开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1时钟开启
	RCC_APB1PeriphClockCmd(USART_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(USART_BT0_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(USART_RESET_RCC,ENABLE);
	
	
	//3)**********初始化串口
	//3.1)**********初始化BOOT0引脚
	GPIO_InitStructure.GPIO_Pin = USART_BT0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_BT0_PORT,&GPIO_InitStructure);
	//3.1)**********初始化RESET引脚
	GPIO_InitStructure.GPIO_Pin = USART_RESET_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_RESET_PORT,&GPIO_InitStructure);
	
	//3.1)**********初始化TXD引脚
	GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_GPIO,&GPIO_InitStructure);

	//3.2)**********初始化RXD引脚
	GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//上拉输入
	GPIO_Init(USART_GPIO,&GPIO_InitStructure);
	
	//3.3)**********初始化串口参数
	USART_DeInit(USART_PORT);
	USART_InitStructure.USART_BaudRate = 115200; 																			//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;												//数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;														//停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ; 															//奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//流控
	USART_Init(USART_PORT, &USART_InitStructure);																			//初始化串口
	
	USART_Cmd(USART_PORT, ENABLE);
}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_Get
* 功能描述	: 获取当前自举程序版本及允许使用的命令
* 输入			: void
* 返回值		: void
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
	
	USART_SendData(USART_PORT, (unsigned char)0x7F);// USART1 可以换成 USART2 等
	while(!(USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == SET));
	while((USART_ReceiveData(USART_PORT)!=UBT_ACK)&&(time2++<5000))
	{
		time=10000;
		while(time--);
		USART_SendData(USART_PORT, (unsigned char)0x7F);// USART1 可以换成 USART2 等
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
* 函数名		:	WOW_USART_BT_Get
* 功能描述	: 获取当前自举程序版本及允许使用的命令
* 输入			: void
* 返回值		: void
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
		USART_SendData(USART_PORT, (unsigned char)0x00);// USART1 可以换成 USART2 等
		while(!(USART_GetFlagStatus(USART_PORT, USART_FLAG_TXE) == SET));
		USART_SendData(USART_PORT, (unsigned char)0xFF);// USART1 可以换成 USART2 等
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
* 函数名		:	WOW_USART_BT_GVRP
* 功能描述	: Get Version & Read Protection Status
							获取自举程序版本及 Flash 的读保护状态
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_GVRP(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_GetID
* 功能描述	: 获取芯片 ID
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_GetID(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_RM
* 功能描述	: Read Memory
							从应用程序指定的地址开始读取最多 256 个字节的存储器空间
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_RM(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_Go
* 功能描述	: 跳转到内部 Flash 或 SRAM 内的应用程序代码
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_Go(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_WM
* 功能描述	: Write Memory
							从应用程序指定的地址开始将最多 256 个字节的数据写入 RAM 或 Flash
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_WM(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_Erase
* 功能描述	: 擦除一个到全部 Flash 页面
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_Erase(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_eErase
* 功能描述	: Extended Erase
							使用双字节寻址模式擦除一个到全部 Flash 页面
						（仅用于v3.0 usart 自举程序版本及以上版本）。
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_eErase(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_WP
* 功能描述	: Write Protect
							使能某些扇区的写保护
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_WP(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_WUP
* 功能描述	: Write Unprotect
							禁止所有 Flash 扇区的写保护
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_WUP(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_RP
* 功能描述	: Readout Protect
							使能读保护
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_RP(void)
{

}
/*******************************************************************************
* 函数名		:	WOW_USART_BT_RUP
* 功能描述	: Readout Unprotect
							禁止读保护
* 输入			: void
* 返回值		: void
*******************************************************************************/
void WOW_USART_BT_RUP(void)
{

}

