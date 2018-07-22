
#ifndef __WOW_USART_BootLoader__
#define __WOW_USART_BootLoader__

#include "stddef.h"
#include "stdint.h"

#include "STM32F10x_BitBand.h"

#if   defined ( STM32_CDC )

	#define USART_CLOCK(state)		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, state)
	#define USART_GPIO_CLOCK(state)	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, state)
	#define USART_REMAP()			/* GPIO_PinRemapConfig(..., ENABLE) */

	#define USART_RCC				RCC_APB2Periph_USART1
	#define USART_PORT			USART1
	#define USART_GPIO			GPIOA
	#define USART_TX_PIN		GPIO_Pin_9
	#define USART_RX_PIN		GPIO_Pin_10
	#define USART_IRQn			USART1_IRQn
	#define USART_IRQHandler	USART1_IRQHandler
	#define USART_BUFFER_SIZE	(256)	/*	Size of Receive and Transmit buffers MUST BE 2^n */
	
	#define USART_BT0_RCC				RCC_APB2ENR_IOPAEN
	#define USART_BT0_PORT			GPIOA
	#define USART_BT0_PIN				GPIO_Pin_1
	#define USART_Target_BT0		PA1
	
	#define USART_RESET_RCC			RCC_APB2ENR_IOPAEN
	#define USART_RESET_PORT		GPIOA
	#define USART_RESET_PIN			GPIO_Pin_4
	#define USART_Target_RESET	PA4
	
	
#elif defined ( USB_TEST )

	#define USART_CLOCK(state)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, state)
	#define USART_REMAP()			/* GPIO_PinRemapConfig(..., ENABLE) */
	
	#define USART_RCC				RCC_APB1Periph_USART2
	#define USART_PORT			USART2
	#define USART_GPIO			GPIOA
	#define USART_TX_PIN		GPIO_Pin_2
	#define USART_RX_PIN		GPIO_Pin_3
	#define USART_IRQn			USART2_IRQn
	#define USART_IRQHandler	USART2_IRQHandler
	#define USART_BUFFER_SIZE	(256)	/*	Size of Receive and Transmit buffers MUST BE 2^n */
	
	#define USART_BT0_RCC				RCC_APB2ENR_IOPAEN
	#define USART_BT0_PORT			GPIOA
	#define USART_BT0_PIN				GPIO_Pin_1
	#define USART_Target_BT0		PA1
	
	#define USART_RESET_RCC			RCC_APB2ENR_IOPAEN
	#define USART_RESET_PORT		GPIOA
	#define USART_RESET_PIN			GPIO_Pin_4
	#define USART_Target_RESET	PA4

#else

	#warning "USART Port not define"

#endif

	
/*应答与非应答*/
#define UBT_ACK 		0x79
#define UBT_NACK		0x1F


void WOW_USART_BT_Configuration(void);	//串口下载端口初始化
void WOW_USART_BT_Start(void);		//启用串口自举程序
void WOW_USART_BT_Get(void);			//获取当前自举程序版本及允许使用的命令
void WOW_USART_BT_GVRP(void);			//获取自举程序版本及 Flash 的读保护状态
void WOW_USART_BT_GetID(void);		//获取芯片 ID
void WOW_USART_BT_RM(void);				//从应用程序指定的地址开始读取最多 256 个字节的存储器空间
void WOW_USART_BT_Go(void);				//跳转到内部 Flash 或 SRAM 内的应用程序代码
void WOW_USART_BT_WM(void);				//从应用程序指定的地址开始将最多 256 个字节的数据写入 RAM 或 Flash
void WOW_USART_BT_Erase(void);		//擦除一个到全部 Flash 页面
void WOW_USART_BT_eErase(void);		//使用双字节寻址模式擦除一个到全部 Flash 页面（仅用于v3.0 usart 自举程序版本及以上版本）。
void WOW_USART_BT_WP(void);				//使能某些扇区的写保护
void WOW_USART_BT_WUP(void);			//禁止所有 Flash 扇区的写保护
void WOW_USART_BT_RP(void);				//使能读保护
void WOW_USART_BT_RUP(void);			//禁止读保护


#endif  /* __DAP_H__ */
