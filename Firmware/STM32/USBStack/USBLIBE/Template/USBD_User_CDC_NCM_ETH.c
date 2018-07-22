/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_User_CDC_NCM_ETH%Instance%.c
 * Purpose: USB Device Communication Device Class (CDC)
 *          Network Control Model (NCM) User module for an USB Ethernet Bridge
 * Rev.:    V1.0.1
 *----------------------------------------------------------------------------*/
/**
 * \addtogroup usbd_cdcFunctions
 *
 * USBD_User_CDC_NCM_ETH_%Instance%.c implements the application specific functionality
 * of the CDC NCM class and is used to respond to control endpoint requests
 * as well as receive and send data to the USB Host.
 * It implements an USB Ethernet Bridge.
 *
 * The implementation depends on the configuration file USBD_Config_CDC_%Instance%.h.
 *
 */
 
 
//! [code_USBD_User_CDC_NCM_ETH]
 
#include <string.h>
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "rl_usb.h"                     // Keil.MDK-Pro::USB:CORE
#include "Driver_ETH_MAC.h"             // ::CMSIS Driver:Ethernet MAC
#include "Driver_ETH_PHY.h"             // ::CMSIS Driver:Ethernet PHY
#include "RTE\USB\USBD_Config_CDC_%Instance%.h"
 
#define ETH_MAC_NUM             0       /* ETH MAC Driver number */
#define ETH_PHY_NUM             0       /* ETH PHY Driver number */
#define USB_CDC_NUM             %Instance%       /* USB CDC Instance number */
 
#define MAX_IN_DATAGRAMS        10
 
extern ARM_DRIVER_ETH_MAC ARM_Driver_ETH_MAC_(ETH_MAC_NUM);
extern ARM_DRIVER_ETH_PHY ARM_Driver_ETH_PHY_(ETH_PHY_NUM);
 
static ARM_DRIVER_ETH_MAC *EthMac = &ARM_Driver_ETH_MAC_(ETH_MAC_NUM);
static ARM_DRIVER_ETH_PHY *EthPhy = &ARM_Driver_ETH_PHY_(ETH_PHY_NUM);
 
static const uint16_t  *wsMacAddress = USBD_CDC%Instance%_NCM_MAC_ADDRESS;
static ARM_ETH_MAC_ADDR   MacAddress;
 
static ARM_ETH_LINK_STATE LinkState;
static ARM_ETH_LINK_INFO  LinkInfo;
static uint32_t           LinkSpeed;
 
static uint32_t           PacketFilter;
 
static struct {
  uint16_t ntb_format;
  uint32_t ntb_input_size;
  uint16_t max_datagram_size;
  uint16_t crc_mode;
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x02) != 0)
  uint8_t  net_address[6];
#endif
#if (USBD_CDC%Instance%_NCM_W_NUMBER_MC_FILTERS != 0)
  uint8_t  mc_filters[6*(USBD_CDC%Instance%_NCM_W_NUMBER_MC_FILTERS & 0x7FFF)];
#endif
#if (USBD_CDC%Instance%_NCM_B_NUMBER_POWER_FILTERS != 0)
  uint8_t  power_filter_active[(USBD_CDC%Instance%_NCM_B_NUMBER_POWER_FILTERS + 7)/8];
#endif
  uint16_t packet_filter_bitmap;
#if (USBD_CDC%Instance%_NCM_BM_ETHERNET_STATISTICS != 0)
  uint32_t eth_statistics[29];
#endif
} NCM_State;
 
static uint32_t FrameIN_Size;
static uint8_t  FrameIN [USBD_CDC%Instance%_NCM_W_MAX_SEGMENT_SIZE];
static uint8_t  FrameOUT[USBD_CDC%Instance%_NCM_W_MAX_SEGMENT_SIZE];
 
static void EthMac_Notify (uint32_t event);
 
static void Connection_Thread (void const *arg);
static void DataIN_Thread     (void const *arg);
static void DataOUT_Thread    (void const *arg);
 
static osThreadId Connection_ThreadId;
static osThreadId DataIN_ThreadId;
static osThreadId DataOUT_ThreadId;
 
