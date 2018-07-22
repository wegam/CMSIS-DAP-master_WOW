/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        27. November 2015
 * $Revision:    V1.1
 *
 * Driver:       Driver_USARTn
 * Project:      USART Driver for Prolific PL2303 USB to serial RS232 adapter
 * Settings:     USART_PL2303_DRV_NUM sets the driver number
 *               (default number value is 9)
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 1.00
 *    - Initial release
 */

#include <stdint.h>

#include "cmsis_os.h"

#include "rl_usb.h"
#include "usb_cdc.h"

#include "Driver_USART.h"

/************************** Constant and Macro Definitions ********************/

// Driver number used for Driver Control Block name
#ifndef USART_PL2303_DRV_NUM
#define USART_PL2303_DRV_NUM            9
#endif

#define USART_PL2303_DRV_(n)            Driver_USART##n
#define USART_PL2303_DRV(n)             USART_PL2303_DRV_(n)

// Send, Receive and Status thread settings
#ifndef USBH_PL2303_SEND_THREAD_STACK_SIZE
#define USBH_PL2303_SEND_THREAD_STACK_SIZE     512
#endif
#ifndef USBH_PL2303_SEND_THREAD_PRIORITY
#define USBH_PL2303_SEND_THREAD_PRIORITY       osPriorityNormal
#endif
#ifndef USBH_PL2303_RECEIVE_THREAD_STACK_SIZE
#define USBH_PL2303_RECEIVE_THREAD_STACK_SIZE  512
#endif
#ifndef USBH_PL2303_RECEIVE_THREAD_PRIORITY
#define USBH_PL2303_RECEIVE_THREAD_PRIORITY    osPriorityNormal
#endif
#ifndef USBH_PL2303_STATUS_THREAD_STACK_SIZE
#define USBH_PL2303_STATUS_THREAD_STACK_SIZE   512
#endif
#ifndef USBH_PL2303_STATUS_THREAD_PRIORITY
#define USBH_PL2303_STATUS_THREAD_PRIORITY     osPriorityNormal
#endif

// Interface class, subclass and protocol of the device that is supported
#define CUSTOM_CLASS_IF_CLASS           USB_DEVICE_CLASS_VENDOR_SPECIFIC
#define CUSTOM_CLASS_IF_SUBCLASS        0
#define CUSTOM_CLASS_IF_PROTOCOL        0

// Indexes of Pipes for PL2303 device
#define PL2303_STATUS_PIPE_INDEX        0
#define PL2303_SEND_PIPE_INDEX          1
#define PL2303_RECEIVE_PIPE_INDEX       2

/************************** Variable and Memory Definitions *******************/

extern uint8_t    USBH_CustomClass_Ctrl;       // Controller number used for USB transfers
extern USBH_PIPE *USBH_CustomClass_Pipes[];    // Pointers to Pipes

static osThreadId usbh_receive_thread_id = 0;  // Receive (Bulk In) thread ID
static osThreadId usbh_send_thread_id    = 0;  // Send (Bulk Out) thread ID
static osThreadId usbh_status_thread_id  = 0;  // Receive status (Interrupt In) thread ID

static ARM_USART_SignalEvent_t usart_cb_event; // Pointer to USART Signal Function

static bool       usart_control_tx;            // USART Tx enable
static bool       usart_control_rx;            // USART Rx enable
static bool       usart_flow_control_rts;      // USART flow control on RTS line enable
static bool       usart_flow_control_cts;      // USART flow control on CTS line enable
static bool       usart_send_busy;             // Send in progress
static uint8_t   *usart_send_data;             // Pointer to memory containing data to send
static uint32_t   usart_send_num;              // Number of data bytes to send
static bool       usart_receive_busy;          // Reception in progress
static uint8_t   *usart_receive_data;          // Pointer to memory for data reception
static uint32_t   usart_receive_num;           // Number of data bytes to receive
static uint16_t   usart_ctrl_lines;            // Modem lines control
static uint16_t   usart_status;                // Modem lines and error status
static CDC_LINE_CODING usart_line_coding =  { 9600, 0, 0 , 8 }; // Initial line coding

