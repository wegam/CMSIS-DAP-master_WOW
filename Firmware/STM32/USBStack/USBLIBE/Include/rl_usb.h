/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    rl_usb.h
 * Purpose: USB User API
 * Rev.:    V6.6.1
 *----------------------------------------------------------------------------*/

#ifndef __RL_USB_H__
#define __RL_USB_H__


#ifdef __cplusplus
extern "C"  {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "usb_def.h"
#include "usb_cdc.h"
#include "usb_hid.h"
#include "usb_msc.h"


///  ==== USB Constants and Defines ====

/// Status code values returned by USB library functions.
typedef enum {
  usbOK                       =    0,   ///< Function completed with no error

  usbTimeout,                           ///< Function completed; time-out occurred
  usbInvalidParameter,                  ///< Invalid Parameter error: a mandatory parameter was missing or specified an incorrect object

  usbThreadError              = 0x10,   ///< CMSIS-RTOS Thread creation/termination failed
  usbTimerError,                        ///< CMSIS-RTOS Timer creation/deletion failed
  usbSemaphoreError,                    ///< CMSIS-RTOS Semaphore creation failed

  usbControllerError          = 0x20,   ///< Controller does not exist
  usbDeviceError,                       ///< Device does not exist
  usbDriverError,                       ///< Driver function produced error
  usbDriverBusy,                        ///< Driver function is busy
  usbMemoryError,                       ///< Memory management function produced error
  usbNotConfigured,                     ///< Device is not configured (is connected)
  usbClassErrorADC,                     ///< Audio Device Class (ADC) error (no device or device produced error)
  usbClassErrorCDC,                     ///< Communication Device Class (CDC) error (no device or device produced error)
  usbClassErrorHID,                     ///< Human Interface Device (HID) error (no device or device produced error)
  usbClassErrorMSC,                     ///< Mass Storage Device (MSC) error (no device or device produced error)
  usbClassErrorCustom,                  ///< Custom device Class (Class) error (no device or device produced error)
  usbUnsupportedClass,                  ///< Unsupported Class

  usbTransferStall            = 0x40,   ///< Transfer handshake was stall
  usbTransferError,                     ///< Transfer error

  usbUnknownError             = 0xFF    ///< Unspecified USB error
} usbStatus;

/// Endianess handling macros
#ifdef __BIG_ENDIAN
 #define U32_LE(v)  (uint32_t)(__rev(v))
 #define U16_LE(v)  (uint16_t)(__rev(v) >> 16)
 #define U32_BE(v)  (uint32_t)(v)
 #define U16_BE(v)  (uint16_t)(v)
#else
 #define U32_BE(v)  (uint32_t)(__rev(v))
 #define U16_BE(v)  (uint16_t)(__rev(v) >> 16)
 #define U32_LE(v)  (uint32_t)(v)
 #define U16_LE(v)  (uint16_t)(v)
#endif

//  ==== USB Device Constants and Defines ====

/// USB Device Custom Class API enumerated constants
typedef enum {
  usbdRequestNotProcessed = 0,          ///< Request not processed
  usbdRequestOK,                        ///< Request processed and OK
  usbdRequestStall,                     ///< Request processed but unsupported
  usbdRequestNAK                        ///< Request processed but busy
} usbdRequestStatus;

/// USB Device MSC Check Media bit masks
#define USBD_MSC_MEDIA_READY     (1U)   ///< Media Ready
#define USBD_MSC_MEDIA_PROTECTED (1U<<1)///< Media Write Protected

/// USB Device HID Class API enumerated constants
typedef enum {
  USBD_HID_REQ_EP_CTRL = 0,             ///< Request from control endpoint
  USBD_HID_REQ_EP_INT,                  ///< Request from interrupt endpoint
  USBD_HID_REQ_PERIOD_UPDATE            ///< Request from periodic update
} USBD_HID_REQ_t;

/* USB Host Constants and Defines */

/* USB Host Pipe settings structure */
/// @cond USBH_PIPE_cond
typedef struct {
  uint32_t          hw_handle;          ///< Handle to Hardware resource
  uint8_t           dev_addr;           ///< Device communication Address
  uint8_t           dev_speed;          ///< Device communication Speed
  uint8_t           hub_addr;           ///< Hub communication Address
  uint8_t           hub_port;           ///< Hub communication Port
  uint8_t           bEndpointAddress;   ///< Endpoint Address + direction
  uint8_t           bmAttributes;       ///< Endpoint Attributes (type + Isochronous info)
  uint16_t          wMaxPacketSize;     ///< Maximum Packet Size + Isochronous info
  uint8_t           bInterval;          ///< Interval
  uint32_t          transferred;        ///< Last transferred information
  uint8_t           active;             ///< Activity flag
} USBH_PIPE;
/// @endcond

/* USB Host Device Instance (DEV) structure */
/// @cond USBH_DEV_cond
typedef struct {
  uint8_t           ctrl;               ///< Index of USB Host controller
  uint8_t           dev_addr;           ///< Device communication Address
  uint8_t           dev_speed;          ///< Device communication Speed
  uint8_t           hub_addr;           ///< Hub communication Address
  uint8_t           hub_port;           ///< Hub communication Port
  struct {
    uint8_t         configured  : 1;    ///< Device Configured status
    uint8_t         initialized : 1;    ///< Device Initialized status
  } state;
  uint8_t           max_packet_size;    ///< Maximum Packet Size
  uint8_t           vid;                ///< Vendor ID
  uint8_t           pid;                ///< Product ID

  uint8_t           class_custom;       ///< Class Custom handling
  uint8_t           class_instance;     ///< Class instance
  uint8_t           class_driver;       ///< Class Driver used
  uint8_t           dev_desc_len;       ///< Device Descriptor Length
  uint8_t           cfg_desc_len;       ///< Configuration Descriptor Length
  osThreadId        recovery_thread_id; ///< Thread ID of thread that activated Recovery
} USBH_DEV;
/// @endcond


/*  USB Host externally defined variables */

/* USB Host number of Custom Class (CLS) instances as defined in USBH_Config_Class.h file */
/// @cond usbh_cls_num_cond
extern const uint8_t usbh_cls_num;
/// @endcond


//  ==== USB Device Functions ====


/// \brief Initialize USB Device stack and controller
/// \param[in]     device               index of USB Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_Initialize (uint8_t device);

/// \brief De-initialize USB Device stack and controller
/// \param[in]     device               index of USB Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_Uninitialize (uint8_t device);

/// \brief Activate pull-up on D+ or D- line to signal USB Device connection on USB Bus
/// \param[in]     device               index of USB Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_Connect (uint8_t device);

/// \brief Disconnect USB Device from USB Bus
/// \param[in]     device               index of USB Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_Disconnect (uint8_t device);

/// \brief Return USB Device configuration status
/// \param[in]     device               index of USB Device.
/// \return        true                 device is in configured state and ready to communicate.
/// \return        false                device is not configured and not ready to communicate.
extern bool USBD_Configured (uint8_t device);

#ifdef __DOXYGEN__

// following functions are available for each instance of a Device.
// generic prefix USBD_Devicen is USBD_Device0 for Device instance 0.

/// \brief Called during \ref USBD_Initialize to initialize the USB Device
/// \return                             none.
void USBD_Devicen_Initialize (void);
 
/// \brief Called during \ref USBD_Uninitialize to de-initialize the USB Device
/// \return                             none.
void USBD_Devicen_Uninitialize (void);
 
/// \brief Device Reset Event handling
/// \return                             none.
void USBD_Devicen_EventReset (void);
 
/// \brief Callback function called when Device received SETUP PACKET on Control Endpoint 0
/// \param[in]     setup_packet         pointer to received setup packet.
/// \param[out]    buf                  pointer to data buffer used for data stage requested by setup packet.
/// \param[out]    len                  pointer to number of data bytes in data stage requested by setup packet.
/// \return        usbdRequestStatus    enumerator value indicating the function execution status
/// \return        usbdRequestNotProcessed:request was not processed; processing will be done by USB library
/// \return        usbdRequestOK:       request was processed successfully (send Zero-Length Packet if no data stage)
/// \return        usbdRequestStall:    request was processed but is not supported (stall Endpoint 0)
usbdRequestStatus USBD_Devicen_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, int32_t *len);