osThreadDef(Connection_Thread, osPriorityNormal, 1, NULL);
osThreadDef(DataIN_Thread,     osPriorityNormal, 1, NULL);
osThreadDef(DataOUT_Thread,    osPriorityNormal, 1, NULL);
 
 
// MAC Address conversion from wide string
// \param[in]   wstr    Pointer to wide string.
// \param[out]  addr    Pointer to address.
static void MAC_wstr_to_addr (const uint16_t *wstr, uint8_t *addr) {
  uint8_t c;
  uint8_t n;
  int32_t i;

  for (i = 0; i < 12; i++) {
    c = (uint8_t)wstr[i];
    if        ((c >= '0') && (c <= '9')) {
      n = c - '0';
    } else if ((c >= 'A') && (c <= 'F')) {
      n = c - 'A' + 10;
    } else if ((c >= 'a') && (c <= 'f')) {
      n = c - 'a' + 10;
    } else {
      n = 0;
    }
    if (i & 1) {
      addr[i>>1] |= n;
    } else {
      addr[i>>1]  = n << 4;
    }
  }
}
 
 
// Called during USBD_Initialize to initialize the USB CDC class instance (NCM).
void USBD_CDC%Instance%_NCM_Initialize (void) {
  // Add code for initialization
  ARM_ETH_MAC_CAPABILITIES capabilities;
  int32_t                  status;
 
  MAC_wstr_to_addr(wsMacAddress, (uint8_t *)&MacAddress);
 
  memset(&NCM_State, 0, sizeof(NCM_State));
  NCM_State.ntb_input_size = USBD_CDC%Instance%_NCM_DW_NTB_IN_MAX_SIZE;
  NCM_State.max_datagram_size = USBD_CDC%Instance%_NCM_W_MAX_SEGMENT_SIZE;
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x02) != 0)
  memcpy(&NCM_State.net_address, &MacAddress, 6);
#endif
  NCM_State.packet_filter_bitmap = 0x0CU;
 
  LinkState = ARM_ETH_LINK_DOWN;
  LinkInfo.speed  = 0U;
  LinkInfo.duplex = 0U;
  LinkSpeed = 0U;
 
  PacketFilter = ARM_ETH_MAC_ADDRESS_BROADCAST;
 
  FrameIN_Size = 0U;
 
  // Initialize Media Access Controller
  capabilities = EthMac->GetCapabilities();
 
  status = EthMac->Initialize(EthMac_Notify);
  if (status != ARM_DRIVER_OK) { return; }
  status = EthMac->PowerControl(ARM_POWER_FULL);
  if (status != ARM_DRIVER_OK) { return; }
 
  status = EthMac->SetMacAddress(&MacAddress);
  if (status != ARM_DRIVER_OK) { return; }
 
  // Initialize Physical Media Interface
  status = EthPhy->Initialize(EthMac->PHY_Read, EthMac->PHY_Write);
  if (status != ARM_DRIVER_OK) { return; }
  status = EthPhy->PowerControl(ARM_POWER_FULL);
  if (status != ARM_DRIVER_OK) { return; }
  status = EthPhy->SetInterface(capabilities.media_interface);
  if (status != ARM_DRIVER_OK) { return; }
  status = EthPhy->SetMode(ARM_ETH_PHY_AUTO_NEGOTIATE);
  if (status != ARM_DRIVER_OK) { return; }
 
  // Create Threads
  Connection_ThreadId = osThreadCreate(osThread(Connection_Thread), NULL);
  DataIN_ThreadId     = osThreadCreate(osThread(DataIN_Thread),     NULL);
  DataOUT_ThreadId    = osThreadCreate(osThread(DataOUT_Thread),    NULL);
}
 
 
// Called during USBD_Uninitialize to de-initialize the USB CDC class instance (NCM).
void USBD_CDC%Instance%_NCM_Uninitialize (void) {
  // Add code for de-initialization
  osThreadTerminate(Connection_ThreadId);
  osThreadTerminate(DataIN_ThreadId);
  osThreadTerminate(DataOUT_ThreadId);
 
  EthPhy->PowerControl(ARM_POWER_OFF);
  EthPhy->Uninitialize();
 
  EthMac->PowerControl(ARM_POWER_OFF);
  EthMac->Uninitialize();
}
 
 
// Called upon USB Bus Reset Event.
void USBD_CDC%Instance%_NCM_Reset (void) {
  // Add code for reset
}
 
 
// Called when USB Host changes data interface from alternate 0 to alternate 1 (activates data interface).
void USBD_CDC%Instance%_NCM_Start (void) {
  // Add code for data interface activation
  osSignalSet(Connection_ThreadId, 1U);
  osSignalSet(DataIN_ThreadId, 1U);
}
 
 
// Called when USB Host changes data interface from alternate 1 to alternate 0 (de-activates data interface).
void USBD_CDC%Instance%_NCM_Stop (void) {
  // Add code for data interface de-activation
  // Explained in ncm10.pdf document from www.usb.org in paragraph 7.2
 
  FrameIN_Size = 0U;
  osSignalClear(DataIN_ThreadId, 1U);
 
  memset(&NCM_State, 0, sizeof(NCM_State));
  NCM_State.ntb_input_size = USBD_CDC%Instance%_NCM_DW_NTB_IN_MAX_SIZE;
  NCM_State.max_datagram_size = USBD_CDC%Instance%_NCM_W_MAX_SEGMENT_SIZE;
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x02) != 0)
  memcpy(&NCM_State.net_address, &MacAddress, 6);
