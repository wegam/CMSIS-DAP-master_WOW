/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbh_config_hc_1.c
 * Purpose: USB Host Host Controller 1 Data and Settings
 * Rev.:    V6.4.1
 *----------------------------------------------------------------------------*/

#if     (USBH1_HC_IF == 0)              // Custom

#if     (USBH1_HC_MEM_POOL_RELOC == 1)
#define  __AT_MEM1(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM1(x)
#endif
#define  __ALIGNED_MEM1(x)                          __attribute__((aligned(x)))

#ifndef  USBH1_HC_PIPE_NUM
#define  USBH1_HC_PIPE_NUM                            USBH1_HC_ENDPOINT_NUM
#endif

#if     (USBH1_HC_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 1 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh1_pipe             [USBH1_HC_PIPE_NUM];
         USBH_PIPE_TID_t      usbh1_pipe_tid         [USBH1_HC_PIPE_NUM];
const    uint32_t             usbh1_pipe_num =        USBH1_HC_PIPE_NUM;

const    uint32_t             usbh1_transfer_num =    USBH1_HC_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER(USBH1_HC_NUM);
const    ARM_DRIVER_USBH     *usbh1_hcd_ptr  =       &USBHn_DRIVER(USBH1_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh1_hci_hcd_ptr =     NULL;

const    uint8_t              usbh1_mem_pool_reloc =  USBH1_HC_MEM_POOL_RELOC;
         uint32_t             usbh1_mem_pool        [(USBH1_HC_MEM_POOL_SIZE + 8 * USBH1_HC_TRANSFER_NUM + 32 + 4 +3)/4] __AT_MEM1(USBH1_HC_MEM_POOL_ADDR);
const    uint32_t             usbh1_mem_pool_size = ((USBH1_HC_MEM_POOL_SIZE + 8 * USBH1_HC_TRANSFER_NUM + 32 + 4 +3)/4)*4;

         USBH_HC_t            usbh1_hc       =      { USBH1_HC_PIPE_NUM };
         USBH_HC_t           *usbh1_hc_ptr   =       &usbh1_hc;
         USBH_OHCI_t         *usbh1_ohci_ptr =        NULL;
         USBH_EHCI_t         *usbh1_ehci_ptr =        NULL;

#elif   (USBH1_HC_IF == 1)              // OHCI

#if     (USBH1_HC_OHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM1(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM1(x)
#endif
#define  __ALIGNED_MEM1(x)                          __attribute__((aligned(x)))

#ifndef  USBH1_HC_OHCI_PIPE_NUM
#define  USBH1_HC_OHCI_PIPE_NUM                       USBH1_HC_OHCI_ENDPOINT_NUM
#endif

#if     (USBH1_HC_OHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 1 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh1_pipe             [USBH1_HC_OHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh1_pipe_tid         [USBH1_HC_OHCI_PIPE_NUM];
const    uint32_t             usbh1_pipe_num =        USBH1_HC_OHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh1_transfer_info    [USBH1_HC_OHCI_TRANSFER_NUM];
const    uint32_t             usbh1_transfer_num =    USBH1_HC_OHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_OHCI_LIB(1);
const    ARM_DRIVER_USBH     *usbh1_hcd_ptr =        &USBHn_DRIVER_OHCI_LIB(1);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH1_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh1_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH1_HC_NUM);

#define  USBH1_OHCI_MEM_HCCA                         (USBH1_HC_OHCI_MEM_POOL_ADDR)
#define  USBH1_OHCI_MEM_HCCA_SIZE                    (256)
#define  USBH1_OHCI_MEM_ED                           (USBH1_OHCI_MEM_HCCA + USBH1_OHCI_MEM_HCCA_SIZE)
#define  USBH1_OHCI_MEM_ED_SIZE                      (USBH1_HC_OHCI_PIPE_NUM*16)
#define  USBH1_OHCI_MEM_TD                           (USBH1_OHCI_MEM_ED   + USBH1_OHCI_MEM_ED_SIZE)
#define  USBH1_OHCI_MEM_TD_SIZE                      (USBH1_HC_OHCI_TRANSFER_NUM*16)
#define  USBH1_OHCI_MEM_POOL_ADDR                    (USBH1_OHCI_MEM_HCCA + USBH1_OHCI_MEM_HCCA_SIZE + USBH1_OHCI_MEM_ED_SIZE + USBH1_OHCI_MEM_TD_SIZE)
#define  USBH1_OHCI_MEM_POOL_SIZE                    (USBH1_HC_OHCI_MEM_POOL_SIZE + 8 * USBH1_HC_TRANSFER_NUM + 32 + 4)

         uint32_t             usbh1_ohci_hcca       [(USBH1_OHCI_MEM_HCCA_SIZE +3)/4] __AT_MEM1(USBH1_OHCI_MEM_HCCA) __ALIGNED_MEM1(256);
         uint32_t             usbh1_ohci_ed         [(USBH1_OHCI_MEM_ED_SIZE   +3)/4] __AT_MEM1(USBH1_OHCI_MEM_ED)   __ALIGNED_MEM1(16);
         uint32_t             usbh1_ohci_td         [(USBH1_OHCI_MEM_TD_SIZE   +3)/4] __AT_MEM1(USBH1_OHCI_MEM_TD)   __ALIGNED_MEM1(16);
const    uint8_t              usbh1_mem_pool_reloc =  USBH1_HC_OHCI_MEM_POOL_RELOC;
         uint32_t             usbh1_mem_pool        [(USBH1_OHCI_MEM_POOL_SIZE +3)/4] __AT_MEM1(USBH1_OHCI_MEM_POOL_ADDR);
