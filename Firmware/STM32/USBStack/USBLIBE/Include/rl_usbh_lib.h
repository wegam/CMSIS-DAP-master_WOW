/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    rl_usbh_lib.h
 * Purpose: USB Host header file
 * Rev.:    V6.5.0
 *----------------------------------------------------------------------------*/

#ifndef __RL_USBH_LIB_H__
#define __RL_USBH_LIB_H__

#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "rl_usb.h"
#include "usb_def.h"
#include "Driver_USBH.h"


//  ==== USB Host Constants and Defines ====

/// Macro for preparing URB to send Setup Packet
#define PREPARE_SETUP_PACKET(ptr_urb, ptr_data)                                \
  ptr_urb->buf                    =  ptr_data;                                 \
  ptr_urb->len                    =  8;                                        \
  ptr_urb->packet_type            =  USB_PID_SETUP;                            \
  ptr_urb->toggle_bit             =  0;                                        \
  ptr_urb->toggle_force           =  1;

/// Macro for preparing Setup Packet
#define PREPARE_SETUP_PACKET_DATA(ptr_sp, dir, typ, rcpnt, req, val, idx, len) \
  ptr_sp->bmRequestType.Dir       =  dir;                                      \
  ptr_sp->bmRequestType.Type      =  typ;                                      \
  ptr_sp->bmRequestType.Recipient =  rcpnt;                                    \
  ptr_sp->bRequest                =  req;                                      \
  ptr_sp->wValue                  =  U16_LE(val);                              \
  ptr_sp->wIndex                  =  U16_LE(idx);                              \
  ptr_sp->wLength                 =  U16_LE(len);

/// Macro for preparing URB to start reception with Data 1 In Packet
#define PREPARE_IN_DATA1_PACKET(ptr_urb, ptr_data, data_len)                   \
  ptr_urb->buf                    =  ptr_data;                                 \
  ptr_urb->len                    =  data_len;                                 \
  ptr_urb->packet_type            =  USB_PID_IN;                               \
  ptr_urb->toggle_bit             =  1;                                        \
  ptr_urb->toggle_force           =  1;

/// Macro for preparing URB to start reception with Data alternated In Packet
#define PREPARE_IN_DATAx_PACKET(ptr_urb, ptr_data, data_len)                   \
  ptr_urb->buf                    =  ptr_data;                                 \
  ptr_urb->len                    =  data_len;                                 \
  ptr_urb->packet_type            =  USB_PID_IN;                               \
  ptr_urb->toggle_force           =  0;

/// Macro for preparing URB to start transmission with Data 1 Out Packet
#define PREPARE_OUT_DATA1_PACKET(ptr_urb, ptr_data, data_len)                  \
  ptr_urb->buf                    =  ptr_data;                                 \
  ptr_urb->len                    =  data_len;                                 \
  ptr_urb->packet_type            =  USB_PID_OUT;                              \
  ptr_urb->toggle_bit             =  1;                                        \
  ptr_urb->toggle_force           =  1;

/// Macro for preparing URB to start transmission with Data alternated Out Packet
#define PREPARE_OUT_DATAx_PACKET(ptr_urb, ptr_data, data_len)                  \
  ptr_urb->buf                    =  ptr_data;                                 \
  ptr_urb->len                    =  data_len;                                 \
  ptr_urb->packet_type            =  USB_PID_OUT;                              \
  ptr_urb->toggle_force           =  0;

/// Macro for preparing URB to do Ping
#define PREPARE_PING_PACKET(ptr_urb)                                           \
  ptr_urb->len                    =  0;                                        \
  ptr_urb->packet_type            =  USB_PID_PING;                             \
  ptr_urb->toggle_force           =  0;

