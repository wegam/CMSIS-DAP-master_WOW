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
 * Driver:       Driver_USARTn..Driver_USARTm
 * Project:      USART Driver for USB Host CDC ACM compliant device
 * Settings:     USART_CDC_DRV_INSTANCE_NUM sets number of driver instances
 *               USART_CDC_DRV0_NUM sets the first instance driver number
 *               (default first instance number is 9)
 *               USART_CDC_DRV1_NUM sets the second instance driver number
 *               (default first instance number is 10)
 *               USART_CDC_DRV2_NUM sets the third instance driver number
 *               (default first instance number is 11)
 *               USART_CDC_DRV3_NUM sets the fourth instance driver number
 *               (default first instance number is 12)
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

// Number of instances (default 1, maximum 4)
#ifndef USART_CDC_DRV_INSTANCE_NUM
#define USART_CDC_DRV_INSTANCE_NUM      1
#endif

// Driver number used for first Driver Control Block instance
// other instances follow
#ifndef USART_CDC_DRV0_NUM
#define USART_CDC_DRV0_NUM              9
#endif
#ifndef USART_CDC_DRV1_NUM
#define USART_CDC_DRV1_NUM              10
#endif
#ifndef USART_CDC_DRV2_NUM
#define USART_CDC_DRV2_NUM              11
#endif
#ifndef USART_CDC_DRV3_NUM
#define USART_CDC_DRV3_NUM              12
#endif

#define USART_CDC_DRV_(n)               Driver_USART##n
#define USART_CDC_DRV(n)                USART_CDC_DRV_(n)

// Send, Receive and Status thread settings
#ifndef USART_CDC_SEND_THREAD_STACK_SIZE
#define USART_CDC_SEND_THREAD_STACK_SIZE      512
#endif
#ifndef USART_CDC_SEND_THREAD_PRIORITY
#define USART_CDC_SEND_THREAD_PRIORITY        osPriorityNormal
#endif
#ifndef USART_CDC_RECEIVE_THREAD_STACK_SIZE
#define USART_CDC_RECEIVE_THREAD_STACK_SIZE   512
#endif
#ifndef USART_CDC_RECEIVE_THREAD_PRIORITY
#define USART_CDC_RECEIVE_THREAD_PRIORITY     osPriorityNormal
#endif

/************************** Variable and Memory Definitions *******************/

typedef struct {
  osThreadId              receive_thread_id;  ///< bulk in pipe thread ID
  osThreadId              send_thread_id;     ///< bulk out pipe thread ID
  ARM_USART_SignalEvent_t cb_event;           ///< USART Driver callback function
  bool                    initialized;        ///< UART instance initialized
  uint8_t                 cdc_instance;       ///< CDC instance
  bool                    control_tx;         ///< UART Tx enable
  bool                    control_rx;         ///< UART Rx enable
  bool                    flow_control_rts;   ///< UART flow control on RTS line enable
  bool                    flow_control_cts;   ///< UART flow control on CTS line enable
  bool                    send_busy;          ///< send in progress
  uint8_t                *send_data;          ///< pointer to memory containing data to send
  uint32_t                send_num;           ///< number of data bytes to send
  bool                    receive_busy;       ///< reception in progress
  uint8_t                *receive_data;       ///< pointer to memory for data reception
  uint32_t                receive_num;        ///< number of data bytes to receive
  uint16_t                ctrl_lines;         ///< modem lines control
  uint16_t                status;             ///< modem lines and error status
  CDC_LINE_CODING         line_coding;        ///< initial line coding
} USART_CDC_t;

static USART_CDC_t usart_cdc[USART_CDC_DRV_INSTANCE_NUM];

/************************** Internal Function Prototypes **********************/

static void ARM_USARTx_Sent     (uint8_t instance);
static void ARM_USARTx_Received (uint8_t instance);

/************************** Internal Functions ********************************/

/// \brief Check device instance pointers and variables
/// \param[in]     instance             index of CDC instance.
/// \return        true                 requested instance exists.
/// \return        false                requested instance does not exist.
static bool CheckInstance (uint8_t instance) {

  if (instance >= USART_CDC_DRV_INSTANCE_NUM)   return false;
  if (usart_cdc[instance].initialized == false) return false;

  return true;
}

