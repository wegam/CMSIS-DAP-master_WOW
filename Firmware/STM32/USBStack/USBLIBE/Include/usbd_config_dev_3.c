/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config_dev_3.c
 * Purpose: USB Device 3 Data and Settings
 * Rev.:    V6.2.1
 *----------------------------------------------------------------------------*/

#ifndef __NO_USB_LIB_C

extern  ARM_DRIVER_USBD  USBDn_DRIVER(USBD3_PORT);

extern  void    USBD3_Core_Thread       (void const *arg);
#ifndef USBD3_CORE_THREAD_STACK_SIZE
#define USBD3_CORE_THREAD_STACK_SIZE    0
#endif
#ifndef USBD3_CORE_THREAD_PRIORITY
#define USBD3_CORE_THREAD_PRIORITY      osPriorityAboveNormal
#endif
osThreadDef(USBD3_Core_Thread, USBD3_CORE_THREAD_PRIORITY, 1, USBD3_CORE_THREAD_STACK_SIZE);

uint8_t         usbd3_alt_setting      [USBD3_IF_CNT];
uint8_t         usbd3_ep0_buf          [USBD3_MAX_PACKET0] __attribute__((aligned(4)));
usbd_data_t     usbd3_data;
usbd_dev_t      usbd3_dev           = {
                                       &USBDn_DRIVER(USBD3_PORT),
                                        usbd3_alt_setting,
                                        usbd3_ep0_buf,
                                       &usbd3_data,
                                        USBD3_CFG_DESC_BMATTRIBUTES,
                                        USBD3_HS,
                                        USBD3_IF_CNT,
                                        USBD3_EP_CNT,
                                        USBD3_MAX_PACKET0,
                                      };

#endif
