/*----------------------------------------------------------------------------
 *      RL-ARM - USB
 *----------------------------------------------------------------------------
 *      Name:    usbreg.h
 *      Purpose: Hardware Layer Definitions for ST STM32F10x
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __USBREG_H
#define __USBREG_H


#define REG(x)  (*((volatile unsigned int *)(x)))

#define USB_BASE_ADDR   0x40005C00  /* USB Registers Base Address */
#define USB_PMA_ADDR    0x40006000  /* USB Packet Memory Area Address */


/* Common Registers */
#define CNTR    REG(USB_BASE_ADDR + 0x40)   /* Control Register */
#define ISTR    REG(USB_BASE_ADDR + 0x44)   /* Interrupt Status Register */
#define FNR     REG(USB_BASE_ADDR + 0x48)   /* Frame Number Register */
#define DADDR   REG(USB_BASE_ADDR + 0x4C)   /* Device Address Register */
#define BTABLE  REG(USB_BASE_ADDR + 0x50)   /* Buffer Table Address Register */

/* CNTR: Control Register Bit Definitions */
#define CNTR_CTRM       0x8000      /* Correct Transfer Interrupt Mask */
#define CNTR_PMAOVRM    0x4000      /* Packet Memory Aerea Over/underrun Interrupt Mask */
#define CNTR_ERRM       0x2000      /* Error Interrupt Mask */
#define CNTR_WKUPM      0x1000      /* Wake-up Interrupt Mask */
#define CNTR_SUSPM      0x0800      /* Suspend Mode Interrupt Mask  */
#define CNTR_RESETM     0x0400      /* USB Reset Interrupt Mask   */
#define CNTR_SOFM       0x0200      /* Start of Frame Interrupt Mask */
#define CNTR_ESOFM      0x0100      /* Expected Start of Frame Interrupt Mask */
#define CNTR_RESUME     0x0010      /* Resume Request */
#define CNTR_FSUSP      0x0008      /* Force Suspend */
#define CNTR_LPMODE     0x0004      /* Low-power Mode */
#define CNTR_PDWN       0x0002      /* Power Down */
#define CNTR_FRES       0x0001      /* Force USB Reset */	//ǿ��USB��λ

/* ISTR: Interrupt Status Register Bit Definitions */					//USB�ж�״̬�Ĵ���(USB_ISTR)
#define ISTR_CTR        0x8000      /* Correct Transfer */										//��ȷ�Ĵ��� (Correct transfer)��λ�ڶ˵���ȷ���һ�����ݴ������Ӳ����λ��
#define ISTR_PMAOVR     0x4000      /* Packet Memory Aerea Over/underrun */		//�������/���黺�������
#define ISTR_ERR        0x2000      /* Error */																//������Ӧ��/CRC����/����λ�������֡��ʽ����
#define ISTR_WKUP       0x1000      /* Wake-up */															//��������
#define ISTR_SUSP       0x0800      /* Suspend Mode */												//����ģ������
#define ISTR_RESET      0x0400      /* USB Reset */														//USB��λ����
#define ISTR_SOF        0x0200      /* Start of Frame */											//֡�ױ�־
#define ISTR_ESOF       0x0100      /* Expected Start of Frame */							//����֡�ױ�ʶλ (Expected start of frame)
#define ISTR_DIR        0x0010      /* Direction of Transaction */						//���䷽��
#define ISTR_EP_ID      0x000F      /* EndPoint Identifier */									//�˵�ID

/* FNR: Frame Number Register Bit Definitions */
#define FNR_RXDP        0x8000      /* D+ Data Line Status */
#define FNR_RXDM        0x4000      /* D- Data Line Status */
#define FNR_LCK         0x2000      /* Locked */
#define FNR_LSOF        0x1800      /* Lost SOF */
#define FNR_FN          0x07FF      /* Frame Number */

/* DADDR: Device Address Register Bit Definitions */
#define DADDR_EF        0x0080      /* Enable Function */
#define DADDR_ADD       0x007F      /* Device Address */


/* EndPoint Registers */		//�˵�Ĵ���
#define EPxREG(x)       REG(USB_BASE_ADDR + 4*(x))

