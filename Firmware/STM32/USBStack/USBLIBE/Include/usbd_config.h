/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config.h
 * Purpose: USB Device Library Configuration
 * Rev.:    V6.6.3
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "usb_def.h"
#include "usb_adc.h"
#include "usb_cdc.h"
#include "usb_hid.h"
#include "usb_msc.h"
#include "rl_usb.h"
#include "rl_usbd_lib.h"

#include "usbd_compatibility.h"


#pragma push
#pragma thumb
#pragma O3


/*------------------------------------------------------------------------------
 *      USB Device Global Macros
 *----------------------------------------------------------------------------*/

#define MAX_OF_2(a,b)                   ((a)>(b)?(a):(b))

#define USBDn_DRIVER_(n)                Driver_USBD##n
#define USBDn_DRIVER(n)                 USBDn_DRIVER_(n)


/*------------------------------------------------------------------------------
 *      USB Device 0 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifndef USBD0_MACROS
#define USBD0_MACROS                    1
#include "usbd_config_def_0.h"
#endif

#ifdef  USBD0_PORT
#include "usbd_config_dev_0.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 1 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifndef USBD1_MACROS
#define USBD1_MACROS                    1
#include "usbd_config_def_1.h"
#endif

#ifdef  USBD1_PORT
#include "usbd_config_dev_1.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 2 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifndef USBD2_MACROS
#define USBD2_MACROS                    1
#include "usbd_config_def_2.h"
#endif

#ifdef  USBD2_PORT
#include "usbd_config_dev_2.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 3 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifndef USBD3_MACROS
#define USBD3_MACROS                    1
#include "usbd_config_def_3.h"
#endif

#ifdef  USBD3_PORT
#include "usbd_config_dev_3.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device Global Macros
 *----------------------------------------------------------------------------*/

#ifndef __NO_USB_LIB_C

#ifdef  USBD3_PORT
#define LAST_DEVICE_COMPILE             1
#elif  (defined(USBD2_PORT) && !defined(RTE_USB_Device_3))
#define LAST_DEVICE_COMPILE             1
#elif  (defined(USBD1_PORT) && !defined(RTE_USB_Device_3) && !defined(RTE_USB_Device_2))
#define LAST_DEVICE_COMPILE             1
#elif  (defined(USBD0_PORT) && !defined(RTE_USB_Device_3) && !defined(RTE_USB_Device_2) && !defined(RTE_USB_Device_1))
#define LAST_DEVICE_COMPILE             1
#endif

#ifdef  LAST_DEVICE_COMPILE

#define USBD_EP_LAST_NUM                USBD0_EP_MAX
#if    (USBD1_EP_MAX > USBD_EP_LAST_NUM)
#undef  USBD_EP_LAST_NUM
#define USBD_EP_LAST_NUM                USBD1_EP_MAX
#endif
#if    (USBD2_EP_MAX > USBD_EP_LAST_NUM)
#undef  USBD_EP_LAST_NUM
#define USBD_EP_LAST_NUM                USBD2_EP_MAX
#endif
#if    (USBD3_EP_MAX > USBD_EP_LAST_NUM)
#undef  USBD_EP_LAST_NUM
#define USBD_EP_LAST_NUM                USBD3_EP_MAX
#endif

#define USBD_EP_NUM                    (USBD_EP_LAST_NUM + 1)

#ifdef  RTE_USB_Device_0
#define USBD0_DEV_NUM                   1
#else
#define USBD0_DEV_NUM                   0
#endif
#ifdef  RTE_USB_Device_1
#define USBD1_DEV_NUM                   1
#else
#define USBD1_DEV_NUM                   0
#endif
#ifdef  RTE_USB_Device_2
#define USBD2_DEV_NUM                   1
#else
#define USBD2_DEV_NUM                   0
#endif
#ifdef  RTE_USB_Device_3
#define USBD3_DEV_NUM                   1
#else
#define USBD3_DEV_NUM                   0
#endif

#define USBD_DEV_NUM                   (USBD0_DEV_NUM + USBD1_DEV_NUM + USBD2_DEV_NUM + USBD3_DEV_NUM)

#ifndef USBD0_EP1
#define USBD0_EP1       0
#endif
#ifndef USBD0_EP2
#define USBD0_EP2       0
#endif
#ifndef USBD0_EP3
#define USBD0_EP3       0
#endif
#ifndef USBD0_EP4
#define USBD0_EP4       0
#endif
#ifndef USBD0_EP5
#define USBD0_EP5       0
#endif
#ifndef USBD0_EP6
#define USBD0_EP6       0
#endif
#ifndef USBD0_EP7
#define USBD0_EP7       0
#endif
#ifndef USBD0_EP8
#define USBD0_EP8       0
#endif
#ifndef USBD0_EP9
#define USBD0_EP9       0
#endif
#ifndef USBD0_EP10
#define USBD0_EP10      0
#endif
#ifndef USBD0_EP11
#define USBD0_EP11      0
#endif
#ifndef USBD0_EP12
#define USBD0_EP12      0
#endif
#ifndef USBD0_EP13
#define USBD0_EP13      0
#endif
#ifndef USBD0_EP14
#define USBD0_EP14      0
#endif
#ifndef USBD0_EP15
#define USBD0_EP15      0
#endif

#ifndef USBD1_EP1
#define USBD1_EP1       0
#endif
#ifndef USBD1_EP2
#define USBD1_EP2       0
#endif
#ifndef USBD1_EP3
#define USBD1_EP3       0
#endif
#ifndef USBD1_EP4
#define USBD1_EP4       0
#endif
#ifndef USBD1_EP5
#define USBD1_EP5       0
#endif
#ifndef USBD1_EP6
#define USBD1_EP6       0
#endif
#ifndef USBD1_EP7
#define USBD1_EP7       0
#endif
#ifndef USBD1_EP8
#define USBD1_EP8       0
#endif
#ifndef USBD1_EP9
#define USBD1_EP9       0
#endif
#ifndef USBD1_EP10
#define USBD1_EP10      0
#endif
#ifndef USBD1_EP11
#define USBD1_EP11      0
#endif
#ifndef USBD1_EP12
#define USBD1_EP12      0
#endif
#ifndef USBD1_EP13
#define USBD1_EP13      0
#endif
#ifndef USBD1_EP14
#define USBD1_EP14      0
#endif
#ifndef USBD1_EP15
#define USBD1_EP15      0
#endif

#ifndef USBD2_EP1
#define USBD2_EP1       0
#endif
#ifndef USBD2_EP2
#define USBD2_EP2       0
#endif
#ifndef USBD2_EP3
#define USBD2_EP3       0
#endif
#ifndef USBD2_EP4
#define USBD2_EP4       0
#endif
#ifndef USBD2_EP5
#define USBD2_EP5       0
#endif
#ifndef USBD2_EP6
#define USBD2_EP6       0
#endif
#ifndef USBD2_EP7
#define USBD2_EP7       0
#endif
#ifndef USBD2_EP8
#define USBD2_EP8       0
#endif
#ifndef USBD2_EP9
#define USBD2_EP9       0
#endif
#ifndef USBD2_EP10
#define USBD2_EP10      0
#endif
#ifndef USBD2_EP11
#define USBD2_EP11      0
#endif
#ifndef USBD2_EP12
#define USBD2_EP12      0
#endif
#ifndef USBD2_EP13
#define USBD2_EP13      0
#endif
#ifndef USBD2_EP14
#define USBD2_EP14      0
#endif
#ifndef USBD2_EP15
#define USBD2_EP15      0
#endif

#ifndef USBD3_EP1
#define USBD3_EP1       0
#endif
#ifndef USBD3_EP2
#define USBD3_EP2       0
#endif
#ifndef USBD3_EP3
#define USBD3_EP3       0
#endif
#ifndef USBD3_EP4
#define USBD3_EP4       0
#endif
#ifndef USBD3_EP5
#define USBD3_EP5       0
#endif
#ifndef USBD3_EP6
#define USBD3_EP6       0
#endif
#ifndef USBD3_EP7
#define USBD3_EP7       0
#endif
#ifndef USBD3_EP8
#define USBD3_EP8       0
#endif
#ifndef USBD3_EP9
#define USBD3_EP9       0
#endif
#ifndef USBD3_EP10
#define USBD3_EP10      0
#endif
#ifndef USBD3_EP11
#define USBD3_EP11      0
#endif
#ifndef USBD3_EP12
#define USBD3_EP12      0
#endif
#ifndef USBD3_EP13
#define USBD3_EP13      0
#endif
#ifndef USBD3_EP14
#define USBD3_EP14      0
#endif
#ifndef USBD3_EP15
#define USBD3_EP15      0
#endif


#if    (USBD_EP_LAST_NUM == 15)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9 , USBD##n##_EP10 , USBD##n##_EP11 , USBD##n##_EP12 , USBD##n##_EP13 , USBD##n##_EP14 , USBD##n##_EP15
#elif  (USBD_EP_LAST_NUM == 14)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9 , USBD##n##_EP10 , USBD##n##_EP11 , USBD##n##_EP12 , USBD##n##_EP13 , USBD##n##_EP14
#elif  (USBD_EP_LAST_NUM == 13)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9 , USBD##n##_EP10 , USBD##n##_EP11 , USBD##n##_EP12 , USBD##n##_EP13
#elif  (USBD_EP_LAST_NUM == 12)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9 , USBD##n##_EP10 , USBD##n##_EP11 , USBD##n##_EP12
#elif  (USBD_EP_LAST_NUM == 11)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9 , USBD##n##_EP10 , USBD##n##_EP11
#elif  (USBD_EP_LAST_NUM == 10)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9 , USBD##n##_EP10
#elif  (USBD_EP_LAST_NUM ==  9)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8 ,  \
                                                 USBD##n##_EP9
#elif  (USBD_EP_LAST_NUM ==  8)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7 , USBD##n##_EP8
#elif  (USBD_EP_LAST_NUM ==  7)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6  , USBD##n##_EP7
#elif  (USBD_EP_LAST_NUM ==  6)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5  , USBD##n##_EP6
#elif  (USBD_EP_LAST_NUM ==  5)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4  , USBD##n##_EP5
#elif  (USBD_EP_LAST_NUM ==  4)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3  , USBD##n##_EP4
#elif  (USBD_EP_LAST_NUM ==  3)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2  , USBD##n##_EP3
#elif  (USBD_EP_LAST_NUM ==  2)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1 , USBD##n##_EP2
#elif  (USBD_EP_LAST_NUM ==  1)
#define EP_POINTERS(n)  &usbd_core_thread_id[n], USBD##n##_EP1
#elif  (USBD_EP_LAST_NUM ==  0)
#define EP_POINTERS(n)  &usbd_core_thread_id[n]
#else
#define EP_POINTERS(n)
#endif


/*------------------------------------------------------------------------------
 *      USB Device 0..3 Configurations
 *----------------------------------------------------------------------------*/

#if    (USBD_DEV_NUM > 0)

osThreadId usbd_core_thread_id          [USBD_DEV_NUM];

osSemaphoreId usbd_driver_semaphore_id  [USBD_DEV_NUM];

#ifdef  RTE_USB_Device_0
osSemaphoreDef (usbd0_driver_semaphore_def);
#endif
#ifdef  RTE_USB_Device_1
osSemaphoreDef (usbd1_driver_semaphore_def);
#endif
#ifdef  RTE_USB_Device_2
osSemaphoreDef (usbd2_driver_semaphore_def);
#endif
#ifdef  RTE_USB_Device_3
osSemaphoreDef (usbd3_driver_semaphore_def);
#endif

const osSemaphoreDef_t * const usbd_driver_semaphore_def_ptr[USBD_DEV_NUM] = {
#ifdef  RTE_USB_Device_0
        osSemaphore(usbd0_driver_semaphore_def)
#endif
#ifdef  RTE_USB_Device_1
      , osSemaphore(usbd1_driver_semaphore_def)
#endif
#ifdef  RTE_USB_Device_2
      , osSemaphore(usbd2_driver_semaphore_def)
#endif
#ifdef  RTE_USB_Device_3
      , osSemaphore(usbd3_driver_semaphore_def)
#endif
};

#ifdef  RTE_USB_Device_0
extern  usbd_dev_t      usbd0_dev;
#endif
#ifdef  RTE_USB_Device_1
extern  usbd_dev_t      usbd1_dev;
#endif
#ifdef  RTE_USB_Device_2
extern  usbd_dev_t      usbd2_dev;
#endif
#ifdef  RTE_USB_Device_3
extern  usbd_dev_t      usbd3_dev;
#endif

const uint8_t   usbd_dev_num =  USBD_DEV_NUM;

const   usbd_dev_t * const usbd_dev_ptr[USBD_DEV_NUM]  = {
#ifdef  RTE_USB_Device_0
       &usbd0_dev
#endif
#ifdef  RTE_USB_Device_1
     , &usbd1_dev
#endif
#ifdef  RTE_USB_Device_2
     , &usbd2_dev
#endif
#ifdef  RTE_USB_Device_3
     , &usbd3_dev
#endif
};

#endif


/*------------------------------------------------------------------------------
 *      USB Device Custom Class 0..3 Configurations
 *----------------------------------------------------------------------------*/

#ifdef  RTE_USB_Device_CustomClass_0
#define USBD_CUSTOM_CLASS0_NUM          1
#else
#define USBD_CUSTOM_CLASS0_NUM          0
#endif
#ifdef  RTE_USB_Device_CustomClass_1
#define USBD_CUSTOM_CLASS1_NUM          1
#else
#define USBD_CUSTOM_CLASS1_NUM          0
#endif
#ifdef  RTE_USB_Device_CustomClass_2
#define USBD_CUSTOM_CLASS2_NUM          1
#else
#define USBD_CUSTOM_CLASS2_NUM          0
#endif
#ifdef  RTE_USB_Device_CustomClass_3
#define USBD_CUSTOM_CLASS3_NUM          1
#else
#define USBD_CUSTOM_CLASS3_NUM          0
#endif

#define USBD_CUSTOM_CLASS_NUM          (USBD_CUSTOM_CLASS0_NUM + USBD_CUSTOM_CLASS1_NUM + USBD_CUSTOM_CLASS2_NUM + USBD_CUSTOM_CLASS3_NUM)

#if    (USBD_CUSTOM_CLASS_NUM > 0)

#if    (USBD_EP_LAST_NUM == 15)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread ), osThread(USBD_CustomClass##n##_EP10_Thread), osThread(USBD_CustomClass##n##_EP11_Thread), osThread(USBD_CustomClass##n##_EP12_Thread), \
                                           osThread(USBD_CustomClass##n##_EP13_Thread), osThread(USBD_CustomClass##n##_EP14_Thread), osThread(USBD_CustomClass##n##_EP15_Thread)
#elif  (USBD_EP_LAST_NUM == 14)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread ), osThread(USBD_CustomClass##n##_EP10_Thread), osThread(USBD_CustomClass##n##_EP11_Thread), osThread(USBD_CustomClass##n##_EP12_Thread), \
                                           osThread(USBD_CustomClass##n##_EP13_Thread), osThread(USBD_CustomClass##n##_EP14_Thread)
#elif  (USBD_EP_LAST_NUM == 13)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread ), osThread(USBD_CustomClass##n##_EP10_Thread), osThread(USBD_CustomClass##n##_EP11_Thread), osThread(USBD_CustomClass##n##_EP12_Thread), \
                                           osThread(USBD_CustomClass##n##_EP13_Thread)
#elif  (USBD_EP_LAST_NUM == 12)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread ), osThread(USBD_CustomClass##n##_EP10_Thread), osThread(USBD_CustomClass##n##_EP11_Thread), osThread(USBD_CustomClass##n##_EP12_Thread)
#elif  (USBD_EP_LAST_NUM == 11)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread ), osThread(USBD_CustomClass##n##_EP10_Thread), osThread(USBD_CustomClass##n##_EP11_Thread)
#elif  (USBD_EP_LAST_NUM == 10)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread ), osThread(USBD_CustomClass##n##_EP10_Thread)
#elif  (USBD_EP_LAST_NUM ==  9)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP9_Thread )
#elif  (USBD_EP_LAST_NUM ==  8)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread ), osThread(USBD_CustomClass##n##_EP8_Thread )
#elif  (USBD_EP_LAST_NUM ==  7)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread ), osThread(USBD_CustomClass##n##_EP7_Thread )
#elif  (USBD_EP_LAST_NUM ==  6)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread ), osThread(USBD_CustomClass##n##_EP6_Thread )
#elif  (USBD_EP_LAST_NUM ==  5)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread ), \
                                           osThread(USBD_CustomClass##n##_EP5_Thread )
#elif  (USBD_EP_LAST_NUM ==  4)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread ), osThread(USBD_CustomClass##n##_EP4_Thread )
#elif  (USBD_EP_LAST_NUM ==  3)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread ), osThread(USBD_CustomClass##n##_EP3_Thread )
#elif  (USBD_EP_LAST_NUM ==  2)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread ), osThread(USBD_CustomClass##n##_EP2_Thread )
#elif  (USBD_EP_LAST_NUM ==  1)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0, osThread(USBD_CustomClass##n##_EP1_Thread )
#elif  (USBD_EP_LAST_NUM ==  0)
#define CUSTOM_CLASS_EP_THREAD_DEF(n)   0
#else
#define CUSTOM_CLASS_EP_THREAD_DEF(n)
#endif

extern void USBD_CustomClass_EP_Thread (uint8_t instance);

#ifdef  RTE_USB_Device_CustomClass_0
#if    (USBD_EP_LAST_NUM >= 1)
        void USBD_CustomClass0_EP1_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP1_Thread,  USBD_CUSTOM_CLASS0_EP1_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP1_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 2)
extern  void USBD_CustomClass0_EP2_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP2_Thread,  USBD_CUSTOM_CLASS0_EP2_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP2_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 3)
extern  void USBD_CustomClass0_EP3_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP3_Thread,  USBD_CUSTOM_CLASS0_EP3_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP3_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 4)
extern  void USBD_CustomClass0_EP4_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP4_Thread,  USBD_CUSTOM_CLASS0_EP4_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP4_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 5)
extern  void USBD_CustomClass0_EP5_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP5_Thread,  USBD_CUSTOM_CLASS0_EP5_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP5_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 6)
extern  void USBD_CustomClass0_EP6_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP6_Thread,  USBD_CUSTOM_CLASS0_EP6_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP6_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 7)
extern  void USBD_CustomClass0_EP7_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP7_Thread,  USBD_CUSTOM_CLASS0_EP7_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP7_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 8)
extern  void USBD_CustomClass0_EP8_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP8_Thread,  USBD_CUSTOM_CLASS0_EP8_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP8_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 9)
extern  void USBD_CustomClass0_EP9_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP9_Thread,  USBD_CUSTOM_CLASS0_EP9_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS0_EP9_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 10)
extern  void USBD_CustomClass0_EP10_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP10_Thread, USBD_CUSTOM_CLASS0_EP10_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS0_EP10_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 11)
extern  void USBD_CustomClass0_EP11_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP11_Thread, USBD_CUSTOM_CLASS0_EP11_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS0_EP11_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 12)
extern  void USBD_CustomClass0_EP12_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP12_Thread, USBD_CUSTOM_CLASS0_EP12_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS0_EP12_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 13)
extern  void USBD_CustomClass0_EP13_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP13_Thread, USBD_CUSTOM_CLASS0_EP13_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS0_EP13_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 14)
extern  void USBD_CustomClass0_EP14_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP14_Thread, USBD_CUSTOM_CLASS0_EP14_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS0_EP14_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM == 15)
extern  void USBD_CustomClass0_EP15_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (0); }
osThreadDef (USBD_CustomClass0_EP15_Thread, USBD_CUSTOM_CLASS0_EP15_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS0_EP15_THREAD_STACK_SIZE);
#endif
#endif

#ifdef  RTE_USB_Device_CustomClass_1
#if    (USBD_EP_LAST_NUM >= 1)
        void USBD_CustomClass1_EP1_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP1_Thread,  USBD_CUSTOM_CLASS1_EP1_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP1_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 2)
extern  void USBD_CustomClass1_EP2_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP2_Thread,  USBD_CUSTOM_CLASS1_EP2_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP2_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 3)
extern  void USBD_CustomClass1_EP3_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP3_Thread,  USBD_CUSTOM_CLASS1_EP3_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP3_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 4)
extern  void USBD_CustomClass1_EP4_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP4_Thread,  USBD_CUSTOM_CLASS1_EP4_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP4_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 5)
extern  void USBD_CustomClass1_EP5_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP5_Thread,  USBD_CUSTOM_CLASS1_EP5_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP5_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 6)
extern  void USBD_CustomClass1_EP6_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP6_Thread,  USBD_CUSTOM_CLASS1_EP6_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP6_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 7)
extern  void USBD_CustomClass1_EP7_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP7_Thread,  USBD_CUSTOM_CLASS1_EP7_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP7_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 8)
extern  void USBD_CustomClass1_EP8_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP8_Thread,  USBD_CUSTOM_CLASS1_EP8_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP8_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 9)
extern  void USBD_CustomClass1_EP9_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP9_Thread,  USBD_CUSTOM_CLASS1_EP9_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS1_EP9_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 10)
extern  void USBD_CustomClass1_EP10_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP10_Thread, USBD_CUSTOM_CLASS1_EP10_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS1_EP10_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 11)
extern  void USBD_CustomClass1_EP11_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP11_Thread, USBD_CUSTOM_CLASS1_EP11_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS1_EP11_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 12)
extern  void USBD_CustomClass1_EP12_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP12_Thread, USBD_CUSTOM_CLASS1_EP12_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS1_EP12_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 13)
extern  void USBD_CustomClass1_EP13_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP13_Thread, USBD_CUSTOM_CLASS1_EP13_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS1_EP13_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 14)
extern  void USBD_CustomClass1_EP14_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP14_Thread, USBD_CUSTOM_CLASS1_EP14_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS1_EP14_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM == 15)
extern  void USBD_CustomClass1_EP15_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (1); }
osThreadDef (USBD_CustomClass1_EP15_Thread, USBD_CUSTOM_CLASS1_EP15_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS1_EP15_THREAD_STACK_SIZE);
#endif
#endif

#ifdef  RTE_USB_Device_CustomClass_2
#if    (USBD_EP_LAST_NUM >= 1)
        void USBD_CustomClass2_EP1_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP1_Thread,  USBD_CUSTOM_CLASS2_EP1_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP1_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 2)
extern  void USBD_CustomClass2_EP2_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP2_Thread,  USBD_CUSTOM_CLASS2_EP2_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP2_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 3)
extern  void USBD_CustomClass2_EP3_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP3_Thread,  USBD_CUSTOM_CLASS2_EP3_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP3_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 4)
extern  void USBD_CustomClass2_EP4_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP4_Thread,  USBD_CUSTOM_CLASS2_EP4_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP4_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 5)
extern  void USBD_CustomClass2_EP5_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP5_Thread,  USBD_CUSTOM_CLASS2_EP5_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP5_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 6)
extern  void USBD_CustomClass2_EP6_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP6_Thread,  USBD_CUSTOM_CLASS2_EP6_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP6_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 7)
extern  void USBD_CustomClass2_EP7_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP7_Thread,  USBD_CUSTOM_CLASS2_EP7_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP7_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 8)
extern  void USBD_CustomClass2_EP8_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP8_Thread,  USBD_CUSTOM_CLASS2_EP8_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP8_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 9)
extern  void USBD_CustomClass2_EP9_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP9_Thread,  USBD_CUSTOM_CLASS2_EP9_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS2_EP9_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 10)
extern  void USBD_CustomClass2_EP10_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP10_Thread, USBD_CUSTOM_CLASS2_EP10_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS2_EP10_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 11)
extern  void USBD_CustomClass2_EP11_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP11_Thread, USBD_CUSTOM_CLASS2_EP11_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS2_EP11_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 12)
extern  void USBD_CustomClass2_EP12_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP12_Thread, USBD_CUSTOM_CLASS2_EP12_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS2_EP12_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 13)
extern  void USBD_CustomClass2_EP13_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP13_Thread, USBD_CUSTOM_CLASS2_EP13_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS2_EP13_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 14)
extern  void USBD_CustomClass2_EP14_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP14_Thread, USBD_CUSTOM_CLASS2_EP14_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS2_EP14_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM == 15)
extern  void USBD_CustomClass2_EP15_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (2); }
osThreadDef (USBD_CustomClass2_EP15_Thread, USBD_CUSTOM_CLASS2_EP15_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS2_EP15_THREAD_STACK_SIZE);
#endif
#endif