/// \brief Callback function called when SETUP PACKET was processed by USB library
/// \param[in]     setup_packet         pointer to processed setup packet.
/// \return                             none.
void USBD_Devicen_Endpoint0_SetupPacketProcessed (const USB_SETUP_PACKET *setup_packet);

/// \brief Callback function called when Device received OUT DATA on Control Endpoint 0
/// \param[in]     len                  number of received data bytes.
/// \return        usbdRequestStatus    enumerator value indicating the function execution status
/// \return        usbdRequestNotProcessed:request was not processed; processing will be done by USB library
/// \return        usbdRequestOK:       request was processed successfully (send Zero-Length Packet)
/// \return        usbdRequestStall:    request was processed but is not supported (stall Endpoint 0)
/// \return        usbdRequestNAK:      request was processed but the device is busy (return NAK)
usbdRequestStatus USBD_Devicen_Endpoint0_OutDataReceived (uint32_t len);

/// \brief Callback function called when Device sent IN DATA on Control Endpoint 0
/// \param[in]     len                  number of sent data bytes.
/// \return        usbdRequestStatus    enumerator value indicating the function execution status
/// \return        usbdRequestNotProcessed:request was not processed; processing will be done by USB library
/// \return        usbdRequestOK:       request was processed successfully (return ACK)
/// \return        usbdRequestStall:    request was processed but is not supported (stall Endpoint 0)
/// \return        usbdRequestNAK:      request was processed but the device is busy (return NAK)
usbdRequestStatus USBD_Devicen_Endpoint0_InDataSent (uint32_t len);

#endif // __DOXYGEN

//  ==== USB Device Audio Device Functions ====

#ifdef __DOXYGEN__

// following functions are available for each instance of a ADC class.
// generic prefix USBD_ADCn is USBD_ADC0 for ADC class instance 0.

/// \brief Called during \ref USBD_Initialize to initialize the USB ADC class instance
/// \return                             none.
void USBD_ADCn_Initialize (void);

/// \brief Called during \ref USBD_Uninitialize to de-initialize the USB ADC class instance
/// \return                             none.
void USBD_ADCn_Uninitialize (void);

/// \brief Callback function called when speaker activity (interface) setting changed event
/// \param[in]     active               activity status.
/// \return                             none.
void USBD_ADCn_SpeakerStatusEvent (bool active);

/// \brief Callback function called when speaker mute setting changed event
/// \param[in]     ch                   channel index.
///                                       - value 0: master channel
///                                       - value 1: left speaker (in stereo mode)
///                                       - value 2: right speaker (in stereo mode)
/// \param[in]     cur                  current setting.
/// \return                             none.
void USBD_ADCn_SpeakerMuteEvent (uint8_t ch, bool cur);

/// \brief Callback function called when speaker volume setting changed event
/// \param[in]     ch                   channel index.
///                                       - value 0: master channel
///                                       - value 1: left speaker (in stereo mode)
///                                       - value 2: right speaker (in stereo mode)
/// \param[in]     cur                  current setting.
/// \return                             none.
void USBD_ADCn_SpeakerVolumeEvent (uint8_t ch, uint16_t cur);

/// \brief Callback function called when microphone activity (interface) setting changed event
/// \param[in]     active               activity status.
/// \return                             none.
void USBD_ADCn_MicrophoneStatusEvent (bool active);

/// \brief Callback function called when microphone mute setting changed event
/// \param[in]     ch                   channel index.
///                                       - value 0: master channel
///                                       - value 1: left microphone (in stereo mode)
///                                       - value 2: right microphone (in stereo mode)
/// \param[in]     cur                  current setting.
/// \return                             none.
void USBD_ADCn_MicrophoneMuteEvent (uint8_t ch, bool cur);

/// \brief Callback function called when microphone volume setting changed event
/// \param[in]     ch                   channel index.
///                                       - value 0: master channel
///                                       - value 1: left microphone (in stereo mode)
///                                       - value 2: right microphone (in stereo mode)
/// \param[in]     cur                  current setting.
/// \return                             none.
void USBD_ADCn_MicrophoneVolumeEvent (uint8_t ch, uint16_t cur);

#endif // __DOXYGEN

/// \brief Set range for speaker volume control
/// \param[in]     instance             instance of ADC class.
/// \param[in]     ch                   channel index.
///                                       - value 0: master channel
///                                       - value 1: left speaker (in stereo mode)
///                                       - value 2: right speaker (in stereo mode)
/// \param[in]     min                  minimum volume value.
/// \param[in]     max                  maximum volume value.
/// \param[in]     res                  volume resolution.
/// \param[in]     cur                  current volume value.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_ADC_SpeakerSetVolumeRange (uint8_t instance, uint8_t ch, uint16_t min, uint16_t max, uint16_t res, uint16_t cur);

/// \brief Set range for microphone volume (level) control
/// \param[in]     instance             instance of ADC class.
/// \param[in]     ch                   channel index.
///                                       - value 0: master channel
///                                       - value 1: left microphone (in stereo mode)
///                                       - value 2: right microphone (in stereo mode)
/// \param[in]     min                  minimum volume value.
/// \param[in]     max                  maximum volume value.
/// \param[in]     res                  volume resolution.
/// \param[in]     cur                  current volume value.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_ADC_MicrophoneSetVolumeRange (uint8_t instance, uint8_t ch, uint16_t min, uint16_t max, uint16_t res, uint16_t cur);

/// \brief Number of audio samples received from USB Host and available to be read
/// \param[in]     instance             instance of ADC class.
/// \return                             number of samples available to be read.
extern uint32_t USBD_ADC_ReceivedSamplesAvailable (uint8_t instance);

/// \brief Number of audio samples written and pending to be sent to USB Host
/// \param[in]     instance             instance of ADC class.
/// \return                             number of samples ready to be sent.
extern uint32_t USBD_ADC_WrittenSamplesPending (uint8_t instance);

