/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbd_config_desc_2.c
 * Purpose: USB Device 2 Descriptor Creation
 * Rev.:    V6.6.0
 *----------------------------------------------------------------------------*/

/* USB Device 2 Endpoint 0 Descriptor */
__weak \
const uint8_t usbd2_ep0_descriptor[] = { USBD_EP0(2) };

/* USB Device 2 Standard Descriptor */
__weak \
const uint8_t usbd2_device_descriptor[] = {
  USB_DEVICE_DESC_SIZE,                 /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,           /* bDescriptorType */
  WBVAL(USBD2_BDC_USB),                 /* bcdUSB */
#if (USBD2_USE_IAD)
  USB_DEVICE_CLASS_MISCELLANEOUS,       /* bDeviceClass */
  0x02,                                 /* bDeviceSubClass */
  0x01,                                 /* bDeviceProtocol */
#else
  0x00,                                 /* bDeviceClass */
  0x00,                                 /* bDeviceSubClass */
  0x00,                                 /* bDeviceProtocol */
#endif
  USBD2_MAX_PACKET0,                    /* bMaxPacketSize0 */
  WBVAL(USBD2_DEV_DESC_IDVENDOR),       /* idVendor */
  WBVAL(USBD2_DEV_DESC_IDPRODUCT),      /* idProduct */
  WBVAL(USBD2_DEV_DESC_BCDDEVICE),      /* bcdDevice */
  0x01,                                 /* iManufacturer */
  0x02,                                 /* iProduct */
  0x03*USBD2_STR_DESC_SER_EN,           /* iSerialNumber */
  0x01                                  /* bNumConfigurations: one possible configuration */
};

/* USB Device 2 Configuration Descriptor (for Full Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak \
const uint8_t usbd2_config_descriptor_fs[] = {
  /* Configuration 1 */
  USB_CONFIGURATION_DESC_SIZE,          /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */
  WBVAL(USBD2_WTOTALLENGTH),            /* wTotalLength */
  USBD2_IF_CNT,                         /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD2_CFG_DESC_BMATTRIBUTES,          /* bmAttributes */
  USBD2_CFG_DESC_BMAXPOWER,             /* bMaxPower, device power consumption */

#if (USBD2_CUSTOM_CLASS0)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (0)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,0)
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,1)
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,2)
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,3)
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS1)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (1)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,0)
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,1)
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,2)
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,3)
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS2)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (2)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,0)
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,1)
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,2)
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,3)
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif


#if (USBD2_CUSTOM_CLASS3)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (3)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,0)
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,1)
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,2)
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,3)
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif

#if (USBD2_ADC0)
#if (USBD2_USE_IAD)
  USBD_ADCn_IAD                                   (0,USBD_ADC0_IF_CTRL_NUM,USBD_ADC0_IF_CNT)
#endif
  USBD_ADCn_IF_DESC_AC                            (0)
#if   (USBD_ADC0_IF_SPKR && USBD_ADC0_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER                     (0,USBD_ADC0_OUT_CH_NUM,USBD_ADC0_IN_CH_NUM)
#elif (USBD_ADC0_IF_SPKR)
  USBD_ADCn_IF_DESC_AC_HEADER_SPEAKER             (0,USBD_ADC0_OUT_CH_NUM)
#elif (USBD_ADC0_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER_MICROPHONE          (0,USBD_ADC0_IN_CH_NUM)
#endif
#if   (USBD_ADC0_IF_SPKR)
#if   (USBD_ADC0_OUT_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_SPEAKER      (0,1)
#elif (USBD_ADC0_OUT_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_SPEAKERS   (0,1)
#endif
#endif
#if   (USBD_ADC0_IF_MIC)
#if   (USBD_ADC0_IN_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_MICROPHONE   (0,1+USBD_ADC0_IF_SPKR*3)
#elif (USBD_ADC0_IN_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_MICROPHONES(0,1+USBD_ADC0_IF_SPKR*3)
#endif
#endif
#if   (USBD_ADC0_IF_SPKR)
  USBD_ADCn_IF_DESC_AS_SPEAKER                    (0)
  USBD_ADCn_IF_DESC_AS_IF_FT_SPEAKER              (0,1,USBD_ADC0_OUT_CH_NUM)
  USBD_ADCn_EP_DESC_SPEAKER                       (0)
#endif
#if   (USBD_ADC0_IF_MIC)
  USBD_ADCn_IF_DESC_AS_MICROPHONE                 (0)
  USBD_ADCn_IF_DESC_AS_IF_FT_MICROPHONE           (0,3+USBD_ADC0_IF_SPKR*3,USBD_ADC0_IN_CH_NUM)
  USBD_ADCn_EP_DESC_MICROPHONE                    (0)
#endif
#endif
#if (USBD2_ADC1)
#if (USBD2_USE_IAD)
  USBD_ADCn_IAD                                   (1,USBD_ADC1_IF_CTRL_NUM,USBD_ADC1_IF_CNT)
#endif
  USBD_ADCn_IF_DESC_AC                            (1)
#if   (USBD_ADC1_IF_SPKR && USBD_ADC1_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER                     (1,USBD_ADC1_OUT_CH_NUM,USBD_ADC1_IN_CH_NUM)
#elif (USBD_ADC1_IF_SPKR)
  USBD_ADCn_IF_DESC_AC_HEADER_SPEAKER             (1,USBD_ADC1_OUT_CH_NUM)
