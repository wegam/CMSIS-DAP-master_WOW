#include "CMSIS_Conf.H"

#include "STM32F10x_BitBand.h"
#include "usbd_user_cdc_acm.h"
#include "usb_cdc.h"
#include "rl_usb.h"

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/*******************************************************************************
*函数名			:	LedConnectedOn
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedConnectedOn(void)
{
	LED_CONNECTED_SET=0;
}
/*******************************************************************************
*函数名			:	LedConnectedOff
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedConnectedOff(void)
{
	LED_CONNECTED_SET=1;
}
/*******************************************************************************
*函数名			:	LedConnectedToggle
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedConnectedToggle(void)
{
	LED_CONNECTED_PORT->ODR 	^= LED_CONNECTED;
}
/*******************************************************************************
*函数名			:	LedRunningOn
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedRunningOn(void)
{
	LED_RUNNING_SET=0;
}
/*******************************************************************************
*函数名			:	LedRunningOff
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedRunningOff(void)
{
	LED_RUNNING_SET=1;
}
/*******************************************************************************
*函数名			:	LedRunningToggle
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedRunningToggle(void)
{
	LED_RUNNING_PORT->ODR			^= LED_RUNNING;
}
/*******************************************************************************
*函数名			:	LedConnectedOut
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedConnectedOut(uint16_t bit)
{
	if (bit & 1)
		LedConnectedOn();
	else			
		LedConnectedOff();
}
/*******************************************************************************
*函数名			:	LedRunningOut
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LedRunningOut(uint16_t bit)
{
	if (bit & 1)
		LedRunningOn();
	else
		LedRunningOff();
}
/*******************************************************************************
*函数名			:	UsbConnectedOn
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void UsbConnectedOn(void)
{
	#ifdef	STM32_CDC			//OLED板
		USB_CONNECTED_PORT->BSRR 	= USB_CONNECTED;
	#else
		USB_CONNECTED_PORT->BRR 	= USB_CONNECTED;
	#endif
}
/*******************************************************************************
*函数名			:	UsbConnectedOff
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void UsbConnectedOff(void)
{
	#ifdef	STM32_CDC			//OLED板
		USB_CONNECTED_PORT->BRR  	= USB_CONNECTED;
	#else
		USB_CONNECTED_PORT->BSRR  = USB_CONNECTED;
	#endif
}
/*******************************************************************************
*函数名			:	UsbConnectedOff
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void PowerOn(void)
{
	#ifdef	STM32_CDC			//OLED板
		POWER_LOCK_PORT->BSRR  	= POWER_CONNECTED;
	#endif
}
/*******************************************************************************
*函数名			:	UsbConnectedOff
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void PowerOff(void)
{
	#ifdef	STM32_CDC			//OLED板
		POWER_LOCK_PORT->BRR  	= POWER_CONNECTED;
	#endif
}



// SWCLK/TCK I/O pin -------------------------------------

/** SWCLK/TCK I/O pin: Get Input.
\return Current status of the SWCLK/TCK DAP hardware I/O pin.
*/
uint8_t PIN_SWCLK_TCK_IN(void)
{
	return (PIN_SWCLK_TCK_PORT->ODR & PIN_SWCLK_TCK) ? 1 : 0;
}

/** SWCLK/TCK I/O pin: Set Output to High.
Set the SWCLK/TCK DAP hardware I/O pin to high level.
*/
void PIN_SWCLK_TCK_SET(void)
{
	PIN_SWCLK_TCK_PORT->BSRR = PIN_SWCLK_TCK;
}

/** SWCLK/TCK I/O pin: Set Output to Low.
Set the SWCLK/TCK DAP hardware I/O pin to low level.
*/
void PIN_SWCLK_TCK_CLR (void)
{
	PIN_SWCLK_TCK_PORT->BRR = PIN_SWCLK_TCK;
}

// SWDIO/TMS Pin I/O --------------------------------------

