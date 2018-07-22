/*------------------------------------------------------------------------------
 *      RL-ARM - USB
 *------------------------------------------------------------------------------
 *      Name:    usb_msc.h
 *      Purpose: USB Mass Storage Device Class Definitions
 *      Rev.:    V4.70
 *------------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __USB_MSC_H__
#define __USB_MSC_H__

#include "RTL.h"

/* MSC Subclass Codes */
#define MSC_SUBCLASS_RBC                0x01
#define MSC_SUBCLASS_SFF8020I_MMC2      0x02
#define MSC_SUBCLASS_QIC157             0x03
#define MSC_SUBCLASS_UFI                0x04
#define MSC_SUBCLASS_SFF8070I           0x05
#define MSC_SUBCLASS_SCSI               0x06

/* MSC Protocol Codes */
#define MSC_PROTOCOL_CBI_INT            0x00
#define MSC_PROTOCOL_CBI_NOINT          0x01
#define MSC_PROTOCOL_BULK_ONLY          0x50


/* MSC Request Codes */
#define MSC_REQUEST_RESET               0xFF
#define MSC_REQUEST_GET_MAX_LUN         0xFE


/* MSC Bulk-only Stage */
#define MSC_BS_CBW                      0       /* Command Block Wrapper */					//һ������һ�������͹�������Ϣ�����ݰ�
#define MSC_BS_DATA_OUT                 1       /* Data Out Phase */								//���������豸�����ݴ��䡣
#define MSC_BS_DATA_IN                  2       /* Data In Phase */									//���豸�����������ݴ��䡣
#define MSC_BS_DATA_IN_LAST             3       /* Data In Last Phase */
#define MSC_BS_DATA_IN_LAST_STALL       4       /* Data In Last Phase with Stall */
#define MSC_BS_CSW                      5       /* Command Status Wrapper */				//һ������һ�������״̬�����ݰ���//����״̬��
#define MSC_BS_ERROR                    6       /* Error */													//����


/* Bulk-only Command Block Wrapper */
typedef __packed struct _MSC_CBW {
  U32 dSignature;					//����0x43425355����ʶΪCBW����顣
  U32 dTag;								//���������͵�CBW��ǩ���豸Ӧ������ص�CSW��dCSWTag����ͬ��ֵӦ��������
  U32 dDataLength;				//�ڱ�����ִ���ڼ䣬��������ͨ��Bulk-In��Bulk-Out�˵㴫������ݳ��ȡ����Ϊ0�����ʾ��֮��û�����ݴ��䡣
  U8  bmFlags;						//�������£�Bit7 Direction��dDataLengthΪ0ʱ����ֵ�����壩 ��Bit7=0�����ݴ��������豸��Bit7=1�����ݴ��豸��������Bit6��Obsolete 0��Bits 5..0��Reserved 0
  U8  bLUN;								//��ʾ���ڷ��������ֵ��豸���߼���Ԫ�ţ�LUN��������֧�ֶ��LUN���豸�������������Ӧ��LUNֵ�����򣬸�ֵΪ0��
  U8  bCBLength;					//CB����Ч�ֽڳ��ȡ���Чֵ����1��16֮�䡣
  U8  CB[16];							//���豸����ִ�е�����顣
} MSC_CBW;

/* Bulk-only Command Status Wrapper */
typedef __packed struct _MSC_CSW {
  U32 dSignature;					//����0x53425355����ʶΪCSW״̬��
  U32 dTag;								//ȡ���Ӧ��CBW��dCBWTagֵ��
  U32 dDataResidue;				//ʵ�ʴ�������ݸ���������Ҫ��������ݸ���֮�
  U8  bStatus;						//ָʾ�����ִ��״̬�����������ȷִ�У�bCSWStatus ����0 ������ȷ����1��phase����2����HOST�յ��˴���ʱ��Ҫ��Device��λ��
} MSC_CSW;

#define MSC_CBW_Signature               0x43425355
#define MSC_CSW_Signature               0x53425355


/* CSW Status Definitions */
#define CSW_CMD_PASSED                  0x00
#define CSW_CMD_FAILED                  0x01
#define CSW_PHASE_ERROR                 0x02


/* SCSI Commands */
#define SCSI_TEST_UNIT_READY            0x00
#define SCSI_REQUEST_SENSE              0x03
#define SCSI_FORMAT_UNIT                0x04
#define SCSI_INQUIRY                    0x12
#define SCSI_MODE_SELECT6               0x15
#define SCSI_MODE_SENSE6                0x1A
#define SCSI_START_STOP_UNIT            0x1B
#define SCSI_MEDIA_REMOVAL              0x1E
#define SCSI_READ_FORMAT_CAPACITIES     0x23
#define SCSI_READ_CAPACITY              0x25
#define SCSI_READ10                     0x28
#define SCSI_WRITE10                    0x2A
#define SCSI_VERIFY10                   0x2F
#define SCSI_SYNC_CACHE10               0x35
#define SCSI_READ12                     0xA8
#define SCSI_WRITE12                    0xAA
#define SCSI_MODE_SELECT10              0x55
#define SCSI_MODE_SENSE10               0x5A
#define SCSI_SYNC_CACHE16               0x91
#define SCSI_ATA_COMMAND_PASS_THROUGH12 0xA1
#define SCSI_ATA_COMMAND_PASS_THROUGH16 0x85
#define SCSI_SERVICE_ACTION_IN12        0xAB
#define SCSI_SERVICE_ACTION_IN16        0x9E
#define SCSI_SERVICE_ACTION_OUT12       0xA9
#define SCSI_SERVICE_ACTION_OUT16       0x9F


#endif  /* __USB_MSC_H__ */
