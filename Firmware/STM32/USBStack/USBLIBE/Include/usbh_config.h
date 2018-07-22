/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbh_config.h
 * Purpose: USB Host Library Configuration
 * Rev.:    V6.4.1
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "usb_def.h"
#include "usb_adc.h"
#include "usb_cdc.h"
#include "usb_hid.h"
#include "usb_msc.h"
#include "rl_usbh_lib.h"


#if !defined (osThreadExt)
/// External reference to a Thread Definition
/// \param         name         name of the thread function.
#define osThreadExt(name)  \
extern const osThreadDef_t os_thread_def_##name
#endif


#pragma push
#pragma thumb
#pragma O3


/*------------------------------------------------------------------------------
 *      USB Host Global Macros
 *----------------------------------------------------------------------------*/

#define USBHn_DRIVER_(n)                Driver_USBH##n
#define USBHn_DRIVER(n)                 USBHn_DRIVER_(n)

#define USBHn_DRIVER_HCI_(n)            Driver_USBH##n##_HCI
#define USBHn_DRIVER_HCI(n)             USBHn_DRIVER_HCI_(n)

#define USBHn_DRIVER_OHCI_LIB_(n)       Driver_USBH##n##_OHCI_LIB
#define USBHn_DRIVER_OHCI_LIB(n)        USBHn_DRIVER_OHCI_LIB_(n)

#define USBHn_DRIVER_EHCI_LIB_(n)       Driver_USBH##n##_EHCI_LIB
#define USBHn_DRIVER_EHCI_LIB(n)        USBHn_DRIVER_EHCI_LIB_(n)


/*------------------------------------------------------------------------------
 *      USB Host 0 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifdef   USBH0_HC_NUM
#include "usbh_config_hc_0.c"
#endif

/*------------------------------------------------------------------------------
 *      USB Host 1 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifdef   USBH1_HC_NUM
#include "usbh_config_hc_1.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Host 2 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifdef   USBH2_HC_NUM
#include "usbh_config_hc_2.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Host 3 Macros, Calculations and Constants for Library
 *----------------------------------------------------------------------------*/

#ifdef   USBH3_HC_NUM
#include "usbh_config_hc_3.c"
#endif


/*------------------------------------------------------------------------------
 *      USB Host Global Macros
 *----------------------------------------------------------------------------*/

#ifdef  USBH3_HC_NUM
#define LAST_DEVICE_COMPILE             1
#elif  (defined(USBH2_HC_NUM) && !defined(RTE_USB_Host_3))
#define LAST_DEVICE_COMPILE             1
#elif  (defined(USBH1_HC_NUM) && !defined(RTE_USB_Host_3) && !defined(RTE_USB_Host_2))
#define LAST_DEVICE_COMPILE             1
#elif  (defined(USBH0_HC_NUM) && !defined(RTE_USB_Host_3) && !defined(RTE_USB_Host_2) && !defined(RTE_USB_Host_1))
#define LAST_DEVICE_COMPILE             1
#endif


/*------------------------------------------------------------------------------
 *      USB Host 0..3 Configurations
 *----------------------------------------------------------------------------*/

#if    (defined(LAST_DEVICE_COMPILE))

#ifndef USBH_MSC_NUM
#define USBH_MSC_NUM                    0
#endif

#ifndef USBH_HID_NUM
#define USBH_HID_NUM                    0
#endif

#ifndef USBH_CDC_NUM
#define USBH_CDC_NUM                    0
#endif

#ifndef USBH_CUSTOM_CLASS_NUM
#define USBH_CUSTOM_CLASS_NUM           0
#endif

#ifdef  RTE_USB_Host_0
#define USBH0_HC                        1
#else
#define USBH0_HC                        0
#endif

#ifdef  RTE_USB_Host_1
#define USBH1_HC                        1
#else
#define USBH1_HC                        0
#endif

#ifdef  RTE_USB_Host_2
#define USBH2_HC                        1
#else
#define USBH2_HC                        0
#endif

#ifdef  RTE_USB_Host_3
#define USBH3_HC                        1
#else
#define USBH3_HC                        0
#endif

#define USBH_HC_NUM                    (USBH0_HC + USBH1_HC + USBH2_HC + USBH3_HC)
#define USBH_HC_MSK                    (0x0F >> (4 - USBH_HC_NUM))
#define USBH_OHCI_NUM                  (USBH_HC_NUM)
#define USBH_EHCI_NXP_NUM              (USBH_HC_NUM)
#define USBH_DCD_NUM                  ((USBH_MSC_NUM > 0) + (USBH_HID_NUM > 0) + (USBH_CDC_NUM > 0) + (USBH_CUSTOM_CLASS_NUM > 0))
#define USBH_DEV_NUM                   (USBH_MSC_NUM      +  USBH_HID_NUM      +  USBH_CDC_NUM      +  USBH_CUSTOM_CLASS_NUM     )

                                        // Define constants