#elif (USBD_ADC1_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER_MICROPHONE          (1,USBD_ADC1_IN_CH_NUM)
#endif
#if   (USBD_ADC1_IF_SPKR)
#if   (USBD_ADC1_OUT_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_SPEAKER      (1,1)
#elif (USBD_ADC1_OUT_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_SPEAKERS   (1,1)
#endif
#endif
#if   (USBD_ADC1_IF_MIC)
#if   (USBD_ADC1_IN_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_MICROPHONE   (1,1+USBD_ADC1_IF_SPKR*3)
#elif (USBD_ADC1_IN_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_MICROPHONES(1,1+USBD_ADC1_IF_SPKR*3)
#endif
#endif
#if   (USBD_ADC1_IF_SPKR)
  USBD_ADCn_IF_DESC_AS_SPEAKER                    (1)
  USBD_ADCn_IF_DESC_AS_IF_FT_SPEAKER              (1,1,USBD_ADC1_OUT_CH_NUM)
  USBD_ADCn_EP_DESC_SPEAKERS                      (1)
#endif
#if   (USBD_ADC1_IF_MIC)
  USBD_ADCn_IF_DESC_AS_MICROPHONE                 (1)
  USBD_ADCn_IF_DESC_AS_IF_FT_MICROPHONE           (1,3+USBD_ADC1_IF_SPKR*3,USBD_ADC1_IN_CH_NUM)
  USBD_ADCn_EP_DESC_MICROPHONE                    (1)
#endif
#endif
#if (USBD2_ADC2)
#if (USBD2_USE_IAD)
  USBD_ADCn_IAD                                   (2,USBD_ADC2_IF_CTRL_NUM,USBD_ADC2_IF_CNT)
#endif
  USBD_ADCn_IF_DESC_AC                            (2)
#if   (USBD_ADC2_IF_SPKR && USBD_ADC2_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER                     (2,USBD_ADC2_OUT_CH_NUM,USBD_ADC2_IN_CH_NUM)
#elif (USBD_ADC2_IF_SPKR)
  USBD_ADCn_IF_DESC_AC_HEADER_SPEAKER             (2,USBD_ADC2_OUT_CH_NUM)
#elif (USBD_ADC2_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER_MICROPHONE          (2,USBD_ADC2_IN_CH_NUM)
#endif
#if   (USBD_ADC2_IF_SPKR)
#if   (USBD_ADC2_OUT_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_SPEAKER      (2,1)
#elif (USBD_ADC2_OUT_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_SPEAKERS   (2,1)
#endif
#endif
#if   (USBD_ADC2_IF_MIC)
#if   (USBD_ADC2_IN_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_MICROPHONE   (2,1+USBD_ADC2_IF_SPKR*3)
#elif (USBD_ADC2_IN_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_MICROPHONES(2,1+USBD_ADC2_IF_SPKR*3)
#endif
#endif
#if   (USBD_ADC2_IF_SPKR)
  USBD_ADCn_IF_DESC_AS_SPEAKERS                   (2)
  USBD_ADCn_IF_DESC_AS_IF_FT_SPEAKER              (2,1,USBD_ADC2_OUT_CH_NUM)
  USBD_ADCn_EP_DESC_SPEAKERS                      (2)
#endif
#if   (USBD_ADC2_IF_MIC)
  USBD_ADCn_IF_DESC_AS_MICROPHONE                 (2)
  USBD_ADCn_IF_DESC_AS_IF_FT_MICROPHONE           (2,3+USBD_ADC2_IF_SPKR*3,USBD_ADC2_IN_CH_NUM)
  USBD_ADCn_EP_DESC_MICROPHONE                    (2)
#endif
#endif
#if (USBD2_ADC3)
#if (USBD2_USE_IAD)
  USBD_ADCn_IAD                                   (3,USBD_ADC3_IF_CTRL_NUM,USBD_ADC3_IF_CNT)
#endif
  USBD_ADCn_IF_DESC_AC                            (3)
#if   (USBD_ADC3_IF_SPKR && USBD_ADC3_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER                     (3,USBD_ADC3_OUT_CH_NUM,USBD_ADC3_IN_CH_NUM)
#elif (USBD_ADC3_IF_SPKR)
  USBD_ADCn_IF_DESC_AC_HEADER_SPEAKER             (3,USBD_ADC3_OUT_CH_NUM)
#elif (USBD_ADC3_IF_MIC)
  USBD_ADCn_IF_DESC_AC_HEADER_MICROPHONE          (3,USBD_ADC3_IN_CH_NUM)
#endif
#if   (USBD_ADC3_IF_SPKR)
#if   (USBD_ADC3_OUT_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_SPEAKER      (3,1)
#elif (USBD_ADC3_OUT_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_SPEAKERS   (3,1)
#endif
#endif
#if   (USBD_ADC3_IF_MIC)
#if   (USBD_ADC3_IN_CH_NUM == 1)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_MONO_MICROPHONE   (3,1+USBD_ADC3_IF_SPKR*3)
#elif (USBD_ADC3_IN_CH_NUM == 2)
  USBD_ADCn_IF_DESC_AC_IT_FU_OT_STEREO_MICROPHONES(3,1+USBD_ADC3_IF_SPKR*3)
#endif
#endif
#if   (USBD_ADC3_IF_SPKR)
  USBD_ADCn_IF_DESC_AS_SPEAKERS                   (3)
  USBD_ADCn_IF_DESC_AS_IF_FT_SPEAKER              (3,1,USBD_ADC3_OUT_CH_NUM)
  USBD_ADCn_EP_DESC_SPEAKERS                      (3)
#endif
#if   (USBD_ADC3_IF_MIC)
  USBD_ADCn_IF_DESC_AS_MICROPHONE                 (3)
  USBD_ADCn_IF_DESC_AS_IF_FT_MICROPHONE           (3,3+USBD_ADC3_IF_SPKR*3,USBD_ADC3_IN_CH_NUM)
  USBD_ADCn_EP_DESC_MICROPHONE                    (3)
#endif
#endif