/*------------------------- Internal Threads ---------------------------------*/

/// \brief User thread for handling data send (to Bulk Out endpoint)
/// \param[in]     arg                  index of CDC instance.
void USART_CDC_Send_Thread (void const *arg) {
  USART_CDC_t *ptr_usart_cdc;
  uint8_t      instance;
  usbStatus    status;

  instance      = *(uint8_t *)arg;
  ptr_usart_cdc = &usart_cdc[instance];

  // Send Data on Bulk Out Pipe in thread
  status = USBH_CDC_ACM_Send (instance, ptr_usart_cdc->send_data, ptr_usart_cdc->send_num);
  ptr_usart_cdc->send_busy = false;

  if (status == usbOK) ARM_USARTx_Sent(instance);
}
osThreadDef(USART_CDC_Send_Thread, USART_CDC_SEND_THREAD_PRIORITY, USART_CDC_DRV_INSTANCE_NUM, USART_CDC_SEND_THREAD_STACK_SIZE);

/// \brief User thread for handling data reception (from Bulk In endpoint)
/// \param[in]     arg                  index of CDC instance.
void USART_CDC_Receive_Thread (void const *arg) {
  USART_CDC_t *ptr_usart_cdc;
  uint8_t      instance;
  usbStatus    status;

  instance      = *(uint8_t *)arg;
  ptr_usart_cdc = &usart_cdc[instance];

  // Receive Data on Bulk In Pipe in thread
  do {
    status = USBH_CDC_ACM_Receive (instance, ptr_usart_cdc->receive_data, ptr_usart_cdc->receive_num);
    if (status == usbTransferError) {
      ptr_usart_cdc->receive_busy = false;
      osThreadTerminate (osThreadGetId());
    }
  } while (status == usbTimeout);
  ptr_usart_cdc->receive_busy = false;

  if (status == usbOK) ARM_USARTx_Received(instance);
}
osThreadDef(USART_CDC_Receive_Thread, USART_CDC_RECEIVE_THREAD_PRIORITY, USART_CDC_DRV_INSTANCE_NUM, USART_CDC_RECEIVE_THREAD_STACK_SIZE);

/***-------------- USBH CDC Specific Functions -----------------------------***/

/// \brief Callback function called when Communication Device Class device
///        modem line or error status changes
/// \param[in]     instance             index of CDC instance.
/// \return                             error status and line states:
///                                       - bit 6: bOverRun
///                                       - bit 5: bParity
///                                       - bit 4: bFraming
///                                       - bit 3: bRingSignal
///                                       - bit 2: bBreak
///                                       - bit 1: bTxCarrier (DSR line state)
///                                       - bit 0: bRxCarrier (DCD line state)
void USBH_CDC_ACM_Notify (uint8_t instance, uint16_t status) {
  usart_cdc[instance].status = status;
}

/************************** USART Driver **************************************/

#define ARM_USART_DRV_VERSION           ARM_DRIVER_VERSION_MAJOR_MINOR(1,00)

// Driver Version
static const ARM_DRIVER_VERSION         usart_driver_version = { ARM_USART_API_VERSION, ARM_USART_DRV_VERSION };

// USART Capabilities
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

