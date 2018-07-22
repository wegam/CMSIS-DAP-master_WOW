/**************************************************************************//**
 * @file     DAP_config.h
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

#ifndef __CMSIS_CDC_H__
#define __CMSIS_CDC_H__

#include "stdio.h"
#include "stddef.h"
#include "stdint.h"


#if   defined( __GNUC__ )
	/*	With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
		set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#elif defined( __CC_ARM )
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#else
	#error "Unknown compiler"
#endif


extern int32_t usb_rx_ch;
extern int32_t usb_tx_ch;

int32_t CMSIS_CDC_Process(void);
void send_char(char ch);



#endif /* __DAP_CONFIG_H__ */
