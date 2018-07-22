/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config_desc_hid_1.c
 * Purpose: USB Device HID 1 Descriptor Creation
 * Rev.:    V6.3
 *----------------------------------------------------------------------------*/

/* USB Device HID 1 Report Descriptor */
#if (USBD_HID1_USER_REPORT_DESCRIPTOR == 0)
  const uint8_t usbd_hid1_report_descriptor[] = {
    HID_UsagePageVendor( 0x00                         ),
    HID_Usage          ( 0x01                         ),
    HID_Collection     ( HID_Application              ),
      HID_LogicalMin   ( 0                            ), /* value range: 0 - 0xFF */
      HID_LogicalMaxS  ( 0xFF                         ),
      HID_ReportSize   ( 8                            ), /* 8 bits */
  #if (USBD_HID1_IN_REPORT_MAX_SZ > 255)
      HID_ReportCountS ( USBD_HID1_IN_REPORT_MAX_SZ   ),
  #else
      HID_ReportCount  ( USBD_HID1_IN_REPORT_MAX_SZ   ),
  #endif
      HID_Usage        ( 0x01                         ),
      HID_Input        ( HID_Data | HID_Variable | HID_Absolute ),
  #if (USBD_HID1_OUT_REPORT_MAX_SZ > 255)
      HID_ReportCountS ( USBD_HID1_OUT_REPORT_MAX_SZ  ),
  #else
      HID_ReportCount  ( USBD_HID1_OUT_REPORT_MAX_SZ  ),
  #endif
      HID_Usage        ( 0x01                         ),
      HID_Output       ( HID_Data | HID_Variable | HID_Absolute ),
  #if (USBD_HID1_FEAT_REPORT_MAX_SZ > 255)
      HID_ReportCountS ( USBD_HID1_FEAT_REPORT_MAX_SZ ),
  #else
      HID_ReportCount  ( USBD_HID1_FEAT_REPORT_MAX_SZ ),
  #endif
      HID_Usage        ( 0x01                         ),
      HID_Feature      ( HID_Data | HID_Variable | HID_Absolute ),
    HID_EndCollection,
  };

  #define USBD_HID1_REPORT_DESC_SIZE    (sizeof(usbd_hid1_report_descriptor))
#else
  extern const uint8_t usbd_hid1_report_descriptor[];

  #define USBD_HID1_REPORT_DESC_SIZE    (USBD_HID1_USER_REPORT_DESCRIPTOR_SIZE)
#endif

usbd_hid_desc_t usbd_hid1_desc = {      (uint8_t *)usbd_hid1_report_descriptor, USBD_HID1_REPORT_DESC_SIZE, USBD_HID1_DESC_OFS };