#endif
  NCM_State.packet_filter_bitmap = 0x0CU;
 
  PacketFilter = ARM_ETH_MAC_ADDRESS_BROADCAST;
 
  EthMac->SetMacAddress(&MacAddress);
  EthMac->SetAddressFilter(NULL, 0);
  EthMac->Control(ARM_ETH_MAC_CONFIGURE,
                  LinkInfo.speed  << ARM_ETH_MAC_SPEED_Pos  |
                  LinkInfo.duplex << ARM_ETH_MAC_DUPLEX_Pos |
                  PacketFilter);
}
 
 
// Called upon USB Host request to set the Ethernet device multicast filters.
// \param[in]   addr_list            Pointer to list of 48-bit Multicast addresses.
// \param[in]   num_of_filters       Number of filters.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetEthernetMulticastFilters (const uint8_t *addr_list, uint16_t num_of_filters) {
#if (USBD_CDC%Instance%_NCM_W_NUMBER_MC_FILTERS != 0)
  int32_t status;
 
  if (num_of_filters > (USBD_CDC%Instance%_NCM_W_NUMBER_MC_FILTERS & 0x7FFF)) { return false; }
 
  // Add code for handling request
  status = EthMac->SetAddressFilter((ARM_ETH_MAC_ADDR *)addr_list, num_of_filters);
  if (status != ARM_DRIVER_OK) { return false; }
 
  memcpy(&NCM_State.mc_filters, addr_list, num_of_filters * 6);
 
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to set up the specified Ethernet power management pattern filter.
// \param[in]   filter_number        Filter number.
// \param[in]   pattern_filter       Power management pattern filter structure.
// \param[in]   pattern_filter_size  Size of pattern filter structure.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetEthernetPowerManagementPatternFilter (uint16_t filter_number, const uint8_t *pattern_filter, uint16_t pattern_filter_size) {
#if (USBD_CDC%Instance%_NCM_B_NUMBER_POWER_FILTERS != 0)
  if (filter_number >= USBD_CDC%Instance%_NCM_B_NUMBER_POWER_FILTERS) { return false; }
 
  // Add code for handling request
 
  NCM_State.power_filter_active[filter_number / 8] |= 1U << (filter_number % 8);
 
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to retrieve the status of the specified Ethernet power management pattern filter.
// \param[in]   filter_number        Filter number.
// \param[out]  pattern_active       Pointer to pattern active boolean.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetEthernetPowerManagementPatternFilter (uint16_t filter_number, uint16_t *pattern_active) {
#if (USBD_CDC%Instance%_NCM_B_NUMBER_POWER_FILTERS != 0)
  *pattern_active = (NCM_State.power_filter_active[filter_number / 8] & (1U << (filter_number % 8))) ? 1 : 0;
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to configure device Ethernet packet filter settings.
// \param[in]   packet_filter_bitmap Packet Filter Bitmap.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetEthernetPacketFilter (uint16_t packet_filter_bitmap) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x01) != 0)
  int32_t status;
 
  // Add code for handling request
  PacketFilter = ((packet_filter_bitmap & 0x01U) ? ARM_ETH_MAC_ADDRESS_ALL       : 0) |
                 ((packet_filter_bitmap & 0x02U) ? ARM_ETH_MAC_ADDRESS_MULTICAST : 0) |
                 ((packet_filter_bitmap & 0x08U) ? ARM_ETH_MAC_ADDRESS_BROADCAST : 0);
 
  status = EthMac->Control(ARM_ETH_MAC_CONFIGURE,
                           LinkInfo.speed  << ARM_ETH_MAC_SPEED_Pos  |
                           LinkInfo.duplex << ARM_ETH_MAC_DUPLEX_Pos |
                           PacketFilter);
  if (status != ARM_DRIVER_OK) { return false; }
 
  NCM_State.packet_filter_bitmap = packet_filter_bitmap;
 
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to retrieve a statistic based on the feature selector.
// \param[in]   feature_selector     Feature Selector.
// \param[out]  data                 Pointer to Statistics Value.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetEthernetStatistic (uint16_t feature_selector, uint32_t *data) {
#if (USBD_CDC%Instance%_NCM_BM_ETHERNET_STATISTICS != 0)
  if (feature_selector == 0x00U) { return true;  }
  if (feature_selector >  0x1DU) { return false; }
  *data = NCM_State.eth_statistics[feature_selector - 1];
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to retrieve the parameters that describe NTBs for each direction.
// \param[out]  ntb_params           Pointer to NTB Parameter Structure.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetNtbParameters (CDC_NCM_NTB_PARAM *ntb_params) {
 
  ntb_params->wLength                 = sizeof(CDC_NCM_NTB_PARAM);
  ntb_params->bmNtbFormatsSupported   = USBD_CDC%Instance%_NCM_BM_NTB_FORMATS_SUPPORTED;
  ntb_params->dwNtbInMaxSize          = USBD_CDC%Instance%_NCM_DW_NTB_IN_MAX_SIZE;
  ntb_params->wNdpInDivisor           = USBD_CDC%Instance%_NCM_W_NDP_IN_DIVISOR;
  ntb_params->wNdpInPayloadRemainder  = USBD_CDC%Instance%_NCM_W_NDP_IN_PAYLOAD_REMINDER;
  ntb_params->wNdpInAlignment         = USBD_CDC%Instance%_NCM_W_NDP_IN_ALIGNMENT;
  ntb_params->Reserved0               = 0U;
  ntb_params->dwNtbOutMaxSize         = USBD_CDC%Instance%_NCM_DW_NTB_OUT_MAX_SIZE;
  ntb_params->wNdpOutDivisor          = USBD_CDC%Instance%_NCM_W_NDP_OUT_DIVISOR;
  ntb_params->wNdpOutPayloadRemainder = USBD_CDC%Instance%_NCM_W_NDP_OUT_PAYLOAD_REMINDER;
  ntb_params->wNdpOutAlignment        = USBD_CDC%Instance%_NCM_W_NDP_OUT_ALIGNMENT;
  ntb_params->Reserved1               = 0U;
 
  return true;
}
 
 
// Called upon USB Host request to return the USB Device’s current EUI-48 station address.
// \param[out]  net_addr             Pointer to EUI-48 current address, in network byte order.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetNetAddress (uint8_t *net_addr) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x02) != 0)
  memcpy(net_addr, &NCM_State.net_address, 6);
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to set the USB Device’s current EUI-48 station address.
// \param[in]   net_addr             Pointer to EUI-48 address, in network byte order.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetNetAddress (const uint8_t *net_addr) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x02) != 0)
  int32_t status;
 
  // Add code for handling request
  status = EthMac->SetMacAddress((ARM_ETH_MAC_ADDR *)net_addr);
  if (status != ARM_DRIVER_OK) { return false; }
 
  memcpy(&NCM_State.net_address, net_addr, 6);
 
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to return the NTB data format currently being used.
// \param[out]  ntb_format           Pointer to NTB format code.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetNtbFormat (uint16_t *ntb_format) {
  *ntb_format = NCM_State.ntb_format;
  return true;
}
 
 
// Called upon USB Host request to select the format of NTB to be used for NTBs transmitted to the USB Host.
// \param[in]   ntb_format           NTB format selection:
//                - value 0 :        NTB-16
//                - value 1 :        NTB-32
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetNtbFormat (uint16_t ntb_format) {
#if (USBD_CDC%Instance%_NCM_BM_NTB_FORMATS_SUPPORTED > 1)
  if (ntb_format > 1) { return false; }
#else
  if (ntb_format > 0) { return false; }
#endif
  NCM_State.ntb_format = ntb_format;
  return true;
}
 
 
// Called upon USB Host request to return NTB input size currently being used.
// \param[out]  ntb_input_size       Pointer to NTB input size.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetNtbInputSize (uint32_t *ntb_input_size) {
  *ntb_input_size = NCM_State.ntb_input_size;
  return true;
}
 
 
// Called upon USB Host request to select the maximum size of NTB that is permitted to be sent to the USB Host.
// \param[in]   ntb_input_size       Maximum NTB size.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetNtbInputSize (uint32_t ntb_input_size) {
  if (ntb_input_size > USBD_CDC%Instance%_NCM_DW_NTB_IN_MAX_SIZE) { return false; }
  NCM_State.ntb_input_size = ntb_input_size;
  return true;
}
 
 
// Called upon USB Host request to return the currently effective maximum datagram size.
// \param[out]  max_datagram_size    Pointer to current maximum datagram size.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetMaxDatagramSize (uint16_t *max_datagram_size) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x08) != 0)
  *max_datagram_size = NCM_State.max_datagram_size;
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to select the maximum datagram size that can be sent in an NTB.
// \param[in]   max_datagram_size    Maximum datagram size.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetMaxDatagramSize (uint16_t max_datagram_size) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x08) != 0)
  if (max_datagram_size > USBD_CDC%Instance%_NCM_W_MAX_SEGMENT_SIZE) { return false; }
  NCM_State.max_datagram_size = max_datagram_size;
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to return the currently selected CRC mode.
// \param[out]  crc_mode             Pointer to current CRC mode.
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_GetCrcMode (uint16_t *crc_mode) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x10) != 0)
  *crc_mode = NCM_State.crc_mode;
  return true;
