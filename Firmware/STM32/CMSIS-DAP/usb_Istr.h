
#ifndef __usbd_STM32F103__
#define __usbd_STM32F103__

#include "RTL.h"
#include "usb_def.h"

#include "stddef.h"
#include "stdint.h"



void EP_Reset (U32 EPNum);
void EP_Status (U32 EPNum, U32 stat);
void USBD_Init (void);
void USBD_Connect (BOOL con);
void USBD_Reset (void);
void USBD_Suspend (void);
void USBD_Resume (void);
void USBD_WakeUp (void);
void USBD_WakeUpCfg (BOOL cfg);
void USBD_SetAddress (U32 adr, U32 setup);
void USBD_Configure (BOOL cfg);
void USBD_ConfigEP (USB_ENDPOINT_DESCRIPTOR *pEPD);
void USBD_DirCtrlEP (U32 dir);
void USBD_EnableEP (U32 EPNum);
void USBD_DisableEP (U32 EPNum);
void USBD_ResetEP (U32 EPNum);
void USBD_SetStallEP (U32 EPNum);
void USBD_ClrStallEP (U32 EPNum);
void USBD_ClearEPBuf (U32 EPNum);
U32 USBD_ReadEP(U32 EPNum, U8 *pData);
U32 MSC_ReadEP(U32 EPNum, U8 *pData);
U32 USBD_WriteEP (U32 EPNum, U8 *pData, U32 cnt);
U32 USBD_GetFrame (void);
void USB_LP_CAN1_RX0_IRQHandler(void);



void USB_Istr(void);

#ifdef __RTX
void USB_Istr_RTX(void);
U32 USBD_GetError (void);
#endif

#endif  /* __DAP_H__ */
