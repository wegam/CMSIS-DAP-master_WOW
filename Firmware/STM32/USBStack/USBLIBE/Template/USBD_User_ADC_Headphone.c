/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_User_ADC_Headphone_%Instance%.c
 * Purpose: USB Device Audio Device Class (ADC) User module
 *          Template for USB Audio Device Class (ADC) Headphone
 * Rev.:    V6.3
 *----------------------------------------------------------------------------*/
/**
 * \addtogroup usbd_adcFunctions
 *
 * USBD_User_ADC_Headphone_%Instance%.c implements the application specific 
 * functionality of the Audio class and is used to create an USB Audio device
 * containing stereo speakers and mono microphone.
 *
 * The implementation must match the configuration file USBD_Config_ADC_%Instance%.h.
 * The following values in USBD_Config_ADC_%Instance%.h affect the user code:
 *
 *  - 'Isochronous OUT Endpoint Settings' specifies speaker availability
 *
 *     - 'Maximum Endpoint Packet Size (in bytes)' must be larger than samples data per
 *        polling interval
 *
 *  - 'Isochronous IN Endpoint Settings' specifies microphone availability
 *
 *     - 'Maximum Endpoint Packet Size (in bytes)' must be larger than samples data per
 *        polling interval
 *
 *  - 'Audio Control Interface String' specifies device name
 *
 *     - 'Audio Output Settings (Speaker)'
 *
 *       - 'Channel Configuration' specifies if speaker is mono or stereo
 *
 *       - 'Sample Frequency (in Hz)' specifies sampling frequency for speaker samples
 *
 *       - 'Audio Subframe Size' specifies speaker sample size in bytes
 *
 *       - 'Sample Resolution' specifies resolution of speaker samples (in bits)
 *
 *       - 'Buffer Size (in samples)' specifies intermediate buffer size used for buffering speaker data
 *
 *     - 'Audio Input Settings (Microphone)'
 *
 *       - 'Channel Configuration' specifies if microphone is mono or stereo
 *
 *       - 'Sample Frequency (in Hz)' specifies sampling frequency for microphone samples
 *
 *       - 'Audio Subframe Size' specifies microphone sample size in bytes
 *
 *       - 'Sample Resolution' specifies resolution of microphone samples (in bits)
 *
 *       - 'Buffer Size (in samples)' specifies intermediate buffer size used for buffering microphone data
 *
 *
 * Settings in USBD_Config_ADC_%Instance%.h corresponding to this template:
 *
 * #define USBD_ADC%Instance%_DEV                       0
 * #define USBD_ADC%Instance%_EP_ISO_OUT_EN             1
 * #define USBD_ADC%Instance%_EP_ISO_OUT                1
 * #define USBD_ADC%Instance%_EP_ISO_OUT_WMAXPACKETSIZE 128
 * #define USBD_ADC%Instance%_EP_ISO_OUT_BINTERVAL      1
 * #define USBD_ADC%Instance%_EP_ISO_IN_EN              1
 * #define USBD_ADC%Instance%_EP_ISO_IN                 2
 * #define USBD_ADC%Instance%_EP_ISO_IN_WMAXPACKETSIZE  64
 * #define USBD_ADC%Instance%_EP_ISO_IN_BINTERVAL       1
 * #define USBD_ADC%Instance%_CIF_STR_DESC              L"USB_ADC0"
 * #define USBD_ADC%Instance%_OUT_SIF_STR0_DESC         L"USB_ADC0_SPKR_OFF"
 * #define USBD_ADC%Instance%_OUT_SIF_STR1_DESC         L"USB_ADC0_SPKR_ON"
 * #define USBD_ADC%Instance%_OUT_CH_NUM                2
 * #define USBD_ADC%Instance%_OUT_TSAM_FREQ             32000
 * #define USBD_ADC%Instance%_OUT_BSUBFRAMESIZE         2
 * #define USBD_ADC%Instance%_OUT_BBITRESOLUTION        16
 * #define USBD_ADC%Instance%_OUT_BUF_SIZE              1024
 * #define USBD_ADC%Instance%_IN_SIF_STR0_DESC          L"USB_ADC0_MIC_OFF"
 * #define USBD_ADC%Instance%_IN_SIF_STR1_DESC          L"USB_ADC0_MIC_ON"
 * #define USBD_ADC%Instance%_IN_CH_NUM                 1
 * #define USBD_ADC%Instance%_IN_TSAM_FREQ              32000
 * #define USBD_ADC%Instance%_IN_BSUBFRAMESIZE          2
 * #define USBD_ADC%Instance%_IN_BBITRESOLUTION         16
 * #define USBD_ADC%Instance%_IN_BUF_SIZE               512
 * #define USBD_ADC%Instance%_THREAD_STACK_SIZE         512
 * #define USBD_ADC%Instance%_THREAD_PRIORITY           osPriorityAboveNormal
 *
 *
 * The following constants in this module affect the module functionality:
 *
 *  - RECORD_CHANNELS:                         specifies number of audio channels for microphone (only mono = 1 is supported)
 *
 *  - RECORD_BUFFER_SIZE_AUDIO:                specifies number of samples buffered for microphone
 *
 *  - RECORD_SAMPLE_CORRECTION_COUNTER:        specifies interval for adding or removing 1 sample for microphone
 *                                             (is used to correct clock differences between USB clock and Audio Interface input clock)
 *
 *  - PLAYBACK_CHANNELS:                       specifies number of audio channels for speakers (only stereo = 2 is supported)
 *
 *  - PLAYBACK_BUFFER_SIZE_AUDIO:              specifies number of samples buffered for speakers
 *
 *  - PLAYBACK_SAMPLE_CORRECTION_COUNTER:      specifies interval for adding or removing 1 sample for speakers
 *                                             (is used to correct clock differences between USB clock and Audio Interface output clock)
 *
 * If different configuration then mono microphone and stereo speakers is to be used re-sampling implementation has to be adjusted.
 *
 */
 
 