/// Macro for preparing Mass Storage Control Block Wrapper (CBW)
#define PREPARE_MSC_CBW(ptr_cbw, sig, tag, len, flg, lun, cb_len, cb0, cb1, cb2, cb3, cb4, cb5, cb6, cb7, cb8, cb9, cb10, cb11, cb12, cb13, cb14, cb15)\
  ptr_cbw->dSignature             =  U32_LE(sig);                              \
  ptr_cbw->dTag                   =  U32_LE(++tag);                            \
  ptr_cbw->dDataLength            =  len;                                      \
  ptr_cbw->bmFlags                =  flg;                                      \
  ptr_cbw->bLUN                   =  lun;                                      \
  ptr_cbw->bCBLength              =  cb_len;                                   \
  ptr_cbw->CB[0]                  =  cb0;                                      \
  ptr_cbw->CB[1]                  =  cb1;                                      \
  ptr_cbw->CB[2]                  =  cb2;                                      \
  ptr_cbw->CB[3]                  =  cb3;                                      \
  ptr_cbw->CB[4]                  =  cb4;                                      \
  ptr_cbw->CB[5]                  =  cb5;                                      \
  ptr_cbw->CB[6]                  =  cb6;                                      \
  ptr_cbw->CB[7]                  =  cb7;                                      \
  ptr_cbw->CB[8]                  =  cb8;                                      \
  ptr_cbw->CB[9]                  =  cb9;                                      \
  ptr_cbw->CB[10]                 =  cb10;                                     \
  ptr_cbw->CB[11]                 =  cb11;                                     \
  ptr_cbw->CB[12]                 =  cb12;                                     \
  ptr_cbw->CB[13]                 =  cb13;                                     \
  ptr_cbw->CB[14]                 =  cb14;                                     \
  ptr_cbw->CB[15]                 =  cb15;


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


//  ==== USB Host Internal Structures ====

/// Structure connecting Endpoint handle to thread ID
typedef struct {
  ARM_USBH_EP_HANDLE    hw_handle;                          ///< handle to hardware resource
  osThreadId            pipe_thread_id;                     ///< pipe transfer thread ID
} USBH_PIPE_TID_t;

/// Structure containing transfer information
typedef struct {
  uint32_t             *ptr_transfer;                       // pointer to transfer structure
  uint32_t             *ptr_pipe;                           // pointer to pipe structure
  uint32_t              packet;                             // packet
  uint8_t              *data;                               // pointer to data
  uint32_t              num;                                // number of bytes to transfer
  uint32_t              num_transferred_total;              // total number of bytes transferred
  uint32_t              num_to_transfer;                    // number of bytes to trasfer in single transfer
  uint32_t              active;                             // activity flag
} USBH_TRANSFER_INFO_t;

/// Structure containing configuration values for Custom Controller Interface
typedef struct {
  uint16_t              max_pipe;                           ///< maximum Pipes
} const USBH_HC_t;

/// Structure containing configuration values for OHCI Compliant Controller
typedef struct {
  uint32_t             *ptr_OHCI;                           ///< pointer to memory mapped reg base address
  uint16_t              max_ED;                             ///< maximum Endpoint Descriptors
  uint16_t              max_TD;                             ///< maximum Transfer Descriptors
  uint16_t              max_ITD;                            ///< maximum Isochronous Transfer Descriptors
  uint32_t             *ptr_HCCA;                           ///< pointer to HCCA memory start
  uint32_t             *ptr_ED;                             ///< pointer to ED memory start
  uint32_t             *ptr_TD;                             ///< pointer to TD memory start
  uint32_t             *ptr_ITD;                            ///< pointer to ITD memory start
  USBH_TRANSFER_INFO_t *ptr_TI;                             ///< pointer to Transfer Info (TI) array start
} const USBH_OHCI_t;

/// Structure containing configuration values for EHCI Compliant Controller
typedef struct {
  uint32_t             *ptr_EHCI;                           ///< pointer to memory mapped reg base address
  uint16_t              max_qH;                             ///< maximum queue Heads
  uint16_t              max_qTD;                            ///< maximum queue Transfer Descriptors
  uint16_t              max_iTD;                            ///< maximum Isochronous Transfer Descriptors
  uint16_t              max_siTD;                           ///< maximum split Isochronous Transfer Descriptors
  uint16_t              max_FSTN;                           ///< maximum periodic Frame Span Traversal Nodes
  uint32_t             *ptr_PFL;                            ///< pointer to Periodic Frame List memory
  uint32_t             *ptr_qH;                             ///< pointer to qH memory start
  uint32_t             *ptr_qTD;                            ///< pointer to qTD memory start
  uint32_t             *ptr_iTD;                            ///< pointer to iTD memory start
  uint32_t             *ptr_siTD;                           ///< pointer to siTD memory start
  uint32_t             *ptr_FSTN;                           ///< pointer to FSTN memory start
  USBH_TRANSFER_INFO_t *ptr_TI;                             ///< pointer to Transfer Info (TI) array start
} const USBH_EHCI_t;

