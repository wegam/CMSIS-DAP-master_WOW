/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbh_config_hc_3.c
 * Purpose: USB Host Host Controller 3 Data and Settings
 * Rev.:    V6.4.1
 *----------------------------------------------------------------------------*/

#if     (USBH3_HC_IF == 0)              // Custom

#if     (USBH3_HC_MEM_POOL_RELOC == 1)
#define  __AT_MEM3(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM3(x)
#endif
#define  __ALIGNED_MEM3(x)                          __attribute__((aligned(x)))

#ifndef  USBH3_HC_PIPE_NUM
#define  USBH3_HC_PIPE_NUM                            USBH3_HC_ENDPOINT_NUM
#endif

#if     (USBH3_HC_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 3 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh3_pipe             [USBH3_HC_PIPE_NUM];
         USBH_PIPE_TID_t      usbh3_pipe_tid         [USBH3_HC_PIPE_NUM];
const    uint32_t             usbh3_pipe_num =        USBH3_HC_PIPE_NUM;

const    uint32_t             usbh3_transfer_num =    USBH3_HC_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER(USBH3_HC_NUM);
const    ARM_DRIVER_USBH     *usbh3_hcd_ptr  =       &USBHn_DRIVER(USBH3_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh3_hci_hcd_ptr =     NULL;

const    uint8_t              usbh3_mem_pool_reloc =  USBH3_HC_MEM_POOL_RELOC;
         uint32_t             usbh3_mem_pool        [(USBH3_HC_MEM_POOL_SIZE + 8 * USBH3_HC_TRANSFER_NUM + 32 + 4 +3)/4] __AT_MEM3(USBH3_HC_MEM_POOL_ADDR);
const    uint32_t             usbh3_mem_pool_size = ((USBH3_HC_MEM_POOL_SIZE + 8 * USBH3_HC_TRANSFER_NUM + 32 + 4 +3)/4)*4;

         USBH_HC_t            usbh3_hc       =      { USBH3_HC_PIPE_NUM };
         USBH_HC_t           *usbh3_hc_ptr   =       &usbh3_hc;
         USBH_OHCI_t         *usbh3_ohci_ptr =        NULL;
         USBH_EHCI_t         *usbh3_ehci_ptr =        NULL;

#elif   (USBH3_HC_IF == 1)              // OHCI

#if     (USBH3_HC_OHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM3(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM3(x)
#endif
#define  __ALIGNED_MEM3(x)                          __attribute__((aligned(x)))

#ifndef  USBH3_HC_OHCI_PIPE_NUM
#define  USBH3_HC_OHCI_PIPE_NUM                       USBH3_HC_OHCI_ENDPOINT_NUM
#endif

#if     (USBH3_HC_OHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 3 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh3_pipe             [USBH3_HC_OHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh3_pipe_tid         [USBH3_HC_OHCI_PIPE_NUM];
const    uint32_t             usbh3_pipe_num =        USBH3_HC_OHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh3_transfer_info    [USBH3_HC_OHCI_TRANSFER_NUM];
const    uint32_t             usbh3_transfer_num =    USBH3_HC_OHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_OHCI_LIB(3);
const    ARM_DRIVER_USBH     *usbh3_hcd_ptr =        &USBHn_DRIVER_OHCI_LIB(3);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH3_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh3_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH3_HC_NUM);

#define  USBH3_OHCI_MEM_HCCA                         (USBH3_HC_OHCI_MEM_POOL_ADDR)
#define  USBH3_OHCI_MEM_HCCA_SIZE                    (256)
#define  USBH3_OHCI_MEM_ED                           (USBH3_OHCI_MEM_HCCA + USBH3_OHCI_MEM_HCCA_SIZE)
#define  USBH3_OHCI_MEM_ED_SIZE                      (USBH3_HC_OHCI_PIPE_NUM*16)
#define  USBH3_OHCI_MEM_TD                           (USBH3_OHCI_MEM_ED   + USBH3_OHCI_MEM_ED_SIZE)
#define  USBH3_OHCI_MEM_TD_SIZE                      (USBH3_HC_OHCI_TRANSFER_NUM*16)
#define  USBH3_OHCI_MEM_POOL_ADDR                    (USBH3_OHCI_MEM_HCCA + USBH3_OHCI_MEM_HCCA_SIZE + USBH3_OHCI_MEM_ED_SIZE + USBH3_OHCI_MEM_TD_SIZE)
#define  USBH3_OHCI_MEM_POOL_SIZE                    (USBH3_HC_OHCI_MEM_POOL_SIZE + 8 * USBH3_HC_TRANSFER_NUM + 32 + 4)

         uint32_t             usbh3_ohci_hcca       [(USBH3_OHCI_MEM_HCCA_SIZE +3)/4] __AT_MEM3(USBH3_OHCI_MEM_HCCA) __ALIGNED_MEM3(256);
         uint32_t             usbh3_ohci_ed         [(USBH3_OHCI_MEM_ED_SIZE   +3)/4] __AT_MEM3(USBH3_OHCI_MEM_ED)   __ALIGNED_MEM3(16);
         uint32_t             usbh3_ohci_td         [(USBH3_OHCI_MEM_TD_SIZE   +3)/4] __AT_MEM3(USBH3_OHCI_MEM_TD)   __ALIGNED_MEM3(16);
const    uint8_t              usbh3_mem_pool_reloc =  USBH3_HC_OHCI_MEM_POOL_RELOC;
         uint32_t             usbh3_mem_pool        [(USBH3_OHCI_MEM_POOL_SIZE +3)/4] __AT_MEM3(USBH3_OHCI_MEM_POOL_ADDR);