const   uint8_t usbh_hc_num  =          USBH_HC_NUM;
const   uint8_t usbh_hc_msk  =          USBH_HC_MSK;
const   uint8_t usbh_dcd_num =          USBH_DCD_NUM;
const   uint8_t usbh_dev_num =          USBH_DEV_NUM;
const   uint8_t usbh_msc_num =          USBH_MSC_NUM;
const   uint8_t usbh_hid_num =          USBH_HID_NUM;
const   uint8_t usbh_cdc_num =          USBH_CDC_NUM;
const   uint8_t usbh_cls_num =          USBH_CUSTOM_CLASS_NUM;

                                        // Define drivers
extern  const ARM_DRIVER_USBH   *usbh0_hcd_ptr;
extern  const ARM_DRIVER_USBH   *usbh1_hcd_ptr;
extern  const ARM_DRIVER_USBH   *usbh2_hcd_ptr;
extern  const ARM_DRIVER_USBH   *usbh3_hcd_ptr;

                                        // Register Host Controller Drivers
const   ARM_DRIVER_USBH ** const usbh_hcd_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_hcd_ptr
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_hcd_ptr
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_hcd_ptr
#endif
#ifdef  RTE_USB_Host_3
      , &usbh3_hcd_ptr
#endif
};

extern  const ARM_DRIVER_USBH_HCI *usbh0_hci_hcd_ptr;
extern  const ARM_DRIVER_USBH_HCI *usbh1_hci_hcd_ptr;
extern  const ARM_DRIVER_USBH_HCI *usbh2_hci_hcd_ptr;
extern  const ARM_DRIVER_USBH_HCI *usbh3_hci_hcd_ptr;

const   ARM_DRIVER_USBH_HCI ** const usbh_hci_hcd_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_hci_hcd_ptr
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_hci_hcd_ptr
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_hci_hcd_ptr
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_hci_hcd_ptr
#endif
};

extern  USBH_HC_t *usbh0_hc_ptr;
extern  USBH_HC_t *usbh1_hc_ptr;
extern  USBH_HC_t *usbh2_hc_ptr;
extern  USBH_HC_t *usbh3_hc_ptr;

const   USBH_HC_t ** const usbh_hc_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_hc_ptr
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_hc_ptr
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_hc_ptr
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_hc_ptr
#endif
};

extern  USBH_OHCI_t *usbh0_ohci_ptr;
extern  USBH_OHCI_t *usbh1_ohci_ptr;
extern  USBH_OHCI_t *usbh2_ohci_ptr;
extern  USBH_OHCI_t *usbh3_ohci_ptr;

const   USBH_OHCI_t ** const usbh_ohci_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_ohci_ptr
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_ohci_ptr
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_ohci_ptr
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_ohci_ptr
#endif
};

extern  USBH_EHCI_t *usbh0_ehci_ptr;
extern  USBH_EHCI_t *usbh1_ehci_ptr;
extern  USBH_EHCI_t *usbh2_ehci_ptr;
extern  USBH_EHCI_t *usbh3_ehci_ptr;

const   USBH_EHCI_t ** const usbh_ehci_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_ehci_ptr
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_ehci_ptr
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_ehci_ptr
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_ehci_ptr
#endif
};

#ifdef  RTE_USB_Host_0
extern  const uint8_t    usbh0_mem_pool_reloc;
extern  uint32_t         usbh0_mem_pool[];
extern  const uint32_t   usbh0_mem_pool_size;
extern  USBH_PIPE        usbh0_pipe    [];
extern  USBH_PIPE_TID_t  usbh0_pipe_tid[];
extern  const uint32_t   usbh0_pipe_num;
extern  const uint32_t   usbh0_transfer_num;
#endif
#ifdef  RTE_USB_Host_1
extern  const uint8_t    usbh1_mem_pool_reloc;
extern  uint32_t         usbh1_mem_pool[];
extern  const uint32_t   usbh1_mem_pool_size;
extern  USBH_PIPE        usbh1_pipe    [];
extern  USBH_PIPE_TID_t  usbh1_pipe_tid[];
extern  const uint32_t   usbh1_pipe_num;
extern  const uint32_t   usbh1_transfer_num;
#endif
#ifdef  RTE_USB_Host_2
extern  const uint8_t    usbh2_mem_pool_reloc;
extern  uint32_t         usbh2_mem_pool[];
extern  const uint32_t   usbh2_mem_pool_size;
extern  USBH_PIPE        usbh2_pipe    [];
extern  USBH_PIPE_TID_t  usbh2_pipe_tid[];
extern  const uint32_t   usbh2_pipe_num;
extern  const uint32_t   usbh2_transfer_num;
#endif
#ifdef  RTE_USB_Host_3
extern  const uint8_t    usbh3_mem_pool_reloc;
extern  uint32_t         usbh3_mem_pool[];
extern  const uint32_t   usbh3_mem_pool_size;
extern  USBH_PIPE        usbh3_pipe    [];
extern  USBH_PIPE_TID_t  usbh3_pipe_tid[];
extern  const uint32_t   usbh3_pipe_num;
extern  const uint32_t   usbh3_transfer_num;
#endif