/// \brief Read audio samples received from USB Host
/// \param[in]     instance             instance of ADC class.
/// \param[out]    buf                  buffer that receives samples.
/// \param[in]     num                  maximum number of samples to read.
/// \return                             number of samples read or execution status.
///                - value >= 0:        number of samples read
///                - value < 0:         error occurred, -value is execution status as defined with \ref usbStatus
extern int32_t USBD_ADC_ReadSamples (uint8_t instance, void *buf, int32_t num);

/// \brief Write audio samples to be transferred to USB Host
/// \param[in]     instance             instance of ADC class.
/// \param[in]     buf                  buffer containing samples to write.
/// \param[in]     num                  maximum number of samples to write.
/// \return                             number of samples written or execution status.
///                - value >= 0:        number of samples written for sending
///                - value < 0:         error occurred, -value is execution status as defined with \ref usbStatus
extern int32_t USBD_ADC_WriteSamples (uint8_t instance, const void *buf, int32_t num);


//  ==== USB Device Communication Device (Abstract Control Model) Functions ====

#ifdef __DOXYGEN__

// following functions are available for each instance of a CDC class.
// generic prefix USBD_CDCn is USBD_CDC0 for CDC class instance 0.

/// \brief Called during \ref USBD_Initialize to initialize the USB CDC class instance (ACM)
/// \return                             none.
void USBD_CDCn_ACM_Initialize (void);

/// \brief Called during \ref USBD_Uninitialize to de-initialize the USB CDC class instance (ACM)
/// \return                             none.
void USBD_CDCn_ACM_Uninitialize (void);

/// \brief Called upon USB Bus Reset Event
/// \return                             none.
void USBD_CDCn_ACM_Reset (void);

/// \brief Called upon USB Host request to change communication settings
/// \param[in]     line_coding          pointer to CDC_LINE_CODING structure.
/// \return        true                 set line coding request processed.
/// \return        false                set line coding request not supported or not processed.
bool USBD_CDCn_ACM_SetLineCoding (CDC_LINE_CODING *line_coding);

/// \brief Called upon USB Host request to retrieve communication settings
/// \param[out]    line_coding          pointer to CDC_LINE_CODING structure.
/// \return        true                 get line coding request processed.
/// \return        false                get line coding request not supported or not processed.
bool USBD_CDCn_ACM_GetLineCoding (CDC_LINE_CODING *line_coding);

/// \brief Called upon USB Host request to set control line states
/// \param[in]     state                control line settings bitmap.
///                                       - bit 0: DTR state
///                                       - bit 1: RTS state
/// \return        true                 set control line state request processed.
/// \return        false                set control line state request not supported or not processed.
bool USBD_CDCn_ACM_SetControlLineState (uint16_t state);

/// \brief Called when new data was received
/// \param[in]     len                  number of bytes available to read.
/// \return                             none.
void USBD_CDCn_ACM_DataReceived (uint32_t len);

/// \brief Called when all data was sent
/// \return                             none.
void USBD_CDCn_ACM_DataSent (void);

/// \brief Called during USBD_Initialize to initialize the USB CDC class instance (NCM)
/// \return                             none.
void USBD_CDCn_NCM_Initialize (void);

/// \brief Called during USBD_Uninitialize to de-initialize the USB CDC class instance (NCM)
/// \return                             none.
void USBD_CDCn_NCM_Uninitialize (void);

/// \brief Called upon USB Bus Reset Event
/// \return                             none.
void USBD_CDCn_NCM_Reset (void);

/// \brief Called when USB Host changes data interface from alternate 0 to alternate 1 (activates data interface)
/// \return                             none.
void USBD_CDCn_NCM_Start (void);

/// \brief Called when USB Host changes data interface from alternate 1 to alternate 0 (de-activates data interface)
/// \return                             none.
void USBD_CDCn_NCM_Stop (void);

/// \brief Called upon USB Host request to set the Ethernet device multicast filters
/// \param[in]     addr_list            Pointer to list of 48-bit Multicast addresses.
/// \param[in]     num_of_filters       Number of filters.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetEthernetMulticastFilters (const uint8_t *addr_list, uint16_t num_of_filters);

/// \brief Called upon USB Host request to set up the specified Ethernet power management pattern filter
/// \param[in]     filter_number        Filter number.
/// \param[in]     pattern_filter       Power management pattern filter structure.
/// \param[in]     pattern_filter_size  Size of pattern filter structure.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetEthernetPowerManagementPatternFilter (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size);

/// \brief Called upon USB Host request to retrieve the status of the specified Ethernet power management pattern filter
/// \param[in]     filter_number        Filter number.
/// \param[out]    pattern_active       Pointer to pattern active boolean.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetEthernetPowerManagementPatternFilter (uint16_t filter_number, uint16_t *pattern_active);

/// \brief Called upon USB Host request to configure device Ethernet packet filter settings
/// \param[in]     packet_filter_bitmap Packet Filter Bitmap.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetEthernetPacketFilter (uint16_t packet_filter_bitmap);

/// \brief Called upon USB Host request to retrieve a statistic based on the feature selector
/// \param[in]     feature_selector     Feature Selector.
/// \param[out]    data                 Pointer to Statistics Value.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetEthernetStatistic (uint16_t feature_selector, uint32_t *data);

/// \brief Called upon USB Host request to retrieve the parameters that describe NTBs for each direction
/// \param[out]    ntb_params           Pointer to NTB Parameter Structure.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetNtbParameters (CDC_NCM_NTB_PARAM *ntb_params);

/// \brief Called upon USB Host request to return the USB Device's current EUI-48 station address
/// \param[out]    net_addr             Pointer to EUI-48 current address, in network byte order.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetNetAddress (uint8_t *net_addr);

/// \brief Called upon USB Host request to set the USB Device's current EUI-48 station address
/// \param[in]     net_addr             Pointer to EUI-48 address, in network byte order.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetNetAddress (const uint8_t *net_addr);

/// \brief Called upon USB Host request to return the NTB data format currently being used
/// \param[out]    ntb_format           Pointer to NTB format code.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetNtbFormat (uint16_t *ntb_format);

/// \brief Called upon USB Host request to select the format of NTB to be used for NTBs transmitted to the USB Host
/// \param[in]     ntb_format           NTB format selection:
///                  - value 0 :        NTB-16
///                  - value 1 :        NTB-32
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetNtbFormat (uint16_t ntb_format);

/// \brief Called upon USB Host request to return NTB input size currently being used
/// \param[out]    ntb_input_size       Pointer to NTB input size.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetNtbInputSize (uint32_t *ntb_input_size);

/// \brief Called upon USB Host request to select the maximum size of NTB that is permitted to be sent to the USB Host
/// \param[in]     ntb_input_size       Maximum NTB size.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetNtbInputSize (uint32_t ntb_input_size);

/// \brief Called upon USB Host request to return the currently effective maximum datagram size
/// \param[out]    max_datagram_size    Pointer to current maximum datagram size.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetMaxDatagramSize (uint16_t *max_datagram_size);

/// \brief Called upon USB Host request to select the maximum datagram size that can be sent in an NTB
/// \param[in]     max_datagram_size    Maximum datagram size.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetMaxDatagramSize (uint16_t max_datagram_size);

