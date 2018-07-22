/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_Config_CustomClass_%Instance%.h
 * Purpose: USB Device Custom Class Configuration
 * Rev.:    V5.00
 *----------------------------------------------------------------------------*/

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

// <h>USB Device: Custom Class %Instance%
// <i>Custom Class can be used to make support for Standard or Vendor-Specific Class
//   <o>Assign Device Class to USB Device # <0-3>
//   <i>Select USB Device that is used for this Device Class instance
#define USBD_CUSTOM_CLASS%Instance%_DEV                                     0


//   <e>Interface
#define USBD_CUSTOM_CLASS%Instance%_IF0_EN                                  1

//     <h>Interface Settings
//     <i>The Interface Settings are used to create the Interface Descriptor.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about the Interface Descriptor.

//       <o>Interface Number <0-255>
//       <i>Defines the value for bInterfaceNumber
//       <i>Each USB Device Interface has a sequential Interface Number starting with 0.
//       <i>Several Interfaces may have the same Interface Number; in this case the value
//       <i>of Alternate Setting is used to differ between the Interfaces. For a
//       <i>composite device the Interface Numbers of the custom classes must be contiguous.
#define USBD_CUSTOM_CLASS%Instance%_IF0_NUM                                 0

//       <o>Alternate Setting <0=>0 <1=>1 <2=>2 <3=>3
//       <i>Defines the value for bAlternateSetting
//       <i>A sequential number starting with 0 to indentify the Interface Descriptors
//       <i>that share the same value for Interface Number.
#define USBD_CUSTOM_CLASS%Instance%_IF0_ALT                                 0

//       <o.0..7>Class Code
//         <i>Class Codes are defined by USB-IF. For more information refer to
//         <i>http://www.usb.org/developers/defined_class.
//         <0x00=>0x00: Indicate a Null Class Code triple
//         <0x01=>0x01: Audio
//         <0x02=>0x02: Communications and CDC Control
//         <0x03=>0x03: HID (Human Interface Device)
//         <0x05=>0x05: Physical
//         <0x06=>0x06: Image
//         <0x07=>0x07: Printer
//         <0x08=>0x08: Mass Storage
//         <0x0A=>0x0A: CDC-Data
//         <0x0B=>0x0B: Smart Card
//         <0x0D=>0x0D: Content Security
//         <0x0E=>0x0E: Video
//         <0x0F=>0x0F: Personal Healthcare
//         <0x10=>0x10: Audio/Video Devices
//         <0xDC=>0xDC: Diagnostic Device
//         <0xE0=>0xE0: Wireless Controller
//         <0xEF=>0xEF: Miscellaneous
//         <0xFE=>0xFE: Application Specific
//         <0xFF=>0xFF: Vendor Specific
#define USBD_CUSTOM_CLASS%Instance%_IF0_CLASS                               0xFF

//       <o.0..7>Subclass Code <0x00-0xFF>
//       <i>The possible values depend on the Class Code:
//       <i>Class Code 0x00: Subclass Code must be 0
//       <i>Class Code 0x01 .. 0xFE: Subclass Code is defined by USB-IF
//       <i>Class Code 0xFF: Subclass Code can be 0x00 .. 0xFF
#define USBD_CUSTOM_CLASS%Instance%_IF0_SUBCLASS                            0x00

//       <o.0..7>Protocol Code <0x00-0xFF>
//       <i>The Protocol Code value defines the protocol used on this interface:
//       <i>Protocol Code 0x00: class-specific protocol not used
//       <i>Protocol Code 0x01 .. 0xFE: class-specific protocol used
//       <i>Protocol Code 0xFF: vendor-specific protocol used
#define USBD_CUSTOM_CLASS%Instance%_IF0_PROTOCOL                            0x00

//     </h>

//     <h>Endpoint Settings
//     <i>Following settings are used to create the Endpoint Descriptors.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about Endpoint Descriptors.