/************************** Internal Function Prototypes **********************/

static void ARM_USART_Sent     (void);
static void ARM_USART_Received (void);

/************************** Internal Functions ********************************/

/*------------------------- Internal Threads ---------------------------------*/

/// \brief User thread for handling data send (to Bulk Out endpoint)
/// \param[in]     arg                  unused.
void USBH_PL2303_Send_Thread (void const *arg) {
  usbStatus status;

  // Send Data on Bulk Out Pipe in thread
  status = USBH_PipeSend (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[PL2303_SEND_PIPE_INDEX], usart_send_data, usart_send_num);
  usart_send_busy  = false;

  if (status == usbOK) ARM_USART_Sent();
}
osThreadDef(USBH_PL2303_Send_Thread, USBH_PL2303_SEND_THREAD_PRIORITY, 1, USBH_PL2303_SEND_THREAD_STACK_SIZE);

/// \brief User thread for handling data reception (from Bulk In endpoint)
/// \param[in]     arg                  unused.
void USBH_PL2303_Receive_Thread (void const *arg) {
  usbStatus status;

  // Receive Data on Bulk In Pipe in thread
  do {
    status = USBH_PipeReceive (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[PL2303_RECEIVE_PIPE_INDEX], usart_receive_data, usart_receive_num);
    if (status == usbTransferError) {
      usart_receive_busy = false;
      osThreadTerminate (osThreadGetId());
    }
  } while (status == usbTimeout);
  usart_receive_busy = false;

  if (status == usbOK) ARM_USART_Received();
}
osThreadDef(USBH_PL2303_Receive_Thread, USBH_PL2303_RECEIVE_THREAD_PRIORITY, 1, USBH_PL2303_RECEIVE_THREAD_STACK_SIZE);

/// \brief User thread for handling modem status and error feedback from PL2303
///        device (from Interrupt In endpoint)
/// \param[in]     arg              unused.
void USBH_PL2303_Status_Thread (void const *arg) {
  usbStatus status;
  uint8_t   buf[16];

  if (USBH_CustomClass_Pipes[PL2303_STATUS_PIPE_INDEX]->wMaxPacketSize > 16) return;

  for (;;) {
    status = USBH_PipeReceive (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[PL2303_STATUS_PIPE_INDEX], buf, USBH_CustomClass_Pipes[PL2303_STATUS_PIPE_INDEX]->wMaxPacketSize);
    if (status == usbOK) {
      // Data has been received on Interrupt In Pipe
      if ((buf[0] == 0xA1)                          &&
          (buf[1] == CDC_NOTIFICATION_SERIAL_STATE) &&
          (buf[2] == 0x00)                          &&
          (buf[3] == 0x00)                          &&
          (buf[4] == 0x00)                          &&
          (buf[5] == 0x00)                          &&
          (buf[6] == 0x02)                          &&
          (buf[7] == 0x00)) {
        // If this is Notification store new modem line and error status
        usart_status = ((uint16_t)buf[9] << 8) | buf[8];
      }
    }
    if (status == usbTransferError) {
      osThreadTerminate (osThreadGetId());
    }
  }
}
osThreadDef(USBH_PL2303_Status_Thread, USBH_PL2303_STATUS_THREAD_PRIORITY, 1, USBH_PL2303_STATUS_THREAD_STACK_SIZE);

/***-------------- PL2303 Specific Functions -------------------------------***/

/// \brief Get result of send data to PL2303 device
/// \return                             number of successfully sent data bytes.
uint32_t USBH_PL2303_GetTxCount (void) {
  return (USBH_PipeSendGetResult (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[PL2303_SEND_PIPE_INDEX]));
}