/// \brief Called upon USB Host request to return the currently selected CRC mode
/// \param[out]    crc_mode             Pointer to current CRC mode.
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_GetCrcMode (uint16_t *crc_mode);

/// \brief Called upon USB Host request to control CRC mode
/// \param[in]     crc_mode             CRC mode:
///                  - value 0 :        CRCs shall not be appended
///                  - value 1 :        CRCs shall be appended
/// \return        true                 if this request was handled.
/// \return        false                if this request was not handled.
bool USBD_CDCn_NCM_SetCrcMode (uint16_t crc_mode);

/// \brief Called when NTB was successfully sent
/// \return                             none.
void USBD_CDCn_NCM_NTB_IN_Sent (void);

/// \brief Called when NTB was successfully received
/// \return                             none.
void USBD_CDCn_NCM_NTB_OUT_Received (void);

#endif // __DOXYGEN

/// \brief Read one character received by Communication Device from USB Host
/// \param[in]     instance             instance of CDC class.
/// \return                             value of read character or no character received.
///                - value >= 0:        value of first received unread character
///                - value -1:          indicates no character was received
extern int USBD_CDC_ACM_GetChar (uint8_t instance);

/// \brief Write a single character from Communication Device to USB Host
/// \param[in]     instance             instance of CDC class.
/// \param[in]     ch                   character to write.
/// \return                             value of accepted character or no character accepted.
///                - value ch:          if character accepted for writing
///                - value -1:          indicates character not accepted
extern int USBD_CDC_ACM_PutChar (uint8_t instance, int ch);

/// \brief Read multiple data bytes received by Communication Device from USB Host
/// \param[in]     instance             instance of CDC class.
/// \param[out]    buf                  buffer that receives data.
/// \param[in]     len                  maximum number of bytes to read.
/// \return                             number of bytes read or execution status.
///                - value >= 0:        number of bytes read
///                - value < 0:         error occurred, -value is execution status as defined with \ref usbStatus
extern int32_t USBD_CDC_ACM_ReadData (uint8_t instance, uint8_t *buf, int32_t len);

/// \brief Write data from Communication Device to USB Host
/// \param[in]     instance             instance of CDC class.
/// \param[in]     buf                  buffer containing data bytes to write.
/// \param[in]     len                  maximum number of bytes to write.
/// \return                             number of bytes accepted for writing or execution status.
///                - value >= 0:        number of bytes accepted for writing
///                - value < 0:         error occurred, -value is execution status as defined with \ref usbStatus
extern int32_t USBD_CDC_ACM_WriteData (uint8_t instance, const uint8_t *buf, int32_t len);

/// \brief Retrieve number of data bytes received by Communication Device from
///        USB Host that are available to read
/// \param[in]     instance             instance of CDC class.
/// \return                             number of bytes available to read.
extern int32_t USBD_CDC_ACM_DataAvailable (uint8_t instance);

/// \brief Send notification of Communication Device status and line states to USB Host
/// \param[in]     instance             instance of CDC class.
/// \param[in]     state                error status and line states:
///                                       - bit 6: bOverRun
///                                       - bit 5: bParity
///                                       - bit 4: bFraming
///                                       - bit 3: bRingSignal
///                                       - bit 2: bBreak
///                                       - bit 1: bTxCarrier (DSR line state)
///                                       - bit 0: bRxCarrier (DCD line state)
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_CDC_ACM_Notify (uint8_t instance, uint16_t state);

/// \brief Clear the active NTB (prepared for sending)
/// \param[in]     instance             Instance of CDC class.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_IN_Initialize (uint8_t instance);


/// \brief Create a new NDP in the NTB (datagrams can be added to it)
/// \param[in]     instance             Instance of CDC class.
/// \param[in]     num_datagrams        Maximum number of datagrams that NDP will contain.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_IN_CreateNDP (uint8_t instance, uint8_t num_datagrams);

/// \brief Add a datagram into the active NDP of the NTB to be sent
/// \param[in]     instance             Instance of CDC class.
/// \param[in]     buf                  Buffer containing data bytes to write.
/// \param[in]     len                  Number of bytes to write.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_IN_WriteDatagram (uint8_t instance, const uint8_t *buf, uint32_t len);

/// \brief Send the active NTB
/// \param[in]     instance             Instance of CDC class.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_IN_Send (uint8_t instance);

/// \brief Check if NTB was sent and new NTB can be prepared
/// \param[in]     instance             Instance of CDC class.
/// \return        value = 1:           NTB was sent.
/// \return        value = 0:           NTB sending is in progress.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_IN_IsSent (uint8_t instance);

/// \brief Check if NTB was received and is available for processing
/// \param[in]     instance             Instance of CDC class.
/// \return        value = 1:           received NTB is available.
/// \return        value = 0:           no received NTB is available.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_OUT_IsReceived (uint8_t instance);

/// \brief Flush the received NTB and release memory for reception of a new NTB
/// \param[in]     instance             Instance of CDC class.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_OUT_Release (uint8_t instance);

/// \brief Process the next NDP in the received NTB
/// \param[in]     instance             Instance of CDC class.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_OUT_ProcessNDP (uint8_t instance);

/// \brief Get size of a datagram from the active NDP of the received NTB
/// \param[in]     instance            Instance of CDC class.
/// \return        Number of bytes available in the datagram.
extern uint32_t USBD_CDC_NCM_NTB_OUT_GetDatagramSize (uint8_t instance);

/// \brief Read a datagram from the active NDP of the received NTB
/// \param[in]     instance             Instance of CDC class.
/// \param[out]    buf                  Buffer that receives read data.
/// \param[in]     max_len              Maximum number of bytes to read.
/// \return        value >= 0:          number of bytes read from the datagram.
/// \return        value <  0:          error code.
extern int32_t USBD_CDC_NCM_NTB_OUT_ReadDatagram (uint8_t instance, uint8_t *buf, uint32_t max_len);

/// \brief Send already prepared NTB (for this option value of define in configuration USBD_CDCn_NCM_RAW_ENABLE has to be 1)
/// \param[in]     instance             Instance of CDC class.
/// \param[in]     buf                  Buffer containing NTB.
/// \param[in]     len                  Size of NTB.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_IN_RawSend (uint8_t instance, const uint8_t *buf, uint32_t len);

/// \brief Get size of the received NTB
/// \param[in]     instance             Instance of CDC class.
/// \return        Number of bytes available in the NTB.
extern uint32_t USBD_CDC_NCM_NTB_OUT_RawGetSize (uint8_t instance);

/// \brief Receive an NDP (for this option value of define in configuration USBD_CDCn_NCM_RAW_ENABLE has to be 1)
/// \param[in]     instance             Instance of CDC class.
/// \param[out]    buf                  Buffer that receives NTB.
/// \param[in]     max_len              Maximum number of bytes that buffer can accept.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_NTB_OUT_RawReceive (uint8_t instance, uint8_t *buf, uint32_t max_len);