#if   (USBD2_CDC0)
#if   (USBD2_CDC0_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (0)
  USBD_CDCn_ACM_EP_IF0                            (0)
  USBD_CDCn_ACM_DESC_IF1                          (0)
  USBD_CDCn_ACM_EP_IF1                            (0)
#elif (USBD2_CDC0_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (0)
  USBD_CDCn_NCM_EP_IF0                            (0)
  USBD_CDCn_NCM_DESC_IF1                          (0)
  USBD_CDCn_NCM_EP_IF1                            (0)
#endif
#endif
#if   (USBD2_CDC1)
#if   (USBD2_CDC1_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (1)
  USBD_CDCn_ACM_EP_IF0                            (1)
  USBD_CDCn_ACM_DESC_IF1                          (1)
  USBD_CDCn_ACM_EP_IF1                            (1)
#elif (USBD2_CDC1_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (1)
  USBD_CDCn_NCM_EP_IF0                            (1)
  USBD_CDCn_NCM_DESC_IF1                          (1)
  USBD_CDCn_NCM_EP_IF1                            (1)
#endif
#endif
#if   (USBD2_CDC2)
#if   (USBD2_CDC2_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (2)
  USBD_CDCn_ACM_EP_IF0                            (2)
  USBD_CDCn_ACM_DESC_IF1                          (2)
  USBD_CDCn_ACM_EP_IF1                            (2)
#elif (USBD2_CDC2_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (2)
  USBD_CDCn_NCM_EP_IF0                            (2)
  USBD_CDCn_NCM_DESC_IF1                          (2)
  USBD_CDCn_NCM_EP_IF1                            (2)
#endif
#endif
#if   (USBD2_CDC3)
#if   (USBD2_CDC3_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (3)
  USBD_CDCn_ACM_EP_IF0                            (3)
  USBD_CDCn_ACM_DESC_IF1                          (3)
  USBD_CDCn_ACM_EP_IF1                            (3)
#elif (USBD2_CDC3_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (3)
  USBD_CDCn_NCM_EP_IF0                            (3)
  USBD_CDCn_NCM_DESC_IF1                          (3)
  USBD_CDCn_NCM_EP_IF1                            (3)
#endif
#endif

#if (USBD2_HID0)
  USBD_HIDn_DESC                                  (0)
#if (USBD_HID0_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (0)
#else
  USBD_HIDn_EP                                    (0)
#endif
#endif
#if (USBD2_HID1)
  USBD_HIDn_DESC                                  (1)
#if (USBD_HID1_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (1)
#else
  USBD_HIDn_EP                                    (1)
#endif
#endif
#if (USBD2_HID2)
  USBD_HIDn_DESC                                  (2)
#if (USBD_HID2_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (2)
#else
  USBD_HIDn_EP                                    (2)
#endif
#endif
#if (USBD2_HID3)
  USBD_HIDn_DESC                                  (3)
#if (USBD_HID3_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (3)
#else
  USBD_HIDn_EP                                    (3)
#endif
#endif

#if (USBD2_MSC0)
  USBD_MSCn_DESC                                  (0)
  USBD_MSCn_EP                                    (0)
#endif
#if (USBD2_MSC1)
  USBD_MSCn_DESC                                  (1)
  USBD_MSCn_EP                                    (1)
#endif
#if (USBD2_MSC2)
  USBD_MSCn_DESC                                  (2)
  USBD_MSCn_EP                                    (2)
#endif
#if (USBD2_MSC3)
  USBD_MSCn_DESC                                  (3)
  USBD_MSCn_EP                                    (3)
#endif

/* Terminator */
  0                                     /* bLength */
};

#if (!USBD2_HS)                         /* If High-speed not enabled, declare dummy descriptors for High-speed */
__weak \
const uint8_t usbd2_device_qualifier_fs[]              = { 0 };
__weak \
const uint8_t usbd2_device_qualifier_hs[]              = { 0 };
__weak \
const uint8_t usbd2_config_descriptor_hs[]             = { 0 };
__weak \
const uint8_t usbd2_other_speed_config_descriptor_fs[] = { 0 };
__weak \
const uint8_t usbd2_other_speed_config_descriptor_hs[] = { 0 };

#else

#if (USBD2_ADC0 || USBD2_ADC1 || USBD2_ADC2 || USBD2_ADC3)
#error High-speed is not supported for Audio Device!
#endif

/* USB Device 2 Qualifier Descriptor (in Full Speed for High Speed) */
__weak \
const uint8_t usbd2_device_qualifier_fs[] = {
  USB_DEVICE_QUALI_SIZE,                /* bLength */
  USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(0x0200), /* 2.00 */             /* bcdUSB */
  0x00,                                 /* bDeviceClass */
  0x00,                                 /* bDeviceSubClass */
  0x00,                                 /* bDeviceProtocol */
  USBD2_MAX_PACKET0,                    /* bMaxPacketSize0 */
  0x01,                                 /* bNumConfigurations */
  0x00                                  /* bReserved */
};

/* USB Device 2 Qualifier Descriptor (in High Speed for Full Speed) */
__weak \
const uint8_t usbd2_device_qualifier_hs[] = {
  USB_DEVICE_QUALI_SIZE,                /* bLength */
  USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(0x0200), /* 2.00 */             /* bcdUSB */
  0x00,                                 /* bDeviceClass */
  0x00,                                 /* bDeviceSubClass */
  0x00,                                 /* bDeviceProtocol */
  USBD2_MAX_PACKET0,                    /* bMaxPacketSize0 */
  0x01,                                 /* bNumConfigurations */
  0x00                                  /* bReserved */
};

