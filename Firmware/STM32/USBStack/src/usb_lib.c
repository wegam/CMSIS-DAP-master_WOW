/*------------------------------------------------------------------------------
 *      RL-ARM - USB
 *------------------------------------------------------------------------------
 *      Name:    usb_lib.c
 *      Purpose: System Configuration
 *      Rev.:    V4.71
 *------------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "RTL.h"
#include "rl_usb.h"
//#include <..\..\RL\USB\INC\usb.h>
#include "usb.h"
//#include "usb_lib.h"

#pragma thumb
#pragma O3


/*------------------------------------------------------------------------------
 *      Library for usb_config.c
 *----------------------------------------------------------------------------*/

#ifdef  __USB_CONFIG__


/*------------------------------------------------------------------------------
 *      USB Host Configuration
 *----------------------------------------------------------------------------*/

#if    (USBH0_ENABLE || USBH1_ENABLE)
                                        /* Prepare constants                  */
#define USBH_HC_NUM       (1 + USBH1_ENABLE)
#define USBH_HC_MSK       (((USBH1_ENABLE & 1) << 1) | (USBH0_ENABLE & 1))
#define USBH_OHCI_NUM     (1 + (USBH1_ENABLE * (USBH1_HC_IF == 1)))
#define USBH_EHCI_NXP_NUM (1 + (USBH1_ENABLE * (USBH1_HC_IF == 2)))
#define USBH_DCD_NUM      (((USBH_CLASS & 0x01) == 0x01) + ((USBH_CLASS & 0x02) == 0x02) + ((USBH_CLASS & 0x04) == 0x04))

#if    (USBH0_ENABLE)
#if    (USBH0_HC_IF == 1)
extern  USBH_HCD         usbh0_hcd_ohci;
extern  USBH_HWD_OHCI    usbh0_hwd_ohci;
#define USBH0_HCD       &usbh0_hcd_ohci
#define USBH0_HWD_OHCI  &usbh0_hwd_ohci
#elif  (USBH0_HC_IF == 2)
extern  USBH_HCD         usbh0_hcd_ehci_NXP;
extern  USBH_HWD_EHCI    usbh0_hwd_ehci_NXP;
#define USBH0_HCD       &usbh0_hcd_ehci_NXP
#define USBH0_HWD_EHCI  &usbh0_hwd_ehci_NXP
#else
extern  USBH_HCD         usbh0_hcd;
#define USBH0_HCD       &usbh0_hcd
#endif
#else
#define USBH0_HCD        NULL
#endif

#if    (USBH1_ENABLE)
#if    (USBH1_HC_IF == 1)
extern  USBH_HCD         usbh1_hcd_ohci;
extern  USBH1_HWD_OHCI   usbh1_hwd_ohci;
#define USBH1_HCD       &usbh1_hcd_ohci
#define USBH1_HWD_OHCI  &usbh1_hwd_ohci
#elif  (USBH1_HC_IF == 2)
extern  USBH_HCD         usbh1_hcd_ehci_NXP;
extern  USBH_HWD_EHCI    usbh1_hwd_ehci_NXP;
#define USBH1_HCD       &usbh1_hcd_ehci_NXP
#define USBH1_HWD_EHCI  &usbh1_hwd_ehci_NXP
#else
extern  USBH_HCD         usbh1_hcd;
#define USBH1_HCD       &usbh1_hcd
#endif
#else
#define USBH1_HCD        NULL
#endif

                                        /* Define constants                   */
const U8  usbh_hc_num          = USBH_HC_NUM;
const U8  usbh_hc_msk          = USBH_HC_MSK;
const U8  usbh_ohci_num        = USBH_OHCI_NUM;
const U8  usbh_ehci_NXP_num    = USBH_EHCI_NXP_NUM;
const U8  usbh_dcd_num         = USBH_DCD_NUM;
const U8  usbh_msc_num         = USBH_MSC_NUM;
const U8  usbh_hid_num         = USBH_HID_NUM;
const U8  usbh_cls_num         = USBH_CLS_NUM;

                                        /* Register Drivers                   */
USBH_HCD *usbh_hcd_ptr[USBH_HC_NUM] = { /* Register Host Controller Drivers   */
#if    (USBH0_ENABLE)
                         USBH0_HCD,
#else
                         NULL,
#endif
#if    (USBH1_ENABLE)
                         USBH1_HCD   
#endif
                       };

#if   ((USBH0_ENABLE && (USBH0_HC_IF == 1)) || (USBH1_ENABLE && (USBH1_HC_IF == 1)))
USBH_HWD_OHCI *usbh_hwd_ohci_ptr[USBH_OHCI_NUM] = { /* Register OHCI Hw Driver*/
#if    (USBH0_ENABLE && (USBH0_HC_IF == 1))
                         USBH0_HWD_OHCI,
#else
                         NULL,
#endif
#if    (USBH1_ENABLE && (USBH1_HC_IF == 1))
                         USBH1_HWD_OHCI   
#endif
                       };
#endif

#if   ((USBH0_ENABLE && (USBH0_HC_IF == 2)) || (USBH1_ENABLE && (USBH1_HC_IF == 2)))
                                        /* Register NXP EHCI Hw Driver        */
USBH_HWD_EHCI *usbh_hwd_ehci_NXP_ptr[USBH_EHCI_NXP_NUM] = { 
#if    (USBH0_ENABLE && (USBH0_HC_IF == 2))
                         USBH0_HWD_EHCI,
#else
                         NULL,
#endif
#if    (USBH1_ENABLE && (USBH1_HC_IF == 2))
                         USBH1_HWD_EHCI   
#endif
                       };
#endif

#if    (USBH_CLASS & 0x01) && (USBH_MSC_NUM)
extern  USBH_DCD         usbh_dcd_msc;
#endif
#if    (USBH_CLASS & 0x02) && (USBH_HID_NUM)
extern  USBH_DCD         usbh_dcd_hid;
#endif
#if    (USBH_CLASS & 0x04) && (USBH_CLS_NUM)
extern  USBH_DCD         usbh_dcd_cls;
#endif
USBH_DCD *usbh_dcd_ptr[USBH_DCD_NUM] = {/* Register Class Drivers             */
#if    (USBH_CLASS & 0x01) && (USBH_MSC_NUM)
                        &usbh_dcd_msc,
#endif
#if    (USBH_CLASS & 0x02) && (USBH_HID_NUM)
                        &usbh_dcd_hid,
#endif
#if    (USBH_CLASS & 0x04) && (USBH_CLS_NUM)
                        &usbh_dcd_cls,
#endif
                      };

USBH_HCI usbh_hci    [USBH_HC_NUM]  = { 0 };
#if    (USBH_CLASS & 0x01) && (USBH_MSC_NUM)
USBH_DCI usbh_dci_msc[USBH_HC_NUM * USBH_MSC_NUM] = { 0 };
USBH_MSC usbh_msc    [USBH_HC_NUM * USBH_MSC_NUM] = { 0 };
#endif
#if    (USBH_CLASS & 0x02) && (USBH_HID_NUM)
USBH_DCI usbh_dci_hid[USBH_HC_NUM * USBH_HID_NUM] = { 0 };
USBH_HID usbh_hid    [USBH_HC_NUM * USBH_HID_NUM] = { 0 };
#endif
#if    (USBH_CLASS & 0x04) && (USBH_CLS_NUM)
USBH_DCI usbh_dci_cls[USBH_HC_NUM * USBH_CLS_NUM] = { 0 };
USBH_HID usbh_cls    [USBH_HC_NUM * USBH_CLS_NUM] = { 0 };
#endif

USBH_DCI *usbh_dci_ptr[3] = {
#if    (USBH_CLASS & 0x01) && (USBH_MSC_NUM)
  usbh_dci_msc,
#else
  NULL,
#endif
#if    (USBH_CLASS & 0x02) && (USBH_HID_NUM)
  usbh_dci_hid,
#else
  NULL,
#endif
#if    (USBH_CLASS & 0x04) && (USBH_CLS_NUM)
  usbh_dci_cls,
#else
  NULL,
#endif
};
#endif


/*------------------------------------------------------------------------------
 *      USB Device Configuration
 *----------------------------------------------------------------------------*/

#if    (USBD_ENABLE)

        U8   USBD_AltSetting[USBD_IF_NUM];
        U8   USBD_EP0Buf    [USBD_MAX_PACKET0];
const   U8   usbd_power                 =  USBD_POWER;
const   U8   usbd_hs_enable             =  USBD_HS_ENABLE;
const   U16  usbd_if_num                =  USBD_IF_NUM;
const   U8   usbd_ep_num                =  USBD_EP_NUM;
const   U8   usbd_max_packet0           =  USBD_MAX_PACKET0;


/*------------------------------------------------------------------------------
 *      USB Device Class Configuration
 *----------------------------------------------------------------------------*/

#if    (!USBD_HID_BINTERVAL)
  #define USBD_HID_INTERVAL                1
#else 
  #define USBD_HID_INTERVAL                USBD_HID_BINTERVAL
#endif
#if    (!USBD_HID_HS_BINTERVAL)
  #define USBD_HID_HS_INTERVAL             1
#else 
  #define USBD_HID_HS_INTERVAL            (2 << ((USBD_HID_HS_BINTERVAL & 0x0F)-1))
#endif

#if    (USBD_HID_ENABLE)
const   U8   usbd_hid_if_num            =  USBD_HID_IF_NUM;
const   U8   usbd_hid_ep_intin          =  USBD_HID_EP_INTIN;
const   U8   usbd_hid_ep_intout         =  USBD_HID_EP_INTOUT;
const   U16  usbd_hid_interval     [2]  = {USBD_HID_INTERVAL,       USBD_HID_HS_INTERVAL};
const   U16  usbd_hid_maxpacketsize[2]  = {USBD_HID_WMAXPACKETSIZE, USBD_HID_HS_WMAXPACKETSIZE};
const   U8   usbd_hid_inreport_num      =  USBD_HID_INREPORT_NUM;
const   U8   usbd_hid_outreport_num     =  USBD_HID_OUTREPORT_NUM;
const   U16  usbd_hid_inreport_max_sz   =  USBD_HID_INREPORT_MAX_SZ;
const   U16  usbd_hid_outreport_max_sz  =  USBD_HID_OUTREPORT_MAX_SZ;
const   U16  usbd_hid_featreport_max_sz =  USBD_HID_FEATREPORT_MAX_SZ;
        U16  USBD_HID_PollingCnt;
        U8   USBD_HID_IdleCnt             [USBD_HID_INREPORT_NUM];
        U8   USBD_HID_IdleReload          [USBD_HID_INREPORT_NUM];
        U8   USBD_HID_IdleSet             [USBD_HID_INREPORT_NUM];
        U8   USBD_HID_InReport            [USBD_HID_INREPORT_MAX_SZ+1];
        U8   USBD_HID_OutReport           [USBD_HID_OUTREPORT_MAX_SZ+1];
        U8   USBD_HID_FeatReport          [USBD_HID_FEATREPORT_MAX_SZ+1];
#endif

//#if    (USBD_MSC_ENABLE)			//USBD_MSC_ENABLE==0时如不注释掉#if则会编译报错，除非把usbd_msc.c和usbd_core_msc.c移除
const   U8   usbd_msc_if_num            =  USBD_MSC_IF_NUM;
const   U8   usbd_msc_ep_bulkin         =  USBD_MSC_EP_BULKIN;
const   U8   usbd_msc_ep_bulkout        =  USBD_MSC_EP_BULKOUT;
const   U16  usbd_msc_maxpacketsize[2]  = {USBD_MSC_WMAXPACKETSIZE, USBD_MSC_HS_WMAXPACKETSIZE};
const   U8  *usbd_msc_inquiry_data      =  USBD_MSC_INQUIRY_DATA;
#if    (USBD_MSC_ENABLE)
        U8   USBD_MSC_BulkBuf             [USBD_MSC_MAX_PACKET*USBD_MSC_ENABLE];
#endif
//#endif

#if    (USBD_ADC_ENABLE)
const   U8   usbd_adc_cif_num           =  USBD_ADC_CIF_NUM;
const   U8   usbd_adc_sif1_num          =  USBD_ADC_SIF1_NUM;
const   U8   usbd_adc_sif2_num          =  USBD_ADC_SIF2_NUM;
const   U8   usbd_adc_ep_isoout         =  USBD_ADC_EP_ISOOUT;
const   U32  usbd_adc_cfg_datafreq      =  USBD_ADC_TSAMFREQ;
const   U32  usbd_adc_cfg_p_s           =  USBD_ADC_CFG_P_S;
const   U32  usbd_adc_cfg_p_c           =  USBD_ADC_CFG_P_C;
const   U32  usbd_adc_cfg_b_s           =  (8*USBD_ADC_CFG_P_C*USBD_ADC_CFG_P_S);
        S16  USBD_ADC_DataBuf              [8*USBD_ADC_CFG_P_C*USBD_ADC_CFG_P_S];