/// \brief Report whether or not the physical layer (modem, Ethernet PHY, etc.) link is up to the USB Host
/// \param[in]     instance             Instance of CDC class.
/// \param[in]     status               Connection status:
///                  - value 0 :        Disconnected
///                  - value 1 :        Connected
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_Notify_NetworkConnection (uint8_t instance, uint16_t status);

/// \brief Report a change in upstream or downstream speed of the networking connection to the USB Host
/// \param[in]     instance             Instance of CDC class.
/// \param[in]     us_bitrate           Upstream bitrate.
/// \param[in]     ds_bitrate           Downstream bitrate.
/// \return        value = 0:           success.
/// \return        value < 0:           error code.
extern int32_t USBD_CDC_NCM_Notify_ConnectionSpeedChange (uint8_t instance, uint32_t us_bitrate, uint32_t ds_bitrate);

//  ==== USB Device Human Interface Device Functions ====

#ifdef __DOXYGEN__

// following functions are available for each instance of a HID class.
// generic prefix USBD_HIDn is USBD_HID0 for HID class instance 0.

/// \brief Called during \ref USBD_Initialize to initialize the USB HID class instance
/// \return                             none.
void USBD_HIDn_Initialize (void);

/// \brief Called during \ref USBD_Uninitialize to de-initialize the USB HID class instance
/// \return                             none.
void USBD_HIDn_Uninitialize (void);

/// \brief Prepare HID Report data to send
/// \param[in]     rtype                report type:
///                  - HID_REPORT_INPUT           = input report requested
///                  - HID_REPORT_FEATURE         = feature report requested
/// \param[in]     req                  request type:
///                  - USBD_HID_REQ_EP_CTRL       = control endpoint request
///                  - USBD_HID_REQ_PERIOD_UPDATE = idle period expiration request
///                  - USBD_HID_REQ_EP_INT        = previously sent report on interrupt endpoint request
/// \param[in]     rid                  report ID (0 if only one report exists).
/// \param[out]    buf                  buffer containing report data to send.
/// \return                             number of report data bytes prepared to send or invalid report requested.
///                - value >= 0:        number of report data bytes prepared to send
///                - value = -1:        invalid report requested
int32_t USBD_HIDn_GetReport (uint8_t rtype, uint8_t req, uint8_t rid, uint8_t *buf);

/// \brief Process received HID Report data
/// \param[in]     rtype                report type:
///                  - HID_REPORT_OUTPUT    = output report received
///                  - HID_REPORT_FEATURE   = feature report received
/// \param[in]     req                  request type:
///                  - USBD_HID_REQ_EP_CTRL = report received on control endpoint
///                  - USBD_HID_REQ_EP_INT  = report received on interrupt endpoint
/// \param[in]     rid                  report ID (0 if only one report exists).
/// \param[in]     buf                  buffer that receives report data.
/// \param[in]     len                  length of received report data.
/// \return        true                 received report data processed.
/// \return        false                received report data not processed or request not supported.
bool USBD_HIDn_SetReport (uint8_t rtype, uint8_t req, uint8_t rid, const uint8_t *buf, int32_t len);

#endif // __DOXYGEN

/// \brief Asynchronously prepare HID Report data to send
/// \param[in]     instance             instance of HID class.
/// \param[in]     rid                  report ID.
/// \param[out]    buf                  buffer containing report data to send.
/// \param[in]     len                  number of report data bytes to send.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_HID_GetReportTrigger (uint8_t instance, uint8_t rid, const uint8_t *buf, int32_t len);


#ifdef __DOXYGEN__

//  ==== USB Device Mass Storage Device Functions ====

// following functions are available for each instance of a MSC class.
// generic prefix USBD_MSCn is USBD_MSC0 for MSC class instance 0.

/// \brief Called during \ref USBD_Initialize to initialize the USB MSC class instance
/// \return                             none.
void USBD_MSCn_Initialize (void);

/// \brief Called during \ref USBD_Uninitialize to de-initialize the USB MSC class instance
/// \return                             none.
void USBD_MSCn_Uninitialize (void);

/// \brief Get cache information
/// \param[out]    buffer               cache buffer address.
/// \param[out]    size                 cache buffer size.
/// \return        true                 operation succeeded.
/// \return        false                operation failed.
bool USBD_MSCn_GetCacheInfo (uint32_t *buffer, uint32_t *size);

/// \brief Get media capacity
/// \param[out]    block_count          total number of blocks on media.
/// \param[out]    block_size           media block size.
/// \return        true                 operation succeeded.
/// \return        false                operation failed.
bool USBD_MSCn_GetMediaCapacity (uint32_t *block_count, uint32_t *block_size);

/// \brief Read data from media
/// \param[in]     lba                  logical address of first block to read.
/// \param[in]     cnt                  number of contiguous blocks to read from media.
/// \param[out]    buf                  data buffer for data read from media.
/// \return        true                 read succeeded.
/// \return        false                read failed.
bool USBD_MSCn_Read (uint32_t lba, uint32_t cnt, uint8_t *buf);

/// \brief Write data to media
/// \param[in]     lba                  logical address of first block to write.
/// \param[in]     cnt                  number of contiguous blocks to write to media.
/// \param[out]    buf                  data buffer containing data to write to media.
/// \return        true                 write succeeded.
/// \return        false                write failed.
bool USBD_MSCn_Write (uint32_t lba, uint32_t cnt, const uint8_t *buf);

/// \brief Check media presence and write protect status
/// \return                             media presence and write protected status
///                bit 1:               write protect bit
///                 - value 1:            media is write protected
///                 - value 0:            media is not write protected
///                bit 0:               media presence bit
///                 - value 1:            media is present
///                 - value 0:            media is not present
uint32_t USBD_MSCn_CheckMedia (void);

#endif // __DOXYGEN


//  ==== USB Device Custom Class Functions ====

#ifdef __DOXYGEN__

// following functions are available for each instance of a Custom class.
// generic prefix USBD_CustomClassn is USBD_CustomClass0 for Custom class instance 0.

/// \brief Called during \ref USBD_Initialize to initialize the USB Custom class instance
/// \return                             none.
void USBD_CustomClassn_Initialize (void);

/// \brief Called during \ref USBD_Uninitialize to de-initialize the USB Custom class instance
/// \return                             none.
void USBD_CustomClassn_Uninitialize (void);

/// \brief Custom Class Reset Event handling
/// \return                             none.
void USBD_CustomClassn_EventReset (void);

/// \brief Custom Class Endpoint Start Event handling
/// \param[in]     ep_addr              endpoint address.
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \return                             none.
void USBD_CustomClassn_EventEndpointStart (uint8_t ep_addr);

/// \brief Custom Class Endpoint Stop Event handling
/// \param[in]     ep_addr              endpoint address.
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \return                             none.
void USBD_CustomClassn_EventEndpointStop (uint8_t ep_addr);

/// \brief Callback function called when a SETUP PACKET was received on Control Endpoint 0
/// \param[in]     setup_packet         pointer to received setup packet.
/// \param[out]    buf                  pointer to data buffer used for data stage requested by setup packet.
/// \param[out]    len                  pointer to number of data bytes in data stage requested by setup packet.
/// \return        usbdRequestStatus    enumerator value indicating the function execution status
/// \return        usbdRequestNotProcessed:request was not processed; processing will be done by USB library
/// \return        usbdRequestOK:       request was processed successfully (send Zero-Length Packet if no data stage)
/// \return        usbdRequestStall:    request was processed but is not supported (STALL EP)
usbdRequestStatus USBD_CustomClassn_Endpoint0_SetupPacketReceived (const USB_SETUP_PACKET *setup_packet, uint8_t **buf, uint32_t *len);