/* USB Device 2 Configuration Descriptor (for High Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak \
const uint8_t usbd2_config_descriptor_hs[] = {
  /* Configuration 1 */
  USB_CONFIGURATION_DESC_SIZE,          /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,    /* bDescriptorType */
  WBVAL(USBD2_WTOTALLENGTH),            /* wTotalLength */
  USBD2_IF_CNT,                         /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD2_CFG_DESC_BMATTRIBUTES,          /* bmAttributes */
  USBD2_CFG_DESC_BMAXPOWER,             /* bMaxPower, device power consumption */

#if (USBD2_CUSTOM_CLASS0)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (0)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,0)
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,1)
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,2)
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,3)
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS1)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (1)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,0)
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,1)
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,2)
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,3)
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS2)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (2)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,0)
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,1)
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,2)
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,3)
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif


#if (USBD2_CUSTOM_CLASS3)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (3)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,0)
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,1)
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,2)
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,3)
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif

#if   (USBD2_CDC0)
#if   (USBD2_CDC0_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (0)
  USBD_CDCn_ACM_EP_IF0_HS                         (0)
  USBD_CDCn_ACM_DESC_IF1                          (0)
  USBD_CDCn_ACM_EP_IF1_HS                         (0)
#elif (USBD2_CDC0_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (0)
  USBD_CDCn_NCM_EP_IF0_HS                         (0)
  USBD_CDCn_NCM_DESC_IF1                          (0)
  USBD_CDCn_NCM_EP_IF1_HS                         (0)
#endif
#endif
#if   (USBD2_CDC1)
#if   (USBD2_CDC1_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (1)
  USBD_CDCn_ACM_EP_IF0_HS                         (1)
  USBD_CDCn_ACM_DESC_IF1                          (1)
  USBD_CDCn_ACM_EP_IF1_HS                         (1)
#elif (USBD2_CDC1_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (1)
  USBD_CDCn_NCM_EP_IF0_HS                         (1)
  USBD_CDCn_NCM_DESC_IF1                          (1)
  USBD_CDCn_NCM_EP_IF1_HS                         (1)
#endif
#endif
#if   (USBD2_CDC2)
#if   (USBD2_CDC2_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (2)
  USBD_CDCn_ACM_EP_IF0_HS                         (2)
  USBD_CDCn_ACM_DESC_IF1                          (2)
  USBD_CDCn_ACM_EP_IF1_HS                         (2)
#elif (USBD2_CDC2_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (2)
  USBD_CDCn_NCM_EP_IF0_HS                         (2)
  USBD_CDCn_NCM_DESC_IF1                          (2)
  USBD_CDCn_NCM_EP_IF1_HS                         (2)
#endif
#endif
#if   (USBD2_CDC3)
#if   (USBD2_CDC3_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (3)
  USBD_CDCn_ACM_EP_IF0_HS                         (3)
  USBD_CDCn_ACM_DESC_IF1                          (3)
  USBD_CDCn_ACM_EP_IF1_HS                         (3)
#elif (USBD2_CDC3_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (3)
  USBD_CDCn_NCM_EP_IF0_HS                         (3)
  USBD_CDCn_NCM_DESC_IF1                          (3)
  USBD_CDCn_NCM_EP_IF1_HS                         (3)
#endif
#endif

#if (USBD2_HID0)
  USBD_HIDn_DESC                                  (0)
#if (USBD_HID0_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (0)
#else
  USBD_HIDn_EP_HS                                 (0)
#endif
#endif
#if (USBD2_HID1)
  USBD_HIDn_DESC                                  (1)
#if (USBD_HID1_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (1)
#else
  USBD_HIDn_EP_HS                                 (1)
#endif
#endif
#if (USBD2_HID2)
  USBD_HIDn_DESC                                  (2)
#if (USBD_HID2_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (2)
#else
  USBD_HIDn_EP_HS                                 (2)
#endif
#endif
#if (USBD2_HID3)
  USBD_HIDn_DESC                                  (3)
#if (USBD_HID3_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (3)
#else
  USBD_HIDn_EP_HS                                 (3)
#endif
#endif

#if (USBD2_MSC0)
  USBD_MSCn_DESC                                  (0)
  USBD_MSCn_EP_HS                                 (0)
#endif
#if (USBD2_MSC1)
  USBD_MSCn_DESC                                  (1)
  USBD_MSCn_EP_HS                                 (1)
#endif
#if (USBD2_MSC2)
  USBD_MSCn_DESC                                  (2)
  USBD_MSCn_EP_HS                                 (2)
#endif
#if (USBD2_MSC3)
  USBD_MSCn_DESC                                  (3)
  USBD_MSCn_EP_HS                                 (3)
#endif

/* Terminator */
  0                                     /* bLength */
};

/* USB Device 2 Other Speed Configuration Descriptor (in Full Speed for High Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak \
const uint8_t usbd2_other_speed_config_descriptor_fs[] = {
  /* Configuration 1 */
  USB_CONFIGURATION_DESC_SIZE,          /* bLength */
  USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(USBD2_WTOTALLENGTH),            /* wTotalLength */
  USBD2_IF_CNT,                         /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD2_CFG_DESC_BMATTRIBUTES,          /* bmAttributes */
  USBD2_CFG_DESC_BMAXPOWER,             /* bMaxPower, device power consumption */

#if (USBD2_CUSTOM_CLASS0)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (0)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,0)
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,1)
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,2)
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,3)
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS1)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (1)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,0)
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,1)
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,2)
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,3)
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS2)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (2)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,0)
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,1)
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,2)
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,3)
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif


#if (USBD2_CUSTOM_CLASS3)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (3)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,0)
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,1)
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,2)
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,3)
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,BULK,BULK,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,BULK,BULK,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,IN,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,OUT,HS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,IN,HS)
#endif
#endif
#endif

