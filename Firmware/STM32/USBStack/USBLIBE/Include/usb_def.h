/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usb_def.h
 * Purpose: USB Definitions
 * Rev.:    V6.2
 *----------------------------------------------------------------------------*/

#ifndef __USB_DEF_H
#define __USB_DEF_H

#include <stdint.h>

/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif

/* USB Speed */
#define USB_SPEED_LOW                   0
#define USB_SPEED_FULL                  1
#define USB_SPEED_HIGH                  2

/* USB PID Types */
#define USB_PID_OUT                     1
#define USB_PID_IN                      9
#define USB_PID_SOF                     5
#define USB_PID_SETUP                   13
#define USB_PID_DATA0                   3
#define USB_PID_DATA1                   11
#define USB_PID_DATA2                   7
#define USB_PID_MDATA                   15
#define USB_PID_ACK                     2
#define USB_PID_NAK                     10
#define USB_PID_STALL                   14
#define USB_PID_NYET                    6
#define USB_PID_PRE                     12
#define USB_PID_ERR                     12
#define USB_PID_SPLIT                   8
#define USB_PID_PING                    4
#define USB_PID_RESERVED                0

/* bmRequestType.Dir */
#define USB_REQUEST_HOST_TO_DEVICE      0
#define USB_REQUEST_DEVICE_TO_HOST      1

/* bmRequestType.Type */
#define USB_REQUEST_STANDARD            0
#define USB_REQUEST_CLASS               1
#define USB_REQUEST_VENDOR              2
#define USB_REQUEST_RESERVED            3

/* bmRequestType.Recipient */
#define USB_REQUEST_TO_DEVICE           0
#define USB_REQUEST_TO_INTERFACE        1
#define USB_REQUEST_TO_ENDPOINT         2
#define USB_REQUEST_TO_OTHER            3

/// bmRequestType Definition
typedef __packed struct _USB_REQUEST_TYPE {
  uint8_t Recipient : 5;                ///< D4..0: Recipient
  uint8_t Type      : 2;                ///< D6..5: Type
  uint8_t Dir       : 1;                ///< D7:    Data Transfer Direction
} USB_REQUEST_TYPE;

/* USB Standard Request Codes */
#define USB_REQUEST_GET_STATUS                  0
#define USB_REQUEST_CLEAR_FEATURE               1
#define USB_REQUEST_SET_FEATURE                 3
#define USB_REQUEST_SET_ADDRESS                 5
#define USB_REQUEST_GET_DESCRIPTOR              6
#define USB_REQUEST_SET_DESCRIPTOR              7
#define USB_REQUEST_GET_CONFIGURATION           8
#define USB_REQUEST_SET_CONFIGURATION           9
#define USB_REQUEST_GET_INTERFACE               10
#define USB_REQUEST_SET_INTERFACE               11
#define USB_REQUEST_SYNC_FRAME                  12

/* USB GET_STATUS Bit Values */
#define USB_GETSTATUS_SELF_POWERED              0x01
#define USB_GETSTATUS_REMOTE_WAKEUP             0x02
#define USB_GETSTATUS_ENDPOINT_STALL            0x01

/* USB Standard Feature selectors */
#define USB_FEATURE_ENDPOINT_STALL              0
#define USB_FEATURE_REMOTE_WAKEUP               1

/// USB Default Control Pipe Setup Packet
typedef __packed struct _USB_SETUP_PACKET {
  USB_REQUEST_TYPE bmRequestType;       ///< Characteristics of request
  uint8_t          bRequest;            ///< Specific request
  __packed union {
    uint16_t       wValue;              ///< Value according to request
    __packed struct {
      uint8_t      wValueL;
      uint8_t      wValueH;
    };
  };
  __packed union {
    uint16_t       wIndex;              ///< Index or Offset according to request
    __packed struct {
      uint8_t      wIndexL;
      uint8_t      wIndexH;
    };
  };
  uint16_t         wLength;             ///< Number of bytes to transfer if there is a Data stage
} USB_SETUP_PACKET;