//       <e>Bulk OUT Endpoint
//       <i>Select if Bulk OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_OUT_EN                      0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_OUT                         1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_OUT_FS_WMAXPACKETSIZE       64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_OUT_HS_WMAXPACKETSIZE       512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_OUT_HS_BINTERVAL            0

//           </h>
//         </h>
//       </e>

//       <e>Bulk IN Endpoint
//       <i>Select if Bulk IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_IN_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_IN                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_IN_FS_WMAXPACKETSIZE        64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_IN_HS_WMAXPACKETSIZE        512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_BULK_IN_HS_BINTERVAL             0

//           </h>
//         </h>
//       </e>

//       <e>Interrupt OUT Endpoint
//       <i>Select if Interrupt OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_OUT_FS_WMAXPACKETSIZE        4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_OUT_FS_BINTERVAL             16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_OUT_HS_WMAXPACKETSIZE        4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_OUT_HS_BINTERVAL             5

//           </h>
//         </h>
//       </e>

//       <e>Interrupt IN Endpoint
//       <i>Select if Interrupt IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_IN_FS_WMAXPACKETSIZE         4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_IN_FS_BINTERVAL              16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_IN_HS_WMAXPACKETSIZE         4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_INT_IN_HS_BINTERVAL              5

//           </h>
//         </h>
//       </e>

//       <e>Isochronous OUT Endpoint
//       <i>Select if Isochronous OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_OUT_FS_WMAXPACKETSIZE        64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_OUT_FS_BINTERVAL             1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_OUT_HS_WMAXPACKETSIZE        64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_OUT_HS_BINTERVAL             1

//           </h>
//         </h>
//       </e>

//       <e>Isochronous IN Endpoint
//       <i>Select if Isochronous IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_IN_FS_WMAXPACKETSIZE         64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_IN_FS_BINTERVAL              1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_IN_HS_WMAXPACKETSIZE         64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF0_EP_ISO_IN_HS_BINTERVAL              1

//           </h>
//         </h>
//       </e>
//     </h>

//     <h>String Settings
//     <i>Following settings are used to create String Descriptor(s)

//       <s.126>Interface String
#define USBD_CUSTOM_CLASS%Instance%_IF0_STR                                 L"USB_CUSTOM_CLASS%Instance%_IF0"

//     </h>
//   </e>


//   <e>Interface
#define USBD_CUSTOM_CLASS%Instance%_IF1_EN                                  0

//     <h>Interface Settings
//     <i>The Interface Settings are used to create the Interface Descriptor.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about the Interface Descriptor.

//       <o>Interface Number <0-255>
//       <i>Defines the value for bInterfaceNumber
//       <i>Each USB Device Interface has a sequential Interface Number starting with 0.
//       <i>Several Interfaces may have the same Interface Number; in this case the value
//       <i>of Alternate Setting is used to differ between the Interfaces. For a
//       <i>composite device the Interface Numbers of the custom classes must be contiguous.
#define USBD_CUSTOM_CLASS%Instance%_IF1_NUM                                 1

//       <o>Alternate Setting <0=>0 <1=>1 <2=>2 <3=>3
//       <i>Defines the value for bAlternateSetting
//       <i>A sequential number starting with 0 to indentify the Interface Descriptors
//       <i>that share the same value for Interface Number.
#define USBD_CUSTOM_CLASS%Instance%_IF1_ALT                                 0

//       <o.0..7>Class Code
//         <i>Class Codes are defined by USB-IF. For more information refer to
//         <i>http://www.usb.org/developers/defined_class.
//         <0x00=>0x00: Indicate a Null Class Code triple
//         <0x01=>0x01: Audio
//         <0x02=>0x02: Communications and CDC Control
//         <0x03=>0x03: HID (Human Interface Device)
//         <0x05=>0x05: Physical
//         <0x06=>0x06: Image
//         <0x07=>0x07: Printer
//         <0x08=>0x08: Mass Storage
//         <0x0A=>0x0A: CDC-Data
//         <0x0B=>0x0B: Smart Card
//         <0x0D=>0x0D: Content Security
//         <0x0E=>0x0E: Video
//         <0x0F=>0x0F: Personal Healthcare
//         <0x10=>0x10: Audio/Video Devices
//         <0xDC=>0xDC: Diagnostic Device
//         <0xE0=>0xE0: Wireless Controller
//         <0xEF=>0xEF: Miscellaneous
//         <0xFE=>0xFE: Application Specific
//         <0xFF=>0xFF: Vendor Specific
#define USBD_CUSTOM_CLASS%Instance%_IF1_CLASS                               0xFF