#endif

#ifndef USBD_CDC_ACM_ENABLE
#if    (USBD_CDC_ENABLE == 1)
#error "Please update usb_config.c file with new definitions for CDC, as new CDC is incompatible with the old one!"
#else
#define USBD_CDC_ACM_ENABLE  0
#endif
#endif

#if    (USBD_CDC_ACM_ENABLE)
const   U8   usbd_cdc_acm_cif_num       =  USBD_CDC_ACM_CIF_NUM;
const   U8   usbd_cdc_acm_dif_num       =  USBD_CDC_ACM_DIF_NUM;
const   U8   usbd_cdc_acm_ep_intin      =  USBD_CDC_ACM_EP_INTIN;
const   U8   usbd_cdc_acm_ep_bulkin     =  USBD_CDC_ACM_EP_BULKIN;
const   U8   usbd_cdc_acm_ep_bulkout    =  USBD_CDC_ACM_EP_BULKOUT;
const   U16  usbd_cdc_acm_sendbuf_sz    =  USBD_CDC_ACM_SENDBUF_SIZE;
const   U16  usbd_cdc_acm_receivebuf_sz =  USBD_CDC_ACM_RECEIVEBUF_SIZE;
const   U16  usbd_cdc_acm_maxpacketsize [2] = {USBD_CDC_ACM_WMAXPACKETSIZE,  USBD_CDC_ACM_HS_WMAXPACKETSIZE};
const   U16  usbd_cdc_acm_maxpacketsize1[2] = {USBD_CDC_ACM_WMAXPACKETSIZE1, USBD_CDC_ACM_HS_WMAXPACKETSIZE1};
        U8   USBD_CDC_ACM_SendBuf         [USBD_CDC_ACM_SENDBUF_SIZE];
        U8   USBD_CDC_ACM_ReceiveBuf      [USBD_CDC_ACM_RECEIVEBUF_SIZE];
        U8   USBD_CDC_ACM_NotifyBuf       [10];
#endif

/*------------------------------------------------------------------------------
 *      USB Device Override Event Handler Fuctions
 *----------------------------------------------------------------------------*/

#if    (USBD_HID_ENABLE)
  #ifndef __RTX
		void USBD_Configure_Event (void)             { USBD_HID_Configure_Event (); }
  #endif
  #ifdef __RTX
    #if   ((USBD_HID_EP_INTOUT != 0) && (USBD_HID_EP_INTIN != USBD_HID_EP_INTOUT))
      #if    (USBD_HID_EP_INTIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_HID_EP_INTIN_Event
      #endif

      #if    (USBD_HID_EP_INTOUT == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_HID_EP_INTOUT_Event
      #endif
    #elif    (USBD_HID_EP_INTOUT != 0)
      #if    (USBD_HID_EP_INTIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_HID_EP_INT_Event
      #endif
    #else
      #if    (USBD_HID_EP_INTIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_HID_EP_INTIN_Event
      #endif
    #endif
  #else
    #if   ((USBD_HID_EP_INTOUT != 0) && (USBD_HID_EP_INTIN != USBD_HID_EP_INTOUT))
      #if    (USBD_HID_EP_INTIN == 1)
        #define USBD_EndPoint1                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 2)
        #define USBD_EndPoint2                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 3)
        #define USBD_EndPoint3                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 4)
        #define USBD_EndPoint4                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 5)
        #define USBD_EndPoint5                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 6)
        #define USBD_EndPoint6                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 7)
        #define USBD_EndPoint7                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 8)
        #define USBD_EndPoint8                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 9)
        #define USBD_EndPoint9                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 10)
        #define USBD_EndPoint10                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 11)
        #define USBD_EndPoint11                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 12)
        #define USBD_EndPoint12                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 13)
        #define USBD_EndPoint13                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 14)
        #define USBD_EndPoint14                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 15)
        #define USBD_EndPoint15                USBD_HID_EP_INTIN_Event
      #endif

      #if    (USBD_HID_EP_INTOUT == 1)
        #define USBD_EndPoint1                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 2)
        #define USBD_EndPoint2                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 3)
        #define USBD_EndPoint3                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 4)
        #define USBD_EndPoint4                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 5)
        #define USBD_EndPoint5                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 6)
        #define USBD_EndPoint6                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 7)
        #define USBD_EndPoint7                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 8)
        #define USBD_EndPoint8                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 9)
        #define USBD_EndPoint9                 USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 10)
        #define USBD_EndPoint10                USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 11)
        #define USBD_EndPoint11                USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 12)
        #define USBD_EndPoint12                USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 13)
        #define USBD_EndPoint13                USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 14)
        #define USBD_EndPoint14                USBD_HID_EP_INTOUT_Event
      #elif  (USBD_HID_EP_INTOUT == 15)
        #define USBD_EndPoint15                USBD_HID_EP_INTOUT_Event
      #endif
    #elif    (USBD_HID_EP_INTOUT != 0)
      #if    (USBD_HID_EP_INTIN == 1)
        #define USBD_EndPoint1                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 2)
        #define USBD_EndPoint2                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 3)
        #define USBD_EndPoint3                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 4)
        #define USBD_EndPoint4                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 5)
        #define USBD_EndPoint5                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 6)
        #define USBD_EndPoint6                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 7)
        #define USBD_EndPoint7                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 8)
        #define USBD_EndPoint8                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 9)
        #define USBD_EndPoint9                 USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 10)
        #define USBD_EndPoint10                USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 11)
        #define USBD_EndPoint11                USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 12)
        #define USBD_EndPoint12                USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 13)
        #define USBD_EndPoint13                USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 14)
        #define USBD_EndPoint14                USBD_HID_EP_INT_Event
      #elif  (USBD_HID_EP_INTIN == 15)
        #define USBD_EndPoint15                USBD_HID_EP_INT_Event
      #endif
    #else
      #if    (USBD_HID_EP_INTIN == 1)
        #define USBD_EndPoint1                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 2)
        #define USBD_EndPoint2                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 3)
        #define USBD_EndPoint3                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 4)
        #define USBD_EndPoint4                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 5)
        #define USBD_EndPoint5                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 6)
        #define USBD_EndPoint6                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 7)
        #define USBD_EndPoint7                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 8)
        #define USBD_EndPoint8                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 9)
        #define USBD_EndPoint9                 USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 10)
        #define USBD_EndPoint10                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 11)
        #define USBD_EndPoint11                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 12)
        #define USBD_EndPoint12                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 13)
        #define USBD_EndPoint13                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 14)
        #define USBD_EndPoint14                USBD_HID_EP_INTIN_Event
      #elif  (USBD_HID_EP_INTIN == 15)
        #define USBD_EndPoint15                USBD_HID_EP_INTIN_Event
      #endif
    #endif
  #endif
#else
  BOOL USBD_ReqGetDescriptor_HID          (U8 **pD, U32 *len)		{ return (__FALSE); }	//HID描述符，包括设备描述符，报告描述符，物理特性描述符
  BOOL USBD_EndPoint0_Setup_HID_ReqToIF   (void)             		{ return (__FALSE); }
  BOOL USBD_EndPoint0_Out_HID_ReqToIF     (void)               	{ return (__FALSE); }
#endif  /* (USBD_HID_ENABLE) */

#if    (USBD_MSC_ENABLE)
  #ifdef __RTX
    #if    (USBD_MSC_EP_BULKIN != USBD_MSC_EP_BULKOUT)
      #if    (USBD_MSC_EP_BULKIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_MSC_EP_BULKIN_Event
      #endif
    
      #if    (USBD_MSC_EP_BULKOUT == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_MSC_EP_BULKOUT_Event
      #endif
    #else
      #if    (USBD_MSC_EP_BULKIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_MSC_EP_BULK_Event
      #endif
    #endif
  #else
    #if    (USBD_MSC_EP_BULKIN != USBD_MSC_EP_BULKOUT)
      #if    (USBD_MSC_EP_BULKIN == 1)
        #define USBD_EndPoint1                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 2)
        #define USBD_EndPoint2                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 3)
        #define USBD_EndPoint3                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 4)
        #define USBD_EndPoint4                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 5)
        #define USBD_EndPoint5                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 6)
        #define USBD_EndPoint6                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 7)
        #define USBD_EndPoint7                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 8)
        #define USBD_EndPoint8                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 9)
        #define USBD_EndPoint9                 USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 10)
        #define USBD_EndPoint10                USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 11)
        #define USBD_EndPoint11                USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 12)
        #define USBD_EndPoint12                USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 13)
        #define USBD_EndPoint13                USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 14)
        #define USBD_EndPoint14                USBD_MSC_EP_BULKIN_Event
      #elif  (USBD_MSC_EP_BULKIN == 15)
        #define USBD_EndPoint15                USBD_MSC_EP_BULKIN_Event
      #endif
    
      #if    (USBD_MSC_EP_BULKOUT == 1)
        #define USBD_EndPoint1                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 2)
        #define USBD_EndPoint2                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 3)
        #define USBD_EndPoint3                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 4)
        #define USBD_EndPoint4                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 5)
        #define USBD_EndPoint5                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 6)
        #define USBD_EndPoint6                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 7)
        #define USBD_EndPoint7                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 8)
        #define USBD_EndPoint8                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 9)
        #define USBD_EndPoint9                 USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 10)
        #define USBD_EndPoint10                USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 11)
        #define USBD_EndPoint11                USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 12)
        #define USBD_EndPoint12                USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 13)
        #define USBD_EndPoint13                USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 14)
        #define USBD_EndPoint14                USBD_MSC_EP_BULKOUT_Event
      #elif  (USBD_MSC_EP_BULKOUT == 15)
        #define USBD_EndPoint15                USBD_MSC_EP_BULKOUT_Event
      #endif
    #else
      #if    (USBD_MSC_EP_BULKIN == 1)
        #define USBD_EndPoint1                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 2)
        #define USBD_EndPoint2                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 3)
        #define USBD_EndPoint3                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 4)
        #define USBD_EndPoint4                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 5)
        #define USBD_EndPoint5                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 6)
        #define USBD_EndPoint6                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 7)
        #define USBD_EndPoint7                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 8)
        #define USBD_EndPoint8                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 9)
        #define USBD_EndPoint9                 USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 10)
        #define USBD_EndPoint10                USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 11)
        #define USBD_EndPoint11                USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 12)
        #define USBD_EndPoint12                USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 13)
        #define USBD_EndPoint13                USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 14)
        #define USBD_EndPoint14                USBD_MSC_EP_BULK_Event
      #elif  (USBD_MSC_EP_BULKIN == 15)
        #define USBD_EndPoint15                USBD_MSC_EP_BULK_Event
      #endif
    #endif
  #endif
