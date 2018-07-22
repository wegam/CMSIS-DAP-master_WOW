/*------------------------------------------------------------------------------
 *      RL-ARM - USB
 *------------------------------------------------------------------------------
 *      Name:    usbd_cdc_acm.h
 *      Purpose: USB Device Communication Device Class Abstract Control Model 
 *               header file
 *      Rev.:    V4.70
 *------------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __USBD_CDC_ACM_H__
#define __USBD_CDC_ACM_H__

#include "RTL.h"
#include "stdint.h"


/*--------------------------- Event handling routines ------------------------*/

extern           void USBD_CDC_ACM_Reset_Event          (void);

extern           void USBD_CDC_ACM_SOF_Event            (void);
/* Local function prototypes                                                  */
static void    USBD_CDC_ACM_EP_BULKOUT_HandleData   (void);
static void    USBD_CDC_ACM_EP_BULKIN_HandleData    (void);

extern           void USBD_CDC_ACM_EP_INTIN_Event       (U32 event);	//串口中断处理函数---空函数
extern           void USBD_CDC_ACM_EP_BULKIN_Event      (U32 event);	//串口批量输入处理函数
extern           void USBD_CDC_ACM_EP_BULKOUT_Event     (U32 event);	//串口批量输出处理函数
extern           void USBD_CDC_ACM_EP_BULK_Event        (U32 event);	//串口批量传输端点处理函数

extern    __task void USBD_RTX_CDC_ACM_EP_INTIN_Event   (void);
extern    __task void USBD_RTX_CDC_ACM_EP_BULKIN_Event  (void);
extern    __task void USBD_RTX_CDC_ACM_EP_BULKOUT_Event (void);
extern    __task void USBD_RTX_CDC_ACM_EP_BULK_Event    (void);




int32_t USBD_CDC_ACM_PutChar (const uint8_t ch);
int32_t USBD_CDC_ACM_GetChar (void);



#endif  /* __USBD_CDC_ACM_H__ */