/// \brief Get result of receive data from PL2303 device
/// \return                             number of successfully received data bytes.
uint32_t USBH_PL2303_GetRxCount (void) {
  return (USBH_PipeSendGetResult (USBH_CustomClass_Ctrl, USBH_CustomClass_Pipes[PL2303_RECEIVE_PIPE_INDEX]));
}
/// \brief Change communication settings of PL2303 device
/// \param[in]     line_coding          pointer to CDC_LINE_CODING structure.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_PL2303_SetLineCoding (CDC_LINE_CODING *line_coding) {
  USB_SETUP_PACKET setup_packet;

  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.bmRequestType.Type     = USB_REQUEST_CLASS;
  setup_packet.bmRequestType.Recipient= USB_REQUEST_TO_INTERFACE;
  setup_packet.bRequest               = CDC_SET_LINE_CODING;
  setup_packet.wValue                 = U16_LE(0);
  setup_packet.wIndex                 = U16_LE(0);
  setup_packet.wLength                = U16_LE(sizeof(CDC_LINE_CODING));

  return (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, (uint8_t *)line_coding, sizeof(CDC_LINE_CODING)));
}

/// \brief Retrieve communication settings of PL2303 device
/// \param[out]    line_coding          pointer to CDC_LINE_CODING structure.
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_PL2303_GetLineCoding (CDC_LINE_CODING *line_coding) {

  *line_coding = usart_line_coding;

  return usbOK;
}

/// \brief Set control line states of PL2303 device
/// \param[in]     state                control line settings bitmap.
///                                       - bit 0: DTR state
///                                       - bit 1: RTS state
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_PL2303_SetControlLineState (uint16_t state) {
  USB_SETUP_PACKET setup_packet;

  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.bmRequestType.Type     = USB_REQUEST_CLASS;
  setup_packet.bmRequestType.Recipient= USB_REQUEST_TO_INTERFACE;
  setup_packet.bRequest               = CDC_SET_CONTROL_LINE_STATE;
  setup_packet.wValue                 = U16_LE(state);
  setup_packet.wIndex                 = U16_LE(0);
  setup_packet.wLength                = U16_LE(0);

  return (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, NULL, 0));
}

/// \brief Get PL2303 device modem line and error status
/// \return                             error status and line states:
///                                       - bit 6: bOverRun
///                                       - bit 5: bParity
///                                       - bit 4: bFraming
///                                       - bit 3: bRingSignal
///                                       - bit 2: bBreak
///                                       - bit 1: bTxCarrier (DSR line state)
///                                       - bit 0: bRxCarrier (DCD line state)
uint16_t USBH_PL2303_GetStatus (void) {
  return usart_status;
}

/// \brief Send break on PL2303 device
/// \param[in]     duration             duration of break (in milliseconds)
///                                       - value 0xFFFF: indefinite
///                                       - value      0: immediate
/// \return                             status code that indicates the execution status of the function as defined with usbStatus.
usbStatus USBH_PL2303_SendBreak (uint16_t duration) {
  USB_SETUP_PACKET setup_packet;

  setup_packet.bmRequestType.Dir      = USB_REQUEST_HOST_TO_DEVICE;
  setup_packet.bmRequestType.Type     = USB_REQUEST_CLASS;
  setup_packet.bmRequestType.Recipient= USB_REQUEST_TO_INTERFACE;
  setup_packet.bRequest               = CDC_SEND_BREAK;
  setup_packet.wValue                 = U16_LE(duration);
  setup_packet.wIndex                 = U16_LE(0);
  setup_packet.wLength                = U16_LE(0);

  return (USBH_ControlTransfer (USBH_CustomClass_Ctrl, &setup_packet, NULL, 0));
}

/************************** USART Driver **************************************/

#define ARM_USART_DRV_VERSION           ARM_DRIVER_VERSION_MAJOR_MINOR(1,00)

// Driver Version
static const ARM_DRIVER_VERSION         usart_driver_version = { ARM_USART_API_VERSION, ARM_USART_DRV_VERSION };

