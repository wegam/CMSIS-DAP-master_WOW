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
#define MSC_BS_CBW                      0       /* Command Block Wrapper */					//一个包含一个命令块和关联的信息的数据包
#define MSC_BS_DATA_OUT                 1       /* Data Out Phase */								//从主机到设备的数据传输。
#define MSC_BS_DATA_IN                  2       /* Data In Phase */									//从设备到主机的数据传输。
#define MSC_BS_DATA_IN_LAST             3       /* Data In Last Phase */
#define MSC_BS_DATA_IN_LAST_STALL       4       /* Data In Last Phase with Stall */
#define MSC_BS_CSW                      5       /* Command Status Wrapper */				//一个包含一个命令块状态的数据包。//命令状态包
#define MSC_BS_ERROR                    6       /* Error */													//错误


/* Bulk-only Command Block Wrapper */
typedef __packed struct _MSC_CBW {
  U32 dSignature;					//常数0x43425355，标识为CBW命令块。
  U32 dTag;								//由主机发送的CBW标签。设备应该在相关的CSW的dCSWTag以相同的值应答主机。
  U32 dDataLength;				//在本命令执行期间，主机期望通过Bulk-In或Bulk-Out端点传输的数据长度。如果为0，则表示这之间没有数据传输。
  U8  bmFlags;						//定义如下（Bit7 Direction（dDataLength为0时，该值无意义） ：Bit7=0：数据从主机到设备，Bit7=1：数据从设备到主机，Bit6：Obsolete 0，Bits 5..0：Reserved 0
  U8  bLUN;								//表示正在发送命令字的设备的逻辑单元号（LUN）。对于支持多个LUN的设备，主机设置相对应的LUN值。否则，该值为0。
  U8  bCBLength;					//CB的有效字节长度。有效值是在1到16之间。
  U8  CB[16];							//被设备解析执行的命令块。
} MSC_CBW;

/* Bulk-only Command Status Wrapper */
typedef __packed struct _MSC_CSW {
  U32 dSignature;					//常数0x53425355，标识为CSW状态块
  U32 dTag;								//取相对应的CBW的dCBWTag值。
  U32 dDataResidue;				//实际传输的数据个数和期望要传输的数据个数之差。
  U8  bStatus;						//指示命令的执行状态。如果命令正确执行，bCSWStatus 返回0 ，不正确返回1，phase错返回2（当HOST收到此错误时需要对Device复位）
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
