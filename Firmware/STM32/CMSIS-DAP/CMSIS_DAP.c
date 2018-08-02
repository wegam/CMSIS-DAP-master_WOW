

#define TIMEOUT_DELAY	200000

#include "CMSIS_DAP.h"
#include "CMSIS_CDC.H"
#include "CMSIS_HID.H"
#include "CMSIS_KEY.H"
#include "CMSIS_ADC.H"
#include "CMSIS_MX25L4006E.H"

#include "WOW_USART_BootLoader.h"
//_______________________________LCD
#include "CMSIS_Conf.H"
#include "SWD_WOW.h"

//_______________________________LCD
#include "oled.h"
#include "bmp.h"
#include "delay.h"
//_______________________________HID
#include "usbd_user_hid.h"

#include "stdio.h"

#include "RTL.h"
#include "rl_usb.h"
#include "stm32f10x.h"

#define  __NO_USB_LIB_C
#include "usb_config.c"

#include "CMSIS_Conf.H"
#include "DAP.h"

#include "usbd_user_cdc_acm.h"

#define	usb_timeout	0x0FFF


//void BoardInit(void);

extern const UserAppDescriptor_t UserAppDescriptor;

UserAppDescriptor_t * pUserAppDescriptor = NULL;			//20170322
//const UserAppDescriptor_t * pUserAppDescriptor = {
//	&UserAppInit,
//	&DAP_ProcessCommand,
//	&UserAppAbort
//};

const CoreDescriptor_t CoreDescriptor = {
	&LedConnectedOut,
	&LedRunningOut,
};

enum usb_stats
{
	usb_unconnect=0,
	usb_connected=1
};
//#if (USBD_CDC_ACM_ENABLE == 1)
//	int32_t usb_rx_ch=-1;
//	int32_t usb_tx_ch=-1
//#endif