#else
  return false;
#endif
}
 
 
// Called upon USB Host request to control CRC mode.
// \param[in]   crc_mode             CRC mode:
//                - value 0 :        CRCs shall not be appended
//                - value 1 :        CRCs shall be appended
// \return      true                 if this request was handled.
// \return      false                if this request was not handled.
bool USBD_CDC%Instance%_NCM_SetCrcMode (uint16_t crc_mode) {
#if ((USBD_CDC%Instance%_NCM_BM_NETWORK_CAPABILITIES & 0x10) != 0)
  if (crc_mode > 1) { return false; }
  NCM_State.crc_mode = crc_mode;
  return true;
#else
  return false;
#endif
}
 
 
// Called when NTB was successfully sent.
void USBD_CDC%Instance%_NCM_NTB_IN_Sent (void) {
  // Add code for handling request
  osSignalSet(DataIN_ThreadId, 1U);
}
 
// Called when NTB was successfully received.
void USBD_CDC%Instance%_NCM_NTB_OUT_Received (void) {
  // Add code for handling request
  osSignalSet(DataOUT_ThreadId, 1U);
}
 
//! [code_USBD_User_CDC_NCM_ETH]


// Called upon Ethernet MAC Event
static void EthMac_Notify (uint32_t event) {

  switch (event) {
    case ARM_ETH_MAC_EVENT_RX_FRAME:
      osSignalSet(DataIN_ThreadId, 2U);
      break;
    default:
      break;
  }
}