//! [code_USBD_User_ADC_Headphone]
 
#include <stdint.h>
#include <stdbool.h>
#include "rl_usb.h"
 
#include ".\RTE\USB\USBD_Config_ADC_%Instance%.h"
 
#include "Board_Audio.h"
 
#define  RECORD_BUFFER_SIZE_USB             (USBD_ADC0_IN_BUF_SIZE)
#define  PLAYBACK_BUFFER_SIZE_USB           (USBD_ADC0_OUT_BUF_SIZE)
 
#define  RECORD_CHANNELS                       1        // Mono microphone = 1 channel (stereo not implemented)
#define  RECORD_BUFFER_SIZE_AUDIO             64        // In samples (64 mono samples at 32 kHz = 2 ms of samples)
#define  RECORD_SAMPLE_CORRECTION_COUNTER   (100/2)     // 100 ms / 2 ms of samples (compensates 625 ppm clock difference)
#define  PLAYBACK_CHANNELS                     2        // Stereo speakers = 2 channels (mono not implemented)
#define  PLAYBACK_BUFFER_SIZE_AUDIO          128        // Out samples (128 stereo samples at 32 kHz = 2 ms samples)
#define  PLAYBACK_SAMPLE_CORRECTION_COUNTER (100/2)     // 100 ms / 2 ms of samples (compensates 625 ppm clock difference)
 
 
static          osThreadId play_buf_tid                              =   0  ;
static volatile bool       play                                      = false;
static          uint8_t    play_buf_index                            =   0  ;
static          int16_t    play_buf[2][PLAYBACK_BUFFER_SIZE_AUDIO+2] = { 0 };
static          int32_t    play_num                                  = { 0 };
static          int32_t    play_add                                  =   0  ;
static          uint16_t   play_sample_correction_cnt                =   0  ;
 
