/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_compatibility.h
 * Purpose: USB Device Library Compatibility module
 * Rev.:    V6.6.0
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *      USB Device Custom Class 0..3 compatibility defines
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *      USB Device ADC 0..3 compatibility defines
 *----------------------------------------------------------------------------*/

#ifdef  RTE_USB_Device_ADC_0
#ifndef USBD_ADC0_THREAD_STACK_SIZE
#define USBD_ADC0_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_ADC0_THREAD_PRIORITY
#define USBD_ADC0_THREAD_PRIORITY                 osPriorityAboveNormal
#endif
#endif

#ifdef  RTE_USB_Device_ADC_1
#ifndef USBD_ADC1_THREAD_STACK_SIZE
#define USBD_ADC1_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_ADC1_THREAD_PRIORITY
#define USBD_ADC1_THREAD_PRIORITY                 osPriorityAboveNormal
#endif
#endif

#ifdef  RTE_USB_Device_ADC_2
#ifndef USBD_ADC2_THREAD_STACK_SIZE
#define USBD_ADC2_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_ADC2_THREAD_PRIORITY
#define USBD_ADC2_THREAD_PRIORITY                 osPriorityAboveNormal
#endif
#endif

#ifdef  RTE_USB_Device_ADC_3
#ifndef USBD_ADC3_THREAD_STACK_SIZE
#define USBD_ADC3_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_ADC3_THREAD_PRIORITY
#define USBD_ADC3_THREAD_PRIORITY                 osPriorityAboveNormal
#endif
#endif


/*------------------------------------------------------------------------------
 *      USB Device CDC 0..3 compatibility defines
 *----------------------------------------------------------------------------*/

#ifdef  RTE_USB_Device_CDC_0
#if    (USBD_CDC0_SUBCLASS == 2)
#ifndef USBD_CDC0_ACM_SEND_BUF_SIZE
#define USBD_CDC0_ACM_SEND_BUF_SIZE               USBD_CDC0_SEND_BUF_SIZE
#endif
#ifndef USBD_CDC0_ACM_RECEIVE_BUF_SIZE
#define USBD_CDC0_ACM_RECEIVE_BUF_SIZE            USBD_CDC0_RECEIVE_BUF_SIZE
#endif
#endif
#endif

#ifdef  RTE_USB_Device_CDC_1
#if    (USBD_CDC1_SUBCLASS == 2)
#ifndef USBD_CDC1_ACM_SEND_BUF_SIZE
#define USBD_CDC1_ACM_SEND_BUF_SIZE               USBD_CDC1_SEND_BUF_SIZE
#endif
#ifndef USBD_CDC1_ACM_RECEIVE_BUF_SIZE
#define USBD_CDC1_ACM_RECEIVE_BUF_SIZE            USBD_CDC1_RECEIVE_BUF_SIZE
#endif
#endif
#endif

#ifdef  RTE_USB_Device_CDC_2
#if    (USBD_CDC2_SUBCLASS == 2)
#ifndef USBD_CDC2_ACM_SEND_BUF_SIZE
#define USBD_CDC2_ACM_SEND_BUF_SIZE               USBD_CDC2_SEND_BUF_SIZE
#endif
#ifndef USBD_CDC2_ACM_RECEIVE_BUF_SIZE
#define USBD_CDC2_ACM_RECEIVE_BUF_SIZE            USBD_CDC2_RECEIVE_BUF_SIZE
#endif
#endif
#endif

#ifdef  RTE_USB_Device_CDC_3
#if    (USBD_CDC3_SUBCLASS == 2)
#ifndef USBD_CDC3_ACM_SEND_BUF_SIZE
#define USBD_CDC3_ACM_SEND_BUF_SIZE               USBD_CDC3_SEND_BUF_SIZE
#endif
#ifndef USBD_CDC3_ACM_RECEIVE_BUF_SIZE
#define USBD_CDC3_ACM_RECEIVE_BUF_SIZE            USBD_CDC3_RECEIVE_BUF_SIZE
#endif
#endif
#endif