//       <o.0..7>Subclass Code <0x00-0xFF>
//       <i>The possible values depend on the Class Code:
//       <i>Class Code 0x00: Subclass Code must be 0
//       <i>Class Code 0x01 .. 0xFE: Subclass Code is defined by USB-IF
//       <i>Class Code 0xFF: Subclass Code can be 0x00 .. 0xFF
#define USBD_CUSTOM_CLASS%Instance%_IF1_SUBCLASS                            0x00

//       <o.0..7>Protocol Code <0x00-0xFF>
//       <i>The Protocol Code value defines the protocol used on this interface:
//       <i>Protocol Code 0x00: class-specific protocol not used
//       <i>Protocol Code 0x01 .. 0xFE: class-specific protocol used
//       <i>Protocol Code 0xFF: vendor-specific protocol used
#define USBD_CUSTOM_CLASS%Instance%_IF1_PROTOCOL                            0x00

//     </h>

//     <h>Endpoint Settings
//     <i>Following settings are used to create the Endpoint Descriptors.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about Endpoint Descriptors.

//       <e>Bulk OUT Endpoint
//       <i>Select if Bulk OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_OUT_EN                      0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_OUT                         1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_OUT_FS_WMAXPACKETSIZE       64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_OUT_HS_WMAXPACKETSIZE       512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_OUT_HS_BINTERVAL            0

//           </h>
//         </h>
//       </e>

//       <e>Bulk IN Endpoint
//       <i>Select if Bulk IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_IN_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_IN                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_IN_FS_WMAXPACKETSIZE        64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_IN_HS_WMAXPACKETSIZE        512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_BULK_IN_HS_BINTERVAL             0

//           </h>
//         </h>
//       </e>

//       <e>Interrupt OUT Endpoint
//       <i>Select if Interrupt OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_OUT_FS_WMAXPACKETSIZE        4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_OUT_FS_BINTERVAL             16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_OUT_HS_WMAXPACKETSIZE        4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_OUT_HS_BINTERVAL             5

//           </h>
//         </h>
//       </e>

//       <e>Interrupt IN Endpoint
//       <i>Select if Interrupt IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_IN_FS_WMAXPACKETSIZE         4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_IN_FS_BINTERVAL              16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_IN_HS_WMAXPACKETSIZE         4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_INT_IN_HS_BINTERVAL              5

//           </h>
//         </h>
//       </e>

//       <e>Isochronous OUT Endpoint
//       <i>Select if Isochronous OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_OUT_FS_WMAXPACKETSIZE        64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_OUT_FS_BINTERVAL             1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_OUT_HS_WMAXPACKETSIZE        64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_OUT_HS_BINTERVAL             1

//           </h>
//         </h>
//       </e>

//       <e>Isochronous IN Endpoint
//       <i>Select if Isochronous IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_IN_FS_WMAXPACKETSIZE         64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_IN_FS_BINTERVAL              1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_IN_HS_WMAXPACKETSIZE         64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF1_EP_ISO_IN_HS_BINTERVAL              1

//           </h>
//         </h>
//       </e>
//     </h>

//     <h>String Settings
//     <i>Following settings are used to create String Descriptor(s)

//       <s.126>Interface String
#define USBD_CUSTOM_CLASS%Instance%_IF1_STR                                 L"USB_CUSTOM_CLASS%Instance%_IF1"

//     </h>
//   </e>


//   <e>Interface
#define USBD_CUSTOM_CLASS%Instance%_IF2_EN                                  0