/** SWDIO/TMS I/O pin: Get Input.
\return Current status of the SWDIO/TMS DAP hardware I/O pin.
*/
uint8_t PIN_SWDIO_TMS_IN(void)
{
	return (PIN_SWDIO_TMS_PORT->IDR & PIN_SWDIO_TMS) ? 1 : 0;
}

/** SWDIO/TMS I/O pin: Set Output to High.
Set the SWDIO/TMS DAP hardware I/O pin to high level.
*/
void PIN_SWDIO_TMS_SET(void)
{
	PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS;
}

///** SWDIO/TMS I/O pin: Set Output to Low.
//Set the SWDIO/TMS DAP hardware I/O pin to low level.
//*/
//void PIN_SWDIO_TMS_CLR(void)
//{
//	PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS;
//}

/** SWDIO I/O pin: Get Input (used in SWD mode only).
\return Current status of the SWDIO DAP hardware I/O pin.
*/
uint8_t PIN_SWDIO_IN (void)
{
	if (PIN_SWDIO_TMS_PORT->IDR & PIN_SWDIO_TMS)
		return 1;
	return 0;
}

/** SWDIO I/O pin: Set Output (used in SWD mode only).
\param bit Output value for the SWDIO DAP hardware I/O pin.
*/
//void PIN_SWDIO_OUT(uint8_t bit)
//{
//	if (bit & 1)
//		PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS;
//	else
//		PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS;
//}

/** SWDIO I/O pin: Switch to Output mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to output mode. This function is
called prior \ref PIN_SWDIO_OUT function calls.
*/
void PIN_SWDIO_OUT_ENABLE(void)
{
//	PIN_SWDIO_TMS_OUT_ENABLE();
	#if (PIN_SWDIO_TMS_PIN >= 8)
		PIN_SWDIO_TMS_PORT->CRH = (PIN_SWDIO_TMS_PORT->CRH & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN - 8)) | PIN_MODE(0x3, PIN_SWDIO_TMS_PIN - 8);
//		PIN_SWDIO_TMS_PORT->BSRR  = PIN_SWDIO_TMS;
//		SWD_WOW_DIOH();
	#else
		PIN_SWDIO_TMS_PORT->CRL = (PIN_SWDIO_TMS_PORT->CRL & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN)) | PIN_MODE(0x3, PIN_SWDIO_TMS_PIN);
//		PIN_SWDIO_TMS_PORT->BSRR  = PIN_SWDIO_TMS;
//		SWD_WOW_DIOH();
	#endif
}

/** SWDIO I/O pin: Switch to Input mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to input mode. This function is
called prior \ref PIN_SWDIO_IN function calls.
*/
void PIN_SWDIO_OUT_DISABLE(void)
{
	//快速设置GPIO，without GPIO_Init call
//	PIN_SWDIO_TMS_OUT_DISABLE();
	#if (PIN_SWDIO_TMS_PIN >= 8)
		PIN_SWDIO_TMS_PORT->CRH = (PIN_SWDIO_TMS_PORT->CRH & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN - 8)) | PIN_MODE(0x8, PIN_SWDIO_TMS_PIN - 8);
//		PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS;
//		SWD_WOW_DIOH();
	#else
		PIN_SWDIO_TMS_PORT->CRL = (PIN_SWDIO_TMS_PORT->CRL & ~PIN_MODE_MASK(PIN_SWDIO_TMS_PIN)) | PIN_MODE(0x8, PIN_SWDIO_TMS_PIN);