/*------------------------------------------------------------------------------
 *      USB Device HID 0..3 compatibility defines
 *----------------------------------------------------------------------------*/

#ifdef  RTE_USB_Device_HID_0
#ifndef USBD_HID0_THREAD_STACK_SIZE
#define USBD_HID0_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_HID0_THREAD_PRIORITY
#define USBD_HID0_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_HID0_EP_INT_IN_WMAXPACKETSIZE
#ifdef  USBD_HID0_WMAXPACKETSIZE
#define USBD_HID0_EP_INT_IN_WMAXPACKETSIZE        USBD_HID0_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID0_EP_INT_IN_BINTERVAL
#ifdef  USBD_HID0_BINTERVAL
#define USBD_HID0_EP_INT_IN_BINTERVAL             USBD_HID0_BINTERVAL
#endif
#endif
#ifndef USBD_HID0_EP_INT_IN_HS_WMAXPACKETSIZE
#ifdef  USBD_HID0_HS_WMAXPACKETSIZE
#define USBD_HID0_EP_INT_IN_HS_WMAXPACKETSIZE     USBD_HID0_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID0_EP_INT_IN_HS_BINTERVAL
#ifdef  USBD_HID0_HS_BINTERVAL
#define USBD_HID0_EP_INT_IN_HS_BINTERVAL          USBD_HID0_HS_BINTERVAL
#endif
#endif
#ifndef USBD_HID0_EP_INT_OUT_WMAXPACKETSIZE
#ifdef  USBD_HID0_WMAXPACKETSIZE
#define USBD_HID0_EP_INT_OUT_WMAXPACKETSIZE       USBD_HID0_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID0_EP_INT_OUT_BINTERVAL
#ifdef  USBD_HID0_BINTERVAL
#define USBD_HID0_EP_INT_OUT_BINTERVAL            USBD_HID0_BINTERVAL
#endif
#endif
#ifndef USBD_HID0_EP_INT_OUT_HS_WMAXPACKETSIZE
#ifdef  USBD_HID0_HS_WMAXPACKETSIZE
#define USBD_HID0_EP_INT_OUT_HS_WMAXPACKETSIZE    USBD_HID0_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID0_EP_INT_OUT_HS_BINTERVAL
#ifdef  USBD_HID0_HS_BINTERVAL
#define USBD_HID0_EP_INT_OUT_HS_BINTERVAL         USBD_HID0_HS_BINTERVAL
#endif
#endif

#ifndef USBD_HID0_USER_REPORT_DESCRIPTOR
#define USBD_HID0_USER_REPORT_DESCRIPTOR          0
#endif
#endif

#ifdef  RTE_USB_Device_HID_1
#ifndef USBD_HID1_THREAD_STACK_SIZE
#define USBD_HID1_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_HID1_THREAD_PRIORITY
#define USBD_HID1_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_HID1_EP_INT_IN_WMAXPACKETSIZE
#ifdef  USBD_HID1_WMAXPACKETSIZE
#define USBD_HID1_EP_INT_IN_WMAXPACKETSIZE        USBD_HID1_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID1_EP_INT_IN_BINTERVAL
#ifdef  USBD_HID1_BINTERVAL
#define USBD_HID1_EP_INT_IN_BINTERVAL             USBD_HID1_BINTERVAL
#endif
#endif
#ifndef USBD_HID1_EP_INT_IN_HS_WMAXPACKETSIZE
#ifdef  USBD_HID1_HS_WMAXPACKETSIZE
#define USBD_HID1_EP_INT_IN_HS_WMAXPACKETSIZE     USBD_HID1_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID1_EP_INT_IN_HS_BINTERVAL
#ifdef  USBD_HID1_HS_BINTERVAL
#define USBD_HID1_EP_INT_IN_HS_BINTERVAL          USBD_HID1_HS_BINTERVAL
#endif
#endif
#ifndef USBD_HID1_EP_INT_OUT_WMAXPACKETSIZE
#ifdef  USBD_HID1_WMAXPACKETSIZE
#define USBD_HID1_EP_INT_OUT_WMAXPACKETSIZE       USBD_HID1_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID1_EP_INT_OUT_BINTERVAL
#ifdef  USBD_HID1_BINTERVAL
#define USBD_HID1_EP_INT_OUT_BINTERVAL            USBD_HID1_BINTERVAL
#endif
#endif
#ifndef USBD_HID1_EP_INT_OUT_HS_WMAXPACKETSIZE
#ifdef  USBD_HID1_HS_WMAXPACKETSIZE
#define USBD_HID1_EP_INT_OUT_HS_WMAXPACKETSIZE    USBD_HID1_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID1_EP_INT_OUT_HS_BINTERVAL
#ifdef  USBD_HID1_HS_BINTERVAL
#define USBD_HID1_EP_INT_OUT_HS_BINTERVAL         USBD_HID1_HS_BINTERVAL
#endif
#endif

