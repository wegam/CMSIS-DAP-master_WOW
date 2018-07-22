/**************************************************************************//**
 * @file     CMSIS_Conf.H
 * @brief    CMSIS-DAP Configuration File for STM32F103C6/8/B
 * @version  V1.00
 * @date     02. Oct 2012
 *
 * @note
 * Copyright (C) 2012 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#ifndef __CMSIS_Conf_H__
#define __CMSIS_Conf_H__



#include "stdio.h"
#include "stddef.h"
#include "stdint.h"

#include "stm32f10x.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "SWD_WOW.h"
#include "STM32F10x_BitBand.h"

typedef const struct
{
	void	(* LedConnected)	(uint16_t);
	void	(* LedRunning)		(uint16_t);
} CoreDescriptor_t;

extern const CoreDescriptor_t * pCoreDescriptor;

typedef const struct
{
	void		(* UserInit)	(CoreDescriptor_t * core);
	uint32_t	(* UserProcess)	(uint8_t *, uint8_t *);
	void		(* UserAbort)	(void);
} UserAppDescriptor_t;

#if !defined ( BOARD_V1      )
	#error "Board undefined"
#endif

#if   defined( __GNUC__ )
	/*	With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
		set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#elif defined( __CC_ARM )
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#else
	#error "Unknown compiler"
#endif

#if   defined( USE_DEBUG )
	#define DEBUG(...)	printf(__VA_ARGS__)
	#define INFO(...)	printf(__VA_ARGS__)
	#define ERROR(...)	printf(__VA_ARGS__)
#elif defined( USE_INFO )
	#define DEBUG(...)
	#define INFO(...)	printf(__VA_ARGS__)
	#define ERROR(...)	printf(__VA_ARGS__)
#elif defined( USE_ERROR )
	#define DEBUG(...)
	#define INFO(...)
	#define ERROR(...)	printf(__VA_ARGS__)
#else
	#define DEBUG(...)
	#define INFO(...)
	#define ERROR(...)
#endif

//**************************************************************************************************
/** 
\defgroup DAP_Config_Debug_gr CMSIS-DAP Debug Unit Information
\ingroup DAP_ConfigIO_gr 
@{
Provides definitions about:
 - Definition of Cortex-M processor parameters used in CMSIS-DAP Debug Unit.
 - Debug Unit communication packet size.
 - Debug Access Port communication mode (JTAG or SWD).
 - Optional information about a connected Target Device (for Evaluation Boards).
*/



/// Processor Clock of the Cortex-M MCU used in the Debug Unit.
/// This value is used to calculate the SWD/JTAG clock speed.
#define CPU_CLOCK				SystemCoreClock		///< Specifies the CPU Clock in Hz

/// Number of processor cycles for I/O Port write operations.
/// This value is used to calculate the SWD/JTAG clock speed that is generated with I/O
/// Port write operations in the Debug Unit by a Cortex-M MCU. Most Cortex-M processors
/// requrie 2 processor cycles for a I/O Port Write operation.  If the Debug Unit uses
/// a Cortex-M0+ processor with high-speed peripheral I/O only 1 processor cycle might be 
/// requrired.
#define IO_PORT_WRITE_CYCLES	2               ///< I/O Cycles: 2=default, 1=Cortex-M0+ fast I/0

/// Indicate that Serial Wire Debug (SWD) communication mode is available at the Debug Access Port.
/// This information is returned by the command \ref DAP_Info as part of <b>Capabilities</b>.
#define DAP_SWD                 1               ///< SWD Mode:  1 = available, 0 = not available

#define DAP_JTAG			1				///< JTAG Mode: 1 = available, 0 = not available.


/// Configure maximum number of JTAG devices on the scan chain connected to the Debug Access Port.
/// This setting impacts the RAM requirements of the Debug Unit. Valid range is 1 .. 255.
#define DAP_JTAG_DEV_CNT        8               ///< Maximum number of JTAG devices on scan chain

/// Default communication mode on the Debug Access Port.
/// Used for the command \ref DAP_Connect when Port Default mode is selected.
#define DAP_DEFAULT_PORT        1               ///< Default JTAG/SWJ Port Mode: 1 = SWD, 2 = JTAG.

/// Default communication speed on the Debug Access Port for SWD and JTAG mode.
/// Used to initialize the default SWD/JTAG clock frequency.
/// The command \ref DAP_SWJ_Clock can be used to overwrite this default setting.
#define DAP_DEFAULT_SWJ_CLOCK   1000000         ///< Default SWD/JTAG clock frequency in Hz.

/// Maximum Package Size for Command and Response data.
/// This configuration settings is used to optimized the communication performance with the
/// debugger and depends on the USB peripheral. Change setting to 1024 for High-Speed USB.
#define DAP_PACKET_SIZE			64				///< USB: 64 = Full-Speed, 1024 = High-Speed.