//		PIN_SWDIO_TMS_PORT->BSRR = PIN_SWDIO_TMS;
//		SWD_WOW_DIOH();
	#endif
}
/** SWDIO I/O pin: Switch to Output mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to output mode. This function is
called prior \ref PIN_SWDIO_OUT function calls.
*/
void PIN_SWCLK_OUT_ENABLE(void)
{
//	PIN_SWDIO_TMS_OUT_ENABLE();
	#if (PIN_SWCLK_TCK_PIN >= 8)
		PIN_SWCLK_TCK_PORT->CRH = (PIN_SWCLK_TCK_PORT->CRH & ~PIN_MODE_MASK(PIN_SWCLK_TCK_PIN - 8)) | PIN_MODE(0x3, PIN_SWCLK_TCK_PIN - 8);
//		PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS;
//		SWD_WOW_CLKL();
	#else
		PIN_SWCLK_TCK_PORT->CRL = (PIN_SWCLK_TCK_PORT->CRL & ~PIN_MODE_MASK(PIN_SWCLK_TCK_PIN)) | PIN_MODE(0x3, PIN_SWCLK_TCK_PIN);
//		PIN_SWDIO_TMS_PORT->BRR  = PIN_SWDIO_TMS;
//		SWD_WOW_CLKL();
	#endif
}
/** SWDIO I/O pin: Switch to Input mode (used in SWD mode only).
Configure the SWDIO DAP hardware I/O pin to input mode. This function is
called prior \ref PIN_SWDIO_IN function calls.
*/
void PIN_SWCLK_OUT_DISABLE(void)
{
	//快速设置GPIO，without GPIO_Init call
//	PIN_SWDIO_TMS_OUT_DISABLE();
	#if (PIN_SWCLK_TCK_PIN >= 8)
		PIN_SWCLK_TCK_PORT->CRH = (PIN_SWCLK_TCK_PORT->CRH & ~PIN_MODE_MASK(PIN_SWCLK_TCK_PIN - 8)) | PIN_MODE(0x8, PIN_SWCLK_TCK_PIN - 8);
//		PIN_SWCLK_TCK_PORT->BRR = PIN_SWCLK_TCK;
//		SWD_WOW_CLKL();
	#else
		PIN_SWCLK_TCK_PORT->CRL = (PIN_SWDIO_TMS_PORT->CRL & ~PIN_MODE_MASK(PIN_SWCLK_TCK_PIN)) | PIN_MODE(0x8, PIN_SWCLK_TCK_PIN);
//		PIN_SWCLK_TCK_PORT->BRR = PIN_SWCLK_TCK;
//		SWD_WOW_CLKL();
	#endif
}


// TDI Pin I/O ---------------------------------------------
#if ( DAP_JTAG != 0 )
/** TDI I/O pin: Get Input.
\return Current status of the TDI DAP hardware I/O pin.
*/
uint8_t PIN_TDI_IN(void)
{
	return (PIN_TDI_PORT->ODR & PIN_TDI) ? 1 : 0;
}

/** TDI I/O pin: Set Output.
\param bit Output value for the TDI DAP hardware I/O pin.
*/
void PIN_TDI_OUT(uint8_t bit)
{
	if (bit & 1)
		PIN_TDI_PORT->BSRR = PIN_TDI;
	else
		PIN_TDI_PORT->BRR  = PIN_TDI;
}


// TDO Pin I/O ---------------------------------------------

/** TDO I/O pin: Get Input.
\return Current status of the TDO DAP hardware I/O pin.
*/
uint8_t PIN_TDO_IN(void)
{
	return (PIN_TDO_PORT->IDR & PIN_TDO) ? 1 : 0;
}
#endif

// nTRST Pin I/O -------------------------------------------

/** nTRST I/O pin: Get Input.
\return Current status of the nTRST DAP hardware I/O pin.
*/
uint8_t PIN_nTRST_IN(void)
{
	return (0);   // Not available
}

/** nTRST I/O pin: Set Output.
\param bit JTAG TRST Test Reset pin status:
           - 0: issue a JTAG TRST Test Reset.
           - 1: release JTAG TRST Test Reset.
*/
void PIN_nTRST_OUT(uint8_t bit)
{

}

// nRESET Pin I/O------------------------------------------