//     <h>Interface Settings
//     <i>The Interface Settings are used to create the Interface Descriptor.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about the Interface Descriptor.

//       <o>Interface Number <0-255>
//       <i>Defines the value for bInterfaceNumber
//       <i>Each USB Device Interface has a sequential Interface Number starting with 0.
//       <i>Several Interfaces may have the same Interface Number; in this case the value
//       <i>of Alternate Setting is used to differ between the Interfaces. For a
//       <i>composite device the Interface Numbers of the custom classes must be contiguous.
#define USBD_CUSTOM_CLASS%Instance%_IF2_NUM                                 2

//       <o>Alternate Setting <0=>0 <1=>1 <2=>2 <3=>3
//       <i>Defines the value for bAlternateSetting
//       <i>A sequential number starting with 0 to indentify the Interface Descriptors
//       <i>that share the same value for Interface Number.
#define USBD_CUSTOM_CLASS%Instance%_IF2_ALT                                 0

//       <o.0..7>Class Code
//         <0x00=>0x00: Indicate a Null Class Code triple
//         <0x01=>0x01: Audio
//         <0x02=>0x02: Communications and CDC Control
//         <0x03=>0x03: HID (Human Interface Device)
//         <0x05=>0x05: Physical
//         <0x06=>0x06: Image
//         <0x07=>0x07: Printer
//         <0x08=>0x08: Mass Storage
//         <0x0A=>0x0A: CDC-Data
//         <0x0B=>0x0B: Smart Card
//         <0x0D=>0x0D: Content Security
//         <0x0E=>0x0E: Video
//         <0x0F=>0x0F: Personal Healthcare
//         <0x10=>0x10: Audio/Video Devices
//         <0xDC=>0xDC: Diagnostic Device
//         <0xE0=>0xE0: Wireless Controller
//         <0xEF=>0xEF: Miscellaneous
//         <0xFE=>0xFE: Application Specific
//         <0xFF=>0xFF: Vendor Specific
#define USBD_CUSTOM_CLASS%Instance%_IF2_CLASS                               0xFF

//       <o.0..7>Subclass Code <0x00-0xFF>
//       <i>The possible values depend on the Class Code:
//       <i>Class Code 0x00: Subclass Code must be 0
//       <i>Class Code 0x01 .. 0xFE: Subclass Code is defined by USB-IF
//       <i>Class Code 0xFF: Subclass Code can be 0x00 .. 0xFF
#define USBD_CUSTOM_CLASS%Instance%_IF2_SUBCLASS                            0x00

//       <o.0..7>Protocol Code <0x00-0xFF>
//       <i>The Protocol Code value defines the protocol used on this interface:
//       <i>Protocol Code 0x00: class-specific protocol not used
//       <i>Protocol Code 0x01 .. 0xFE: class-specific protocol used
//       <i>Protocol Code 0xFF: vendor-specific protocol used
#define USBD_CUSTOM_CLASS%Instance%_IF2_PROTOCOL                            0x00

//     </h>

//     <h>Endpoint Settings
//     <i>Following settings are used to create the Endpoint Descriptors.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about Endpoint Descriptors.

//       <e>Bulk OUT Endpoint
//       <i>Select if Bulk OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_OUT_EN                      0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_OUT                         1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_OUT_FS_WMAXPACKETSIZE       64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_OUT_HS_WMAXPACKETSIZE       512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_OUT_HS_BINTERVAL            0

//           </h>
//         </h>
//       </e>

//       <e>Bulk IN Endpoint
//       <i>Select if Bulk IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_IN_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_IN                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_IN_FS_WMAXPACKETSIZE        64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_IN_HS_WMAXPACKETSIZE        512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_BULK_IN_HS_BINTERVAL             0

//           </h>
//         </h>
//       </e>

//       <e>Interrupt OUT Endpoint
//       <i>Select if Interrupt OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_OUT_FS_WMAXPACKETSIZE        4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_OUT_FS_BINTERVAL             16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_OUT_HS_WMAXPACKETSIZE        4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_OUT_HS_BINTERVAL             5