/// Maximum Package Buffers for Command and Response data.
/// This configuration settings is used to optimized the communication performance with the
/// debugger and depends on the USB peripheral. For devices with limited RAM or USB buffer the
/// setting can be reduced (valid range is 1 .. 255). Change setting to 4 for High-Speed USB.
#define DAP_PACKET_COUNT		64				///< Buffers: 64 = Full-Speed, 4 = High-Speed.


/// Debug Unit is connected to fixed Target Device.
/// The Debug Unit may be part of an evaluation board and always connected to a fixed
/// known device.  In this case a Device Vendor and Device Name string is stored which
/// may be used by the debugger or IDE to configure device parameters.
#define TARGET_DEVICE_FIXED     0               ///< Target Device: 1 = known, 0 = unknown;

#if TARGET_DEVICE_FIXED
	#define TARGET_DEVICE_VENDOR    ""		///< String indicating the Silicon Vendor
	#define TARGET_DEVICE_NAME      ""		///< String indicating the Target Device
#endif

///@}

#define GPIO_INIT(port, data)		GPIO_Init(port, (GPIO_InitTypeDef *)&data)
#define PIN_MODE_MASK(pin)			(((uint32_t)0x0F) << ((pin) << 2))
#define PIN_MODE(mode,pin)			(((uint32_t)mode) << ((pin) << 2))
#define PIN_MASK(pin)						(((uint16_t)0x01) << (pin))

//typedef enum Pin_e {
//	PA = 0x00, PA0 = 0x00, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
//	PB = 0x10, PB0 = 0x10, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
//	PC = 0x20, PC0 = 0x20, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
//	PD = 0x30, PD0 = 0x30, PD1, PD2,
//} Pin_t;

// USART Port and I/O Pins

#if   defined ( STM32_CDC )

	#define USART_CLOCK(state)		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, state)
	#define USART_GPIO_CLOCK(state)	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, state)
	#define USART_REMAP()			/* GPIO_PinRemapConfig(..., ENABLE) */

	#define USART_PORT			USART1
	#define USART_GPIO			GPIOA
	#define USART_TX_PIN		GPIO_Pin_9
	#define USART_RX_PIN		GPIO_Pin_10
	#define USART_IRQn			USART1_IRQn
	#define USART_IRQHandler	USART1_IRQHandler
	#define USART_BUFFER_SIZE	(256)	/*	Size of Receive and Transmit buffers MUST BE 2^n */

#elif defined ( USB_TEST )

	#define USART_CLOCK(state)		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, state)
	#define USART_REMAP()			/* GPIO_PinRemapConfig(..., ENABLE) */

	#define USART_PORT			USART2
	#define USART_GPIO			GPIOA
	#define USART_TX_PIN		GPIO_Pin_2
	#define USART_RX_PIN		GPIO_Pin_3
	#define USART_IRQn			USART2_IRQn
	#define USART_IRQHandler	USART2_IRQHandler
	#define USART_BUFFER_SIZE	(256)	/*	Size of Receive and Transmit buffers MUST BE 2^n */

#else

	#warning "USART Port not define"

#endif

#if   defined ( BOARD_V1 )
	#ifdef	STM32_CDC			//OLED板

		// SWDIO/TMS Pin
		#define PIN_SWDIO_TMS_PORT      GPIOA
		#define PIN_SWDIO_TMS_PIN		2

		// SWCLK/TCK Pin
		#define PIN_SWCLK_TCK_PORT		GPIOA
		#define PIN_SWCLK_TCK_PIN		3

		// TDO/SWO Pin (input)
		#define PIN_TDO_PORT            GPIOB
		#define PIN_TDO					0

		// TDI Pin (output)
		#define PIN_TDI_PORT			GPIOB
		#define PIN_TDI					0

		// nRESET Pin
		#define PIN_nRESET_PORT         GPIOB
		#define PIN_nRESET_PIN			0

	// Debug Unit LEDs		
		// Connected LED (GREEN)
		#define LED_CONNECTED_RCC		RCC_APB2ENR_IOPAEN
		#define LED_CONNECTED_PORT	GPIOA
		#define LED_CONNECTED_PIN		4

		// Target Running LED (RED)
		#define LED_RUNNING_RCC			RCC_APB2ENR_IOPAEN
		#define LED_RUNNING_PORT		GPIOA
		#define LED_RUNNING_PIN			4
		
		//USB连接控制
		#define USB_CONNECT_RCC			RCC_APB2ENR_IOPAEN
		#define	USB_CONNECTED_PORT	GPIOA
		#define	USB_CONNECTED_PIN		15
		
		//电源锁定控制
		#define POWER_LOCK_RCC			RCC_APB2Periph_GPIOB
		#define	POWER_LOCK_PORT			GPIOB
		#define	POWER_LOCK_PIN			10
		#define POWER_CONNECTED 		PIN_MASK(POWER_LOCK_PIN)			//电源锁定
	
	#elif	USB_TEST		//USB_TEST板
	
		// SWDIO/TMS Pin
		#define PIN_SWDIO_TMS_PORT      GPIOA
		#define PIN_SWDIO_TMS_PIN		6

		// SWCLK/TCK Pin
		#define PIN_SWCLK_TCK_PORT		GPIOA
		#define PIN_SWCLK_TCK_PIN		5

		// TDO/SWO Pin (input)
		#define PIN_TDO_PORT            GPIOA
		#define PIN_TDO					7

		// TDI Pin (output)
		#define PIN_TDI_PORT			GPIOB
		#define PIN_TDI					7

