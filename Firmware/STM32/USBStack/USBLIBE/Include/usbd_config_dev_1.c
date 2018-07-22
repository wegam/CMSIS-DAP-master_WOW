/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config_dev_1.c
 * Purpose: USB Device 1 Data and Settings
 * Rev.:    V6.2.1
 *----------------------------------------------------------------------------*/

#ifndef __NO_USB_LIB_C

extern  ARM_DRIVER_USBD  USBDn_DRIVER(USBD1_PORT);

extern  void    USBD1_Core_Thread       (void const *arg);
#ifndef USBD1_CORE_THREAD_STACK_SIZE
#define USBD1_CORE_THREAD_STACK_SIZE    0
#endif
#ifndef USBD1_CORE_THREAD_PRIORITY
#define USBD1_CORE_THREAD_PRIORITY      osPriorityAboveNormal
#endif
osThreadDef(USBD1_Core_Thread, USBD1_CORE_THREAD_PRIORITY, 1, USBD1_CORE_THREAD_STACK_SIZE);

uint8_t         usbd1_alt_setting      [USBD1_IF_CNT];
uint8_t         usbd1_ep0_buf          [USBD1_MAX_PACKET0] __attribute__((aligned(4)));
usbd_data_t     usbd1_data;
usbd_dev_t      usbd1_dev           = {
                                       &USBDn_DRIVER(USBD1_PORT),
                                        usbd1_alt_setting,
                                        usbd1_ep0_buf,
                                       &usbd1_data,
                                        USBD1_CFG_DESC_BMATTRIBUTES,
                                        USBD1_HS,
                                        USBD1_IF_CNT,
                                        USBD1_EP_CNT,
                                        USBD1_MAX_PACKET0,
                                      };

#endif