uint32_t led_count;
uint32_t led_timeout;
int32_t rx_num=0;
int32_t hid_num=0;
int32_t hid_numbac=0;
int32_t hid_time=0;
int32_t key_num=0;
int32_t bat_num=0;
int8_t key_flg=0;
int32_t Rkey_num=0;
int8_t usb_flg=usb_unconnect;
/*******************************************************************************
*������			:	main
*��������		:	������
*����				: 
*����ֵ			:	��
*******************************************************************************/
int main(void)
{
	#ifdef	STM32_CDC
	main_STM32_CDC();
	#elif	USB_TEST
	main_USB_TEST();
	#else
	#error	"ndefine bd"
	#endif

}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void main_STM32_CDC(void)
{
	u32 usb_num=0;	
	SystemCoreClockUpdate();		//ʱ������	
//	RCC_Configuration();			//ϵͳʱ������
	BoardInit();
			
	PowerOn();
	
	WOW_DISPALY_INIT();							//��ʼ����ʾ����
	
	WOW_USB_INIT();									//USB��ʼ��
/*	
	#ifndef ADC_TEST
		#ifndef	SWD_TEST
				OLED_ShowString(0,2,"STM32_CDC Model");

			Delay_ms(1000);
			UsbConnectedOff();
			LedRunningOn();
			
			if (UserAppDescriptor.UserInit != NULL)
			{
				pUserAppDescriptor = &UserAppDescriptor;
				pUserAppDescriptor->UserInit((CoreDescriptor_t *)&CoreDescriptor);
			}			
			SYS_LED(7200,1000,50);
			OLED_ShowString(0,2,"USB Connectting...");
	//		Delay_ms(1000);		
	//		UsbConnectedOn();
	// 		USB Device Initialization and connect
			
				usbd_init();						//USB��ʼ�������á�����HID��CDC����ʱ�ӡ��жϺ�ʹ��USB����
				usbd_connect(__TRUE);
				
		//		SYS_LED(7200,10000,50);
				Delay_ms(50);
				led_count = 0;
				usb_num=0;
				while ((!usbd_configured())&&(usb_num++<usb_timeout))	// Wait for USB Device to configure		//�ȴ�USB�������
				{
					OLED_ShowNum(0,4,usb_num,16,16);//��ʾASCII�ַ�����ֵ
				}
				if(usb_num>=usb_timeout-1)
				{
					usb_flg=usb_unconnect;
					OLED_ShowString(0,2,"USB Unconnect   ");				
				}
				else
				{
					usb_flg=usb_connected;
					OLED_ShowString(0,2,"USB Connected   ");
				}
				Delay_ms(1000);	
			
				usb_num=0;
				LED_Configuration();
				LedRunningOn();
				
				led_count = 0;
				led_timeout = TIMEOUT_DELAY;
			#endif

			#ifdef	ADC_TEST			//ADC����	
				OLED_ShowString(0,2,"VBAT:");	
				OLED_ShowString(0,4,"ADC :");
		//		OLED_ShowString(120,2,"%:");
			#else
				OLED_ShowString(0,2,"VBAT:");
				OLED_ShowNum(40,2,0,11,16);		//��ʾ��ֵ0���˴�Ŀ��Ϊ����Connectting��ʾ���ַ�
				OLED_ShowString(0,4,"HID :");
				OLED_ShowString(0,6,"UART:");	
			#endif
	#endif
	*/
//	ADC_Configuration();
	SYS_LED(7200,2000,50);
	WOW_USART_BT_Configuration();	//�������ض˿ڳ�ʼ��
	#ifndef	USB_TEST
		#ifndef	STM32_CDC			//OLED��
			CMSIS_MX25L4006E_Configuration();
		#endif
	#endif
	
	while (1)
	{
		
		
		#ifdef	STM32_CDC			//OLED��
			int16_t adc_num=0;			
			adc_num=Read_ADC();
			if(adc_num!=-1)
			{
				#ifdef	ADC_TEST			//ADC����
//					OLED_ShowString(0,4,"ADC :");
					
					OLED_ShowNum(40,2,ADC_Result[0],4,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(80,2,ADC_Result[1],4,16);//��ʾASCII�ַ�����ֵ		
					OLED_ShowNum(40,4,ADC_Result[2],4,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(80,4,ADC_Result[3],4,16);//��ʾASCII�ַ�����ֵ
				#else
					OLED_ShowNum(40,2,ADC_Result[0],11,16);//��ʾASCII�ַ�����ֵ
				#endif
				OLED_ShowNum(104,0,adc_num,3,16);//��ʾASCII�ַ�����ֵ
			}
		#endif
		
		
//		if(usb_flg==usb_connected)
//		{
			#ifndef	SWD_TEST
				#ifndef	ADC_TEST			//ADC����
					hid_num+=CMSIS_HID_Process();	
					#ifdef	STM32_CDC			//OLED��
					if(hid_numbac!=hid_num)
					{
						hid_numbac	=	hid_num;
						hid_time		=	0;
					}
					if(hid_time++>100)
					{
						hid_time		=	0;
						OLED_ShowNum(40,4,hid_num,11,16);//��ʾASCII�ַ�����ֵ
					}
					#endif			
					
					#if (USBD_CDC_ACM_ENABLE == 1)
						rx_num+=CMSIS_CDC_Process();
						#ifdef	STM32_CDC			//OLED��
							OLED_ShowNum(40,6,rx_num,11,16);//��ʾASCII�ַ�����ֵ---���ڼ���
						#endif
					#endif
				#endif
			#endif
//		}

		if(hid_num>999999)
			hid_num=0;
		if(rx_num>999999)
			rx_num=0;
		
		//��������������������������������������������������������OLED��ʾ
//		WOW_DISPALY_Event();	
		//��������������������������������������������������������������/����/���״̬
//		WOW_KEY_Event();	
//		//��������������������������������������������������������USB���ݴ���
//		WOW_USB_Event();
	}

}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void main_USB_TEST(void)
{
		u32 usb_num=0;	
	SystemCoreClockUpdate();		//ʱ������	
	BoardInit();
			
	PowerOn();
	
	#ifdef ADC_TEST
		OLED_ShowString(0,2,"ADC_TEST:");
		Delay_ms(1000);
	#endif
	
	#ifndef ADC_TEST
		#ifndef	SWD_TEST
			#ifdef	STM32_CDC
				OLED_ShowString(0,2,"STM32_CDC Model");
			#endif
			#ifdef	USB_TEST
				OLED_ShowString(0,2,"USB_TEST Model");
			#endif
			Delay_ms(1000);
			UsbConnectedOff();
			LedRunningOn();
			
			if (UserAppDescriptor.UserInit != NULL)
			{
				pUserAppDescriptor = &UserAppDescriptor;
				pUserAppDescriptor->UserInit((CoreDescriptor_t *)&CoreDescriptor);
			}
			
			SYS_LED(7200,1000,50);
			OLED_ShowString(0,2,"USB Connectting...");
	//		Delay_ms(1000);		
	//		UsbConnectedOn();
	// 		USB Device Initialization and connect
			
				usbd_init();						//USB��ʼ�������á�����HID��CDC����ʱ�ӡ��жϺ�ʹ��USB����
				usbd_connect(__TRUE);
				
		//		SYS_LED(7200,10000,50);
				Delay_ms(50);
				led_count = 0;
				usb_num=0;
				while ((!usbd_configured())&&(usb_num++<usb_timeout))	// Wait for USB Device to configure		//�ȴ�USB�������
				{
					#ifdef	STM32_CDC
					OLED_ShowNum(0,4,usb_num,16,16);//��ʾASCII�ַ�����ֵ
					#endif
				}
				#ifdef	STM32_CDC
					if(usb_num>=usb_timeout-1)
					{
						usb_flg=usb_unconnect;
						OLED_ShowString(0,2,"USB Unconnect   ");				
					}
					else
					{
						usb_flg=usb_connected;
						OLED_ShowString(0,2,"USB Connected   ");
					}
					Delay_ms(1000);	
				#endif
			
				usb_num=0;
				LED_Configuration();
				LedRunningOn();
				
				led_count = 0;
				led_timeout = TIMEOUT_DELAY;
			#endif

			#ifdef	ADC_TEST			//ADC����	
				OLED_ShowString(0,2,"VBAT:");	
				OLED_ShowString(0,4,"ADC :");
		//		OLED_ShowString(120,2,"%:");
			#else
				OLED_ShowString(0,2,"VBAT:");
				OLED_ShowNum(40,2,0,11,16);		//��ʾ��ֵ0���˴�Ŀ��Ϊ����Connectting��ʾ���ַ�
				OLED_ShowString(0,4,"HID :");
				OLED_ShowString(0,6,"UART:");	
			#endif
	#endif
//	ADC_Configuration();
	SYS_LED(7200,2000,50);
	WOW_USART_BT_Configuration();	//�������ض˿ڳ�ʼ��
	#ifndef	USB_TEST
		#ifndef	STM32_CDC			//OLED��
			CMSIS_MX25L4006E_Configuration();
		#endif
	#endif
	while (1)
	{

		
		
		#ifdef	STM32_CDC			//OLED��
			int16_t adc_num=0;			
			adc_num=Read_ADC();
			if(adc_num!=-1)
			{
				#ifdef	ADC_TEST			//ADC����
//					OLED_ShowString(0,4,"ADC :");
					
					OLED_ShowNum(40,2,ADC_Result[0],4,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(80,2,ADC_Result[1],4,16);//��ʾASCII�ַ�����ֵ		
					OLED_ShowNum(40,4,ADC_Result[2],4,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(80,4,ADC_Result[3],4,16);//��ʾASCII�ַ�����ֵ
				#else
					OLED_ShowNum(40,2,ADC_Result[0],11,16);//��ʾASCII�ַ�����ֵ
				#endif
				OLED_ShowNum(104,0,adc_num,3,16);//��ʾASCII�ַ�����ֵ
			}
		#endif
		
		
		if(usb_flg==usb_connected)
		{
			#ifndef	SWD_TEST
				#ifndef	ADC_TEST			//ADC����
					hid_num+=CMSIS_HID_Process();	
					#ifdef	STM32_CDC			//OLED��	
						OLED_ShowNum(40,4,hid_num,11,16);//��ʾASCII�ַ�����ֵ
					#endif			
					
					#if (USBD_CDC_ACM_ENABLE == 1)
						rx_num+=CMSIS_CDC_Process();
						#ifdef	STM32_CDC			//OLED��
							OLED_ShowNum(40,6,rx_num,11,16);//��ʾASCII�ַ�����ֵ---���ڼ���
						#endif
					#endif
				#endif
			#endif
		}

		#ifndef	USB_TEST
			#ifndef	STM32_CDC			//OLED��
				CMSIS_MX25L4006E_Server();
				if(FLASH_ID)
				{
					OLED_ShowString(40,6,&FLASH_ID);
					OLED_ShowNum(40,6,FLASH_ID,11,16);//��ʾASCII�ַ�����ֵ
			}
			#endif
		#endif
		
		
		//��������������������������������������������������������OLED��ʾ
//		WOW_DISPALY_Event();	
		//��������������������������������������������������������������/����/���״̬
//		WOW_KEY_Event();	
		//��������������������������������������������������������USB���ݴ���
//		WOW_USB_Event();
	}

}
/*******************************************************************************
* ������		:	RCC_Configuration
* ��������	:	ϵͳʱ������ 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();																	//��λϵͳʱ��
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);										//���ⲿ����ʱ��
	
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();		//�ȴ��ⲿ����ʱ������
	
	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//ʹ�ܻ���ʧ��Ԥȡָ����
		
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);					//���ô�����ʱֵ
		
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 						//����AHBʱ�ӣ�HCLK��
		
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); 						//���ø���AHBʱ�ӣ�PCLK2��
		
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);							//���õ���AHBʱ�ӣ�PCLK1��
		
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	//����PLLʱ��Դ����Ƶϵ�� 
		
		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);			//ʹ�ܻ���ʧ��PLL
		
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//����ϵͳʱ��Դ��SYSCLK��
		
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)				//��������ϵͳʱ�ӵ�ʱ��Դ
		{
		}
	}
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void BoardInit(void)
{	
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);
	GPIO_DeInit(GPIOF);
	// Enable GPIOA-GPIOC
	#ifdef	USB_TEST
	RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN);
	#else
	RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);
	#endif
	// Enable SWJ only
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//	GPIO_INIT(GPIOA, INIT_PINS_A);
//	GPIO_INIT(GPIOB, INIT_PINS_B);
//	GPIO_INIT(GPIOC, INIT_PINS_C);
//	Power_Control_SETUP();		//STM_CDC��Դ��������	
	LED_Configuration();
	PORT_SWD_SETUP();	
	#ifndef	SWD_TEST
		USB_CONNECTED_SETUP();
	#endif
	OLED_Init();							//��ʼ��OLED	
	
	KEY_Configuration();			//������ʼ��
	#ifdef	STM32_CDC					//OLED��
		ADC_Configuration();
	#endif
	LedRunningOff();
	UsbConnectedOff();
	LedConnectedOff();	
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void USBD_Error_Event(void)
{
	LedConnectedOn();
	LedRunningOn();

	usbd_connect(__FALSE);		//�Ͽ�����
	usbd_reset_core();				//��λUSB��һЩ���ݱ�־

	HardFault_Handler();			//������--LED��ʾ������ϵͳ
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void WOW_KEY_Event(void)
{
#ifdef	STM32_CDC			//OLED��
	if((Read_Input()&0x01)==0x01)		//���ڳ��/�Ҽ�
	{
		key_num++;
	}
	else
	{
		key_num=0;
		key_flg&=0XFE;
	}
	if((Read_Input()&0x02)==0x02)	//�����
	{
		bat_num++;
	}
	else
	{
		bat_num=0;
		key_flg&=0XFD;
	}
	if(key_num>0x09FF)
	{
		if((key_flg&0x01)!=0x01)
		{
			key_flg|=0x01;
			SYS_LED(7200,1000,50);
//			PowerOff();
//			while(1);
		}
	}
	if(bat_num>0xFF)
	{
		if((key_flg&0x02)!=0x02)
		{
			key_flg|=0x02;
			SYS_LED(7200,10000,95);
			OLED_ShowString(0,2,"FULL:");
		}
	}
#else
	
	if((Read_Input()&0x01)==0x01)		//���ڳ��/�Ҽ�
	{
		Rkey_num++;		
	}
	else
	{
		Rkey_num=0;
	}
	if(Rkey_num==10000)
	{
//		WOW_USART_BT_Get();
//		WOW_USART_BT_Start();		//���ô����Ծٳ���
//		SWD_Line_RESET();			
//		SWD_Read_IDCODE();
	}
	if(Rkey_num>100000)
	{
		Rkey_num=0;
	}
	
#endif
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void WOW_USB_Event(void)
{
		if(usb_flg==usb_connected)
		{
			#ifndef	SWD_TEST
				#ifndef	ADC_TEST			//ADC����
					hid_num+=CMSIS_HID_Process();	
					#ifdef	STM32_CDC			//OLED��	
						OLED_ShowNum(40,4,hid_num,11,16);//��ʾASCII�ַ�����ֵ
					#endif			
					
					#if (USBD_CDC_ACM_ENABLE == 1)
						rx_num+=CMSIS_CDC_Process();
						#ifdef	STM32_CDC			//OLED��
							OLED_ShowNum(40,6,rx_num,11,16);//��ʾASCII�ַ�����ֵ---���ڼ���
						#endif
					#endif
				#endif
			#endif
		}
}
/*******************************************************************************
*������			:	DISPALY_INIT
*��������		:	USB��ʼ��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void WOW_USB_INIT(void)
{	
	u32 usb_num=0;
	


	UsbConnectedOff();		//�Ͽ�USB����

	if (UserAppDescriptor.UserInit != NULL)
	{
		pUserAppDescriptor = &UserAppDescriptor;
		pUserAppDescriptor->UserInit((CoreDescriptor_t *)&CoreDescriptor);
	}

	usbd_init();						//USB��ʼ�������á�����HID��CDC����ʱ�ӡ��жϺ�ʹ��USB����
	usbd_connect(__TRUE);

	Delay_ms(50);

	usb_num=0;
	while ((!usbd_configured())&&(usb_num++<usb_timeout))	// Wait for USB Device to configure		//�ȴ�USB�������
	{
	}
	if(usb_num>=usb_timeout-1)
	{
		usb_flg=usb_unconnect;
	}
	else
	{
		usb_flg=usb_connected;
	}

}
/*******************************************************************************
*������			:	DISPALY_INIT
*��������		:	��ʼ����ʾ����
*����				: 
*����ֵ			:	��
*******************************************************************************/
void WOW_DISPALY_INIT(void)
{	
	OLED_Clear();			//�����ʾ
	
	//-------------ADC����ģʽ
	#ifdef ADC_TEST
		OLED_ShowString(0,0,"ADC_TEST");
		OLED_ShowString(0,2,"VBAT:");	
		OLED_ShowString(0,4,"ADC :");
	
	//-------------CMSIS-DAPģʽ
	#elif	STM32_CDC
		OLED_ShowString(0,0,"CMSIS-DAP:SWD");
		OLED_ShowString(0,2,"VBAT:");
		OLED_ShowString(0,4,"HID :");
		OLED_ShowString(0,6,"UART:");
//		OLED_ShowString(0,6,"RX:");
//		OLED_ShowString(64,6,"TX:");
	#else
//		#error "Board undefined"
	OLED_ShowString(0,0,"Board undefined");
	#endif
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void WOW_DISPALY_Event(void)
{		
	#ifdef	STM32_CDC			//OLED��	
	int16_t adc_num=0;	
		adc_num=Read_ADC();
		#ifdef	ADC_TEST			//ADC����
			Delay_ms(1);
		#endif
		if(adc_num!=-1)
		{
			#ifdef	ADC_TEST			//ADC����
				OLED_ShowNum(40,2,ADC_Result[0],4,16);//��ʾASCII�ַ�����ֵ
				OLED_ShowNum(80,2,ADC_Result[1],4,16);//��ʾASCII�ַ�����ֵ		
				OLED_ShowNum(40,4,ADC_Result[2],4,16);//��ʾASCII�ַ�����ֵ
				OLED_ShowNum(80,4,ADC_Result[3],4,16);//��ʾASCII�ַ�����ֵ
			#else
				OLED_ShowNum(40,2,ADC_Result[0],11,16);//��ʾASCII�ַ�����ֵ
			#endif
			OLED_ShowNum(104,0,adc_num,3,16);//��ʾASCII�ַ�����ֵ
		}
	#endif
}