// Thread handling ETH Connection
static void Connection_Thread (void const *arg) {
  ARM_ETH_LINK_STATE link_state;
  osEvent            event;
  uint32_t           speed;
  uint16_t           state;
  int32_t            status;

  while (1) {
    event = osSignalWait(1U, 500U);
    link_state = EthPhy->GetLinkState();
    if (link_state == ARM_ETH_LINK_UP) {
      LinkInfo = EthPhy->GetLinkInfo();
      switch (LinkInfo.speed) {
        case 0:  speed =   10000000U; break;
        case 1:  speed =  100000000U; break;
        case 2:  speed = 1000000000U; break;
        default: speed = 0U;
      }
    } else {
      speed = 0U;
    }
    if (speed != LinkSpeed) {
      LinkSpeed = speed;
      if (link_state == ARM_ETH_LINK_UP) {
        do {
          status = USBD_CDC_NCM_Notify_ConnectionSpeedChange(USB_CDC_NUM, speed, speed);
        } while (status == -(usbDriverBusy));
      }
    }
    if (link_state != LinkState) {
      LinkState = link_state;
      if (link_state == ARM_ETH_LINK_UP) {
        EthMac->Control(ARM_ETH_MAC_CONFIGURE,
                        LinkInfo.speed  << ARM_ETH_MAC_SPEED_Pos  |
                        LinkInfo.duplex << ARM_ETH_MAC_DUPLEX_Pos |
                        PacketFilter);
        EthMac->Control(ARM_ETH_MAC_CONTROL_TX, 1U);
        EthMac->Control(ARM_ETH_MAC_CONTROL_RX, 1U);
      } else {
        EthMac->Control(ARM_ETH_MAC_FLUSH,
                        ARM_ETH_MAC_FLUSH_TX |
                        ARM_ETH_MAC_FLUSH_RX);
        EthMac->Control(ARM_ETH_MAC_CONTROL_TX, 0U);
        EthMac->Control(ARM_ETH_MAC_CONTROL_RX, 0U);
      }
      state = (link_state == ARM_ETH_LINK_UP) ? 1U : 0U;
      do {
        status = USBD_CDC_NCM_Notify_NetworkConnection(USB_CDC_NUM, state);
      } while (status == -(usbDriverBusy));
    }
    if (event.status == osEventSignal) {
      if (LinkState == ARM_ETH_LINK_UP) {
        do {
          status = USBD_CDC_NCM_Notify_ConnectionSpeedChange(USB_CDC_NUM, LinkSpeed, LinkSpeed);
        } while (status == -(usbDriverBusy));
      }
      state = (LinkState == ARM_ETH_LINK_UP) ? 1U : 0U;
      do {
        status = USBD_CDC_NCM_Notify_NetworkConnection(USB_CDC_NUM, state);
      } while (status == -(usbDriverBusy));
    }
  }
}