// USB to serial RS232 adapter Capabilities
static const ARM_USART_CAPABILITIES     usart_capabilities = {
  1,                                    ///< supports UART (Asynchronous) mode
  0,                                    ///< supports Synchronous Master mode
  0,                                    ///< supports Synchronous Slave mode
  0,                                    ///< supports UART Single-wire mode
  0,                                    ///< supports UART IrDA mode
  0,                                    ///< supports UART Smart Card mode
  0,                                    ///< Smart Card Clock generator available
  1,                                    ///< RTS Flow Control available
  1,                                    ///< CTS Flow Control available
  0,                                    ///< Transmit completed event: ARM_USART_EVENT_TX_COMPLETE
  0,                                    ///< Signal receive character timeout event: ARM_USART_EVENT_RX_TIMEOUT
  1,                                    ///< RTS Line: 0=not available, 1=available
  1,                                    ///< CTS Line: 0=not available, 1=available
  1,                                    ///< DTR Line: 0=not available, 1=available
  1,                                    ///< DSR Line: 0=not available, 1=available
  1,                                    ///< DCD Line: 0=not available, 1=available
  1,                                    ///< RI Line: 0=not available, 1=available
  0,                                    ///< Signal CTS change event: ARM_USART_EVENT_CTS
  0,                                    ///< Signal DSR change event: ARM_USART_EVENT_DSR
  0,                                    ///< Signal DCD change event: ARM_USART_EVENT_DCD
  0                                     ///< Signal RI change event: ARM_USART_EVENT_RI
};

/// \fn          ARM_DRIVER_VERSION ARM_USART_GetVersion (void)
/// \brief       Get driver version.
/// \return      ARM_DRIVER_VERSION
static ARM_DRIVER_VERSION ARM_USART_GetVersion (void) {
  return usart_driver_version;
}

/// \fn          ARM_USART_CAPABILITIES ARM_USART_GetCapabilities (void)
/// \brief       Get driver capabilities
/// \return      ARM_USART_CAPABILITIES
static ARM_USART_CAPABILITIES ARM_USART_GetCapabilities (void) {
  return usart_capabilities;
}

/// \fn          int32_t ARM_USART_Initialize (ARM_USART_SignalEvent_t cb_event)
/// \brief       Initialize USART Interface.
/// \param[in]   cb_event  Pointer to ARM_USART_SignalEvent
/// \return      execution status
static int32_t ARM_USART_Initialize (ARM_USART_SignalEvent_t cb_event) {
  usart_cb_event = cb_event;

  return ARM_DRIVER_OK;
}

/// \fn          int32_t ARM_USART_Uninitialize (void)
/// \brief       De-initialize USART Interface.
/// \return      execution status
static int32_t ARM_USART_Uninitialize (void) {
  return ARM_DRIVER_OK;
}

