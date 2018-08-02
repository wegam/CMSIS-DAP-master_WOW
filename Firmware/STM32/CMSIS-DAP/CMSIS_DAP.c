

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
*函数名			:	main
*功能描述		:	主函数
*输入				: 
*返回值			:	无
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
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void main_STM32_CDC(void)
{
	u32 usb_num=0;	
	SystemCoreClockUpdate();		//时钟配置	
//	RCC_Configuration();			//系统时钟配置
	BoardInit();
			
	PowerOn();
	
	WOW_DISPALY_INIT();							//初始化显示内容
	
	WOW_USB_INIT();									//USB初始化
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
			
				usbd_init();						//USB初始化、配置、包括HID和CDC，打开时钟、中断和使能USB连接
				usbd_connect(__TRUE);
				
		//		SYS_LED(7200,10000,50);
				Delay_ms(50);
				led_count = 0;
				usb_num=0;
				while ((!usbd_configured())&&(usb_num++<usb_timeout))	// Wait for USB Device to configure		//等待USB配置完成
				{
					OLED_ShowNum(0,4,usb_num,16,16);//显示ASCII字符的码值
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

			#ifdef	ADC_TEST			//ADC测试	
				OLED_ShowString(0,2,"VBAT:");	
				OLED_ShowString(0,4,"ADC :");
		//		OLED_ShowString(120,2,"%:");
			#else
				OLED_ShowString(0,2,"VBAT:");
				OLED_ShowNum(40,2,0,11,16);		//显示数值0，此处目的为覆盖Connectting显示的字符
				OLED_ShowString(0,4,"HID :");
				OLED_ShowString(0,6,"UART:");	
			#endif
	#endif
	*/
//	ADC_Configuration();
	SYS_LED(7200,2000,50);
	WOW_USART_BT_Configuration();	//串口下载端口初始化
	#ifndef	USB_TEST
		#ifndef	STM32_CDC			//OLED板
			CMSIS_MX25L4006E_Configuration();
		#endif
	#endif
	
	while (1)
	{
		
		
		#ifdef	STM32_CDC			//OLED板
			int16_t adc_num=0;			
			adc_num=Read_ADC();
			if(adc_num!=-1)
			{
				#ifdef	ADC_TEST			//ADC测试
//					OLED_ShowString(0,4,"ADC :");
					
					OLED_ShowNum(40,2,ADC_Result[0],4,16);//显示ASCII字符的码值
					OLED_ShowNum(80,2,ADC_Result[1],4,16);//显示ASCII字符的码值		
					OLED_ShowNum(40,4,ADC_Result[2],4,16);//显示ASCII字符的码值
					OLED_ShowNum(80,4,ADC_Result[3],4,16);//显示ASCII字符的码值
				#else
					OLED_ShowNum(40,2,ADC_Result[0],11,16);//显示ASCII字符的码值
				#endif
				OLED_ShowNum(104,0,adc_num,3,16);//显示ASCII字符的码值
			}
		#endif
		
		
//		if(usb_flg==usb_connected)
//		{
			#ifndef	SWD_TEST
				#ifndef	ADC_TEST			//ADC测试
					hid_num+=CMSIS_HID_Process();	
					#ifdef	STM32_CDC			//OLED板
					if(hid_numbac!=hid_num)
					{
						hid_numbac	=	hid_num;
						hid_time		=	0;
					}
					if(hid_time++>100)
					{
						hid_time		=	0;
						OLED_ShowNum(40,4,hid_num,11,16);//显示ASCII字符的码值
					}
					#endif			
					
					#if (USBD_CDC_ACM_ENABLE == 1)
						rx_num+=CMSIS_CDC_Process();
						#ifdef	STM32_CDC			//OLED板
							OLED_ShowNum(40,6,rx_num,11,16);//显示ASCII字符的码值---串口计数
						#endif
					#endif
				#endif
			#endif
//		}

		if(hid_num>999999)
			hid_num=0;
		if(rx_num>999999)
			rx_num=0;
		
		//————————————————————————————OLED显示
//		WOW_DISPALY_Event();	
		//————————————————————————————输入检测/按键/充电状态
//		WOW_KEY_Event();	
//		//————————————————————————————USB数据处理
//		WOW_USB_Event();
	}

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void main_USB_TEST(void)
{
		u32 usb_num=0;	
	SystemCoreClockUpdate();		//时钟配置	
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
			
				usbd_init();						//USB初始化、配置、包括HID和CDC，打开时钟、中断和使能USB连接
				usbd_connect(__TRUE);
				
		//		SYS_LED(7200,10000,50);
				Delay_ms(50);
				led_count = 0;
				usb_num=0;
				while ((!usbd_configured())&&(usb_num++<usb_timeout))	// Wait for USB Device to configure		//等待USB配置完成
				{
					#ifdef	STM32_CDC
					OLED_ShowNum(0,4,usb_num,16,16);//显示ASCII字符的码值
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

			#ifdef	ADC_TEST			//ADC测试	
				OLED_ShowString(0,2,"VBAT:");	
				OLED_ShowString(0,4,"ADC :");
		//		OLED_ShowString(120,2,"%:");
			#else
				OLED_ShowString(0,2,"VBAT:");
				OLED_ShowNum(40,2,0,11,16);		//显示数值0，此处目的为覆盖Connectting显示的字符
				OLED_ShowString(0,4,"HID :");
				OLED_ShowString(0,6,"UART:");	
			#endif
	#endif
//	ADC_Configuration();
	SYS_LED(7200,2000,50);
	WOW_USART_BT_Configuration();	//串口下载端口初始化
	#ifndef	USB_TEST
		#ifndef	STM32_CDC			//OLED板
			CMSIS_MX25L4006E_Configuration();
		#endif
	#endif
	while (1)
	{

		
		
		#ifdef	STM32_CDC			//OLED板
			int16_t adc_num=0;			
			adc_num=Read_ADC();
			if(adc_num!=-1)
			{
				#ifdef	ADC_TEST			//ADC测试
//					OLED_ShowString(0,4,"ADC :");
					
					OLED_ShowNum(40,2,ADC_Result[0],4,16);//显示ASCII字符的码值
					OLED_ShowNum(80,2,ADC_Result[1],4,16);//显示ASCII字符的码值		
					OLED_ShowNum(40,4,ADC_Result[2],4,16);//显示ASCII字符的码值
					OLED_ShowNum(80,4,ADC_Result[3],4,16);//显示ASCII字符的码值
				#else
					OLED_ShowNum(40,2,ADC_Result[0],11,16);//显示ASCII字符的码值
				#endif
				OLED_ShowNum(104,0,adc_num,3,16);//显示ASCII字符的码值
			}
		#endif
		
		
		if(usb_flg==usb_connected)
		{
			#ifndef	SWD_TEST
				#ifndef	ADC_TEST			//ADC测试
					hid_num+=CMSIS_HID_Process();	
					#ifdef	STM32_CDC			//OLED板	
						OLED_ShowNum(40,4,hid_num,11,16);//显示ASCII字符的码值
					#endif			
					
					#if (USBD_CDC_ACM_ENABLE == 1)
						rx_num+=CMSIS_CDC_Process();
						#ifdef	STM32_CDC			//OLED板
							OLED_ShowNum(40,6,rx_num,11,16);//显示ASCII字符的码值---串口计数
						#endif
					#endif
				#endif
			#endif
		}

		#ifndef	USB_TEST
			#ifndef	STM32_CDC			//OLED板
				CMSIS_MX25L4006E_Server();
				if(FLASH_ID)
				{
					OLED_ShowString(40,6,&FLASH_ID);
					OLED_ShowNum(40,6,FLASH_ID,11,16);//显示ASCII字符的码值
			}
			#endif
		#endif
		
		
		//————————————————————————————OLED显示
//		WOW_DISPALY_Event();	
		//————————————————————————————输入检测/按键/充电状态
//		WOW_KEY_Event();	
		//————————————————————————————USB数据处理
//		WOW_USB_Event();
	}

}
/*******************************************************************************
* 函数名		:	RCC_Configuration
* 功能描述	:	系统时钟配置 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();																	//复位系统时钟
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);										//打开外部高速时钟
	
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();		//等待外部高速时钟启动
	
	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//使能或者失能预取指缓存
		
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);					//设置代码延时值
		
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 						//设置AHB时钟（HCLK）
		
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); 						//设置高速AHB时钟（PCLK2）
		
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);							//设置低速AHB时钟（PCLK1）
		
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	//设置PLL时钟源及倍频系数 
		
		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);			//使能或者失能PLL
		
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//设置系统时钟源（SYSCLK）
		
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)				//返回用作系统时钟的时钟源
		{
		}
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
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
//	Power_Control_SETUP();		//STM_CDC电源锁定配置	
	LED_Configuration();
	PORT_SWD_SETUP();	
	#ifndef	SWD_TEST
		USB_CONNECTED_SETUP();
	#endif
	OLED_Init();							//初始化OLED	
	
	KEY_Configuration();			//按键初始化
	#ifdef	STM32_CDC					//OLED板
		ADC_Configuration();
	#endif
	LedRunningOff();
	UsbConnectedOff();
	LedConnectedOff();	
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void USBD_Error_Event(void)
{
	LedConnectedOn();
	LedRunningOn();

	usbd_connect(__FALSE);		//断开连接
	usbd_reset_core();				//复位USB的一些数据标志

	HardFault_Handler();			//错误处理--LED显示、重启系统
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void WOW_KEY_Event(void)
{
#ifdef	STM32_CDC			//OLED板
	if((Read_Input()&0x01)==0x01)		//正在充电/右键
	{
		key_num++;
	}
	else
	{
		key_num=0;
		key_flg&=0XFE;
	}
	if((Read_Input()&0x02)==0x02)	//充电满
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
	
	if((Read_Input()&0x01)==0x01)		//正在充电/右键
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
//		WOW_USART_BT_Start();		//启用串口自举程序
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
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void WOW_USB_Event(void)
{
		if(usb_flg==usb_connected)
		{
			#ifndef	SWD_TEST
				#ifndef	ADC_TEST			//ADC测试
					hid_num+=CMSIS_HID_Process();	
					#ifdef	STM32_CDC			//OLED板	
						OLED_ShowNum(40,4,hid_num,11,16);//显示ASCII字符的码值
					#endif			
					
					#if (USBD_CDC_ACM_ENABLE == 1)
						rx_num+=CMSIS_CDC_Process();
						#ifdef	STM32_CDC			//OLED板
							OLED_ShowNum(40,6,rx_num,11,16);//显示ASCII字符的码值---串口计数
						#endif
					#endif
				#endif
			#endif
		}
}
/*******************************************************************************
*函数名			:	DISPALY_INIT
*功能描述		:	USB初始化
*输入				: 
*返回值			:	无
*******************************************************************************/
void WOW_USB_INIT(void)
{	
	u32 usb_num=0;
	


	UsbConnectedOff();		//断开USB连接

	if (UserAppDescriptor.UserInit != NULL)
	{
		pUserAppDescriptor = &UserAppDescriptor;
		pUserAppDescriptor->UserInit((CoreDescriptor_t *)&CoreDescriptor);
	}

	usbd_init();						//USB初始化、配置、包括HID和CDC，打开时钟、中断和使能USB连接
	usbd_connect(__TRUE);

	Delay_ms(50);

	usb_num=0;
	while ((!usbd_configured())&&(usb_num++<usb_timeout))	// Wait for USB Device to configure		//等待USB配置完成
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
*函数名			:	DISPALY_INIT
*功能描述		:	初始化显示内容
*输入				: 
*返回值			:	无
*******************************************************************************/
void WOW_DISPALY_INIT(void)
{	
	OLED_Clear();			//清除显示
	
	//-------------ADC测试模式
	#ifdef ADC_TEST
		OLED_ShowString(0,0,"ADC_TEST");
		OLED_ShowString(0,2,"VBAT:");	
		OLED_ShowString(0,4,"ADC :");
	
	//-------------CMSIS-DAP模式
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
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void WOW_DISPALY_Event(void)
{		
	#ifdef	STM32_CDC			//OLED板	
	int16_t adc_num=0;	
		adc_num=Read_ADC();
		#ifdef	ADC_TEST			//ADC测试
			Delay_ms(1);
		#endif
		if(adc_num!=-1)
		{
			#ifdef	ADC_TEST			//ADC测试
				OLED_ShowNum(40,2,ADC_Result[0],4,16);//显示ASCII字符的码值
				OLED_ShowNum(80,2,ADC_Result[1],4,16);//显示ASCII字符的码值		
				OLED_ShowNum(40,4,ADC_Result[2],4,16);//显示ASCII字符的码值
				OLED_ShowNum(80,4,ADC_Result[3],4,16);//显示ASCII字符的码值
			#else
				OLED_ShowNum(40,2,ADC_Result[0],11,16);//显示ASCII字符的码值
			#endif
			OLED_ShowNum(104,0,adc_num,3,16);//显示ASCII字符的码值
		}
	#endif
}