// Thread handling Data IN (ETH -> USB)
static void DataIN_Thread (void const *arg) {
  uint32_t size;
  int32_t  status;

  while (1) {
    osSignalWait(3U, osWaitForever);
    do {
      status = USBD_CDC_NCM_NTB_IN_Initialize(USB_CDC_NUM);
      if (status != usbOK) { break; }
      status = USBD_CDC_NCM_NTB_IN_CreateNDP(USB_CDC_NUM, MAX_IN_DATAGRAMS);
      if (status != usbOK) { break; }
      while (1) {
        if (FrameIN_Size != 0) {
          USBD_CDC_NCM_NTB_IN_WriteDatagram(USB_CDC_NUM, FrameIN, FrameIN_Size);
          FrameIN_Size = 0;
        }
        size = EthMac->GetRxFrameSize();
        if (size == 0U) { break; }
        if ((size < 14U) || (size > NCM_State.max_datagram_size)) {
          EthMac->ReadFrame(NULL, 0U);
          continue;
        }
        EthMac->ReadFrame(FrameIN, size);
        if (size > 0) {
          #if ((USBD_CDC%Instance%_NCM_BM_ETHERNET_STATISTICS & 0x00000002) != 0)
            NCM_State.eth_statistics[1]++;
          #endif
          status = USBD_CDC_NCM_NTB_IN_WriteDatagram(USB_CDC_NUM, FrameIN, size);
          if (status != usbOK) {
            FrameIN_Size = size;
            break;
          }
        }
      }
      USBD_CDC_NCM_NTB_IN_Send(USB_CDC_NUM);
    } while (FrameIN_Size);
  }
}

// Thread handling Data OUT (USB -> ETH)
static void DataOUT_Thread (void const *arg) {
  uint32_t size;
  int32_t  len, status;

  while (1) {
    osSignalWait(1U, osWaitForever);
    while (1) {
      status = USBD_CDC_NCM_NTB_OUT_ProcessNDP(USB_CDC_NUM);
      if (status != usbOK) { break; }
      while (1) {
        size = USBD_CDC_NCM_NTB_OUT_GetDatagramSize(USB_CDC_NUM);
        if (size == 0U) { break; }
        if ((size < 14U) || (size > NCM_State.max_datagram_size)) {
          USBD_CDC_NCM_NTB_OUT_ReadDatagram(USB_CDC_NUM, NULL, 0U);
          continue;
        }
        len = USBD_CDC_NCM_NTB_OUT_ReadDatagram(USB_CDC_NUM, FrameOUT, size);
        if (len > 0) {
          do {
            status = EthMac->SendFrame(FrameOUT, len, 0U);
          } while (status == ARM_DRIVER_ERROR_BUSY);
          #if ((USBD_CDC%Instance%_NCM_BM_ETHERNET_STATISTICS & 0x00000001) != 0)
            NCM_State.eth_statistics[0]++;
          #endif
        }
      }
    }
    USBD_CDC_NCM_NTB_OUT_Release(USB_CDC_NUM);
  }
}
