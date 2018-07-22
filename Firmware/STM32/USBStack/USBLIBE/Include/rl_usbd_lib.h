/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    rl_usbd_lib.h
 * Purpose: USB Device header file
 * Rev.:    V6.6.2
 *----------------------------------------------------------------------------*/

#ifndef __RL_USBD_LIB_H__
#define __RL_USBD_LIB_H__

#include <stdint.h>
#include "usb_cdc.h"
#include "usb_msc.h"
#include "Driver_USBD.h"


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


//  ==== USB Device Internal Structures ====

/// Structure used for Control Endpoint 0 communication
typedef struct _usbd_ep_data_t {
  uint8_t              *data;                               ///< data buffer for send or receive
  uint16_t              cnt;                                ///< number of bytes in data buffer (to send or received)
} usbd_ep_data_t;

/// Structure containing device information
typedef struct _usbd_data_t {
  uint16_t              device_status;                      ///< device status (remote wakeup, self powered)
  uint8_t               device_address;                     ///< device address on the bus
  volatile uint8_t      configuration;                      ///< active configuration
  uint8_t               interface;                          ///< active interface
  uint32_t              endpoint_mask;                      ///< mask containing active endpoints
  uint32_t              endpoint_halt;                      ///< mask containing halted endpoints
  uint32_t              endpoint_no_halt_clr;               ///< mask containing endpoints on which halt clear is prevented
  uint32_t              endpoint_active;                    ///< mask containing endpoints with active transfers
  uint8_t               num_interfaces;                     ///< number of available interfaces
  union {
    uint8_t             flags;                              ///< status flags
    struct {
      uint8_t           high_speed : 1;                     ///< information if device is in high speed
      uint8_t           zlp        : 1;                     ///< zero length packet flag
      uint8_t           ext_handle : 1;                     ///< externally handled request
    };
  };

  usbd_ep_data_t        ep0_data;                           ///< Control Endpoint 0 structure
  USB_SETUP_PACKET      setup_packet;                       ///< Setup Packet structure
  uint8_t              *buf;                                ///< Buffer for in/out data
  int32_t               len;                                ///< Length for in/out data
} usbd_data_t;

/// Structure containing controller instance information for stack
typedef struct _usbd_dev_t {
  ARM_DRIVER_USBD      *driver;                             ///< pointer to driver
  uint8_t              *alt_setting;                        ///< pointer to alternate settings
  uint8_t              *ep0_buf;                            ///< pointer to Control Endpoint 0 buffer
  usbd_data_t          *data_ptr;                           ///< pointer to structure containing device information
  uint8_t               bmattributes;                       ///< bmAttributes configuration setting
  uint8_t               hs;                                 ///< high-speed capability setting
  uint16_t              if_num;                             ///< number of interfaces
  uint8_t               ep_num;                             ///< number of endpoints
  uint8_t               max_packet0;                        ///< maximum packet size for Control Endpoint 0
} const usbd_dev_t;

