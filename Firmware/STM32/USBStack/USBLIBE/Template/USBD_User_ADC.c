/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_User_ADC_%Instance%.c
 * Purpose: USB Device Audio Device Class (ADC) User module
 * Rev.:    V6.2
 *----------------------------------------------------------------------------*/
/**
 * \addtogroup usbd_adcFunctions
 *
 */
 
 
//! [code_USBD_User_ADC]
 
#include <stdint.h>
#include <stdbool.h>
#include "rl_usb.h"
 
// Called during USBD_Initialize to initialize the USB ADC class instance.
void USBD_ADC%Instance%_Initialize (void) {
  // Add code for initialization
}
 
// Called during USBD_Uninitialize to de-initialize the USB ADC class instance.
void USBD_ADC%Instance%_Uninitialize (void) {
  // Add code for de-initialization
}
 
// Callback function called when speaker activity (interface) setting changed event.
// \param[in]     active        activity status.
void USBD_ADC%Instance%_SpeakerStatusEvent (bool active) {
  // Add code for speaker activity setting change
}
 
// Callback function called when speaker mute setting changed event.
// \param[in]     ch            channel index.
//                                - value 0: master channel
//                                - value 1: left speaker (in stereo mode)
//                                - value 2: right speaker (in stereo mode)
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_SpeakerMuteEvent (uint8_t ch, bool cur) {
  // Add code for speaker mute setting change
}
 
// Callback function called when speaker volume setting changed event.
// \param[in]     ch            channel index.
//                                - value 0: master channel
//                                - value 1: left speaker (in stereo mode)
//                                - value 2: right speaker (in stereo mode)
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_SpeakerVolumeEvent (uint8_t ch, uint16_t cur) {
  // Add code for speaker volume setting change
}
 
// Callback function called when microphone activity (interface) setting changed event.
// \param[in]     active        activity status.
void USBD_ADC%Instance%_MicrophoneStatusEvent (bool active) {
  // Add code for microphone activity setting change
}
 
// Callback function called when microphone mute setting changed event.
// \param[in]     ch            channel index.
//                                - value 0: master channel
//                                - value 1: left microphone (in stereo mode)
//                                - value 2: right microphone (in stereo mode)
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_MicrophoneMuteEvent (uint8_t ch, bool cur) {
  // Add code for microphone mute setting change
}
 
// Callback function called when microphone volume setting changed event.
// \param[in]     ch            channel index.
//                                - value 0: master channel
//                                - value 1: left microphone (in stereo mode)
//                                - value 2: right microphone (in stereo mode)
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_MicrophoneVolumeEvent (uint8_t ch, uint16_t cur) {
  // Add code for microphone volume setting change
}
 
//! [code_USBD_User_ADC]