const   uint8_t          * const usbh_mem_pool_reloc_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_mem_pool_reloc
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_mem_pool_reloc
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_mem_pool_reloc
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_mem_pool_reloc
#endif
};
        uint32_t       * const usbh_mem_pool_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        usbh0_mem_pool
#endif
#ifdef  RTE_USB_Host_1
      , usbh1_mem_pool
#endif
#ifdef  RTE_USB_Host_2
      , usbh2_mem_pool
#endif
#ifdef  RTE_USB_Host_3
      , usbh3_mem_pool
#endif
};
const   uint32_t       * const usbh_mem_pool_size_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_mem_pool_size
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_mem_pool_size
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_mem_pool_size
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_mem_pool_size
#endif
};
        USBH_PIPE_TID_t  * const usbh_pipe_tid_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        usbh0_pipe_tid
#endif
#ifdef  RTE_USB_Host_1
      , usbh1_pipe_tid
#endif
#ifdef  RTE_USB_Host_2
      , usbh2_pipe_tid
#endif
#ifdef  RTE_USB_Host_3
      , usbh3_pipe_tid
#endif
};
        USBH_PIPE        * const usbh_pipe_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        usbh0_pipe
#endif
#ifdef  RTE_USB_Host_1
      , usbh1_pipe
#endif
#ifdef  RTE_USB_Host_2
      , usbh2_pipe
#endif
#ifdef  RTE_USB_Host_3
      , usbh3_pipe
#endif
};
const   uint32_t         * const usbh_pipe_num_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_pipe_num
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_pipe_num
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_pipe_num
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_pipe_num
#endif
};

const   uint32_t         * const  usbh_transfer_num_ptr [USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
       &usbh0_transfer_num
#endif
#ifdef  RTE_USB_Host_1
     , &usbh1_transfer_num
#endif
#ifdef  RTE_USB_Host_2
     , &usbh2_transfer_num
#endif
#ifdef  RTE_USB_Host_3
     , &usbh3_transfer_num
#endif
};

#ifdef  RTE_USB_Host_0
osThreadExt(USBH0_Core_Thread);
#endif

#ifdef  RTE_USB_Host_1
osThreadExt(USBH1_Core_Thread);
#endif

#ifdef  RTE_USB_Host_2
osThreadExt(USBH2_Core_Thread);
#endif

#ifdef  RTE_USB_Host_3
osThreadExt(USBH3_Core_Thread);
#endif

const   osThreadDef_t * const usbh_core_thread_def_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        osThread(USBH0_Core_Thread)
#endif
#ifdef  RTE_USB_Host_1
      , osThread(USBH1_Core_Thread)
#endif
#ifdef  RTE_USB_Host_2
      , osThread(USBH2_Core_Thread)
#endif
#ifdef  RTE_USB_Host_3
      , osThread(USBH3_Core_Thread)
#endif
};
osThreadId usbh_core_thread_id[USBH_HC_NUM];

#define USBH_DEBOUNCE_IN_MS             100

const   uint16_t usbh_debounce_in_ms[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        USBH_DEBOUNCE_IN_MS
#endif
#ifdef  RTE_USB_Host_1
      , USBH_DEBOUNCE_IN_MS
#endif
#ifdef  RTE_USB_Host_2
      , USBH_DEBOUNCE_IN_MS
#endif
#ifdef  RTE_USB_Host_3
      , USBH_DEBOUNCE_IN_MS
#endif
};

                                        // Define semaphores
osSemaphoreId usbh_driver_semaphore_id [USBH_HC_NUM];