/// Structure containing configuration values for Custom Class device instance
typedef struct _usbd_custom_class_t {
  uint8_t               dev_num;                            ///< device instance configuration setting
  uint8_t               if0_num;                            ///< interface 0 number
  uint8_t               if1_num;                            ///< interface 1 number
  uint8_t               if2_num;                            ///< interface 2 number
  uint8_t               if3_num;                            ///< interface 3 number
  uint8_t               ep_msk;                             ///< mask of used endpoints
  uint8_t               if0_ep_bulk_out;                    ///< interface 0 bulk out endpoint number
  uint8_t               if0_ep_bulk_in;                     ///< interface 0 bulk in endpoint number
  uint8_t               if0_ep_int_out;                     ///< interface 0 interrupt out endpoint number
  uint8_t               if0_ep_int_in;                      ///< interface 0 interrupt in endpoint number
  uint8_t               if0_ep_iso_out;                     ///< interface 0 isochronous out endpoint number
  uint8_t               if0_ep_iso_in;                      ///< interface 0 isochronous in endpoint number
  uint8_t               if1_ep_bulk_out;                    ///< interface 1 bulk out endpoint number
  uint8_t               if1_ep_bulk_in;                     ///< interface 1 bulk in endpoint number
  uint8_t               if1_ep_int_out;                     ///< interface 1 interrupt out endpoint number
  uint8_t               if1_ep_int_in;                      ///< interface 1 interrupt in endpoint number
  uint8_t               if1_ep_iso_out;                     ///< interface 1 isochronous out endpoint number
  uint8_t               if1_ep_iso_in;                      ///< interface 1 isochronous in endpoint number
  uint8_t               if2_ep_bulk_out;                    ///< interface 2 bulk out endpoint number
  uint8_t               if2_ep_bulk_in;                     ///< interface 2 bulk in endpoint number
  uint8_t               if2_ep_int_out;                     ///< interface 2 interrupt out endpoint number
  uint8_t               if2_ep_int_in;                      ///< interface 2 interrupt in endpoint number
  uint8_t               if2_ep_iso_out;                     ///< interface 2 isochronous out endpoint number
  uint8_t               if2_ep_iso_in;                      ///< interface 2 isochronous in endpoint number
  uint8_t               if3_ep_bulk_out;                    ///< interface 3 bulk out endpoint number
  uint8_t               if3_ep_bulk_in;                     ///< interface 3 bulk in endpoint number
  uint8_t               if3_ep_int_out;                     ///< interface 3 interrupt out endpoint number
  uint8_t               if3_ep_int_in;                      ///< interface 3 interrupt in endpoint number
  uint8_t               if3_ep_iso_out;                     ///< interface 3 isochronous out endpoint number
  uint8_t               if3_ep_iso_in;                      ///< interface 3 isochronous in endpoint number
} const usbd_custom_class_t;

/// Structure containing runtime values for ADC device speaker instance
typedef struct _usbd_adc_spkr_data_t {
  uint8_t               active;                             ///< streaming interface active
  uint8_t               mute;                               ///< mute state
  uint16_t              vol_cur[2];                         ///< volume current value
  uint16_t              vol_min[2];                         ///< volume minimum value
  uint16_t              vol_max[2];                         ///< volume maximum value
  uint16_t              vol_res[2];                         ///< volume resolution
  uint8_t               receive_active;                     ///< reception of data on the USB Bus active
  uint8_t              *ptr_data_received;                  ///< pointer to receive intermediate buffer to received unread data
  int32_t               data_received_cnt;                  ///< number of received bytes (cumulative)
  uint8_t              *ptr_data_read;                      ///< pointer to receive intermediate buffer to received read data
  int32_t               data_read_cnt;                      ///< number of read bytes (cumulative)
} usbd_adc_spkr_data_t;

/// Structure containing runtime values for ADC device microphone instance
typedef struct _usbd_adc_mic_data_t {
  uint8_t               active;                             ///< streaming interface active
  uint8_t               mute;                               ///< mute state
  uint16_t              vol_cur[2];                         ///< volume current value
  uint16_t              vol_min[2];                         ///< volume minimum value
  uint16_t              vol_max[2];                         ///< volume maximum value
  uint16_t              vol_res[2];                         ///< volume resolution
  uint8_t               send_active;                        ///< sending of data on the USB Bus active
  uint8_t              *ptr_data_to_send;                   ///< pointer to send intermediate buffer to data to be sent
  int32_t               data_to_send_cnt;                   ///< number of bytes to send (cumulative)
  uint8_t              *ptr_data_sent;                      ///< pointer to send intermediate buffer to data already sent
  int32_t               data_sent_cnt;                      ///< number of bytes sent (cumulative)
} usbd_adc_mic_data_t;

/// Structure containing configuration values for ADC device (out or in) instance
typedef struct _usbd_adc_code_t {
  uint8_t              *data_buf;                           ///< data buffer for audio samples
  uint8_t               sif_num;                            ///< audio streaming (zero bandwidth) interface number (operational is next)
  uint8_t               fu_id;                              ///< feature unit ID
  uint8_t               ep_iso;                             ///< isochronous endpoint number
  uint32_t              ch_num;                             ///< number of channels (1 = mono, 2 = stereo)
  uint32_t              data_freq;                          ///< data frequency setting
  uint32_t              sample_sz;                          ///< sample size (in bytes)
  uint32_t              sample_res;                         ///< sample resolution (in bits)
  uint32_t              data_buf_sz;                        ///< data buffer size
  uint16_t              max_packet_size;                    ///< maximum packet size for isochronous endpoint (for LS/FS)
} const usbd_adc_code_t;

