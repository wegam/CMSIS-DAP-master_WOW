/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Host
 * Copyright (c) 2004-2015 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    usbh_config_hc_0.c
 * Purpose: USB Host Host Controller 0 Data and Settings
 * Rev.:    V6.4.1
 *----------------------------------------------------------------------------*/

#if     (USBH0_HC_IF == 0)              // Custom

#if     (USBH0_HC_MEM_POOL_RELOC == 1)
#define  __AT_MEM0(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM0(x)
#endif
#define  __ALIGNED_MEM0(x)                          __attribute__((aligned(x)))

#ifndef  USBH0_HC_PIPE_NUM
#define  USBH0_HC_PIPE_NUM                            USBH0_HC_ENDPOINT_NUM
#endif

#if     (USBH0_HC_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 0 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh0_pipe             [USBH0_HC_PIPE_NUM];
         USBH_PIPE_TID_t      usbh0_pipe_tid         [USBH0_HC_PIPE_NUM];
const    uint32_t             usbh0_pipe_num =        USBH0_HC_PIPE_NUM;

const    uint32_t             usbh0_transfer_num =    USBH0_HC_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER(USBH0_HC_NUM);
const    ARM_DRIVER_USBH     *usbh0_hcd_ptr  =       &USBHn_DRIVER(USBH0_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh0_hci_hcd_ptr =     NULL;

const    uint8_t              usbh0_mem_pool_reloc =  USBH0_HC_MEM_POOL_RELOC;
         uint32_t             usbh0_mem_pool        [(USBH0_HC_MEM_POOL_SIZE + 8 * USBH0_HC_TRANSFER_NUM + 32 + 4 +3)/4] __AT_MEM0(USBH0_HC_MEM_POOL_ADDR);
const    uint32_t             usbh0_mem_pool_size = ((USBH0_HC_MEM_POOL_SIZE + 8 * USBH0_HC_TRANSFER_NUM + 32 + 4 +3)/4)*4;

         USBH_HC_t            usbh0_hc       =      { USBH0_HC_PIPE_NUM };
         USBH_HC_t           *usbh0_hc_ptr   =       &usbh0_hc;
         USBH_OHCI_t         *usbh0_ohci_ptr =        NULL;
         USBH_EHCI_t         *usbh0_ehci_ptr =        NULL;

#elif   (USBH0_HC_IF == 1)              // OHCI

#if     (USBH0_HC_OHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM0(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM0(x)
#endif
#define  __ALIGNED_MEM0(x)                          __attribute__((aligned(x)))

#ifndef  USBH0_HC_OHCI_PIPE_NUM
#define  USBH0_HC_OHCI_PIPE_NUM                       USBH0_HC_OHCI_ENDPOINT_NUM
#endif

#if     (USBH0_HC_OHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 0 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh0_pipe             [USBH0_HC_OHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh0_pipe_tid         [USBH0_HC_OHCI_PIPE_NUM];
const    uint32_t             usbh0_pipe_num =        USBH0_HC_OHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh0_transfer_info    [USBH0_HC_OHCI_TRANSFER_NUM];
const    uint32_t             usbh0_transfer_num =    USBH0_HC_OHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_OHCI_LIB(0);
const    ARM_DRIVER_USBH     *usbh0_hcd_ptr =        &USBHn_DRIVER_OHCI_LIB(0);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH0_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh0_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH0_HC_NUM);

