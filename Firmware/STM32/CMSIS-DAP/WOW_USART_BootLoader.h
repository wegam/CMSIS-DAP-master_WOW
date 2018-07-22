
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

	
/*Ӧ�����Ӧ��*/
#define UBT_ACK 		0x79
#define UBT_NACK		0x1F


void WOW_USART_BT_Configuration(void);	//�������ض˿ڳ�ʼ��
void WOW_USART_BT_Start(void);		//���ô����Ծٳ���
void WOW_USART_BT_Get(void);			//��ȡ��ǰ�Ծٳ���汾������ʹ�õ�����
void WOW_USART_BT_GVRP(void);			//��ȡ�Ծٳ���汾�� Flash �Ķ�����״̬
void WOW_USART_BT_GetID(void);		//��ȡоƬ ID
void WOW_USART_BT_RM(void);				//��Ӧ�ó���ָ���ĵ�ַ��ʼ��ȡ��� 256 ���ֽڵĴ洢���ռ�
void WOW_USART_BT_Go(void);				//��ת���ڲ� Flash �� SRAM �ڵ�Ӧ�ó������
void WOW_USART_BT_WM(void);				//��Ӧ�ó���ָ���ĵ�ַ��ʼ����� 256 ���ֽڵ�����д�� RAM �� Flash
void WOW_USART_BT_Erase(void);		//����һ����ȫ�� Flash ҳ��
void WOW_USART_BT_eErase(void);		//ʹ��˫�ֽ�Ѱַģʽ����һ����ȫ�� Flash ҳ�棨������v3.0 usart �Ծٳ���汾�����ϰ汾����
void WOW_USART_BT_WP(void);				//ʹ��ĳЩ������д����
void WOW_USART_BT_WUP(void);			//��ֹ���� Flash ������д����
void WOW_USART_BT_RP(void);				//ʹ�ܶ�����
void WOW_USART_BT_RUP(void);			//��ֹ������


#endif  /* __DAP_H__ */