#else
  void USBD_ReqClrFeature_MSC             (U32 EPNum)                                   { }
  BOOL USBD_EndPoint0_Setup_MSC_ReqToIF   (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_MSC_ReqToIF     (void)                                        { return (__FALSE); }
#endif  /* (USBD_MSC_ENABLE) */

#if    (USBD_ADC_ENABLE == 0)
  BOOL USBD_EndPoint0_Setup_ADC_ReqToIF   (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Setup_ADC_ReqToEP   (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_ADC_ReqToIF     (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_ADC_ReqToEP     (void)                                        { return (__FALSE); }
#endif  /* (USBD_MSC_ENABLE) */

#if    (USBD_CDC_ACM_ENABLE)
  #ifdef __RTX
    #if    (USBD_CDC_ACM_EP_INTIN == 1)
      #define USBD_RTX_EndPoint1               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 2)
      #define USBD_RTX_EndPoint2               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 3)
      #define USBD_RTX_EndPoint3               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 4)
      #define USBD_RTX_EndPoint4               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 5)
      #define USBD_RTX_EndPoint5               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 6)
      #define USBD_RTX_EndPoint6               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 7)
      #define USBD_RTX_EndPoint7               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 8)
      #define USBD_RTX_EndPoint8               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 9)
      #define USBD_RTX_EndPoint9               USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 10)
      #define USBD_RTX_EndPoint10              USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 11)
      #define USBD_RTX_EndPoint11              USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 12)
      #define USBD_RTX_EndPoint12              USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 13)
      #define USBD_RTX_EndPoint13              USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 14)
      #define USBD_RTX_EndPoint14              USBD_RTX_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 15)
      #define USBD_RTX_EndPoint15              USBD_RTX_CDC_ACM_EP_INTIN_Event
    #endif
  #else
    #if    (USBD_CDC_ACM_EP_INTIN == 1)
      #define USBD_EndPoint1                   USBD_CDC_ACM_EP_INTIN_Event		//空函数
    #elif  (USBD_CDC_ACM_EP_INTIN == 2)
      #define USBD_EndPoint2                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 3)
      #define USBD_EndPoint3                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 4)
      #define USBD_EndPoint4                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 5)
      #define USBD_EndPoint5                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 6)
      #define USBD_EndPoint6                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 7)
      #define USBD_EndPoint7                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 8)
      #define USBD_EndPoint8                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 9)
      #define USBD_EndPoint9                   USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 10)
      #define USBD_EndPoint10                  USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 11)
      #define USBD_EndPoint11                  USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 12)
      #define USBD_EndPoint12                  USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 13)
      #define USBD_EndPoint13                  USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 14)
      #define USBD_EndPoint14                  USBD_CDC_ACM_EP_INTIN_Event
    #elif  (USBD_CDC_ACM_EP_INTIN == 15)
      #define USBD_EndPoint15                  USBD_CDC_ACM_EP_INTIN_Event
    #endif
  #endif

  #ifdef __RTX
    #if    (USBD_CDC_ACM_EP_BULKIN != USBD_CDC_ACM_EP_BULKOUT)
      #if    (USBD_CDC_ACM_EP_BULKIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_CDC_ACM_EP_BULKIN_Event
      #endif
    
      #if    (USBD_CDC_ACM_EP_BULKOUT == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_CDC_ACM_EP_BULKOUT_Event
      #endif
    #else
      #if    (USBD_CDC_ACM_EP_BULKIN == 1)
        #define USBD_RTX_EndPoint1             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 2)
        #define USBD_RTX_EndPoint2             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 3)
        #define USBD_RTX_EndPoint3             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 4)
        #define USBD_RTX_EndPoint4             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 5)
        #define USBD_RTX_EndPoint5             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 6)
        #define USBD_RTX_EndPoint6             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 7)
        #define USBD_RTX_EndPoint7             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 8)
        #define USBD_RTX_EndPoint8             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 9)
        #define USBD_RTX_EndPoint9             USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 10)
        #define USBD_RTX_EndPoint10            USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 11)
        #define USBD_RTX_EndPoint11            USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 12)
        #define USBD_RTX_EndPoint12            USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 13)
        #define USBD_RTX_EndPoint13            USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 14)
        #define USBD_RTX_EndPoint14            USBD_RTX_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 15)
        #define USBD_RTX_EndPoint15            USBD_RTX_CDC_ACM_EP_BULK_Event
      #endif
    #endif
  #else
    #if    (USBD_CDC_ACM_EP_BULKIN != USBD_CDC_ACM_EP_BULKOUT)
      #if    (USBD_CDC_ACM_EP_BULKIN == 1)
        #define USBD_EndPoint1                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 2)
        #define USBD_EndPoint2                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 3)
        #define USBD_EndPoint3                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 4)
        #define USBD_EndPoint4                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 5)
        #define USBD_EndPoint5                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 6)
        #define USBD_EndPoint6                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 7)
        #define USBD_EndPoint7                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 8)
        #define USBD_EndPoint8                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 9)
        #define USBD_EndPoint9                 USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 10)
        #define USBD_EndPoint10                USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 11)
        #define USBD_EndPoint11                USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 12)
        #define USBD_EndPoint12                USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 13)
        #define USBD_EndPoint13                USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 14)
        #define USBD_EndPoint14                USBD_CDC_ACM_EP_BULKIN_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 15)
        #define USBD_EndPoint15                USBD_CDC_ACM_EP_BULKIN_Event
      #endif
    
      #if    (USBD_CDC_ACM_EP_BULKOUT == 1)
        #define USBD_EndPoint1                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 2)
        #define USBD_EndPoint2                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 3)
        #define USBD_EndPoint3                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 4)
        #define USBD_EndPoint4                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 5)
        #define USBD_EndPoint5                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 6)
        #define USBD_EndPoint6                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 7)
        #define USBD_EndPoint7                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 8)
        #define USBD_EndPoint8                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 9)
        #define USBD_EndPoint9                 USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 10)
        #define USBD_EndPoint10                USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 11)
        #define USBD_EndPoint11                USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 12)
        #define USBD_EndPoint12                USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 13)
        #define USBD_EndPoint13                USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 14)
        #define USBD_EndPoint14                USBD_CDC_ACM_EP_BULKOUT_Event
      #elif  (USBD_CDC_ACM_EP_BULKOUT == 15)
        #define USBD_EndPoint15                USBD_CDC_ACM_EP_BULKOUT_Event
      #endif
    #else
      #if    (USBD_CDC_ACM_EP_BULKIN == 1)
        #define USBD_EndPoint1                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 2)
        #define USBD_EndPoint2                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 3)
        #define USBD_EndPoint3                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 4)
        #define USBD_EndPoint4                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 5)
        #define USBD_EndPoint5                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 6)
        #define USBD_EndPoint6                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 7)
        #define USBD_EndPoint7                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 8)
        #define USBD_EndPoint8                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 9)
        #define USBD_EndPoint9                 USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 10)
        #define USBD_EndPoint10                USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 11)
        #define USBD_EndPoint11                USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 12)
        #define USBD_EndPoint12                USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 13)
        #define USBD_EndPoint13                USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 14)
        #define USBD_EndPoint14                USBD_CDC_ACM_EP_BULK_Event
      #elif  (USBD_CDC_ACM_EP_BULKIN == 15)
        #define USBD_EndPoint15                USBD_CDC_ACM_EP_BULK_Event
      #endif
    #endif
  #endif
#else
  BOOL USBD_EndPoint0_Setup_CDC_ReqToIF(void)                                       { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_CDC_ReqToIF (void)                                        { return (__FALSE); }
#endif  /* (USBD_CDC_ACM_ENABLE) */

#if    (USBD_CLS_ENABLE)
#else
  BOOL USBD_EndPoint0_Setup_CLS_ReqToDEV  (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Setup_CLS_ReqToIF   (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Setup_CLS_ReqToEP   (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_CLS_ReqToDEV    (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_CLS_ReqToIF     (void)                                        { return (__FALSE); }
  BOOL USBD_EndPoint0_Out_CLS_ReqToEP     (void)                                        { return (__FALSE); }
#endif  /* (USBD_CLS_ENABLE) */

#if   ((USBD_CDC_ACM_ENABLE))
  #ifndef __RTX
  void USBD_Reset_Event (void)
	{ 
    #if    (USBD_CDC_ACM_ENABLE)
			USBD_CDC_ACM_Reset_Event ();		//复位串口为默认状态9600
    #endif
  }
  #endif
#endif  /* ((USBD_CDC_ACM_ENABLE)) */

#if   ((USBD_HID_ENABLE) || (USBD_ADC_ENABLE) || (USBD_CDC_ACM_ENABLE) || (USBD_CLS_ENABLE))
  #ifndef __RTX
  void USBD_SOF_Event (void)
	{ 
    #if    (USBD_HID_ENABLE)
    USBD_HID_SOF_Event     ();
    #endif
    #if    (USBD_ADC_ENABLE)
    USBD_ADC_SOF_Event     ();
    #endif
    #if    (USBD_CDC_ACM_ENABLE)
    USBD_CDC_ACM_SOF_Event ();
    #endif
    #if    (USBD_CLS_ENABLE)
    USBD_CLS_SOF_Event     ();
    #endif
  }
  #endif
#endif  /* ((USBD_HID_ENABLE) || (USBD_ADC_ENABLE) || (USBD_CDC_ACM_ENABLE) || (USBD_CLS_ENABLE)) */

/* USB Device - Device Events Callback Functions */
__weak   void USBD_Power_Event       (BOOL power);
__weak   void USBD_Reset_Event       (void); 				//复位串口为默认状态9600
__weak   void USBD_Suspend_Event     (void);
__weak   void USBD_Resume_Event      (void);				//空函数
__weak   void USBD_WakeUp_Event      (void);
__weak   void USBD_SOF_Event         (void);
__weak   void USBD_Error_Event       (U32 error);

/* USB Device - Device Events Callback Pointers */
void (* const USBD_P_Power_Event    )(BOOL power) = USBD_Power_Event;
void (* const USBD_P_Reset_Event    )(void)       = USBD_Reset_Event;			//复位串口为默认状态9600
void (* const USBD_P_Suspend_Event  )(void)       = USBD_Suspend_Event;		//空函数
void (* const USBD_P_Resume_Event   )(void)       = USBD_Resume_Event;		//空函数
void (* const USBD_P_WakeUp_Event   )(void)       = USBD_WakeUp_Event;		//空函数
void (* const USBD_P_SOF_Event      )(void)       = USBD_SOF_Event;
void (* const USBD_P_Error_Event    )(U32 error)  = USBD_Error_Event;

/* USB Device - Endpoint Events Callback Functions */
extern   void USBD_EndPoint0         (U32 event);
#ifndef       USBD_EndPoint1
__weak   void USBD_EndPoint1         (U32 event);
#endif
#ifndef       USBD_EndPoint2
__weak   void USBD_EndPoint2         (U32 event);
#endif
#ifndef       USBD_EndPoint3
__weak   void USBD_EndPoint3         (U32 event);
#endif
#ifndef       USBD_EndPoint4
__weak   void USBD_EndPoint4         (U32 event);
#endif
#ifndef       USBD_EndPoint5
__weak   void USBD_EndPoint5         (U32 event);
#endif
#ifndef       USBD_EndPoint6
__weak   void USBD_EndPoint6         (U32 event);
#endif
#ifndef       USBD_EndPoint7
__weak   void USBD_EndPoint7         (U32 event);
#endif
#ifndef       USBD_EndPoint8
__weak   void USBD_EndPoint8         (U32 event);
#endif
#ifndef       USBD_EndPoint9
__weak   void USBD_EndPoint9         (U32 event);
#endif
#ifndef       USBD_EndPoint10
__weak   void USBD_EndPoint10        (U32 event);
#endif
#ifndef       USBD_EndPoint11
__weak   void USBD_EndPoint11        (U32 event);
#endif
#ifndef       USBD_EndPoint12
__weak   void USBD_EndPoint12        (U32 event);
#endif
#ifndef       USBD_EndPoint13
__weak   void USBD_EndPoint13        (U32 event);
#endif
#ifndef       USBD_EndPoint14
__weak   void USBD_EndPoint14        (U32 event);
#endif
#ifndef       USBD_EndPoint15
__weak   void USBD_EndPoint15        (U32 event);
#endif

/* USB Device - Endpoint Events Callback Pointers */
void (* const USBD_P_EP[16])	(U32 event) = 
{
  USBD_EndPoint0,			//配置端点--USB配置--控制传输
  USBD_EndPoint1,			//CDC端点--空函数--中断传输										//void USBD_CDC_ACM_EP_INTIN_Event (uint32_t event)
//	USBD_CDC_ACM_EP_INTIN_Event,	//  USBD_EndPoint1								//Abstract Control Model
  USBD_EndPoint2,			//CDC输出端点--批量传输										//void USBD_CDC_ACM_EP_BULK_Event (uint32_t event)
//	USBD_CDC_ACM_EP_BULK_Event,	//USBD_EndPoint2
  USBD_EndPoint3,			//HID端点--空函数//数据的接收和发送处理--中断传输		//void USBD_HID_EP_INT_Event (U32 event)
//	USBD_HID_EP_INT_Event,	//USBD_EndPoint3
  USBD_EndPoint4,
//	USBD_MSC_EP_BULK_Event,		//USBD_EndPoint4,
  USBD_EndPoint5,
  USBD_EndPoint6,
  USBD_EndPoint7,
  USBD_EndPoint8,
  USBD_EndPoint9,
  USBD_EndPoint10,
  USBD_EndPoint11,
  USBD_EndPoint12,
  USBD_EndPoint13,
  USBD_EndPoint14,
  USBD_EndPoint15
};

/* USB Device - Core Events Callback Functions */
__weak   void USBD_Configure_Event   (void);
__weak   void USBD_Interface_Event   (void);
__weak   void USBD_Feature_Event     (void);

/* USB Device - Core Events Callback Pointers */
void (* const USBD_P_Configure_Event)(void)       = USBD_Configure_Event;		//USBD_HID_Configure_Event ();
void (* const USBD_P_Interface_Event)(void)       = USBD_Interface_Event;
void (* const USBD_P_Feature_Event  )(void)       = USBD_Feature_Event;

#ifdef __RTX
const BOOL __rtx = __TRUE;

#if   ((USBD_HID_ENABLE) || (USBD_ADC_ENABLE) || (USBD_CDC_ACM_ENABLE) || (USBD_CLS_ENABLE))
__weak __task void USBD_RTX_Device     (void)
{
  U16 evt;

  for (;;) 
	{
    os_evt_wait_or(0xFFFF, 0xFFFF);         /* Wait for an Event */
    evt = os_evt_get();                     /* Get Event Flags */

    if (evt & USBD_EVT_RESET) 
		{
			#if (USBD_CDC_ACM_ENABLE)
				USBD_CDC_ACM_Reset_Event ();
			#endif
    }

    if (evt & USBD_EVT_SOF)
		{
		#if (USBD_HID_ENABLE)
      USBD_HID_SOF_Event     ();
		#endif
		#if (USBD_ADC_ENABLE)
      USBD_ADC_SOF_Event     ();
		#endif
		#if (USBD_CDC_ACM_ENABLE)
      USBD_CDC_ACM_SOF_Event ();
		#endif
		#if (USBD_CLS_ENABLE)
      USBD_CLS_SOF_Event     ();
		#endif
    }
  }
}
#else
__weak __task void USBD_RTX_Device     (void);
#endif

/* USB Device - Device Events Callback Pointer */
void (* const USBD_RTX_P_Device)(void)= USBD_RTX_Device;

/* USB Device Endpoint Events Callback Functions */
extern __task void USBD_RTX_EndPoint0  (void);
#ifndef       USBD_RTX_EndPoint1
__weak __task void USBD_RTX_EndPoint1  (void);
#endif
#ifndef       USBD_RTX_EndPoint2
__weak __task void USBD_RTX_EndPoint2  (void);
#endif
#ifndef       USBD_RTX_EndPoint3
__weak __task void USBD_RTX_EndPoint3  (void);
#endif
#ifndef       USBD_RTX_EndPoint4
__weak __task void USBD_RTX_EndPoint4  (void);
#endif
#ifndef       USBD_RTX_EndPoint5
__weak __task void USBD_RTX_EndPoint5  (void);
#endif
#ifndef       USBD_RTX_EndPoint6
__weak __task void USBD_RTX_EndPoint6  (void);
#endif
#ifndef       USBD_RTX_EndPoint7
__weak __task void USBD_RTX_EndPoint7  (void);
#endif
#ifndef       USBD_RTX_EndPoint8
__weak __task void USBD_RTX_EndPoint8  (void);
#endif
#ifndef       USBD_RTX_EndPoint9
__weak __task void USBD_RTX_EndPoint9  (void);
#endif
#ifndef       USBD_RTX_EndPoint10
__weak __task void USBD_RTX_EndPoint10 (void);
#endif
#ifndef       USBD_RTX_EndPoint11
__weak __task void USBD_RTX_EndPoint11 (void);
#endif
#ifndef       USBD_RTX_EndPoint12
__weak __task void USBD_RTX_EndPoint12 (void);
#endif
#ifndef       USBD_RTX_EndPoint13
__weak __task void USBD_RTX_EndPoint13 (void);
#endif
#ifndef       USBD_RTX_EndPoint14
__weak __task void USBD_RTX_EndPoint14 (void);
#endif
#ifndef       USBD_RTX_EndPoint15
__weak __task void USBD_RTX_EndPoint15 (void);
#endif

#if    (USBD_HID_ENABLE)
__weak __task void USBD_RTX_Core       (void)
{
  U16 evt;
  for (;;) 
	{
    os_evt_wait_or(0xFFFF, 0xFFFF);         /* Wait for an Event */
    evt = os_evt_get();                     /* Get Event Flags */

    if (evt & USBD_EVT_SET_CFG)
		{
      USBD_HID_Configure_Event ();
    }
  }
}
#else
__weak __task void USBD_RTX_Core       (void);
#endif

/* USB Device - Core Events Callback Pointer */
void (* const USBD_RTX_P_Core)(void)  = USBD_RTX_Core;

/* USB Device Endpoint Events Callback Pointers */
void (* const USBD_RTX_P_EP[16]) (void) = {
  USBD_RTX_EndPoint0,
  USBD_RTX_EndPoint1,
  USBD_RTX_EndPoint2,
  USBD_RTX_EndPoint3,
  USBD_RTX_EndPoint4,
  USBD_RTX_EndPoint5,
  USBD_RTX_EndPoint6,
  USBD_RTX_EndPoint7,
  USBD_RTX_EndPoint8,
  USBD_RTX_EndPoint9,
  USBD_RTX_EndPoint10,
  USBD_RTX_EndPoint11,
  USBD_RTX_EndPoint12,
  USBD_RTX_EndPoint13,
  USBD_RTX_EndPoint14,
  USBD_RTX_EndPoint15,
};

void usbd_os_evt_set     (U16 event_flags, U32 task)                  { if (task) { os_evt_set(event_flags, task); } }
U16  usbd_os_evt_get     (void)                                       { return (os_evt_get()); }
U32  usbd_os_evt_wait_or (U16 wait_flags, U16 timeout)                { return (os_evt_wait_or (wait_flags, timeout)); }

#else
const BOOL __rtx = __FALSE;

void usbd_os_evt_set     (U16 event_flags, U32 task)                  { }
U16  usbd_os_evt_get     (void)                                       { return (0); }
U32  usbd_os_evt_wait_or (U16 wait_flags, U16 timeout)                { return (0); }
#endif

void usbd_class_init     (void)                                       { 		//USB类初始化 
#if (USBD_HID_ENABLE)
                                                                        usbd_hid_init();			//HID初始化--将参数设置为默认值
#endif
#if (USBD_MSC_ENABLE)
                                                                        usbd_msc_init();
#endif
#if (USBD_ADC_ENABLE)
                                                                        usbd_adc_init();
#endif
#if (USBD_CDC_ACM_ENABLE)
                                                                        USBD_CDC_ACM_Initialize();			//串口配置/初始化
#endif
#if (USBD_CLS_ENABLE)
                                                                        usbd_cls_init();
#endif
                                                                      }

void USBD_RTX_TaskInit (void) {

#ifdef __RTX
  /* Initialize memory pools for endpoints */
  U32 i;

  USBD_RTX_DevTask = 0;
  if (USBD_RTX_P_Device) {
    USBD_RTX_DevTask = os_tsk_create(USBD_RTX_Device,      3);
  }

  for (i = 0; i <= 15; i++) {
    USBD_RTX_EPTask[i] = 0;
    if (USBD_RTX_P_EP[i]) {
      USBD_RTX_EPTask[i] = os_tsk_create(USBD_RTX_P_EP[i], 2);
    }
  }
 
  USBD_RTX_CoreTask = 0;
  if (USBD_RTX_P_Core) {
    USBD_RTX_CoreTask = os_tsk_create(USBD_RTX_Core,       2);
  }
#endif
}


/*------------------------------------------------------------------------------
 *      USB Device Descriptors
 *----------------------------------------------------------------------------*/

#define USBD_ADC_DESC_LEN                 (USBD_MULTI_IF * USB_INTERFACE_ASSOC_DESC_SIZE + USB_INTERFACE_DESC_SIZE +                              \
                                           AUDIO_CONTROL_INTERFACE_DESC_SZ(1) + AUDIO_INPUT_TERMINAL_DESC_SIZE  +                                 \
                                           AUDIO_FEATURE_UNIT_DESC_SZ(1,1) + AUDIO_OUTPUT_TERMINAL_DESC_SIZE + USB_INTERFACE_DESC_SIZE          + \
                                           USB_INTERFACE_DESC_SIZE + AUDIO_STREAMING_INTERFACE_DESC_SIZE + AUDIO_FORMAT_TYPE_I_DESC_SZ(1)       + \
                                           AUDIO_STANDARD_ENDPOINT_DESC_SIZE + AUDIO_STREAMING_ENDPOINT_DESC_SIZE)
#define USBD_CDC_ACM_DESC_LEN             (USB_INTERFACE_DESC_SIZE + USBD_MULTI_IF * USB_INTERFACE_ASSOC_DESC_SIZE + 0x0013                     + \
                                           USB_ENDPOINT_DESC_SIZE + USB_INTERFACE_DESC_SIZE + 2*USB_ENDPOINT_DESC_SIZE)
#define USBD_HID_DESC_LEN                 (USB_INTERFACE_DESC_SIZE + USB_HID_DESC_SIZE                                                          + \
                                          (USB_ENDPOINT_DESC_SIZE*(1+(USBD_HID_EP_INTOUT != 0))))
#define USBD_MSC_DESC_LEN                 (USB_INTERFACE_DESC_SIZE + 2*USB_ENDPOINT_DESC_SIZE)
#define USBD_HID_DESC_OFS                 (USB_CONFIGUARTION_DESC_SIZE + USB_INTERFACE_DESC_SIZE                                                + \
                                           USBD_ADC_ENABLE * USBD_ADC_DESC_LEN + USBD_CDC_ACM_ENABLE * USBD_CDC_ACM_DESC_LEN)

#define USBD_WTOTALLENGTH                 (USB_CONFIGUARTION_DESC_SIZE +                 \
                                           USBD_ADC_DESC_LEN     * USBD_ADC_ENABLE     + \
                                           USBD_CDC_ACM_DESC_LEN * USBD_CDC_ACM_ENABLE + \
                                           USBD_HID_DESC_LEN     * USBD_HID_ENABLE     + \
                                           USBD_MSC_DESC_LEN     * USBD_MSC_ENABLE)

/*------------------------------------------------------------------------------
  Default HID Report Descriptor
 *----------------------------------------------------------------------------*/

/*   Bit    Input       Output
      0     IN0          OUT0
      1     IN1          OUT1
      2     IN2          OUT2
      3     IN3          OUT3
      4     IN4          OUT4
      5     IN5          OUT5
      6     IN6          OUT6
      7     IN7          OUT7
*/

__weak \
const U8 USBD_HID_ReportDescriptor[] = {
  HID_UsagePageVendor( 0x00                      ),
  HID_Usage          ( 0x01                      ),
  HID_Collection     ( HID_Application           ),
    HID_LogicalMin   ( 0                         ), /* value range: 0 - 0xFF */
    HID_LogicalMaxS  ( 0xFF                      ),
    HID_ReportSize   ( 8                         ), /* 8 bits */
#if (USBD_HID_INREPORT_MAX_SZ > 255)
    HID_ReportCountS ( USBD_HID_INREPORT_MAX_SZ  ),
#else
    HID_ReportCount  ( USBD_HID_INREPORT_MAX_SZ  ),
#endif
    HID_Usage        ( 0x01                      ),
    HID_Input        ( HID_Data | HID_Variable | HID_Absolute ),
#if (USBD_HID_OUTREPORT_MAX_SZ > 255)
    HID_ReportCountS ( USBD_HID_OUTREPORT_MAX_SZ ),
#else
    HID_ReportCount  ( USBD_HID_OUTREPORT_MAX_SZ ),
#endif
    HID_Usage        ( 0x01                      ),
    HID_Output       ( HID_Data | HID_Variable | HID_Absolute ),
#if (USBD_HID_FEATREPORT_MAX_SZ > 255)
    HID_ReportCountS ( USBD_HID_FEATREPORT_MAX_SZ),
#else
    HID_ReportCount  ( USBD_HID_FEATREPORT_MAX_SZ),
#endif
    HID_Usage        ( 0x01                      ),
    HID_Feature      ( HID_Data | HID_Variable | HID_Absolute ),
  HID_EndCollection,
};

__weak const U16 USBD_HID_ReportDescriptorSize = sizeof(USBD_HID_ReportDescriptor);

__weak const U16 USBD_HID_DescriptorOffset     = USBD_HID_DESC_OFS;

/* USB Device Standard Descriptor */
__weak const U8 USBD_DeviceDescriptor[] =
{
  USB_DEVICE_DESC_SIZE,                 /* bLength */						//描述设备描述符的总字节数
  USB_DEVICE_DESCRIPTOR_TYPE,           /* bDescriptorType */		//描述符的类型（为0X01，这里是设备描述符）
#if ((USBD_HS_ENABLE) || (USBD_MULTI_IF))
  WBVAL(0x0200), /* 2.00 */             /* bcdUSB */						//这个设备兼容的USB设备版本号
#else
  WBVAL(0x0110), /* 1.10 */             /* bcdUSB */
#endif
#if (USBD_MULTI_IF)
  USB_DEVICE_CLASS_MISCELLANEOUS,       /* bDeviceClass */					//设备类码：是由USB 协会规定的，描述的是接口所能实现的功能。当此域为0时下面的子类也必须为0，当为0XFF表示的是厂商自定义设备类
  0x02,                                 /* bDeviceSubClass */				//子类代码码：这个码值的意思是根据设备类码来看。如设备类码为零，这字段也要零，如设备类码为0XFF，此域的所有值保留。
  0x01,                                 /* bDeviceProtocol */				//协议码：这些码的值视设备码和子类代码的值而定。当该字段为0是，表示设备不使用类所定义的协议， 当该字段的值为0XFF时，表示使用设备厂商自定义的协议	
#elif (USBD_CDC_ACM_ENABLE)
  USB_DEVICE_CLASS_COMMUNICATIONS,      /* bDeviceClass CDC*/	//02	//设备类码：是由USB 协会规定的，描述的是接口所能实现的功能。当此域为0时下面的子类也必须为0，当为0XFF表示的是厂商自定义设备类
  0x00,                                 /* bDeviceSubClass */				//子类代码码：这个码值的意思是根据设备类码来看。如设备类码为零，这字段也要零，如设备类码为0XFF，此域的所有值保留。
  0x00,                                 /* bDeviceProtocol */				//协议码：这些码的值视设备码和子类代码的值而定。当该字段为0是，表示设备不使用类所定义的协议， 当该字段的值为0XFF时，表示使用设备厂商自定义的协议
#else
  0x00,                                 /* bDeviceClass */
  0x00,                                 /* bDeviceSubClass */
  0x00,                                 /* bDeviceProtocol */
#endif
  USBD_MAX_PACKET0,                     /* bMaxPacketSize0 */				//端点0的能缓冲的最大数据包大小
  WBVAL(USBD_DEVDESC_IDVENDOR),         /* idVendor */							//生产设备厂家的标志（由USB 相关组织给的）
  WBVAL(USBD_DEVDESC_IDPRODUCT),        /* idProduct */							//产品标志（由生产的厂家自己做编号）
  WBVAL(USBD_DEVDESC_BCDDEVICE),        /* bcdDevice */							//设备的版本号
  0x01,                                 /* iManufacturer */					//描述生产设备厂家的信息的字符串描述符的索引值。
  0x02,                                 /* iProduct */							//描述所使用设备产品的信息的字串描述符的索引值。
  0x03*USBD_STRDESC_SER_ENABLE,         /* iSerialNumber */					//描述设备产品的序列号信息的字串描述符的索引值。
  0x01                                  /* bNumConfigurations: one possible configuration*/	//设备有多少种配置
};

#if (USBD_HS_ENABLE)
/* USB Device Qualifier Descriptor (for Full Speed) */
__weak const U8 USBD_DeviceQualifier[] =
{
  USB_DEVICE_QUALI_SIZE,                /* bLength */
  USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(0x0200), /* 2.00 */             /* bcdUSB */
  0x00,                                 /* bDeviceClass */
  0x00,                                 /* bDeviceSubClass */
  0x00,                                 /* bDeviceProtocol */
  USBD_MAX_PACKET0,                     /* bMaxPacketSize0 */
  0x01,                                 /* bNumConfigurations */
  0x00                                  /* bReserved */
};

/* USB Device Qualifier Descriptor for High Speed */
__weak const U8 USBD_DeviceQualifier_HS[] =
{
  USB_DEVICE_QUALI_SIZE,                /* bLength */
  USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(0x0200), /* 2.00 */             /* bcdUSB */
  0x00,                                 /* bDeviceClass */
  0x00,                                 /* bDeviceSubClass */
  0x00,                                 /* bDeviceProtocol */
  USBD_MAX_PACKET0,                     /* bMaxPacketSize0 */
  0x01,                                 /* bNumConfigurations */
  0x00                                  /* bReserved */
};
#else
/* USB Device Qualifier Descriptor (for Full Speed) */
__weak const U8 USBD_DeviceQualifier[]    = { 0 };

/* USB Device Qualifier Descriptor for High Speed */
__weak const U8 USBD_DeviceQualifier_HS[] = { 0 };
#endif

#define HID_DESC                                                                                            \
  /* Interface, Alternate Setting 0, HID Class */                                                           \
  USB_INTERFACE_DESC_SIZE,              /* bLength */                                                       \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */                                               \
  USBD_HID_IF_NUM,                      /* bInterfaceNumber */                                              \
  0x00,                                 /* bAlternateSetting */                                             \
  0x01+(USBD_HID_EP_INTOUT != 0),       /* bNumEndpoints */                                                 \
  USB_DEVICE_CLASS_HUMAN_INTERFACE,     /* bInterfaceClass */                                               \
  HID_SUBCLASS_NONE,                    /* bInterfaceSubClass */                                            \
  HID_PROTOCOL_NONE,                    /* bInterfaceProtocol */                                            \
  USBD_HID_IF_STR_NUM,                  /* iInterface */                                                    \
                                                                                                            \
/* HID Class Descriptor */                                                                                  \
  USB_HID_DESC_SIZE,                    /* bLength */                                                       \
  HID_HID_DESCRIPTOR_TYPE,              /* bDescriptorType */                                               \
  WBVAL(0x0100), /* 1.00 */             /* bcdHID */                                                        \
  0x00,                                 /* bCountryCode */                                                  \
  0x01,                                 /* bNumDescriptors */                                               \
  HID_REPORT_DESCRIPTOR_TYPE,           /* bDescriptorType */                                               \
  WBVAL(USB_HID_REPORT_DESC_SIZE),      /* wDescriptorLength */

#define HID_EP                          /* HID Endpoint for Low-speed/Full-speed */                         \
/* Endpoint, HID Interrupt In */                                                                            \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_HID_EP_INTIN),   /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_HID_WMAXPACKETSIZE),       /* wMaxPacketSize */                                                \
  USBD_HID_BINTERVAL,                   /* bInterval */

#define HID_EP_INOUT                    /* HID Endpoint for Low-speed/Full-speed */                         \
/* Endpoint, HID Interrupt In */                                                                            \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_HID_EP_INTIN),   /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_HID_WMAXPACKETSIZE),       /* wMaxPacketSize */                                                \
  USBD_HID_BINTERVAL,                   /* bInterval */                                                     \
                                                                                                            \