#ifndef USBD_HID1_USER_REPORT_DESCRIPTOR
#define USBD_HID1_USER_REPORT_DESCRIPTOR          0
#endif
#endif

#ifdef  RTE_USB_Device_HID_2
#ifndef USBD_HID2_THREAD_STACK_SIZE
#define USBD_HID2_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_HID2_THREAD_PRIORITY
#define USBD_HID2_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_HID2_EP_INT_IN_WMAXPACKETSIZE
#ifdef  USBD_HID2_WMAXPACKETSIZE
#define USBD_HID2_EP_INT_IN_WMAXPACKETSIZE        USBD_HID2_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID2_EP_INT_IN_BINTERVAL
#ifdef  USBD_HID2_BINTERVAL
#define USBD_HID2_EP_INT_IN_BINTERVAL             USBD_HID2_BINTERVAL
#endif
#endif
#ifndef USBD_HID2_EP_INT_IN_HS_WMAXPACKETSIZE
#ifdef  USBD_HID2_HS_WMAXPACKETSIZE
#define USBD_HID2_EP_INT_IN_HS_WMAXPACKETSIZE     USBD_HID2_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID2_EP_INT_IN_HS_BINTERVAL
#ifdef  USBD_HID2_HS_BINTERVAL
#define USBD_HID2_EP_INT_IN_HS_BINTERVAL          USBD_HID2_HS_BINTERVAL
#endif
#endif
#ifndef USBD_HID2_EP_INT_OUT_WMAXPACKETSIZE
#ifdef  USBD_HID2_WMAXPACKETSIZE
#define USBD_HID2_EP_INT_OUT_WMAXPACKETSIZE       USBD_HID2_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID2_EP_INT_OUT_BINTERVAL
#ifdef  USBD_HID2_BINTERVAL
#define USBD_HID2_EP_INT_OUT_BINTERVAL            USBD_HID2_BINTERVAL
#endif
#endif
#ifndef USBD_HID2_EP_INT_OUT_HS_WMAXPACKETSIZE
#ifdef  USBD_HID2_HS_WMAXPACKETSIZE
#define USBD_HID2_EP_INT_OUT_HS_WMAXPACKETSIZE    USBD_HID2_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID2_EP_INT_OUT_HS_BINTERVAL
#ifdef  USBD_HID2_HS_BINTERVAL
#define USBD_HID2_EP_INT_OUT_HS_BINTERVAL         USBD_HID2_HS_BINTERVAL
#endif
#endif

#ifndef USBD_HID2_USER_REPORT_DESCRIPTOR
#define USBD_HID2_USER_REPORT_DESCRIPTOR          0
#endif
#endif