#if   (USBD2_CDC0)
#if   (USBD2_CDC0_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (0)
  USBD_CDCn_ACM_EP_IF0_HS                         (0)
  USBD_CDCn_ACM_DESC_IF1                          (0)
  USBD_CDCn_ACM_EP_IF1_HS                         (0)
#elif (USBD2_CDC0_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (0)
  USBD_CDCn_NCM_EP_IF0_HS                         (0)
  USBD_CDCn_NCM_DESC_IF1                          (0)
  USBD_CDCn_NCM_EP_IF1_HS                         (0)
#endif
#endif
#if   (USBD2_CDC1)
#if   (USBD2_CDC1_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (1)
  USBD_CDCn_ACM_EP_IF0_HS                         (1)
  USBD_CDCn_ACM_DESC_IF1                          (1)
  USBD_CDCn_ACM_EP_IF1_HS                         (1)
#elif (USBD2_CDC1_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (1)
  USBD_CDCn_NCM_EP_IF0_HS                         (1)
  USBD_CDCn_NCM_DESC_IF1                          (1)
  USBD_CDCn_NCM_EP_IF1_HS                         (1)
#endif
#endif
#if   (USBD2_CDC2)
#if   (USBD2_CDC2_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (2)
  USBD_CDCn_ACM_EP_IF0_HS                         (2)
  USBD_CDCn_ACM_DESC_IF1                          (2)
  USBD_CDCn_ACM_EP_IF1_HS                         (2)
#elif (USBD2_CDC2_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (2)
  USBD_CDCn_NCM_EP_IF0_HS                         (2)
  USBD_CDCn_NCM_DESC_IF1                          (2)
  USBD_CDCn_NCM_EP_IF1_HS                         (2)
#endif
#endif
#if   (USBD2_CDC3)
#if   (USBD2_CDC3_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (3)
  USBD_CDCn_ACM_EP_IF0_HS                         (3)
  USBD_CDCn_ACM_DESC_IF1                          (3)
  USBD_CDCn_ACM_EP_IF1_HS                         (3)
#elif (USBD2_CDC3_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (3)
  USBD_CDCn_NCM_EP_IF0_HS                         (3)
  USBD_CDCn_NCM_DESC_IF1                          (3)
  USBD_CDCn_NCM_EP_IF1_HS                         (3)
#endif
#endif

#if (USBD2_HID0)
  USBD_HIDn_DESC                                  (0)
#if (USBD_HID0_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (0)
#else
  USBD_HIDn_EP_HS                                 (0)
#endif
#endif
#if (USBD2_HID1)
  USBD_HIDn_DESC                                  (1)
#if (USBD_HID1_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (1)
#else
  USBD_HIDn_EP_HS                                 (1)
#endif
#endif
#if (USBD2_HID2)
  USBD_HIDn_DESC                                  (2)
#if (USBD_HID2_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (2)
#else
  USBD_HIDn_EP_HS                                 (2)
#endif
#endif
#if (USBD2_HID3)
  USBD_HIDn_DESC                                  (3)
#if (USBD_HID3_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT_HS                           (3)
#else
  USBD_HIDn_EP_HS                                 (3)
#endif
#endif

#if (USBD2_MSC0)
  USBD_MSCn_DESC                                  (0)
  USBD_MSCn_EP_HS                                 (0)
#endif
#if (USBD2_MSC1)
  USBD_MSCn_DESC                                  (1)
  USBD_MSCn_EP_HS                                 (1)
#endif
#if (USBD2_MSC2)
  USBD_MSCn_DESC                                  (2)
  USBD_MSCn_EP_HS                                 (2)
#endif
#if (USBD2_MSC3)
  USBD_MSCn_DESC                                  (3)
  USBD_MSCn_EP_HS                                 (3)
#endif

/* Terminator */
  0                                     /* bLength */
};

/* USB Device 2 Other Speed Configuration Descriptor (in High Speed for Full Speed) */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
__weak \
const uint8_t usbd2_other_speed_config_descriptor_hs[] = {
/* Configuration 1 */
  USB_CONFIGURATION_DESC_SIZE,          /* bLength */
  USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(USBD2_WTOTALLENGTH),            /* wTotalLength */
  USBD2_IF_CNT,                         /* bNumInterfaces */
  0x01,                                 /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                                 /* iConfiguration: no string to describe this configuration */
  USBD2_CFG_DESC_BMATTRIBUTES,          /* bmAttributes */
  USBD2_CFG_DESC_BMAXPOWER,             /* bMaxPower, device power consumption */

#if (USBD2_CUSTOM_CLASS0)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (0)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,0)
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,1)
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,2)
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (0,3)
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (0,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (0,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS1)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (1)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,0)
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,1)
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,2)
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (1,3)
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (1,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (1,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif

#if (USBD2_CUSTOM_CLASS2)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (2)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,0)
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,1)
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,2)
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (2,3)
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (2,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (2,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif


#if (USBD2_CUSTOM_CLASS3)
#if (USBD2_USE_IAD)
  USBD_CUSTOM_CLASSn_IAD                          (3)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,0)
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,0,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,0,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF0_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,0,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,1)
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,1,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,1,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,1,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,2)
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,2,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,2,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,2,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EN)
  USBD_CUSTOM_CLASSn_IFx_DESC                     (3,3)
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,3,BULK,BULK,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_BULK_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP                       (3,3,BULK,BULK,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_INT_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,INT,INTERRUPT,IN,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_OUT_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,OUT,FS)
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EP_ISO_IN_EN)
  USBD_CUSTOM_CLASSn_IFx_EP_w_BINTERVAL           (3,3,ISO,ISOCHRONOUS,IN,FS)
#endif
#endif
#endif