/* Endpoint, HID Interrupt Out */                                                                           \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_HID_EP_INTOUT), /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_HID_WMAXPACKETSIZE),       /* wMaxPacketSize */                                                \
  USBD_HID_BINTERVAL,                   /* bInterval */

#define HID_EP_HS                       /* HID Endpoint for High-speed */                                   \
/* Endpoint, HID Interrupt In */                                                                            \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_HID_EP_INTIN),   /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_HID_HS_WMAXPACKETSIZE),    /* wMaxPacketSize */                                                \
  USBD_HID_HS_BINTERVAL,                /* bInterval */

#define HID_EP_INOUT_HS                 /* HID Endpoint for High-speed */                                   \
/* Endpoint, HID Interrupt In */                                                                            \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_HID_EP_INTIN),   /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_HID_HS_WMAXPACKETSIZE),    /* wMaxPacketSize */                                                \
  USBD_HID_HS_BINTERVAL,                /* bInterval */                                                     \
                                                                                                            \
/* Endpoint, HID Interrupt Out */                                                                           \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_HID_EP_INTOUT), /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_HID_HS_WMAXPACKETSIZE),    /* wMaxPacketSize */                                                \
  USBD_HID_HS_BINTERVAL,                /* bInterval */

#define MSC_DESC                                                                                            \
/* Interface, Alternate Setting 0, MSC Class */                                                             \
  USB_INTERFACE_DESC_SIZE,              /* bLength */                                                       \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */                                               \
  USBD_MSC_IF_NUM,                      /* bInterfaceNumber */                                              \
  0x00,                                 /* bAlternateSetting */                                             \
  0x02,                                 /* bNumEndpoints */                                                 \
  USB_DEVICE_CLASS_STORAGE,             /* bInterfaceClass */                                               \
  MSC_SUBCLASS_SCSI,                    /* bInterfaceSubClass */                                            \
  MSC_PROTOCOL_BULK_ONLY,               /* bInterfaceProtocol */                                            \
  USBD_MSC_IF_STR_NUM,                  /* iInterface */

