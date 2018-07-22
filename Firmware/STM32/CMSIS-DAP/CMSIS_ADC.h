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

#ifndef __CMSIS_ADC_H__
#define __CMSIS_ADC_H__

#include "stdio.h"
#include "stddef.h"
#include "stdint.h"

#ifdef	STM32_CDC			//OLED∞Â
//	#define ADC_TEST			//≤‚ ‘ADC
#endif

#ifdef	STM32_CDC			//OLED∞Â
	//ADC
	#define ADC_CONNECTED_RCC		RCC_APB2ENR_IOPBEN
	#define ADC_CONNECTED_PORT	GPIOB
	#define ADC_CONNECTED_PIN		GPIO_Pin_1
#endif

void ADC_Configuration(void);
int16_t	Read_ADC(void);

extern int16_t ADC_Result[4];
extern int16_t ADC_Value[4];
//extern int16_t ADC_Ch1[10];
//extern int16_t ADC_Ch2[10];
//extern int16_t ADC_Ch3[10];
//extern int16_t ADC_Ch4[10];

#endif /* __DAP_CONFIG_H__ */