//           </h>
//         </h>
//       </e>

//       <e>Interrupt IN Endpoint
//       <i>Select if Interrupt IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_IN_FS_WMAXPACKETSIZE         4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_IN_FS_BINTERVAL              16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_IN_HS_WMAXPACKETSIZE         4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_INT_IN_HS_BINTERVAL              5

//           </h>
//         </h>
//       </e>

//       <e>Isochronous OUT Endpoint
//       <i>Select if Isochronous OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_OUT_FS_WMAXPACKETSIZE        64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_OUT_FS_BINTERVAL             1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_OUT_HS_WMAXPACKETSIZE        64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_OUT_HS_BINTERVAL             1

//           </h>
//         </h>
//       </e>

//       <e>Isochronous IN Endpoint
//       <i>Select if Isochronous IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_IN_FS_WMAXPACKETSIZE         64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_IN_FS_BINTERVAL              1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_IN_HS_WMAXPACKETSIZE         64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF2_EP_ISO_IN_HS_BINTERVAL              1

//           </h>
//         </h>
//       </e>
//     </h>

//     <h>String Settings
//     <i>Following settings are used to create String Descriptor(s)

//       <s.126>Interface String
#define USBD_CUSTOM_CLASS%Instance%_IF2_STR                                 L"USB_CUSTOM_CLASS%Instance%_IF2"

//     </h>
//   </e>


//   <e>Interface
#define USBD_CUSTOM_CLASS%Instance%_IF3_EN                                  0

//     <h>Interface Settings
//     <i>The Interface Settings are used to create the Interface Descriptor.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about the Interface Descriptor.

//       <o>Interface Number <0-255>
//       <i>Defines the value for bInterfaceNumber
//       <i>Each USB Device Interface has a sequential Interface Number starting with 0.
//       <i>Several Interfaces may have the same Interface Number; in this case the value
//       <i>of Alternate Setting is used to differ between the Interfaces. For a
//       <i>composite device the Interface Numbers of the custom classes must be contiguous.
#define USBD_CUSTOM_CLASS%Instance%_IF3_NUM                                 3

//       <o>Alternate Setting <0=>0 <1=>1 <2=>2 <3=>3
//       <i>Defines the value for bAlternateSetting
//       <i>A sequential number starting with 0 to indentify the Interface Descriptors
//       <i>that share the same value for Interface Number.
#define USBD_CUSTOM_CLASS%Instance%_IF3_ALT                                 0

//       <o.0..7>Class Code
//         <i>Class Codes are defined by USB-IF. For more information refer to
//         <i>http://www.usb.org/developers/defined_class.
//         <0x00=>0x00: Indicate a Null Class Code triple
//         <0x01=>0x01: Audio
//         <0x02=>0x02: Communications and CDC Control
//         <0x03=>0x03: HID (Human Interface Device)
//         <0x05=>0x05: Physical
//         <0x06=>0x06: Image
//         <0x07=>0x07: Printer
//         <0x08=>0x08: Mass Storage
//         <0x0A=>0x0A: CDC-Data
//         <0x0B=>0x0B: Smart Card
//         <0x0D=>0x0D: Content Security
//         <0x0E=>0x0E: Video
//         <0x0F=>0x0F: Personal Healthcare
//         <0x10=>0x10: Audio/Video Devices
//         <0xDC=>0xDC: Diagnostic Device
//         <0xE0=>0xE0: Wireless Controller
//         <0xEF=>0xEF: Miscellaneous
//         <0xFE=>0xFE: Application Specific
//         <0xFF=>0xFF: Vendor Specific
#define USBD_CUSTOM_CLASS%Instance%_IF3_CLASS                               0xFF

//       <o.0..7>Subclass Code <0x00-0xFF>
//       <i>The possible values depend on the Class Code:
//       <i>Class Code 0x00: Subclass Code must be 0
//       <i>Class Code 0x01 .. 0xFE: Subclass Code is defined by USB-IF
//       <i>Class Code 0xFF: Subclass Code can be 0x00 .. 0xFF
#define USBD_CUSTOM_CLASS%Instance%_IF3_SUBCLASS                            0x00