#define MSC_EP                          /* MSC Endpoints for Low-speed/Full-speed */                        \
/* Endpoint, EP Bulk IN */                                                                                  \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_MSC_EP_BULKIN),  /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_MSC_WMAXPACKETSIZE),       /* wMaxPacketSize */                                                \
  0x00,                                 /* bInterval: ignore for Bulk transfer */                           \
                                                                                                            \
/* Endpoint, EP Bulk OUT */                                                                                 \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_MSC_EP_BULKOUT),/* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_MSC_WMAXPACKETSIZE),       /* wMaxPacketSize */                                                \
  0x00,                                 /* bInterval: ignore for Bulk transfer */

#define MSC_EP_HS                       /* MSC Endpoints for High-speed */                                  \
/* Endpoint, EP Bulk IN */                                                                                  \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_MSC_EP_BULKIN),  /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_MSC_HS_WMAXPACKETSIZE),    /* wMaxPacketSize */                                                \
  USBD_MSC_HS_BINTERVAL,                /* bInterval */                                                     \
                                                                                                            \
/* Endpoint, EP Bulk OUT */                                                                                 \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_MSC_EP_BULKOUT),/* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_MSC_HS_WMAXPACKETSIZE),    /* wMaxPacketSize */                                                \
  USBD_MSC_HS_BINTERVAL,                /* bInterval */

#define ADC_DESC_IAD(first,num_of_ifs)  /* ADC: Interface Association Descriptor */                         \
  USB_INTERFACE_ASSOC_DESC_SIZE,        /* bLength */                                                       \
  USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,  /* bDescriptorType */                                         \
 (first),                               /* bFirstInterface */                                               \
 (num_of_ifs),                          /* bInterfaceCount */                                               \
  USB_DEVICE_CLASS_AUDIO,               /* bFunctionClass */                                                \
  AUDIO_SUBCLASS_AUDIOCONTROL,          /* bFunctionSubclass */                                             \
  AUDIO_PROTOCOL_UNDEFINED,             /* bFunctionProtocol */                                             \
  USBD_ADC_CIF_STR_NUM,                 /* iFunction */                                                     \

#define ADC_DESC                                                                                            \
/* Interface, Alternate Setting 0, Audio Control */                                                         \
  USB_INTERFACE_DESC_SIZE,              /* bLength */                                                       \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */                                               \
  USBD_ADC_CIF_NUM,                     /* bInterfaceNumber */                                              \
  0x00,                                 /* bAlternateSetting */                                             \
  0x00,                                 /* bNumEndpoints */                                                 \
  USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */                                               \
  AUDIO_SUBCLASS_AUDIOCONTROL,          /* bInterfaceSubClass */                                            \
  AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */                                            \
  USBD_ADC_CIF_STR_NUM,                 /* iInterface */                                                    \
/* Audio Control Interface */                                                                               \
  AUDIO_CONTROL_INTERFACE_DESC_SZ(1),   /* bLength */                                                       \
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */                                               \
  AUDIO_CONTROL_HEADER,                 /* bDescriptorSubtype */                                            \
  WBVAL(0x0100), /* 1.00 */             /* bcdADC */                                                        \
  WBVAL(                                /* wTotalLength */                                                  \
    AUDIO_CONTROL_INTERFACE_DESC_SZ(1) +                                                                    \
    AUDIO_INPUT_TERMINAL_DESC_SIZE     +                                                                    \
    AUDIO_FEATURE_UNIT_DESC_SZ(1,1)    +                                                                    \
    AUDIO_OUTPUT_TERMINAL_DESC_SIZE                                                                         \
  ),                                                                                                        \
  0x01,                                 /* bInCollection */                                                 \
  0x01,                                 /* baInterfaceNr */                                                 \
                                                                                                            \
/* Audio Input Terminal */                                                                                  \
  AUDIO_INPUT_TERMINAL_DESC_SIZE,       /* bLength */                                                       \
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */                                               \
  AUDIO_CONTROL_INPUT_TERMINAL,         /* bDescriptorSubtype */                                            \
  0x01,                                 /* bTerminalID */                                                   \
  WBVAL(AUDIO_TERMINAL_USB_STREAMING),  /* wTerminalType */                                                 \
  0x00,                                 /* bAssocTerminal */                                                \
  0x01,                                 /* bNrChannels */                                                   \
  WBVAL(AUDIO_CHANNEL_M),               /* wChannelConfig */                                                \
  0x00,                                 /* iChannelNames */                                                 \
  0x00,                                 /* iTerminal */                                                     \
                                                                                                            \