/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE                1
#define USB_CONFIGURATION_DESCRIPTOR_TYPE         2
#define USB_STRING_DESCRIPTOR_TYPE                3
#define USB_INTERFACE_DESCRIPTOR_TYPE             4
#define USB_ENDPOINT_DESCRIPTOR_TYPE              5
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE      6
#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE    7
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE       8
#define USB_OTG_DESCRIPTOR_TYPE                   9
#define USB_DEBUG_DESCRIPTOR_TYPE                 10
#define USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE 11

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED               0x00
#define USB_DEVICE_CLASS_AUDIO                  0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS         0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE        0x03
#define USB_DEVICE_CLASS_MONITOR                0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE     0x05
#define USB_DEVICE_CLASS_POWER                  0x06
#define USB_DEVICE_CLASS_PRINTER                0x07
#define USB_DEVICE_CLASS_STORAGE                0x08
#define USB_DEVICE_CLASS_HUB                    0x09
#define USB_DEVICE_CLASS_MISCELLANEOUS          0xEF
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC        0xFF

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_POWERED_MASK                 0x40
#define USB_CONFIG_BUS_POWERED                  0x80
#define USB_CONFIG_SELF_POWERED                 0xC0
#define USB_CONFIG_REMOTE_WAKEUP                0x20

/* bMaxPower in Configuration Descriptor */
#define USB_CONFIG_POWER_MA(mA)                 ((mA)/2)

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK             0x80
#define USB_ENDPOINT_OUT(addr)                  ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)                   ((addr) | 0x80)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK                  0x03
#define USB_ENDPOINT_TYPE_CONTROL               0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS           0x01
#define USB_ENDPOINT_TYPE_BULK                  0x02
#define USB_ENDPOINT_TYPE_INTERRUPT             0x03
#define USB_ENDPOINT_SYNC_MASK                  0x0C
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION    0x00
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS          0x04
#define USB_ENDPOINT_SYNC_ADAPTIVE              0x08
#define USB_ENDPOINT_SYNC_SYNCHRONOUS           0x0C
#define USB_ENDPOINT_USAGE_MASK                 0x30
#define USB_ENDPOINT_USAGE_DATA                 0x00
#define USB_ENDPOINT_USAGE_FEEDBACK             0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK    0x20
#define USB_ENDPOINT_USAGE_RESERVED             0x30

/// USB Standard Device Descriptor
typedef __packed struct _USB_DEVICE_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t  iManufacturer;
  uint8_t  iProduct;
  uint8_t  iSerialNumber;
  uint8_t  bNumConfigurations;
} USB_DEVICE_DESCRIPTOR;

/// USB 2.0 Device Qualifier Descriptor
typedef __packed struct _USB_DEVICE_QUALIFIER_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint8_t  bNumConfigurations;
  uint8_t  bReserved;
} USB_DEVICE_QUALIFIER_DESCRIPTOR;

/// USB Standard Configuration Descriptor
typedef __packed struct _USB_CONFIGURATION_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationValue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
} USB_CONFIGURATION_DESCRIPTOR;

/// USB Standard Interface Descriptor
typedef __packed struct _USB_INTERFACE_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bInterfaceNumber;
  uint8_t  bAlternateSetting;
  uint8_t  bNumEndpoints;
  uint8_t  bInterfaceClass;
  uint8_t  bInterfaceSubClass;
  uint8_t  bInterfaceProtocol;
  uint8_t  iInterface;
} USB_INTERFACE_DESCRIPTOR;

/// USB Standard Endpoint Descriptor
typedef __packed struct _USB_ENDPOINT_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bEndpointAddress;
  uint8_t  bmAttributes;
  uint16_t wMaxPacketSize;
  uint8_t  bInterval;
} USB_ENDPOINT_DESCRIPTOR;

/// USB String Descriptor
typedef __packed struct _USB_STRING_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bString;
} USB_STRING_DESCRIPTOR;

/// USB Common Descriptor
typedef __packed struct _USB_COMMON_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
} USB_COMMON_DESCRIPTOR;

/// USB Interface Association Descriptor
typedef __packed struct _USB_INTERFACE_ASSOCIATION_DESCRIPTOR {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bFirstInterface;
  uint8_t  bInterfaceCount;
  uint8_t  bFunctionClass;
  uint8_t  bFunctionSubclass;
  uint8_t  bFunctionProtocol;
  uint8_t  iFunction;
} USB_INTERFACE_ASSOCIATION_DESCRIPTOR;

/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif

#endif  /* __USB_DEF_H */