/// \brief Callback function called when a SETUP PACKET was processed by USB library
/// \param[in]     setup_packet         pointer to processed setup packet.
/// \return                             none.
void USBD_CustomClassn_Endpoint0_SetupPacketProcessed (const USB_SETUP_PACKET *setup_packet);

/// \brief Callback function called when OUT DATA was received on Control Endpoint 0
/// \param[in]     len                  number of received data bytes.
/// \return        usbdRequestStatus    enumerator value indicating the function execution status
/// \return        usbdRequestNotProcessed:request was not processed; processing will be done by USB library
/// \return        usbdRequestOK:       request was processed successfully (send Zero-Length Packet)
/// \return        usbdRequestStall:    request was processed but is not supported (stall endpoint 0)
/// \return        usbdRequestNAK:      request was processed but the device is busy (return NAK)
usbdRequestStatus USBD_CustomClassn_Endpoint0_OutDataReceived (uint32_t len);

/// \brief Callback function called when IN DATA was sent on Control Endpoint 0
/// \param[in]     len                  number of sent data bytes.
/// \return        usbdRequestStatus    enumerator value indicating the function execution status
/// \return        usbdRequestNotProcessed:request was not processed; processing will be done by USB library
/// \return        usbdRequestOK:       request was processed successfully (return ACK)
/// \return        usbdRequestStall:    request was processed but is not supported (stall endpoint 0)
/// \return        usbdRequestNAK:      request was processed but the device is busy (return NAK)
usbdRequestStatus USBD_CustomClassn_Endpoint0_InDataSent (uint32_t len);

/// \brief Callback function called when DATA was sent or received on Endpoint n
/// \param[in]     event                event on Endpoint:
///                                       - ARM_USBD_EVENT_OUT = data OUT received
///                                       - ARM_USBD_EVENT_IN  = data IN  sent
void USBD_CustomClassn_Endpoint1_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint2_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint3_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint4_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint5_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint6_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint7_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint8_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint9_Event  (uint32_t event);
void USBD_CustomClassn_Endpoint10_Event (uint32_t event);
void USBD_CustomClassn_Endpoint11_Event (uint32_t event);
void USBD_CustomClassn_Endpoint12_Event (uint32_t event);
void USBD_CustomClassn_Endpoint13_Event (uint32_t event);
void USBD_CustomClassn_Endpoint14_Event (uint32_t event);
void USBD_CustomClassn_Endpoint15_Event (uint32_t event);

#endif // __DOXYGEN

/// \brief Start reception on Endpoint
/// \param[in]     device               index of USB Device.
/// \param[in]     ep_addr              endpoint address
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \param[out]    buf                  buffer that receives data.
/// \param[in]     len                  maximum number of bytes to receive.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_EndpointRead (uint8_t device, uint8_t ep_addr, uint8_t *buf, uint32_t len);

/// \brief Get result of read operation on Endpoint
/// \param[in]     device               index of USB Device.
/// \param[in]     ep_addr              endpoint address
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \return                             number of bytes received.
extern uint32_t USBD_EndpointReadGetResult (uint8_t device, uint8_t ep_addr);

/// \brief Start write on Endpoint
/// \param[in]     device               index of USB Device.
/// \param[in]     ep_addr              endpoint address
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \param[out]    buf                  buffer containing data bytes to write.
/// \param[in]     len                  maximum number of bytes to write.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_EndpointWrite (uint8_t device, uint8_t ep_addr, const uint8_t *buf, uint32_t len);

/// \brief Get result of write operation on Endpoint
/// \param[in]     device               index of USB Device.
/// \param[in]     ep_addr              endpoint address
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \return                             number of bytes written.
extern uint32_t USBD_EndpointWriteGetResult (uint8_t device, uint8_t ep_addr);

/// \brief Set/Clear stall on Endpoint
/// \param[in]     device               index of USB Device.
/// \param[in]     ep_addr              endpoint address.
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \param[in]     stall                false = Clear stall, true = Set stall.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_EndpointStall (uint8_t device, uint8_t ep_addr, bool stall);

/// \brief Abort read/write operation on Endpoint
/// \param[in]     device               index of USB Device.
/// \param[in]     ep_addr              endpoint address
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBD_EndpointAbort (uint8_t device, uint8_t ep_addr);


//  ==== USB Host Functions ====

/// \brief Initialize USB Host stack and controller
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_Initialize (uint8_t ctrl);

/// \brief De-initialize USB Host stack and controller
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_Uninitialize (uint8_t ctrl);

/// \brief Get status of USB Device
/// \param[in]     device               index of USB Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_GetDeviceStatus (uint8_t device);


//  ==== USB Host Mass Storage Functions ====

/// \brief Get status of Mass Storage Device
/// \param[in]     instance             instance of MSC Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MSC_GetDeviceStatus (uint8_t instance);

/// \brief Read requested number of blocks from Mass Storage Device
/// \param[in]     instance             instance of MSC Device.
/// \param[in]     lba                  logical block address of first block to read.
/// \param[in]     cnt                  number of contiguous blocks to read.
/// \param[out]    buf                  data buffer in which to read data.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MSC_Read (uint8_t instance, uint32_t lba, uint32_t cnt, uint8_t *buf);

/// \brief Write requested number of blocks to Mass Storage Device
/// \param[in]     instance             instance of MSC Device.
/// \param[in]     lba                  logical address of first block to write.
/// \param[in]     cnt                  number of contiguous blocks to write.
/// \param[in]     buf                  data buffer containing data to write.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MSC_Write (uint8_t instance, uint32_t lba, uint32_t cnt, const uint8_t *buf);

/// \brief Read capacity of Mass Storage Device
/// \param[in]     instance             instance of MSC Device.
/// \param[out]    block_count          pointer to where total number of blocks available will be read.
/// \param[out]    block_size           pointer to where block size will be read.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_MSC_ReadCapacity (uint8_t instance, uint32_t *block_count, uint32_t *block_size);


//  ==== USB Host Human Interface Device Functions ====

/// \brief Get status of Human Interface Device
/// \param[in]     instance             instance of HID Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_HID_GetDeviceStatus (uint8_t instance);

/// \brief Read data received from Human Interface Device
/// \param[in]     instance             instance of HID Device.
/// \param[out]    buf                  buffer that receives data.
/// \param[in]     len                  maximum number of bytes to read.
/// \return                             number of bytes read or execution status.
///                - value >= 0:        number of bytes read
///                - value < 0:         error occurred, -value is execution status as defined with \ref usbStatus
extern int32_t USBH_HID_Read (uint8_t instance, uint8_t *buf, int32_t len);