/* Audio Feature Unit */                                                                                    \
  AUDIO_FEATURE_UNIT_DESC_SZ(1,1),      /* bLength */                                                       \
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */                                               \
  AUDIO_CONTROL_FEATURE_UNIT,           /* bDescriptorSubtype */                                            \
  0x02,                                 /* bUnitID */                                                       \
  0x01,                                 /* bSourceID */                                                     \
  0x01,                                 /* bControlSize */                                                  \
  AUDIO_CONTROL_MUTE |                                                                                      \
  AUDIO_CONTROL_VOLUME,                 /* bmaControls(0) */                                                \
  0x00,                                 /* bmaControls(1) */                                                \
  0x00,                                 /* iTerminal */                                                     \
                                                                                                            \
/* Audio Output Terminal */                                                                                 \
  AUDIO_OUTPUT_TERMINAL_DESC_SIZE,      /* bLength */                                                       \
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */                                               \
  AUDIO_CONTROL_OUTPUT_TERMINAL,        /* bDescriptorSubtype */                                            \
  0x03,                                 /* bTerminalID */                                                   \
  WBVAL(AUDIO_TERMINAL_SPEAKER),        /* wTerminalType */                                                 \
  0x00,                                 /* bAssocTerminal */                                                \
  0x02,                                 /* bSourceID */                                                     \
  0x00,                                 /* iTerminal */                                                     \
                                                                                                            \
/* Interface, Alternate Setting 0, Audio Streaming - Zero Bandwith */                                       \
  USB_INTERFACE_DESC_SIZE,              /* bLength */                                                       \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */                                               \
  USBD_ADC_SIF1_NUM,                    /* bInterfaceNumber */                                              \
  0x00,                                 /* bAlternateSetting */                                             \
  0x00,                                 /* bNumEndpoints */                                                 \
  USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */                                               \
  AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */                                            \
  AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */                                            \
  USBD_ADC_SIF1_STR_NUM,                /* iInterface */                                                    \
                                                                                                            \
/* Interface, Alternate Setting 1, Audio Streaming - Operational */                                         \
  USB_INTERFACE_DESC_SIZE,              /* bLength */                                                       \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */                                               \
  USBD_ADC_SIF1_NUM,                    /* bInterfaceNumber */                                              \
  0x01,                                 /* bAlternateSetting */                                             \
  0x01,                                 /* bNumEndpoints */                                                 \
  USB_DEVICE_CLASS_AUDIO,               /* bInterfaceClass */                                               \
  AUDIO_SUBCLASS_AUDIOSTREAMING,        /* bInterfaceSubClass */                                            \
  AUDIO_PROTOCOL_UNDEFINED,             /* bInterfaceProtocol */                                            \
  USBD_ADC_SIF2_STR_NUM,                /* iInterface */                                                    \
                                                                                                            \
/* Audio Streaming Interface */                                                                             \
  AUDIO_STREAMING_INTERFACE_DESC_SIZE,  /* bLength */                                                       \
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */                                               \
  AUDIO_STREAMING_GENERAL,              /* bDescriptorSubtype */                                            \
  0x01,                                 /* bTerminalLink */                                                 \
  0x01,                                 /* bDelay */                                                        \
  WBVAL(AUDIO_FORMAT_PCM),              /* wFormatTag */                                                    \
                                                                                                            \
/* Audio Type I Format */                                                                                   \
  AUDIO_FORMAT_TYPE_I_DESC_SZ(1),       /* bLength */                                                       \
  AUDIO_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */                                               \
  AUDIO_STREAMING_FORMAT_TYPE,          /* bDescriptorSubtype */                                            \
  AUDIO_FORMAT_TYPE_I,                  /* bFormatType */                                                   \
  0x01,                                 /* bNrChannels */                                                   \
  USBD_ADC_BSUBFRAMESIZE,               /* bSubFrameSize */                                                 \
  USBD_ADC_BBITRESOLUTION,              /* bBitResolution */                                                \
  0x01,                                 /* bSamFreqType */                                                  \
  B3VAL(USBD_ADC_TSAMFREQ),             /* tSamFreq */

#define ADC_EP                          /* ADC Endpoints for Low-speed/Full-speed */                        \
/* Endpoint, EP ISO OUT - Standard Descriptor */                                                            \
  AUDIO_STANDARD_ENDPOINT_DESC_SIZE,    /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_ADC_EP_ISOOUT), /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_ISOCHRONOUS,        /* bmAttributes */                                                  \
  WBVAL(USBD_ADC_WMAXPACKETSIZE),       /* wMaxPacketSize */                                                \
  USBD_ADC_BINTERVAL,                   /* bInterval */                                                     \
  0x00,                                 /* bRefresh */                                                      \
  0x00,                                 /* bSynchAddress */                                                 \
                                                                                                            \
/* Endpoint - Audio Streaming */                                                                            \
  AUDIO_STREAMING_ENDPOINT_DESC_SIZE,   /* bLength */                                                       \
  AUDIO_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */                                               \
  AUDIO_ENDPOINT_GENERAL,               /* bDescriptor */                                                   \
  0x00,                                 /* bmAttributes */                                                  \
  0x00,                                 /* bLockDelayUnits */                                               \
  WBVAL(0x0000),                        /* wLockDelay */

#define ADC_EP_HS                       /* ADC Endpoints for High-speed */                                  \
/* Endpoint, EP ISO OUT - Standard Descriptor */                                                            \
  AUDIO_STANDARD_ENDPOINT_DESC_SIZE,    /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_ADC_EP_ISOOUT), /* bEndpointAddress */                                              \
  USB_ENDPOINT_TYPE_ISOCHRONOUS,        /* bmAttributes */                                                  \
  WBVAL(USBD_ADC_HS_WMAXPACKETSIZE),    /* wMaxPacketSize */                                                \
  USBD_ADC_BINTERVAL,                   /* bInterval */                                                     \
  0x00,                                 /* bRefresh */                                                      \
  0x00,                                 /* bSynchAddress */                                                 \
                                                                                                            \
/* Endpoint - Audio Streaming */                                                                            \
  AUDIO_STREAMING_ENDPOINT_DESC_SIZE,   /* bLength */                                                       \
  AUDIO_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */                                               \
  AUDIO_ENDPOINT_GENERAL,               /* bDescriptor */                                                   \
  0x00,                                 /* bmAttributes */                                                  \
  0x00,                                 /* bLockDelayUnits */                                               \
  WBVAL(0x0000),                        /* wLockDelay */

#define CDC_ACM_DESC_IAD(first,num_of_ifs)  /* CDC: Interface Association Descriptor */                     \
  USB_INTERFACE_ASSOC_DESC_SIZE,        /* bLength */                                                       \
  USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,  /* bDescriptorType */                                         \
 (first),                               /* bFirstInterface */                                               \
 (num_of_ifs),                          /* bInterfaceCount */                                               \
  CDC_COMMUNICATION_INTERFACE_CLASS,    /* bFunctionClass    (Communication Class) */                       \
  CDC_ABSTRACT_CONTROL_MODEL,           /* bFunctionSubclass (Abstract Control Model) */                    \
  0x01,                                 /* bFunctionProtocol (V.25ter, Common AT commands) */               \
  USBD_CDC_ACM_CIF_STR_NUM,             /* iFunction */                                                     \

#define CDC_ACM_DESC_IF0                                                                                    \
/* Interface, Alternate Setting 0, CDC Class */                                                             \
  USB_INTERFACE_DESC_SIZE,              /* bLength */        	                 	                            \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */																	            	\
  USBD_CDC_ACM_CIF_NUM,                 /* bInterfaceNumber: Number of Interface */                         \
  0x00,                                 /* bAlternateSetting: Alternate setting */                          \
  0x01,                                 /* bNumEndpoints: One endpoint used */                              \
  CDC_COMMUNICATION_INTERFACE_CLASS,    /* bInterfaceClass: Communication Interface Class */                \
  CDC_ABSTRACT_CONTROL_MODEL,           /* bInterfaceSubClass: Abstract Control Model */                    \
  0x00,                                 /* bInterfaceProtocol: no protocol used */                          \
  USBD_CDC_ACM_CIF_STR_NUM,             /* iInterface: */                                                   \
                                                                                                            \
/* Header Functional Descriptor */                                                                          \
  0x05,                                 /* bLength: Endpoint Descriptor size */                             \
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */                                 \
  CDC_HEADER,                           /* bDescriptorSubtype: Header Func Desc */                          \
  WBVAL(CDC_V1_10), /* 1.10 */          /* bcdCDC */                                                        \
/* Call Management Functional Descriptor */                                                                 \
  0x05,                                 /* bFunctionLength */                                               \
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */                                 \
  CDC_CALL_MANAGEMENT,                  /* bDescriptorSubtype: Call Management Func Desc */                 \
  0x01,                                 /* bmCapabilities: device handles call management */                \
  0x01,                                 /* bDataInterface: CDC data IF ID */                                \
/* Abstract Control Management Functional Descriptor */                                                     \
  0x04,                                 /* bFunctionLength */                                               \
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */                                 \
  CDC_ABSTRACT_CONTROL_MANAGEMENT,      /* bDescriptorSubtype: Abstract Control Management desc */          \
  0x02,                                 /* bmCapabilities: SET_LINE_CODING, GET_LINE_CODING, SET_CONTROL_LINE_STATE supported */ \
/* Union Functional Descriptor */                                                                           \
  0x05,                                 /* bFunctionLength */                                               \
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */                                 \
  CDC_UNION,                            /* bDescriptorSubtype: Union func desc */                           \
  USBD_CDC_ACM_CIF_NUM,                 /* bMasterInterface: Communication class interface is master */     \
  USBD_CDC_ACM_DIF_NUM,                 /* bSlaveInterface0: Data class interface is slave 0 */

#define CDC_ACM_EP_IF0                  /* CDC Endpoints for Interface 0 for Low-speed/Full-speed */        \
/* Endpoint, EP Interrupt IN */         /* event notification (optional) */                                 \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_CDC_ACM_EP_INTIN),/* bEndpointAddress */                                             \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_CDC_ACM_WMAXPACKETSIZE),   /* wMaxPacketSize */                                                \
  USBD_CDC_ACM_BINTERVAL,               /* bInterval */

#define CDC_ACM_EP_IF0_HS               /* CDC Endpoints for Interface 0 for High-speed */                  \
/* Endpoint, EP Interrupt IN */         /* event notification (optional) */                                 \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_CDC_ACM_EP_INTIN),/* bEndpointAddress */                                             \
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */                                                  \
  WBVAL(USBD_CDC_ACM_HS_WMAXPACKETSIZE),/* wMaxPacketSize */                                                \
  USBD_CDC_ACM_HS_BINTERVAL,            /* bInterval */

#define CDC_ACM_DESC_IF1                                                                                 		\
/* Interface, Alternate Setting 0, Data class interface descriptor*/                                        \
  USB_INTERFACE_DESC_SIZE,              /* bLength */                                                       \
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */                                               \
  USBD_CDC_ACM_DIF_NUM,                 /* bInterfaceNumber: Number of Interface */                         \
  0x00,                                 /* bAlternateSetting: no alternate setting */                       \
  0x02,                                 /* bNumEndpoints: two endpoints used */                             \
  CDC_DATA_INTERFACE_CLASS,             /* bInterfaceClass: Data Interface Class */                         \
  0x00,                                 /* bInterfaceSubClass: no subclass available */                     \
  0x00,                                 /* bInterfaceProtocol: no protocol used */                          \
  USBD_CDC_ACM_DIF_STR_NUM,             /* iInterface */

#define CDC_ACM_EP_IF1                  /* CDC Endpoints for Interface 1 for Low-speed/Full-speed */        \
/* Endpoint, EP Bulk OUT */                                                                                 \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_CDC_ACM_EP_BULKOUT),/* bEndpointAddress */                                          \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_CDC_ACM_WMAXPACKETSIZE1),  /* wMaxPacketSize */                                                \
  0x00,                                 /* bInterval: ignore for Bulk transfer */                           \
                                                                                                            \
