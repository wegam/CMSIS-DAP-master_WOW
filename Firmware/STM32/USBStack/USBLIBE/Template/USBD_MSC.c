/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host:MSC
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_MSC_%Instance%.c
 * Purpose: Functions for media ownership control between USB and File System
 * Rev.:    V6.3
 *----------------------------------------------------------------------------*/
/*
 * USBD_MSC_%Instance%.c is a code template for the application specific functionality of
 * the USB Device MSC class %Instance% instance. It implements the ownership control over
 * media and changing the owner of media between USB and File System.
 *
 * USBD_MSC_%Instance%.h is the related header file.
 *
 * To select USB as owner of media you can call function:
 *   USBD_MSC%Instance%_SetMediaOwnerUSB ()
 *
 * To select File System as owner of media you can call function:
 *   USBD_MSC%Instance%_SetMediaOwnerFS  ()
 *
 */
 
#include "stdint.h"                     // data type definitions
#include "stdbool.h"                    // data type definitions
#include "cmsis_os.h"                   // Keil.MDK-Pro::CMSIS:CORE
 
#include "USBD_MSC_%Instance%.h"                 // Media ownership control for USB Device
 
extern volatile uint8_t usbd_msc%Instance%_media_own;    // USB MSC%Instance% media ownership
 
 
//! [usbd_msc_setmediaownerusb]
/// \brief Set USB as media owner
/// \return     execution status
///               - USBD_MSC_OK           = Media ownership changed successfully
///               - USBD_MSC_ERROR        = Media ownership change has failed (due timeout)
int32_t USBD_MSC%Instance%_SetMediaOwnerUSB (void) {
  uint32_t timeout_cnt;
 
  timeout_cnt = 300U;                   // 3 second timeout (300 * 10 ms)
  usbd_msc%Instance%_media_own = USBD_MSC%Instance%_MEDIA_OWN_CHG | USBD_MSC%Instance%_MEDIA_OWN_USB;
  while (usbd_msc%Instance%_media_own & USBD_MSC%Instance%_MEDIA_OWN_CHG) {
    osDelay(10);
    if ((--timeout_cnt) == 0) { return USBD_MSC%Instance%_ERROR; }
  }
 
  return USBD_MSC%Instance%_OK;
}
//! [usbd_msc_setmediaownerusb]
 
 
//! [usbd_msc_setmediaownerfs]
/// \brief Set File System as media owner
/// \return     execution status
///               - USBD_MSC_OK           = Media ownership changed successfully
///               - USBD_MSC_ERROR        = Media ownership change has failed (due timeout)
int32_t USBD_MSC%Instance%_SetMediaOwnerFS (void) {
  uint32_t timeout_cnt;
 
  timeout_cnt = 300U;                   // 3 second timeout (300 * 10 ms)
  usbd_msc%Instance%_media_own = USBD_MSC%Instance%_MEDIA_OWN_CHG;
  while (usbd_msc%Instance%_media_own & USBD_MSC%Instance%_MEDIA_OWN_CHG) {
    osDelay(10);
    if ((--timeout_cnt) == 0) { return USBD_MSC%Instance%_ERROR; }
  }
 
  return USBD_MSC%Instance%_OK;
}
//! [usbd_msc_setmediaownerfs]