/// \brief Write data to Human Interface Device
/// \param[in]     instance             instance of HID Device.
/// \param[in]     buf                  data buffer containing data to write.
/// \param[in]     len                  number of data bytes to write.
/// \return                             number of bytes accepted for writing or execution status.
///                - value >= 0:        number of bytes accepted for writing
///                - value < 0:         error occurred, -value is execution status as defined with \ref usbStatus
extern int32_t USBH_HID_Write (uint8_t instance, const uint8_t *buf, int32_t len);

/// \brief Retrieve first pending pressed keyboard key on HID Keyboard
/// \param[in]     instance             instance of HID Device.
/// \return                             value of read character or no character received.
///                - value >= 0:        value of first received unread character
///                - value -1:          indicates no character was received
extern int USBH_HID_GetKeyboardKey (uint8_t instance);

/// Mouse state information.
typedef struct _usbHID_MouseState {
  uint8_t button;                       ///< Current button states
  int16_t x;                            ///< Absolute X position change
  int16_t y;                            ///< Absolute Y position change
} usbHID_MouseState;

/// \brief Retrieve state change since last call of this function
/// \param[in]     instance             instance of HID Device.
/// \param[out]    state                pointer to mouse state \ref usbHID_MouseState structure.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_HID_GetMouseState (uint8_t instance, usbHID_MouseState *state);

/// \brief Callback function called for parsing of the Human Interface Device report descriptor
/// \param[in]     instance             instance index.
/// \param[in]     ptr_hid_report_desc  pointer to HID report descriptor.
/// \return                             none.
extern void USBH_HID_ParseReportDescriptor (uint8_t instance, uint8_t *ptr_hid_report_desc);

/// \brief Callback function called when data is received from the Human Interface Device
/// \param[in]     instance             instance index.
/// \param[in]     len                  length of received data.
/// \return                             none.
extern void USBH_HID_DataReceived (uint8_t instance, uint32_t len);


//  ==== USB Host Communication Device Class (Abstract Control Model) Functions ====

/// \brief Get status of Communication Device Class device
/// \param[in]     instance             instance of CDC Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_CDC_ACM_GetDeviceStatus (uint8_t instance);

/// \brief Send data to Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \param[in]     data                 buffer containing data bytes to send.
/// \param[in]     num                  number of bytes to send.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
extern usbStatus USBH_CDC_ACM_Send (uint8_t instance, const uint8_t *data, uint32_t num);

/// \brief Get result of send data to Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \return                             number of successfully sent data bytes.
extern uint32_t USBH_CDC_ACM_GetTxCount (uint8_t instance);

/// \brief Receive data from Communication Device Class device
/// \param[in]     instance             index of CDC instance
/// \param[out]    data                 buffer that receives data.
/// \param[in]     num                  maximum number of bytes to receive.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
extern usbStatus USBH_CDC_ACM_Receive (uint8_t instance, uint8_t *data, uint32_t num);

/// \brief Get result of receive data from Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \return                             number of successfully received data bytes.
extern uint32_t USBH_CDC_ACM_GetRxCount (uint8_t instance);

/// \brief Change communication settings of Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \param[in]     line_coding          pointer to CDC_LINE_CODING structure.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
extern usbStatus USBH_CDC_ACM_SetLineCoding (uint8_t instance, CDC_LINE_CODING *line_coding);

/// \brief Retrieve communication settings of Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \param[out]    line_coding          pointer to CDC_LINE_CODING structure.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
extern usbStatus USBH_CDC_ACM_GetLineCoding (uint8_t instance, CDC_LINE_CODING *line_coding);

/// \brief Set control line states of Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \param[in]     state                control line settings bitmap.
///                                       - bit 0: DTR state
///                                       - bit 1: RTS state
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
extern usbStatus USBH_CDC_ACM_SetControlLineState (uint8_t instance, uint16_t state);

/// \brief Callback function called when Communication Device Class device
///        modem line or error status changes
/// \param[in]     instance             index of CDC instance.
/// \param[in]     status               error status and line states:
///                                       - bit 6: bOverRun
///                                       - bit 5: bParity
///                                       - bit 4: bFraming
///                                       - bit 3: bRingSignal
///                                       - bit 2: bBreak
///                                       - bit 1: bTxCarrier (DSR line state)
///                                       - bit 0: bRxCarrier (DCD line state)
/// \return                             none.
extern void USBH_CDC_ACM_Notify (uint8_t instance, uint16_t status);

/// \brief Send break on Communication Device Class device
/// \param[in]     instance             index of CDC instance.
/// \param[in]     duration             duration of break (in milliseconds)
///                                       - value 0xFFFF: indefinite
///                                       - value      0: immediate
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
extern usbStatus USBH_CDC_ACM_SendBreak (uint8_t instance, uint16_t duration);


//  ==== USB Host Custom Class Functions ====

/// \brief Get status of Custom Class Device
/// \param[in]     instance             instance of Custom Class Device.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_CustomClass_GetDeviceStatus (uint8_t instance);

/// \brief Callback function called when custom class device is connected and needs
///        to configure resources used by custom class device instance
/// \param[in]     ptr_dev              pointer to device structure.
/// \param[in]     ptr_dev_desc         pointer to device descriptor.
/// \param[in]     ptr_cfg_desc         pointer to configuration descriptor.
/// \return        value <= 127         index of configured custom class device instance.
/// \return        value == 0xFF        configuration failed.
extern uint8_t USBH_CustomClass_Configure (const USBH_DEV *ptr_dev, const USB_DEVICE_DESCRIPTOR *ptr_dev_desc, const USB_CONFIGURATION_DESCRIPTOR *ptr_cfg_desc);

/// \brief Callback function called when custom class device is disconnected and needs
///        to de-configure resources used by custom class device instance
/// \param[in]     instance             index of custom class device instance.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_CustomClass_Unconfigure (uint8_t instance);

/// \brief Callback function called when custom class device is connected and needs
///        to initialize custom class device instance
/// \param[in]     instance             index of custom class device instance.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_CustomClass_Initialize (uint8_t instance);

/// \brief Callback function called when custom class device is disconnected and needs
///        to de-initialize custom class device instance
/// \param[in]     instance             index of custom class device instance.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_CustomClass_Uninitialize (uint8_t instance);

/// \brief Create Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     dev_addr             device address.
/// \param[in]     dev_speed            device speed.
/// \param[in]     hub_addr             hub address.
/// \param[in]     hub_port             hub port.
/// \param[in]     ep_addr              endpoint address
///                 - ep_addr.0..3:       address
///                 - ep_addr.7:          direction
/// \param[in]     ep_type              endpoint type.
/// \param[in]     ep_max_packet_size   endpoint maximum packet size.
/// \param[in]     ep_interval          endpoint polling interval.
/// \return                             pointer to created pipe or pipe creation failed
///                - value > 0:         pointer to created pipe
///                - value 0:           pipe creation failed
extern USBH_PIPE *USBH_PipeCreate (uint8_t ctrl, uint8_t dev_addr, uint8_t dev_speed, uint8_t hub_addr, uint8_t hub_port, uint8_t ep_addr, uint8_t ep_type, uint16_t ep_max_packet_size, uint8_t ep_interval);