#define  USBH0_OHCI_MEM_HCCA                         (USBH0_HC_OHCI_MEM_POOL_ADDR)
#define  USBH0_OHCI_MEM_HCCA_SIZE                    (256)
#define  USBH0_OHCI_MEM_ED                           (USBH0_OHCI_MEM_HCCA + USBH0_OHCI_MEM_HCCA_SIZE)
#define  USBH0_OHCI_MEM_ED_SIZE                      (USBH0_HC_OHCI_PIPE_NUM*16)
#define  USBH0_OHCI_MEM_TD                           (USBH0_OHCI_MEM_ED   + USBH0_OHCI_MEM_ED_SIZE)
#define  USBH0_OHCI_MEM_TD_SIZE                      (USBH0_HC_OHCI_TRANSFER_NUM*16)
#define  USBH0_OHCI_MEM_POOL_ADDR                    (USBH0_OHCI_MEM_HCCA + USBH0_OHCI_MEM_HCCA_SIZE + USBH0_OHCI_MEM_ED_SIZE + USBH0_OHCI_MEM_TD_SIZE)
#define  USBH0_OHCI_MEM_POOL_SIZE                    (USBH0_HC_OHCI_MEM_POOL_SIZE + 8 * USBH0_HC_TRANSFER_NUM + 32 + 4)

         uint32_t             usbh0_ohci_hcca       [(USBH0_OHCI_MEM_HCCA_SIZE +3)/4] __AT_MEM0(USBH0_OHCI_MEM_HCCA) __ALIGNED_MEM0(256);
         uint32_t             usbh0_ohci_ed         [(USBH0_OHCI_MEM_ED_SIZE   +3)/4] __AT_MEM0(USBH0_OHCI_MEM_ED)   __ALIGNED_MEM0(16);
         uint32_t             usbh0_ohci_td         [(USBH0_OHCI_MEM_TD_SIZE   +3)/4] __AT_MEM0(USBH0_OHCI_MEM_TD)   __ALIGNED_MEM0(16);
const    uint8_t              usbh0_mem_pool_reloc =  USBH0_HC_OHCI_MEM_POOL_RELOC;
         uint32_t             usbh0_mem_pool        [(USBH0_OHCI_MEM_POOL_SIZE +3)/4] __AT_MEM0(USBH0_OHCI_MEM_POOL_ADDR);