/** nRESET I/O pin: Get Input.
\return Current status of the nRESET DAP hardware I/O pin.
*/
uint8_t PIN_nRESET_IN(void)
{
	if (PIN_nRESET_PORT->IDR & PIN_nRESET)
		return 1;
	return 0;
}

/** nRESET I/O pin: Set Output.
\param bit target device hardware reset pin status:
           - 0: issue a device hardware reset.
           - 1: release device hardware reset.
*/	
void PIN_nRESET_OUT(uint8_t bit)
{
	if (bit & 1)
		PIN_nRESET_PORT->BSRR = PIN_nRESET_PIN;
	else
		PIN_nRESET_PORT->BRR  = PIN_nRESET_PIN;
}

/*******************************************************************************
*函数名			:	PIN_nRESET_LOW
*功能描述		:	快速配置GPIO
*输入				: 
*返回值			:	无
*******************************************************************************/
void PIN_nRESET_LOW(void)
{
//	PIN_nRESET_LOW()
	#if (PIN_nRESET_PIN >= 8)
		/* GPIO_Mode_Out_OD | GPIO_Speed_50MHz */	\
		PIN_nRESET_PORT->CRH = (PIN_nRESET_PORT->CRH & ~PIN_MODE_MASK(PIN_nRESET_PIN - 8))	\
									| PIN_MODE(((GPIO_Mode_Out_OD | GPIO_Speed_50MHz) & 0x0F), PIN_nRESET_PIN - 8);
	#else
		/* GPIO_Mode_Out_OD | GPIO_Speed_50MHz */	\
		PIN_nRESET_PORT->CRL = (PIN_nRESET_PORT->CRL & ~PIN_MODE_MASK(PIN_nRESET_PIN))	\
									| PIN_MODE(((GPIO_Mode_Out_OD | GPIO_Speed_50MHz) & 0x0F), PIN_nRESET_PIN);
	#endif
}
/*******************************************************************************
*函数名			:	PIN_nRESET_LOW
*功能描述		:	快速配置GPIO
*输入				: 
*返回值			:	无
*******************************************************************************/
void PIN_nRESET_HIGH(void)
{
//	PIN_nRESET_HIGH()
	#if (PIN_nRESET_PIN >= 8)
		/* GPIO_Mode_Out_OD | GPIO_Speed_50MHz */	\
		PIN_nRESET_PORT->CRH = (PIN_nRESET_PORT->CRH & ~PIN_MODE_MASK(PIN_nRESET_PIN - 8))	\
									| PIN_MODE(GPIO_Mode_IN_FLOATING, PIN_nRESET_PIN - 8);
	#else
		/* GPIO_Mode_Out_OD | GPIO_Speed_50MHz */	\
		PIN_nRESET_PORT->CRL = (PIN_nRESET_PORT->CRL & ~PIN_MODE_MASK(PIN_nRESET_PIN))	\
									| PIN_MODE(GPIO_Mode_IN_FLOATING, PIN_nRESET_PIN);
	#endif
}
//**************************************************************************************************
/** 
\defgroup DAP_Config_Initialization_gr CMSIS-DAP Initialization
\ingroup DAP_ConfigIO_gr
@{

CMSIS-DAP Hardware I/O and LED Pins are initialized with the function \ref DAP_SETUP.
*/

/** Reset Target Device with custom specific I/O pin or command sequence.
This function allows the optional implementation of a device specific reset sequence.
It is called when the command \ref DAP_ResetTarget and is for example required 
when a device needs a time-critical unlock sequence that enables the debug port.
\return 0 = no device specific reset sequence is implemented.\n
        1 = a device specific reset sequence is implemented.
*/
uint8_t RESET_TARGET(void)
{
	return (0); // change to '1' when a device reset sequence is implemented
}















