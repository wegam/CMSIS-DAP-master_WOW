#include "CMSIS_Conf.H"

#include "STM32F10x_BitBand.h"
#include "usbd_user_cdc_acm.h"
#include "usb_cdc.h"
#include "rl_usb.h"







//void LedConnectedOn(void)		{	LED_CONNECTED_PORT->BRR = LED_CONNECTED;	}
//void LedConnectedOff(void)		{	LED_CONNECTED_PORT->BSRR  = LED_CONNECTED;	}
//void LedConnectedToggle(void)	{	LED_CONNECTED_PORT->ODR ^= LED_CONNECTED;	}

//void LedRunningOn(void)			{	LED_RUNNING_PORT->BRR   = LED_RUNNING;		}
//void LedRunningOff(void)		{	LED_RUNNING_PORT->BSRR    = LED_RUNNING;		}
//void LedRunningToggle(void)		{	LED_RUNNING_PORT->ODR   ^= LED_RUNNING;		}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void LED_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
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
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void USB_CONNECTED_SETUP(void)
{
//	GPIO_InitTypeDef INIT_USB_CONNECTED = {
//		(USB_CONNECTED),
//		GPIO_Speed_2MHz,
//		GPIO_Mode_Out_PP
//	};
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//关闭JTAG,SW功能开启

//	USB_CONNECTED_PORT->BRR = (USB_CONNECTED_PIN);
//	GPIO_INIT(USB_CONNECTED_PORT,INIT_USB_CONNECTED);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	  /* Enable USB_DISCONNECT GPIO clock */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//关闭JTAG,SW功能开启

  /* Configure USB pull-up pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PIN_USB_CONNECT_OFF();
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
/* Control USB connecting via SW	*/
#ifdef PIN_USB_CONNECT_PORT
const GPIO_InitTypeDef INIT_PIN_USB_CONNECT = {
	PIN_USB_CONNECT,
	GPIO_Speed_50MHz,
	PIN_USB_MODE
};
#endif

void PORT_USB_CONNECT_SETUP(void)
{
#ifdef PIN_USB_CONNECT_PORT
	RCC->APB2ENR |= PIN_USB_CONNECT_RCC;
	PIN_USB_CONNECT_OFF();
	GPIO_INIT(PIN_USB_CONNECT_PORT, INIT_PIN_USB_CONNECT);
#endif
}
/*******************************************************************************
*函数名			:	DAP_JTAG
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
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
/** Setup JTAG I/O pins: TCK, TMS, TDI, TDO, nTRST, and nRESET.
	Configures the DAP Hardware I/O pins for JTAG mode:
	- TCK, TMS, TDI, nTRST, nRESET to output mode and set to high level.
	- TDO to input mode.
*/ 
void PORT_JTAG_SETUP()
{
	PIN_SWCLK_TCK_PORT->BSRR = PIN_SWCLK_TCK | PIN_SWDIO_TMS | PIN_TDI | PIN_TDO;
	PIN_nRESET_PORT->BRR = PIN_nRESET;
	PIN_nRESET_HIGH();

	GPIO_INIT(PIN_TDO_PORT,       INIT_JTAG_IN);
	GPIO_INIT(PIN_SWCLK_TCK_PORT, INIT_JTAG_OUT);
}
#endif

/*******************************************************************************
*函数名			:	DAP_SWD
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
#if ( DAP_SWD != 0 )

#if ( DAP_JTAG != 0 )
const GPIO_InitTypeDef INIT_SWD_TDx = {
	PIN_TDI | PIN_TDO,
	(GPIOSpeed_TypeDef)0,
	GPIO_Mode_IPU
};
#endif

const GPIO_InitTypeDef INIT_SWD_PINS = {
	PIN_SWCLK_TCK | PIN_SWDIO_TMS,
	GPIO_Speed_50MHz,
	GPIO_Mode_Out_PP
};

/** Setup SWD I/O pins: SWCLK, SWDIO, and nRESET.
	Configures the DAP Hardware I/O pins for Serial Wire Debug (SWD) mode:
	 - SWCLK, SWDIO, nRESET to output mode and set to default high level.
	 - TDI, TDO, nTRST to HighZ mode (pins are unused in SWD mode).
*/ 
void PORT_SWD_SETUP()
{
	PIN_SWCLK_TCK_PORT->BSRR = (PIN_SWCLK_TCK | PIN_SWDIO_TMS);
	PIN_nRESET_PORT->BRR = PIN_nRESET;

#if ( DAP_JTAG != 0 )
	GPIO_INIT(PIN_TDI_PORT,       INIT_SWD_TDx);
#endif
	GPIO_INIT(PIN_SWCLK_TCK_PORT, INIT_SWD_PINS);
	PIN_nRESET_HIGH();
}
#endif
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
const GPIO_InitTypeDef INIT_OFF_1 = {
#if ( DAP_JTAG != 0 )
	(PIN_SWCLK_TCK | PIN_SWDIO_TMS | PIN_TDI | PIN_TDO),
#else
	(PIN_SWCLK_TCK | PIN_SWDIO_TMS),
#endif
	(GPIOSpeed_TypeDef)0,
	GPIO_Mode_IPU
};
const GPIO_InitTypeDef INIT_OFF_2 = {
	(PIN_nRESET),
	(GPIOSpeed_TypeDef)0,
	GPIO_Mode_IPU
};
const GPIO_InitTypeDef INIT_OFF_3 = {
	(PIN_nRESET),
	(GPIOSpeed_TypeDef)0,
	GPIO_Mode_IPD
};

void PORT_OFF()
{
	GPIO_INIT(PIN_SWCLK_TCK_PORT, INIT_OFF_1);
	GPIO_INIT(PIN_nRESET_PORT,    INIT_OFF_2);
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
void LedConnectedOn(void)				{	LED_CONNECTED_PORT->BRR = LED_CONNECTED;		}
void LedConnectedOff(void)			{	LED_CONNECTED_PORT->BSRR  = LED_CONNECTED;	}
void LedConnectedToggle(void)		{	LED_CONNECTED_PORT->ODR ^= LED_CONNECTED;		}

void LedRunningOn(void)					{	LED_RUNNING_PORT->BRR   = LED_RUNNING;			}
void LedRunningOff(void)				{	LED_RUNNING_PORT->BSRR    = LED_RUNNING;		}
void LedRunningToggle(void)			{	LED_RUNNING_PORT->ODR   ^= LED_RUNNING;			}
//_______________________________________连接LED输出________________________________________
void LedConnectedOut(uint16_t bit)
{
	if (bit & 1)
		LedConnectedOn();
	else			
		LedConnectedOff();
}
//_______________________________________运行LED输出________________________________________
void LedRunningOut(uint16_t bit)
{
	if (bit & 1)
		LedRunningOn();
	else
		LedRunningOff();
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

/** nRESET I/O pin: Set Output.
\param bit target device hardware reset pin status:
           - 0: issue a device hardware reset.
           - 1: release device hardware reset.
*/
void PIN_nRESET_OUT(uint8_t bit)
{
 	if (bit & 1)
	{
		PIN_nRESET_HIGH();
	}
	else
	{
		PIN_nRESET_LOW();
	}
}
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
