//		// nRESET Pin
//		#define PIN_nRESET_PORT         GPIOA
//		#define PIN_nRESET_PIN			4
		// nRESET Pin
		#define PIN_nRESET_PORT         GPIOB
		#define PIN_nRESET_PIN			7

		// Debug Unit LEDs
		// Connected LED (GREEN)
		#define LED_CONNECTED_RCC		RCC_APB2ENR_IOPBEN		
		#define LED_CONNECTED_PORT	GPIOB
		#define LED_CONNECTED_PIN		10	

		// Target Running LED (RED)
		#define LED_RUNNING_RCC			RCC_APB2ENR_IOPBEN
		#define LED_RUNNING_PORT		GPIOB
		#define LED_RUNNING_PIN			0
		
		
		//USB连接开关
		#define USB_CONNECT_RCC			RCC_APB2ENR_IOPAEN
		#define	USB_CONNECTED_PORT	GPIOA
		#define	USB_CONNECTED_PIN		15	
	
	#endif	
#endif


#define USB_CONNECTED  		PIN_MASK(USB_CONNECTED_PIN)		//USB连接
#define LED_RUNNING				PIN_MASK(LED_RUNNING_PIN)			//运行LED
#define LED_CONNECTED			PIN_MASK(LED_CONNECTED_PIN)		//连接LED

#define PIN_nRESET				PIN_MASK(PIN_nRESET_PIN)			//复位
#define PIN_SWDIO_TMS			PIN_MASK(PIN_SWDIO_TMS_PIN)		//SWDIO
#define PIN_SWCLK_TCK			PIN_MASK(PIN_SWCLK_TCK_PIN)		//SWCLK

#ifdef	STM32_CDC			//OLED板

	#define LED_CONNECTED_SET			PA4
	#define LED_RUNNING_SET				PA4
	
	#define SWD_WOW_CLKH()		PA3=1
	#define SWD_WOW_CLKL()		PA3=0

	#define SWD_WOW_DIOH()		PA2=1
	#define SWD_WOW_DIOL()		PA2=0

	#define SWD_WOW_DIO				PA2

	#define SWD_WOW_DIOIN()		PA2in
	
#else		//USB_TEST

	#define LED_CONNECTED_SET		PB10
	#define LED_RUNNING_SET		PB0
	
	#define SWD_WOW_CLKH()		PA5=1
	#define SWD_WOW_CLKL()		PA5=0

	#define SWD_WOW_DIOH()		PA6=1
	#define SWD_WOW_DIOL()		PA6=0

	#define SWD_WOW_DIO				PA6

	#define SWD_WOW_DIOIN()		PA6in
	
#endif


//#define PIN_SWCLK_SET()		PIN_SWCLK_TCK_SET()
//#define PIN_SWCLK_CLR()		PIN_SWCLK_TCK_CLR()

#define SW_CLOCK_CYCLE()		\
		SWD_WOW_CLKL();		\
		PIN_DELAY();			\
		SWD_WOW_CLKH();		\
		PIN_DELAY()

#define SW_WRITE_BIT(bit)		\
		SWD_WOW_DIO=bit;		\
		SWD_WOW_CLKL();		\
		PIN_DELAY();			\
		SWD_WOW_CLKH();		\
		PIN_DELAY()

#define SW_READ_BIT(bit)		\
		SWD_WOW_CLKL();		\
		PIN_DELAY();			\
		bit = SWD_WOW_DIOIN();	\
		SWD_WOW_CLKH();		\
		PIN_DELAY()

#define PIN_DELAY()		PIN_DELAY_SLOW(DAP_Data.clock_delay)


/** Setup of the Debug Unit I/O pins and LEDs (called when Debug Unit is initialized).
This function performs the initialization of the CMSIS-DAP Hardware I/O Pins and the 
Status LEDs. In detail the operation of Hardware I/O and LED pins are enabled and set:
 - I/O clock system enabled.
 - all I/O pins: input buffer enabled, output pins are set to HighZ mode.
 - for nTRST, nRESET a weak pull-up (if available) is enabled.
 - LED output pins are enabled and LEDs are turned off.
*/
#define DAP_SETUP()	PORT_OFF()