static          uint8_t    rec_buf_index                             =   0  ;
static          int16_t    rec_buf[2][RECORD_BUFFER_SIZE_AUDIO+1]    = { 0 };
static          int32_t    rec_num                                   =   0  ;
static          int32_t    rec_add                                   =   0  ;
static          uint16_t   rec_sample_correction_cnt                 =   0  ;
 
 
// Thread: waits for USB buffer to be half full of samples and then starts playback.
// \param[in]     arg           not used.
void AudioPlaybackInitialBufferingThread%Instance% (void const *arg) {
  uint32_t play_samples_available;
  int32_t  play_num0;
 
  while (1) {
    play_samples_available = USBD_ADC_ReceivedSamplesAvailable (%Instance%);
    if (!play && (play_samples_available > (PLAYBACK_BUFFER_SIZE_USB / 2))) {
      // If play is not active and USB buffer is half full of samples
      play      = true;
      play_num0 = USBD_ADC_ReadSamples (%Instance%, (void *)(&play_buf[0][0]), PLAYBACK_BUFFER_SIZE_AUDIO);
      play_num  = USBD_ADC_ReadSamples (%Instance%, (void *)(&play_buf[1][0]), PLAYBACK_BUFFER_SIZE_AUDIO);
      play_buf_index = 1;
      // Send initial data, further sending will happen from audio callback
      Audio_SendData (&play_buf[0][0], play_num0);
    }
    if (play && !play_samples_available) {
      // If play was active but there is no more samples than play has stopped
      play = false;
    }
    osDelay(10);
  }
}
osThreadDef (AudioPlaybackInitialBufferingThread%Instance%, osPriorityNormal, 1, 0);
 
