/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbh_config_hc_2.c
 * Purpose: USB Host Host Controller 2 Data and Settings
 * Rev.:    V6.4.1
 *----------------------------------------------------------------------------*/

#if     (USBH2_HC_IF == 0)              // Custom

#if     (USBH2_HC_MEM_POOL_RELOC == 1)
#define  __AT_MEM2(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM2(x)
#endif
#define  __ALIGNED_MEM2(x)                          __attribute__((aligned(x)))

#ifndef  USBH2_HC_PIPE_NUM
#define  USBH2_HC_PIPE_NUM                            USBH2_HC_ENDPOINT_NUM
#endif

#if     (USBH2_HC_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 2 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh2_pipe             [USBH2_HC_PIPE_NUM];
         USBH_PIPE_TID_t      usbh2_pipe_tid         [USBH2_HC_PIPE_NUM];
const    uint32_t             usbh2_pipe_num =        USBH2_HC_PIPE_NUM;

const    uint32_t             usbh2_transfer_num =    USBH2_HC_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER(USBH2_HC_NUM);
const    ARM_DRIVER_USBH     *usbh2_hcd_ptr  =       &USBHn_DRIVER(USBH2_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh2_hci_hcd_ptr =     NULL;

const    uint8_t              usbh2_mem_pool_reloc =  USBH2_HC_MEM_POOL_RELOC;
         uint32_t             usbh2_mem_pool        [(USBH2_HC_MEM_POOL_SIZE + 8 * USBH2_HC_TRANSFER_NUM + 32 + 4 +3)/4] __AT_MEM2(USBH2_HC_MEM_POOL_ADDR);
const    uint32_t             usbh2_mem_pool_size = ((USBH2_HC_MEM_POOL_SIZE + 8 * USBH2_HC_TRANSFER_NUM + 32 + 4 +3)/4)*4;

         USBH_HC_t            usbh2_hc       =      { USBH2_HC_PIPE_NUM };
         USBH_HC_t           *usbh2_hc_ptr   =       &usbh2_hc;
         USBH_OHCI_t         *usbh2_ohci_ptr =        NULL;
         USBH_EHCI_t         *usbh2_ehci_ptr =        NULL;

#elif   (USBH2_HC_IF == 1)              // OHCI

#if     (USBH2_HC_OHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM2(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM2(x)
#endif
#define  __ALIGNED_MEM2(x)                          __attribute__((aligned(x)))

#ifndef  USBH2_HC_OHCI_PIPE_NUM
#define  USBH2_HC_OHCI_PIPE_NUM                       USBH2_HC_OHCI_ENDPOINT_NUM
#endif

#if     (USBH2_HC_OHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 2 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh2_pipe             [USBH2_HC_OHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh2_pipe_tid         [USBH2_HC_OHCI_PIPE_NUM];
const    uint32_t             usbh2_pipe_num =        USBH2_HC_OHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh2_transfer_info    [USBH2_HC_OHCI_TRANSFER_NUM];
const    uint32_t             usbh2_transfer_num =    USBH2_HC_OHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_OHCI_LIB(2);
const    ARM_DRIVER_USBH     *usbh2_hcd_ptr =        &USBHn_DRIVER_OHCI_LIB(2);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH2_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh2_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH2_HC_NUM);

#define  USBH2_OHCI_MEM_HCCA                         (USBH2_HC_OHCI_MEM_POOL_ADDR)
#define  USBH2_OHCI_MEM_HCCA_SIZE                    (256)
#define  USBH2_OHCI_MEM_ED                           (USBH2_OHCI_MEM_HCCA + USBH2_OHCI_MEM_HCCA_SIZE)
#define  USBH2_OHCI_MEM_ED_SIZE                      (USBH2_HC_OHCI_PIPE_NUM*16)
#define  USBH2_OHCI_MEM_TD                           (USBH2_OHCI_MEM_ED   + USBH2_OHCI_MEM_ED_SIZE)
#define  USBH2_OHCI_MEM_TD_SIZE                      (USBH2_HC_OHCI_TRANSFER_NUM*16)
#define  USBH2_OHCI_MEM_POOL_ADDR                    (USBH2_OHCI_MEM_HCCA + USBH2_OHCI_MEM_HCCA_SIZE + USBH2_OHCI_MEM_ED_SIZE + USBH2_OHCI_MEM_TD_SIZE)
#define  USBH2_OHCI_MEM_POOL_SIZE                    (USBH2_HC_OHCI_MEM_POOL_SIZE + 8 * USBH2_HC_TRANSFER_NUM +32 + 4)

         uint32_t             usbh2_ohci_hcca       [(USBH2_OHCI_MEM_HCCA_SIZE +3)/4] __AT_MEM2(USBH2_OHCI_MEM_HCCA) __ALIGNED_MEM2(256);
         uint32_t             usbh2_ohci_ed         [(USBH2_OHCI_MEM_ED_SIZE   +3)/4] __AT_MEM2(USBH2_OHCI_MEM_ED)   __ALIGNED_MEM2(16);
         uint32_t             usbh2_ohci_td         [(USBH2_OHCI_MEM_TD_SIZE   +3)/4] __AT_MEM2(USBH2_OHCI_MEM_TD)   __ALIGNED_MEM2(16);
const    uint8_t              usbh2_mem_pool_reloc =  USBH2_HC_OHCI_MEM_POOL_RELOC;
         uint32_t             usbh2_mem_pool        [(USBH2_OHCI_MEM_POOL_SIZE +3)/4] __AT_MEM2(USBH2_OHCI_MEM_POOL_ADDR);
