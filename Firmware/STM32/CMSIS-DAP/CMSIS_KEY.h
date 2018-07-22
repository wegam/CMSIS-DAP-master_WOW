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

#ifndef __CMSIS_KEY_H__
#define __CMSIS_KEY_H__

#include "stdio.h"
#include "stddef.h"
#include "stdint.h"

#ifdef	STM32_CDC			//OLED°å
	//°´¼ü/³äµçÊäÈë
	#define KEY_CONNECTED_RCC		RCC_APB2ENR_IOPAEN
	#define KEY_CONNECTED_PORT	GPIOA
	#define KEY_CONNECTED_PIN		GPIO_Pin_1

//³äµçÂú-µÍµçÆ½
	#define STDBY_CONNECTED_RCC		RCC_APB2ENR_IOPBEN
	#define STDBY_CONNECTED_PORT	GPIOB
	#define STDBY_CONNECTED_PIN		GPIO_Pin_3

	
#else
	//ÓÒ¼ü
	#define KEY_CONNECTED_RCC		RCC_APB2ENR_IOPAEN
	#define KEY_CONNECTED_PORT	GPIOA
	#define KEY_CONNECTED_PIN		GPIO_Pin_8

//×ó¼ü
	#define STDBY_CONNECTED_RCC		RCC_APB2ENR_IOPBEN
	#define STDBY_CONNECTED_PORT	GPIOB
	#define STDBY_CONNECTED_PIN		GPIO_Pin_11

#endif


void KEY_Configuration(void);
int8_t	Read_Input(void);

#endif /* __DAP_CONFIG_H__ */