/// Structure containing configuration values for ADC device instance
typedef struct _usbd_adc_t {
  usbd_adc_spkr_data_t *spkr_data_ptr;                      ///< pointer to structure containing speaker (out) runtime values
  usbd_adc_code_t      *out_cfg;                            ///< pointer to structure containing out configuration settings
  usbd_adc_mic_data_t  *mic_data_ptr;                       ///< pointer to structure containing microphone (in) runtime values
  usbd_adc_code_t      *in_cfg;                             ///< pointer to structure containing in configuration settings
  uint8_t               dev_num;                            ///< device instance configuration setting
  uint8_t               cif_num;                            ///< audio control interface number
} const usbd_adc_t;

/// Structure containing runtime values for CDC device instance
typedef struct _usbd_cdc_data_t {
  uint8_t               send_active;                        ///< flag active while data is being sent
  uint8_t               send_zlp;                           ///< flag active when zero length packet needs to be sent
  uint8_t               receive_active;                     ///< flag active while data is being received
  uint8_t               notify_active;                      ///< flag active while notification is being sent
  uint8_t              *ptr_data_to_send;                   ///< pointer to send intermediate buffer to data to be sent
  int32_t               data_to_send_cnt;                   ///< number of bytes to send (cumulative)
  uint8_t              *ptr_data_sent;                      ///< pointer to send intermediate buffer to data already sent
  int32_t               data_sent_cnt;                      ///< number of bytes sent (cumulative)
  uint8_t              *ptr_data_received;                  ///< pointer to receive intermediate buffer to received unread data
  int32_t               data_received_cnt;                  ///< number of bytes received (cumulative)
  uint8_t              *ptr_data_read;                      ///< pointer to receive intermediate buffer to received read data
  int32_t               data_read_cnt;                      ///< number of bytes read (cumulative)
  uint16_t              control_line_state;                 ///< control line state settings bitmap (bit 0: DTR state, bit 1: - RTS state)
  CDC_LINE_CODING       line_coding;                        ///< communication settings */
  uint8_t               ncm_ntb_format;                     ///< NCM used NTB format (SetNtbFormat/GetNtbFormat)
  uint8_t               ncm_crc_mode;                       ///< NCM used CRC mode (SetCrcMode/GetCrcMode)
  uint16_t              ncm_max_datagram_size;              ///< NCM maximum datagram size (SetMaxDatagramSize/GetMaxDatagramSize)
  uint32_t              ncm_ntb_input_size;                 ///< NCM maximum NTB IN size that can be sent to host (SetNtbInputSize/GetNtbInputSize)
  uint32_t              ncm_in_ntb_seq;                     ///< NCM IN NTB sequence number
  uint32_t              ncm_out_ntb_seq;                    ///< NCM OUT NTB sequence number
  uint32_t              ncm_addr_in_ndp;                    ///< NCM address to current NDP in IN NTB (for sending)
  uint32_t              ncm_addr_out_ndp;                   ///< NCM address to current NDP in OUT NTB (received)
  uint32_t              ncm_in_datagram_index;              ///< NCM current datagram index in current NDP in IN NTB (for sending)
  uint32_t              ncm_in_datagram_num;                ///< NCM number of datagrams for current NDP in IN NTB (for sending)
  uint32_t              ncm_out_datagram_index;             ///< NCM current datagram index in current NDP in OUT NTB (received)
  uint32_t              ncm_ntb_in_len;                     ///< NCM current IN NTB data size (for sending)
  uint32_t              ncm_ntb_in_buf_len[2];              ///< NCM current IN NTB data size in respective buffer (for sending)
  uint32_t              ncm_ntb_out_buf_len[2];             ///< NCM current OUT NTB data size in respective buffer (received)
  CDC_NCM_NTB_PARAM     ncm_ntb_param;                      ///< NCM NTB parameter structure */
} usbd_cdc_data_t;