const    uint32_t             usbh1_mem_pool_size = ((USBH1_OHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_OHCI_t          usbh1_ohci = {         (uint32_t *)USBH1_HC_OHCI_BASE_ADDRESS,
                                                      USBH1_HC_OHCI_PIPE_NUM,
                                                      USBH1_HC_OHCI_TRANSFER_NUM,
                                                      0,
                                                     &usbh1_ohci_hcca[0],
                                                     &usbh1_ohci_ed[0],
                                                     &usbh1_ohci_td[0],
                                                      NULL,
                                                     &usbh1_transfer_info[0] };
         USBH_HC_t           *usbh1_hc_ptr   =        NULL;
         USBH_OHCI_t         *usbh1_ohci_ptr =       &usbh1_ohci;
         USBH_EHCI_t         *usbh1_ehci_ptr =        NULL;

#elif   (USBH1_HC_IF == 2)              // NXP EHCI with extensions for full/low-speed support

#if     (USBH1_HC_EHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM1(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM1(x)
#endif
#define  __ALIGNED_MEM1(x)                          __attribute__((aligned(x)))

#ifndef  USBH1_HC_EHCI_PIPE_NUM
#define  USBH1_HC_EHCI_PIPE_NUM                       USBH1_HC_EHCI_ENDPOINT_NUM
#endif

#if     (USBH1_HC_EHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 1 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh1_pipe             [USBH1_HC_EHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh1_pipe_tid         [USBH1_HC_EHCI_PIPE_NUM];
const    uint32_t             usbh1_pipe_num =        USBH1_HC_EHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh1_transfer_info    [USBH1_HC_EHCI_TRANSFER_NUM];
const    uint32_t             usbh1_transfer_num =    USBH1_HC_EHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_EHCI_LIB(1);
const    ARM_DRIVER_USBH     *usbh1_hcd_ptr =        &USBHn_DRIVER_EHCI_LIB(1);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH1_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh1_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH1_HC_NUM);

#define  USBH1_EHCI_MEM_PFL                          (USBH1_HC_EHCI_MEM_POOL_ADDR + (((_USBH1_HC_EHCI_MEM_POOL_SIZE + 3)/4)*4))
#define  USBH1_EHCI_MEM_PFL_SIZE                     (4096)
#define  USBH1_EHCI_MEM_QH                           (USBH1_EHCI_MEM_PFL  + USBH1_EHCI_MEM_PFL_SIZE)
#define  USBH1_EHCI_MEM_QH_SIZE                      (USBH1_HC_EHCI_PIPE_NUM*64)
#define  USBH1_EHCI_MEM_QTD                          (USBH1_EHCI_MEM_QH   + USBH1_EHCI_MEM_QH_SIZE)
#define  USBH1_EHCI_MEM_QTD_SIZE                     (USBH1_HC_EHCI_TRANSFER_NUM*32)
#define  USBH1_EHCI_MEM_POOL_ADDR                    (USBH1_EHCI_MEM_PFL + USBH1_EHCI_MEM_PFL_SIZE + USBH1_OHCI_MEM_QH_SIZE + USBH1_OHCI_MEM_QTD_SIZE)
#define  USBH1_EHCI_MEM_POOL_SIZE                    (USBH1_HC_EHCI_MEM_POOL_SIZE + 8 * USBH1_HC_TRANSFER_NUM +32 + 4)

         uint32_t             usbh1_ehci_pfl        [(USBH1_EHCI_MEM_PFL_SIZE  +3)/4] __AT_MEM1(USBH1_EHCI_MEM_PFL) __ALIGNED_MEM1(4096);
         uint32_t             usbh1_ehci_qh         [(USBH1_EHCI_MEM_QH_SIZE   +3)/4] __AT_MEM1(USBH1_EHCI_MEM_QH)  __ALIGNED_MEM1(64);
         uint32_t             usbh1_ehci_qtd        [(USBH1_EHCI_MEM_QTD_SIZE  +3)/4] __AT_MEM1(USBH1_EHCI_MEM_QTD) __ALIGNED_MEM1(32);
const    uint8_t              usbh1_mem_pool_reloc =  USBH1_HC_EHCI_MEM_POOL_RELOC;
         uint32_t             usbh1_mem_pool        [(USBH1_EHCI_MEM_POOL_SIZE +3)/4] __AT_MEM1(USBH1_EHCI_MEM_POOL_ADDR);
const    uint32_t             usbh1_mem_pool_size = ((USBH1_EHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_EHCI_t          usbh1_ehci = {         (uint32_t *)USBH1_HC_EHCI_BASE_ADDRESS,
                                                      USBH1_HC_EHCI_PIPE_NUM,
                                                      USBH1_HC_EHCI_TRANSFER_NUM,
                                                      0,
                                                      0,
                                                      1024,
                                                     &usbh1_ehci_pfl[0],
                                                     &usbh1_ehci_qh[0],
                                                     &usbh1_ehci_qtd[0],
                                                      NULL,
                                                      NULL,
                                                      NULL,
                                                     &usbh1_transfer_info[0] };
         USBH_HC_t           *usbh1_hc_ptr   =        NULL;
         USBH_EHCI_t         *usbh1_ehci_ptr =       &usbh1_ehci;
         USBH_OHCI_t         *usbh1_ohci_ptr =        NULL;
#endif

extern  void USBH1_Core_Thread                        (void const *arg);
#ifndef USBH1_CORE_THREAD_STACK_SIZE
#define USBH1_CORE_THREAD_STACK_SIZE                  0
#endif
#ifndef USBH1_CORE_THREAD_PRIORITY
#define USBH1_CORE_THREAD_PRIORITY                    osPriorityAboveNormal
#endif
osThreadDef(USBH1_Core_Thread, USBH1_CORE_THREAD_PRIORITY, 1, USBH1_CORE_THREAD_STACK_SIZE);
