/******************************************************************************
 * @file	DAP.h
 * @brief	CMSIS-DAP Definitions
 * @version V1.00
 * @date	31. May 2012
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

#ifndef __CMSIS_DAP__
#define __CMSIS_DAP__

#include "stddef.h"
#include "stdint.h"

void main_STM32_CDC(void);
void main_USB_TEST(void);
void RCC_Configuration(void);	//系统时钟配置
void BoardInit(void);
void USBD_Error_Event(void);
void WOW_KEY_Event(void);
void WOW_USB_Event(void);
void WOW_USB_INIT(void);				//USB初始化

void WOW_DISPALY_INIT(void);		//初始化显示内容
void WOW_DISPALY_Event(void);

#endif  /* __DAP_H__ */