/// Structure containing configuration values for CDC device instance
typedef struct _usbd_cdc_t {
  uint8_t              *send_buf;                           ///< send data buffer
  uint8_t              *receive_buf;                        ///< receive data buffer
  uint8_t              *notify_buf;                         ///< notify data buffer
  usbd_cdc_data_t      *data_ptr;                           ///< pointer to structure containing runtime values
  uint8_t               dev_num;                            ///< device instance configuration setting
  uint8_t               acm;                                ///< abstract control model
  uint8_t               cif_num;                            ///< communication class interface number
  uint8_t               dif_num;                            ///< data class interface number
  uint8_t               ep_int_in;                          ///< interrupt in endpoint number
  uint8_t               ep_bulk_in;                         ///< bulk in endpoint number
  uint8_t               ep_bulk_out;                        ///< bulk out endpoint number
  uint16_t              send_buf_sz;                        ///< maximum size of send buffer
  uint16_t              receive_buf_sz;                     ///< maximum size of receive buffer
  uint16_t              max_packet_size [2];                ///< maximum packet size for interrupt endpoint (for LS/FS and HS)
  uint16_t              max_packet_size1[2];                ///< maximum packet size for bulk endpoints (for LS/FS and HS)
  uint8_t               ncm_raw;                            ///< NCM raw access configuration
  uint8_t               ncm_in_buf_cnt;                     ///< NCM number of input buffers
  uint8_t               ncm_out_buf_cnt;                    ///< NCM number of output buffers
  uint16_t              ncm_max_segment_size;               ///< NCM Maximum Segment Size configuration
  uint8_t               ncm_ntb_formats;                    ///< NCM Supported NTB Formats configuration
  uint32_t              ncm_ntb_in_max_size;                ///< NCM Maximum IN NTB Size configuration
  uint16_t              ncm_ndp_in_divisor;                 ///< NCM IN NTB Datagram Payload Alignment Divisor configuration
  uint16_t              ncm_ndp_in_payload_reminder;        ///< NCM IN NTB Datagram Payload Alignment Remainder configuration
  uint16_t              ncm_ndp_in_alignment;               ///< NCM NDP Alignment Modulus in IN NTB configuration
  uint32_t              ncm_ntb_out_max_size;               ///< NCM Maximum OUT NTB Size configuration
  uint16_t              ncm_ndp_out_divisor;                ///< NCM OUT NTB Datagram Payload Alignment Divisor configuration
  uint16_t              ncm_ndp_out_payload_reminder;       ///< NCM OUT NTB Datagram Payload Alignment Remainder configuration
  uint16_t              ncm_ndp_out_alignment;              ///< NCM NDP Alignment Modulus in OUT NTB configuration
} const usbd_cdc_t;

/// Structure containing runtime values for HID device instance
typedef struct _usbd_hid_data_t {
  uint8_t               protocol;                           ///< active protocol
  bool                  data_out_async_req;                 ///< request to asynchronously send data flag
  volatile bool         data_out_in_progress;               ///< data out in progress flag
  uint32_t              data_out_update_req_mask;           ///< request to update send data flag
  uint8_t              *ptr_data_out;                       ///< send data buffer
  volatile uint16_t     data_out_to_send_len;               ///< length of data to be sent
  uint16_t              data_out_sent_len;                  ///< length of data already sent
  bool                  data_out_end_with_zlp_packet;       ///< data send ended with Zero Length Packet (ZLP) flag
  uint8_t              *ptr_data_in;                        ///< receive data buffer
  uint16_t              data_in_rece_len;                   ///< length of received data
  uint8_t              *ptr_data_feat;                      ///< feature data buffer
  uint16_t              data_feat_rece_len;                 ///< length of received feature data
  uint16_t              polling_count;                      ///< polling count used for data update
} usbd_hid_data_t;