#ifdef  RTE_USB_Device_CustomClass_3
#if    (USBD_EP_LAST_NUM >= 1)
        void USBD_CustomClass3_EP1_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP1_Thread,  USBD_CUSTOM_CLASS3_EP1_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP1_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 2)
extern  void USBD_CustomClass3_EP2_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP2_Thread,  USBD_CUSTOM_CLASS3_EP2_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP2_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 3)
extern  void USBD_CustomClass3_EP3_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP3_Thread,  USBD_CUSTOM_CLASS3_EP3_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP3_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 4)
extern  void USBD_CustomClass3_EP4_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP4_Thread,  USBD_CUSTOM_CLASS3_EP4_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP4_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 5)
extern  void USBD_CustomClass3_EP5_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP5_Thread,  USBD_CUSTOM_CLASS3_EP5_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP5_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 6)
extern  void USBD_CustomClass3_EP6_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP6_Thread,  USBD_CUSTOM_CLASS3_EP6_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP6_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 7)
extern  void USBD_CustomClass3_EP7_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP7_Thread,  USBD_CUSTOM_CLASS3_EP7_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP7_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 8)
extern  void USBD_CustomClass3_EP8_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP8_Thread,  USBD_CUSTOM_CLASS3_EP8_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP8_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 9)
extern  void USBD_CustomClass3_EP9_Thread   (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP9_Thread,  USBD_CUSTOM_CLASS3_EP9_THREAD_PRIORITY,  1, USBD_CUSTOM_CLASS3_EP9_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 10)
extern  void USBD_CustomClass3_EP10_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP10_Thread, USBD_CUSTOM_CLASS3_EP10_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS3_EP10_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 11)
extern  void USBD_CustomClass3_EP11_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP11_Thread, USBD_CUSTOM_CLASS3_EP11_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS3_EP11_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 12)
extern  void USBD_CustomClass3_EP12_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP12_Thread, USBD_CUSTOM_CLASS3_EP12_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS3_EP12_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 13)
extern  void USBD_CustomClass3_EP13_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP13_Thread, USBD_CUSTOM_CLASS3_EP13_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS3_EP13_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM >= 14)
extern  void USBD_CustomClass3_EP14_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP14_Thread, USBD_CUSTOM_CLASS3_EP14_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS3_EP14_THREAD_STACK_SIZE);
#endif
#if    (USBD_EP_LAST_NUM == 15)
extern  void USBD_CustomClass3_EP15_Thread  (void const *arg) { USBD_CustomClass_EP_Thread (3); }
osThreadDef (USBD_CustomClass3_EP15_Thread, USBD_CUSTOM_CLASS3_EP15_THREAD_PRIORITY, 1, USBD_CUSTOM_CLASS3_EP15_THREAD_STACK_SIZE);
#endif
#endif

osThreadId                  usbd_custom_class_ep_thread_id[USBD_CUSTOM_CLASS_NUM][16];
const osThreadDef_t * const usbd_custom_class_ep_thread_def_ptr[USBD_CUSTOM_CLASS_NUM * USBD_EP_NUM] = {
#ifdef  RTE_USB_Device_CustomClass_0
        CUSTOM_CLASS_EP_THREAD_DEF(0)
#endif
#ifdef  RTE_USB_Device_CustomClass_1
      , CUSTOM_CLASS_EP_THREAD_DEF(1)
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , CUSTOM_CLASS_EP_THREAD_DEF(2)
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , CUSTOM_CLASS_EP_THREAD_DEF(3)
#endif
};

const   uint8_t     usbd_custom_class_num  =   USBD_CUSTOM_CLASS_NUM;
usbd_custom_class_t usbd_custom_class         [USBD_CUSTOM_CLASS_NUM] = {
#ifdef  RTE_USB_Device_CustomClass_0
                                      {
                                        USBD_CUSTOM_CLASS0_DEV,
                                        USBD_CUSTOM_CLASS0_IF0_NUM         * USBD_CUSTOM_CLASS0_IF0_EN,
                                        USBD_CUSTOM_CLASS0_IF1_NUM         * USBD_CUSTOM_CLASS0_IF1_EN,
                                        USBD_CUSTOM_CLASS0_IF2_NUM         * USBD_CUSTOM_CLASS0_IF2_EN,
                                        USBD_CUSTOM_CLASS0_IF3_NUM         * USBD_CUSTOM_CLASS0_IF3_EN,
                                        USBD_CUSTOM_CLASS0_EP_MSK,
                                        USBD_CUSTOM_CLASS0_IF0_EP_BULK_OUT * USBD_CUSTOM_CLASS0_IF0_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF0_EP_BULK_IN  * USBD_CUSTOM_CLASS0_IF0_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF0_EP_INT_OUT  * USBD_CUSTOM_CLASS0_IF0_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF0_EP_INT_IN   * USBD_CUSTOM_CLASS0_IF0_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF0_EP_ISO_OUT  * USBD_CUSTOM_CLASS0_IF0_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF0_EP_ISO_IN   * USBD_CUSTOM_CLASS0_IF0_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF1_EP_BULK_OUT * USBD_CUSTOM_CLASS0_IF1_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF1_EP_BULK_IN  * USBD_CUSTOM_CLASS0_IF1_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF1_EP_INT_OUT  * USBD_CUSTOM_CLASS0_IF1_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF1_EP_INT_IN   * USBD_CUSTOM_CLASS0_IF1_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF1_EP_ISO_OUT  * USBD_CUSTOM_CLASS0_IF1_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF1_EP_ISO_IN   * USBD_CUSTOM_CLASS0_IF1_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF2_EP_BULK_OUT * USBD_CUSTOM_CLASS0_IF2_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF2_EP_BULK_IN  * USBD_CUSTOM_CLASS0_IF2_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF2_EP_INT_OUT  * USBD_CUSTOM_CLASS0_IF2_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF2_EP_INT_IN   * USBD_CUSTOM_CLASS0_IF2_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF2_EP_ISO_OUT  * USBD_CUSTOM_CLASS0_IF2_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF2_EP_ISO_IN   * USBD_CUSTOM_CLASS0_IF2_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF3_EP_BULK_OUT * USBD_CUSTOM_CLASS0_IF3_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF3_EP_BULK_IN  * USBD_CUSTOM_CLASS0_IF3_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF3_EP_INT_OUT  * USBD_CUSTOM_CLASS0_IF3_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF3_EP_INT_IN   * USBD_CUSTOM_CLASS0_IF3_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS0_IF3_EP_ISO_OUT  * USBD_CUSTOM_CLASS0_IF3_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS0_IF3_EP_ISO_IN   * USBD_CUSTOM_CLASS0_IF3_EP_ISO_IN_EN,
                                      }
#endif
#ifdef  RTE_USB_Device_CustomClass_1
                                    , {
                                        USBD_CUSTOM_CLASS1_DEV,
                                        USBD_CUSTOM_CLASS1_IF0_NUM         * USBD_CUSTOM_CLASS1_IF0_EN,
                                        USBD_CUSTOM_CLASS1_IF1_NUM         * USBD_CUSTOM_CLASS1_IF1_EN,
                                        USBD_CUSTOM_CLASS1_IF2_NUM         * USBD_CUSTOM_CLASS1_IF2_EN,
                                        USBD_CUSTOM_CLASS1_IF3_NUM         * USBD_CUSTOM_CLASS1_IF3_EN,
                                        USBD_CUSTOM_CLASS1_EP_MSK,
                                        USBD_CUSTOM_CLASS1_IF0_EP_BULK_OUT * USBD_CUSTOM_CLASS1_IF0_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF0_EP_BULK_IN  * USBD_CUSTOM_CLASS1_IF0_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF0_EP_INT_OUT  * USBD_CUSTOM_CLASS1_IF0_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF0_EP_INT_IN   * USBD_CUSTOM_CLASS1_IF0_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF0_EP_ISO_OUT  * USBD_CUSTOM_CLASS1_IF0_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF0_EP_ISO_IN   * USBD_CUSTOM_CLASS1_IF0_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF1_EP_BULK_OUT * USBD_CUSTOM_CLASS1_IF1_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF1_EP_BULK_IN  * USBD_CUSTOM_CLASS1_IF1_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF1_EP_INT_OUT  * USBD_CUSTOM_CLASS1_IF1_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF1_EP_INT_IN   * USBD_CUSTOM_CLASS1_IF1_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF1_EP_ISO_OUT  * USBD_CUSTOM_CLASS1_IF1_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF1_EP_ISO_IN   * USBD_CUSTOM_CLASS1_IF1_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF2_EP_BULK_OUT * USBD_CUSTOM_CLASS1_IF2_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF2_EP_BULK_IN  * USBD_CUSTOM_CLASS1_IF2_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF2_EP_INT_OUT  * USBD_CUSTOM_CLASS1_IF2_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF2_EP_INT_IN   * USBD_CUSTOM_CLASS1_IF2_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF2_EP_ISO_OUT  * USBD_CUSTOM_CLASS1_IF2_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF2_EP_ISO_IN   * USBD_CUSTOM_CLASS1_IF2_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF3_EP_BULK_OUT * USBD_CUSTOM_CLASS1_IF3_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF3_EP_BULK_IN  * USBD_CUSTOM_CLASS1_IF3_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF3_EP_INT_OUT  * USBD_CUSTOM_CLASS1_IF3_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF3_EP_INT_IN   * USBD_CUSTOM_CLASS1_IF3_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS1_IF3_EP_ISO_OUT  * USBD_CUSTOM_CLASS1_IF3_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS1_IF3_EP_ISO_IN   * USBD_CUSTOM_CLASS1_IF3_EP_ISO_IN_EN,
                                      }
#endif
#ifdef  RTE_USB_Device_CustomClass_2
                                    , {
                                        USBD_CUSTOM_CLASS2_DEV,
                                        USBD_CUSTOM_CLASS2_IF0_NUM         * USBD_CUSTOM_CLASS2_IF0_EN,
                                        USBD_CUSTOM_CLASS2_IF1_NUM         * USBD_CUSTOM_CLASS2_IF1_EN,
                                        USBD_CUSTOM_CLASS2_IF2_NUM         * USBD_CUSTOM_CLASS2_IF2_EN,
                                        USBD_CUSTOM_CLASS2_IF3_NUM         * USBD_CUSTOM_CLASS2_IF3_EN,
                                        USBD_CUSTOM_CLASS2_EP_MSK,
                                        USBD_CUSTOM_CLASS2_IF0_EP_BULK_OUT * USBD_CUSTOM_CLASS2_IF0_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF0_EP_BULK_IN  * USBD_CUSTOM_CLASS2_IF0_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF0_EP_INT_OUT  * USBD_CUSTOM_CLASS2_IF0_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF0_EP_INT_IN   * USBD_CUSTOM_CLASS2_IF0_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF0_EP_ISO_OUT  * USBD_CUSTOM_CLASS2_IF0_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF0_EP_ISO_IN   * USBD_CUSTOM_CLASS2_IF0_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF1_EP_BULK_OUT * USBD_CUSTOM_CLASS2_IF1_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF1_EP_BULK_IN  * USBD_CUSTOM_CLASS2_IF1_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF1_EP_INT_OUT  * USBD_CUSTOM_CLASS2_IF1_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF1_EP_INT_IN   * USBD_CUSTOM_CLASS2_IF1_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF1_EP_ISO_OUT  * USBD_CUSTOM_CLASS2_IF1_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF1_EP_ISO_IN   * USBD_CUSTOM_CLASS2_IF1_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF2_EP_BULK_OUT * USBD_CUSTOM_CLASS2_IF2_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF2_EP_BULK_IN  * USBD_CUSTOM_CLASS2_IF2_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF2_EP_INT_OUT  * USBD_CUSTOM_CLASS2_IF2_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF2_EP_INT_IN   * USBD_CUSTOM_CLASS2_IF2_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF2_EP_ISO_OUT  * USBD_CUSTOM_CLASS2_IF2_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF2_EP_ISO_IN   * USBD_CUSTOM_CLASS2_IF2_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF3_EP_BULK_OUT * USBD_CUSTOM_CLASS2_IF3_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF3_EP_BULK_IN  * USBD_CUSTOM_CLASS2_IF3_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF3_EP_INT_OUT  * USBD_CUSTOM_CLASS2_IF3_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF3_EP_INT_IN   * USBD_CUSTOM_CLASS2_IF3_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS2_IF3_EP_ISO_OUT  * USBD_CUSTOM_CLASS2_IF3_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS2_IF3_EP_ISO_IN   * USBD_CUSTOM_CLASS2_IF3_EP_ISO_IN_EN,
                                      }
#endif
#ifdef  RTE_USB_Device_CustomClass_3
                                    , {
                                        USBD_CUSTOM_CLASS3_DEV,
                                        USBD_CUSTOM_CLASS3_IF0_NUM         * USBD_CUSTOM_CLASS3_IF0_EN,
                                        USBD_CUSTOM_CLASS3_IF1_NUM         * USBD_CUSTOM_CLASS3_IF1_EN,
                                        USBD_CUSTOM_CLASS3_IF2_NUM         * USBD_CUSTOM_CLASS3_IF2_EN,
                                        USBD_CUSTOM_CLASS3_IF3_NUM         * USBD_CUSTOM_CLASS3_IF3_EN,
                                        USBD_CUSTOM_CLASS3_EP_MSK,
                                        USBD_CUSTOM_CLASS3_IF0_EP_BULK_OUT * USBD_CUSTOM_CLASS3_IF0_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF0_EP_BULK_IN  * USBD_CUSTOM_CLASS3_IF0_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF0_EP_INT_OUT  * USBD_CUSTOM_CLASS3_IF0_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF0_EP_INT_IN   * USBD_CUSTOM_CLASS3_IF0_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF0_EP_ISO_OUT  * USBD_CUSTOM_CLASS3_IF0_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF0_EP_ISO_IN   * USBD_CUSTOM_CLASS3_IF0_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF1_EP_BULK_OUT * USBD_CUSTOM_CLASS3_IF1_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF1_EP_BULK_IN  * USBD_CUSTOM_CLASS3_IF1_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF1_EP_INT_OUT  * USBD_CUSTOM_CLASS3_IF1_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF1_EP_INT_IN   * USBD_CUSTOM_CLASS3_IF1_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF1_EP_ISO_OUT  * USBD_CUSTOM_CLASS3_IF1_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF1_EP_ISO_IN   * USBD_CUSTOM_CLASS3_IF1_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF2_EP_BULK_OUT * USBD_CUSTOM_CLASS3_IF2_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF2_EP_BULK_IN  * USBD_CUSTOM_CLASS3_IF2_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF2_EP_INT_OUT  * USBD_CUSTOM_CLASS3_IF2_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF2_EP_INT_IN   * USBD_CUSTOM_CLASS3_IF2_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF2_EP_ISO_OUT  * USBD_CUSTOM_CLASS3_IF2_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF2_EP_ISO_IN   * USBD_CUSTOM_CLASS3_IF2_EP_ISO_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF3_EP_BULK_OUT * USBD_CUSTOM_CLASS3_IF3_EP_BULK_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF3_EP_BULK_IN  * USBD_CUSTOM_CLASS3_IF3_EP_BULK_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF3_EP_INT_OUT  * USBD_CUSTOM_CLASS3_IF3_EP_INT_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF3_EP_INT_IN   * USBD_CUSTOM_CLASS3_IF3_EP_INT_IN_EN,
                                        USBD_CUSTOM_CLASS3_IF3_EP_ISO_OUT  * USBD_CUSTOM_CLASS3_IF3_EP_ISO_OUT_EN,
                                        USBD_CUSTOM_CLASS3_IF3_EP_ISO_IN   * USBD_CUSTOM_CLASS3_IF3_EP_ISO_IN_EN,
                                      }
#endif
};
const   usbd_custom_class_t * const usbd_custom_class_ptr[USBD_CUSTOM_CLASS_NUM] = {
#ifdef  RTE_USB_Device_CustomClass_0
                                       &usbd_custom_class[0]
#endif
#ifdef  RTE_USB_Device_CustomClass_1
                                     , &usbd_custom_class[1]
#endif
#ifdef  RTE_USB_Device_CustomClass_2
                                     , &usbd_custom_class[2]
#endif
#ifdef  RTE_USB_Device_CustomClass_3
                                     , &usbd_custom_class[3]
#endif
};

#endif


/*------------------------------------------------------------------------------
 *      USB Device ADC 0..3 Configurations
 *----------------------------------------------------------------------------*/

#ifdef  RTE_USB_Device_ADC_0
#define USBD_ADC0_NUM                   1
#else
#define USBD_ADC0_NUM                   0
#endif
#ifdef  RTE_USB_Device_ADC_1
#define USBD_ADC1_NUM                   1
#else
#define USBD_ADC1_NUM                   0
#endif
#ifdef  RTE_USB_Device_ADC_2
#define USBD_ADC2_NUM                   1
#else
#define USBD_ADC2_NUM                   0
#endif
#ifdef  RTE_USB_Device_ADC_3
#define USBD_ADC3_NUM                   1
#else
#define USBD_ADC3_NUM                   0
#endif

#define USBD_ADC_NUM                   (USBD_ADC0_NUM + USBD_ADC1_NUM + USBD_ADC2_NUM + USBD_ADC3_NUM)

#if    (USBD_ADC_NUM > 0)