//       <o.0..7>Protocol Code <0x00-0xFF>
//       <i>The Protocol Code value defines the protocol used on this interface:
//       <i>Protocol Code 0x00: class-specific protocol not used
//       <i>Protocol Code 0x01 .. 0xFE: class-specific protocol used
//       <i>Protocol Code 0xFF: vendor-specific protocol used
#define USBD_CUSTOM_CLASS%Instance%_IF3_PROTOCOL                            0x00

//     </h>

//     <h>Endpoint Settings
//     <i>Following settings are used to create the Endpoint Descriptors.
//     <i>Refer to USB - USB Concepts - USB Descriptor in the MDK Components
//     <i>User's Guide for more information about Endpoint Descriptors.

//       <e>Bulk OUT Endpoint
//       <i>Select if Bulk OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_OUT_EN                      0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_OUT                         1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_OUT_FS_WMAXPACKETSIZE       64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_OUT_HS_WMAXPACKETSIZE       512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_OUT_HS_BINTERVAL            0

//           </h>
//         </h>
//       </e>

//       <e>Bulk IN Endpoint
//       <i>Select if Bulk IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_IN_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_IN                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <8=>8 <16=>16 <32=>32 <64=>64
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_IN_FS_WMAXPACKETSIZE        64

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <512=>512
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Only available value is 512.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_IN_HS_WMAXPACKETSIZE        512

//              <o.0..7>Maximum NAK Rate (in 125 us intervals) <0-255>
//              <i>Specifies the frequency in which Bulk Endpoint can NAK.
//              <i>Value of 0 indicates that Bulk Endpoint never NAKs.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_BULK_IN_HS_BINTERVAL             0

//           </h>
//         </h>
//       </e>

//       <e>Interrupt OUT Endpoint
//       <i>Select if Interrupt OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_OUT_FS_WMAXPACKETSIZE        4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_OUT_FS_BINTERVAL             16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_OUT_HS_WMAXPACKETSIZE        4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_OUT_HS_BINTERVAL             5

//           </h>
//         </h>
//       </e>

//       <e>Interrupt IN Endpoint
//       <i>Select if Interrupt IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..6>Maximum Endpoint Packet Size (in bytes) <0-64>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 64.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_IN_FS_WMAXPACKETSIZE         4

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_IN_FS_BINTERVAL              16

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per microframe
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_IN_HS_WMAXPACKETSIZE         4

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_INT_IN_HS_BINTERVAL              5

//           </h>
//         </h>
//       </e>

//       <e>Isochronous OUT Endpoint
//       <i>Select if Isochronous OUT Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_OUT_EN                       0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_OUT                          1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_OUT_FS_WMAXPACKETSIZE        64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_OUT_FS_BINTERVAL             1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_OUT_HS_WMAXPACKETSIZE        64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_OUT_HS_BINTERVAL             1

//           </h>
//         </h>
//       </e>

//       <e>Isochronous IN Endpoint
//       <i>Select if Isochronous IN Endpoint exists in this interface.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_IN_EN                        0

//         <o.0..3>Endpoint Number
//                   <1=>1   <2=>2   <3=>3   <4=>4   <5=>5   <6=>6   <7=>7
//           <8=>8   <9=>9   <10=>10 <11=>11 <12=>12 <13=>13 <14=>14 <15=>15
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_IN                           1

//         <h>Endpoint Settings
//
//           <h>Full/Low-speed
//           <i>Parameters apply when High-speed is disabled in corresponding USBD_Config_n.c
//           <i>(n is the index of device on which this interface will be used)
//
//             <o.0..9>Maximum Endpoint Packet Size (in bytes) <0-1023>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1023.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_IN_FS_WMAXPACKETSIZE         64

//             <o.0..7>Endpoint polling Interval (in ms) <1-255>
//             <i>Specifies the frequency of requests initiated by USB Host.
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_IN_FS_BINTERVAL              1