#ifdef  RTE_USB_Host_0
osSemaphoreDef (usbh0_driver_semaphore_def);
#endif
#ifdef  RTE_USB_Host_1
osSemaphoreDef (usbh1_driver_semaphore_def);
#endif
#ifdef  RTE_USB_Host_2
osSemaphoreDef (usbh2_driver_semaphore_def);
#endif
#ifdef  RTE_USB_Host_3
osSemaphoreDef (usbh3_driver_semaphore_def);
#endif

const osSemaphoreDef_t * const usbh_driver_semaphore_def_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        osSemaphore(usbh0_driver_semaphore_def)
#endif
#ifdef  RTE_USB_Host_1
      , osSemaphore(usbh1_driver_semaphore_def)
#endif
#ifdef  RTE_USB_Host_2
      , osSemaphore(usbh2_driver_semaphore_def)
#endif
#ifdef  RTE_USB_Host_3
      , osSemaphore(usbh3_driver_semaphore_def)
#endif
};

extern  void USBH_ConnectDebounce (void const * arg);

#ifdef  RTE_USB_Host_0
osTimerDef (USBH_DebounceTimer0, USBH_ConnectDebounce);
#endif
#ifdef  RTE_USB_Host_1
osTimerDef (USBH_DebounceTimer1, USBH_ConnectDebounce);
#endif
#ifdef  RTE_USB_Host_2
osTimerDef (USBH_DebounceTimer2, USBH_ConnectDebounce);
#endif
#ifdef  RTE_USB_Host_3
osTimerDef (USBH_DebounceTimer3, USBH_ConnectDebounce);
#endif

const   osTimerDef_t * const usbh_debounce_timer_def_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        osTimer(USBH_DebounceTimer0)
#endif
#ifdef  RTE_USB_Host_1
      , osTimer(USBH_DebounceTimer1)
#endif
#ifdef  RTE_USB_Host_2
      , osTimer(USBH_DebounceTimer2)
#endif
#ifdef  RTE_USB_Host_3
      , osTimer(USBH_DebounceTimer3)
#endif
};
osTimerId usbh_debounce_timer_id[USBH_HC_NUM];

extern  void USBH_SignalPortEvent       (uint8_t ctrl, uint8_t port, uint32_t event);
extern  void USBH_SignalPipeEvent       (uint8_t ctrl, ARM_USBH_EP_HANDLE ep_hndl, uint32_t event);
#ifdef  RTE_USB_Host_0
        void USBH0_SignalPortEvent      (uint8_t port, uint32_t event)                      { USBH_SignalPortEvent (0, port, event);      }
        void USBH0_SignalPipeEvent      (ARM_USBH_PIPE_HANDLE pipe_hndl, uint32_t event)    { USBH_SignalPipeEvent (0, pipe_hndl, event); }
#endif
#ifdef  RTE_USB_Host_1
        void USBH1_SignalPortEvent      (uint8_t port, uint32_t event)                      { USBH_SignalPortEvent (1, port, event);      }
        void USBH1_SignalPipeEvent      (ARM_USBH_PIPE_HANDLE pipe_hndl, uint32_t event)    { USBH_SignalPipeEvent (1, pipe_hndl, event); }
#endif
#ifdef  RTE_USB_Host_2
        void USBH2_SignalPortEvent      (uint8_t port, uint32_t event)                      { USBH_SignalPortEvent (2, port, event);      }
        void USBH2_SignalPipeEvent      (ARM_USBH_PIPE_HANDLE pipe_hndl, uint32_t event)    { USBH_SignalPipeEvent (2, pipe_hndl, event); }
#endif
#ifdef  RTE_USB_Host_3
        void USBH3_SignalPortEvent      (uint8_t port, uint32_t event)                      { USBH_SignalPortEvent (3, port, event);      }
        void USBH3_SignalPipeEvent      (ARM_USBH_PIPE_HANDLE pipe_hndl, uint32_t event)    { USBH_SignalPipeEvent (3, pipe_hndl, event); }
#endif

#if    (USBH_HC_NUM)
        ARM_USBH_SignalPortEvent_t const usbh_cb_port_event_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        USBH0_SignalPortEvent
#endif
#ifdef  RTE_USB_Host_1
      , USBH1_SignalPortEvent
#endif
#ifdef  RTE_USB_Host_2
      , USBH2_SignalPortEvent
#endif
#ifdef  RTE_USB_Host_3
      , USBH3_SignalPortEvent
