/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBH_PL2303.c
 * Purpose: USB Host (USBH) - Custom Class - Prolific PL2303 USB to serial
 *          RS232 adapter driver
 * Rev.:    V6.2
 *----------------------------------------------------------------------------*/
/*
 * USBH_PL2303.c is a Prolific PL2303 USB to serial RS232 adapter driver
 * for USB Host stack implemented as USB Host Custom Class driver.
 * Prolific PL2303 USB to serial RS232 adapter is similar to the CDC device
 * but using vendor specific class device with interface containing
 * 1 Bulk IN, 1 Bulk OUT and 1 Interrupt IN Endpoints.
 * This implementation supports only one instance.
 *
 * The driver implements 4 callback functions called by the USB Host core
 * when device is connected or disconnected, these are:
 *   USBH_CustomClass_Configure
 *   USBH_CustomClass_Unconfigure
 *   USBH_CustomClass_Initialize
 *   USBH_CustomClass_Uninitialize
 * 
 * First to enable USB Host Controller (if not already enabled) call:
 *   USBH_Initialize (ctrl_num);
 */
 
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
 
  // Supported device: - Prolific PL2303 (VID = 0x067B, PID = 0x2303)
  if ((ptr_dev_desc->idVendor != 0x067B) || (ptr_dev_desc->idProduct != 0x2303))
    return 0xFF;
 
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
  USB_SETUP_PACKET setup_packet;
  uint8_t          buf[8];
 
  // Custom PL2303 initialization
  setup_packet.bmRequestType.Dir      = USB_REQUEST_DEVICE_TO_HOST;
  setup_packet.bmRequestType.Type     = USB_REQUEST_VENDOR;
  setup_packet.bmRequestType.Recipient= USB_REQUEST_TO_DEVICE;
  setup_packet.bRequest               = 1;
  setup_packet.wValue                 = U16_LE(0x8484);
  setup_packet.wIndex                 = U16_LE(0);
  setup_packet.wLength                = U16_LE(1);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.wValue                 = U16_LE(0x0404);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.bmRequestType.Dir      = USB_REQUEST_DEVICE_TO_HOST;
  setup_packet.wValue                 = U16_LE(0x8484);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.wValue                 = U16_LE(0x8383);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.wValue                 = U16_LE(0x8484);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.wValue                 = U16_LE(0x0404);
  setup_packet.wIndex                 = U16_LE(1);
  setup_packet.wLength                = U16_LE(0);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, NULL, 0) != usbOK) return usbClassErrorCustom;
 
  setup_packet.bmRequestType.Dir      = USB_REQUEST_DEVICE_TO_HOST;
  setup_packet.wValue                 = U16_LE(0x8484);
  setup_packet.wIndex                 = U16_LE(0);
  setup_packet.wLength                = U16_LE(1);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.wValue                 = U16_LE(0x8383);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf,  1) != usbOK) return usbClassErrorCustom;
 
  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.wValue                 = U16_LE(0);
  setup_packet.wIndex                 = U16_LE(1);
  setup_packet.wLength                = U16_LE(0);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, NULL, 0) != usbOK) return usbClassErrorCustom;
 
  setup_packet.wValue                 = U16_LE(1);
  setup_packet.wIndex                 = U16_LE(0);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, NULL, 0) != usbOK) return usbClassErrorCustom;
 
  setup_packet.wValue                 = U16_LE(2);
  setup_packet.wIndex                 = U16_LE(0x44);
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, NULL, 0) != usbOK) return usbClassErrorCustom;
 
  // Initial CDC SetLineCoding request: Set 9600 baud, 8 data bits, 1 stop bit, no parity
  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.bmRequestType.Type     = USB_REQUEST_CLASS;
  setup_packet.bmRequestType.Recipient= USB_REQUEST_TO_INTERFACE;
  setup_packet.bRequest               = 0x20;
  setup_packet.wValue                 = U16_LE(0);
  setup_packet.wIndex                 = U16_LE(0);
  setup_packet.wLength                = U16_LE(7);
  *((uint32_t *)&buf[0]) = U32_LE(9600);// Data terminal rate in bits per second = 9600 baud
  buf[4]                 = 0;           // Number of stop bits = 1
  buf[5]                 = 0;           // Parity bit type = None
  buf[6]                 = 8;           // Number of data bits = 8
  if (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, buf, 7) != usbOK) return usbClassErrorCustom;
 
  return usbOK;
}
 
/// \brief De-initialize Custom Class Device instance
/// \param[in]     instance             index of class device instance.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_CustomClass_Uninitialize (uint8_t instance) {

  return usbOK;
}