/*******************************************************************************
*函数名			:	LED驱动
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
// Delay for specified time
//    delay:  delay time in ms
void Delay_ms(uint32_t delay)
{
	delay *= (CPU_CLOCK / 1000 + (3 - 1)) / (2 * 3);
	while (--delay)
	{ }
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LED_Configuration(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitTypeDef INIT_LED_CONNECTED = {
		(LED_CONNECTED),
		GPIO_Speed_2MHz,
		GPIO_Mode_Out_PP
	};
	
	GPIO_InitTypeDef INIT_LED_RUNNING = {
		(LED_RUNNING),
		GPIO_Speed_2MHz,
		GPIO_Mode_Out_PP
	};
	
//	GPIO_InitTypeDef GPIO_InitStructure;

	RCC->APB2ENR |= LED_CONNECTED_RCC;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	
	LED_CONNECTED_PORT->BRR = (LED_CONNECTED);
	GPIO_INIT(LED_CONNECTED_PORT, INIT_LED_CONNECTED);
	

	LED_CONNECTED_PORT->BRR = (LED_RUNNING);
	GPIO_INIT(LED_RUNNING_PORT, INIT_LED_RUNNING);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*******************************************************************************
*函数名			:	USB_CONNECTED_SETUP
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void USB_CONNECTED_SETUP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	/* Control USB connecting via SW	*/
	#ifdef USB_CONNECTED_PORT
	const GPIO_InitTypeDef INIT_PIN_USB_CONNECT = {
		USB_CONNECTED,
		GPIO_Speed_50MHz,
		GPIO_Mode_Out_PP
	};
	UsbConnectedOff();
	RCC->APB2ENR |= USB_CONNECT_RCC;
	GPIO_INIT(USB_CONNECTED_PORT, INIT_PIN_USB_CONNECT);
	#endif
	UsbConnectedOff();
	//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//关闭JTAG,SW功能开启
  /* Configure USB pull-up pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	UsbConnectedOff();
}

/*******************************************************************************
*函数名			:	DAP_JTAG
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
/** Setup JTAG I/O pins: TCK, TMS, TDI, TDO, nTRST, and nRESET.
	Configures the DAP Hardware I/O pins for JTAG mode:
	- TCK, TMS, TDI, nTRST, nRESET to output mode and set to high level.
	- TDO to input mode.
*/ 
void PORT_JTAG_SETUP(void)
{
	#if ( DAP_JTAG != 0 )
	const GPIO_InitTypeDef INIT_JTAG_IN = {
		PIN_TDO,
		(GPIOSpeed_TypeDef)0,
		GPIO_Mode_IPU
	};
	const GPIO_InitTypeDef INIT_JTAG_OUT = {
		PIN_SWCLK_TCK | PIN_SWDIO_TMS | PIN_TDI,
		GPIO_Speed_50MHz,
		GPIO_Mode_Out_PP
	};

	PIN_SWCLK_TCK_PORT->BSRR = PIN_SWCLK_TCK | PIN_SWDIO_TMS | PIN_TDI | PIN_TDO;
	PIN_nRESET_PORT->BRR = PIN_nRESET;
	PIN_nRESET_HIGH();

	GPIO_INIT(PIN_TDO_PORT,       INIT_JTAG_IN);
	GPIO_INIT(PIN_SWCLK_TCK_PORT, INIT_JTAG_OUT);
}
#endif