//**************************************************************************************************
/** 
\defgroup DAP_Config_LEDs_gr CMSIS-DAP Hardware Status LEDs
\ingroup DAP_ConfigIO_gr
@{

CMSIS-DAP Hardware may provide LEDs that indicate the status of the CMSIS-DAP Debug Unit.

It is recommended to provide the following LEDs for status indication:
 - Connect LED: is active when the DAP hardware is connected to a debugger.
 - Running LED: is active when the debugger has put the target device into running state.
*/

/** Debug Unit: Set status of Connected LED.
\param bit status of the Connect LED.
           - 1: Connect LED ON: debugger is connected to CMSIS-DAP Debug Unit.
           - 0: Connect LED OFF: debugger is not connected to CMSIS-DAP Debug Unit.
*/
#define LED_CONNECTED_OUT(b)	pCoreDescriptor->LedConnected(b)

/** Debug Unit: Set status Target Running LED.
\param bit status of the Target Running LED.
           - 1: Target Running LED ON: program execution in target started.
           - 0: Target Running LED OFF: program execution in target stopped.
*/
#define LED_RUNNING_OUT(b)		pCoreDescriptor->LedRunning(b)





void LedConnectedOn(void);
void LedConnectedOff(void);
void LedConnectedToggle(void);
void LedRunningOn(void);
void LedRunningOff(void);
void LedRunningToggle(void);
void LedConnectedOut(uint16_t bit);
void LedRunningOut(uint16_t bit);
void UsbConnectedOn(void);
void UsbConnectedOff(void);
void PowerOn(void);
void PowerOff(void);
uint8_t PIN_SWCLK_TCK_IN(void);
void PIN_SWCLK_TCK_SET(void);
void PIN_SWCLK_TCK_CLR (void);
uint8_t PIN_SWDIO_TMS_IN(void);
void PIN_SWDIO_TMS_SET(void);
//void PIN_SWDIO_TMS_CLR(void);
uint8_t PIN_SWDIO_IN (void);
//void PIN_SWDIO_OUT(uint8_t bit);
void PIN_SWDIO_OUT_ENABLE(void);
void PIN_SWDIO_OUT_DISABLE(void);
void PIN_SWCLK_OUT_ENABLE(void);
void PIN_SWCLK_OUT_DISABLE(void);

#if ( DAP_JTAG != 0 )
uint8_t PIN_TDI_IN(void);
void PIN_TDI_OUT(uint8_t bit);
uint8_t PIN_TDO_IN(void);
#endif
uint8_t PIN_nTRST_IN(void);
void PIN_nTRST_OUT(uint8_t bit);
uint8_t PIN_nRESET_IN(void);
void PIN_nRESET_OUT(uint8_t bit);
void PIN_nRESET_LOW(void);
void PIN_nRESET_HIGH(void);
uint8_t RESET_TARGET(void);




// 廷时 ------------------------------
void Delay_ms(uint32_t delay);

void LED_Configuration(void);
void USB_CONNECTED_SETUP(void);			//USB连接控制管脚


// Configure DAP I/O pins ------------------------------
void PORT_JTAG_SETUP(void);
void PORT_SWD_SETUP(void);
void PORT_OFF(void);
void SYS_LED(u16 Prescaler,u16 Period,u8 PWM_RATIO);

void NotifyOnStatusChange(void);
////_______________________________________连接LED输出
//void LedConnectedOn(void);
//void LedConnectedOff(void);
//void LedConnectedToggle(void);
////_______________________________________运行LED输出
//void LedRunningOn(void);
//void LedRunningOff(void);
//void LedRunningToggle(void);
//void LedConnectedOut(uint16_t bit);
//void LedRunningOut(uint16_t bit);
////_______________________________________连接USB
//void UsbConnectedOn(void);
//void UsbConnectedOff(void);

//void PIN_nRESET_OUT(uint8_t bit);

void HardFault_Handler(void);
//void NMI_Handler(void)			__attribute((alias("HardFault_Handler")));
//void MemManage_Handler(void)	__attribute((alias("HardFault_Handler")));
//void BusFault_Handler(void)		__attribute((alias("HardFault_Handler")));
//void UsageFault_Handler(void)	__attribute((alias("HardFault_Handler")));
//void SVC_Handler(void)			__attribute((alias("HardFault_Handler")));
//void DebugMon_Handler(void)		__attribute((alias("HardFault_Handler")));
//void PendSV_Handler(void)		__attribute((alias("HardFault_Handler")));


#endif /* __DAP_CONFIG_H__ */
