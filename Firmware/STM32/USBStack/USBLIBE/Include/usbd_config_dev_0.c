/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config_dev_0.c
 * Purpose: USB Device 0 Data and Settings
 * Rev.:    V6.2.1
 *----------------------------------------------------------------------------*/

#ifndef __NO_USB_LIB_C

extern  ARM_DRIVER_USBD  USBDn_DRIVER(USBD0_PORT);

extern  void    USBD0_Core_Thread       (void const *arg);
#ifndef USBD0_CORE_THREAD_STACK_SIZE
#define USBD0_CORE_THREAD_STACK_SIZE    0
#endif
#ifndef USBD0_CORE_THREAD_PRIORITY
#define USBD0_CORE_THREAD_PRIORITY      osPriorityAboveNormal
#endif
osThreadDef(USBD0_Core_Thread, USBD0_CORE_THREAD_PRIORITY, 1, USBD0_CORE_THREAD_STACK_SIZE);

uint8_t         usbd0_alt_setting      [USBD0_IF_CNT];
uint8_t         usbd0_ep0_buf          [USBD0_MAX_PACKET0] __attribute__((aligned(4)));
usbd_data_t     usbd0_data;
usbd_dev_t      usbd0_dev           = {
                                       &USBDn_DRIVER(USBD0_PORT),
                                        usbd0_alt_setting,
                                        usbd0_ep0_buf,
                                       &usbd0_data,
                                        USBD0_CFG_DESC_BMATTRIBUTES,
                                        USBD0_HS,
                                        USBD0_IF_CNT,
                                        USBD0_EP_CNT,
                                        USBD0_MAX_PACKET0,
                                      };

#endif