/*******************************************************************************
*函数名			:	PORT_SWD_SETUP
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
/** Setup SWD I/O pins: SWCLK, SWDIO, and nRESET.
	Configures the DAP Hardware I/O pins for Serial Wire Debug (SWD) mode:
	 - SWCLK, SWDIO, nRESET to output mode and set to default high level.
	 - TDI, TDO, nTRST to HighZ mode (pins are unused in SWD mode).
*/ 
void PORT_SWD_SETUP(void)
{
//	#if ( DAP_SWD != 0 )
//		#if ( DAP_JTAG != 0 )
//		const GPIO_InitTypeDef INIT_SWD_TDx = {
//			PIN_TDI | PIN_TDO,
//			(GPIOSpeed_TypeDef)0,
//			GPIO_Mode_IPU
//		};
//		#endif
		const GPIO_InitTypeDef INIT_SWD_PINS =
		{
			PIN_SWCLK_TCK | PIN_SWDIO_TMS,
			GPIO_Speed_50MHz,
			GPIO_Mode_Out_PP
		};

		PIN_SWCLK_TCK_PORT->BSRR = (PIN_SWCLK_TCK | PIN_SWDIO_TMS);
		PIN_nRESET_PORT->BRR = PIN_nRESET;

//		#if ( DAP_JTAG != 0 )
//			GPIO_INIT(PIN_TDI_PORT,       INIT_SWD_TDx);
//		#endif
	
		GPIO_INIT(PIN_SWCLK_TCK_PORT, INIT_SWD_PINS);
		PIN_SWDIO_TMS_SET();
		SWD_WOW_CLKL();
		PIN_nRESET_HIGH();
//	#endif
}