// Audio Events Handling Callback function
// \param[in]   event  notification mask
static void AudioCallback (uint32_t event) {
  uint32_t rec_samples_pending;
  int32_t  rec_num_last;
  uint8_t  rec_correct_sample;
  uint32_t play_samples_available;
  int32_t  play_num_last;
  uint8_t  play_correct_sample;
 
  // Handling of recording samples
  if (event & AUDIO_EVENT_RECEIVE_COMPLETE) {
    rec_num_last = rec_num;
    rec_num      = RECORD_BUFFER_SIZE_AUDIO;
    // Start new audio data reception
    Audio_ReceiveData (&rec_buf[rec_buf_index ^ 1][0], rec_num);
 
    rec_correct_sample = 0;
    if (rec_sample_correction_cnt++ >= RECORD_SAMPLE_CORRECTION_COUNTER) {
      // Correction interval counter for example if interval is 50 ms
      // the clock difference of 625 ppm will be compensated at 32 kHz
      // sampling rate
      rec_sample_correction_cnt = 0;
      rec_correct_sample        = 1;
    }
 
    rec_samples_pending = USBD_ADC_WrittenSamplesPending (%Instance%);
    if         (rec_samples_pending <   RECORD_BUFFER_SIZE_USB/8) {
      rec_add =  0;
    } else if  (rec_samples_pending <   RECORD_BUFFER_SIZE_USB/4) {
      rec_add =  1;
    } else if ((rec_samples_pending > 3*RECORD_BUFFER_SIZE_USB/8) &&
               (rec_samples_pending < 5*RECORD_BUFFER_SIZE_USB/8)) {
      rec_add =  0;
    } else if  (rec_samples_pending > 3*RECORD_BUFFER_SIZE_USB/4) {
      rec_add = -1;
    }
    if (rec_correct_sample) {           // Correct sample interval is active
      if (rec_add == -1) {              // Removing 1 sample (1 sample for mono microphone)
        // Sample N-2 is average of N-3, N-2, N-1 and N samples
        rec_buf[rec_buf_index][rec_num_last-2] = (rec_buf[rec_buf_index][rec_num_last-3] +
                                                  rec_buf[rec_buf_index][rec_num_last-2] +
                                                  rec_buf[rec_buf_index][rec_num_last-1] +
                                                  rec_buf[rec_buf_index][rec_num_last  ])/4;
        // Sample N moved to N-1
        rec_buf[rec_buf_index][rec_num_last-1] =  rec_buf[rec_buf_index][rec_num_last  ];
      }
      if (rec_add == 1) {               // Adding 1 new sample (1 sample for mono microphone)
        // Sample N moved to N+1
        rec_buf[rec_buf_index][rec_num_last+1] =  rec_buf[rec_buf_index][rec_num_last  ];
        // Sample N is average of N-1 and N+1 samples
        rec_buf[rec_buf_index][rec_num_last]   = (rec_buf[rec_buf_index][rec_num_last-1] +
                                                  rec_buf[rec_buf_index][rec_num_last+1])/2;
      }
    }
    // Send last received buffer of samples to USB
    USBD_ADC_WriteSamples (%Instance%, &rec_buf[rec_buf_index][0], rec_num_last + (rec_add*RECORD_CHANNELS*rec_correct_sample));
    rec_buf_index ^= 1;                 // Change active buffer index
  }
 
  // Handling of playback samples
  if (event & AUDIO_EVENT_SEND_COMPLETE) {
    if (play) {
      play_num_last = play_num;

      play_correct_sample = 0;
      if (play_sample_correction_cnt++ >= PLAYBACK_SAMPLE_CORRECTION_COUNTER) {
        // Correction interval counter for example if interval is 50 ms
        // the clock difference of 625 ppm will be compensated at 32 kHz
        // sampling rate
        play_sample_correction_cnt = 0;
        play_correct_sample        = 1;
      }
 
      play_samples_available = USBD_ADC_ReceivedSamplesAvailable (0);
      if         (play_samples_available <   PLAYBACK_BUFFER_SIZE_USB/8) {
        rec_add =  0;
      } else if  (play_samples_available <   PLAYBACK_BUFFER_SIZE_USB/4) {
        rec_add =  1;
      } else if ((play_samples_available > 3*PLAYBACK_BUFFER_SIZE_USB/8) &&
                 (play_samples_available < 5*PLAYBACK_BUFFER_SIZE_USB/8)) {
        rec_add =  0;
      } else if  (play_samples_available > 3*PLAYBACK_BUFFER_SIZE_USB/4) {
        rec_add = -1;
      }
      if (play_correct_sample) {        // Correct sample interval is active
        if (play_add == -1) {           // Removing 1 sample (actually 2 for stereo (1 for each channel))
          if (play_num >= 8) {
            // Sample N-2 is average of N-3, N-2, N-1 and N samples
            play_buf[play_buf_index][play_num-6] = (play_buf[play_buf_index][play_num-8] +
                                                    play_buf[play_buf_index][play_num-6] +
                                                    play_buf[play_buf_index][play_num-4] +
                                                    play_buf[play_buf_index][play_num-2])/4;
            play_buf[play_buf_index][play_num-5] = (play_buf[play_buf_index][play_num-7] +
                                                    play_buf[play_buf_index][play_num-5] +
                                                    play_buf[play_buf_index][play_num-3] +
                                                    play_buf[play_buf_index][play_num-1])/4;
            // Sample N moved to N-1
            play_buf[play_buf_index][play_num-4] =  play_buf[play_buf_index][play_num-2];
            play_buf[play_buf_index][play_num-3] =  play_buf[play_buf_index][play_num-1];
          }
        }
        if (play_add == 1) {            // Adding 1 new sample (actually 2 for stereo (1 for each channel))
          if (play_num >= 4) {
            // Sample N moved to N+1
            play_buf[play_buf_index][play_num]   =  play_buf[play_buf_index][play_num-2];
            play_buf[play_buf_index][play_num+1] =  play_buf[play_buf_index][play_num-1];
            // Sample N is average of N-1 and N+1 samples
            play_buf[play_buf_index][play_num-2] = (play_buf[play_buf_index][play_num-4]   +
                                                    play_buf[play_buf_index][play_num  ])/2;
            play_buf[play_buf_index][play_num-1] = (play_buf[play_buf_index][play_num-3] +
                                                    play_buf[play_buf_index][play_num+1])/2;
          }
        }
      }
      if (play_num_last > 0) {
        // Start new audio data transmission
        Audio_SendData (&play_buf[play_buf_index][0], play_num + (play_add*PLAYBACK_CHANNELS*play_correct_sample));
        play_buf_index ^= 1;            // Change active buffer index
        // Read next buffer of samples from USB
        play_num = USBD_ADC_ReadSamples (%Instance%, (void *)(&play_buf[play_buf_index][0]), PLAYBACK_BUFFER_SIZE_AUDIO);
      }
    }
  }
}
 