const    uint32_t             usbh2_mem_pool_size = ((USBH2_OHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_OHCI_t          usbh2_ohci = {         (uint32_t *)USBH2_HC_OHCI_BASE_ADDRESS,
                                                      USBH2_HC_OHCI_PIPE_NUM,
                                                      USBH2_HC_OHCI_TRANSFER_NUM,
                                                      0,
                                                     &usbh2_ohci_hcca[0],
                                                     &usbh2_ohci_ed[0],
                                                     &usbh2_ohci_td[0],
                                                      NULL,
                                                     &usbh2_transfer_info[0] };
         USBH_HC_t           *usbh2_hc_ptr   =        NULL;
         USBH_OHCI_t         *usbh2_ohci_ptr =       &usbh2_ohci;
         USBH_EHCI_t         *usbh2_ehci_ptr =        NULL;

#elif   (USBH2_HC_IF == 2)              // NXP EHCI with extensions for full/low-speed support

#if     (USBH2_HC_EHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM2(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM2(x)
#endif
#define  __ALIGNED_MEM2(x)                          __attribute__((aligned(x)))

#ifndef  USBH2_HC_EHCI_PIPE_NUM
#define  USBH2_HC_EHCI_PIPE_NUM                       USBH2_HC_EHCI_ENDPOINT_NUM
#endif

#if     (USBH2_HC_EHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 2 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh2_pipe             [USBH2_HC_EHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh2_pipe_tid         [USBH2_HC_EHCI_PIPE_NUM];
const    uint32_t             usbh2_pipe_num =        USBH2_HC_EHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh2_transfer_info    [USBH2_HC_EHCI_TRANSFER_NUM];
const    uint32_t             usbh2_transfer_num =    USBH2_HC_EHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_EHCI_LIB(2);
const    ARM_DRIVER_USBH     *usbh2_hcd_ptr =        &USBHn_DRIVER_EHCI_LIB(2);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH2_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh2_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH2_HC_NUM);

#define  USBH2_EHCI_MEM_PFL                          (USBH2_HC_EHCI_MEM_POOL_ADDR + (((_USBH2_HC_EHCI_MEM_POOL_SIZE + 3)/4)*4))
#define  USBH2_EHCI_MEM_PFL_SIZE                     (4096)
#define  USBH2_EHCI_MEM_QH                           (USBH2_EHCI_MEM_PFL  + USBH2_EHCI_MEM_PFL_SIZE)
#define  USBH2_EHCI_MEM_QH_SIZE                      (USBH2_HC_EHCI_PIPE_NUM*64)
#define  USBH2_EHCI_MEM_QTD                          (USBH2_EHCI_MEM_QH   + USBH2_EHCI_MEM_QH_SIZE)
#define  USBH2_EHCI_MEM_QTD_SIZE                     (USBH2_HC_EHCI_TRANSFER_NUM*32)
#define  USBH2_EHCI_MEM_POOL_ADDR                    (USBH2_EHCI_MEM_PFL + USBH2_EHCI_MEM_PFL_SIZE + USBH2_OHCI_MEM_QH_SIZE + USBH2_OHCI_MEM_QTD_SIZE)
#define  USBH2_EHCI_MEM_POOL_SIZE                    (USBH2_HC_EHCI_MEM_POOL_SIZE + 8 * USBH2_HC_TRANSFER_NUM + 32 + 4)

         uint32_t             usbh2_ehci_pfl        [(USBH2_EHCI_MEM_PFL_SIZE  +3)/4] __AT_MEM2(USBH2_EHCI_MEM_PFL) __ALIGNED_MEM2(4096);
         uint32_t             usbh2_ehci_qh         [(USBH2_EHCI_MEM_QH_SIZE   +3)/4] __AT_MEM2(USBH2_EHCI_MEM_QH)  __ALIGNED_MEM2(64);
         uint32_t             usbh2_ehci_qtd        [(USBH2_EHCI_MEM_QTD_SIZE  +3)/4] __AT_MEM2(USBH2_EHCI_MEM_QTD) __ALIGNED_MEM2(32);
const    uint8_t              usbh2_mem_pool_reloc =  USBH2_HC_EHCI_MEM_POOL_RELOC;
         uint32_t             usbh2_mem_pool        [(USBH2_EHCI_MEM_POOL_SIZE +3)/4] __AT_MEM2(USBH2_EHCI_MEM_POOL_ADDR);
const    uint32_t             usbh2_mem_pool_size = ((USBH2_EHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_EHCI_t          usbh2_ehci = {         (uint32_t *)USBH2_HC_EHCI_BASE_ADDRESS,
                                                      USBH2_HC_EHCI_PIPE_NUM,
                                                      USBH2_HC_EHCI_TRANSFER_NUM,
                                                      0,
                                                      0,
                                                      1024,
                                                     &usbh2_ehci_pfl[0],
                                                     &usbh2_ehci_qh[0],
                                                     &usbh2_ehci_qtd[0],
                                                      NULL,
                                                      NULL,
                                                      NULL,
                                                     &usbh2_transfer_info[0] };
         USBH_HC_t           *usbh2_hc_ptr   =        NULL;
         USBH_EHCI_t         *usbh2_ehci_ptr =       &usbh2_ehci;
         USBH_OHCI_t         *usbh2_ohci_ptr =        NULL;
#endif

extern  void USBH2_Core_Thread                        (void const *arg);
#ifndef USBH2_CORE_THREAD_STACK_SIZE
#define USBH2_CORE_THREAD_STACK_SIZE                  0
#endif
#ifndef USBH2_CORE_THREAD_PRIORITY
#define USBH2_CORE_THREAD_PRIORITY                    osPriorityAboveNormal
#endif
osThreadDef(USBH2_Core_Thread, USBH2_CORE_THREAD_PRIORITY, 1, USBH2_CORE_THREAD_STACK_SIZE);