//           </h>

//           <h>High-speed
//           <i>Parameters apply when High-speed is enabled
//
//             <o.0..10>Maximum Endpoint Packet Size (in bytes) <0-1024>
//             <i>Specifies the physical packet size used for information exchange.
//             <i>Maximum value is 1024.
//             <o.11..12>Additional transactions per micro-frame
//             <i>Additional transactions improve communication performance.
//               <0=>None <1=>1 additional <2=>2 additional
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_IN_HS_WMAXPACKETSIZE         64

//             <o.0..4>Endpoint polling Interval (in 125 us intervals)
//             <i>Specifies the frequency of requests initiated by USB Host.
//               <1=>    1 <2=>    2 <3=>     4 <4=>     8
//               <5=>   16 <6=>   32 <7=>    64 <8=>   128
//               <9=>  256 <10=> 512 <11=> 1024 <12=> 2048
//               <13=>4096 <14=>8192 <15=>16384 <16=>32768
#define USBD_CUSTOM_CLASS%Instance%_IF3_EP_ISO_IN_HS_BINTERVAL              1

//           </h>
//         </h>
//       </e>
//     </h>

//     <h>String Settings
//     <i>Following settings are used to create String Descriptor(s)

//       <s.126>Interface String
#define USBD_CUSTOM_CLASS%Instance%_IF3_STR                                 L"USB_CUSTOM_CLASS%Instance%_IF3"

//     </h>
//   </e>


//   <h>OS Resources Settings
//   <i>These settings are used to optimize usage of OS resources.
//     <o>Endpoint 1 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 1 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP1_THREAD_STACK_SIZE                   512

//        Endpoint 1 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP1_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 2 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 2 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP2_THREAD_STACK_SIZE                   512

//        Endpoint 2 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP2_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 3 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 3 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP3_THREAD_STACK_SIZE                   512

//        Endpoint 3 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP3_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 4 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 4 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP4_THREAD_STACK_SIZE                   512

//        Endpoint 4 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP4_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 5 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 5 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP5_THREAD_STACK_SIZE                   512

//        Endpoint 5 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP5_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 6 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 6 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP6_THREAD_STACK_SIZE                   512

//        Endpoint 6 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP6_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 7 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 7 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP7_THREAD_STACK_SIZE                   512

//        Endpoint 7 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP7_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 8 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 8 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP8_THREAD_STACK_SIZE                   512

//        Endpoint 8 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP8_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 9 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 9 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP9_THREAD_STACK_SIZE                   512

//        Endpoint 9 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP9_THREAD_PRIORITY                     osPriorityAboveNormal

//     <o>Endpoint 10 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 10 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP10_THREAD_STACK_SIZE                  512

//        Endpoint 10 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP10_THREAD_PRIORITY                    osPriorityAboveNormal

//     <o>Endpoint 11 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 11 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP11_THREAD_STACK_SIZE                  512

//        Endpoint 11 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP11_THREAD_PRIORITY                    osPriorityAboveNormal

//     <o>Endpoint 12 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 12 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP12_THREAD_STACK_SIZE                  512

//        Endpoint 12 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP12_THREAD_PRIORITY                    osPriorityAboveNormal

//     <o>Endpoint 13 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 13 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP13_THREAD_STACK_SIZE                  512

//        Endpoint 13 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP13_THREAD_PRIORITY                    osPriorityAboveNormal

//     <o>Endpoint 14 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 14 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP14_THREAD_STACK_SIZE                  512

//        Endpoint 14 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP14_THREAD_PRIORITY                    osPriorityAboveNormal

//     <o>Endpoint 15 Thread Stack Size <64-65536>
//     <i>This setting is used if Endpoint 15 is enabled.
#define USBD_CUSTOM_CLASS%Instance%_EP15_THREAD_STACK_SIZE                  512

//        Endpoint 15 Thread Priority
#define USBD_CUSTOM_CLASS%Instance%_EP15_THREAD_PRIORITY                    osPriorityAboveNormal

//   </h>
// </h>