/* EPxREG: EndPoint Registers Bit Definitions */								//�˵�Ĵ���
#define EP_CTR_RX       0x8000      /* Correct RX Transfer */		//��ȷ���ձ�־λ (Correct Transfer for reception)
#define EP_DTOG_RX      0x4000      /* RX Data Toggle */				//�������ݽ��յ����ݷ�תλ (Data Toggle, for reception transfers)
#define EP_STAT_RX      0x3000      /* RX Status */							//�������ݽ��յ�״̬λ (Status bits, for reception transfers)			�鿴	EP_STAT_RX: RX Status
#define EP_SETUP        0x0800      /* EndPoint Setup */				//SETUP���鴫����ɱ�־λ (Setup transaction completed)
#define EP_TYPE         0x0600      /* EndPoint Type */					//�˵�����λ (Endpoint type),�鿴	EP_TYPE: EndPoint Types
#define EP_KIND         0x0100      /* EndPoint Kind */					//�˵���������λ (Endpoint kind)	�鿴	EP_KIND: EndPoint Kind
#define EP_CTR_TX       0x0080      /* Correct TX Transfer */		//��ȷ���ͱ�־λ (Correct transfer for transmission)
#define EP_DTOG_TX      0x0040      /* TX Data Toggle */				//�������ݷ�תλ (Data Toggle, for transmission transfers)
#define EP_STAT_TX      0x0030      /* TX Status */							//���ڷ������ݵ�״̬λ (Status bits, for transmission transfers)	�鿴	EP_STAT_TX: TX Status
#define EP_EA           0x000F      /* EndPoint Address */			//�˵��ַ (Endpoint address)

/* EndPoint Register Mask (No Toggle Fields) */
#define EP_MASK         (EP_CTR_RX|EP_SETUP|EP_TYPE|EP_KIND|EP_CTR_TX|EP_EA)

/* EP_TYPE: EndPoint Types */
#define EP_BULK         0x0000      /* BULK EndPoint */					//�����˵�
#define EP_CONTROL      0x0200      /* CONTROL EndPoint */			//���ƶ˵�
#define EP_ISOCHRONOUS  0x0400      /* ISOCHRONOUS EndPoint */	//ͬ���˵�
#define EP_INTERRUPT    0x0600      /* INTERRUPT EndPoint */		//�ж϶˵�

/* EP_KIND: EndPoint Kind */
#define EP_DBL_BUF      EP_KIND     /* Double Buffer for Bulk Endpoint */		//DBL_BUF��˫����˵�
#define EP_STATUS_OUT   EP_KIND     /* Status Out for Control Endpoint */		//STATUS_OUT

/* EP_STAT_TX: TX Status */
#define EP_TX_DIS       0x0000      /* Disabled */		//�˵�������еķ�������
#define EP_TX_STALL     0x0010      /* Stalled */			//�˵���STALL������Ӧ���еķ�������
#define EP_TX_NAK       0x0020      /* NAKed */				//�˵���NAK������Ӧ���еķ�������
#define EP_TX_VALID     0x0030      /* Valid */				//�˵�����ڷ��͡�

/* EP_STAT_RX: RX Status */
#define EP_RX_DIS       0x0000      /* Disabled */		//�˵�������еĽ�������
#define EP_RX_STALL     0x1000      /* Stalled */			//�˵���STALL������Ӧ���еĽ�������
#define EP_RX_NAK       0x2000      /* NAKed */				//�˵���NAK������Ӧ���еĽ�������
#define EP_RX_VALID     0x3000      /* Valid */				//�˵�����ڽ��ա�


/* Endpoint Buffer Descriptor */
typedef struct _EP_BUF_DSCR {
  U32 ADDR_TX;
  U32 COUNT_TX;
  U32 ADDR_RX;
  U32 COUNT_RX;
} EP_BUF_DSCR;

#define EP_ADDR_MASK    0xFFFE      /* Address Mask */
#define EP_COUNT_MASK   0x03FF      /* Count Mask */


#endif  /* __USBREG_H */
