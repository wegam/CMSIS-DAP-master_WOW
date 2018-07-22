/*------------------------------------------------------------------------------
 *      RL-ARM - USB
 *------------------------------------------------------------------------------
 *      Name:    usbd_msc.h
 *      Purpose: USB Device Mass Storage Device Class header file
 *      Rev.:    V4.70
 *------------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __USBD_MSC_H__
#define __USBD_MSC_H__

#include "RTL.h"
/*--------------------------- Global variables -------------------------------*/

/* USB Device Mass Storage Device Class Global Variables */
extern       BOOL USBD_MSC_MediaReady;
extern       BOOL USBD_MSC_ReadOnly;
extern       U32  USBD_MSC_MemorySize;
extern       U32  USBD_MSC_BlockSize;
extern       U32  USBD_MSC_BlockGroup;
extern       U32  USBD_MSC_BlockCount;
extern       U8  *USBD_MSC_BlockBuf;


/*--------------------------- Event handling routines ------------------------*/

extern        void USBD_MSC_EP_BULKIN_Event      (U32 event);
extern        void USBD_MSC_EP_BULKOUT_Event     (U32 event);
extern        void USBD_MSC_EP_BULK_Event        (U32 event);

//º¯Êý²¹³ä
void USBD_MSC_SetStallEP (U32 EPNum);
void USBD_MSC_ClrStallEP (U32 EPNum);
BOOL USBD_MSC_Reset (void);
BOOL USBD_MSC_GetMaxLUN (void);
BOOL USBD_MSC_CheckMedia (void);
void USBD_MSC_MemoryRead (void);
void USBD_MSC_MemoryWrite (void);
void USBD_MSC_MemoryVerify (void);
BOOL USBD_MSC_RWSetup (void);
BOOL USBD_MSC_DataInFormat (void);
void USBD_MSC_DataInTransfer (void);
void USBD_MSC_TestUnitReady (void);
void USBD_MSC_RequestSense (void);
void USBD_MSC_Inquiry (void);
void USBD_MSC_StartStopUnit (void);
void USBD_MSC_MediaRemoval (void);
void USBD_MSC_ModeSense6 (void);
void USBD_MSC_ModeSense10 (void);
void USBD_MSC_ReadCapacity (void);
void USBD_MSC_ReadFormatCapacity (void);
void USBD_MSC_SynchronizeCache (void);
void USBD_MSC_ATAPassThrough (void);
void USBD_MSC_ServiceActionIn16 (void);
void USBD_MSC_GetCBW (void);
void USBD_MSC_SetCSW (void);
void USBD_MSC_BulkIn (void);
void USBD_MSC_BulkOut (void);
void USBD_MSC_EP_BULKIN_Event (U32 event);
void USBD_MSC_EP_BULKOUT_Event (U32 event);
void USBD_MSC_EP_BULK_Event (U32 event);

#ifdef __RTX
extern __task void USBD_RTX_MSC_EP_BULKIN_Event  (void);
extern __task void USBD_RTX_MSC_EP_BULKOUT_Event (void);
extern __task void USBD_RTX_MSC_EP_BULK_Event    (void);
#endif

#endif  /* __USBD_MSC_H__ */