/// \fn          int32_t ARM_USARTx_Initialize (uint8_t instance, ARM_USART_SignalEvent_t cb_event)
/// \brief       Initialize USART Interface.
/// \param[in]   instance  Index of CDC instance
/// \param[in]   cb_event  Pointer to ARM_USART_SignalEvent
/// \return      execution status
static int32_t ARM_USARTx_Initialize (uint8_t instance, ARM_USART_SignalEvent_t cb_event) {

  if (instance >= USART_CDC_DRV_INSTANCE_NUM) return ARM_DRIVER_ERROR;

  usart_cdc[instance].cb_event     = cb_event;
  usart_cdc[instance].initialized  = true;
  usart_cdc[instance].cdc_instance = instance;

  return ARM_DRIVER_OK;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static int32_t ARM_USART0_Initialize (ARM_USART_SignalEvent_t cb_event) { return ARM_USARTx_Initialize (0, cb_event); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static int32_t ARM_USART1_Initialize (ARM_USART_SignalEvent_t cb_event) { return ARM_USARTx_Initialize (1, cb_event); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static int32_t ARM_USART2_Initialize (ARM_USART_SignalEvent_t cb_event) { return ARM_USARTx_Initialize (2, cb_event); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static int32_t ARM_USART3_Initialize (ARM_USART_SignalEvent_t cb_event) { return ARM_USARTx_Initialize (3, cb_event); }
#endif

/// \fn          int32_t ARM_USARTx_Uninitialize (uint8_t instance)
/// \brief       De-initialize USART Interface.
/// \param[in]   instance  Index of CDC instance
/// \return      execution status
static int32_t ARM_USARTx_Uninitialize (uint8_t instance) {

  if (CheckInstance (instance) == false) return ARM_DRIVER_ERROR;

  usart_cdc[instance].initialized = false;

  return ARM_DRIVER_OK;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static int32_t ARM_USART0_Uninitialize (void) { return ARM_USARTx_Uninitialize (0); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static int32_t ARM_USART1_Uninitialize (void) { return ARM_USARTx_Uninitialize (1); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static int32_t ARM_USART2_Uninitialize (void) { return ARM_USARTx_Uninitialize (2); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static int32_t ARM_USART3_Uninitialize (void) { return ARM_USARTx_Uninitialize (3); }
#endif

/// \fn          int32_t ARM_USART_PowerControl (ARM_POWER_STATE state)
/// \brief       Control USART Interface Power.
/// \param[in]   state  Power state
/// \return      execution status
static int32_t ARM_USART_PowerControl (ARM_POWER_STATE state) {
  switch (state) {
    case ARM_POWER_OFF:
    case ARM_POWER_FULL:
      break;

    default: return ARM_DRIVER_ERROR_UNSUPPORTED;
  }

  return ARM_DRIVER_OK;
}

/// \fn          int32_t ARM_USARTx_Send (uint8_t instance, const void *data, uint32_t num)
/// \brief       Start sending data to USART transmitter.
/// \param[in]   instance  Index of CDC instance
/// \param[in]   data      Pointer to buffer with data to send to USART transmitter
/// \param[in]   num       Number of data items to send
/// \return      execution status
static int32_t ARM_USARTx_Send (uint8_t instance, const void *data, uint32_t num) {
  USART_CDC_t *ptr_usart_cdc;

  if (CheckInstance (instance) == false) return ARM_DRIVER_ERROR;
  if (!usart_cdc[instance].control_tx)   return ARM_DRIVER_ERROR;  // Tx disabled

  ptr_usart_cdc = &usart_cdc[instance];

  if (ptr_usart_cdc->send_busy) return ARM_DRIVER_ERROR_BUSY;
  ptr_usart_cdc->send_busy    = true;

  ptr_usart_cdc->send_data    = (uint8_t *)data;
  ptr_usart_cdc->send_num     = num;

  // Start send thread
  ptr_usart_cdc->send_thread_id = osThreadCreate (osThread(USART_CDC_Send_Thread), &usart_cdc[instance].cdc_instance);
  if (!ptr_usart_cdc->send_thread_id) {
    ptr_usart_cdc->send_busy  = false;
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static int32_t ARM_USART0_Send (const void *data, uint32_t num) { return (ARM_USARTx_Send (0, data, num)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static int32_t ARM_USART1_Send (const void *data, uint32_t num) { return (ARM_USARTx_Send (1, data, num)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static int32_t ARM_USART2_Send (const void *data, uint32_t num) { return (ARM_USARTx_Send (2, data, num)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static int32_t ARM_USART3_Send (const void *data, uint32_t num) { return (ARM_USARTx_Send (3, data, num)); }
#endif

/// \fn          void ARM_USARTx_Sent (uint8_t instance)
/// \brief       All data was sent on USART transmitter.
/// \param[in]   instance  Index of CDC instance
static void ARM_USARTx_Sent (uint8_t instance) {
  if (usart_cdc[instance].cb_event) usart_cdc[instance].cb_event (ARM_USART_EVENT_SEND_COMPLETE);
}

/// \fn          int32_t ARM_USARTx_Receive (uint8_t instance, void *data, uint32_t num)
/// \brief       Start receiving data from USART receiver.
/// \param[in]   instance  Index of CDC instance
/// \param[out]  data      Pointer to buffer for data to receive from USART receiver
/// \param[in]   num       Number of data items to receive
/// \return      execution status
static int32_t ARM_USARTx_Receive (uint8_t instance, void *data, uint32_t num) {
  USART_CDC_t *ptr_usart_cdc;

  if (CheckInstance (instance) == false) return ARM_DRIVER_ERROR;
  if (!usart_cdc[instance].control_rx)   return ARM_DRIVER_ERROR;  // Rx disabled

  ptr_usart_cdc = &usart_cdc[instance];

  if (ptr_usart_cdc->receive_busy) return ARM_DRIVER_ERROR_BUSY;
  ptr_usart_cdc->receive_busy    = true;

  ptr_usart_cdc->receive_data    = data;
  ptr_usart_cdc->receive_num     = num;

  // Start reception thread
  ptr_usart_cdc->receive_thread_id = osThreadCreate (osThread(USART_CDC_Receive_Thread), &usart_cdc[instance].cdc_instance);
  if (!ptr_usart_cdc->receive_thread_id) {
    ptr_usart_cdc->receive_busy  = false;
    return ARM_DRIVER_ERROR;
  }

  return ARM_DRIVER_OK;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static int32_t ARM_USART0_Receive (void *data, uint32_t num) { return (ARM_USARTx_Receive (0, data, num)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static int32_t ARM_USART1_Receive (void *data, uint32_t num) { return (ARM_USARTx_Receive (1, data, num)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static int32_t ARM_USART2_Receive (void *data, uint32_t num) { return (ARM_USARTx_Receive (2, data, num)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static int32_t ARM_USART3_Receive (void *data, uint32_t num) { return (ARM_USARTx_Receive (3, data, num)); }
#endif

/// \fn          void ARM_USARTx_Received (uint8_t instance)
/// \brief       All data was received on USART receiver.
/// \param[in]   instance  Index of CDC instance
static void ARM_USARTx_Received (uint8_t instance) {
  if (usart_cdc[instance].cb_event) usart_cdc[instance].cb_event (ARM_USART_EVENT_RECEIVE_COMPLETE);
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

/// \fn          uint32_t ARM_USARTx_GetTxCount (uint8_t instance)
/// \brief       Get transmitted data count.
/// \param[in]   instance  Index of CDC instance
/// \return      number of data items transmitted
static uint32_t ARM_USARTx_GetTxCount (uint8_t instance) {

  if (CheckInstance (instance) == false) return 0;

  return (USBH_CDC_ACM_GetTxCount(instance));
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static uint32_t ARM_USART0_GetTxCount (void) { return (ARM_USARTx_GetTxCount (0)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static uint32_t ARM_USART1_GetTxCount (void) { return (ARM_USARTx_GetTxCount (1)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static uint32_t ARM_USART2_GetTxCount (void) { return (ARM_USARTx_GetTxCount (2)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static uint32_t ARM_USART3_GetTxCount (void) { return (ARM_USARTx_GetTxCount (3)); }
#endif

/// \fn          uint32_t ARM_USARTx_GetRxCount (uint8_t instance)
/// \brief       Get received data count.
/// \param[in]   instance  Index of CDC instance
/// \return      number of data items received
static uint32_t ARM_USARTx_GetRxCount (uint8_t instance) {

  if (CheckInstance (instance) == false) return 0;

  return (USBH_CDC_ACM_GetRxCount(instance));
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static uint32_t ARM_USART0_GetRxCount (void) { return (ARM_USARTx_GetRxCount (0)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static uint32_t ARM_USART1_GetRxCount (void) { return (ARM_USARTx_GetRxCount (1)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static uint32_t ARM_USART2_GetRxCount (void) { return (ARM_USARTx_GetRxCount (2)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static uint32_t ARM_USART3_GetRxCount (void) { return (ARM_USARTx_GetRxCount (3)); }
#endif

/// \fn          int32_t ARM_USARTx_Control (uint8_t instance, uint32_t control, uint32_t arg)
/// \brief       Control USART Interface.
/// \param[in]   instance  Index of CDC instance
/// \param[in]   control   Operation
/// \param[in]   arg       Argument of operation (optional)
/// \return      common execution status and driver specific usart_execution status
static int32_t ARM_USARTx_Control (uint8_t instance, uint32_t control, uint32_t arg) {
  USART_CDC_t       *ptr_usart_cdc;
  CDC_LINE_CODING    line_coding;

  if (CheckInstance (instance) == false) return ARM_DRIVER_ERROR;

  ptr_usart_cdc = &usart_cdc[instance];
  line_coding   = ptr_usart_cdc->line_coding;

  switch (control & ARM_USART_CONTROL_Msk) {
    case ARM_USART_MODE_ASYNCHRONOUS:
      break;

    case ARM_USART_CONTROL_TX:                // Control Tx
      if (arg) ptr_usart_cdc->control_tx = true;       // Tx enabled
      else     ptr_usart_cdc->control_tx = false;      // Tx disable
      return ARM_DRIVER_OK;

    case ARM_USART_CONTROL_RX:                // Control Rx
      if (arg) ptr_usart_cdc->control_rx = true;       // Rx enabled
      else     ptr_usart_cdc->control_rx = false;      // Rx disable
      return ARM_DRIVER_OK;

    case ARM_USART_CONTROL_BREAK:             // Control break
      if (arg) {                              // Break enabled
        if (USBH_CDC_ACM_SendBreak (instance, 0xFFFF)) return ARM_DRIVER_ERROR;
      } else {                                // Break disable
        if (USBH_CDC_ACM_SendBreak (instance, 0))      return ARM_DRIVER_ERROR;
      }
      return ARM_DRIVER_OK;

    case ARM_USART_ABORT_SEND:                // Abort send
      if (ptr_usart_cdc->send_thread_id) {
        if (osThreadTerminate(ptr_usart_cdc->send_thread_id) != osOK) return ARM_DRIVER_ERROR;
        ptr_usart_cdc->send_thread_id = 0;
      }
      return ARM_DRIVER_OK;

    case ARM_USART_ABORT_RECEIVE:             // Abort receive
      if (ptr_usart_cdc->receive_thread_id) {
        if (osThreadTerminate(ptr_usart_cdc->receive_thread_id) != osOK) return ARM_DRIVER_ERROR;
        ptr_usart_cdc->receive_thread_id = 0;
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
      ptr_usart_cdc->flow_control_rts = false;
      ptr_usart_cdc->flow_control_cts = false;
      break;
    case ARM_USART_FLOW_CONTROL_RTS:
      ptr_usart_cdc->flow_control_rts = true;
      break;
    case ARM_USART_FLOW_CONTROL_CTS:
      ptr_usart_cdc->flow_control_cts = true;
      break;
    case ARM_USART_FLOW_CONTROL_RTS_CTS:
      ptr_usart_cdc->flow_control_rts = true;
      ptr_usart_cdc->flow_control_cts = true;
      break;
    default:                            return ARM_USART_ERROR_FLOW_CONTROL;
  }

  line_coding.dwDTERate = arg;          // USART Baudrate

  if (USBH_CDC_ACM_SetLineCoding (instance, &line_coding)) return ARM_DRIVER_ERROR;

  ptr_usart_cdc->line_coding = line_coding;

  return ARM_DRIVER_OK;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static int32_t ARM_USART0_Control (uint32_t control, uint32_t arg) { return (ARM_USARTx_Control (0, control, arg)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static int32_t ARM_USART1_Control (uint32_t control, uint32_t arg) { return (ARM_USARTx_Control (1, control, arg)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static int32_t ARM_USART2_Control (uint32_t control, uint32_t arg) { return (ARM_USARTx_Control (2, control, arg)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static int32_t ARM_USART3_Control (uint32_t control, uint32_t arg) { return (ARM_USARTx_Control (3, control, arg)); }
#endif

/// \fn          ARM_USART_STATUS ARM_USARTx_GetStatus (uint8_t instance)
/// \brief       Get USART status.
/// \param[in]   instance  Index of CDC instance
/// \return      USART status ARM_USART_STATUS
static ARM_USART_STATUS ARM_USARTx_GetStatus (uint8_t instance) {
  USART_CDC_t        *ptr_usart_cdc;
  ARM_USART_STATUS    status = {0};
  uint16_t            usart_status;

  if (CheckInstance (instance) == false) return status;

  ptr_usart_cdc = &usart_cdc[instance];
  usart_status  = ptr_usart_cdc->status;

  status.tx_busy          =  ptr_usart_cdc->send_busy;      // Transmitter busy flag
  status.rx_busy          =  ptr_usart_cdc->receive_busy;   // Receiver busy flag
  status.tx_underflow     =  0;                             // Transmit data underflow detected (cleared on start of next send operation)
  status.rx_overflow      = (usart_status >> 6) & 1;        // Receive data overflow detected (cleared on start of next receive operation)
  status.rx_break         = (usart_status >> 2) & 1;        // Break detected on receive (cleared on start of next receive operation)
  status.rx_framing_error = (usart_status >> 4) & 1;        // Framing error detected on receive (cleared on start of next receive operation)
  status.rx_parity_error  = (usart_status >> 5) & 1;        // Parity error detected on receive (cleared on start of next receive operation)

  return status;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static ARM_USART_STATUS ARM_USART0_GetStatus (void) { return (ARM_USARTx_GetStatus (0)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static ARM_USART_STATUS ARM_USART1_GetStatus (void) { return (ARM_USARTx_GetStatus (1)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static ARM_USART_STATUS ARM_USART2_GetStatus (void) { return (ARM_USARTx_GetStatus (2)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static ARM_USART_STATUS ARM_USART3_GetStatus (void) { return (ARM_USARTx_GetStatus (3)); }
#endif

/// \fn          int32_t ARM_USARTx_SetModemControl (uint8_t instance, ARM_USART_MODEM_CONTROL control)
/// \brief       Set USART Modem Control line state.
/// \param[in]   instance  Index of CDC instance
/// \param[in]   control   ARM_USART_MODEM_CONTROL
/// \return      execution status
static int32_t ARM_USARTx_SetModemControl (uint8_t instance, ARM_USART_MODEM_CONTROL control) {
  USART_CDC_t *ptr_usart_cdc;
  uint16_t     ctrl_lines;

  if (CheckInstance (instance) == false) return ARM_DRIVER_ERROR;

  ptr_usart_cdc = &usart_cdc[instance];
  ctrl_lines    = ptr_usart_cdc->ctrl_lines;

  if (ptr_usart_cdc->flow_control_rts) {// If flow control on RTS line enabled
    if (control == ARM_USART_RTS_CLEAR) // Deactivate RTS
      ctrl_lines &= ~(1 << 1);
    if (control == ARM_USART_RTS_SET)   // Activate RTS
      ctrl_lines |=  (1 << 1);
  }
  if (control == ARM_USART_DTR_CLEAR)   // Deactivate DTR
    ctrl_lines &= ~(1 << 0);
  if (control == ARM_USART_DTR_SET)     // Activate DTR
    ctrl_lines |=  (1 << 0);

  if (USBH_CDC_ACM_SetControlLineState (instance, ctrl_lines) != usbOK) return ARM_DRIVER_ERROR;

  ptr_usart_cdc->ctrl_lines = ctrl_lines;

  return ARM_DRIVER_OK;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static int32_t ARM_USART0_SetModemControl (ARM_USART_MODEM_CONTROL control) { return (ARM_USARTx_SetModemControl (0, control)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static int32_t ARM_USART1_SetModemControl (ARM_USART_MODEM_CONTROL control) { return (ARM_USARTx_SetModemControl (1, control)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static int32_t ARM_USART2_SetModemControl (ARM_USART_MODEM_CONTROL control) { return (ARM_USARTx_SetModemControl (2, control)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static int32_t ARM_USART3_SetModemControl (ARM_USART_MODEM_CONTROL control) { return (ARM_USARTx_SetModemControl (3, control)); }
#endif

/// \fn          ARM_USART_MODEM_STATUS ARM_USARTx_GetModemStatus (uint8_t instance)
/// \brief       Get USART Modem Status lines state.
/// \param[in]   instance  Index of CDC instance
/// \return      modem status ARM_USART_MODEM_STATUS
static ARM_USART_MODEM_STATUS ARM_USARTx_GetModemStatus (uint8_t instance) {
  USART_CDC_t            *ptr_usart_cdc;
  ARM_USART_MODEM_STATUS  modem_status = {0};
  uint16_t                usart_status;

  if (CheckInstance (instance) == false) return modem_status;

  ptr_usart_cdc = &usart_cdc[instance];
  usart_status  = usart_cdc[instance].status;

  modem_status.cts =  ptr_usart_cdc->flow_control_cts;  // CTS state: 1=Active, 0=Inactive
  modem_status.dsr = (usart_status >> 1) & 1;  // DSR state: 1=Active, 0=Inactive
  modem_status.dcd = (usart_status >> 0) & 1;  // DCD state: 1=Active, 0=Inactive
  modem_status.ri  = (usart_status >> 3) & 1;  // RI  state: 1=Active, 0=Inactive

  return modem_status;
}
#if   (USART_CDC_DRV_INSTANCE_NUM > 0)
static ARM_USART_MODEM_STATUS ARM_USART0_GetModemStatus (void) { return (ARM_USARTx_GetModemStatus(0)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 1)
static ARM_USART_MODEM_STATUS ARM_USART1_GetModemStatus (void) { return (ARM_USARTx_GetModemStatus(1)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 2)
static ARM_USART_MODEM_STATUS ARM_USART2_GetModemStatus (void) { return (ARM_USARTx_GetModemStatus(2)); }
#endif
#if   (USART_CDC_DRV_INSTANCE_NUM > 3)
static ARM_USART_MODEM_STATUS ARM_USART3_GetModemStatus (void) { return (ARM_USARTx_GetModemStatus(3)); }
#endif

#if (USART_CDC_DRV_INSTANCE_NUM > 0)
// USART CDC Driver Control Instance 1st Block
ARM_DRIVER_USART USART_CDC_DRV(USART_CDC_DRV0_NUM) = {
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART0_Initialize,
    ARM_USART0_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART0_Send,
    ARM_USART0_Receive,
    ARM_USART_Transfer,
    ARM_USART0_GetTxCount,
    ARM_USART0_GetRxCount,
    ARM_USART0_Control,
    ARM_USART0_GetStatus,
    ARM_USART0_SetModemControl,
    ARM_USART0_GetModemStatus
};
#endif
#if (USART_CDC_DRV_INSTANCE_NUM > 1)
// USART CDC Driver Control Instance 2nd Block
ARM_DRIVER_USART USART_CDC_DRV(USART_CDC_DRV1_NUM) = {
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART1_Initialize,
    ARM_USART1_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART1_Send,
    ARM_USART1_Receive,
    ARM_USART_Transfer,
    ARM_USART1_GetTxCount,
    ARM_USART1_GetRxCount,
    ARM_USART1_Control,
    ARM_USART1_GetStatus,
    ARM_USART1_SetModemControl,
    ARM_USART1_GetModemStatus
};
#endif
#if (USART_CDC_DRV_INSTANCE_NUM > 2)
// USART CDC Driver Control Instance 3rd Block
ARM_DRIVER_USART USART_CDC_DRV(USART_CDC_DRV2_NUM) = {
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART2_Initialize,
    ARM_USART2_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART2_Send,
    ARM_USART2_Receive,
    ARM_USART_Transfer,
    ARM_USART2_GetTxCount,
    ARM_USART2_GetRxCount,
    ARM_USART2_Control,
    ARM_USART2_GetStatus,
    ARM_USART2_SetModemControl,
    ARM_USART2_GetModemStatus
};
#endif
#if (USART_CDC_DRV_INSTANCE_NUM > 3)
// USART CDC Driver Control Instance 4th Block
ARM_DRIVER_USART USART_CDC_DRV(USART_CDC_DRV3_NUM) = {
    ARM_USART_GetVersion,
    ARM_USART_GetCapabilities,
    ARM_USART3_Initialize,
    ARM_USART3_Uninitialize,
    ARM_USART_PowerControl,
    ARM_USART3_Send,
    ARM_USART3_Receive,
    ARM_USART_Transfer,
    ARM_USART3_GetTxCount,
    ARM_USART3_GetRxCount,
    ARM_USART3_Control,
    ARM_USART3_GetStatus,
    ARM_USART3_SetModemControl,
    ARM_USART3_GetModemStatus
};
#endif