// Called during USBD_Initialize to initialize the USB ADC class instance.
void USBD_ADC%Instance%_Initialize (void) {
 
  // Set stereo speakers volume range to 0 to 100 with step 1, initially positioned at 50 %
  USBD_ADC_SpeakerSetVolumeRange (%Instance%, 0, 0, 100, 1, 50);

  // Initialize audio codec for: 
  //   - stereo speakers
  //   - sampling rate 32 kHz
  //   - 16 bits per sample
  //   - not muted
  //   - volume at 50 %
  //
  //  NOTE !!!
  //  - These values must correspond to settings in USBD_Config_ADC_%Instance%.h file
  Audio_Initialize        (&AudioCallback);
  Audio_SetDataFormat     (AUDIO_STREAM_OUT, AUDIO_DATA_16_STEREO);
  Audio_SetFrequency      (AUDIO_STREAM_OUT, 32000);
  Audio_SetMute           (AUDIO_STREAM_OUT, AUDIO_CHANNEL_MASTER, false);
  Audio_SetVolume         (AUDIO_STREAM_OUT, AUDIO_CHANNEL_MASTER, 50);
  Audio_Start             (AUDIO_STREAM_OUT);
 
  // Set microphone volume range to 0 to 100 with step 1, initially positioned at 50 %
  USBD_ADC_MicrophoneSetVolumeRange (%Instance%, 0, 0, 100, 1, 50);

  // Initialize audio codec for: 
  //   - mono microphone
  //   - sampling rate 32 kHz
  //   - 16 bits per sample
  //   - not muted
  //   - volume at 50 %
  //
  //  NOTE !!!
  //  - These values must correspond to settings in USBD_Config_ADC_%Instance%.h file
  Audio_SetFrequency      (AUDIO_STREAM_IN,  32000);
  Audio_SetDataFormat     (AUDIO_STREAM_IN,  AUDIO_DATA_16_MONO);
  Audio_SetMute           (AUDIO_STREAM_IN,  AUDIO_CHANNEL_MASTER, false);
  Audio_SetVolume         (AUDIO_STREAM_IN,  AUDIO_CHANNEL_MASTER, 50);
}
 
// Called during USBD_Uninitialize to de-initialize the USB ADC class instance.
void USBD_ADC%Instance%_Uninitialize (void) {
  Audio_Uninitialize ();
}
 
// Callback function called when speaker activity (interface) setting changed event.
// \param[in]     active        activity status.
void USBD_ADC%Instance%_SpeakerStatusEvent (bool active) {
  if (active) {                         // If playback was activated
    Audio_Start (AUDIO_STREAM_OUT);     // Start playback audio stream
                                        // Start initial playback samples buffering thread
    play_buf_tid = osThreadCreate (osThread (AudioPlaybackInitialBufferingThread%Instance%), NULL);
  } else {                              // If playback was de-activated
    if (play_buf_tid) {                 // If initial playback samples buffering thread is active
                                        // Kill initial playback samples buffering thread
      if (osThreadTerminate (play_buf_tid) == osOK) { play_buf_tid = 0; }
    }
    Audio_Stop  (AUDIO_STREAM_OUT);     // Stop playback audio stream
  }
}
 
// Callback function called when speaker mute setting changed event.
// \param[in]     ch            channel index.
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_SpeakerMuteEvent (uint8_t ch, bool cur) {
  Audio_SetMute (AUDIO_STREAM_OUT, AUDIO_CHANNEL_MASTER, cur);
}
 
// Callback function called when speaker volume setting changed event.
// \param[in]     ch            channel index.
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_SpeakerVolumeEvent (uint8_t ch, uint16_t cur) {
  Audio_SetVolume (AUDIO_STREAM_OUT, ch, cur);
}
 
// Callback function called when microphone activity (interface) setting changed event.
// \param[in]     active        activity status.
void USBD_ADC%Instance%_MicrophoneStatusEvent (bool active) {
  if (active) {                         // If recording was activated
    rec_num = RECORD_BUFFER_SIZE_AUDIO; // Receive samples
    rec_buf_index = 0;                  // Current receiving buffer index is 0
    Audio_ReceiveData(&rec_buf[0][0],rec_num);// Start initial audio data reception
    Audio_Start (AUDIO_STREAM_IN);      // Start recording audio stream
  } else {                              // If recording was de-activated
    Audio_Stop  (AUDIO_STREAM_IN);      // Stop recording audio stream
  }
}
 
// Callback function called when microphone mute setting changed event.
// \param[in]     ch            channel index.
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_MicrophoneMuteEvent (uint8_t ch, bool cur) {
  Audio_SetMute (AUDIO_STREAM_IN, AUDIO_CHANNEL_MASTER, cur);
}
 
// Callback function called when microphone volume setting changed event.
// \param[in]     ch            channel index.
// \param[in]     cur           current setting.
void USBD_ADC%Instance%_MicrophoneVolumeEvent (uint8_t ch, uint16_t cur) {
  Audio_SetVolume (AUDIO_STREAM_IN, ch, cur);
}
 
//! [code_USBD_User_ADC_Headphone]