/// \fn          int32_t ARM_USART_PowerControl (ARM_POWER_STATE state)
/// \brief       Control USART Interface Power.
/// \param[in]   state  Power state
/// \return      execution status
static int32_t ARM_USART_PowerControl (ARM_POWER_STATE state) {
  switch (state) {
    case ARM_POWER_OFF:
      if (usbh_status_thread_id) {
        if (osThreadTerminate(usbh_status_thread_id) != osOK)
          return ARM_DRIVER_ERROR;
        usbh_status_thread_id = 0;
      }
      break;
    case ARM_POWER_FULL:
      if (USBH_CustomClass_GetDeviceStatus (0) != usbOK)    // If device is not connected or not enumerated
        return ARM_DRIVER_ERROR;

      // Start Interrupt In Pipe handling thread
      usbh_status_thread_id = osThreadCreate (osThread(USBH_PL2303_Status_Thread), NULL);
      if (!usbh_status_thread_id)
        return ARM_DRIVER_ERROR;
      break;

    default: return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/// \fn          int32_t ARM_USART_Send (const void *data, uint32_t num)
/// \brief       Start sending data to USART transmitter.
/// \param[in]   data  Pointer to buffer with data to send to USART transmitter
/// \param[in]   num   Number of data items to send
/// \return      execution status
static int32_t ARM_USART_Send (const void *data, uint32_t num) {

  if (!usart_control_tx) return ARM_DRIVER_ERROR;  // Tx disabled

  if (usart_send_busy) return ARM_DRIVER_ERROR_BUSY;
  usart_send_busy = true;

  usart_send_data = (uint8_t *)data;
  usart_send_num  = num;

  // Start send thread
  usbh_send_thread_id = osThreadCreate (osThread(USBH_PL2303_Send_Thread), NULL);
  if (!usbh_send_thread_id) {
    usart_send_busy = false;
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

/// \fn          void ARM_USART_Sent (void)
/// \brief       All data was sent on USART transmitter.
static void ARM_USART_Sent (void) {

  if (usart_cb_event) usart_cb_event (ARM_USART_EVENT_SEND_COMPLETE);
}

/// \fn          int32_t ARM_USART_Receive (void *data, uint32_t num)
/// \brief       Start receiving data from USART receiver.
/// \param[out]  data  Pointer to buffer for data to receive from USART receiver
/// \param[in]   num   Number of data items to receive
/// \return      execution status
static int32_t ARM_USART_Receive (void *data, uint32_t num) {

  if (!usart_control_rx) return ARM_DRIVER_ERROR;  // Rx disabled

  if (usart_receive_busy) return ARM_DRIVER_ERROR_BUSY;
  usart_receive_busy = true;

  usart_receive_data = data;
  usart_receive_num  = num;

  // Start reception thread
  usbh_receive_thread_id = osThreadCreate (osThread(USBH_PL2303_Receive_Thread), NULL);
  if (!usbh_receive_thread_id) {
    usart_receive_busy  = false;
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}

/// \fn          void ARM_USART_Received (void)
/// \brief       All data was received on USART receiver.
static void ARM_USART_Received (void) {

  if (usart_cb_event) usart_cb_event (ARM_USART_EVENT_RECEIVE_COMPLETE);
}

/// \fn          int32_t ARM_USART_Transfer (const void *data_out,
///                                                void *data_in,
///                                          uint32_t    num)
/// \brief       Start sending/receiving data to/from USART transmitter/receiver.
/// \param[in]   data_out  Pointer to buffer with data to send to USART transmitter
/// \param[out]  data_in   Pointer to buffer for data to receive from USART receiver
/// \param[in]   num       Number of data items to transfer
/// \return      execution status
static int32_t ARM_USART_Transfer (const void *data_out, void *data_in, uint32_t num) {
  // Not supported in asynchronous mode
  return ARM_DRIVER_ERROR;
}

/// \fn          uint32_t ARM_USART_GetTxCount (void)
/// \brief       Get transmitted data count.
/// \return      number of data items transmitted
static uint32_t ARM_USART_GetTxCount (void) {
  return (USBH_PL2303_GetTxCount());
}

/// \fn          uint32_t ARM_USART_GetRxCount (void)
/// \brief       Get received data count.
/// \return      number of data items received
static uint32_t ARM_USART_GetRxCount (void) {
  return (USBH_PL2303_GetRxCount());
}

/// \fn          int32_t ARM_USART_Control (uint32_t control, uint32_t arg)
/// \brief       Control USART Interface.
/// \param[in]   control  Operation
/// \param[in]   arg      Argument of operation (optional)
/// \return      common execution status and driver specific usart_execution status
static int32_t ARM_USART_Control (uint32_t control, uint32_t arg) {
  CDC_LINE_CODING  line_coding;

  line_coding = usart_line_coding;

  switch (control & ARM_USART_CONTROL_Msk) {
    case ARM_USART_MODE_ASYNCHRONOUS:
      break;

    case ARM_USART_CONTROL_TX:                // Control Tx
      if (arg) usart_control_tx = true;       // Tx enabled
      else     usart_control_tx = false;      // Tx disable
      return ARM_DRIVER_OK;

    case ARM_USART_CONTROL_RX:                // Control Rx
      if (arg) usart_control_rx = true;       // Rx enabled
      else     usart_control_rx = false;      // Rx disable
      return ARM_DRIVER_OK;

    case ARM_USART_CONTROL_BREAK:             // Control break
      if (arg) {                              // Break enabled
        if (USBH_PL2303_SendBreak (0xFFFF)) return ARM_DRIVER_ERROR;
      } else {                                // Break disable
        if (USBH_PL2303_SendBreak (0))      return ARM_DRIVER_ERROR;
      }
      return ARM_DRIVER_OK;

    case ARM_USART_ABORT_SEND:                // Abort send
      if (usbh_send_thread_id) {
        if (osThreadTerminate(usbh_send_thread_id) != osOK) return ARM_DRIVER_ERROR;
        usbh_send_thread_id = 0;
      }
      return ARM_DRIVER_OK;

    case ARM_USART_ABORT_RECEIVE:             // Abort receive
      if (usbh_receive_thread_id) {
        if (osThreadTerminate(usbh_receive_thread_id) != osOK) return ARM_DRIVER_ERROR;
        usbh_receive_thread_id = 0;
      }
      return ARM_DRIVER_OK;

//  case ARM_USART_MODE_SYNCHRONOUS_MASTER:
//  case ARM_USART_MODE_SYNCHRONOUS_SLAVE:
//  case ARM_USART_MODE_SINGLE_WIRE:
//  case ARM_USART_MODE_IRDA:
//  case ARM_USART_MODE_SMART_CARD:
//  case ARM_USART_SET_DEFAULT_TX_VALUE:      // Default TX value
//  case ARM_USART_SET_IRDA_PULSE:            // IrDA pulse
//  case ARM_USART_SET_SMART_CARD_GUARD_TIME: // SmartCard guard time
//  case ARM_USART_SET_SMART_CARD_CLOCK:      // SmartCard guard time
//  case ARM_USART_CONTROL_SMART_CARD_NACK:   // SmartCard NACK
//  case ARM_USART_ABORT_TRANSFER:            // Abort transfer

    default:                                  // Undefined command
      return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  switch (control & ARM_USART_DATA_BITS_Msk) {// USART Data bits
    case ARM_USART_DATA_BITS_5:         line_coding.bDataBits   =  5; break;
    case ARM_USART_DATA_BITS_6:         line_coding.bDataBits   =  6; break;
    case ARM_USART_DATA_BITS_7:         line_coding.bDataBits   =  7; break;
    case ARM_USART_DATA_BITS_8:         line_coding.bDataBits   =  8; break;
    default:                            return ARM_USART_ERROR_DATA_BITS;
  }

  switch (control & ARM_USART_PARITY_Msk) {   // USART Parity
    case ARM_USART_PARITY_NONE:         line_coding.bParityType =  0; break;
    case ARM_USART_PARITY_ODD:          line_coding.bParityType =  1; break;
    case ARM_USART_PARITY_EVEN:         line_coding.bParityType =  2; break;
    default:                            return ARM_USART_ERROR_PARITY;
  }

  switch (control & ARM_USART_STOP_BITS_Msk) {// USART Stop bits
    case ARM_USART_STOP_BITS_1:         line_coding.bCharFormat =  0; break;
    case ARM_USART_STOP_BITS_1_5:       line_coding.bCharFormat =  1; break;
    case ARM_USART_STOP_BITS_2:         line_coding.bCharFormat =  2; break;
    default:                            return ARM_USART_ERROR_STOP_BITS;
  }

  switch (control & ARM_USART_FLOW_CONTROL_Msk) { // USART Flow control
    case ARM_USART_FLOW_CONTROL_NONE:
      usart_flow_control_rts = false;
      usart_flow_control_cts = false;
      break;
    case ARM_USART_FLOW_CONTROL_RTS:
      usart_flow_control_rts = true;
      break;
    case ARM_USART_FLOW_CONTROL_CTS:
      usart_flow_control_cts = true;
      break;
    case ARM_USART_FLOW_CONTROL_RTS_CTS:
      usart_flow_control_rts = true;
      usart_flow_control_cts = true;
      break;
    default:                            return ARM_USART_ERROR_FLOW_CONTROL;
  }

  line_coding.dwDTERate = arg;          // USART Baudrate

  if (USBH_PL2303_SetLineCoding (&line_coding)) return ARM_DRIVER_ERROR;

  usart_line_coding = line_coding;

  return ARM_DRIVER_OK;
}

/// \fn          ARM_USART_STATUS ARM_USART_GetStatus (void)
/// \brief       Get USART status.
/// \return      USART status ARM_USART_STATUS
static ARM_USART_STATUS ARM_USART_GetStatus (void) {
  ARM_USART_STATUS status = {0};

  status.tx_busy          =  usart_send_busy;        // Transmitter busy flag
  status.rx_busy          =  usart_receive_busy;     // Receiver busy flag
  status.tx_underflow     =  0;                      // Transmit data underflow detected (cleared on start of next send operation)
  status.rx_overflow      = (usart_status >> 6) & 1; // Receive data overflow detected (cleared on start of next receive operation)
  status.rx_break         = (usart_status >> 2) & 1; // Break detected on receive (cleared on start of next receive operation)
  status.rx_framing_error = (usart_status >> 4) & 1; // Framing error detected on receive (cleared on start of next receive operation)
  status.rx_parity_error  = (usart_status >> 5) & 1; // Parity error detected on receive (cleared on start of next receive operation)

  return status;
}

/// \fn          int32_t ARM_USART_SetModemControl (ARM_USART_MODEM_CONTROL control)
/// \brief       Set USART Modem Control line state.
/// \param[in]   control  ARM_USART_MODEM_CONTROL
/// \return      execution status
static int32_t ARM_USART_SetModemControl (ARM_USART_MODEM_CONTROL control) {
  uint16_t  ctrl_lines;

  ctrl_lines = usart_ctrl_lines;

  if (usart_flow_control_rts) {         // If flow control on RTS line enabled
    if (control == ARM_USART_RTS_CLEAR) // Deactivate RTS
      ctrl_lines &= ~(1 << 1);
    if (control == ARM_USART_RTS_SET)   // Activate RTS
      ctrl_lines |=  (1 << 1);
  }
  if (control == ARM_USART_DTR_CLEAR)   // Deactivate DTR
    ctrl_lines &= ~(1 << 0);
  if (control == ARM_USART_DTR_SET)     // Activate DTR
    ctrl_lines |=  (1 << 0);

  if (USBH_PL2303_SetControlLineState (ctrl_lines) != usbOK) return ARM_DRIVER_ERROR;

  usart_ctrl_lines = ctrl_lines;

  return ARM_DRIVER_OK;
}

/// \fn          ARM_USART_MODEM_STATUS ARM_USART_GetModemStatus (void)
/// \brief       Get USART Modem Status lines state.
/// \return      modem status ARM_USART_MODEM_STATUS
static ARM_USART_MODEM_STATUS ARM_USART_GetModemStatus (void) {
  ARM_USART_MODEM_STATUS modem_status = {0};

  modem_status.cts =  usart_flow_control_cts;  // CTS state: 1=Active, 0=Inactive
  modem_status.dsr = (usart_status >> 1) & 1;  // DSR state: 1=Active, 0=Inactive
  modem_status.dcd = (usart_status >> 0) & 1;  // DCD state: 1=Active, 0=Inactive
  modem_status.ri  = (usart_status >> 3) & 1;  // RI  state: 1=Active, 0=Inactive

  return modem_status;
}

// USB to serial RS232 adapter Driver Control Block
ARM_DRIVER_USART USART_PL2303_DRV(USART_PL2303_DRV_NUM) = {
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART_Initialize,
    ARM_USART_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART_Send,
    ARM_USART_Receive,
    ARM_USART_Transfer,
    ARM_USART_GetTxCount,
    ARM_USART_GetRxCount,
    ARM_USART_Control,
    ARM_USART_GetStatus,
    ARM_USART_SetModemControl,
    ARM_USART_GetModemStatus
};