#if   (USBD2_CDC0)
#if   (USBD2_CDC0_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (0)
  USBD_CDCn_ACM_EP_IF0                            (0)
  USBD_CDCn_ACM_DESC_IF1                          (0)
  USBD_CDCn_ACM_EP_IF1                            (0)
#elif (USBD2_CDC0_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (0,USBD_CDC0_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (0)
  USBD_CDCn_NCM_EP_IF0                            (0)
  USBD_CDCn_NCM_DESC_IF1                          (0)
  USBD_CDCn_NCM_EP_IF1                            (0)
#endif
#endif
#if   (USBD2_CDC1)
#if   (USBD2_CDC1_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (1)
  USBD_CDCn_ACM_EP_IF0                            (1)
  USBD_CDCn_ACM_DESC_IF1                          (1)
  USBD_CDCn_ACM_EP_IF1                            (1)
#elif (USBD2_CDC1_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (1,USBD_CDC1_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (1)
  USBD_CDCn_NCM_EP_IF0                            (1)
  USBD_CDCn_NCM_DESC_IF1                          (1)
  USBD_CDCn_NCM_EP_IF1                            (1)
#endif
#endif
#if   (USBD2_CDC2)
#if   (USBD2_CDC2_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (2)
  USBD_CDCn_ACM_EP_IF0                            (2)
  USBD_CDCn_ACM_DESC_IF1                          (2)
  USBD_CDCn_ACM_EP_IF1                            (2)
#elif (USBD2_CDC2_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (2,USBD_CDC2_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (2)
  USBD_CDCn_NCM_EP_IF0                            (2)
  USBD_CDCn_NCM_DESC_IF1                          (2)
  USBD_CDCn_NCM_EP_IF1                            (2)
#endif
#endif
#if   (USBD2_CDC3)
#if   (USBD2_CDC3_ACM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_ACM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_ACM_DESC_IF0                          (3)
  USBD_CDCn_ACM_EP_IF0                            (3)
  USBD_CDCn_ACM_DESC_IF1                          (3)
  USBD_CDCn_ACM_EP_IF1                            (3)
#elif (USBD2_CDC3_NCM)
#if   (USBD2_USE_IAD)
  USBD_CDCn_NCM_IAD                               (3,USBD_CDC3_IF0_NUM,2)
#endif
  USBD_CDCn_NCM_DESC_IF0                          (3)
  USBD_CDCn_NCM_EP_IF0                            (3)
  USBD_CDCn_NCM_DESC_IF1                          (3)
  USBD_CDCn_NCM_EP_IF1                            (3)
#endif
#endif

#if (USBD2_HID0)
  USBD_HIDn_DESC                                  (0)
#if (USBD_HID0_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (0)
#else
  USBD_HIDn_EP                                    (0)
#endif
#endif
#if (USBD2_HID1)
  USBD_HIDn_DESC                                  (1)
#if (USBD_HID1_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (1)
#else
  USBD_HIDn_EP                                    (1)
#endif
#endif
#if (USBD2_HID2)
  USBD_HIDn_DESC                                  (2)
#if (USBD_HID2_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (2)
#else
  USBD_HIDn_EP                                    (2)
#endif
#endif
#if (USBD2_HID3)
  USBD_HIDn_DESC                                  (3)
#if (USBD_HID3_EP_INT_OUT != 0)
  USBD_HIDn_EP_INOUT                              (3)
#else
  USBD_HIDn_EP                                    (3)
#endif
#endif

#if (USBD2_MSC0)
  USBD_MSCn_DESC                                  (0)
  USBD_MSCn_EP                                    (0)
#endif
#if (USBD2_MSC1)
  USBD_MSCn_DESC                                  (1)
  USBD_MSCn_EP                                    (1)
#endif
#if (USBD2_MSC2)
  USBD_MSCn_DESC                                  (2)
  USBD_MSCn_EP                                    (2)
#endif
#if (USBD2_MSC3)
  USBD_MSCn_DESC                                  (3)
  USBD_MSCn_EP                                    (3)
#endif

/* Terminator */
  0                                     /* bLength */
};

#endif

__weak \
const struct {
  struct {
    uint8_t  len;
    uint8_t  type;
    uint16_t langid;
  } desc_langid;
  USBD_STR_DEF(USBD2_STR_DESC_MAN);
  USBD_STR_DEF(USBD2_STR_DESC_PROD);
#if  (USBD2_STR_DESC_SER_EN)
  USBD_STR_DEF(USBD2_STR_DESC_SER);
#endif

#if (USBD2_CUSTOM_CLASS0)
#if (USBD_CUSTOM_CLASS0_IF0_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS0_IF0_STR);
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS0_IF1_STR);
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS0_IF2_STR);
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS0_IF3_STR);
#endif
#endif
#if (USBD2_CUSTOM_CLASS1)
#if (USBD_CUSTOM_CLASS1_IF0_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS1_IF0_STR);
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS1_IF1_STR);
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS1_IF2_STR);
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS1_IF3_STR);
#endif
#endif
#if (USBD2_CUSTOM_CLASS2)
#if (USBD_CUSTOM_CLASS2_IF0_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS2_IF0_STR);
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS2_IF1_STR);
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS2_IF2_STR);
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS2_IF3_STR);
#endif
#endif
#if (USBD2_CUSTOM_CLASS3)
#if (USBD_CUSTOM_CLASS3_IF0_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS3_IF0_STR);
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS3_IF1_STR);
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS3_IF2_STR);
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EN)
  USBD_STR_DEF(USBD_CUSTOM_CLASS3_IF3_STR);
#endif
#endif

#if (USBD2_ADC0)
  USBD_STR_DEF(USBD_ADC0_CIF_STR_DESC);
#if (USBD_ADC0_IF_SPKR)
  USBD_STR_DEF(USBD_ADC0_OUT_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC0_OUT_SIF_STR1_DESC);