/// \brief Modify Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \param[in]     dev_addr             device address.
/// \param[in]     dev_speed            device speed.
/// \param[in]     hub_addr             hub address.
/// \param[in]     hub_port             hub port.
/// \param[in]     ep_max_packet_size   endpoint maximum packet size.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_PipeModify (uint8_t ctrl, USBH_PIPE *ptr_pipe, uint8_t dev_addr, uint8_t dev_speed, uint8_t hub_addr, uint8_t hub_port, uint16_t ep_max_packet_size);

/// \brief Delete Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_PipeDelete (uint8_t ctrl, USBH_PIPE *ptr_pipe);

/// \brief Reset Pipe (reset data toggle)
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_PipeReset (uint8_t ctrl, USBH_PIPE *ptr_pipe);

/// \brief Receive data on Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \param[out]    buf                  buffer that receives data.
/// \param[in]     len                  maximum number of bytes to receive.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_PipeReceive (uint8_t ctrl, USBH_PIPE *ptr_pipe, uint8_t *buf, uint32_t len);

/// \brief Get result of receive data operation on Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \return                             number of successfully received data bytes.
extern uint32_t USBH_PipeReceiveGetResult (uint8_t ctrl, const USBH_PIPE *ptr_pipe);

/// \brief Send data on Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \param[in]     buf                  buffer containing data bytes to send.
/// \param[in]     len                  maximum number of bytes to send.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_PipeSend (uint8_t ctrl, USBH_PIPE *ptr_pipe, const uint8_t *buf, uint32_t len);

/// \brief Get result of send data operation on Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \return                             number of successfully sent data bytes.
extern uint32_t USBH_PipeSendGetResult (uint8_t ctrl, const USBH_PIPE *ptr_pipe);

/// \brief Abort send/receive operation on Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     ptr_pipe             pointer to pipe.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_PipeAbort (uint8_t ctrl, const USBH_PIPE *ptr_pipe);

/// \brief Receive data on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[out]    buf                  buffer that receives data.
/// \param[in]     len                  maximum number of bytes to receive.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DefaultPipeReceive (uint8_t ctrl, uint8_t *buf, uint32_t len);

/// \brief Get result of receive data operation on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             number of successfully received data bytes.
extern uint32_t USBH_DefaultPipeReceiveGetResult (uint8_t ctrl);

/// \brief Send Setup Packet on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     setup_packet         pointer to setup packet.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DefaultPipeSendSetup (uint8_t ctrl, const USB_SETUP_PACKET *setup_packet);

/// \brief Send data on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     buf                  buffer containing data bytes to send.
/// \param[in]     len                  maximum number of bytes to send.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DefaultPipeSend (uint8_t ctrl, const uint8_t *buf, uint32_t len);

/// \brief Get result of send data operation on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             number of successfully sent data bytes.
extern uint32_t USBH_DefaultPipeSendGetResult (uint8_t ctrl);

/// \brief Abort send/receive operation on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DefaultPipeAbort (uint8_t ctrl);

/// \brief Do a Control Transfer on Default Pipe
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     setup_packet         pointer to setup packet.
/// \param[in,out] data                 buffer containing data bytes to send or where data should be received in data stage of Control Transfer.
/// \param[in]     len                  number of bytes to send or receive in data stage of Control Transfer.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_ControlTransfer (uint8_t ctrl, const USB_SETUP_PACKET *setup_packet, uint8_t *data, uint32_t len);

/// \brief Standard Device Request on Default Pipe - GET_STATUS
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     recipient            recipient.
/// \param[in]     index                interface or endpoint index.
/// \param[out]    ptr_stat_dat         pointer to where status data should be received.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_GetStatus (uint8_t ctrl, uint8_t recipient, uint8_t index, uint8_t *ptr_stat_dat);

/// \brief Standard Device Request on Default Pipe - CLEAR_FEATURE
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     recipient            recipient.
/// \param[in]     index                interface or endpoint index.
/// \param[in]     feature_selector     feature selector.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_ClearFeature (uint8_t ctrl, uint8_t recipient, uint8_t index, uint8_t feature_selector);

/// \brief Standard Device Request on Default Pipe - SET_FEATURE
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     recipient            recipient.
/// \param[in]     index                interface or endpoint index.
/// \param[in]     feature_selector     feature selector.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_SetFeature (uint8_t ctrl, uint8_t recipient, uint8_t index, uint8_t feature_selector);

/// \brief Standard Device Request on Default Pipe - SET_ADDRESS
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     device_address       device address.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_SetAddress (uint8_t ctrl, uint8_t device_address);

/// \brief Standard Device Request on Default Pipe - GET_DESCRIPTOR
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     recipient            recipient.
/// \param[in]     descriptor_type      descriptor type.
/// \param[in]     descriptor_index     descriptor index.
/// \param[in]     language_id          language ID.
/// \param[out]    descriptor_data      pointer to where descriptor data will be read.
/// \param[in]     descriptor_length    descriptor length.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_GetDescriptor (uint8_t ctrl, uint8_t recipient, uint8_t descriptor_type, uint8_t descriptor_index, uint8_t language_id, uint8_t *descriptor_data, uint16_t descriptor_length);

/// \brief Standard Device Request on Default Pipe - SET_DESCRIPTOR
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     recipient            recipient.
/// \param[in]     descriptor_type      descriptor type.
/// \param[in]     descriptor_index     descriptor index.
/// \param[in]     language_id          language ID.
/// \param[in]     descriptor_data      pointer to descriptor data to be written.
/// \param[in]     descriptor_length    descriptor length.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_SetDescriptor (uint8_t ctrl, uint8_t recipient, uint8_t descriptor_type, uint8_t descriptor_index, uint8_t language_id, uint8_t *descriptor_data, uint16_t descriptor_length);

/// \brief Standard Device Request on Default Pipe - GET_CONFIGURATION
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[out]    ptr_configuration    pointer to where configuration will be read.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_GetConfiguration (uint8_t ctrl, uint8_t *ptr_configuration);

/// \brief Standard Device Request on Default Pipe - SET_CONFIGURATION
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     configuration        configuration.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_SetConfiguration (uint8_t ctrl, uint8_t configuration);

/// \brief Standard Device Request on Default Pipe - GET_INTERFACE
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     index                interface index.
/// \param[out]    ptr_alternate        pointer to where alternate setting data will be read.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_GetInterface (uint8_t ctrl, uint8_t index, uint8_t *ptr_alternate);

/// \brief Standard Device Request on Default Pipe - SET_INTERFACE
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     index                interface index.
/// \param[in]     alternate            alternate setting.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_SetInterface (uint8_t ctrl, uint8_t index, uint8_t alternate);

/// \brief Standard Device Request on Default Pipe - SYNCH_FRAME
/// \param[in]     ctrl                 index of USB Host controller.
/// \param[in]     index                interface or endpoint index.
/// \param[out]    ptr_frame_number     pointer to where frame number data will be read.
/// \return                             status code that indicates the execution status of the function as defined with \ref usbStatus.
extern usbStatus USBH_DeviceRequest_SynchFrame (uint8_t ctrl, uint8_t index, uint8_t *ptr_frame_number);

#ifdef __cplusplus
}
#endif

#endif