/* Endpoint, EP Bulk IN */                                                                                  \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_CDC_ACM_EP_BULKIN),/* bEndpointAddress */                                            \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_CDC_ACM_WMAXPACKETSIZE1),  /* wMaxPacketSize */                                                \
  0x00,                                 /* bInterval: ignore for Bulk transfer */

#define CDC_ACM_EP_IF1_HS               /* CDC Endpoints for Interface 1 for High-speed */                  \
/* Endpoint, EP Bulk OUT */                                                                                 \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_OUT(USBD_CDC_ACM_EP_BULKOUT),/* bEndpointAddress */                                          \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_CDC_ACM_HS_WMAXPACKETSIZE1),/* wMaxPacketSize */                                               \
  USBD_CDC_ACM_HS_BINTERVAL1,           /* bInterval */                                                     \
                                                                                                            \
/* Endpoint, EP Bulk IN */                                                                                  \
  USB_ENDPOINT_DESC_SIZE,               /* bLength */                                                       \
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */                                               \
  USB_ENDPOINT_IN(USBD_CDC_ACM_EP_BULKIN),/* bEndpointAddress */                                            \
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */                                                  \
  WBVAL(USBD_CDC_ACM_HS_WMAXPACKETSIZE1),/* wMaxPacketSize */                                               \
  USBD_CDC_ACM_HS_BINTERVAL1,           /* bInterval */

/* USB Device Configuration Descriptor (for Full Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak const U8 USBD_ConfigDescriptor[] =
{
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,          /* bLength */					//整个描述符长度--0x09/9个字节
  USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */	//类别--0X02设备描述符
  WBVAL(USBD_WTOTALLENGTH),             /* wTotalLength */		//此配置信息的总长（包括配置，接口，端点和设备类及厂商定义的描述符）
  USBD_IF_NUM,                          /* bNumInterfaces */	//此配置所支持的接口个数
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */	//在SetConfiguration（）请求中用作参数来选定此配置。
  0x00,                                 /* iConfiguration: no string to describe this configuration */				//描述此配置的字串描述表索引
  USBD_CFGDESC_BMATTRIBUTES |           /* bmAttributes */		//配置特性：D7： 保留（设为一），D6： 自给电源，D5： 远程唤醒，D4..0：保留（设为一）		
  (USBD_POWER << 6),	
  USBD_CFGDESC_BMAXPOWER,               /* bMaxPower, device power consumption */	//在此配置下的总线电源耗费量。以2mA 为一个单位。

	
//USB复合设备一般用Interface Association Descriptor（IAD）实现，就是在要合并的接口前加上IAD描述符。
#if (USBD_ADC_ENABLE)  									//--未使用                                                                                
#if (USBD_MULTI_IF)											//USB复合设备一般用Interface Association Descriptor（IAD）实现，就是在要合并的接口前加上IAD描述符。
//  ADC_DESC_IAD(USBD_ADC_CIF_NUM,2)		//20170419
	
	/* ADC: Interface Association Descriptor */
	USB_INTERFACE_ASSOC_DESC_SIZE,        			/* bLength */ 						//描述符大小  	
	USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,  /* bDescriptorType */			//IAD描述符类型
	USBD_ADC_CIF_NUM,                         	/* bFirstInterface */  		//起始接口	
	2,                          								/* bInterfaceCount */ 		//接口数
  USB_DEVICE_CLASS_AUDIO,              			 	/* bFunctionClass */   		//类型代码
  AUDIO_SUBCLASS_AUDIOCONTROL,          			/* bFunctionSubclass */		//子类型代码
  AUDIO_PROTOCOL_UNDEFINED,             			/* bFunctionProtocol */		//协议代码
  USBD_ADC_CIF_STR_NUM,                 			/* iFunction */						//描述字符串索引
	
#endif
  ADC_DESC
  ADC_EP
#endif

#if (USBD_CDC_ACM_ENABLE) 								//虚拟串口---使用                                                                             
#if (USBD_MULTI_IF)												//USB复合设备一般用Interface Association Descriptor（IAD）实现，就是在要合并的接口前加上IAD描述符。
//  CDC_ACM_DESC_IAD(USBD_CDC_ACM_CIF_NUM,2)	//20170419

	/* CDC: Interface Association Descriptor */
	USB_INTERFACE_ASSOC_DESC_SIZE,        			/* bLength */																					//描述符大小
	USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,  /* bDescriptorType */																	//IAD描述符类型
	USBD_CDC_ACM_CIF_NUM,                     	/* bFirstInterface */ 																//起始接口
	2,                          								/* bInterfaceCount */  																//接口数
  CDC_COMMUNICATION_INTERFACE_CLASS,    			/* bFunctionClass    (Communication Class) */					//类型代码
  CDC_ABSTRACT_CONTROL_MODEL,           			/* bFunctionSubclass (Abstract Control Model) */			//子类型代码
  0x01,                                			 	/* bFunctionProtocol (V.25ter, Common AT commands) */	//协议代码
  USBD_CDC_ACM_CIF_STR_NUM,             			/* iFunction */ 																			//描述字符串索引
#endif
//  CDC_ACM_DESC_IF0														//端点描述符
/* Interface, Alternate Setting 0, CDC Class */ 	
  USB_INTERFACE_DESC_SIZE,              /* bLength */	
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */	
  USBD_CDC_ACM_CIF_NUM,                 /* bInterfaceNumber: Number of Interface */	
  0x00,                                 /* bAlternateSetting: Alternate setting */	
  0x01,                                 /* bNumEndpoints: One endpoint used */	
  CDC_COMMUNICATION_INTERFACE_CLASS,    /* bInterfaceClass: Communication Interface Class */	
  CDC_ABSTRACT_CONTROL_MODEL,           /* bInterfaceSubClass: Abstract Control Model */	
  0x00,                                 /* bInterfaceProtocol: no protocol used */	
  USBD_CDC_ACM_CIF_STR_NUM,             /* iInterface: */                           	
																																													
/* Header Functional Descriptor */                                               	
  0x05,                                 /* bLength: Endpoint Descriptor size */     	
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */                       	
  CDC_HEADER,                           /* bDescriptorSubtype: Header Func Desc */ 	
  WBVAL(CDC_V1_10), /* 1.10 */          /* bcdCDC */	
/* Call Management Functional Descriptor */	
  0x05,                                 /* bFunctionLength */	
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */	
  CDC_CALL_MANAGEMENT,                  /* bDescriptorSubtype: Call Management Func Desc */	
  0x01,                                 /* bmCapabilities: device handles call management */	
  0x01,                                 /* bDataInterface: CDC data IF ID */	
/* Abstract Control Management Functional Descriptor */	
  0x04,                                 /* bFunctionLength */	
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */	
  CDC_ABSTRACT_CONTROL_MANAGEMENT,      /* bDescriptorSubtype: Abstract Control Management desc */	
  0x02,                                 /* bmCapabilities: SET_LINE_CODING, GET_LINE_CODING, SET_CONTROL_LINE_STATE supported */	
/* Union Functional Descriptor */	
  0x05,                                 /* bFunctionLength */	
  CDC_CS_INTERFACE,                     /* bDescriptorType: CS_INTERFACE */	
  CDC_UNION,                            /* bDescriptorSubtype: Union func desc */	
  USBD_CDC_ACM_CIF_NUM,                 /* bMasterInterface: Communication class interface is master */	
  USBD_CDC_ACM_DIF_NUM,                 /* bSlaveInterface0: Data class interface is slave 0 */
	
	
//  CDC_ACM_EP_IF0															//端点描述
	/* Endpoint, EP Interrupt IN */         /* event notification (optional) */	
  USB_ENDPOINT_DESC_SIZE,               /* bLength */	
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */	
  USB_ENDPOINT_IN(USBD_CDC_ACM_EP_INTIN),/* bEndpointAddress */	
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */	
  WBVAL(USBD_CDC_ACM_WMAXPACKETSIZE),   /* wMaxPacketSize */	
  USBD_CDC_ACM_BINTERVAL,               /* bInterval */
	
	
//  CDC_ACM_DESC_IF1														//接口描述符
	/* Interface, Alternate Setting 0, Data class interface descriptor*/	
  USB_INTERFACE_DESC_SIZE,              /* bLength */	
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */	
  USBD_CDC_ACM_DIF_NUM,                 /* bInterfaceNumber: Number of Interface */	
  0x00,                                 /* bAlternateSetting: no alternate setting */	
  0x02,                                 /* bNumEndpoints: two endpoints used */	
  CDC_DATA_INTERFACE_CLASS,             /* bInterfaceClass: Data Interface Class */	
  0x00,                                 /* bInterfaceSubClass: no subclass available */	
  0x00,                                 /* bInterfaceProtocol: no protocol used */	
  USBD_CDC_ACM_DIF_STR_NUM,             /* iInterface */
	
	
//  CDC_ACM_EP_IF1															//接口描述
/* Endpoint, EP Bulk OUT */                                  	
  USB_ENDPOINT_DESC_SIZE,               /* bLength */  	
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */	
  USB_ENDPOINT_OUT(USBD_CDC_ACM_EP_BULKOUT),/* bEndpointAddress */	
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */	
  WBVAL(USBD_CDC_ACM_WMAXPACKETSIZE1),  /* wMaxPacketSize */	
  0x00,                                 /* bInterval: ignore for Bulk transfer */	
																																	
/* Endpoint, EP Bulk IN */                                        	
  USB_ENDPOINT_DESC_SIZE,               /* bLength */      	
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */	
  USB_ENDPOINT_IN(USBD_CDC_ACM_EP_BULKIN),/* bEndpointAddress */ 	
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */	
  WBVAL(USBD_CDC_ACM_WMAXPACKETSIZE1),  /* wMaxPacketSize */	
  0x00,
	
	
#endif

#if (USBD_HID_ENABLE)										//HID---使用
//  HID_DESC					//20170419
	
	/* Interface, Alternate Setting 0, HID Class */	
  USB_INTERFACE_DESC_SIZE,              /* bLength */ 						//接口描述符的字节数大小	
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */ 		//接口描述符的类型编号
  USBD_HID_IF_NUM,                      /* bInterfaceNumber */ 		//该接口的编号
  0x00,                                 /* bAlternateSetting */		//备用的接口描述符编号
  0x01+(USBD_HID_EP_INTOUT != 0),       /* bNumEndpoints */ 			//该接口使用的端点数，不包括端点0
  USB_DEVICE_CLASS_HUMAN_INTERFACE,     /* bInterfaceClass */  		//接口类型
  HID_SUBCLASS_NONE,                    /* bInterfaceSubClass */	//接口子类型	
  HID_PROTOCOL_NONE,                    /* bInterfaceProtocol */	//接口遵循的协议
  USBD_HID_IF_STR_NUM,                  /* iInterface */  				//描述该接口的字符串索引值
																											
/* HID Class Descriptor */                            	
  USB_HID_DESC_SIZE,                    /* bLength */							//此描述符的长度（以字节为单位）	
  HID_HID_DESCRIPTOR_TYPE,              /* bDescriptorType */			//描述符种类（此处为0x21即HID类描述符）
  WBVAL(0x0100), /* 1.00 */             /* bcdHID */							//HID规范版本号（BCD码），采用4个16进制的BCD格式编码，如版本1.0的BCD码为0x0100,版本为1.1的BCD码为0x0110
  0x00,                                 /* bCountryCode */				//硬件目的国家的识别码（BCD码）
  0x01,                                 /* bNumDescriptors */			//支持的附属描述符数目
  HID_REPORT_DESCRIPTOR_TYPE,           /* bDescriptorType */			//HID相关描述符的类型
  WBVAL(USB_HID_REPORT_DESC_SIZE),      /* wDescriptorLength */		//报告描述符总长度
	
#if (USBD_HID_EP_INTOUT != 0)
//  HID_EP_INOUT		//20170419
	
	/* Endpoint, HID Interrupt In */ 
  USB_ENDPOINT_DESC_SIZE,               /* bLength */             //端点描述符字节数大小
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */     //端点描述符类型编号
  USB_ENDPOINT_IN(USBD_HID_EP_INTIN),   /* bEndpointAddress */    //端点地址及输入输出属性
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */        //端点的传输类型属性
  WBVAL(USBD_HID_WMAXPACKETSIZE),       /* wMaxPacketSize */      //端点收、发的最大包大小
  USBD_HID_BINTERVAL,                   /* bInterval */           //主机查询端点的时间间隔
	/* Endpoint, HID Interrupt Out */                     	
  USB_ENDPOINT_DESC_SIZE,               /* bLength */        	
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */ 	
  USB_ENDPOINT_OUT(USBD_HID_EP_INTOUT), /* bEndpointAddress */ 	
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */     	
  WBVAL(USBD_HID_WMAXPACKETSIZE),       /* wMaxPacketSize */   	
  USBD_HID_BINTERVAL,                   /* bInterval */
	