#endif
#if (USBD_ADC0_IF_MIC)
  USBD_STR_DEF(USBD_ADC0_IN_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC0_IN_SIF_STR1_DESC);
#endif
#endif
#if (USBD2_ADC1)
  USBD_STR_DEF(USBD_ADC1_CIF_STR_DESC);
#if (USBD_ADC1_IF_SPKR)
  USBD_STR_DEF(USBD_ADC1_OUT_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC1_OUT_SIF_STR1_DESC);
#endif
#if (USBD_ADC1_IF_MIC)
  USBD_STR_DEF(USBD_ADC1_IN_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC1_IN_SIF_STR1_DESC);
#endif
#endif
#if (USBD2_ADC2)
  USBD_STR_DEF(USBD_ADC2_CIF_STR_DESC);
#if (USBD_ADC2_IF_SPKR)
  USBD_STR_DEF(USBD_ADC2_OUT_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC2_OUT_SIF_STR1_DESC);
#endif
#if (USBD_ADC2_IF_MIC)
  USBD_STR_DEF(USBD_ADC2_IN_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC2_IN_SIF_STR1_DESC);
#endif
#endif
#if (USBD2_ADC3)
  USBD_STR_DEF(USBD_ADC3_CIF_STR_DESC);
#if (USBD_ADC3_IF_SPKR)
  USBD_STR_DEF(USBD_ADC3_OUT_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC3_OUT_SIF_STR1_DESC);
#endif
#if (USBD_ADC3_IF_MIC)
  USBD_STR_DEF(USBD_ADC3_IN_SIF_STR0_DESC);
  USBD_STR_DEF(USBD_ADC3_IN_SIF_STR1_DESC);
#endif
#endif

#if (USBD2_CDC0)
  USBD_STR_DEF(USBD_CDC0_CIF_STR_DESC);
  USBD_STR_DEF(USBD_CDC0_DIF_STR_DESC);
#if (USBD2_CDC0_NCM)
  USBD_STR_DEF(USBD_CDC0_NCM_MAC_ADDRESS);
#endif
#endif
#if (USBD2_CDC1)
  USBD_STR_DEF(USBD_CDC1_CIF_STR_DESC);
  USBD_STR_DEF(USBD_CDC1_DIF_STR_DESC);
#if (USBD2_CDC1_NCM)
  USBD_STR_DEF(USBD_CDC1_NCM_MAC_ADDRESS);
#endif
#endif
#if (USBD2_CDC2)
  USBD_STR_DEF(USBD_CDC2_CIF_STR_DESC);
  USBD_STR_DEF(USBD_CDC2_DIF_STR_DESC);
#if (USBD2_CDC2_NCM)
  USBD_STR_DEF(USBD_CDC2_NCM_MAC_ADDRESS);
#endif
#endif
#if (USBD2_CDC3)
  USBD_STR_DEF(USBD_CDC3_CIF_STR_DESC);
  USBD_STR_DEF(USBD_CDC3_DIF_STR_DESC);
#if (USBD2_CDC3_NCM)
  USBD_STR_DEF(USBD_CDC3_NCM_MAC_ADDRESS);
#endif
#endif

#if (USBD2_HID0)
  USBD_STR_DEF(USBD_HID0_STR_DESC);
#endif
#if (USBD2_HID1)
  USBD_STR_DEF(USBD_HID1_STR_DESC);
#endif
#if (USBD2_HID2)
  USBD_STR_DEF(USBD_HID2_STR_DESC);
#endif
#if (USBD2_HID3)
  USBD_STR_DEF(USBD_HID3_STR_DESC);
#endif

#if (USBD2_MSC0)
  USBD_STR_DEF(USBD_MSC0_STR_DESC);
#endif
#if (USBD2_MSC1)
  USBD_STR_DEF(USBD_MSC1_STR_DESC);
#endif
#if (USBD2_MSC2)
  USBD_STR_DEF(USBD_MSC2_STR_DESC);
#endif
#if (USBD2_MSC3)
  USBD_STR_DEF(USBD_MSC3_STR_DESC);