#endif
};

        ARM_USBH_SignalPipeEvent_t const usbh_cb_pipe_event_ptr[USBH_HC_NUM] = {
#ifdef  RTE_USB_Host_0
        USBH0_SignalPipeEvent
#endif
#ifdef  RTE_USB_Host_1
      , USBH1_SignalPipeEvent
#endif
#ifdef  RTE_USB_Host_2
      , USBH2_SignalPipeEvent
#endif
#ifdef  RTE_USB_Host_3
      , USBH3_SignalPipeEvent
#endif
};

        ARM_DRIVER_VERSION      usbh_drv_version [USBH_HC_NUM] = { 0 };
        ARM_USBH_CAPABILITIES   usbh_capabilities[USBH_HC_NUM] = { 0 };

        USBH_HCI                usbh_hci [USBH_HC_NUM]  = { 0 };
#endif

        USBH_DEV                usbh_dev [USBH_DEV_NUM] = { 0 };

#if    (USBH_MSC_NUM)
        USBH_MSC                usbh_msc [USBH_MSC_NUM] = { 0 };
#else
uint8_t   USBH_MSC_Configure    (const USBH_DEV *ptr_dev, const USB_DEVICE_DESCRIPTOR *ptr_dev_desc, const USB_CONFIGURATION_DESCRIPTOR *ptr_cfg_desc) { return 0xFF; }
usbStatus USBH_MSC_Unconfigure  (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_MSC_Initialize   (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_MSC_Uninitialize (uint8_t instance) { return usbDeviceError; }
#endif

#if    (USBH_HID_NUM)
#ifdef  USBH0_HID_THREAD_STACK_SIZE
#define USBH_HID_INT_IN_THREAD_STACK_SIZE             USBH0_HID_THREAD_STACK_SIZE
#endif
#ifndef USBH_HID_INT_IN_THREAD_STACK_SIZE
#define USBH_HID_INT_IN_THREAD_STACK_SIZE             512
#endif
#ifdef  USBH0_HID_THREAD_PRIORITY
#define USBH_HID_INT_IN_THREAD_PRIORITY               USBH0_HID_THREAD_PRIORITY
#endif
#ifndef USBH_HID_INT_IN_THREAD_PRIORITY
#define USBH_HID_INT_IN_THREAD_PRIORITY               osPriorityAboveNormal
#endif
        USBH_HID                usbh_hid [USBH_HID_NUM] = { 0 };
extern void USBH_HID_IntIn_Thread (void const *arg);
osThreadDef(USBH_HID_IntIn_Thread, USBH_HID_INT_IN_THREAD_PRIORITY, USBH_HID_NUM, USBH_HID_INT_IN_THREAD_STACK_SIZE);
const osThreadDef_t * const usbh_hid_int_in_thread_def_ptr  = osThread(USBH_HID_IntIn_Thread);
#else
uint8_t   USBH_HID_Configure    (const USBH_DEV *ptr_dev, const USB_DEVICE_DESCRIPTOR *ptr_dev_desc, const USB_CONFIGURATION_DESCRIPTOR *ptr_cfg_desc) { return 0xFF; }
usbStatus USBH_HID_Unconfigure  (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_HID_Initialize   (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_HID_Uninitialize (uint8_t instance) { return usbDeviceError; }
#endif

#if    (USBH_CDC_NUM)
        USBH_CDC                usbh_cdc [USBH_CDC_NUM] = { 0 };
extern void USBH_CDC_IntIn_Thread   (void const *arg);
osThreadDef(USBH_CDC_IntIn_Thread, USBH_CDC_INT_IN_THREAD_PRIORITY, USBH_CDC_NUM, USBH_CDC_INT_IN_THREAD_STACK_SIZE);
const osThreadDef_t * const usbh_cdc_int_in_thread_def_ptr   = osThread(USBH_CDC_IntIn_Thread);
#else
uint8_t   USBH_CDC_Configure        (const USBH_DEV *ptr_dev, const USB_DEVICE_DESCRIPTOR *ptr_dev_desc, const USB_CONFIGURATION_DESCRIPTOR *ptr_cfg_desc) { return 0xFF; }
usbStatus USBH_CDC_Unconfigure      (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_CDC_Initialize       (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_CDC_Uninitialize     (uint8_t instance) { return usbDeviceError; }
#endif

#if    (!USBH_CUSTOM_CLASS_NUM)
uint8_t   USBH_CustomClass_Configure    (const USBH_DEV *ptr_dev, const USB_DEVICE_DESCRIPTOR *ptr_dev_desc, const USB_CONFIGURATION_DESCRIPTOR *ptr_cfg_desc) { return 0xFF; }
usbStatus USBH_CustomClass_Unconfigure  (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_CustomClass_Initialize   (uint8_t instance) { return usbDeviceError; }
usbStatus USBH_CustomClass_Uninitialize (uint8_t instance) { return usbDeviceError; }
#endif
#endif

#pragma pop