const    uint32_t             usbh0_mem_pool_size = ((USBH0_OHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_OHCI_t          usbh0_ohci = {         (uint32_t *)USBH0_HC_OHCI_BASE_ADDRESS,
                                                      USBH0_HC_OHCI_PIPE_NUM,
                                                      USBH0_HC_OHCI_TRANSFER_NUM,
                                                      0,
                                                     &usbh0_ohci_hcca[0],
                                                     &usbh0_ohci_ed[0],
                                                     &usbh0_ohci_td[0],
                                                      NULL,
                                                     &usbh0_transfer_info[0] };
         USBH_HC_t           *usbh0_hc_ptr   =        NULL;
         USBH_OHCI_t         *usbh0_ohci_ptr =       &usbh0_ohci;
         USBH_EHCI_t         *usbh0_ehci_ptr =        NULL;

#elif   (USBH0_HC_IF == 2)              // NXP EHCI with extensions for full/low-speed support

#if     (USBH0_HC_EHCI_MEM_POOL_RELOC == 1)
#define  __AT_MEM0(x)                               __attribute__((at(x)))
#else
#define  __AT_MEM0(x)
#endif
#define  __ALIGNED_MEM0(x)                          __attribute__((aligned(x)))

#ifndef  USBH0_HC_EHCI_PIPE_NUM
#define  USBH0_HC_EHCI_PIPE_NUM                       USBH0_HC_EHCI_ENDPOINT_NUM
#endif

#if     (USBH0_HC_EHCI_MEM_POOL_SIZE < 512)
#warning Memory Pool Size for Host Controller 0 not recommended less than 512 bytes!
#endif

         USBH_PIPE            usbh0_pipe             [USBH0_HC_EHCI_PIPE_NUM];
         USBH_PIPE_TID_t      usbh0_pipe_tid         [USBH0_HC_EHCI_PIPE_NUM];
const    uint32_t             usbh0_pipe_num =        USBH0_HC_EHCI_PIPE_NUM;

         USBH_TRANSFER_INFO_t usbh0_transfer_info    [USBH0_HC_EHCI_TRANSFER_NUM];
const    uint32_t             usbh0_transfer_num =    USBH0_HC_EHCI_TRANSFER_NUM;

extern   ARM_DRIVER_USBH                              USBHn_DRIVER_EHCI_LIB(0);
const    ARM_DRIVER_USBH     *usbh0_hcd_ptr =        &USBHn_DRIVER_EHCI_LIB(0);

extern   ARM_DRIVER_USBH_HCI                          USBHn_DRIVER_HCI(USBH0_HC_NUM);
const    ARM_DRIVER_USBH_HCI *usbh0_hci_hcd_ptr =    &USBHn_DRIVER_HCI(USBH0_HC_NUM);

#define  USBH0_EHCI_MEM_PFL                          (USBH0_HC_EHCI_MEM_POOL_ADDR + (((_USBH0_HC_EHCI_MEM_POOL_SIZE + 3)/4)*4))
#define  USBH0_EHCI_MEM_PFL_SIZE                     (4096)
#define  USBH0_EHCI_MEM_QH                           (USBH0_EHCI_MEM_PFL  + USBH0_EHCI_MEM_PFL_SIZE)
#define  USBH0_EHCI_MEM_QH_SIZE                      (USBH0_HC_EHCI_PIPE_NUM*64)
#define  USBH0_EHCI_MEM_QTD                          (USBH0_EHCI_MEM_QH   + USBH0_EHCI_MEM_QH_SIZE)
#define  USBH0_EHCI_MEM_QTD_SIZE                     (USBH0_HC_EHCI_TRANSFER_NUM*32)
#define  USBH0_EHCI_MEM_POOL_ADDR                    (USBH0_EHCI_MEM_PFL + USBH0_EHCI_MEM_PFL_SIZE + USBH0_OHCI_MEM_QH_SIZE + USBH0_OHCI_MEM_QTD_SIZE)
#define  USBH0_EHCI_MEM_POOL_SIZE                    (USBH0_HC_EHCI_MEM_POOL_SIZE + 8 * USBH0_HC_TRANSFER_NUM + 32 + 4)

         uint32_t             usbh0_ehci_pfl        [(USBH0_EHCI_MEM_PFL_SIZE  +3)/4] __AT_MEM0(USBH0_EHCI_MEM_PFL) __ALIGNED_MEM0(4096);
         uint32_t             usbh0_ehci_qh         [(USBH0_EHCI_MEM_QH_SIZE   +3)/4] __AT_MEM0(USBH0_EHCI_MEM_QH)  __ALIGNED_MEM0(64);
         uint32_t             usbh0_ehci_qtd        [(USBH0_EHCI_MEM_QTD_SIZE  +3)/4] __AT_MEM0(USBH0_EHCI_MEM_QTD) __ALIGNED_MEM0(32);
const    uint8_t              usbh0_mem_pool_reloc =  USBH0_HC_EHCI_MEM_POOL_RELOC;
         uint32_t             usbh0_mem_pool        [(USBH0_EHCI_MEM_POOL_SIZE +3)/4] __AT_MEM0(USBH0_EHCI_MEM_POOL_ADDR);
const    uint32_t             usbh0_mem_pool_size = ((USBH0_EHCI_MEM_POOL_SIZE +3)/4)*4;

         USBH_EHCI_t          usbh0_ehci = {         (uint32_t *)USBH0_HC_EHCI_BASE_ADDRESS,
                                                      USBH0_HC_EHCI_PIPE_NUM,
                                                      USBH0_HC_EHCI_TRANSFER_NUM,
                                                      0,
                                                      0,
                                                      1024,
                                                     &usbh0_ehci_pfl[0],
                                                     &usbh0_ehci_qh[0],
                                                     &usbh0_ehci_qtd[0],
                                                      NULL,
                                                      NULL,
                                                      NULL,
                                                     &usbh0_transfer_info[0] };
         USBH_HC_t           *usbh0_hc_ptr   =        NULL;
         USBH_EHCI_t         *usbh0_ehci_ptr =       &usbh0_ehci;
         USBH_OHCI_t         *usbh0_ohci_ptr =        NULL;
#endif

extern  void USBH0_Core_Thread                        (void const *arg);
#ifndef USBH0_CORE_THREAD_STACK_SIZE
#define USBH0_CORE_THREAD_STACK_SIZE                  0
#endif
#ifndef USBH0_CORE_THREAD_PRIORITY
#define USBH0_CORE_THREAD_PRIORITY                    osPriorityAboveNormal
#endif
osThreadDef(USBH0_Core_Thread, USBH0_CORE_THREAD_PRIORITY, 1, USBH0_CORE_THREAD_STACK_SIZE);