#endif

} usbd2_string_descriptor
  =
{
  { 4, USB_STRING_DESCRIPTOR_TYPE, USBD2_STR_DESC_LANGID },
  USBD_STR_VAL(USBD2_STR_DESC_MAN),
  USBD_STR_VAL(USBD2_STR_DESC_PROD),
#if (USBD2_STR_DESC_SER_EN)
  USBD_STR_VAL(USBD2_STR_DESC_SER),
#endif

#if (USBD2_CUSTOM_CLASS0)
#if (USBD_CUSTOM_CLASS0_IF0_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS0_IF0_STR),
#endif
#if (USBD_CUSTOM_CLASS0_IF1_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS0_IF1_STR),
#endif
#if (USBD_CUSTOM_CLASS0_IF2_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS0_IF2_STR),
#endif
#if (USBD_CUSTOM_CLASS0_IF3_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS0_IF3_STR),
#endif
#endif
#if (USBD2_CUSTOM_CLASS1)
#if (USBD_CUSTOM_CLASS1_IF0_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS1_IF0_STR),
#endif
#if (USBD_CUSTOM_CLASS1_IF1_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS1_IF1_STR),
#endif
#if (USBD_CUSTOM_CLASS1_IF2_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS1_IF2_STR),
#endif
#if (USBD_CUSTOM_CLASS1_IF3_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS1_IF3_STR),
#endif
#endif
#if (USBD2_CUSTOM_CLASS2)
#if (USBD_CUSTOM_CLASS2_IF0_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS2_IF0_STR),
#endif
#if (USBD_CUSTOM_CLASS2_IF1_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS2_IF1_STR),
#endif
#if (USBD_CUSTOM_CLASS2_IF2_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS2_IF2_STR),
#endif
#if (USBD_CUSTOM_CLASS2_IF3_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS2_IF3_STR),
#endif
#endif
#if (USBD2_CUSTOM_CLASS3)
#if (USBD_CUSTOM_CLASS3_IF0_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS3_IF0_STR),
#endif
#if (USBD_CUSTOM_CLASS3_IF1_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS3_IF1_STR),
#endif
#if (USBD_CUSTOM_CLASS3_IF2_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS3_IF2_STR),
#endif
#if (USBD_CUSTOM_CLASS3_IF3_EN)
  USBD_STR_VAL(USBD_CUSTOM_CLASS3_IF3_STR),
#endif
#endif

#if (USBD2_ADC0)
  USBD_STR_VAL(USBD_ADC0_CIF_STR_DESC),
#if (USBD_ADC0_IF_SPKR)
  USBD_STR_VAL(USBD_ADC0_OUT_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC0_OUT_SIF_STR1_DESC),
#endif
#if (USBD_ADC0_IF_MIC)
  USBD_STR_VAL(USBD_ADC0_IN_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC0_IN_SIF_STR1_DESC),
#endif
#endif
#if (USBD2_ADC1)
  USBD_STR_VAL(USBD_ADC1_CIF_STR_DESC),
#if (USBD_ADC1_IF_SPKR)
  USBD_STR_VAL(USBD_ADC1_OUT_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC1_OUT_SIF_STR1_DESC),
#endif
#if (USBD_ADC1_IF_MIC)
  USBD_STR_VAL(USBD_ADC1_IN_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC1_IN_SIF_STR1_DESC),
#endif
#endif
#if (USBD2_ADC2)
  USBD_STR_VAL(USBD_ADC2_CIF_STR_DESC),
#if (USBD_ADC2_IF_SPKR)
  USBD_STR_VAL(USBD_ADC2_OUT_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC2_OUT_SIF_STR1_DESC),
#endif
#if (USBD_ADC2_IF_MIC)
  USBD_STR_VAL(USBD_ADC2_IN_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC2_IN_SIF_STR1_DESC),
#endif
#endif
#if (USBD2_ADC3)
  USBD_STR_VAL(USBD_ADC3_CIF_STR_DESC),
#if (USBD_ADC3_IF_SPKR)
  USBD_STR_VAL(USBD_ADC3_OUT_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC3_OUT_SIF_STR1_DESC),
#endif
#if (USBD_ADC3_IF_MIC)
  USBD_STR_VAL(USBD_ADC3_IN_SIF_STR0_DESC),
  USBD_STR_VAL(USBD_ADC3_IN_SIF_STR1_DESC),
#endif
#endif

#if (USBD2_CDC0)
  USBD_STR_VAL(USBD_CDC0_CIF_STR_DESC),
  USBD_STR_VAL(USBD_CDC0_DIF_STR_DESC),
#if (USBD2_CDC0_NCM)
  USBD_STR_VAL(USBD_CDC0_NCM_MAC_ADDRESS),
#endif
#endif
#if (USBD2_CDC1)
  USBD_STR_VAL(USBD_CDC1_CIF_STR_DESC),
  USBD_STR_VAL(USBD_CDC1_DIF_STR_DESC),
#if (USBD2_CDC1_NCM)
  USBD_STR_VAL(USBD_CDC1_NCM_MAC_ADDRESS),
#endif
#endif
#if (USBD2_CDC2)
  USBD_STR_VAL(USBD_CDC2_CIF_STR_DESC),
  USBD_STR_VAL(USBD_CDC2_DIF_STR_DESC),
#if (USBD2_CDC2_NCM)
  USBD_STR_VAL(USBD_CDC2_NCM_MAC_ADDRESS),
#endif
#endif
#if (USBD2_CDC3)
  USBD_STR_VAL(USBD_CDC3_CIF_STR_DESC),
  USBD_STR_VAL(USBD_CDC3_DIF_STR_DESC),
#if (USBD2_CDC3_NCM)
  USBD_STR_VAL(USBD_CDC3_NCM_MAC_ADDRESS),
#endif
#endif

#if (USBD2_HID0)
  USBD_STR_VAL(USBD_HID0_STR_DESC),
#endif
#if (USBD2_HID1)
  USBD_STR_VAL(USBD_HID1_STR_DESC),
#endif
#if (USBD2_HID2)
  USBD_STR_VAL(USBD_HID2_STR_DESC),
#endif
#if (USBD2_HID3)
  USBD_STR_VAL(USBD_HID3_STR_DESC),
#endif

#if (USBD2_MSC0)
  USBD_STR_VAL(USBD_MSC0_STR_DESC),
#endif
#if (USBD2_MSC1)
  USBD_STR_VAL(USBD_MSC1_STR_DESC),
#endif
#if (USBD2_MSC2)
  USBD_STR_VAL(USBD_MSC2_STR_DESC),
#endif
#if (USBD2_MSC3)
  USBD_STR_VAL(USBD_MSC3_STR_DESC),
#endif
};

usbd_desc_t usbd2_desc = {
  (uint8_t *)usbd2_ep0_descriptor,
  (uint8_t *)usbd2_device_descriptor,
  (uint8_t *)usbd2_device_qualifier_fs,
  (uint8_t *)usbd2_device_qualifier_hs,
  (uint8_t *)usbd2_config_descriptor_fs,
  (uint8_t *)usbd2_config_descriptor_hs,
  (uint8_t *)usbd2_other_speed_config_descriptor_fs,
  (uint8_t *)usbd2_other_speed_config_descriptor_hs,
  (uint8_t *)&usbd2_string_descriptor
};