#else
//  HID_EP				//20170419
	/* Endpoint, HID Interrupt In */                              
  USB_ENDPOINT_DESC_SIZE,               /* bLength */            	//端点描述符字节数大小
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */     //端点描述符类型编号
  USB_ENDPOINT_IN(USBD_HID_EP_INTIN),   /* bEndpointAddress */    //端点地址及输入输出属性
  USB_ENDPOINT_TYPE_INTERRUPT,          /* bmAttributes */        //端点的传输类型属性
  WBVAL(USBD_HID_WMAXPACKETSIZE),       /* wMaxPacketSize */      //端点收、发的最大包大小
  USBD_HID_BINTERVAL,                   /* bInterval */						//主机查询端点的时间间隔
#endif
#endif

#if (USBD_MSC_ENABLE)			//--未使用
//  MSC_DESC			//20170419
	/* Interface, Alternate Setting 0, MSC Class */	
  USB_INTERFACE_DESC_SIZE,              /* bLength */       			//接口描述符的字节数大小
  USB_INTERFACE_DESCRIPTOR_TYPE,        /* bDescriptorType */    	//接口描述符的类型编号
  USBD_MSC_IF_NUM,                      /* bInterfaceNumber */   	//该接口的编号
  0x00,                                 /* bAlternateSetting */   //备用的接口描述符编号
  0x02,                                 /* bNumEndpoints */       //该接口使用的端点数，不包括端点0
  USB_DEVICE_CLASS_STORAGE,             /* bInterfaceClass */     //接口类型
  MSC_SUBCLASS_SCSI,                    /* bInterfaceSubClass */  //接口子类型
  MSC_PROTOCOL_BULK_ONLY,               /* bInterfaceProtocol */  //接口遵循的协议
  USBD_MSC_IF_STR_NUM,                  /* iInterface */					//描述该接口的字符串索引值
	
	
//  MSC_EP			//20170419
	/* Endpoint, EP Bulk IN */                	
  USB_ENDPOINT_DESC_SIZE,               /* bLength */        			//端点描述符字节数大小
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */ 		//端点描述符类型编号
  USB_ENDPOINT_IN(USBD_MSC_EP_BULKIN),  /* bEndpointAddress */ 		//端点地址及输入输出属性
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */    		//端点的传输类型属性
  WBVAL(USBD_MSC_WMAXPACKETSIZE),       /* wMaxPacketSize */  		//端点收、发的最大包大小
  0x00,																	/* bInterval: ignore for Bulk transfer */		//主机查询端点的时间间隔
																															
/* Endpoint, EP Bulk OUT */             	
  USB_ENDPOINT_DESC_SIZE,               /* bLength */   					//端点描述符字节数大小
  USB_ENDPOINT_DESCRIPTOR_TYPE,         /* bDescriptorType */  		//端点描述符类型编号
  USB_ENDPOINT_OUT(USBD_MSC_EP_BULKOUT),/* bEndpointAddress */   	//端点地址及输入输出属性
  USB_ENDPOINT_TYPE_BULK,               /* bmAttributes */        //端点的传输类型属性
  WBVAL(USBD_MSC_WMAXPACKETSIZE),       /* wMaxPacketSize */      //端点收、发的最大包大小
  0x00,                                 /* bInterval: ignore for Bulk transfer */		//主机查询端点的时间间隔

#endif

/* Terminator */	
  0                                     /* bLength */	
};

#if (USBD_HS_ENABLE == 0)               /* If High-speed not enabled, declare dummy descriptors for High-speed */
__weak const U8 USBD_ConfigDescriptor_HS[] = { 0 };
__weak const U8 USBD_OtherSpeedConfigDescriptor[] = { 0 };
__weak const U8 USBD_OtherSpeedConfigDescriptor_HS[] = { 0 };
#else

/* USB Device Configuration Descriptor (for High Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak const U8 USBD_ConfigDescriptor_HS[] = 
{
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,          /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */
  WBVAL(USBD_WTOTALLENGTH),             /* wTotalLength */
  USBD_IF_NUM,                          /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD_CFGDESC_BMATTRIBUTES |           /* bmAttributes */
  (USBD_POWER << 6),
  USBD_CFGDESC_BMAXPOWER,               /* bMaxPower, device power consumption */

#if (USBD_ADC_ENABLE)                                                                                  
#if (USBD_MULTI_IF)
  ADC_DESC_IAD(USBD_ADC_CIF_NUM,2)
#endif
  ADC_DESC
  ADC_EP_HS
#endif

#if (USBD_CDC_ACM_ENABLE)                                                                                  
#if (USBD_MULTI_IF)
  CDC_ACM_DESC_IAD(USBD_CDC_ACM_CIF_NUM,2)
#endif
  CDC_ACM_DESC_IF0
  CDC_ACM_EP_IF0_HS
  CDC_ACM_DESC_IF1
  CDC_ACM_EP_IF1_HS
#endif

#if (USBD_HID_ENABLE)
  HID_DESC
#if (USBD_HID_EP_INTOUT != 0)
  HID_EP_INOUT_HS
#else
  HID_EP_HS
#endif
#endif

#if (USBD_MSC_ENABLE)
  MSC_DESC
  MSC_EP_HS
#endif

/* Terminator */                                                                                            \
  0                                     /* bLength */                                                       \
};

/* USB Device Other Speed Configuration Descriptor (for Full Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak const U8 USBD_OtherSpeedConfigDescriptor[] = 
{
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,          /* bLength */
  USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(USBD_WTOTALLENGTH),             /* wTotalLength */
  USBD_IF_NUM,                          /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD_CFGDESC_BMATTRIBUTES |           /* bmAttributes */
  (USBD_POWER << 6),
  USBD_CFGDESC_BMAXPOWER,               /* bMaxPower, device power consumption */

#if (USBD_ADC_ENABLE)                                                                                  
#if (USBD_MULTI_IF)
  ADC_DESC_IAD(USBD_ADC_CIF_NUM,2)
#endif
  ADC_DESC
  ADC_EP_HS
#endif

#if (USBD_CDC_ACM_ENABLE)                                                                                  
#if (USBD_MULTI_IF)
  CDC_ACM_DESC_IAD(USBD_CDC_ACM_CIF_NUM,2)
#endif
  CDC_ACM_DESC_IF0
  CDC_ACM_EP_IF0_HS
  CDC_ACM_DESC_IF1
  CDC_ACM_EP_IF1_HS
#endif

#if (USBD_HID_ENABLE)
  HID_DESC
#if (USBD_HID_EP_INTOUT != 0)
  HID_EP_INOUT_HS
#else
  HID_EP_HS
#endif
#endif

#if (USBD_MSC_ENABLE)
  MSC_DESC
  MSC_EP_HS
#endif

/* Terminator */
  0                                     /* bLength */
};

/* USB Device Other Speed Configuration Descriptor for High Speed */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak const U8 USBD_OtherSpeedConfigDescriptor_HS[] = 
{
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,          /* bLength */
  USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(USBD_WTOTALLENGTH),             /* wTotalLength */
  USBD_IF_NUM,                          /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD_CFGDESC_BMATTRIBUTES |           /* bmAttributes */
  (USBD_POWER << 6),
  USBD_CFGDESC_BMAXPOWER,               /* bMaxPower, device power consumption */

#if (USBD_ADC_ENABLE)                                                                                  
#if (USBD_MULTI_IF)
  ADC_DESC_IAD(USBD_ADC_CIF_NUM,2)
#endif
  ADC_DESC
  ADC_EP
#endif

#if (USBD_CDC_ACM_ENABLE)                                                                                  
#if (USBD_MULTI_IF)
  CDC_ACM_DESC_IAD(USBD_CDC_ACM_CIF_NUM,2)
#endif
  CDC_ACM_DESC_IF0
  CDC_ACM_EP_IF0
  CDC_ACM_DESC_IF1
  CDC_ACM_EP_IF1
#endif

#if (USBD_HID_ENABLE)
  HID_DESC
#if (USBD_HID_EP_INTOUT != 0)
  HID_EP_INOUT
#else
  HID_EP
#endif
#endif

#if (USBD_MSC_ENABLE)
  MSC_DESC
  MSC_EP
#endif

/* Terminator */
  0                                     /* bLength */
};
#endif

/* USB Device Create String Descriptor */
//USBD_##n 说明：USBD_与n连接，例如：USBD_STR_DEF(CDC_ACM_CIF_STRDESC)==USBD_##CDC_ACM_CIF_STRDESC==USBD_CDC_ACM_CIF_STRDESC
#define USBD_STR_DEF(n)                 \
  struct {                              \
    U8  len;                            \
    U8  type;                           \
    U16 str[sizeof(USBD_##n)/2-1];      \
  } desc##n                      

#define USBD_STR_VAL(n)                  \
 { sizeof(USBD_##n), USB_STRING_DESCRIPTOR_TYPE, USBD_##n }  

__weak const struct 
{
  struct 
	{
    U8  len;
    U8  type;
    U16 langid;
  } desc_langid;                      
  USBD_STR_DEF(STRDESC_MAN);			//L"X893 ARM"
  USBD_STR_DEF(STRDESC_PROD);			//L"CMSIS-DAP"
	#if  (USBD_STRDESC_SER_ENABLE)
		USBD_STR_DEF(STRDESC_SER);			//L"0001A0000000"
	#endif
	#if (USBD_ADC_ENABLE)			//未使用
		USBD_STR_DEF(ADC_CIF_STRDESC);		//L"USB_ADC"
		USBD_STR_DEF(ADC_SIF1_STRDESC);		//L"USB_ADC1"
		USBD_STR_DEF(ADC_SIF2_STRDESC);		//L"USB_ADC2"
	#endif
	#if (USBD_CDC_ACM_ENABLE)
		USBD_STR_DEF(CDC_ACM_CIF_STRDESC);	//L"CMSIS-DAP CDC"
		USBD_STR_DEF(CDC_ACM_DIF_STRDESC);	//L"CMSIS-DAP DCI"
	#endif
	#if (USBD_HID_ENABLE)
		USBD_STR_DEF(HID_STRDESC);					//L"CMSIS-DAP HID"
	#endif
	#if (USBD_MSC_ENABLE)
		USBD_STR_DEF(MSC_STRDESC);					//L"USB_MSC"
	#endif
} USBD_StringDescriptor									//usb_config.c 字符串描述符
= 
{
  { 4, USB_STRING_DESCRIPTOR_TYPE, USBD_STRDESC_LANGID },
  USBD_STR_VAL(STRDESC_MAN),						//#define USBD_STRDESC_MAN            L"X893 ARM"	 	//usb_config.c
  USBD_STR_VAL(STRDESC_PROD),						//#define USBD_STRDESC_PROD           L"CMSIS-DAP"	//usb_config.c
	#if (USBD_STRDESC_SER_ENABLE)		
		USBD_STR_VAL(STRDESC_SER),					//#define USBD_STRDESC_SER            L"0001A0000000"
	#endif
	#if (USBD_ADC_ENABLE)
		USBD_STR_VAL(ADC_CIF_STRDESC),			//#define USBD_ADC_CIF_STRDESC        L"USB_ADC"
		USBD_STR_VAL(ADC_SIF1_STRDESC),			//#define USBD_ADC_SIF1_STRDESC       L"USB_ADC1"
		USBD_STR_VAL(ADC_SIF2_STRDESC),			//#define USBD_ADC_SIF2_STRDESC       L"USB_ADC2"
	#endif
	#if (USBD_CDC_ACM_ENABLE)
		USBD_STR_VAL(CDC_ACM_CIF_STRDESC),	//#define USBD_CDC_ACM_CIF_STRDESC        L"CMSIS-DAP CDC"
		USBD_STR_VAL(CDC_ACM_DIF_STRDESC),	//#define USBD_CDC_ACM_DIF_STRDESC        L"CMSIS-DAP DCI"
	#endif
	#if (USBD_HID_ENABLE)
		USBD_STR_VAL(HID_STRDESC),					//#define USBD_HID_STRDESC            L"CMSIS-DAP HID"  //usb_config.c
	#endif
	#if (USBD_MSC_ENABLE)
		USBD_STR_VAL(MSC_STRDESC),					//#define USBD_MSC_STRDESC            L"USB_MSC"				//usb_config.c
	#endif
};

#endif

#endif  /* __USB_CONFIG__ */