/// Host Controller Instance (HCI) structure
typedef struct {
  uint16_t              port_con;                           ///< port connected map in software
  uint16_t              port_discon;                        ///< port disconnect map in software
  uint16_t              port_oc;                            ///< port over-current
  uint8_t               port_lock;                          ///< port locked (for enumeration (0 = none, 1..128 = locked port))
  uint8_t               port_rst;                           ///< port reset (for enumeration or recovery (0 = none, 1..128 = reset active port))
  uint8_t               port_state[16];                     ///< port states (8 bits per port)
  uint16_t              port_event[16];                     ///< port states (16 bits per port)
  uint32_t              port_retry;                         ///< port enumeration retry counters (2 bits per port)
  uint16_t              port_debounce;                      ///< port debounce active
  uint32_t              port_mem_max;                       ///< port maximum available memory from the common memory pool
  uint16_t              debounce_countdown;                 ///< de-bounce countdown counter
  uint16_t              debounce_max_countdown;             ///< de-bounce maximum countdown counter
  uint8_t               debounce_restart;                   ///< de-bounce restart
  uint8_t               last_dev_addr;                      ///< last addressed device address
  uint32_t              dev_addr_mask[4];                   ///< mask of used device addresses
  USBH_PIPE            *def_pipe;                           ///< Default Pipe
} USBH_HCI;

/// Mass Storage Class (MSC) instance structure
typedef struct {
  USBH_DEV             *ptr_dev;                            ///< pointer to device structure
  USBH_PIPE            *bulk_in_pipe;                       ///< bulk in pipe
  USBH_PIPE            *bulk_out_pipe;                      ///< bulk out pipe
  uint8_t               max_lun;                            ///< maximum logical units
  uint32_t              tag;                                ///< tag command/data/status protocol
  uint32_t              block_count;                        ///< block count (capacity)
  uint32_t              block_size;                         ///< block size (capacity)
  bool                  media_ok;                           ///< physical media ready status
} USBH_MSC;

/// Human Interface Device (HID) instance structure
typedef struct {
  USBH_DEV             *ptr_dev;                            ///< pointer to device structure
  USBH_PIPE            *int_in_pipe;                        ///< interrupt in pipe
  USBH_PIPE            *int_out_pipe;                       ///< interrupt out pipe
  osThreadId            int_in_thread_id;                   ///< interrupt in pipe thread ID
  uint8_t              *ptr_int_in_buf;                     ///< pointer to interrupt in buffer
  uint8_t               report_desc_type;                   ///< report descriptor type
  uint16_t              report_desc_len;                    ///< report descriptor length
  uint8_t               protocol;                           ///< protocol type (HID_PROTOCOL_KEYBOARD or HID_PROTOCOL_MOUSE)
  uint8_t               keyboard_in_key_pos;                ///< report input current key position
  uint8_t               hid_in_data_buf[8];                 ///< report input data buffer
  uint8_t               hid_in_data_buf_ex[8];              ///< report input data buffer last state
  uint16_t              hid_in_data_len;                    ///< report input data bytes received
  usbHID_MouseState     mouse_state;                        ///< current mouse position and state
} USBH_HID;

/// Communication Device Class (CDC) instance structure
typedef struct {
  USBH_DEV             *ptr_dev;                            ///< pointer to device structure
  USBH_PIPE            *bulk_in_pipe;                       ///< bulk in pipe
  USBH_PIPE            *bulk_out_pipe;                      ///< bulk out pipe
  USBH_PIPE            *int_in_pipe;                        ///< interrupt in pipe
  osThreadId            int_in_thread_id;                   ///< interrupt in pipe thread ID
} USBH_CDC;

//  ==== USB Host Functions for Memory Management ====

/// \brief Initialize memory pool to be used used by USB Host controller
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MemoryInitialize (uint8_t ctrl);

/// \brief De-initialize memory pool used by USB Host controller
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MemoryUninitialize (uint8_t ctrl);

/// \brief Allocate a chunk of memory from the initialized pool to be used by USB Host controller
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[out]    ptr                  pointer to pointer to allocated memory chunk.
/// \param[in]     size                 size of memory chunk to be allocated.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MemoryAllocate (uint8_t ctrl, uint8_t **ptr, uint32_t size);

/// \brief Release a piece of memory back to memory pool used by USB Host controller
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr                  pointer to allocated memory chunk to be released.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MemoryFree (uint8_t ctrl, uint8_t *ptr);

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

#endif