#ifdef  RTE_USB_Device_HID_3
#ifndef USBD_HID3_THREAD_STACK_SIZE
#define USBD_HID3_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_HID3_THREAD_PRIORITY
#define USBD_HID3_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_HID3_EP_INT_IN_WMAXPACKETSIZE
#ifdef  USBD_HID3_WMAXPACKETSIZE
#define USBD_HID3_EP_INT_IN_WMAXPACKETSIZE        USBD_HID3_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID3_EP_INT_IN_BINTERVAL
#ifdef  USBD_HID3_BINTERVAL
#define USBD_HID3_EP_INT_IN_BINTERVAL             USBD_HID3_BINTERVAL
#endif
#endif
#ifndef USBD_HID3_EP_INT_IN_HS_WMAXPACKETSIZE
#ifdef  USBD_HID3_HS_WMAXPACKETSIZE
#define USBD_HID3_EP_INT_IN_HS_WMAXPACKETSIZE     USBD_HID3_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID3_EP_INT_IN_HS_BINTERVAL
#ifdef  USBD_HID3_HS_BINTERVAL
#define USBD_HID3_EP_INT_IN_HS_BINTERVAL          USBD_HID3_HS_BINTERVAL
#endif
#endif
#ifndef USBD_HID3_EP_INT_OUT_WMAXPACKETSIZE
#ifdef  USBD_HID3_WMAXPACKETSIZE
#define USBD_HID3_EP_INT_OUT_WMAXPACKETSIZE       USBD_HID3_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID3_EP_INT_OUT_BINTERVAL
#ifdef  USBD_HID3_BINTERVAL
#define USBD_HID3_EP_INT_OUT_BINTERVAL            USBD_HID3_BINTERVAL
#endif
#endif
#ifndef USBD_HID3_EP_INT_OUT_HS_WMAXPACKETSIZE
#ifdef  USBD_HID3_HS_WMAXPACKETSIZE
#define USBD_HID3_EP_INT_OUT_HS_WMAXPACKETSIZE    USBD_HID3_HS_WMAXPACKETSIZE
#endif
#endif
#ifndef USBD_HID3_EP_INT_OUT_HS_BINTERVAL
#ifdef  USBD_HID3_HS_BINTERVAL
#define USBD_HID3_EP_INT_OUT_HS_BINTERVAL         USBD_HID3_HS_BINTERVAL
#endif
#endif

#ifndef USBD_HID3_USER_REPORT_DESCRIPTOR
#define USBD_HID3_USER_REPORT_DESCRIPTOR          0
#endif
#endif


/*------------------------------------------------------------------------------
 *      USB Device MSC 0..3 compatibility defines
 *----------------------------------------------------------------------------*/

#ifdef  RTE_USB_Device_MSC_0
#ifndef USBD_MSC0_THREAD_STACK_SIZE
#define USBD_MSC0_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_MSC0_THREAD_PRIORITY
#define USBD_MSC0_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_MSC0_BULK_BUF_SIZE
#define USBD_MSC0_BULK_BUF_SIZE                   USBD_MSC0_MAX_PACKET
#endif
#endif

#ifdef  RTE_USB_Device_MSC_1
#ifndef USBD_MSC1_THREAD_STACK_SIZE
#define USBD_MSC1_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_MSC1_THREAD_PRIORITY
#define USBD_MSC1_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_MSC1_BULK_BUF_SIZE
#define USBD_MSC1_BULK_BUF_SIZE                   USBD_MSC1_MAX_PACKET
#endif
#endif

#ifdef  RTE_USB_Device_MSC_2
#ifndef USBD_MSC2_THREAD_STACK_SIZE
#define USBD_MSC2_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_MSC2_THREAD_PRIORITY
#define USBD_MSC2_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_MSC2_BULK_BUF_SIZE
#define USBD_MSC2_BULK_BUF_SIZE                   USBD_MSC2_MAX_PACKET
#endif
#endif

#ifdef  RTE_USB_Device_MSC_3
#ifndef USBD_MSC3_THREAD_STACK_SIZE
#define USBD_MSC3_THREAD_STACK_SIZE               0
#endif
#ifndef USBD_MSC3_THREAD_PRIORITY
#define USBD_MSC3_THREAD_PRIORITY                 osPriorityAboveNormal
#endif

#ifndef USBD_MSC3_BULK_BUF_SIZE
#define USBD_MSC3_BULK_BUF_SIZE                   USBD_MSC3_MAX_PACKET
#endif
#endif
