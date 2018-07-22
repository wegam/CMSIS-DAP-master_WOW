/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBH_User_CustomClass.c
 * Purpose: USB Host (USBH) - Custom Class User template
 * Rev.:    V6.2
 *----------------------------------------------------------------------------*/
/*
 * USBH_User_CustomClass.c is a code template for the Custom Class driver
 * implementation on the USB Host stack.
 * This implementation supports only one instance.
 *
 * The template implements 4 callback functions called by the USB Host core
 * when device is connected or disconnected, these are:
 *   USBH_CustomClass_Configure
 *   USBH_CustomClass_Unconfigure
 *   USBH_CustomClass_Initialize
 *   USBH_CustomClass_Uninitialize
 * 
 * First to enable USB Host Controller (if not already enabled) call:
 *   USBH_Initialize (ctrl_num);
 */
 
/**
 * \addtogroup usbh_custom_classFunctions
 *
 */
 
 
//! [code_USBH_User_CustomClass]
 
#include <stdint.h>
#include "rl_usb.h"
 
// Interface class, subclass and protocol of the device that is supported
#define CUSTOM_CLASS_IF_CLASS           USB_DEVICE_CLASS_VENDOR_SPECIFIC
#define CUSTOM_CLASS_IF_SUBCLASS        0
#define CUSTOM_CLASS_IF_PROTOCOL        0
 
uint8_t    USBH_CustomClass_Ctrl     =   0;    // Controller number used for USB transfers
USBH_PIPE *USBH_CustomClass_Pipes[8] = { 0 };  // Pointers to Pipes
 
/************************** Class Driver Functions ****************************/
 
/// \brief Analyse device configuration and configure resources
/// \param[in]     ptr_dev              pointer to device structure.
/// \param[in]     ptr_dev_desc         pointer to device descriptor.
/// \param[in]     ptr_cfg_desc         pointer to configuration descriptor.
/// \return        value <= 127         index of configured custom class device instance.
/// \return        value == 0xFF        configuration failed.
uint8_t USBH_CustomClass_Configure (const USBH_DEV *ptr_dev, const USB_DEVICE_DESCRIPTOR *ptr_dev_desc, const USB_CONFIGURATION_DESCRIPTOR *ptr_cfg_desc) {
  USBH_PIPE                *ptr_pipe;
  USB_INTERFACE_DESCRIPTOR *ptr_if_desc;
  USB_ENDPOINT_DESCRIPTOR  *ptr_ep_desc;
  uint8_t                   num, i;
 
  USBH_CustomClass_Ctrl = ptr_dev->ctrl;  // Store controller number
  ptr_if_desc = (USB_INTERFACE_DESCRIPTOR *)((uint32_t)ptr_cfg_desc + ptr_cfg_desc->bLength);
  num = ptr_if_desc->bNumEndpoints;       // Number of endpoints
 
// Check if this is the supported device (VID, PID)
// Vendor ID value:  ptr_dev_desc->idVendor
// Product ID value: ptr_dev_desc->idProduct
 
  switch (ptr_if_desc->bInterfaceClass) {
    case CUSTOM_CLASS_IF_CLASS:             // Interface class
      switch (ptr_if_desc->bInterfaceSubClass) {
        case CUSTOM_CLASS_IF_SUBCLASS:      // Interface subclass
          switch (ptr_if_desc->bInterfaceProtocol) {
            case CUSTOM_CLASS_IF_PROTOCOL:  // Interface protocol
              // Create Pipes
              ptr_ep_desc = (USB_ENDPOINT_DESCRIPTOR *)((uint32_t)ptr_if_desc + ptr_if_desc->bLength);
              i           = 0;
              while (num--) {
                ptr_pipe = USBH_PipeCreate (ptr_dev->ctrl, ptr_dev->dev_addr, ptr_dev->dev_speed, 0, 0, ptr_ep_desc->bEndpointAddress, ptr_ep_desc->bmAttributes & USB_ENDPOINT_TYPE_MASK, ptr_ep_desc->wMaxPacketSize & 0x7FF, ptr_ep_desc->bInterval);
                if (!ptr_pipe) {
                  // If creation of pipe failed delete previously created pipes
                  for (i = 0; i < 8; i++) {
                    if (USBH_CustomClass_Pipes[i]) {
                      USBH_PipeDelete (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[i]);
                      USBH_CustomClass_Pipes[i] = NULL;
                    }
                  }
                  return 0xFF;
                }
                USBH_CustomClass_Pipes[i++] = ptr_pipe;
                ptr_ep_desc++;
              }
              return 0;                 // Device connected and configured
                                        // Only single instance supported
                                        // so it's instance index is 0
          }
          break;
      }
      break;
  }
 
  return 0xFF;                          // Device not handled
}
 
/// \brief De-configure resources
/// \param[in]     instance             index of class device instance.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_CustomClass_Unconfigure (uint8_t instance) {
  uint8_t i;
 
  USBH_CustomClass_Ctrl = 0;
 
  for (i = 0; i < 8; i++) {
    if (USBH_CustomClass_Pipes[i]) {
      USBH_PipeDelete (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[i]);
      USBH_CustomClass_Pipes[i] = NULL;
    }
  }
 
  return usbOK;
}
 
/// \brief Initialize Custom Class Device instance
/// \param[in]     instance             index of class device instance.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_CustomClass_Initialize (uint8_t instance) {
//  Add code for initializing device
 
  return usbOK;
}
 
/// \brief De-initialize Custom Class Device instance
/// \param[in]     instance             index of class device instance.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_CustomClass_Uninitialize (uint8_t instance) {
  // Add code for de-initializing device
 
  return usbOK;
}
 
//! [code_USBH_User_CustomClass]
