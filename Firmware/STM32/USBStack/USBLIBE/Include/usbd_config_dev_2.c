/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config_dev_2.c
 * Purpose: USB Device 2 Data and Settings
 * Rev.:    V6.2.1
 *----------------------------------------------------------------------------*/

#ifndef __NO_USB_LIB_C

extern  ARM_DRIVER_USBD  USBDn_DRIVER(USBD2_PORT);

extern  void    USBD2_Core_Thread       (void const *arg);
#ifndef USBD2_CORE_THREAD_STACK_SIZE
#define USBD2_CORE_THREAD_STACK_SIZE    0
#endif
#ifndef USBD2_CORE_THREAD_PRIORITY
#define USBD2_CORE_THREAD_PRIORITY      osPriorityAboveNormal
#endif
osThreadDef(USBD2_Core_Thread, USBD2_CORE_THREAD_PRIORITY, 1, USBD2_CORE_THREAD_STACK_SIZE);

uint8_t         usbd2_alt_setting      [USBD2_IF_CNT];
uint8_t         usbd2_ep0_buf          [USBD2_MAX_PACKET0] __attribute__((aligned(4)));
usbd_data_t     usbd2_data;
usbd_dev_t      usbd2_dev           = {
                                       &USBDn_DRIVER(USBD2_PORT),
                                        usbd2_alt_setting,
                                        usbd2_ep0_buf,
                                       &usbd2_data,
                                        USBD2_CFG_DESC_BMATTRIBUTES,
                                        USBD2_HS,
                                        USBD2_IF_CNT,
                                        USBD2_EP_CNT,
                                        USBD2_MAX_PACKET0,
                                      };

#endif