const    uint32_t             usbh3_mem_pool_size = ((USBH3_OHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_OHCI_t          usbh3_ohci = {         (uint32_t *)USBH3_HC_OHCI_BASE_ADDRESS,
                                                      USBH3_HC_OHCI_PIPE_NUM,
                                                      USBH3_HC_OHCI_TRANSFER_NUM,
                                                      0,
                                                     &usbh3_ohci_hcca[0],
                                                     &usbh3_ohci_ed[0],
                                                     &usbh3_ohci_td[0],
                                                      NULL,
                                                     &usbh3_transfer_info[0] };
         USBH_HC_t           *usbh3_hc_ptr   =        NULL;
         USBH_OHCI_t         *usbh3_ohci_ptr =       &usbh3_ohci;
         USBH_EHCI_t         *usbh3_ehci_ptr =        NULL;

#elif   (USBH3_HC_IF == 2)              // NXP EHCI with extensions for full/low-speed support

#if     (USBH3_HC_EHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM3(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM3(x)
#endif
#define  __ALIGNED_MEM3(x)                          __attribute__((aligned(x)))

#ifndef  USBH3_HC_EHCI_PIPE_NUM
#define  USBH3_HC_EHCI_PIPE_NUM                       USBH3_HC_EHCI_ENDPOINT_NUM
#endif

#if     (USBH3_HC_EHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 3 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh3_pipe             [USBH3_HC_EHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh3_pipe_tid         [USBH3_HC_EHCI_PIPE_NUM];
const    uint32_t             usbh3_pipe_num =        USBH3_HC_EHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh3_transfer_info    [USBH3_HC_EHCI_TRANSFER_NUM];
const    uint32_t             usbh3_transfer_num =    USBH3_HC_EHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_EHCI_LIB(3);
const    ARM_DRIVER_USBH     *usbh3_hcd_ptr =        &USBHn_DRIVER_EHCI_LIB(3);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH3_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh3_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH3_HC_NUM);

#define  USBH3_EHCI_MEM_PFL                          (USBH3_HC_EHCI_MEM_POOL_ADDR + (((_USBH3_HC_EHCI_MEM_POOL_SIZE + 3)/4)*4))
#define  USBH3_EHCI_MEM_PFL_SIZE                     (4096)
#define  USBH3_EHCI_MEM_QH                           (USBH3_EHCI_MEM_PFL  + USBH3_EHCI_MEM_PFL_SIZE)
#define  USBH3_EHCI_MEM_QH_SIZE                      (USBH3_HC_EHCI_PIPE_NUM*64)
#define  USBH3_EHCI_MEM_QTD                          (USBH3_EHCI_MEM_QH   + USBH3_EHCI_MEM_QH_SIZE)
#define  USBH3_EHCI_MEM_QTD_SIZE                     (USBH3_HC_EHCI_TRANSFER_NUM*32)
#define  USBH3_EHCI_MEM_POOL_ADDR                    (USBH3_EHCI_MEM_PFL + USBH3_EHCI_MEM_PFL_SIZE + USBH3_OHCI_MEM_QH_SIZE + USBH3_OHCI_MEM_QTD_SIZE)
#define  USBH3_EHCI_MEM_POOL_SIZE                    (USBH3_HC_EHCI_MEM_POOL_SIZE + 8 * USBH3_HC_TRANSFER_NUM + 32 + 4)

         uint32_t             usbh3_ehci_pfl        [(USBH3_EHCI_MEM_PFL_SIZE  +3)/4] __AT_MEM3(USBH3_EHCI_MEM_PFL) __ALIGNED_MEM3(4096);
         uint32_t             usbh3_ehci_qh         [(USBH3_EHCI_MEM_QH_SIZE   +3)/4] __AT_MEM3(USBH3_EHCI_MEM_QH)  __ALIGNED_MEM3(64);
         uint32_t             usbh3_ehci_qtd        [(USBH3_EHCI_MEM_QTD_SIZE  +3)/4] __AT_MEM3(USBH3_EHCI_MEM_QTD) __ALIGNED_MEM3(32);
const    uint8_t              usbh3_mem_pool_reloc =  USBH3_HC_EHCI_MEM_POOL_RELOC;
         uint32_t             usbh3_mem_pool        [(USBH3_EHCI_MEM_POOL_SIZE +3)/4] __AT_MEM3(USBH3_EHCI_MEM_POOL_ADDR);
const    uint32_t             usbh3_mem_pool_size = ((USBH3_EHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_EHCI_t          usbh3_ehci = {         (uint32_t *)USBH3_HC_EHCI_BASE_ADDRESS,
                                                      USBH3_HC_EHCI_PIPE_NUM,
                                                      USBH3_HC_EHCI_TRANSFER_NUM,
                                                      0,
                                                      0,
                                                      1024,
                                                     &usbh3_ehci_pfl[0],
                                                     &usbh3_ehci_qh[0],
                                                     &usbh3_ehci_qtd[0],
                                                      NULL,
                                                      NULL,
                                                      NULL,
                                                     &usbh3_transfer_info[0] };
         USBH_HC_t           *usbh3_hc_ptr   =        NULL;
         USBH_EHCI_t         *usbh3_ehci_ptr =       &usbh3_ehci;
         USBH_OHCI_t         *usbh3_ohci_ptr =        NULL;
#endif

extern  void USBH3_Core_Thread                        (void const *arg);
#ifndef USBH3_CORE_THREAD_STACK_SIZE
#define USBH3_CORE_THREAD_STACK_SIZE                  0
#endif
#ifndef USBH3_CORE_THREAD_PRIORITY
#define USBH3_CORE_THREAD_PRIORITY                    osPriorityAboveNormal
#endif
osThreadDef(USBH3_Core_Thread, USBH3_CORE_THREAD_PRIORITY, 1, USBH3_CORE_THREAD_STACK_SIZE);