/*******************************************************************************
*函数名			:	DAP_SWD
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
/** Disable JTAG/SWD I/O Pins.
Disables the DAP Hardware I/O pins which configures:
 - TCK/SWCLK, TMS/SWDIO, TDI, TDO, nTRST, nRESET to High-Z mode.
*/
void PORT_OFF()
{
	const GPIO_InitTypeDef INIT_OFF_1 =
	{
	#if ( DAP_JTAG != 0 )
		(PIN_SWCLK_TCK | PIN_SWDIO_TMS | PIN_TDI | PIN_TDO),
	#else
		(PIN_SWCLK_TCK | PIN_SWDIO_TMS),
	#endif
		(GPIOSpeed_TypeDef)0,
		GPIO_Mode_IPU
	};
	const GPIO_InitTypeDef INIT_OFF_2 =
	{
		(PIN_nRESET),
		(GPIOSpeed_TypeDef)0,
		GPIO_Mode_IPU
	};
//	const GPIO_InitTypeDef INIT_OFF_3 = {
//		(PIN_nRESET),
//		(GPIOSpeed_TypeDef)0,
//		GPIO_Mode_IPD
//	};
	
	GPIO_INIT(PIN_SWCLK_TCK_PORT, INIT_OFF_1);
	GPIO_INIT(PIN_nRESET_PORT,    INIT_OFF_2);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SYS_LED(u16 Prescaler,u16 Period,u8 PWM_RATIO)
{	
	//PA0配置
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//定时器结构体定义
	TIM_OCInitTypeDef TIMOCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA和复用时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//打开相应定时器2时钟
	
	//GPIO_DeInit(GPIOA);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;//复用推挽输出	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//1)**********定义相关变量	
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler-1; 		// 设定分频值
	TIM_TimeBaseStructure.TIM_Period = Period-1;        	//设定自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //不分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	//????,???????????????????-??????????
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		//初始化
	//1)**********定义相关变量	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE); 
	
	/* Clear TIMx update pending flag[清除TIMx溢出中断] */
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	/* TIM2 enable counter [使能TIMx计数]*/
	TIM_Cmd(TIM2, ENABLE);	//使能TIMx计数
	
	TIMOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 							//PWM输出模式1
//	TIMOCInitStructure.TIM_Pulse =5000;													//占空比=(CCRx/ARR)*100%
	TIMOCInitStructure.TIM_Pulse =(TIM2->ARR)*PWM_RATIO/100;			//占空比=(CCRx/ARR)*100%
	TIMOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//TIM输出极性高
	TIMOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出
	TIM_OC1Init(TIM2, &TIMOCInitStructure);												//TIM2的CH1输出使能
	TIM_CtrlPWMOutputs(TIM2,ENABLE);															//设置TIM2的PWM输出使能
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}


/* Check if status has changed and if so, send notify to USB Host on Int EP   */
void NotifyOnStatusChange(void)
{
	static int32_t old_notify = -1;
	int32_t status, notify = 0;

	status = UART_GetCommunicationErrorStatus();

	if (status & UART_OVERRUN_ERROR_Msk)
		notify |= CDC_SERIAL_STATE_OVERRUN;
	if (status & UART_PARITY_ERROR_Msk )
		notify |= CDC_SERIAL_STATE_OVERRUN;
	if (status & UART_FRAMING_ERROR_Msk)
		notify |= CDC_SERIAL_STATE_FRAMING;
	
	status	= UART_GetStatusLineState();	
	
	if (status & UART_STATUS_LINE_RI_Msk )
		notify |= CDC_SERIAL_STATE_RING;
	if (status & UART_STATUS_LINE_DSR_Msk)
		notify |= CDC_SERIAL_STATE_TX_CARRIER;
	if (status & UART_STATUS_LINE_DCD_Msk)
		notify |= CDC_SERIAL_STATE_RX_CARRIER;
	
	if (UART_GetBreak())
		notify |= CDC_SERIAL_STATE_BREAK;
	
	if (notify ^ old_notify)				// If notify changed
	{
		if (USBD_CDC_ACM_Notify (notify))   // Send new notification
			old_notify = notify;
	}
}

/*******************************************************************************
*函数名			:	LED驱动
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
//_______________________________________连接LED输出
//void LedConnectedOn(void)				{	LED_CONNECTED_PORT->BRR 	 = LED_CONNECTED;		}
//void LedConnectedOff(void)			{	LED_CONNECTED_PORT->BSRR 	 = LED_CONNECTED;	}
//void LedConnectedToggle(void)		{	LED_CONNECTED_PORT->ODR 	^= LED_CONNECTED;		}
//_______________________________________运行LED输出
//void LedRunningOn(void)					{	LED_RUNNING_PORT->BRR  		 = LED_RUNNING;			}
//void LedRunningOff(void)				{	LED_RUNNING_PORT->BSRR		 = LED_RUNNING;		}
//void LedRunningToggle(void)			{	LED_RUNNING_PORT->ODR			^= LED_RUNNING;			}
//_______________________________________连接USB
//#ifdef	STM32_CDC			//OLED板
//	void UsbConnectedOn(void)		{	USB_CONNECTED_PORT->BSRR 	= USB_CONNECTED;	}
//	void UsbConnectedOff(void)	{	USB_CONNECTED_PORT->BRR  	= USB_CONNECTED;	}
//#elif	USB_TEST		//USB_TEST板
//	void UsbConnectedOn(void)		{	USB_CONNECTED_PORT->BRR 	= USB_CONNECTED;	}
//	void UsbConnectedOff(void)	{	USB_CONNECTED_PORT->BSRR  = USB_CONNECTED;	}
//#endif
////_______________________________________连接LED输出________________________________________
//void LedConnectedOut(uint16_t bit)
//{
//	if (bit & 1)
//		LedConnectedOn();
//	else			
//		LedConnectedOff();
//}
////_______________________________________运行LED输出________________________________________
//void LedRunningOut(uint16_t bit)
//{
//	if (bit & 1)
//		LedRunningOn();
//	else
//		LedRunningOff();
//}


/*******************************************************************************
*函数名			:	HardFault_Handler
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void HardFault_Handler(void)
{
//	extern uint32_t __Vectors;
//	__disable_irq();
//	__set_MSP(__Vectors);
	LED_Configuration();
	{
		register int count;
		for (count = 0; count < 5; count++)
		{
			LedRunningOn();
			Delay_ms(250);
			LedRunningOff();

			LedConnectedOn();
			Delay_ms(250);
			LedConnectedOff();

			Delay_ms(1000);
		}
	}
	NVIC_SystemReset();
}
















