/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_User_Device_SerNum_%Instance%.c
 * Purpose: USB Device User module
 * Rev.:    V1.0.0
 *----------------------------------------------------------------------------*/
/*
 * USBD_User_Device_SerNum_%Instance%.c is a code template for the user specific 
 * USB Control Endpoint 0 request handling. It demonstrates how to specify serial 
 * number at runtime instead of fixed one specified in USBD_Config_%Instance%.c file.
 */
 
/**
 * \addtogroup usbd_coreFunctions_api
 *
 */
 
 
//! [code_USBD_User_Device]
 
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "rl_usb.h"
 
 
static bool    handle_request;
static uint8_t ser_no_string_desc[32];  // String Descriptor runtime value
 
// \brief Called during USBD_Initialize to initialize the USB Device
void USBD_Device%Instance%_Initialize (void) {
  // Handle Device Initialization

  handle_request = false;
}
 
// \brief Called during USBD_Uninitialize to de-initialize the USB Device
void USBD_Device%Instance%_Uninitialize (void) {
  // Handle Device De-initialization
}
 
// \brief Device Reset Event handling
void USBD_Device%Instance%_EventReset (void) {
  // Handle USB Bus Reset Event
}
 
// \brief Callback function called when Device %Instance% received SETUP PACKET on Control Endpoint 0
// \param[in]     setup_packet             pointer to received setup packet.
// \param[out]    buf                      pointer to data buffer used for data stage requested by setup packet.
// \param[out]    len                      pointer to number of data bytes in data stage requested by setup packet.
// \return        usbdRequestStatus        enumerator value indicating the function execution status
// \return        usbdRequestNotProcessed: request was not processed; processing will be done by USB library
// \return        usbdRequestOK:           request was processed successfully (send Zero-Length Packet if no data stage)
// \return        usbdRequestStall:        request was processed but is not supported (stall Endpoint 0)
usbdRequestStatus USBD_Device%Instance%_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len) {
 
  switch (setup_packet->bmRequestType.Type) {
    case USB_REQUEST_STANDARD:
      // Catch Get String Descriptor request for serial number string and return desired string:
      if ((setup_packet->bmRequestType.Dir       == USB_REQUEST_DEVICE_TO_HOST) &&      // Request to get
          (setup_packet->bmRequestType.Recipient == USB_REQUEST_TO_DEVICE     ) &&      // from device
          (setup_packet->bRequest                == USB_REQUEST_GET_DESCRIPTOR) &&      // the descriptor
          (setup_packet->wValueH                 == USB_STRING_DESCRIPTOR_TYPE) &&      // String Descriptor Type
          (setup_packet->wValueL                 == 0x03U                     ) &&      // Index of String = 3
          (setup_packet->wIndex                  == 0x0409U                   )) {      // Language ID = 0x0409 = English (United States)
        ser_no_string_desc[0] = 26U;    // Total size of String Descriptor
        ser_no_string_desc[1] = USB_STRING_DESCRIPTOR_TYPE;   // String Descriptor Type
        memcpy(&ser_no_string_desc[2], L"0001A0000001", 24);  // Serial Number String value
        *buf = ser_no_string_desc;      // Return pointer to prepared String Descriptor
        *len = 26U;                     // Return number of bytes of prepared String Descriptor
        handle_request = true;          // This request is handled
        return usbdRequestOK;           // Return status that custom handling for this request is used
      }
      break;
    case USB_REQUEST_CLASS:
      break;
    case USB_REQUEST_VENDOR:
      break;
    case USB_REQUEST_RESERVED:
      break;
  }
 
  return usbdRequestNotProcessed;
}
 
// \brief Callback function called when SETUP PACKET was processed by USB library
// \param[in]     setup_packet            pointer to processed setup packet.
void USBD_Device%Instance%_Endpoint0_SetupPacketProcessed (const USB_SETUP_PACKET *setup_packet) {
 
  switch (setup_packet->bmRequestType.Type) {
    case USB_REQUEST_STANDARD:
      break;
    case USB_REQUEST_CLASS:
      break;
    case USB_REQUEST_VENDOR:
      break;
    case USB_REQUEST_RESERVED:
      break;
  }
}
 
// \brief Callback function called when Device %Instance% received OUT DATA on Control Endpoint 0
// \param[in]     len                      number of received data bytes.
// \return        usbdRequestStatus        enumerator value indicating the function execution status
// \return        usbdRequestNotProcessed: request was not processed; processing will be done by USB library
// \return        usbdRequestOK:           request was processed successfully (send Zero-Length Packet)
// \return        usbdRequestStall:        request was processed but is not supported (stall Endpoint 0)
// \return        usbdRequestNAK:          request was processed but the device is busy (return NAK)
usbdRequestStatus USBD_Device%Instance%_Endpoint0_OutDataReceived (uint32_t len) {

  return usbdRequestNotProcessed;
}
 
// \brief Callback function called when Device %Instance% sent IN DATA on Control Endpoint 0
// \param[in]     len                      number of sent data bytes.
// \return        usbdRequestStatus        enumerator value indicating the function execution status
// \return        usbdRequestNotProcessed: request was not processed; processing will be done by USB library
// \return        usbdRequestOK:           request was processed successfully (return ACK)
// \return        usbdRequestStall:        request was processed but is not supported (stall Endpoint 0)
// \return        usbdRequestNAK:          request was processed but the device is busy (return NAK)
usbdRequestStatus USBD_Device%Instance%_Endpoint0_InDataSent (uint32_t len) {

  if (handle_request == true) {
    handle_request = false;
    return usbdRequestOK;               // Acknowledge custom handled request
  }

  return usbdRequestNotProcessed;
}
 
//! [code_USBD_User_Device]