#ifdef  RTE_USB_Device_ADC_0
extern  void USBD_ADC0_Thread          (void const *arg);
osThreadDef (USBD_ADC0_Thread, USBD_ADC0_THREAD_PRIORITY, 1, USBD_ADC0_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_ADC_1
extern  void USBD_ADC1_Thread          (void const *arg);
osThreadDef (USBD_ADC1_Thread, USBD_ADC1_THREAD_PRIORITY, 1, USBD_ADC1_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_ADC_2
extern  void USBD_ADC2_Thread          (void const *arg);
osThreadDef (USBD_ADC2_Thread, USBD_ADC2_THREAD_PRIORITY, 1, USBD_ADC2_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_ADC_3
extern  void USBD_ADC3_Thread          (void const *arg);
osThreadDef (USBD_ADC3_Thread, USBD_ADC3_THREAD_PRIORITY, 1, USBD_ADC3_THREAD_STACK_SIZE);
#endif

osThreadId          usbd_adc_thread_id[USBD_ADC_NUM];
const osThreadDef_t * const usbd_adc_thread_def_ptr[USBD_ADC_NUM] = {
#ifdef  RTE_USB_Device_ADC_0
        osThread(USBD_ADC0_Thread)
#endif
#ifdef  RTE_USB_Device_ADC_1
      , osThread(USBD_ADC1_Thread)
#endif
#ifdef  RTE_USB_Device_ADC_2
      , osThread(USBD_ADC2_Thread)
#endif
#ifdef  RTE_USB_Device_ADC_3
      , osThread(USBD_ADC3_Thread)
#endif
};

#ifdef  RTE_USB_Device_ADC_0
#if    (USBD_ADC0_EP_ISO_OUT_EN)
uint8_t             usbd_adc0_out_data_buf [USBD_ADC0_OUT_BUF_SIZE*USBD_ADC0_OUT_BSUBFRAMESIZE] __attribute__((aligned(4)));
#endif
#if    (USBD_ADC0_EP_ISO_IN_EN)
uint8_t             usbd_adc0_in_data_buf  [USBD_ADC0_IN_BUF_SIZE*USBD_ADC0_IN_BSUBFRAMESIZE]   __attribute__((aligned(4)));
#endif
#endif

#ifdef  RTE_USB_Device_ADC_1
#if    (USBD_ADC1_EP_ISO_OUT_EN)
uint8_t             usbd_adc1_out_data_buf [USBD_ADC1_OUT_BUF_SIZE*USBD_ADC1_OUT_BSUBFRAMESIZE] __attribute__((aligned(4)));
#endif
#if    (USBD_ADC1_EP_ISO_IN_EN)
uint8_t             usbd_adc1_in_data_buf  [USBD_ADC1_IN_BUF_SIZE*USBD_ADC1_IN_BSUBFRAMESIZE]   __attribute__((aligned(4)));
#endif
#endif

#ifdef  RTE_USB_Device_ADC_2
#if    (USBD_ADC2_EP_ISO_OUT_EN)
uint8_t             usbd_adc2_out_data_buf [USBD_ADC2_OUT_BUF_SIZE*USBD_ADC2_OUT_BSUBFRAMESIZE] __attribute__((aligned(4)));
#endif
#if    (USBD_ADC2_EP_ISO_IN_EN)
uint8_t             usbd_adc2_in_data_buf  [USBD_ADC2_IN_BUF_SIZE*USBD_ADC2_IN_BSUBFRAMESIZE]   __attribute__((aligned(4)));
#endif
#endif

#ifdef  RTE_USB_Device_ADC_3
#if    (USBD_ADC3_EP_ISO_OUT_EN)
uint8_t             usbd_adc3_out_data_buf [USBD_ADC3_OUT_BUF_SIZE*USBD_ADC3_OUT_BSUBFRAMESIZE] __attribute__((aligned(4)));
#endif
#if    (USBD_ADC3_EP_ISO_IN_EN)
uint8_t             usbd_adc3_in_data_buf  [USBD_ADC3_IN_BUF_SIZE*USBD_ADC3_IN_BSUBFRAMESIZE]   __attribute__((aligned(4)));
#endif
#endif

const   uint8_t     usbd_adc_num  =     USBD_ADC_NUM;

#ifdef  RTE_USB_Device_ADC_0
#if    (USBD_ADC0_EP_ISO_OUT_EN)
usbd_adc_spkr_data_t usbd_adc0_spkr_data;
usbd_adc_code_t      usbd_adc0_out_data = {
                                        usbd_adc0_out_data_buf,
                                        USBD_ADC0_IF_SPKR_NUM,
                                        2,
                                        USBD_ADC0_EP_ISO_OUT,
                                        USBD_ADC0_OUT_CH_NUM,
                                        USBD_ADC0_OUT_TSAM_FREQ,
                                        USBD_ADC0_OUT_BSUBFRAMESIZE,
                                        USBD_ADC0_OUT_BBITRESOLUTION,
                                        USBD_ADC0_OUT_BUF_SIZE*USBD_ADC0_OUT_BSUBFRAMESIZE,
                                        USBD_ADC0_EP_ISO_OUT_WMAXPACKETSIZE
};
#endif
#if    (USBD_ADC0_EP_ISO_IN_EN)
usbd_adc_mic_data_t  usbd_adc0_mic_data;
usbd_adc_code_t      usbd_adc0_in_data = {
                                        usbd_adc0_in_data_buf,
                                        USBD_ADC0_IF_MIC_NUM,
                                        USBD_ADC0_IF_SPKR*3+2,
                                        USBD_ADC0_EP_ISO_IN,
                                        USBD_ADC0_IN_CH_NUM,
                                        USBD_ADC0_IN_TSAM_FREQ,
                                        USBD_ADC0_IN_BSUBFRAMESIZE,
                                        USBD_ADC0_IN_BBITRESOLUTION,
                                        USBD_ADC0_IN_BUF_SIZE*USBD_ADC0_IN_BSUBFRAMESIZE,
                                        USBD_ADC0_EP_ISO_IN_WMAXPACKETSIZE
};
#endif
#endif
#ifdef  RTE_USB_Device_ADC_1
#if    (USBD_ADC1_EP_ISO_OUT_EN)
usbd_adc_spkr_data_t usbd_adc1_spkr_data;
usbd_adc_code_t      usbd_adc1_out_data = {
                                        usbd_adc1_out_data_buf,
                                        USBD_ADC1_IF_SPKR_NUM,
                                        2,
                                        USBD_ADC1_EP_ISO_OUT,
                                        USBD_ADC1_OUT_CH_NUM,
                                        USBD_ADC1_OUT_TSAM_FREQ,
                                        USBD_ADC1_OUT_BSUBFRAMESIZE,
                                        USBD_ADC1_OUT_BBITRESOLUTION,
                                        USBD_ADC1_OUT_BUF_SIZE*USBD_ADC1_OUT_BSUBFRAMESIZE,
                                        USBD_ADC1_EP_ISO_OUT_WMAXPACKETSIZE
};
#endif
#if    (USBD_ADC1_EP_ISO_IN_EN)
usbd_adc_mic_data_t  usbd_adc1_mic_data;
usbd_adc_code_t      usbd_adc1_in_data = {
                                        usbd_adc1_in_data_buf,
                                        USBD_ADC1_IF_MIC_NUM,
                                        USBD_ADC1_IF_SPKR*3+2,
                                        USBD_ADC1_EP_ISO_IN,
                                        USBD_ADC1_IN_CH_NUM,
                                        USBD_ADC1_IN_TSAM_FREQ,
                                        USBD_ADC1_IN_BSUBFRAMESIZE,
                                        USBD_ADC1_IN_BBITRESOLUTION,
                                        USBD_ADC1_IN_BUF_SIZE*USBD_ADC1_IN_BSUBFRAMESIZE,
                                        USBD_ADC1_EP_ISO_IN_WMAXPACKETSIZE
};
#endif
#endif
#ifdef  RTE_USB_Device_ADC_2
#if    (USBD_ADC2_EP_ISO_OUT_EN)
usbd_adc_spkr_data_t usbd_adc2_spkr_data;
usbd_adc_code_t      usbd_adc2_out_data = {
                                        usbd_adc2_out_data_buf,
                                        USBD_ADC2_IF_SPKR_NUM,
                                        2,
                                        USBD_ADC2_EP_ISO_OUT,
                                        USBD_ADC2_OUT_CH_NUM,
                                        USBD_ADC2_OUT_TSAM_FREQ,
                                        USBD_ADC2_OUT_BSUBFRAMESIZE,
                                        USBD_ADC2_OUT_BBITRESOLUTION,
                                        USBD_ADC2_OUT_BUF_SIZE*USBD_ADC2_OUT_BSUBFRAMESIZE,
                                        USBD_ADC2_EP_ISO_OUT_WMAXPACKETSIZE
};
#endif
#if    (USBD_ADC2_EP_ISO_IN_EN)
usbd_adc_mic_data_t  usbd_adc2_mic_data;
usbd_adc_code_t      usbd_adc2_in_data = {
                                        usbd_adc2_in_data_buf,
                                        USBD_ADC2_IF_MIC_NUM,
                                        USBD_ADC2_IF_SPKR*3+2,
                                        USBD_ADC2_EP_ISO_IN,
                                        USBD_ADC2_IN_CH_NUM,
                                        USBD_ADC2_IN_TSAM_FREQ,
                                        USBD_ADC2_IN_BSUBFRAMESIZE,
                                        USBD_ADC2_IN_BBITRESOLUTION,
                                        USBD_ADC2_IN_BUF_SIZE*USBD_ADC2_IN_BSUBFRAMESIZE,
                                        USBD_ADC2_EP_ISO_IN_WMAXPACKETSIZE
};
#endif
#endif
#ifdef  RTE_USB_Device_ADC_3
#if    (USBD_ADC3_EP_ISO_OUT_EN)
usbd_adc_spkr_data_t usbd_adc3_spkr_data;
usbd_adc_code_t      usbd_adc3_out_data = {
                                        usbd_adc3_out_data_buf,
                                        USBD_ADC3_IF_SPKR_NUM,
                                        2,
                                        USBD_ADC3_EP_ISO_OUT,
                                        USBD_ADC3_OUT_CH_NUM,
                                        USBD_ADC3_OUT_TSAM_FREQ,
                                        USBD_ADC3_OUT_BSUBFRAMESIZE,
                                        USBD_ADC3_OUT_BBITRESOLUTION,
                                        USBD_ADC3_OUT_BUF_SIZE*USBD_ADC3_OUT_BSUBFRAMESIZE,
                                        USBD_ADC3_EP_ISO_OUT_WMAXPACKETSIZE
};
#endif
#if    (USBD_ADC3_EP_ISO_IN_EN)
usbd_adc_mic_data_t  usbd_adc3_mic_data;
usbd_adc_code_t      usbd_adc3_in_data = {
                                        usbd_adc3_in_data_buf,
                                        USBD_ADC3_IF_MIC_NUM,
                                        USBD_ADC3_IF_SPKR*3+2,
                                        USBD_ADC3_EP_ISO_IN,
                                        USBD_ADC3_IN_CH_NUM,
                                        USBD_ADC3_IN_TSAM_FREQ,
                                        USBD_ADC3_IN_BSUBFRAMESIZE,
                                        USBD_ADC3_IN_BBITRESOLUTION,
                                        USBD_ADC3_IN_BUF_SIZE*USBD_ADC3_IN_BSUBFRAMESIZE,
                                        USBD_ADC3_EP_ISO_IN_WMAXPACKETSIZE
};
#endif
#endif

usbd_adc_t usbd_adc                    [USBD_ADC_NUM] = {
#ifdef  RTE_USB_Device_ADC_0
                                      {
#if    (USBD_ADC0_EP_ISO_OUT_EN)
                                       &usbd_adc0_spkr_data,
                                       &usbd_adc0_out_data,
#else
                                        NULL,
                                        NULL,
#endif
#if    (USBD_ADC0_EP_ISO_IN_EN)
                                       &usbd_adc0_mic_data,
                                       &usbd_adc0_in_data,
#else
                                        NULL,
                                        NULL,
#endif
                                      }
#endif
#ifdef  RTE_USB_Device_ADC_1
                                    , {
#if    (USBD_ADC1_EP_ISO_OUT_EN)
                                       &usbd_adc1_spkr_data,
                                       &usbd_adc1_out_data,
#else
                                        NULL,
                                        NULL,
#endif
#if    (USBD_ADC1_EP_ISO_IN_EN)
                                       &usbd_adc1_mic_data,
                                       &usbd_adc1_in_data,
#else
                                        NULL,
                                        NULL,
#endif
                                      }
#endif

#ifdef  RTE_USB_Device_ADC_2
                                    , {
#if    (USBD_ADC2_EP_ISO_OUT_EN)
                                       &usbd_adc2_spkr_data,
                                       &usbd_adc2_out_data,
#else
                                        NULL,
                                        NULL,
#endif
#if    (USBD_ADC2_EP_ISO_IN_EN)
                                       &usbd_adc2_mic_data,
                                       &usbd_adc2_in_data,
#else
                                        NULL,
                                        NULL,
#endif
                                      }
#endif


#ifdef  RTE_USB_Device_ADC_3
                                    , {
#if    (USBD_ADC3_EP_ISO_OUT_EN)
                                       &usbd_adc3_spkr_data,
                                       &usbd_adc3_out_data,
#else
                                        NULL,
                                        NULL,
#endif
#if    (USBD_ADC3_EP_ISO_IN_EN)
                                       &usbd_adc3_mic_data,
                                       &usbd_adc3_in_data,
#else
                                        NULL,
                                        NULL,
#endif
                                      }
#endif
};
const   usbd_adc_t * const usbd_adc_ptr[USBD_ADC_NUM] = {
#ifdef  RTE_USB_Device_ADC_0
       &usbd_adc[0]
#endif
#ifdef  RTE_USB_Device_ADC_1
     , &usbd_adc[1]
#endif
#ifdef  RTE_USB_Device_ADC_2
     , &usbd_adc[2]
#endif
#ifdef  RTE_USB_Device_ADC_3
     , &usbd_adc[3]
#endif
};

#endif


/*------------------------------------------------------------------------------
 *      USB Device CDC 0..3 Configurations
 *----------------------------------------------------------------------------*/

#define USBD_CDC0_MAX_PACKET           (MAX_OF_2(USBD_CDC0_WMAXPACKETSIZE,  USBD_CDC0_HS_WMAXPACKETSIZE))
#define USBD_CDC1_MAX_PACKET           (MAX_OF_2(USBD_CDC1_WMAXPACKETSIZE,  USBD_CDC1_HS_WMAXPACKETSIZE))
#define USBD_CDC2_MAX_PACKET           (MAX_OF_2(USBD_CDC2_WMAXPACKETSIZE,  USBD_CDC2_HS_WMAXPACKETSIZE))
#define USBD_CDC3_MAX_PACKET           (MAX_OF_2(USBD_CDC3_WMAXPACKETSIZE,  USBD_CDC3_HS_WMAXPACKETSIZE))
#define USBD_CDC0_MAX_PACKET1          (MAX_OF_2(USBD_CDC0_WMAXPACKETSIZE1, USBD_CDC0_HS_WMAXPACKETSIZE1))
#define USBD_CDC1_MAX_PACKET1          (MAX_OF_2(USBD_CDC1_WMAXPACKETSIZE1, USBD_CDC1_HS_WMAXPACKETSIZE1))
#define USBD_CDC2_MAX_PACKET1          (MAX_OF_2(USBD_CDC2_WMAXPACKETSIZE1, USBD_CDC2_HS_WMAXPACKETSIZE1))
#define USBD_CDC3_MAX_PACKET1          (MAX_OF_2(USBD_CDC3_WMAXPACKETSIZE1, USBD_CDC3_HS_WMAXPACKETSIZE1))

#ifdef  RTE_USB_Device_CDC_0
#define USBD_CDC0_NUM                   1
#else
#define USBD_CDC0_NUM                   0
#endif
#ifdef  RTE_USB_Device_CDC_1
#define USBD_CDC1_NUM                   1
#else
#define USBD_CDC1_NUM                   0
#endif
#ifdef  RTE_USB_Device_CDC_2
#define USBD_CDC2_NUM                   1
#else
#define USBD_CDC2_NUM                   0
#endif
#ifdef  RTE_USB_Device_CDC_3
#define USBD_CDC3_NUM                   1
#else
#define USBD_CDC3_NUM                   0
#endif

#define USBD_CDC_NUM                   (USBD_CDC0_NUM + USBD_CDC1_NUM + USBD_CDC2_NUM + USBD_CDC3_NUM)

#if    (USBD_CDC_NUM > 0)

#ifdef  RTE_USB_Device_CDC_0
extern  void USBD_CDC0_Int_Thread      (void const *arg);
osThreadDef (USBD_CDC0_Int_Thread,  USBD_CDC0_INT_THREAD_PRIORITY,  1, USBD_CDC0_INT_THREAD_STACK_SIZE);
extern  void USBD_CDC0_Bulk_Thread     (void const *arg);
osThreadDef (USBD_CDC0_Bulk_Thread, USBD_CDC0_BULK_THREAD_PRIORITY, 1, USBD_CDC0_BULK_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_CDC_1
extern  void USBD_CDC1_Int_Thread      (void const *arg);
osThreadDef (USBD_CDC1_Int_Thread,  USBD_CDC1_INT_THREAD_PRIORITY,  1, USBD_CDC1_INT_THREAD_STACK_SIZE);
extern  void USBD_CDC1_Bulk_Thread     (void const *arg);
osThreadDef (USBD_CDC1_Bulk_Thread, USBD_CDC1_BULK_THREAD_PRIORITY, 1, USBD_CDC1_BULK_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_CDC_2
extern  void USBD_CDC2_Int_Thread      (void const *arg);
osThreadDef (USBD_CDC2_Int_Thread,  USBD_CDC2_INT_THREAD_PRIORITY,  1, USBD_CDC2_INT_THREAD_STACK_SIZE);
extern  void USBD_CDC2_Bulk_Thread     (void const *arg);
osThreadDef (USBD_CDC2_Bulk_Thread, USBD_CDC2_BULK_THREAD_PRIORITY, 1, USBD_CDC2_BULK_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_CDC_3
extern  void USBD_CDC3_Int_Thread      (void const *arg);
osThreadDef (USBD_CDC3_Int_Thread,  USBD_CDC3_INT_THREAD_PRIORITY,  1, USBD_CDC3_INT_THREAD_STACK_SIZE);
extern  void USBD_CDC3_Bulk_Thread     (void const *arg);
osThreadDef (USBD_CDC3_Bulk_Thread, USBD_CDC3_BULK_THREAD_PRIORITY, 1, USBD_CDC3_BULK_THREAD_STACK_SIZE);
#endif

osThreadId          usbd_cdc_int_thread_id[USBD_CDC_NUM];
const osThreadDef_t * const usbd_cdc_int_thread_def_ptr[USBD_CDC_NUM] = {
#ifdef  RTE_USB_Device_CDC_0
        osThread(USBD_CDC0_Int_Thread)
#endif
#ifdef  RTE_USB_Device_CDC_1
      , osThread(USBD_CDC1_Int_Thread)
#endif
#ifdef  RTE_USB_Device_CDC_2
      , osThread(USBD_CDC2_Int_Thread)
#endif
#ifdef  RTE_USB_Device_CDC_3
      , osThread(USBD_CDC3_Int_Thread)
#endif
};

osThreadId          usbd_cdc_bulk_thread_id[USBD_CDC_NUM];
const osThreadDef_t * const usbd_cdc_bulk_thread_def_ptr[USBD_CDC_NUM] = {
#ifdef  RTE_USB_Device_CDC_0
        osThread(USBD_CDC0_Bulk_Thread)
#endif
#ifdef  RTE_USB_Device_CDC_1
      , osThread(USBD_CDC1_Bulk_Thread)
#endif
#ifdef  RTE_USB_Device_CDC_2
      , osThread(USBD_CDC2_Bulk_Thread)
#endif
#ifdef  RTE_USB_Device_CDC_3
      , osThread(USBD_CDC3_Bulk_Thread)
#endif
};


#ifdef  RTE_USB_Device_CDC_0
#if     USBD_CDC0_ACM
uint8_t             usbd_cdc0_send_buf   [USBD_CDC0_ACM_SEND_BUF_SIZE]    __attribute__((aligned(4)));
uint8_t             usbd_cdc0_receive_buf[USBD_CDC0_ACM_RECEIVE_BUF_SIZE] __attribute__((aligned(4)));
uint8_t             usbd_cdc0_notify_buf [10]                             __attribute__((aligned(4)));
#elif   USBD_CDC0_NCM
#if    (USBD_CDC0_NCM_RAW_ENABLE == 0)
#if    (USBD_CDC0_NCM_NTB_IN_BUF_CNT == 0)
#error Maximum CDC0 NCM IN NTB Data Buffers can not be 0!
#elif  (USBD_CDC0_NCM_NTB_IN_BUF_CNT > 2)
#error Maximum CDC0 NCM IN NTB Data Buffers can not be more than 2!
#endif
#if    (USBD_CDC0_NCM_NTB_OUT_BUF_CNT == 0)
#error Maximum CDC0 NCM OUT NTB Data Buffers can not be 0!
#elif  (USBD_CDC0_NCM_NTB_OUT_BUF_CNT > 2)
#error Maximum CDC0 NCM OUT NTB Data Buffers can not be more than 2!
#endif
#define USBD_CDC0_NCM_NTB_IN_BUF_SIZE    (USBD_CDC0_NCM_NTB_IN_BUF_CNT *USBD_CDC0_NCM_DW_NTB_IN_MAX_SIZE)
#define USBD_CDC0_NCM_NTB_OUT_BUF_SIZE   (USBD_CDC0_NCM_NTB_OUT_BUF_CNT*USBD_CDC0_NCM_DW_NTB_OUT_MAX_SIZE)
uint8_t             usbd_cdc0_send_buf   [USBD_CDC0_NCM_NTB_IN_BUF_SIZE]  __attribute__((aligned(4)));
uint8_t             usbd_cdc0_receive_buf[USBD_CDC0_NCM_NTB_OUT_BUF_SIZE] __attribute__((aligned(4)));
#else
#define USBD_CDC0_NCM_NTB_IN_BUF_SIZE    (0)
#define USBD_CDC0_NCM_NTB_OUT_BUF_SIZE   (0)
#endif
uint8_t             usbd_cdc0_notify_buf [16]                             __attribute__((aligned(4)));
#endif
#endif

#ifdef  RTE_USB_Device_CDC_1
#if     USBD_CDC1_ACM
uint8_t             usbd_cdc1_send_buf   [USBD_CDC1_ACM_SEND_BUF_SIZE]    __attribute__((aligned(4)));
uint8_t             usbd_cdc1_receive_buf[USBD_CDC1_ACM_RECEIVE_BUF_SIZE] __attribute__((aligned(4)));
uint8_t             usbd_cdc1_notify_buf [10]                             __attribute__((aligned(4)));
#elif   USBD_CDC1_NCM
#if    (USBD_CDC1_NCM_RAW_ENABLE == 0)
#if    (USBD_CDC1_NCM_NTB_IN_BUF_CNT == 0)
#error Maximum CDC1 NCM IN NTB Data Buffers can not be 0!
#elif  (USBD_CDC1_NCM_NTB_IN_BUF_CNT > 2)
#error Maximum CDC1 NCM IN NTB Data Buffers can not be more than 2!
#endif
#if    (USBD_CDC1_NCM_NTB_OUT_BUF_CNT == 0)
#error Maximum CDC1 NCM OUT NTB Data Buffers can not be 0!
#elif  (USBD_CDC1_NCM_NTB_OUT_BUF_CNT > 2)
#error Maximum CDC1 NCM OUT NTB Data Buffers can not be more than 2!
#endif
#define USBD_CDC1_NCM_NTB_IN_BUF_SIZE    (USBD_CDC1_NCM_NTB_IN_BUF_CNT *USBD_CDC1_NCM_DW_NTB_IN_MAX_SIZE)
#define USBD_CDC1_NCM_NTB_OUT_BUF_SIZE   (USBD_CDC1_NCM_NTB_OUT_BUF_CNT*USBD_CDC1_NCM_DW_NTB_OUT_MAX_SIZE)
uint8_t             usbd_cdc1_send_buf   [USBD_CDC1_NCM_NTB_IN_BUF_SIZE]  __attribute__((aligned(4)));
uint8_t             usbd_cdc1_receive_buf[USBD_CDC1_NCM_NTB_OUT_BUF_SIZE] __attribute__((aligned(4)));
#else
#define USBD_CDC1_NCM_NTB_IN_BUF_SIZE    (0)
#define USBD_CDC1_NCM_NTB_OUT_BUF_SIZE   (0)
#endif
uint8_t             usbd_cdc1_notify_buf [16]                             __attribute__((aligned(4)));
#endif
#endif

#ifdef  RTE_USB_Device_CDC_2
#if     USBD_CDC2_ACM
uint8_t             usbd_cdc2_send_buf   [USBD_CDC2_ACM_SEND_BUF_SIZE]    __attribute__((aligned(4)));
uint8_t             usbd_cdc2_receive_buf[USBD_CDC2_ACM_RECEIVE_BUF_SIZE] __attribute__((aligned(4)));
uint8_t             usbd_cdc2_notify_buf [10]                             __attribute__((aligned(4)));
#elif   USBD_CDC2_NCM
#if    (USBD_CDC2_NCM_RAW_ENABLE == 0)
#if    (USBD_CDC2_NCM_NTB_IN_BUF_CNT == 0)
#error Maximum CDC2 NCM IN NTB Data Buffers can not be 0!
#elif  (USBD_CDC2_NCM_NTB_IN_BUF_CNT > 2)
#error Maximum CDC2 NCM IN NTB Data Buffers can not be more than 2!
#endif
#if    (USBD_CDC2_NCM_NTB_OUT_BUF_CNT == 0)
#error Maximum CDC2 NCM OUT NTB Data Buffers can not be 0!
#elif  (USBD_CDC2_NCM_NTB_OUT_BUF_CNT > 2)
#error Maximum CDC2 NCM OUT NTB Data Buffers can not be more than 2!
#endif
#define USBD_CDC2_NCM_NTB_IN_BUF_SIZE    (USBD_CDC2_NCM_NTB_IN_BUF_CNT *USBD_CDC2_NCM_DW_NTB_IN_MAX_SIZE)
#define USBD_CDC2_NCM_NTB_OUT_BUF_SIZE   (USBD_CDC2_NCM_NTB_OUT_BUF_CNT*USBD_CDC2_NCM_DW_NTB_OUT_MAX_SIZE)
uint8_t             usbd_cdc2_send_buf   [USBD_CDC2_NCM_NTB_IN_BUF_SIZE]  __attribute__((aligned(4)));
uint8_t             usbd_cdc2_receive_buf[USBD_CDC2_NCM_NTB_OUT_BUF_SIZE] __attribute__((aligned(4)));
#else
#define USBD_CDC2_NCM_NTB_IN_BUF_SIZE    (0)
#define USBD_CDC2_NCM_NTB_OUT_BUF_SIZE   (0)
#endif
uint8_t             usbd_cdc2_notify_buf [16]                             __attribute__((aligned(4)));
#endif
#endif

#ifdef  RTE_USB_Device_CDC_3
#if     USBD_CDC3_ACM
uint8_t             usbd_cdc3_send_buf   [USBD_CDC3_ACM_SEND_BUF_SIZE]    __attribute__((aligned(4)));
uint8_t             usbd_cdc3_receive_buf[USBD_CDC3_ACM_RECEIVE_BUF_SIZE] __attribute__((aligned(4)));
uint8_t             usbd_cdc3_notify_buf [10]                             __attribute__((aligned(4)));
#elif   USBD_CDC3_NCM
#if    (USBD_CDC3_NCM_RAW_ENABLE == 0)
#if    (USBD_CDC3_NCM_NTB_IN_BUF_CNT == 0)
#error Maximum CDC3 NCM IN NTB Data Buffers can not be 0!
#elif  (USBD_CDC3_NCM_NTB_IN_BUF_CNT > 2)
#error Maximum CDC3 NCM IN NTB Data Buffers can not be more than 2!
#endif
#if    (USBD_CDC3_NCM_NTB_OUT_BUF_CNT == 0)
#error Maximum CDC3 NCM OUT NTB Data Buffers can not be 0!
#elif  (USBD_CDC3_NCM_NTB_OUT_BUF_CNT > 2)
#error Maximum CDC3 NCM OUT NTB Data Buffers can not be more than 2!
#endif
#define USBD_CDC3_NCM_NTB_IN_BUF_SIZE    (USBD_CDC3_NCM_NTB_IN_BUF_CNT *USBD_CDC3_NCM_DW_NTB_IN_MAX_SIZE)
#define USBD_CDC3_NCM_NTB_OUT_BUF_SIZE   (USBD_CDC3_NCM_NTB_OUT_BUF_CNT*USBD_CDC3_NCM_DW_NTB_OUT_MAX_SIZE)
uint8_t             usbd_cdc3_send_buf   [USBD_CDC3_NCM_NTB_IN_BUF_SIZE]  __attribute__((aligned(4)));
uint8_t             usbd_cdc3_receive_buf[USBD_CDC3_NCM_NTB_OUT_BUF_SIZE] __attribute__((aligned(4)));
#else
#define USBD_CDC3_NCM_NTB_IN_BUF_SIZE    (0)
#define USBD_CDC3_NCM_NTB_OUT_BUF_SIZE   (0)
#endif
uint8_t             usbd_cdc3_notify_buf [16]                             __attribute__((aligned(4)));
#endif
#endif

const   uint8_t     usbd_cdc_num  =     USBD_CDC_NUM;
usbd_cdc_data_t     usbd_cdc_data      [USBD_CDC_NUM];
usbd_cdc_t          usbd_cdc           [USBD_CDC_NUM] = {
#ifdef  RTE_USB_Device_CDC_0
                                      {
#if   ((USBD_CDC0_NCM != 0) && (USBD_CDC0_NCM_RAW_ENABLE == 1))
                                        NULL,
                                        NULL,
#else
                                        usbd_cdc0_send_buf,
                                        usbd_cdc0_receive_buf,
#endif
                                        usbd_cdc0_notify_buf,
                                       &usbd_cdc_data[0],
                                        USBD_CDC0_DEV,
                                        USBD_CDC0_ACM,
                                        USBD_CDC0_IF0_NUM,
                                        USBD_CDC0_IF1_NUM,
                                        USBD_CDC0_EP_INT_IN,
                                        USBD_CDC0_EP_BULK_IN,
                                        USBD_CDC0_EP_BULK_OUT,
#if     USBD_CDC0_ACM
                                        USBD_CDC0_ACM_SEND_BUF_SIZE,
                                        USBD_CDC0_ACM_RECEIVE_BUF_SIZE,
#elif   USBD_CDC0_NCM
                                        USBD_CDC0_NCM_NTB_IN_BUF_SIZE,
                                        USBD_CDC0_NCM_NTB_OUT_BUF_SIZE,
#endif
                                      { USBD_CDC0_WMAXPACKETSIZE,  USBD_CDC0_HS_WMAXPACKETSIZE  },
                                      { USBD_CDC0_WMAXPACKETSIZE1, USBD_CDC0_HS_WMAXPACKETSIZE1 },
#if     USBD_CDC0_ACM
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0
#elif   USBD_CDC0_NCM
                                        USBD_CDC0_NCM_RAW_ENABLE,
                                        USBD_CDC0_NCM_NTB_IN_BUF_CNT,
                                        USBD_CDC0_NCM_NTB_OUT_BUF_CNT,
                                        USBD_CDC0_NCM_W_MAX_SEGMENT_SIZE,
                                        USBD_CDC0_NCM_BM_NTB_FORMATS_SUPPORTED,
                                        USBD_CDC0_NCM_DW_NTB_IN_MAX_SIZE,
                                        USBD_CDC0_NCM_W_NDP_IN_DIVISOR,
                                        USBD_CDC0_NCM_W_NDP_IN_PAYLOAD_REMINDER,
                                        USBD_CDC0_NCM_W_NDP_IN_ALIGNMENT,
                                        USBD_CDC0_NCM_DW_NTB_OUT_MAX_SIZE,
                                        USBD_CDC0_NCM_W_NDP_OUT_DIVISOR,
                                        USBD_CDC0_NCM_W_NDP_OUT_PAYLOAD_REMINDER,
                                        USBD_CDC0_NCM_W_NDP_OUT_ALIGNMENT
#endif
                                      }
#endif
#ifdef  RTE_USB_Device_CDC_1
                                    , {
#if   ((USBD_CDC1_NCM != 0) && (USBD_CDC1_NCM_RAW_ENABLE == 1))
                                        NULL,
                                        NULL,
#else
                                        usbd_cdc1_send_buf,
                                        usbd_cdc1_receive_buf,
#endif
                                        usbd_cdc1_notify_buf,
                                       &usbd_cdc_data[1],
                                        USBD_CDC1_DEV,
                                        USBD_CDC1_ACM,
                                        USBD_CDC1_IF0_NUM,
                                        USBD_CDC1_IF1_NUM,
                                        USBD_CDC1_EP_INT_IN,
                                        USBD_CDC1_EP_BULK_IN,
                                        USBD_CDC1_EP_BULK_OUT,
#if     USBD_CDC1_ACM
                                        USBD_CDC1_ACM_SEND_BUF_SIZE,
                                        USBD_CDC1_ACM_RECEIVE_BUF_SIZE,
#elif   USBD_CDC1_NCM
                                        USBD_CDC1_NCM_NTB_IN_BUF_SIZE,
                                        USBD_CDC1_NCM_NTB_OUT_BUF_SIZE,
#endif
                                      { USBD_CDC1_WMAXPACKETSIZE,  USBD_CDC1_HS_WMAXPACKETSIZE  },
                                      { USBD_CDC1_WMAXPACKETSIZE1, USBD_CDC1_HS_WMAXPACKETSIZE1 },
#if     USBD_CDC1_ACM
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0
#elif   USBD_CDC1_NCM
                                        USBD_CDC1_NCM_RAW_ENABLE,
                                        USBD_CDC1_NCM_NTB_IN_BUF_CNT,
                                        USBD_CDC1_NCM_NTB_OUT_BUF_CNT,
                                        USBD_CDC1_NCM_W_MAX_SEGMENT_SIZE,
                                        USBD_CDC1_NCM_BM_NTB_FORMATS_SUPPORTED,
                                        USBD_CDC1_NCM_DW_NTB_IN_MAX_SIZE,
                                        USBD_CDC1_NCM_W_NDP_IN_DIVISOR,
                                        USBD_CDC1_NCM_W_NDP_IN_PAYLOAD_REMINDER,
                                        USBD_CDC1_NCM_W_NDP_IN_ALIGNMENT,
                                        USBD_CDC1_NCM_DW_NTB_OUT_MAX_SIZE,
                                        USBD_CDC1_NCM_W_NDP_OUT_DIVISOR,
                                        USBD_CDC1_NCM_W_NDP_OUT_PAYLOAD_REMINDER,
                                        USBD_CDC1_NCM_W_NDP_OUT_ALIGNMENT
#endif
                                      }
#endif
#ifdef  RTE_USB_Device_CDC_2
                                    , {
#if   ((USBD_CDC2_NCM != 0) && (USBD_CDC2_NCM_RAW_ENABLE == 1))
                                        NULL,
                                        NULL,
#else
                                        usbd_cdc2_send_buf,
                                        usbd_cdc2_receive_buf,
#endif
                                        usbd_cdc2_notify_buf,
                                       &usbd_cdc_data[2],
                                        USBD_CDC2_DEV,
                                        USBD_CDC2_ACM,
                                        USBD_CDC2_IF0_NUM,
                                        USBD_CDC2_IF1_NUM,
                                        USBD_CDC2_EP_INT_IN,
                                        USBD_CDC2_EP_BULK_IN,
                                        USBD_CDC2_EP_BULK_OUT,
#if     USBD_CDC2_ACM
                                        USBD_CDC2_ACM_SEND_BUF_SIZE,
                                        USBD_CDC2_ACM_RECEIVE_BUF_SIZE,
#elif   USBD_CDC2_NCM
                                        USBD_CDC2_NCM_NTB_IN_BUF_SIZE,
                                        USBD_CDC2_NCM_NTB_OUT_BUF_SIZE,
#endif
                                      { USBD_CDC2_WMAXPACKETSIZE,  USBD_CDC2_HS_WMAXPACKETSIZE  },
                                      { USBD_CDC2_WMAXPACKETSIZE1, USBD_CDC2_HS_WMAXPACKETSIZE1 },
#if     USBD_CDC2_ACM
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0
#elif   USBD_CDC2_NCM
                                        USBD_CDC2_NCM_RAW_ENABLE,
                                        USBD_CDC2_NCM_NTB_IN_BUF_CNT,
                                        USBD_CDC2_NCM_NTB_OUT_BUF_CNT,
                                        USBD_CDC2_NCM_W_MAX_SEGMENT_SIZE,
                                        USBD_CDC2_NCM_BM_NTB_FORMATS_SUPPORTED,
                                        USBD_CDC2_NCM_DW_NTB_IN_MAX_SIZE,
                                        USBD_CDC2_NCM_W_NDP_IN_DIVISOR,
                                        USBD_CDC2_NCM_W_NDP_IN_PAYLOAD_REMINDER,
                                        USBD_CDC2_NCM_W_NDP_IN_ALIGNMENT,
                                        USBD_CDC2_NCM_DW_NTB_OUT_MAX_SIZE,
                                        USBD_CDC2_NCM_W_NDP_OUT_DIVISOR,
                                        USBD_CDC2_NCM_W_NDP_OUT_PAYLOAD_REMINDER,
                                        USBD_CDC2_NCM_W_NDP_OUT_ALIGNMENT
#endif
                                      }
#endif
#ifdef  RTE_USB_Device_CDC_3
                                    , {
#if   ((USBD_CDC3_NCM != 0) && (USBD_CDC3_NCM_RAW_ENABLE == 1))
                                        NULL,
                                        NULL,
#else
                                        usbd_cdc3_send_buf,
                                        usbd_cdc3_receive_buf,
#endif
                                        usbd_cdc3_notify_buf,
                                       &usbd_cdc_data[3],
                                        USBD_CDC3_DEV,
                                        USBD_CDC3_ACM,
                                        USBD_CDC3_IF0_NUM,
                                        USBD_CDC3_IF1_NUM,
                                        USBD_CDC3_EP_INT_IN,
                                        USBD_CDC3_EP_BULK_IN,
                                        USBD_CDC3_EP_BULK_OUT,
#if     USBD_CDC3_ACM
                                        USBD_CDC3_ACM_SEND_BUF_SIZE,
                                        USBD_CDC3_ACM_RECEIVE_BUF_SIZE,
#elif   USBD_CDC3_NCM
                                        USBD_CDC3_NCM_NTB_IN_BUF_SIZE,
                                        USBD_CDC3_NCM_NTB_OUT_BUF_SIZE,
#endif
                                      { USBD_CDC3_WMAXPACKETSIZE,  USBD_CDC3_HS_WMAXPACKETSIZE  },
                                      { USBD_CDC3_WMAXPACKETSIZE1, USBD_CDC3_HS_WMAXPACKETSIZE1 },
#if     USBD_CDC3_ACM
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0,
                                        0
#elif   USBD_CDC3_NCM
                                        USBD_CDC3_NCM_RAW_ENABLE,
                                        USBD_CDC3_NCM_NTB_IN_BUF_CNT,
                                        USBD_CDC3_NCM_NTB_OUT_BUF_CNT,
                                        USBD_CDC3_NCM_W_MAX_SEGMENT_SIZE,
                                        USBD_CDC3_NCM_BM_NTB_FORMATS_SUPPORTED,
                                        USBD_CDC3_NCM_DW_NTB_IN_MAX_SIZE,
                                        USBD_CDC3_NCM_W_NDP_IN_DIVISOR,
                                        USBD_CDC3_NCM_W_NDP_IN_PAYLOAD_REMINDER,
                                        USBD_CDC3_NCM_W_NDP_IN_ALIGNMENT,
                                        USBD_CDC3_NCM_DW_NTB_OUT_MAX_SIZE,
                                        USBD_CDC3_NCM_W_NDP_OUT_DIVISOR,
                                        USBD_CDC3_NCM_W_NDP_OUT_PAYLOAD_REMINDER,
                                        USBD_CDC3_NCM_W_NDP_OUT_ALIGNMENT
#endif
                                      }
#endif
};
const   usbd_cdc_t * const usbd_cdc_ptr[USBD_CDC_NUM] = {
#ifdef  RTE_USB_Device_CDC_0
       &usbd_cdc[0]
#endif
#ifdef  RTE_USB_Device_CDC_1
     , &usbd_cdc[1]
#endif
#ifdef  RTE_USB_Device_CDC_2
     , &usbd_cdc[2]
#endif
#ifdef  RTE_USB_Device_CDC_3
     , &usbd_cdc[3]
#endif
};

#endif

#endif  /* LAST_DEVICE_COMPILE */


/*------------------------------------------------------------------------------
 *      USB Device HID 0..3 Configurations
 *----------------------------------------------------------------------------*/

#define USBD_HID0_MAX_PACKET           (MAX_OF_2(USBD_HID0_WMAXPACKETSIZE, USBD_HID0_HS_WMAXPACKETSIZE))
#define USBD_HID1_MAX_PACKET           (MAX_OF_2(USBD_HID1_WMAXPACKETSIZE, USBD_HID1_HS_WMAXPACKETSIZE))
#define USBD_HID2_MAX_PACKET           (MAX_OF_2(USBD_HID2_WMAXPACKETSIZE, USBD_HID2_HS_WMAXPACKETSIZE))
#define USBD_HID3_MAX_PACKET           (MAX_OF_2(USBD_HID3_WMAXPACKETSIZE, USBD_HID3_HS_WMAXPACKETSIZE))

#ifdef  RTE_USB_Device_HID_0
#define USBD_HID0_NUM                   1
#else
#define USBD_HID0_NUM                   0
#endif
#ifdef  RTE_USB_Device_HID_1
#define USBD_HID1_NUM                   1
#else
#define USBD_HID1_NUM                   0
#endif
#ifdef  RTE_USB_Device_HID_2
#define USBD_HID2_NUM                   1
#else
#define USBD_HID2_NUM                   0
#endif
#ifdef  RTE_USB_Device_HID_3
#define USBD_HID3_NUM                   1
#else
#define USBD_HID3_NUM                   0
#endif

#define USBD_HID_NUM                   (USBD_HID0_NUM + USBD_HID1_NUM + USBD_HID2_NUM + USBD_HID3_NUM)

#ifdef  LAST_DEVICE_COMPILE

#if    (USBD_HID_NUM > 0)

#ifdef  RTE_USB_Device_HID_0
extern  void USBD_HID0_Thread          (void const *arg);
osThreadDef (USBD_HID0_Thread, USBD_HID0_THREAD_PRIORITY, 1, USBD_HID0_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_HID_1
extern  void USBD_HID1_Thread          (void const *arg);
osThreadDef (USBD_HID1_Thread, USBD_HID1_THREAD_PRIORITY, 1, USBD_HID1_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_HID_2
extern  void USBD_HID2_Thread          (void const *arg);
osThreadDef (USBD_HID2_Thread, USBD_HID2_THREAD_PRIORITY, 1, USBD_HID2_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_HID_3
extern  void USBD_HID3_Thread          (void const *arg);
osThreadDef (USBD_HID3_Thread, USBD_HID3_THREAD_PRIORITY, 1, USBD_HID3_THREAD_STACK_SIZE);
#endif

osThreadId          usbd_hid_thread_id[USBD_HID_NUM];
const osThreadDef_t * const usbd_hid_thread_def_ptr[USBD_HID_NUM] = {
#ifdef  RTE_USB_Device_HID_0
        osThread(USBD_HID0_Thread)
#endif
#ifdef  RTE_USB_Device_HID_1
      , osThread(USBD_HID1_Thread)
#endif
#ifdef  RTE_USB_Device_HID_2
      , osThread(USBD_HID2_Thread)
#endif
#ifdef  RTE_USB_Device_HID_3
      , osThread(USBD_HID3_Thread)
#endif
};

extern  void USBD_HID_Timer            (void const *arg);
#ifdef  RTE_USB_Device_HID_0
osTimerDef         (usbd_hid0_timer, USBD_HID_Timer);
#endif
#ifdef  RTE_USB_Device_HID_1
osTimerDef         (usbd_hid1_timer, USBD_HID_Timer);
#endif
#ifdef  RTE_USB_Device_HID_2
osTimerDef         (usbd_hid2_timer, USBD_HID_Timer);
#endif
#ifdef  RTE_USB_Device_HID_3
osTimerDef         (usbd_hid3_timer, USBD_HID_Timer);
#endif
const osTimerDef_t * const usbd_hid_timer_def_ptr[USBD_HID_NUM] = {
#ifdef  RTE_USB_Device_HID_0
        osTimer(usbd_hid0_timer)
#endif
#ifdef  RTE_USB_Device_HID_1
      , osTimer(usbd_hid1_timer)
#endif
#ifdef  RTE_USB_Device_HID_2
      , osTimer(usbd_hid2_timer)
#endif
#ifdef  RTE_USB_Device_HID_3
      , osTimer(usbd_hid3_timer)
#endif
};

osTimerId           usbd_hid_timer_id[USBD_HID_NUM];

#ifdef  RTE_USB_Device_HID_0
uint16_t            usbd_hid0_idle_count [USBD_HID0_IN_REPORT_NUM];
uint16_t            usbd_hid0_idle_reload[USBD_HID0_IN_REPORT_NUM];
uint8_t             usbd_hid0_idle_set   [USBD_HID0_IN_REPORT_NUM];
uint8_t             usbd_hid0_in_report  [USBD_HID0_IN_REPORT_MAX_SZ  +(USBD_HID0_IN_REPORT_MAX_SZ>1)]   __attribute__((aligned(4)));
uint8_t             usbd_hid0_out_report [USBD_HID0_OUT_REPORT_MAX_SZ +(USBD_HID0_OUT_REPORT_MAX_SZ>1)]  __attribute__((aligned(4)));
uint8_t             usbd_hid0_feat_report[USBD_HID0_FEAT_REPORT_MAX_SZ+(USBD_HID0_FEAT_REPORT_MAX_SZ>1)] __attribute__((aligned(4)));
#endif

#ifdef  RTE_USB_Device_HID_1
uint16_t            usbd_hid1_idle_count [USBD_HID1_IN_REPORT_NUM];
uint16_t            usbd_hid1_idle_reload[USBD_HID1_IN_REPORT_NUM];
uint8_t             usbd_hid1_idle_set   [USBD_HID1_IN_REPORT_NUM];
uint8_t             usbd_hid1_in_report  [USBD_HID1_IN_REPORT_MAX_SZ  +(USBD_HID1_IN_REPORT_MAX_SZ>1)]   __attribute__((aligned(4)));
uint8_t             usbd_hid1_out_report [USBD_HID1_OUT_REPORT_MAX_SZ +(USBD_HID1_OUT_REPORT_MAX_SZ>1)]  __attribute__((aligned(4)));
uint8_t             usbd_hid1_feat_report[USBD_HID1_FEAT_REPORT_MAX_SZ+(USBD_HID1_FEAT_REPORT_MAX_SZ>1)] __attribute__((aligned(4)));
#endif

#ifdef  RTE_USB_Device_HID_2
uint16_t            usbd_hid2_idle_count [USBD_HID2_IN_REPORT_NUM];
uint16_t            usbd_hid2_idle_reload[USBD_HID2_IN_REPORT_NUM];
uint8_t             usbd_hid2_idle_set   [USBD_HID2_IN_REPORT_NUM];
uint8_t             usbd_hid2_in_report  [USBD_HID2_IN_REPORT_MAX_SZ  +(USBD_HID2_IN_REPORT_MAX_SZ>1)]   __attribute__((aligned(4)));
uint8_t             usbd_hid2_out_report [USBD_HID2_OUT_REPORT_MAX_SZ +(USBD_HID2_OUT_REPORT_MAX_SZ>1)]  __attribute__((aligned(4)));
uint8_t             usbd_hid2_feat_report[USBD_HID2_FEAT_REPORT_MAX_SZ+(USBD_HID2_FEAT_REPORT_MAX_SZ>1)] __attribute__((aligned(4)));
#endif

#ifdef  RTE_USB_Device_HID_3
uint16_t            usbd_hid3_idle_count [USBD_HID3_IN_REPORT_NUM];
uint16_t            usbd_hid3_idle_reload[USBD_HID3_IN_REPORT_NUM];
uint8_t             usbd_hid3_idle_set   [USBD_HID3_IN_REPORT_NUM];
uint8_t             usbd_hid3_in_report  [USBD_HID3_IN_REPORT_MAX_SZ  +(USBD_HID3_IN_REPORT_MAX_SZ>1)]   __attribute__((aligned(4)));
uint8_t             usbd_hid3_out_report [USBD_HID3_OUT_REPORT_MAX_SZ +(USBD_HID3_OUT_REPORT_MAX_SZ>1)]  __attribute__((aligned(4)));
uint8_t             usbd_hid3_feat_report[USBD_HID3_FEAT_REPORT_MAX_SZ+(USBD_HID3_FEAT_REPORT_MAX_SZ>1)] __attribute__((aligned(4)));
#endif

const   uint8_t     usbd_hid_num  =     USBD_HID_NUM;
usbd_hid_data_t     usbd_hid_data      [USBD_HID_NUM];
usbd_hid_t          usbd_hid           [USBD_HID_NUM] = {
#ifdef  RTE_USB_Device_HID_0
                                      {
                                        usbd_hid0_idle_count,
                                        usbd_hid0_idle_reload,
                                        usbd_hid0_idle_set,
                                        usbd_hid0_in_report,
                                        usbd_hid0_out_report,
                                        usbd_hid0_feat_report,
                                       &usbd_hid_data[0],
                                        USBD_HID0_DEV,
                                        USBD_HID0_IF0_NUM,
                                        USBD_HID0_EP_INT_IN,
                                        USBD_HID0_EP_INT_OUT,
                                      { USBD_HID0_EP_INT_IN_BINTERVAL,       (2 << ((USBD_HID0_EP_INT_IN_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID0_EP_INT_IN_WMAXPACKETSIZE,  USBD_HID0_EP_INT_IN_HS_WMAXPACKETSIZE },
                                      { USBD_HID0_EP_INT_OUT_BINTERVAL,      (2 << ((USBD_HID0_EP_INT_OUT_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID0_EP_INT_OUT_WMAXPACKETSIZE, USBD_HID0_EP_INT_OUT_HS_WMAXPACKETSIZE },
                                        USBD_HID0_IN_REPORT_NUM,
                                        USBD_HID0_OUT_REPORT_NUM,
                                        USBD_HID0_IN_REPORT_MAX_SZ,
                                        USBD_HID0_OUT_REPORT_MAX_SZ,
                                        USBD_HID0_FEAT_REPORT_MAX_SZ,
                                      }
#endif
#ifdef  RTE_USB_Device_HID_1
                                    , {
                                        usbd_hid1_idle_count,
                                        usbd_hid1_idle_reload,
                                        usbd_hid1_idle_set,
                                        usbd_hid1_in_report,
                                        usbd_hid1_out_report,
                                        usbd_hid1_feat_report,
                                       &usbd_hid_data[1],
                                        USBD_HID1_DEV,
                                        USBD_HID1_IF0_NUM,
                                        USBD_HID1_EP_INT_IN,
                                        USBD_HID1_EP_INT_OUT,
                                      { USBD_HID1_EP_INT_IN_BINTERVAL,       (2 << ((USBD_HID1_EP_INT_IN_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID1_EP_INT_IN_WMAXPACKETSIZE,  USBD_HID1_EP_INT_IN_HS_WMAXPACKETSIZE },
                                      { USBD_HID1_EP_INT_OUT_BINTERVAL,      (2 << ((USBD_HID1_EP_INT_OUT_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID1_EP_INT_OUT_WMAXPACKETSIZE, USBD_HID1_EP_INT_OUT_HS_WMAXPACKETSIZE },
                                        USBD_HID1_IN_REPORT_NUM,
                                        USBD_HID1_OUT_REPORT_NUM,
                                        USBD_HID1_IN_REPORT_MAX_SZ,
                                        USBD_HID1_OUT_REPORT_MAX_SZ,
                                        USBD_HID1_FEAT_REPORT_MAX_SZ,
                                      }
#endif
#ifdef  RTE_USB_Device_HID_2
                                    , {
                                        usbd_hid2_idle_count,
                                        usbd_hid2_idle_reload,
                                        usbd_hid2_idle_set,
                                        usbd_hid2_in_report,
                                        usbd_hid2_out_report,
                                        usbd_hid2_feat_report,
                                       &usbd_hid_data[2],
                                        USBD_HID2_DEV,
                                        USBD_HID2_IF0_NUM,
                                        USBD_HID2_EP_INT_IN,
                                        USBD_HID2_EP_INT_OUT,
                                      { USBD_HID2_EP_INT_IN_BINTERVAL,       (2 << ((USBD_HID2_EP_INT_IN_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID2_EP_INT_IN_WMAXPACKETSIZE,  USBD_HID2_EP_INT_IN_HS_WMAXPACKETSIZE },
                                      { USBD_HID2_EP_INT_OUT_BINTERVAL,      (2 << ((USBD_HID2_EP_INT_OUT_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID2_EP_INT_OUT_WMAXPACKETSIZE, USBD_HID2_EP_INT_OUT_HS_WMAXPACKETSIZE },
                                        USBD_HID2_IN_REPORT_NUM,
                                        USBD_HID2_OUT_REPORT_NUM,
                                        USBD_HID2_IN_REPORT_MAX_SZ,
                                        USBD_HID2_OUT_REPORT_MAX_SZ,
                                        USBD_HID2_FEAT_REPORT_MAX_SZ,
                                      }
#endif
#ifdef  RTE_USB_Device_HID_3
                                    , {
                                        usbd_hid3_idle_count,
                                        usbd_hid3_idle_reload,
                                        usbd_hid3_idle_set,
                                        usbd_hid3_in_report,
                                        usbd_hid3_out_report,
                                        usbd_hid3_feat_report,
                                       &usbd_hid_data[3],
                                        USBD_HID3_DEV,
                                        USBD_HID3_IF0_NUM,
                                        USBD_HID3_EP_INT_IN,
                                        USBD_HID3_EP_INT_OUT,
                                      { USBD_HID3_EP_INT_IN_BINTERVAL,       (2 << ((USBD_HID3_EP_INT_IN_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID3_EP_INT_IN_WMAXPACKETSIZE,  USBD_HID3_EP_INT_IN_HS_WMAXPACKETSIZE },
                                      { USBD_HID3_EP_INT_OUT_BINTERVAL,      (2 << ((USBD_HID3_EP_INT_OUT_HS_BINTERVAL & 0x0F)-1)) },
                                      { USBD_HID3_EP_INT_OUT_WMAXPACKETSIZE, USBD_HID3_EP_INT_OUT_HS_WMAXPACKETSIZE },
                                        USBD_HID3_IN_REPORT_NUM,
                                        USBD_HID3_OUT_REPORT_NUM,
                                        USBD_HID3_IN_REPORT_MAX_SZ,
                                        USBD_HID3_OUT_REPORT_MAX_SZ,
                                        USBD_HID3_FEAT_REPORT_MAX_SZ,
                                      }
#endif
};
const   usbd_hid_t *usbd_hid_ptr       [USBD_HID_NUM] = {
#ifdef  RTE_USB_Device_HID_0
       &usbd_hid[0]
#endif
#ifdef  RTE_USB_Device_HID_1
     , &usbd_hid[1]
#endif
#ifdef  RTE_USB_Device_HID_2
     , &usbd_hid[2]
#endif
#ifdef  RTE_USB_Device_HID_3
     , &usbd_hid[3]
#endif
};

#endif


/*------------------------------------------------------------------------------
 *      USB Device MSC 0..3 Configurations
 *----------------------------------------------------------------------------*/

#define USBD_MSC0_MAX_PACKET           (MAX_OF_2(USBD_MSC0_WMAXPACKETSIZE, USBD_MSC0_HS_WMAXPACKETSIZE))
#define USBD_MSC1_MAX_PACKET           (MAX_OF_2(USBD_MSC1_WMAXPACKETSIZE, USBD_MSC1_HS_WMAXPACKETSIZE))
#define USBD_MSC2_MAX_PACKET           (MAX_OF_2(USBD_MSC2_WMAXPACKETSIZE, USBD_MSC2_HS_WMAXPACKETSIZE))
#define USBD_MSC3_MAX_PACKET           (MAX_OF_2(USBD_MSC3_WMAXPACKETSIZE, USBD_MSC3_HS_WMAXPACKETSIZE))

#ifdef  RTE_USB_Device_MSC_0
#define USBD_MSC0_NUM                   1
#else
#define USBD_MSC0_NUM                   0
#endif
#ifdef  RTE_USB_Device_MSC_1
#define USBD_MSC1_NUM                   1
#else
#define USBD_MSC1_NUM                   0
#endif
#ifdef  RTE_USB_Device_MSC_2
#define USBD_MSC2_NUM                   1
#else
#define USBD_MSC2_NUM                   0
#endif
#ifdef  RTE_USB_Device_MSC_3
#define USBD_MSC3_NUM                   1
#else
#define USBD_MSC3_NUM                   0
#endif

#define USBD_MSC_NUM                   (USBD_MSC0_NUM + USBD_MSC1_NUM + USBD_MSC2_NUM + USBD_MSC3_NUM)

#if    (USBD_MSC_NUM > 0)

// Check settings
#ifdef  RTE_USB_Device_MSC_0
#if    (USBD_MSC0_BULK_BUF_SIZE < USBD_MSC0_WMAXPACKETSIZE   ) || \
       (USBD_MSC0_BULK_BUF_SIZE < USBD_MSC0_HS_WMAXPACKETSIZE)
#error Maximum Bulk Buffer Size for Mass Storage Instance 0 can not be smaller then Bulk Endpoint Maximum Packet Size!
#endif
#endif

#ifdef  RTE_USB_Device_MSC_1
#if    (USBD_MSC1_BULK_BUF_SIZE < USBD_MSC1_WMAXPACKETSIZE   ) || \
       (USBD_MSC1_BULK_BUF_SIZE < USBD_MSC1_HS_WMAXPACKETSIZE)
#error Maximum Bulk Buffer Size for Mass Storage Instance 1 can not be smaller then Bulk Endpoint Maximum Packet Size!
#endif
#endif

#ifdef  RTE_USB_Device_MSC_2
#if    (USBD_MSC2_BULK_BUF_SIZE < USBD_MSC2_WMAXPACKETSIZE   ) || \
       (USBD_MSC2_BULK_BUF_SIZE < USBD_MSC2_HS_WMAXPACKETSIZE)
#error Maximum Bulk Buffer Size for Mass Storage Instance 2 can not be smaller then Bulk Endpoint Maximum Packet Size!
#endif
#endif

#ifdef  RTE_USB_Device_MSC_3
#if    (USBD_MSC3_BULK_BUF_SIZE < USBD_MSC3_WMAXPACKETSIZE   ) || \
       (USBD_MSC3_BULK_BUF_SIZE < USBD_MSC3_HS_WMAXPACKETSIZE)
#error Maximum Bulk Buffer Size for Mass Storage Instance 3 can not be smaller then Bulk Endpoint Maximum Packet Size!
#endif
#endif

#ifdef  RTE_USB_Device_MSC_0
extern  void USBD_MSC0_Thread          (void const *arg);
osThreadDef (USBD_MSC0_Thread, USBD_MSC0_THREAD_PRIORITY, 1, USBD_MSC0_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_MSC_1
extern  void USBD_MSC1_Thread          (void const *arg);
osThreadDef (USBD_MSC1_Thread, USBD_MSC1_THREAD_PRIORITY, 1, USBD_MSC1_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_MSC_2
extern  void USBD_MSC2_Thread          (void const *arg);
osThreadDef (USBD_MSC2_Thread, USBD_MSC2_THREAD_PRIORITY, 1, USBD_MSC2_THREAD_STACK_SIZE);
#endif
#ifdef  RTE_USB_Device_MSC_3
extern  void USBD_MSC3_Thread          (void const *arg);
osThreadDef (USBD_MSC3_Thread, USBD_MSC3_THREAD_PRIORITY, 1, USBD_MSC3_THREAD_STACK_SIZE);
#endif

osThreadId          usbd_msc_thread_id[USBD_MSC_NUM];
const osThreadDef_t * const usbd_msc_thread_def_ptr[USBD_MSC_NUM] = {
#ifdef  RTE_USB_Device_MSC_0
        osThread(USBD_MSC0_Thread)
#endif
#ifdef  RTE_USB_Device_MSC_1
      , osThread(USBD_MSC1_Thread)
#endif
#ifdef  RTE_USB_Device_MSC_2
      , osThread(USBD_MSC2_Thread)
#endif
#ifdef  RTE_USB_Device_MSC_3
      , osThread(USBD_MSC3_Thread)
#endif
};

#ifdef  RTE_USB_Device_MSC_0
extern  void USBD_MSC0_Thread          (void const *arg);
uint8_t             usbd_msc0_bulk_buf [USBD_MSC0_BULK_BUF_SIZE] __attribute__((aligned(4)));
#endif

#ifdef  RTE_USB_Device_MSC_1
extern  void USBD_MSC1_Thread          (void const *arg);
uint8_t             usbd_msc1_bulk_buf [USBD_MSC1_BULK_BUF_SIZE] __attribute__((aligned(4)));
#endif

#ifdef  RTE_USB_Device_MSC_2
extern  void USBD_MSC2_Thread          (void const *arg);
uint8_t             usbd_msc2_bulk_buf [USBD_MSC2_BULK_BUF_SIZE] __attribute__((aligned(4)));
#endif

#ifdef  RTE_USB_Device_MSC_3
extern  void USBD_MSC3_Thread          (void const *arg);
uint8_t             usbd_msc3_bulk_buf [USBD_MSC3_BULK_BUF_SIZE] __attribute__((aligned(4)));
#endif

const   uint8_t     usbd_msc_num  =     USBD_MSC_NUM;
usbd_msc_data_t     usbd_msc_data      [USBD_MSC_NUM];
usbd_msc_t          usbd_msc           [USBD_MSC_NUM] = {
#ifdef  RTE_USB_Device_MSC_0
                                      {
                                        usbd_msc0_bulk_buf,
                                       &usbd_msc_data[0],
                                        USBD_MSC0_DEV,
                                        USBD_MSC0_IF0_NUM,
                                        USBD_MSC0_EP_BULK_IN,
                                        USBD_MSC0_EP_BULK_OUT,
                                        USBD_MSC0_BULK_BUF_SIZE,
                                      { USBD_MSC0_WMAXPACKETSIZE,
                                        USBD_MSC0_HS_WMAXPACKETSIZE },
                                        USBD_MSC0_INQUIRY_DATA,
                                      }
#endif
#ifdef  RTE_USB_Device_MSC_1
                                    , {
                                        usbd_msc1_bulk_buf,
                                       &usbd_msc_data[1],
                                        USBD_MSC1_DEV,
                                        USBD_MSC1_IF0_NUM,
                                        USBD_MSC1_EP_BULK_IN,
                                        USBD_MSC1_EP_BULK_OUT,
                                        USBD_MSC1_BULK_BUF_SIZE,
                                      { USBD_MSC1_WMAXPACKETSIZE,
                                        USBD_MSC1_HS_WMAXPACKETSIZE },
                                        USBD_MSC1_INQUIRY_DATA,
                                      }
#endif
#ifdef  RTE_USB_Device_MSC_2
                                    , {
                                        usbd_msc2_bulk_buf,
                                       &usbd_msc_data[2],
                                        USBD_MSC2_DEV,
                                        USBD_MSC2_IF0_NUM,
                                        USBD_MSC2_EP_BULK_IN,
                                        USBD_MSC2_EP_BULK_OUT,
                                        USBD_MSC2_BULK_BUF_SIZE,
                                      { USBD_MSC2_WMAXPACKETSIZE,
                                        USBD_MSC2_HS_WMAXPACKETSIZE },
                                        USBD_MSC2_INQUIRY_DATA,
                                      }
#endif
#ifdef  RTE_USB_Device_MSC_3
                                    , {
                                        usbd_msc3_bulk_buf,
                                       &usbd_msc_data[3],
                                        USBD_MSC3_DEV,
                                        USBD_MSC3_IF0_NUM,
                                        USBD_MSC3_EP_BULK_IN,
                                        USBD_MSC3_EP_BULK_OUT,
                                        USBD_MSC3_BULK_BUF_SIZE,
                                      { USBD_MSC3_WMAXPACKETSIZE,
                                        USBD_MSC3_HS_WMAXPACKETSIZE },
                                        USBD_MSC3_INQUIRY_DATA,
                                      }
#endif
};

const   usbd_msc_t * const usbd_msc_ptr[USBD_MSC_NUM] = {
#ifdef  RTE_USB_Device_MSC_0
       &usbd_msc[0]
#endif
#ifdef  RTE_USB_Device_MSC_1
     , &usbd_msc[1]
#endif
#ifdef  RTE_USB_Device_MSC_2
     , &usbd_msc[2]
#endif
#ifdef  RTE_USB_Device_MSC_3
     , &usbd_msc[3]
#endif
};

#endif


/*------------------------------------------------------------------------------
 *      USB Device Event Handler Functions
 *----------------------------------------------------------------------------*/

#if    (USBD_DEV_NUM)

const   uint8_t         usbd_ep_max_num = USBD_EP_NUM;
const   osThreadId     *usbd_ep_thread_id_ptr[USBD_DEV_NUM * USBD_EP_NUM] = {
#if    (USBD_DEV_NUM > 0)
        EP_POINTERS(0)
#endif
#if    (USBD_DEV_NUM > 1)
      , EP_POINTERS(1)
#endif
#if    (USBD_DEV_NUM > 2)
      , EP_POINTERS(2)
#endif
#if    (USBD_DEV_NUM > 3)
      , EP_POINTERS(3)
#endif
};

#if    (defined(RTE_USB_Device_0) || defined(RTE_USB_Device_1) || defined(RTE_USB_Device_2) || defined(RTE_USB_Device_3))
#ifdef  RTE_USB_Device_0
extern const osThreadDef_t os_thread_def_USBD0_Core_Thread;
#endif
#ifdef  RTE_USB_Device_1
extern const osThreadDef_t os_thread_def_USBD1_Core_Thread;
#endif
#ifdef  RTE_USB_Device_2
extern const osThreadDef_t os_thread_def_USBD2_Core_Thread;
#endif
#ifdef  RTE_USB_Device_3
extern const osThreadDef_t os_thread_def_USBD3_Core_Thread;
#endif
const osThreadDef_t * const usbd_core_thread_def_ptr[USBD_DEV_NUM] = {
#ifdef  RTE_USB_Device_0
        osThread(USBD0_Core_Thread)
#endif
#ifdef  RTE_USB_Device_1
      , osThread(USBD1_Core_Thread)
#endif
#ifdef  RTE_USB_Device_2
      , osThread(USBD2_Core_Thread)
#endif
#ifdef  RTE_USB_Device_3
      , osThread(USBD3_Core_Thread)
#endif
};

extern  void    USBD_SignalDeviceEvent   (uint8_t  device, uint32_t event);
extern  void    USBD_SignalEndpointEvent (uint8_t  device, uint8_t ep_addr, uint32_t event);
#ifdef  RTE_USB_Device_0
        void    USBD0_SignalDeviceEvent  (uint32_t event)                    { USBD_SignalDeviceEvent  (0, event);            }
        void    USBD0_SignalEndpointEvent(uint8_t  ep_addr, uint32_t event)  { USBD_SignalEndpointEvent(0, ep_addr, event);   }
#endif
#ifdef  RTE_USB_Device_1
        void    USBD1_SignalDeviceEvent  (uint32_t event)                    { USBD_SignalDeviceEvent  (1, event);            }
        void    USBD1_SignalEndpointEvent(uint8_t  ep_addr, uint32_t event)  { USBD_SignalEndpointEvent(1, ep_addr, event);   }
#endif
#ifdef  RTE_USB_Device_2
        void    USBD2_SignalDeviceEvent  (uint32_t event)                    { USBD_SignalDeviceEvent  (2, event);            }
        void    USBD2_SignalEndpointEvent(uint8_t  ep_addr, uint32_t event)  { USBD_SignalEndpointEvent(2, ep_addr, event);   }
#endif
#ifdef  RTE_USB_Device_3
        void    USBD3_SignalDeviceEvent  (uint32_t event)                    { USBD_SignalDeviceEvent  (3, event);            }
        void    USBD3_SignalEndpointEvent(uint8_t  ep_addr, uint32_t event)  { USBD_SignalEndpointEvent(3, ep_addr, event);   }
#endif

        ARM_USBD_SignalDeviceEvent_t const usbd_cb_device_event_ptr[USBD_DEV_NUM]   = {
#if    (USBD_DEV_NUM > 0)
        USBD0_SignalDeviceEvent
#endif
#if    (USBD_DEV_NUM > 1)
      , USBD1_SignalDeviceEvent
#endif
#if    (USBD_DEV_NUM > 2)
      , USBD2_SignalDeviceEvent
#endif
#if    (USBD_DEV_NUM > 3)
      , USBD3_SignalDeviceEvent
#endif
};

        ARM_USBD_SignalEndpointEvent_t const usbd_cb_endpoint_event_ptr[USBD_DEV_NUM] = {
#if    (USBD_DEV_NUM > 0)
        USBD0_SignalEndpointEvent
#endif
#if    (USBD_DEV_NUM > 1)
      , USBD1_SignalEndpointEvent
#endif
#if    (USBD_DEV_NUM > 2)
      , USBD2_SignalEndpointEvent
#endif
#if    (USBD_DEV_NUM > 3)
      , USBD3_SignalEndpointEvent
#endif
};

ARM_DRIVER_VERSION    usbd_drv_version [USBD_DEV_NUM] = { 0 };
ARM_USBD_CAPABILITIES usbd_capabilities[USBD_DEV_NUM] = { 0 };
#endif

#if    (USBD_CUSTOM_CLASS_NUM == 0)
__weak  usbdRequestStatus USBD_Class_Endpoint0_SetupPacketReceived        (uint8_t device)                                                    { return usbdRequestNotProcessed; }
__weak  void              USBD_Class_Endpoint0_SetupPacketProcessed       (uint8_t device)                                                    {                                 }
__weak  usbdRequestStatus USBD_Class_Endpoint0_OutDataReceived            (uint8_t device)                                                    { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_Class_Endpoint0_InDataSent                 (uint8_t device)                                                    { return usbdRequestNotProcessed; }
#else
extern  usbStatus         USBD_CustomClass_ClassInitialize                (uint8_t instance);
extern  usbStatus         USBD_CustomClass_ClassUninitialize              (uint8_t instance);

__weak  void              USBD_CustomClass0_Initialize                    (void)                                                              {};
__weak  void              USBD_CustomClass0_Uninitialize                  (void)                                                              {};
__weak  void              USBD_CustomClass0_EventReset                    (void)                                                              {};
__weak  void              USBD_CustomClass0_EventEndpointStart            (uint8_t ep_addr)                                                   {};
__weak  void              USBD_CustomClass0_EventEndpointStop             (uint8_t ep_addr)                                                   {};
__weak  usbdRequestStatus USBD_CustomClass0_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass0_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_CustomClass0_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_CustomClass0_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass0_Endpoint1_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint2_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint3_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint4_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint5_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint6_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint7_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint8_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint9_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint10_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint11_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint12_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint13_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint14_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass0_Endpoint15_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
#ifdef  RTE_USB_Device_CustomClass_1
__weak  void              USBD_CustomClass1_Initialize                    (void)                                                              {};
__weak  void              USBD_CustomClass1_Uninitialize                  (void)                                                              {};
__weak  void              USBD_CustomClass1_EventReset                    (void)                                                              {};
__weak  void              USBD_CustomClass1_EventEndpointStart            (uint8_t ep_addr)                                                   {};
__weak  void              USBD_CustomClass1_EventEndpointStop             (uint8_t ep_addr)                                                   {};
__weak  usbdRequestStatus USBD_CustomClass1_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass1_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_CustomClass1_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_CustomClass1_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass1_Endpoint1_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint2_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint3_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint4_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint5_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint6_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint7_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint8_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint9_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint10_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint11_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint12_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint13_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint14_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass1_Endpoint15_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
#endif
#ifdef  RTE_USB_Device_CustomClass_2
__weak  void              USBD_CustomClass2_Initialize                    (void)                                                              {};
__weak  void              USBD_CustomClass2_Uninitialize                  (void)                                                              {};
__weak  void              USBD_CustomClass2_EventReset                    (void)                                                              {};
__weak  void              USBD_CustomClass2_EventEndpointStart            (uint8_t ep_addr)                                                   {};
__weak  void              USBD_CustomClass2_EventEndpointStop             (uint8_t ep_addr)                                                   {};
__weak  usbdRequestStatus USBD_CustomClass2_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass2_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_CustomClass2_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_CustomClass2_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass2_Endpoint1_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint2_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint3_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint4_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint5_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint6_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint7_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint8_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint9_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint10_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint11_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint12_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint13_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint14_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass2_Endpoint15_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
#endif
#ifdef  RTE_USB_Device_CustomClass_3
__weak  void              USBD_CustomClass3_Initialize                    (void)                                                              {};
__weak  void              USBD_CustomClass3_Uninitialize                  (void)                                                              {};
__weak  void              USBD_CustomClass3_EventReset                    (void)                                                              {};
__weak  void              USBD_CustomClass3_EventEndpointStart            (uint8_t ep_addr)                                                   {};
__weak  void              USBD_CustomClass3_EventEndpointStop             (uint8_t ep_addr)                                                   {};
__weak  usbdRequestStatus USBD_CustomClass3_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass3_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_CustomClass3_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_CustomClass3_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  void              USBD_CustomClass3_Endpoint1_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint2_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint3_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint4_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint5_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint6_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint7_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint8_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint9_Event               (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint10_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint11_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint12_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint13_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint14_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
__weak  void              USBD_CustomClass3_Endpoint15_Event              (uint32_t event)                                                    { osSignalWait(0, osWaitForever); };
#endif

        void (* const USBD_CustomClass_Initialize[USBD_CUSTOM_CLASS_NUM]) (void) =
      {
        USBD_CustomClass0_Initialize
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_Initialize
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_Initialize
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_Initialize
#endif
      };
        void (* const USBD_CustomClass_Uninitialize[USBD_CUSTOM_CLASS_NUM]) (void) =
      {
        USBD_CustomClass0_Uninitialize
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_Uninitialize
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_Uninitialize
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_Uninitialize
#endif
      };
        void (* const USBD_CustomClass_EventReset[USBD_CUSTOM_CLASS_NUM]) (void) =
      {
        USBD_CustomClass0_EventReset
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_EventReset
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_EventReset
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_EventReset
#endif
      };
        void (* const USBD_CustomClass_EventEndpointStart[USBD_CUSTOM_CLASS_NUM]) (uint8_t ep_addr) =
      {
        USBD_CustomClass0_EventEndpointStart
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_EventEndpointStart
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_EventEndpointStart
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_EventEndpointStart
#endif
      };
        void (* const USBD_CustomClass_EventEndpointStop[USBD_CUSTOM_CLASS_NUM]) (uint8_t ep_addr) =
      {
        USBD_CustomClass0_EventEndpointStop
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_EventEndpointStop
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_EventEndpointStop
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_EventEndpointStop
#endif
      };
        usbdRequestStatus (* const USBD_CustomClass_Endpoint0_SetupPacketReceived[USBD_CUSTOM_CLASS_NUM]) (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) =
      {
        USBD_CustomClass0_Endpoint0_SetupPacketReceived
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_Endpoint0_SetupPacketReceived
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_Endpoint0_SetupPacketReceived
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_Endpoint0_SetupPacketReceived
#endif
      };
        void (* const USBD_CustomClass_Endpoint0_SetupPacketProcessed[USBD_CUSTOM_CLASS_NUM]) (const USB_SETUP_PACKET *setup_packet) =
      {
        USBD_CustomClass0_Endpoint0_SetupPacketProcessed
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_Endpoint0_SetupPacketProcessed
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_Endpoint0_SetupPacketProcessed
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_Endpoint0_SetupPacketProcessed
#endif
      };
        usbdRequestStatus (* const USBD_CustomClass_Endpoint0_OutDataReceived[USBD_CUSTOM_CLASS_NUM]) (int32_t len) =
      {
        USBD_CustomClass0_Endpoint0_OutDataReceived
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_Endpoint0_OutDataReceived
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_Endpoint0_OutDataReceived
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_Endpoint0_OutDataReceived
#endif
      };
        usbdRequestStatus (* const USBD_CustomClass_Endpoint0_InDataSent[USBD_CUSTOM_CLASS_NUM]) (int32_t len) =
      {
        USBD_CustomClass0_Endpoint0_InDataSent
#ifdef  RTE_USB_Device_CustomClass_1
      , USBD_CustomClass1_Endpoint0_InDataSent
#endif
#ifdef  RTE_USB_Device_CustomClass_2
      , USBD_CustomClass2_Endpoint0_InDataSent
#endif
#ifdef  RTE_USB_Device_CustomClass_3
      , USBD_CustomClass3_Endpoint0_InDataSent
#endif
      };

#if    (USBD_EP_LAST_NUM >= 15)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event , USBD_CustomClass##n##_Endpoint10_Event, USBD_CustomClass##n##_Endpoint11_Event, USBD_CustomClass##n##_Endpoint12_Event, \
                                          USBD_CustomClass##n##_Endpoint13_Event, USBD_CustomClass##n##_Endpoint14_Event, USBD_CustomClass##n##_Endpoint15_Event
#elif  (USBD_EP_LAST_NUM == 14)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event , USBD_CustomClass##n##_Endpoint10_Event, USBD_CustomClass##n##_Endpoint11_Event, USBD_CustomClass##n##_Endpoint12_Event, \
                                          USBD_CustomClass##n##_Endpoint13_Event, USBD_CustomClass##n##_Endpoint14_Event
#elif  (USBD_EP_LAST_NUM == 13)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event , USBD_CustomClass##n##_Endpoint10_Event, USBD_CustomClass##n##_Endpoint11_Event, USBD_CustomClass##n##_Endpoint12_Event, \
                                          USBD_CustomClass##n##_Endpoint13_Event
#elif  (USBD_EP_LAST_NUM == 12)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event , USBD_CustomClass##n##_Endpoint10_Event, USBD_CustomClass##n##_Endpoint11_Event, USBD_CustomClass##n##_Endpoint12_Event
#elif  (USBD_EP_LAST_NUM == 11)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event , USBD_CustomClass##n##_Endpoint10_Event, USBD_CustomClass##n##_Endpoint11_Event
#elif  (USBD_EP_LAST_NUM == 10)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event , USBD_CustomClass##n##_Endpoint10_Event
#elif  (USBD_EP_LAST_NUM ==  9)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event,  \
                                          USBD_CustomClass##n##_Endpoint9_Event
#elif  (USBD_EP_LAST_NUM ==  8)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event , USBD_CustomClass##n##_Endpoint8_Event
#elif  (USBD_EP_LAST_NUM ==  7)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event , USBD_CustomClass##n##_Endpoint7_Event
#elif  (USBD_EP_LAST_NUM ==  6)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event , USBD_CustomClass##n##_Endpoint6_Event
#elif  (USBD_EP_LAST_NUM ==  5)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,  \
                                          USBD_CustomClass##n##_Endpoint5_Event
#elif  (USBD_EP_LAST_NUM ==  4)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event , USBD_CustomClass##n##_Endpoint4_Event,
#elif  (USBD_EP_LAST_NUM ==  3)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event , USBD_CustomClass##n##_Endpoint3_Event
#elif  (USBD_EP_LAST_NUM ==  2)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event , USBD_CustomClass##n##_Endpoint2_Event
#elif  (USBD_EP_LAST_NUM ==  1)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0, USBD_CustomClass##n##_Endpoint1_Event
#elif  (USBD_EP_LAST_NUM ==  0)
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)  0
#else
#define CUSTOM_CLASS_EP_EVENT_FUNC(n)
#endif

        void (* const USBD_Endpoint_Event[USBD_CUSTOM_CLASS_NUM * USBD_EP_NUM]) (uint32_t event) =
      {
        CUSTOM_CLASS_EP_EVENT_FUNC(0)
#ifdef  RTE_USB_Device_CustomClass_1
    ,   CUSTOM_CLASS_EP_EVENT_FUNC(1)
#endif
#ifdef  RTE_USB_Device_CustomClass_2
    ,   CUSTOM_CLASS_EP_EVENT_FUNC(2)
#endif
#ifdef  RTE_USB_Device_CustomClass_3
    ,   CUSTOM_CLASS_EP_EVENT_FUNC(3)
#endif
      };
#endif

#if    (USBD_ADC_NUM == 0)
        bool      USBD_Endpoint0_Setup_ADC_ReqToIF (uint8_t device)               { return false; }
        bool      USBD_Endpoint0_Out_ADC_ReqToIF   (uint8_t device)               { return false; }
        bool      USBD_Endpoint0_Setup_ADC_ReqToEP (uint8_t device)               { return false; }
        bool      USBD_Endpoint0_Out_ADC_ReqToEP   (uint8_t device)               { return false; }
#else
extern  bool      USBD_Endpoint0_Setup_ADC_ReqToIF (uint8_t device);
extern  bool      USBD_Endpoint0_Setup_ADC_ReqToEP (uint8_t device);
extern  bool      USBD_Endpoint0_Out_ADC_ReqToIF   (uint8_t device);
extern  bool      USBD_Endpoint0_Out_ADC_ReqToEP   (uint8_t device);
extern  usbStatus USBD_ADC_ClassInitialize         (uint8_t instance);
extern  usbStatus USBD_ADC_ClassUninitialize       (uint8_t instance);
extern  void      USBD_ADC_EventReset              (uint8_t instance);
extern  void      USBD_ADC_EventEndpointStart      (uint8_t instance, uint8_t ep_addr);
extern  void      USBD_ADC_EventEndpointStop       (uint8_t instance, uint8_t ep_addr);
__weak  void      USBD_ADC0_Initialize             (void)                         {};
__weak  void      USBD_ADC0_Uninitialize           (void)                         {};
__weak  void      USBD_ADC0_SpeakerStatusEvent     (bool active)                  {};
__weak  void      USBD_ADC0_SpeakerMuteEvent       (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC0_SpeakerVolumeEvent     (uint8_t ch, uint16_t cur)     {};
__weak  void      USBD_ADC0_MicrophoneStatusEvent  (bool active)                  {};
__weak  void      USBD_ADC0_MicrophoneMuteEvent    (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC0_MicrophoneVolumeEvent  (uint8_t ch, uint16_t cur)     {};
#ifdef  RTE_USB_Device_ADC_1
__weak  void      USBD_ADC1_Initialize             (void)                         {};
__weak  void      USBD_ADC1_Uninitialize           (void)                         {};
__weak  void      USBD_ADC1_SpeakerStatusEvent     (bool active)                  {};
__weak  void      USBD_ADC1_SpeakerMuteEvent       (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC1_SpeakerVolumeEvent     (uint8_t ch, uint16_t cur)     {};
__weak  void      USBD_ADC1_MicrophoneStatusEvent  (bool active)                  {};
__weak  void      USBD_ADC1_MicrophoneMuteEvent    (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC1_MicrophoneVolumeEvent  (uint8_t ch, uint16_t cur)     {};
#endif
#ifdef  RTE_USB_Device_ADC_2
__weak  void      USBD_ADC2_Initialize             (void)                         {};
__weak  void      USBD_ADC2_Uninitialize           (void)                         {};
__weak  void      USBD_ADC2_SpeakerStatusEvent     (bool active)                  {};
__weak  void      USBD_ADC2_SpeakerMuteEvent       (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC2_SpeakerVolumeEvent     (uint8_t ch, uint16_t cur)     {};
__weak  void      USBD_ADC2_MicrophoneStatusEvent  (bool active)                  {};
__weak  void      USBD_ADC2_MicrophoneMuteEvent    (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC2_MicrophoneVolumeEvent  (uint8_t ch, uint16_t cur)     {};
#endif
#ifdef  RTE_USB_Device_ADC_3
__weak  void      USBD_ADC3_Initialize             (void)                         {};
__weak  void      USBD_ADC3_Uninitialize           (void)                         {};
__weak  void      USBD_ADC3_SpeakerStatusEvent     (bool active)                  {};
__weak  void      USBD_ADC3_SpeakerMuteEvent       (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC3_SpeakerVolumeEvent     (uint8_t ch, uint16_t cur)     {};
__weak  void      USBD_ADC3_MicrophoneStatusEvent  (bool active)                  {};
__weak  void      USBD_ADC3_MicrophoneMuteEvent    (uint8_t ch, bool     cur)     {};
__weak  void      USBD_ADC3_MicrophoneVolumeEvent  (uint8_t ch, uint16_t cur)     {};
#endif
        void (* const USBD_ADC_Initialize[USBD_ADC_NUM]) (void) =
      {
        USBD_ADC0_Initialize
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_Initialize
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_Initialize
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_Initialize
#endif
      };
        void (* const USBD_ADC_Uninitialize[USBD_ADC_NUM]) (void) =
      {
        USBD_ADC0_Uninitialize
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_Uninitialize
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_Uninitialize
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_Uninitialize
#endif
      };
        void (* const USBD_ADC_SpeakerStatusEvent[USBD_ADC_NUM]) (bool active) =
      {
        USBD_ADC0_SpeakerStatusEvent
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_SpeakerStatusEvent
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_SpeakerStatusEvent
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_SpeakerStatusEvent
#endif
      };
        void (* const USBD_ADC_SpeakerMuteEvent[USBD_ADC_NUM]) (uint8_t ch, bool cur) =
      {
        USBD_ADC0_SpeakerMuteEvent
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_SpeakerMuteEvent
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_SpeakerMuteEvent
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_SpeakerMuteEvent
#endif
      };
        void (* const USBD_ADC_SpeakerVolumeEvent[USBD_ADC_NUM]) (uint8_t ch, uint16_t cur) =
      {
        USBD_ADC0_SpeakerVolumeEvent
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_SpeakerVolumeEvent
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_SpeakerVolumeEvent
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_SpeakerVolumeEvent
#endif
      };
        void (* const USBD_ADC_MicrophoneStatusEvent[USBD_ADC_NUM]) (bool active) =
      {
        USBD_ADC0_MicrophoneStatusEvent
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_MicrophoneStatusEvent
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_MicrophoneStatusEvent
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_MicrophoneStatusEvent
#endif
      };
        void (* const USBD_ADC_MicrophoneMuteEvent[USBD_ADC_NUM]) (uint8_t ch, bool cur) =
      {
        USBD_ADC0_MicrophoneMuteEvent
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_MicrophoneMuteEvent
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_MicrophoneMuteEvent
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_MicrophoneMuteEvent
#endif
      };
        void (* const USBD_ADC_MicrophoneVolumeEvent[USBD_ADC_NUM]) (uint8_t ch, uint16_t cur) =
      {
        USBD_ADC0_MicrophoneVolumeEvent
#ifdef  RTE_USB_Device_ADC_1
      , USBD_ADC1_MicrophoneVolumeEvent
#endif
#ifdef  RTE_USB_Device_ADC_2
      , USBD_ADC2_MicrophoneVolumeEvent
#endif
#ifdef  RTE_USB_Device_ADC_3
      , USBD_ADC3_MicrophoneVolumeEvent
#endif
      };
#endif

#if    (USBD_CDC_NUM == 0)
        bool      USBD_Endpoint0_Setup_CDC_ReqToIF (uint8_t device)               { return false; }
        bool      USBD_Endpoint0_Out_CDC_ReqToIF   (uint8_t device)               { return false; }
#else
extern  bool      USBD_Endpoint0_Setup_CDC_ReqToIF (uint8_t device);
extern  bool      USBD_Endpoint0_Out_CDC_ReqToIF   (uint8_t device);
extern  usbStatus USBD_CDC_ClassInitialize         (uint8_t instance);
extern  usbStatus USBD_CDC_ClassUninitialize       (uint8_t instance);
extern  void      USBD_CDC_EventReset              (uint8_t instance);
extern  void      USBD_CDC_EventEndpointStart      (uint8_t instance, uint8_t ep_addr);
__weak  void      USBD_CDC_EventEndpointStop       (uint8_t instance, uint8_t ep_addr);
__weak  void      USBD_CDC0_ACM_Initialize         (void)                         { };
__weak  void      USBD_CDC0_ACM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC0_ACM_Reset              (void)                         { };
__weak  bool      USBD_CDC0_ACM_SetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC0_ACM_GetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC0_ACM_SetControlLineState(uint16_t state)               { return false; };
__weak  void      USBD_CDC0_ACM_DataReceived       (uint32_t len)                 { };
__weak  void      USBD_CDC0_ACM_DataSent           (void)                         { };
__weak  void      USBD_CDC0_NCM_Initialize         (void)                         { };
__weak  void      USBD_CDC0_NCM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC0_NCM_Reset              (void)                         { };
__weak  void      USBD_CDC0_NCM_Start              (void)                         { };
__weak  void      USBD_CDC0_NCM_Stop               (void)                         { };
__weak  bool      USBD_CDC0_NCM_SetEthernetMulticastFilters             (const uint8_t *addr_list, uint16_t num_of_filters)                                   { return false; };
__weak  bool      USBD_CDC0_NCM_SetEthernetPowerManagementPatternFilter (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size) { return false; };
__weak  bool      USBD_CDC0_NCM_GetEthernetPowerManagementPatternFilter (uint16_t filter_number, uint16_t *pattern_active)                                    { return false; };
__weak  bool      USBD_CDC0_NCM_SetEthernetPacketFilter                 (uint16_t packet_filter_bitmap)                                                       { return false; };
__weak  bool      USBD_CDC0_NCM_GetEthernetStatistic                    (uint16_t feature_selector, uint32_t *data)                                           { return false; };
__weak  bool      USBD_CDC0_NCM_GetNtbParameters   (CDC_NCM_NTB_PARAM *ntb_params){ return false; };
__weak  bool      USBD_CDC0_NCM_GetNetAddress      (uint8_t *addr)                { return false; };
__weak  bool      USBD_CDC0_NCM_SetNetAddress      (const uint8_t *addr)          { return false; };
__weak  bool      USBD_CDC0_NCM_GetNtbFormat       (uint16_t *ntb_format)         { return false; };
__weak  bool      USBD_CDC0_NCM_SetNtbFormat       (uint16_t ntb_format)          { return false; };
__weak  bool      USBD_CDC0_NCM_GetNtbInputSize    (uint32_t *ntb_input_size)     { return false; };
__weak  bool      USBD_CDC0_NCM_SetNtbInputSize    (uint32_t ntb_input_size)      { return false; };
__weak  bool      USBD_CDC0_NCM_GetMaxDatagramSize (uint16_t *max_datagram_size)  { return false; };
__weak  bool      USBD_CDC0_NCM_SetMaxDatagramSize (uint16_t max_datagram_size)   { return false; };
__weak  bool      USBD_CDC0_NCM_GetCrcMode         (uint16_t *mode)               { return false; };
__weak  bool      USBD_CDC0_NCM_SetCrcMode         (uint16_t mode)                { return false; };
__weak  void      USBD_CDC0_NCM_NTB_IN_Sent        (void)                         { };
__weak  void      USBD_CDC0_NCM_NTB_OUT_Received   (void)                         { };
#ifdef  RTE_USB_Device_CDC_1
__weak  void      USBD_CDC1_ACM_Initialize         (void)                         { };
__weak  void      USBD_CDC1_ACM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC1_ACM_Reset              (void)                         { };
__weak  bool      USBD_CDC1_ACM_SetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC1_ACM_GetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC1_ACM_SetControlLineState(uint16_t state)               { return false; };
__weak  void      USBD_CDC1_ACM_DataReceived       (uint32_t len)                 { };
__weak  void      USBD_CDC1_ACM_DataSent           (void)                         { };
__weak  void      USBD_CDC1_NCM_Initialize         (void)                         { };
__weak  void      USBD_CDC1_NCM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC1_NCM_Reset              (void)                         { };
__weak  void      USBD_CDC1_NCM_Start              (void)                         { };
__weak  void      USBD_CDC1_NCM_Stop               (void)                         { };
__weak  bool      USBD_CDC1_NCM_SetEthernetMulticastFilters             (const uint8_t *addr_list, uint16_t num_of_filters)                                   { return false; };
__weak  bool      USBD_CDC1_NCM_SetEthernetPowerManagementPatternFilter (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size) { return false; };
__weak  bool      USBD_CDC1_NCM_GetEthernetPowerManagementPatternFilter (uint16_t filter_number, uint16_t *pattern_active)                                    { return false; };
__weak  bool      USBD_CDC1_NCM_SetEthernetPacketFilter                 (uint16_t packet_filter_bitmap)                                                       { return false; };
__weak  bool      USBD_CDC1_NCM_GetEthernetStatistic                    (uint16_t feature_selector, uint32_t *data)                                           { return false; };
__weak  bool      USBD_CDC1_NCM_GetNtbParameters   (CDC_NCM_NTB_PARAM *ntb_params){ return false; };
__weak  bool      USBD_CDC1_NCM_GetNetAddress      (uint8_t *addr)                { return false; };
__weak  bool      USBD_CDC1_NCM_SetNetAddress      (const uint8_t *addr)          { return false; };
__weak  bool      USBD_CDC1_NCM_GetNtbFormat       (uint16_t *ntb_format)         { return false; };
__weak  bool      USBD_CDC1_NCM_SetNtbFormat       (uint16_t ntb_format)          { return false; };
__weak  bool      USBD_CDC1_NCM_GetNtbInputSize    (uint32_t *ntb_input_size)     { return false; };
__weak  bool      USBD_CDC1_NCM_SetNtbInputSize    (uint32_t ntb_input_size)      { return false; };
__weak  bool      USBD_CDC1_NCM_GetMaxDatagramSize (uint16_t *max_datagram_size)  { return false; };
__weak  bool      USBD_CDC1_NCM_SetMaxDatagramSize (uint16_t max_datagram_size)   { return false; };
__weak  bool      USBD_CDC1_NCM_GetCrcMode         (uint16_t *mode)               { return false; };
__weak  bool      USBD_CDC1_NCM_SetCrcMode         (uint16_t mode)                { return false; };
__weak  void      USBD_CDC1_NCM_NTB_IN_Sent        (void)                         { };
__weak  void      USBD_CDC1_NCM_NTB_OUT_Received   (void)                         { };
#endif
#ifdef  RTE_USB_Device_CDC_2
__weak  void      USBD_CDC2_ACM_Initialize         (void)                         { };
__weak  void      USBD_CDC2_ACM_Uninitialize       (void)                         { };
__weak  bool      USBD_CDC2_ACM_Reset              (void)                         { return false; };
__weak  bool      USBD_CDC2_ACM_SetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC2_ACM_GetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC2_ACM_SetControlLineState(uint16_t state)               { return false; };
__weak  void      USBD_CDC2_ACM_DataReceived       (uint32_t len)                 { };
__weak  void      USBD_CDC2_ACM_DataSent           (void)                         { };
__weak  void      USBD_CDC2_NCM_Initialize         (void)                         { };
__weak  void      USBD_CDC2_NCM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC2_NCM_Reset              (void)                         { };
__weak  void      USBD_CDC2_NCM_Start              (void)                         { };
__weak  void      USBD_CDC2_NCM_Stop               (void)                         { };
__weak  bool      USBD_CDC2_NCM_SetEthernetMulticastFilters             (const uint8_t *addr_list, uint16_t num_of_filters)                                   { return false; };
__weak  bool      USBD_CDC2_NCM_SetEthernetPowerManagementPatternFilter (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size) { return false; };
__weak  bool      USBD_CDC2_NCM_GetEthernetPowerManagementPatternFilter (uint16_t filter_number, uint16_t *pattern_active)                                    { return false; };
__weak  bool      USBD_CDC2_NCM_SetEthernetPacketFilter                 (uint16_t packet_filter_bitmap)                                                       { return false; };
__weak  bool      USBD_CDC2_NCM_GetEthernetStatistic                    (uint16_t feature_selector, uint32_t *data)                                           { return false; };
__weak  bool      USBD_CDC2_NCM_GetNtbParameters   (CDC_NCM_NTB_PARAM *ntb_params){ return false; };
__weak  bool      USBD_CDC2_NCM_GetNetAddress      (uint8_t *addr)                { return false; };
__weak  bool      USBD_CDC2_NCM_SetNetAddress      (const uint8_t *addr)          { return false; };
__weak  bool      USBD_CDC2_NCM_GetNtbFormat       (uint16_t *ntb_format)         { return false; };
__weak  bool      USBD_CDC2_NCM_SetNtbFormat       (uint16_t ntb_format)          { return false; };
__weak  bool      USBD_CDC2_NCM_GetNtbInputSize    (uint32_t *ntb_input_size)     { return false; };
__weak  bool      USBD_CDC2_NCM_SetNtbInputSize    (uint32_t ntb_input_size)      { return false; };
__weak  bool      USBD_CDC2_NCM_GetMaxDatagramSize (uint16_t *max_datagram_size)  { return false; };
__weak  bool      USBD_CDC2_NCM_SetMaxDatagramSize (uint16_t max_datagram_size)   { return false; };
__weak  bool      USBD_CDC2_NCM_GetCrcMode         (uint16_t *mode)               { return false; };
__weak  bool      USBD_CDC2_NCM_SetCrcMode         (uint16_t mode)                { return false; };
__weak  void      USBD_CDC2_NCM_NTB_IN_Sent        (void)                         { };
__weak  void      USBD_CDC2_NCM_NTB_OUT_Received   (void)                         { };
#endif
#ifdef  RTE_USB_Device_CDC_3
__weak  void      USBD_CDC3_ACM_Initialize         (void)                         { };
__weak  void      USBD_CDC3_ACM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC3_ACM_Reset              (void)                         { };
__weak  bool      USBD_CDC3_ACM_SetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC3_ACM_GetLineCoding      (CDC_LINE_CODING *line_coding) { return false; };
__weak  bool      USBD_CDC3_ACM_SetControlLineState(uint16_t state)               { return false; };
__weak  void      USBD_CDC3_ACM_DataReceived       (uint32_t len)                 { };
__weak  void      USBD_CDC3_ACM_DataSent           (void)                         { };
__weak  void      USBD_CDC3_NCM_Initialize         (void)                         { };
__weak  void      USBD_CDC3_NCM_Uninitialize       (void)                         { };
__weak  void      USBD_CDC3_NCM_Reset              (void)                         { };
__weak  void      USBD_CDC3_NCM_Start              (void)                         { };
__weak  void      USBD_CDC3_NCM_Stop               (void)                         { };
__weak  bool      USBD_CDC3_NCM_SetEthernetMulticastFilters             (const uint8_t *addr_list, uint16_t num_of_filters)                                   { return false; };
__weak  bool      USBD_CDC3_NCM_SetEthernetPowerManagementPatternFilter (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size) { return false; };
__weak  bool      USBD_CDC3_NCM_GetEthernetPowerManagementPatternFilter (uint16_t filter_number, uint16_t *pattern_active)                                    { return false; };
__weak  bool      USBD_CDC3_NCM_SetEthernetPacketFilter                 (uint16_t packet_filter_bitmap)                                                       { return false; };
__weak  bool      USBD_CDC3_NCM_GetEthernetStatistic                    (uint16_t feature_selector, uint32_t *data)                                           { return false; };
__weak  bool      USBD_CDC3_NCM_GetNtbParameters   (CDC_NCM_NTB_PARAM *ntb_params){ return false; };
__weak  bool      USBD_CDC3_NCM_GetNetAddress      (uint8_t *addr)                { return false; };
__weak  bool      USBD_CDC3_NCM_SetNetAddress      (const uint8_t *addr)          { return false; };
__weak  bool      USBD_CDC3_NCM_GetNtbFormat       (uint16_t *ntb_format)         { return false; };
__weak  bool      USBD_CDC3_NCM_SetNtbFormat       (uint16_t ntb_format)          { return false; };
__weak  bool      USBD_CDC3_NCM_GetNtbInputSize    (uint32_t *ntb_input_size)     { return false; };
__weak  bool      USBD_CDC3_NCM_SetNtbInputSize    (uint32_t ntb_input_size)      { return false; };
__weak  bool      USBD_CDC3_NCM_GetMaxDatagramSize (uint16_t *max_datagram_size)  { return false; };
__weak  bool      USBD_CDC3_NCM_SetMaxDatagramSize (uint16_t max_datagram_size)   { return false; };
__weak  bool      USBD_CDC3_NCM_GetCrcMode         (uint16_t *mode)               { return false; };
__weak  bool      USBD_CDC3_NCM_SetCrcMode         (uint16_t mode)                { return false; };
__weak  void      USBD_CDC3_NCM_NTB_IN_Sent        (void)                         { };
__weak  void      USBD_CDC3_NCM_NTB_OUT_Received   (void)                         { };
#endif
        void (* const USBD_CDC_ACM_Initialize[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_ACM_Initialize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_Initialize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_Initialize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_Initialize
#endif
      };
        void (* const USBD_CDC_ACM_Uninitialize[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_ACM_Uninitialize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_Uninitialize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_Uninitialize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_Uninitialize
#endif
      };
        void (* const USBD_CDC_ACM_Reset[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_ACM_Reset
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_Reset
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_Reset
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_Reset
#endif
      };
        bool (* const USBD_CDC_ACM_SetLineCoding[USBD_CDC_NUM]) (CDC_LINE_CODING *line_coding) =
      {
        USBD_CDC0_ACM_SetLineCoding
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_SetLineCoding
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_SetLineCoding
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_SetLineCoding
#endif
      };
        bool (* const USBD_CDC_ACM_GetLineCoding[USBD_CDC_NUM]) (CDC_LINE_CODING *line_coding) =
      {
        USBD_CDC0_ACM_GetLineCoding
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_GetLineCoding
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_GetLineCoding
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_GetLineCoding
#endif
      };
        bool (* const USBD_CDC_ACM_SetControlLineState[USBD_CDC_NUM]) (uint16_t ctrl_bmp) =
      {
        USBD_CDC0_ACM_SetControlLineState
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_SetControlLineState
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_SetControlLineState
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_SetControlLineState
#endif
      };
        void (* const USBD_CDC_ACM_DataReceived[USBD_CDC_NUM]) (uint32_t len) =
      {
        USBD_CDC0_ACM_DataReceived
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_DataReceived
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_DataReceived
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_DataReceived
#endif
      };
        void (* const USBD_CDC_ACM_DataSent[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_ACM_DataSent
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_ACM_DataSent
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_ACM_DataSent
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_ACM_DataSent
#endif
      };
        void (* const USBD_CDC_NCM_Initialize[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_Initialize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_Initialize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_Initialize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_Initialize
#endif
      };
        void (* const USBD_CDC_NCM_Uninitialize[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_Uninitialize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_Uninitialize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_Uninitialize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_Uninitialize
#endif
      };
        void (* const USBD_CDC_NCM_Reset[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_Reset
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_Reset
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_Reset
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_Reset
#endif
      };
        void (* const USBD_CDC_NCM_Start[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_Start
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_Start
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_Start
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_Start
#endif
      };
        void (* const USBD_CDC_NCM_Stop[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_Stop
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_Stop
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_Stop
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_Stop
#endif
      };
        bool (* const USBD_CDC_NCM_SetEthernetMulticastFilters[USBD_CDC_NUM]) (const uint8_t *addr_list, uint16_t num_of_filters) =
      {
        USBD_CDC0_NCM_SetEthernetMulticastFilters
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetEthernetMulticastFilters
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetEthernetMulticastFilters
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetEthernetMulticastFilters
#endif
      };
        bool (* const USBD_CDC_NCM_SetEthernetPowerManagementPatternFilter[USBD_CDC_NUM]) (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size) =
      {
        USBD_CDC0_NCM_SetEthernetPowerManagementPatternFilter
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetEthernetPowerManagementPatternFilter
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetEthernetPowerManagementPatternFilter
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetEthernetPowerManagementPatternFilter
#endif
      };
        bool (* const USBD_CDC_NCM_GetEthernetPowerManagementPatternFilter[USBD_CDC_NUM]) (uint16_t filter_number, uint16_t *pattern_active) =
      {
        USBD_CDC0_NCM_GetEthernetPowerManagementPatternFilter
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetEthernetPowerManagementPatternFilter
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetEthernetPowerManagementPatternFilter
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetEthernetPowerManagementPatternFilter
#endif
      };
        bool (* const USBD_CDC_NCM_SetEthernetPacketFilter[USBD_CDC_NUM]) (uint16_t packet_filter_bitmap) =
      {
        USBD_CDC0_NCM_SetEthernetPacketFilter
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetEthernetPacketFilter
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetEthernetPacketFilter
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetEthernetPacketFilter
#endif
      };
        bool (* const USBD_CDC_NCM_GetEthernetStatistic[USBD_CDC_NUM]) (uint16_t feature_selector, uint32_t *data) =
      {
        USBD_CDC0_NCM_GetEthernetStatistic
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetEthernetStatistic
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetEthernetStatistic
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetEthernetStatistic
#endif
      };
        bool (* const USBD_CDC_NCM_GetNtbParameters[USBD_CDC_NUM]) (CDC_NCM_NTB_PARAM *ntb_params) =
      {
        USBD_CDC0_NCM_GetNtbParameters
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetNtbParameters
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetNtbParameters
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetNtbParameters
#endif
      };
        bool (* const USBD_CDC_NCM_GetNetAddress[USBD_CDC_NUM]) (uint8_t *addr) =
      {
        USBD_CDC0_NCM_GetNetAddress
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetNetAddress
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetNetAddress
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetNetAddress
#endif
      };
        bool (* const USBD_CDC_NCM_SetNetAddress[USBD_CDC_NUM]) (const uint8_t *addr) =
      {
        USBD_CDC0_NCM_SetNetAddress
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetNetAddress
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetNetAddress
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetNetAddress
#endif
      };
        bool (* const USBD_CDC_NCM_GetNtbFormat[USBD_CDC_NUM]) (uint16_t *ntb_format) =
      {
        USBD_CDC0_NCM_GetNtbFormat
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetNtbFormat
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetNtbFormat
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetNtbFormat
#endif
      };
        bool (* const USBD_CDC_NCM_SetNtbFormat[USBD_CDC_NUM]) (uint16_t ntb_format) =
      {
        USBD_CDC0_NCM_SetNtbFormat
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetNtbFormat
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetNtbFormat
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetNtbFormat
#endif
      };
        bool (* const USBD_CDC_NCM_GetNtbInputSize[USBD_CDC_NUM]) (uint32_t *ntb_input_size) =
      {
        USBD_CDC0_NCM_GetNtbInputSize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetNtbInputSize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetNtbInputSize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetNtbInputSize
#endif
      };
        bool (* const USBD_CDC_NCM_SetNtbInputSize[USBD_CDC_NUM]) (uint32_t ntb_input_size) =
      {
        USBD_CDC0_NCM_SetNtbInputSize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetNtbInputSize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetNtbInputSize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetNtbInputSize
#endif
      };
        bool (* const USBD_CDC_NCM_GetMaxDatagramSize[USBD_CDC_NUM]) (uint16_t *max_datagram_size) =
      {
        USBD_CDC0_NCM_GetMaxDatagramSize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetMaxDatagramSize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetMaxDatagramSize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetMaxDatagramSize
#endif
      };
        bool (* const USBD_CDC_NCM_SetMaxDatagramSize[USBD_CDC_NUM]) (uint16_t max_datagram_size) =
      {
        USBD_CDC0_NCM_SetMaxDatagramSize
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetMaxDatagramSize
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetMaxDatagramSize
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetMaxDatagramSize
#endif
      };
        bool (* const USBD_CDC_NCM_GetCrcMode[USBD_CDC_NUM]) (uint16_t *mode) =
      {
        USBD_CDC0_NCM_GetCrcMode
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_GetCrcMode
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_GetCrcMode
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_GetCrcMode
#endif
      };
        bool (* const USBD_CDC_NCM_SetCrcMode[USBD_CDC_NUM]) (uint16_t mode) =
      {
        USBD_CDC0_NCM_SetCrcMode
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_SetCrcMode
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_SetCrcMode
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_SetCrcMode
#endif
      };
        void (* const USBD_CDC_NCM_NTB_IN_Sent[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_NTB_IN_Sent
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_NTB_IN_Sent
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_NTB_IN_Sent
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_NTB_IN_Sent
#endif
      };
        void (* const USBD_CDC_NCM_NTB_OUT_Received[USBD_CDC_NUM]) (void) =
      {
        USBD_CDC0_NCM_NTB_OUT_Received
#ifdef  RTE_USB_Device_CDC_1
      , USBD_CDC1_NCM_NTB_OUT_Received
#endif
#ifdef  RTE_USB_Device_CDC_2
      , USBD_CDC2_NCM_NTB_OUT_Received
#endif
#ifdef  RTE_USB_Device_CDC_3
      , USBD_CDC3_NCM_NTB_OUT_Received
#endif
      };
#endif

#if    (USBD_HID_NUM == 0)
        bool      USBD_Endpoint0_ReqGetDescriptor_HID (uint8_t device, uint8_t **pD, uint32_t *len)                               { return false; }
        bool      USBD_Endpoint0_Setup_HID_ReqToIF    (uint8_t device)                                                            { return false; }
        bool      USBD_Endpoint0_Out_HID_ReqToIF      (uint8_t device)                                                            { return false; }
#else
extern  usbStatus USBD_HID_ClassInitialize            (uint8_t instance);
extern  usbStatus USBD_HID_ClassUninitialize          (uint8_t instance);
extern  void      USBD_HID_EventReset                 (uint8_t instance);
extern  void      USBD_HID_EventSetConfiguration      (uint8_t instance);
extern  void      USBD_HID_EventEndpointStart         (uint8_t instance, uint8_t ep_addr);
__weak  void      USBD_HID0_Initialize                (void)                                                                      {};
__weak  void      USBD_HID0_Uninitialize              (void)                                                                      {};
__weak  int32_t   USBD_HID0_GetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid,       uint8_t *buf)              { return -1;    };
__weak  bool      USBD_HID0_SetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid, const uint8_t *buf, int32_t len) { return false; };
__weak  int8_t    USBD_HID0_GetProtocol               (void)                                                                      { return -1;    };
__weak  bool      USBD_HID0_SetProtocol               (uint8_t protocol)                                                          { return false; };
#ifdef  RTE_USB_Device_HID_1
__weak  void      USBD_HID1_Initialize                (void)                                                                      {};
__weak  void      USBD_HID1_Uninitialize              (void)                                                                      {};
__weak  int32_t   USBD_HID1_GetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid,       uint8_t *buf)              { return -1;    };
__weak  bool      USBD_HID1_SetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid, const uint8_t *buf, int32_t len) { return false; };
__weak  int8_t    USBD_HID1_GetProtocol               (void)                                                                      { return -1;    };
__weak  bool      USBD_HID1_SetProtocol               (uint8_t protocol)                                                          { return false; };
#endif
#ifdef  RTE_USB_Device_HID_2
__weak  void      USBD_HID2_Initialize                (void)                                                                      {};
__weak  void      USBD_HID2_Uninitialize              (void)                                                                      {};
__weak  int32_t   USBD_HID2_GetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid,       uint8_t *buf)              { return -1;    };
__weak  bool      USBD_HID2_SetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid, const uint8_t *buf, int32_t len) { return false; };
__weak  int8_t    USBD_HID2_GetProtocol               (void)                                                                      { return -1;    };
__weak  bool      USBD_HID2_SetProtocol               (uint8_t protocol)                                                          { return false; };
#endif
#ifdef  RTE_USB_Device_HID_3
__weak  void      USBD_HID3_Initialize                (void)                                                                      {};
__weak  void      USBD_HID3_Uninitialize              (void)                                                                      {};
__weak  int32_t   USBD_HID3_GetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid,       uint8_t *buf)              { return -1;    };
__weak  bool      USBD_HID3_SetReport                 (uint8_t rtype, uint8_t  req, uint8_t rid, const uint8_t *buf, int32_t len) { return false; };
__weak  int8_t    USBD_HID3_GetProtocol               (void)                                                                      { return -1;    };
__weak  bool      USBD_HID3_SetProtocol               (uint8_t protocol)                                                          { return false; };
#endif
        void (* const USBD_HID_Initialize[USBD_HID_NUM])  (void) =
      {
        USBD_HID0_Initialize
#ifdef  RTE_USB_Device_HID_1
      , USBD_HID1_Initialize
#endif
#ifdef  RTE_USB_Device_HID_2
      , USBD_HID2_Initialize
#endif
#ifdef  RTE_USB_Device_HID_3
      , USBD_HID3_Initialize
#endif
      };
        void (* const USBD_HID_Uninitialize[USBD_HID_NUM]) (void) =
      {
        USBD_HID0_Uninitialize
#ifdef  RTE_USB_Device_HID_1
      , USBD_HID1_Uninitialize
#endif
#ifdef  RTE_USB_Device_HID_2
      , USBD_HID2_Uninitialize
#endif
#ifdef  RTE_USB_Device_HID_3
      , USBD_HID3_Uninitialize
#endif
      };
        int32_t  (* const USBD_HID_GetReport[USBD_HID_NUM]) (uint8_t rtype, uint8_t req, uint8_t  rid, uint8_t *buf) =
      {
        USBD_HID0_GetReport
#ifdef  RTE_USB_Device_HID_1
      , USBD_HID1_GetReport
#endif
#ifdef  RTE_USB_Device_HID_2
      , USBD_HID2_GetReport
#endif
#ifdef  RTE_USB_Device_HID_3
      , USBD_HID3_GetReport
#endif
      };
        bool (* const USBD_HID_SetReport[USBD_HID_NUM]) (uint8_t rtype, uint8_t req, uint8_t rid, const uint8_t *buf, int32_t len) =
      {
        USBD_HID0_SetReport
#ifdef  RTE_USB_Device_HID_1
      , USBD_HID1_SetReport
#endif
#ifdef  RTE_USB_Device_HID_2
      , USBD_HID2_SetReport
#endif
#ifdef  RTE_USB_Device_HID_3
      , USBD_HID3_SetReport
#endif
      };
        int8_t (* const USBD_HID_GetProtocol[USBD_HID_NUM]) (void) =
      {
        USBD_HID0_GetProtocol
#ifdef  RTE_USB_Device_HID_1
      , USBD_HID1_GetProtocol
#endif
#ifdef  RTE_USB_Device_HID_2
      , USBD_HID2_GetProtocol
#endif
#ifdef  RTE_USB_Device_HID_3
      , USBD_HID3_GetProtocol
#endif
      };
        bool (* const USBD_HID_SetProtocol[USBD_HID_NUM]) (uint8_t protocol) =
      {
        USBD_HID0_SetProtocol
#ifdef  RTE_USB_Device_HID_1
      , USBD_HID1_SetProtocol
#endif
#ifdef  RTE_USB_Device_HID_2
      , USBD_HID2_SetProtocol
#endif
#ifdef  RTE_USB_Device_HID_3
      , USBD_HID3_SetProtocol
#endif
      };
#endif

#if    (USBD_MSC_NUM == 0)
        bool      USBD_Endpoint0_Setup_MSC_ReqToIF        (uint8_t device)                                 { return false; }
#else
extern  usbStatus USBD_MSC_ClassInitialize                (uint8_t instance);
extern  usbStatus USBD_MSC_ClassUninitialize              (uint8_t instance);
extern  void      USBD_MSC_EventReset                     (uint8_t instance);
extern  void      USBD_MSC_EventEndpointClearFeatureStall (uint8_t instance, uint8_t ep_addr);
extern  void      USBD_MSC_EventEndpointStart             (uint8_t instance, uint8_t ep_addr);
__weak  void      USBD_MSC0_Initialize                    (void)                                           {};
__weak  void      USBD_MSC0_Uninitialize                  (void)                                           {};
__weak  bool      USBD_MSC0_GetCacheInfo                  (uint32_t *buffer, uint32_t *size)               { 
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[0]->data_ptr;
  *buffer = (uint32_t)msc_data_ptr->block_buf;
  *size   = msc_data_ptr->block_group * 512U;
  return true;
}
__weak  bool      USBD_MSC0_GetMediaCapacity              (uint32_t *block_count, uint32_t *block_size)    {
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[0]->data_ptr;
  *block_count = msc_data_ptr->block_count;
  *block_size  = 512U;
  return true;
}
__weak  bool      USBD_MSC0_Read                          (uint32_t lba, uint32_t cnt, uint8_t *buf)       { return false; };
__weak  bool      USBD_MSC0_Write                         (uint32_t lba, uint32_t cnt, const uint8_t *buf) { return false; };
__weak  bool      USBD_MSC0_StartStop                     (bool start)                                     { return false; };
__weak  uint32_t  USBD_MSC0_CheckMedia                    (void)                                           { return USBD_MSC_MEDIA_READY; };
#ifdef  RTE_USB_Device_MSC_1
__weak  void      USBD_MSC1_Initialize                    (void)                                           {};
__weak  void      USBD_MSC1_Uninitialize                  (void)                                           {};
__weak  bool      USBD_MSC1_GetCacheInfo                  (uint32_t *buffer, uint32_t *size)               { 
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[1]->data_ptr;
  *buffer = (uint32_t)msc_data_ptr->block_buf;
  *size   = msc_data_ptr->block_group * 512U;
  return true;
}
__weak  bool      USBD_MSC1_GetMediaCapacity              (uint32_t *block_count, uint32_t *block_size)    {
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[1]->data_ptr;
  *block_count = msc_data_ptr->block_count;
  *block_size  = 512U;
  return true;
}
__weak  bool      USBD_MSC1_Read                          (uint32_t lba, uint32_t cnt, uint8_t *buf)       { return false; };
__weak  bool      USBD_MSC1_Write                         (uint32_t lba, uint32_t cnt, const uint8_t *buf) { return false; };
__weak  bool      USBD_MSC1_StartStop                     (bool start)                                     { return false; };
__weak  uint32_t  USBD_MSC1_CheckMedia                    (void)                                           { return USBD_MSC_MEDIA_READY; };
#endif
#ifdef  RTE_USB_Device_MSC_2
__weak  void      USBD_MSC2_Initialize                    (void)                                           {};
__weak  void      USBD_MSC2_Uninitialize                  (void)                                           {};
__weak  bool      USBD_MSC2_GetCacheInfo                  (uint32_t *buffer, uint32_t *size)               { 
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[2]->data_ptr;
  *buffer = (uint32_t)msc_data_ptr->block_buf;
  *size   = msc_data_ptr->block_group * 512U;
  return true;
}
__weak  bool      USBD_MSC2_GetMediaCapacity              (uint32_t *block_count, uint32_t *block_size)    {
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[2]->data_ptr;
  *block_count = msc_data_ptr->block_count;
  *block_size  = 512U;
  return true;
}
__weak  bool      USBD_MSC2_Read                          (uint32_t lba, uint32_t cnt, uint8_t *buf)       { return false; };
__weak  bool      USBD_MSC2_Write                         (uint32_t lba, uint32_t cnt, const uint8_t *buf) { return false; };
__weak  bool      USBD_MSC2_StartStop                     (bool start)                                     { return false; };
__weak  uint32_t  USBD_MSC2_CheckMedia                    (void)                                           { return USBD_MSC_MEDIA_READY; };
#endif
#ifdef  RTE_USB_Device_MSC_3
__weak  void      USBD_MSC3_Initialize                    (void)                                           {};
__weak  void      USBD_MSC3_Uninitialize                  (void)                                           {};
__weak  bool      USBD_MSC3_GetCacheInfo                  (uint32_t *buffer, uint32_t *size)               { 
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[3]->data_ptr;
  *buffer = (uint32_t)msc_data_ptr->block_buf;
  *size   = msc_data_ptr->block_group * 512U;
  return true;
}
__weak  bool      USBD_MSC3_GetMediaCapacity              (uint32_t *block_count, uint32_t *block_size)    {
  // Legacy support (return already selected cache previously set from Initialize function)
  usbd_msc_data_t *msc_data_ptr = usbd_msc_ptr[3]->data_ptr;
  *block_count = msc_data_ptr->block_count;
  *block_size  = 512U;
  return true;
}
__weak  bool      USBD_MSC3_Read                          (uint32_t lba, uint32_t cnt, uint8_t *buf)       { return false; };
__weak  bool      USBD_MSC3_Write                         (uint32_t lba, uint32_t cnt, const uint8_t *buf) { return false; };
__weak  bool      USBD_MSC3_StartStop                     (bool start)                                     { return false; };
__weak  uint32_t  USBD_MSC3_CheckMedia                    (void)                                           { return USBD_MSC_MEDIA_READY; };
#endif
        void (* const USBD_MSC_Initialize[USBD_MSC_NUM])  (void) =
      {
        USBD_MSC0_Initialize
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_Initialize
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_Initialize
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_Initialize
#endif
      };
        void (* const USBD_MSC_Uninitialize[USBD_MSC_NUM]) (void) =
      {
        USBD_MSC0_Uninitialize
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_Uninitialize
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_Uninitialize
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_Uninitialize
#endif
      };
        bool (* const USBD_MSC_GetCacheInfo[USBD_MSC_NUM]) (uint32_t *buffer, uint32_t *size) =
      {
        USBD_MSC0_GetCacheInfo
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_GetCacheInfo
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_GetCacheInfo
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_GetCacheInfo
#endif
      };
        bool (* const USBD_MSC_GetMediaCapacity[USBD_MSC_NUM]) (uint32_t *block_count, uint32_t *block_size) =
      {
        USBD_MSC0_GetMediaCapacity
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_GetMediaCapacity
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_GetMediaCapacity
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_GetMediaCapacity
#endif
      };
        bool (* const USBD_MSC_Read[USBD_MSC_NUM]) (uint32_t lba, uint32_t cnt, uint8_t *buf) =
      {
        USBD_MSC0_Read
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_Read
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_Read
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_Read
#endif
      };
        bool (* const USBD_MSC_Write[USBD_MSC_NUM]) (uint32_t lba, uint32_t cnt, const uint8_t *buf) =
      {
        USBD_MSC0_Write
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_Write
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_Write
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_Write
#endif
      };
        bool (* const USBD_MSC_StartStop[USBD_MSC_NUM]) (bool start) =
      {
        USBD_MSC0_StartStop
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_StartStop
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_StartStop
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_StartStop
#endif
      };
        uint32_t (* const USBD_MSC_CheckMedia[USBD_MSC_NUM]) (void) =
      {
        USBD_MSC0_CheckMedia
#ifdef  RTE_USB_Device_MSC_1
      , USBD_MSC1_CheckMedia
#endif
#ifdef  RTE_USB_Device_MSC_2
      , USBD_MSC2_CheckMedia
#endif
#ifdef  RTE_USB_Device_MSC_3
      , USBD_MSC3_CheckMedia
#endif
      };
#endif

__weak  void              USBD_Device0_Initialize                    (void)                                                              {};
__weak  void              USBD_Device0_Uninitialize                  (void)                                                              {};
__weak  void              USBD_Device0_EventReset                    (void)                                                              {};
__weak  usbdRequestStatus USBD_Device0_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_Device0_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_Device0_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_Device0_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
#ifdef  RTE_USB_Device_1
__weak  void              USBD_Device1_Initialize                    (void)                                                              {};
__weak  void              USBD_Device1_Uninitialize                  (void)                                                              {};
__weak  void              USBD_Device1_EventReset                    (void)                                                              {};
__weak  usbdRequestStatus USBD_Device1_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_Device1_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_Device1_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_Device1_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
#endif
#ifdef  RTE_USB_Device_2
__weak  void              USBD_Device2_Initialize                    (void)                                                              {};
__weak  void              USBD_Device2_Uninitialize                  (void)                                                              {};
__weak  void              USBD_Device2_EventReset                    (void)                                                              {};
__weak  usbdRequestStatus USBD_Device2_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_Device2_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_Device2_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_Device2_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
#endif
#ifdef  RTE_USB_Device_3
__weak  void              USBD_Device3_Initialize                    (void)                                                              {};
__weak  void              USBD_Device3_Uninitialize                  (void)                                                              {};
__weak  void              USBD_Device3_EventReset                    (void)                                                              {};
__weak  usbdRequestStatus USBD_Device3_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) { return usbdRequestNotProcessed; }
__weak  void              USBD_Device3_Endpoint0_SetupPacketProcessed(const USB_SETUP_PACKET *setup_packet)                              {                                 }
__weak  usbdRequestStatus USBD_Device3_Endpoint0_OutDataReceived     (int32_t len)                                                       { return usbdRequestNotProcessed; }
__weak  usbdRequestStatus USBD_Device3_Endpoint0_InDataSent          (int32_t len)                                                       { return usbdRequestNotProcessed; }
#endif

        void (* const USBD_Device_Initialize[USBD_DEV_NUM]) (void) =
      {
        USBD_Device0_Initialize
#ifdef  RTE_USB_Device_1
      , USBD_Device1_Initialize
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_Initialize
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_Initialize
#endif
      };
        void (* const USBD_Device_Uninitialize[USBD_DEV_NUM]) (void) =
      {
        USBD_Device0_Uninitialize
#ifdef  RTE_USB_Device_1
      , USBD_Device1_Uninitialize
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_Uninitialize
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_Uninitialize
#endif
      };
        void (* const USBD_Device_EventReset[USBD_DEV_NUM]) (void) =
      {
        USBD_Device0_EventReset
#ifdef  RTE_USB_Device_1
      , USBD_Device1_EventReset
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_EventReset
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_EventReset
#endif
      };
        usbdRequestStatus (* const USBD_Device_Endpoint0_SetupPacketReceived[USBD_DEV_NUM]) (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) =
      {
        USBD_Device0_Endpoint0_SetupPacketReceived
#ifdef  RTE_USB_Device_1
      , USBD_Device1_Endpoint0_SetupPacketReceived
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_Endpoint0_SetupPacketReceived
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_Endpoint0_SetupPacketReceived
#endif
      };
        void (* const USBD_Device_Endpoint0_SetupPacketProcessed[USBD_DEV_NUM]) (const USB_SETUP_PACKET *setup_packet) =
      {
        USBD_Device0_Endpoint0_SetupPacketProcessed
#ifdef  RTE_USB_Device_1
      , USBD_Device1_Endpoint0_SetupPacketProcessed
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_Endpoint0_SetupPacketProcessed
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_Endpoint0_SetupPacketProcessed
#endif
      };
        usbdRequestStatus (* const USBD_Device_Endpoint0_OutDataReceived[USBD_DEV_NUM]) (int32_t len) =
      {
        USBD_Device0_Endpoint0_OutDataReceived
#ifdef  RTE_USB_Device_1
      , USBD_Device1_Endpoint0_OutDataReceived
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_Endpoint0_OutDataReceived
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_Endpoint0_OutDataReceived
#endif
      };
        usbdRequestStatus (* const USBD_Device_Endpoint0_InDataSent[USBD_DEV_NUM]) (int32_t len) =
      {
        USBD_Device0_Endpoint0_InDataSent
#ifdef  RTE_USB_Device_1
      , USBD_Device1_Endpoint0_InDataSent
#endif
#ifdef  RTE_USB_Device_2
      , USBD_Device2_Endpoint0_InDataSent
#endif
#ifdef  RTE_USB_Device_3
      , USBD_Device3_Endpoint0_InDataSent
#endif
      };

__weak usbStatus USBD_ClassInitialize (uint8_t device) {
  uint8_t   instance;
  usbStatus status_ret, status;

  status_ret = usbOK;
#if (USBD_CUSTOM_CLASS_NUM > 0)
  for (instance = 0; instance < usbd_custom_class_num; instance++) {
    if (usbd_custom_class_ptr[instance] != NULL) {
      if (usbd_custom_class_ptr[instance]->dev_num == device) {
        status = USBD_CustomClass_ClassInitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_ADC_NUM > 0)
  for (instance = 0; instance < usbd_adc_num; instance++) {
    if ((usbd_adc_ptr[instance]->spkr_data_ptr != NULL) || (usbd_adc_ptr[instance]->mic_data_ptr != NULL)) {
      if (usbd_adc_ptr[instance]->dev_num == device) {
        status = USBD_ADC_ClassInitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_CDC_NUM > 0)
  for (instance = 0; instance < usbd_cdc_num; instance++) {
    if (usbd_cdc_ptr[instance]->data_ptr != NULL) {
      if (usbd_cdc_ptr[instance]->dev_num == device) {
        status = USBD_CDC_ClassInitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_HID_NUM > 0)
  for (instance = 0; instance < usbd_hid_num; instance++) {
    if (usbd_hid_ptr[instance]->data_ptr != NULL) {
      if (usbd_hid_ptr[instance]->dev_num == device) {
        status = USBD_HID_ClassInitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_MSC_NUM > 0)
  for (instance = 0; instance < usbd_msc_num; instance++) {
    if (usbd_msc_ptr[instance]->data_ptr != NULL) {
      if (usbd_msc_ptr[instance]->dev_num == device) {
        status = USBD_MSC_ClassInitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

  return status_ret;
}

__weak usbStatus USBD_ClassUninitialize (uint8_t device) {
  int8_t    instance;
  usbStatus status_ret, status;

  status_ret = usbOK;
#if (USBD_CUSTOM_CLASS_NUM > 0)
  for (instance = 0; instance < usbd_custom_class_num; instance++) {
    if (usbd_custom_class_ptr[instance] != NULL) {
      if (usbd_custom_class_ptr[instance]->dev_num == device) {
        status = USBD_CustomClass_ClassUninitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_ADC_NUM > 0)
  for (instance = 0; instance < usbd_adc_num; instance++) {
    if ((usbd_adc_ptr[instance]->spkr_data_ptr != NULL) || (usbd_adc_ptr[instance]->mic_data_ptr != NULL)) {
      if (usbd_adc_ptr[instance]->dev_num == device) {
        status = USBD_ADC_ClassUninitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_CDC_NUM > 0)
  for (instance = 0; instance < usbd_cdc_num; instance++) {
    if (usbd_cdc_ptr[instance]->data_ptr != NULL) {
      if (usbd_cdc_ptr[instance]->dev_num == device) {
        status = USBD_CDC_ClassUninitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_HID_NUM > 0)
  for (instance = 0; instance < usbd_hid_num; instance++) {
    if (usbd_hid_ptr[instance]->data_ptr != NULL) {
      if (usbd_hid_ptr[instance]->dev_num == device) {
        status = USBD_HID_ClassUninitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

#if (USBD_MSC_NUM > 0)
  for (instance = 0; instance < usbd_msc_num; instance++) {
    if (usbd_msc_ptr[instance]->data_ptr != NULL) {
      if (usbd_msc_ptr[instance]->dev_num == device) {
        status = USBD_MSC_ClassUninitialize (instance);
        if (status) status_ret = status;
      }
    }
  }
#endif

  return status_ret;
}

__weak void USBD_EventPowerOn                    (uint8_t device) {};
__weak void USBD_EventPowerOff                   (uint8_t device) {};
__weak void USBD_EventHighSpeed                  (uint8_t device) {};
__weak void USBD_EventSuspend                    (uint8_t device) {};
__weak void USBD_EventResume                     (uint8_t device) {};
__weak void USBD_EventSetInterface               (uint8_t device, uint8_t interface) {};
__weak void USBD_EventEndpointSetFeatureStall    (uint8_t device, uint8_t ep_addr)   {};
__weak void USBD_EventEnableRemoteWakeup         (uint8_t device) {};
__weak void USBD_EventDisableRemoteWakeup        (uint8_t device) {};

__weak void USBD_EventReset                      (uint8_t device) {
  uint8_t instance;

  USBD_Device_EventReset[device] ();

#if (USBD_CUSTOM_CLASS_NUM > 0)
  for (instance = 0; instance < usbd_custom_class_num; instance++) {
    if (usbd_custom_class_ptr[instance] != NULL) {
      if (usbd_custom_class_ptr[instance]->dev_num == device) {
        USBD_CustomClass_EventReset [instance] ();
      }
    }
  }
#endif

#if (USBD_ADC_NUM > 0)
  for (instance = 0; instance < usbd_adc_num; instance++) {
    if ((usbd_adc_ptr[instance]->spkr_data_ptr != NULL) || (usbd_adc_ptr[instance]->mic_data_ptr != NULL)){
      if (usbd_adc_ptr[instance]->dev_num == device) {
        USBD_ADC_EventReset (instance);
      }
    }
  }
#endif

#if (USBD_CDC_NUM > 0)
  for (instance = 0; instance < usbd_cdc_num; instance++) {
    if (usbd_cdc_ptr[instance]->data_ptr != NULL) {
      if (usbd_cdc_ptr[instance]->dev_num == device) {
        USBD_CDC_EventReset (instance);
      }
    }
  }
#endif

#if (USBD_HID_NUM > 0)
  for (instance = 0; instance < usbd_hid_num; instance++) {
    if (usbd_hid_ptr[instance]->data_ptr != NULL) {
      if (usbd_hid_ptr[instance]->dev_num == device) {
        USBD_HID_EventReset (instance);
      }
    }
  }
#endif

#if (USBD_MSC_NUM > 0)
  for (instance = 0; instance < usbd_msc_num; instance++) {
    if (usbd_msc_ptr[instance]->data_ptr != NULL) {
      if (usbd_msc_ptr[instance]->dev_num == device) {
        USBD_MSC_EventReset (instance);
      }
    }
  }
#endif
}

__weak void USBD_EventSetConfiguration           (uint8_t device, uint8_t configuration) {
#if (USBD_HID_NUM > 0)
  uint8_t instance;

  for (instance = 0; instance < usbd_hid_num; instance++) {
    if (usbd_hid_ptr[instance]->data_ptr != NULL) {
      if (usbd_hid_ptr[instance]->dev_num == device) {
        USBD_HID_EventSetConfiguration (instance);
      }
    }
  }
#endif
}

__weak void USBD_EventEndpointClearFeatureStall  (uint8_t device, uint8_t ep_addr) {
#if (USBD_MSC_NUM > 0)
  uint8_t instance;

  for (instance = 0; instance < usbd_msc_num; instance++) {
    if (usbd_msc_ptr[instance]->data_ptr != NULL) {
      if (usbd_msc_ptr[instance]->dev_num == device) {
        if (((usbd_msc_ptr[instance]->ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_msc_ptr[instance]->ep_bulk_out      ) == ep_addr)) {
          USBD_MSC_EventEndpointClearFeatureStall (instance, ep_addr);
        }
      }
    }
  }
#endif
}

__weak void USBD_EventEndpointStart              (uint8_t device, uint8_t ep_addr) {
  uint8_t instance;

#if (USBD_CUSTOM_CLASS_NUM > 0)
  for (instance = 0; instance < usbd_custom_class_num; instance++) {
    if (usbd_custom_class_ptr[instance] != NULL) {
      if (usbd_custom_class_ptr[instance]->dev_num == device) {
        if (((usbd_custom_class_ptr[instance]->if0_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_iso_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_iso_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_iso_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_iso_in  | 0x80) == ep_addr)) {
          USBD_CustomClass_EventEndpointStart [instance] (ep_addr);
        }
      }
    }
  }
#endif

#if (USBD_ADC_NUM > 0)
  for (instance = 0; instance < usbd_adc_num; instance++) {
    if (usbd_adc_ptr[instance]->dev_num == device) {
      if ((usbd_adc_ptr[instance]->spkr_data_ptr != NULL) && (usbd_adc_ptr[instance]->out_cfg != NULL)) {
        if ((usbd_adc_ptr[instance]->out_cfg->ep_iso) == ep_addr) {
          USBD_ADC_EventEndpointStart (instance, ep_addr);
        }
      }
      if ((usbd_adc_ptr[instance]->mic_data_ptr  != NULL) && (usbd_adc_ptr[instance]->in_cfg  != NULL)) {
        if ((usbd_adc_ptr[instance]->in_cfg->ep_iso | 0x80) == ep_addr) {
          USBD_ADC_EventEndpointStart (instance, ep_addr);
        }
      }
    }
  }
#endif

#if (USBD_CDC_NUM > 0)
  for (instance = 0; instance < usbd_cdc_num; instance++) {
    if (usbd_cdc_ptr[instance]->data_ptr != NULL) {
      if (usbd_cdc_ptr[instance]->dev_num == device) {
        if (((usbd_cdc_ptr[instance]->ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_cdc_ptr[instance]->ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_cdc_ptr[instance]->ep_bulk_out      ) == ep_addr)) {
          USBD_CDC_EventEndpointStart (instance, ep_addr);
        }
      }
    }
  }
#endif

#if (USBD_HID_NUM > 0)
  for (instance = 0; instance < usbd_hid_num; instance++) {
    if (usbd_hid_ptr[instance]->data_ptr != NULL) {
      if (usbd_hid_ptr[instance]->dev_num == device) {
        if (((usbd_hid_ptr[instance]->ep_int_in | 0x80) == ep_addr) ||
            ((usbd_hid_ptr[instance]->ep_int_out      ) == ep_addr)) {
          USBD_HID_EventEndpointStart (instance, ep_addr);
        }
      }
    }
  }
#endif

#if (USBD_MSC_NUM > 0)
  for (instance = 0; instance < usbd_msc_num; instance++) {
    if (usbd_msc_ptr[instance]->data_ptr != NULL) {
      if (usbd_msc_ptr[instance]->dev_num == device) {
        if (((usbd_msc_ptr[instance]->ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_msc_ptr[instance]->ep_bulk_out      ) == ep_addr)) {
          USBD_MSC_EventEndpointStart (instance, ep_addr);
        }
      }
    }
  }
#endif
}

__weak void USBD_EventEndpointStop               (uint8_t device, uint8_t ep_addr) {
#if ((USBD_CUSTOM_CLASS_NUM > 0) || (USBD_ADC_NUM > 0)  || (USBD_CDC_NUM > 0))
  uint8_t instance;
#endif

#if (USBD_CUSTOM_CLASS_NUM > 0)
  for (instance = 0; instance < usbd_custom_class_num; instance++) {
    if (usbd_custom_class_ptr[instance] != NULL) {
      if (usbd_custom_class_ptr[instance]->dev_num == device) {
        if (((usbd_custom_class_ptr[instance]->if0_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if0_ep_iso_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if1_ep_iso_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if2_ep_iso_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_bulk_out      ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_int_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_iso_out       ) == ep_addr) ||
            ((usbd_custom_class_ptr[instance]->if3_ep_iso_in  | 0x80) == ep_addr)) {
          USBD_CustomClass_EventEndpointStop [instance] (ep_addr);
        }
      }
    }
  }
#endif

#if (USBD_ADC_NUM > 0)
  for (instance = 0; instance < usbd_adc_num; instance++) {
    if (usbd_adc_ptr[instance]->dev_num == device) {
      if ((usbd_adc_ptr[instance]->spkr_data_ptr != NULL) && (usbd_adc_ptr[instance]->out_cfg != NULL)) {
        if ((usbd_adc_ptr[instance]->out_cfg->ep_iso) == ep_addr) {
          USBD_ADC_EventEndpointStop (instance, ep_addr);
        }
      }
      if ((usbd_adc_ptr[instance]->mic_data_ptr  != NULL) && (usbd_adc_ptr[instance]->in_cfg  != NULL)) {
        if ((usbd_adc_ptr[instance]->in_cfg->ep_iso | 0x80) == ep_addr) {
          USBD_ADC_EventEndpointStop (instance, ep_addr);
        }
      }
    }
  }
#endif

#if (USBD_CDC_NUM > 0)
  for (instance = 0; instance < usbd_cdc_num; instance++) {
    if (usbd_cdc_ptr[instance]->data_ptr != NULL) {
      if (usbd_cdc_ptr[instance]->dev_num == device) {
        if (((usbd_cdc_ptr[instance]->ep_int_in  | 0x80) == ep_addr) ||
            ((usbd_cdc_ptr[instance]->ep_bulk_in | 0x80) == ep_addr) ||
            ((usbd_cdc_ptr[instance]->ep_bulk_out      ) == ep_addr)) {
          USBD_CDC_EventEndpointStop (instance, ep_addr);
        }
      }
    }
  }
#endif
}
#endif

#endif  /* LAST_DEVICE_COMPILE */


/*------------------------------------------------------------------------------
 *      USB Device Global Macros for Descriptors
 *----------------------------------------------------------------------------*/

#ifndef USBD_DESC_MACROS
#define USBD_DESC_MACROS                1
#include "usbd_config_desc_macros.h"
#endif


/*------------------------------------------------------------------------------
 *      USB HID 0..3 Device Descriptors
 *----------------------------------------------------------------------------*/

#if    (USBD_HID_NUM > 0)

#ifdef  RTE_USB_Device_HID_0
#if   ((defined(USBD0_PORT) && (USBD0_HID0 == 1)) || \
       (defined(USBD1_PORT) && (USBD1_HID0 == 1)) || \
       (defined(USBD2_PORT) && (USBD2_HID0 == 1)) || \
       (defined(USBD3_PORT) && (USBD3_HID0 == 1)))
#include "usbd_config_desc_hid_0.c"
#endif
#endif

#ifdef  RTE_USB_Device_HID_1
#if   ((defined(USBD0_PORT) && (USBD0_HID1 == 1)) || \
       (defined(USBD1_PORT) && (USBD1_HID1 == 1)) || \
       (defined(USBD2_PORT) && (USBD2_HID1 == 1)) || \
       (defined(USBD3_PORT) && (USBD3_HID1 == 1)))
#include "usbd_config_desc_hid_1.c"
#endif
#endif

#ifdef  RTE_USB_Device_HID_2
#if   ((defined(USBD0_PORT) && (USBD0_HID2 == 1)) || \
       (defined(USBD1_PORT) && (USBD1_HID2 == 1)) || \
       (defined(USBD2_PORT) && (USBD2_HID2 == 1)) || \
       (defined(USBD3_PORT) && (USBD3_HID2 == 1)))
#include "usbd_config_desc_hid_2.c"
#endif
#endif

#ifdef  RTE_USB_Device_HID_3
#if   ((defined(USBD0_PORT) && (USBD0_HID3 == 1)) || \
       (defined(USBD1_PORT) && (USBD1_HID3 == 1)) || \
       (defined(USBD2_PORT) && (USBD2_HID3 == 1)) || \
       (defined(USBD3_PORT) && (USBD3_HID3 == 1)))
#include "usbd_config_desc_hid_3.c"
#endif
#endif

#ifdef  LAST_DEVICE_COMPILE

extern  usbd_hid_desc_t usbd_hid0_desc;
extern  usbd_hid_desc_t usbd_hid1_desc;
extern  usbd_hid_desc_t usbd_hid2_desc;
extern  usbd_hid_desc_t usbd_hid3_desc;

usbd_hid_desc_t * const usbd_hid_desc_ptr[USBD_HID_NUM]  = {
#ifdef  RTE_USB_Device_HID_0
       &usbd_hid0_desc
#endif
#ifdef  RTE_USB_Device_HID_1
     , &usbd_hid1_desc
#endif
#ifdef  RTE_USB_Device_HID_2
     , &usbd_hid2_desc
#endif
#ifdef  RTE_USB_Device_HID_3
     , &usbd_hid3_desc
#endif
};

#endif  /* LAST_DEVICE_COMPILE */

#endif


/*------------------------------------------------------------------------------
 *      USB Device 0 Descriptors
 *----------------------------------------------------------------------------*/

#ifdef  USBD0_PORT
#include "usbd_config_desc_0.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 1 Descriptors
 *----------------------------------------------------------------------------*/

#ifdef  USBD1_PORT
#include "usbd_config_desc_1.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 2 Descriptors
 *----------------------------------------------------------------------------*/

#ifdef  USBD2_PORT
#include "usbd_config_desc_2.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 0 Descriptors
 *----------------------------------------------------------------------------*/

#ifdef  USBD3_PORT
#include "usbd_config_desc_3.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Device 0..3 Pointers to Descriptors
 *----------------------------------------------------------------------------*/

#ifdef  LAST_DEVICE_COMPILE

#if    (USBD_DEV_NUM > 0)

extern usbd_desc_t usbd0_desc;
extern usbd_desc_t usbd1_desc;
extern usbd_desc_t usbd2_desc;
extern usbd_desc_t usbd3_desc;

usbd_desc_t *usbd_desc_ptr [USBD_DEV_NUM]  = {
#ifdef  RTE_USB_Device_0
       &usbd0_desc
#endif
#ifdef  RTE_USB_Device_1
     , &usbd1_desc
#endif
#ifdef  RTE_USB_Device_2
     , &usbd2_desc
#endif
#ifdef  RTE_USB_Device_3
     , &usbd3_desc
#endif
};

#endif

#endif  /* LAST_DEVICE_COMPILE */

#endif  /* __NO_USB_LIB_C */

#pragma pop