/// Structure containing configuration values for HID device instance
typedef struct _usbd_hid_t {
  uint16_t             *idle_count;                         ///< pointer to idle count data for each report
  uint16_t             *idle_reload;                        ///< pointer to idle reload data for each report
  uint8_t              *idle_set;                           ///< pointer to idle set data (using SetIdle) for each report
  uint8_t              *in_report;                          ///< input report data buffer for each report
  uint8_t              *out_report;                         ///< output report data buffer for each report
  uint8_t              *feat_report;                        ///< feature report data buffer for each report
  usbd_hid_data_t      *data_ptr;                           ///< pointer to structure containing runtime values for each report
  uint8_t               dev_num;                            ///< device instance configuration setting
  uint8_t               if_num;                             ///< interface number
  uint8_t               ep_int_in;                          ///< interrupt in endpoint number
  uint8_t               ep_int_out;                         ///< interrupt out endpoint number (0 if not used)
  uint16_t              ep_int_in_interval        [2];      ///< interrupt in endpoint polling interval configuration setting (for LS/FS and HS)
  uint16_t              ep_int_in_max_packet_size [2];      ///< interrupt in endpoint maximum packet size interrupt endpoints (for LS/FS and HS)
  uint16_t              ep_int_out_interval       [2];      ///< interrupt out endpoint polling interval configuration setting (for LS/FS and HS)
  uint16_t              ep_int_out_max_packet_size[2];      ///< interrupt out endpoint maximum packet size interrupt endpoints (for LS/FS and HS)
  uint8_t               in_report_num;                      ///< number of input reports
  uint8_t               out_report_num;                     ///< number of output reports
  uint16_t              in_report_max_sz;                   ///< maximum input report size
  uint16_t              out_report_max_sz;                  ///< maximum output report size
  uint16_t              feat_report_max_sz;                 ///< maximum feature report size
} const usbd_hid_t;

/// Structure containing values for HID descriptor
typedef struct _usbd_hid_desc_t {
  uint8_t              *report_descriptor;                  ///< report descriptor
  uint16_t              report_descriptor_size;             ///< report descriptor size
  uint16_t              hid_descriptor_offset;              ///< HID descriptor offset in configuration descriptor
} usbd_hid_desc_t;

/// Structure containing runtime values for MSC device instance
typedef struct _usbd_msc_data_t {
  MSC_CBW           cbw;                ///< command block wrapper
  MSC_CSW           csw;                ///< command status wrapper
  uint32_t          block;              ///< read/write operation block
  uint32_t          offset;             ///< read/write operation offset
  uint32_t          length;             ///< read write operation remaining length
  bool              mem_ok;             ///< memory verify status
  uint8_t           bulk_stage;         ///< bulk stage
  uint32_t          bulk_len;           ///< bulk in/out length
  uint32_t          bulk_req_len;       ///< bulk in/out requested length
  bool              media_ready;        ///< media ready flag  (Legacy Support)
  uint32_t          memory_size;        ///< media memory size (Legacy Support)
  uint32_t          block_size;         ///< media block size
  uint32_t          block_group;        ///< blocks available size in cache
  uint32_t          block_count;        ///< media total number of blocks
  uint8_t          *block_buf;          ///< data buffer for media data read/write
  uint8_t           request_sense;      ///< current request sense information
} usbd_msc_data_t;

/// Structure containing configuration values for MSC device instance
typedef struct _usbd_msc_t {
  uint8_t          *bulk_buf;           ///< data buffer for bulk transfers
  usbd_msc_data_t  *data_ptr;           ///< pointer to structure containing runtime values
  uint8_t           dev_num;            ///< device instance configuration setting
  uint8_t           if_num;             ///< interface number
  uint8_t           ep_bulk_in;         ///< bulk in endpoint number
  uint8_t           ep_bulk_out;        ///< bulk out endpoint number
  uint32_t          bulk_buf_sz;        ///< size of bulk buffer
  uint16_t          max_packet_size[2]; ///< maximum packet size for bulk endpoints (for LS/FS and HS)
  uint8_t          *inquiry_data;       ///< data returned upon SCSI Inquiry request
} const usbd_msc_t;

/// Structure containing all descriptors (except report descriptor)
typedef struct _usbd_desc_t {
  uint8_t              *ep0_descriptor;                     ///< Control Endpoint 0 descriptor
  uint8_t              *device_descriptor;                  ///< device descriptor
  uint8_t              *device_qualifier_fs;                ///< device qualifier for low/full-speed
  uint8_t              *device_qualifier_hs;                ///< device qualifier for high-speed
  uint8_t              *config_descriptor_fs;               ///< configuration descriptor for low/full-speed
  uint8_t              *config_descriptor_hs;               ///< configuration descriptor for high-speed
  uint8_t              *other_speed_config_descriptor_fs;   ///< other speed configuration descriptor for low/full-speed
  uint8_t              *other_speed_config_descriptor_hs;   ///< other speed configuration descriptor for high-speed
  uint8_t              *string_descriptor;                  ///< string descriptors
} usbd_desc_t;

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
