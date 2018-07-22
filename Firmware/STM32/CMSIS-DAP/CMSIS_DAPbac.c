

#define TIMEOUT_DELAY	200000

#include "CMSIS_DAP.h"
#include "CMSIS_CDC.H"
#include "CMSIS_HID.H"
#include "CMSIS_KEY.H"
#include "CMSIS_ADC.H"
//_______________________________LCD
#include "CMSIS_Conf.H"
#include "SWO_WOW.h"

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


void BoardInit(void);

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

//#if (USBD_CDC_ACM_ENABLE == 1)
//	int32_t usb_rx_ch=-1;
//	int32_t usb_tx_ch=-1
//#endif

uint32_t led_count;
uint32_t led_timeout;
int32_t rx_num=0;
int32_t hid_num=0;
/*******************************************************************************
*������			:	main
*��������		:	������
*����				: 
*����ֵ			:	��
*******************************************************************************/
int main(void)
{
	u32 usb_num=0;	
	u32 adc_num=0;
	SystemCoreClockUpdate();		//ʱ������	
	BoardInit();
			
	
	
	#ifdef ADC_TEST
		OLED_ShowString(0,2,"ADC_TEST:");
		Delay_ms(1000);
	#endif
	
	#ifndef ADC_TEST
		#ifdef	STM32_CDC
			OLED_ShowString(0,2,"STM32_CDC Model");
		#endif
		#ifdef	CMSIS_TEST
			OLED_ShowString(0,2,"CMSIS_TEST Model");
		#endif
		Delay_ms(1000);
		UsbConnectedOff();
		LedRunningOn();

		if (UserAppDescriptor.UserInit != NULL)
		{
			pUserAppDescriptor = &UserAppDescriptor;
			pUserAppDescriptor->UserInit((CoreDescriptor_t *)&CoreDescriptor);
		}
		
		SYS_LED(7200,1000,10);
		OLED_ShowString(0,2,"USB Connectting...");
//		Delay_ms(1000);		
//		UsbConnectedOn();
		// USB Device Initialization and connect
		usbd_init();						//USB��ʼ�������á�����HID��CDC����ʱ�ӡ��жϺ�ʹ��USB����
		usbd_connect(__TRUE);
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
				OLED_ShowString(0,2,"USB Unconnect   ");				
			}
			else
			{
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
		OLED_ShowNum(40,2,0,11,16);			//��ʾ��ֵ0���˴�Ŀ��Ϊ����Connectting��ʾ���ַ�
		OLED_ShowString(120,2,"%");	
		OLED_ShowString(0,4,"ADC :");
	#else
		OLED_ShowString(0,2,"VBAT:");		
		OLED_ShowNum(40,2,0,11,16);			//��ʾ��ֵ0���˴�Ŀ��Ϊ����Connectting��ʾ���ַ�
		OLED_ShowString(120,2,"%");	
		OLED_ShowString(0,4,"HID :");
		OLED_ShowString(0,6,"UART:");	
	#endif
//	ADC_Configuration();
	SYS_LED(7200,20000,99);
	while (1)
	{	
		#ifdef	STM32_CDC			//OLED��		
			adc_num=Read_ADC();
			if(adc_num!=-1)
			{
				#ifdef	ADC_TEST			//ADC����
//					OLED_ShowString(0,4,"ADC :");
					OLED_ShowNum(48,2,ADC_Result[0],5,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(96,2,adc_num,3,16);			//��ʾASCII�ַ�����ֵ		
					OLED_ShowNum(40,4,ADC_Result[2],4,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(80,4,ADC_Result[3],4,16);//��ʾASCII�ַ�����ֵ
				#else
					OLED_ShowNum(48,2,ADC_Result[0],5,16);//��ʾASCII�ַ�����ֵ
					OLED_ShowNum(96,2,adc_num,3,16);//��ʾASCII�ַ�����ֵ
				#endif
			}
		#endif
		Delay_ms(1);				// Wait for 100ms

		
		#ifndef	ADC_TEST			//ADC����
			hid_num+=CMSIS_HID_Process();	
			#ifdef	STM32_CDC			//OLED��	
				OLED_ShowNum(40,4,hid_num,11,16);//��ʾASCII�ַ�����ֵ
			#endif			

			#if (USBD_CDC_ACM_ENABLE == 1)
				rx_num+=CMSIS_CDC_Process();
				#ifdef	STM32_CDC			//OLED��
					OLED_ShowNum(40,6,rx_num,11,16);//��ʾASCII�ַ�����ֵ
				#endif
			#endif
		#endif
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
	#ifdef	CMSIS_TEST
	RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN);
	#else
	RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);
	#endif
	// Enable SWJ only
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//	GPIO_INIT(GPIOA, INIT_PINS_A);
//	GPIO_INIT(GPIOB, INIT_PINS_B);
//	GPIO_INIT(GPIOC, INIT_PINS_C);	
	LED_Configuration();
	PORT_SWD_SETUP();	
	USB_CONNECTED_SETUP();
	OLED_Init();			//��ʼ��OLED	
	KEY_Configuration();
	#ifdef	STM32_CDC			//OLED��
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

