/******************************************************************************
 * @file	DAP.h
 * @brief	CMSIS-DAP Definitions
 * @version V1.00
 * @date	31. May 2012
 *
 * @note
 * Copyright (C) 2012 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#ifndef __DAP_H__
#define __DAP_H__

#include "stddef.h"
#include "stdint.h"


// DAP Command IDs
#define ID_DAP_Info								0x00		//获取DAP信息命令及响应标志
#define ID_DAP_LED								0x01		//指示类状态显示命令及响应标志
#define ID_DAP_Connect						0x02		//DAP连接命令及响应标志
#define ID_DAP_Disconnect					0x03		//DAP断开连接命令及响应标志
#define ID_DAP_TransferConfigure	0x04		//传输参数配置---重试，廷时控制类参数
#define ID_DAP_Transfer						0x05		//单个传输---获取芯片设备ID码（IDCODE）MCU device ID code(微控制器设备ID编码)
#define ID_DAP_TransferBlock			0x06		//块传输----SWD写入数据或者读出数据
#define ID_DAP_TransferAbort			0x07		//中止传输命令及响应
#define ID_DAP_WriteABORT					0x08		//中止写入命令及响应	
#define ID_DAP_Delay							0x09		//延时命令及响应
#define ID_DAP_ResetTarget				0x0A		//复位目标命令及响应
#define ID_DAP_SWJ_Pins						0x10
#define ID_DAP_SWJ_Clock					0x11
#define ID_DAP_SWJ_Sequence				0x12		//连接请求--数据高电平，给51个时钟，总线复位
#define ID_DAP_SWD_Configure			0x13
#define ID_DAP_JTAG_Sequence			0x14
#define ID_DAP_JTAG_Configure			0x15
#define ID_DAP_JTAG_IDCODE				0x16

// DAP Vendor Command IDs
#define ID_DAP_Vendor0				0x80
#define ID_DAP_Vendor1				0x81
#define ID_DAP_Vendor2				0x82
#define ID_DAP_Vendor3				0x83
#define ID_DAP_Vendor4				0x84
#define ID_DAP_Vendor5				0x85
#define ID_DAP_Vendor6				0x86
#define ID_DAP_Vendor7				0x87
#define ID_DAP_Vendor8				0x88
#define ID_DAP_Vendor9				0x89
#define ID_DAP_Vendor10				0x8A
#define ID_DAP_Vendor11				0x8B
#define ID_DAP_Vendor12				0x8C
#define ID_DAP_Vendor13				0x8D
#define ID_DAP_Vendor14				0x8E
#define ID_DAP_Vendor15				0x8F
#define ID_DAP_Vendor16				0x90
#define ID_DAP_Vendor17				0x91
#define ID_DAP_Vendor18				0x92
#define ID_DAP_Vendor19				0x93
#define ID_DAP_Vendor20				0x94
#define ID_DAP_Vendor21				0x95
#define ID_DAP_Vendor22				0x96
#define ID_DAP_Vendor23				0x97
#define ID_DAP_Vendor24				0x98
#define ID_DAP_Vendor25				0x99
#define ID_DAP_Vendor26				0x9A
#define ID_DAP_Vendor27				0x9B
#define ID_DAP_Vendor28				0x9C
#define ID_DAP_Vendor29				0x9D
#define ID_DAP_Vendor30				0x9E
#define ID_DAP_Vendor31				0x9F

#define ID_DAP_Invalid				0xFF

// DAP Status Code
#define DAP_OK						0
#define DAP_ERROR					0xFF

// DAP ID
#define DAP_ID_VENDOR						1				//获取供应商代码
#define DAP_ID_PRODUCT					2				//获取设备ID
#define DAP_ID_SER_NUM					3				//获取序列号
#define DAP_ID_FW_VER						4				//获取DAP固件版本
#define DAP_ID_DEVICE_VENDOR		5				//获取设备供应商代码
#define DAP_ID_DEVICE_NAME			6				//获取产品名称
#define DAP_ID_CAPABILITIES			0xF0		//获取容量
#define DAP_ID_PACKET_COUNT			0xFE		//获取接收和应答缓冲器大小
#define DAP_ID_PACKET_SIZE			0xFF		//获取包大小

// DAP LEDs
#define DAP_LED_DEBUGGER_CONNECTED	0
#define DAP_LED_TARGET_RUNNING		1

// DAP Port
#define DAP_PORT_AUTODETECT			0		// Autodetect Port
#define DAP_PORT_DISABLED			0		// Port Disabled (I/O pins in High-Z)
#define DAP_PORT_SWD				1		// SWD Port (SWCLK, SWDIO) + nRESET
#define DAP_PORT_JTAG				2		// JTAG Port (TCK, TMS, TDI, TDO, nTRST) + nRESET

// DAP SWJ Pins
#define DAP_SWJ_SWCLK_TCK			0		// SWCLK/TCK
#define DAP_SWJ_SWDIO_TMS			1		// SWDIO/TMS
#define DAP_SWJ_TDI					2		// TDI
#define DAP_SWJ_TDO					3		// TDO
#define DAP_SWJ_nTRST				5		// nTRST
#define DAP_SWJ_nRESET				7		// nRESET

// DAP Transfer Request
#define DAP_TRANSFER_APnDP			(1 << 0)
#define DAP_TRANSFER_RnW			(1 << 1)
#define DAP_TRANSFER_A2				(1 << 2)
#define DAP_TRANSFER_A3				(1 << 3)
#define DAP_TRANSFER_MATCH_VALUE	(1 << 4)
#define DAP_TRANSFER_MATCH_MASK		(1 << 5)

// DAP Transfer Response
//#define DAP_TRANSFER_OK				(1 << 0)
//#define DAP_TRANSFER_WAIT			(1 << 1)
//#define DAP_TRANSFER_FAULT			(1 << 2)
//#define DAP_TRANSFER_ERROR			(1 << 3)
//#define DAP_TRANSFER_MISMATCH		(1 << 4)
enum	DAP_TRANSFER
{
	DAP_TRANSFER_OK				=	0x01,
	DAP_TRANSFER_WAIT			=	0x02,
	DAP_TRANSFER_FAULT		=	0x04,
	DAP_TRANSFER_ERROR		=	0x08,
	DAP_TRANSFER_MISMATCH	=	0x10
};


// Debug Port Register Addresses
#define DP_IDCODE					0x00	// IDCODE Register (SW Read only)
#define DP_ABORT					0x00	// Abort Register (SW Write only)
#define DP_CTRL_STAT				0x04	// Control & Status
#define DP_WCR						0x04	// Wire Control Register (SW Only)
#define DP_SELECT					0x08	// Select Register (JTAG R/W & SW W)
#define DP_RESEND					0x08	// Resend (SW Read Only)
#define DP_RDBUFF					0x0C	// Read Buffer (Read Only)

// JTAG IR Codes
#define JTAG_ABORT					0x08
#define JTAG_DPACC					0x0A
#define JTAG_APACC					0x0B
#define JTAG_IDCODE					0x0E
#define JTAG_BYPASS					0x0F

// JTAG Sequence Info
#define JTAG_SEQUENCE_TCK			0x3F	// TCK count
#define JTAG_SEQUENCE_TMS			0x40	// TMS value
#define JTAG_SEQUENCE_TDO			0x80	// TDO capture



// DAP Data structure
typedef struct
{
	uint8_t	 debug_port;			// Debug Port						//调试接口-SWD：1/JATG：2
	uint8_t	 fast_clock;			// Fast Clock Flag			//高速时钟标志
	uint32_t	clock_delay;		// Clock Delay					//时钟廷迟
	struct {						// Transfer Configuration			//传输配置
		uint8_t	idle_cycles;		// Idle cycles after transfer		//传输后空闲周期
		uint16_t  retry_count;		// Number of retries after WAIT response	//在等待响应的重试次数
		uint16_t  match_retry;		// Number of retries if read value does not match	//如果读取的值不匹配时的重试次数
		uint32_t  match_mask;		// Match Mask		//匹配标志
	} transfer;

#if (DAP_SWD != 0)
	struct {						// SWD Configuration
		uint8_t		turnaround;		// Turnaround period		//周转期
		uint8_t		data_phase;		// Always generate Data Phase	//总是生成数据相位
	} swd_conf;
#endif

#if (DAP_JTAG != 0)
	struct {						// JTAG Device Chain
		uint8_t		count;			// Number of devices
		uint8_t		index;			// Device index (device at TDO has index 0)
#if (DAP_JTAG_DEV_CNT != 0)
		uint8_t	ir_length[DAP_JTAG_DEV_CNT];	// IR Length in bits
		uint16_t  ir_before[DAP_JTAG_DEV_CNT];	// Bits before IR
		uint16_t  ir_after [DAP_JTAG_DEV_CNT];	// Bits after IR
#endif
	} jtag_dev;
#endif

} DAP_Data_t;

extern		  DAP_Data_t DAP_Data;			// DAP Data
extern volatile uint8_t	DAP_TransferAbort;	// Transfer Abort Flag


// Functions
static uint8_t DAP_Info(uint8_t id, uint8_t *info);
#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
static __inline void TIMER_START (uint32_t usec);
static __inline void TIMER_STOP (void);
static __inline uint32_t TIMER_EXPIRED (void);
#endif

void Delayms(uint32_t delay);
static uint32_t DAP_Delay(uint8_t *request, uint8_t *response);
static uint32_t DAP_LED(uint8_t *request, uint8_t *response);
static uint32_t DAP_Connect(uint8_t *request, uint8_t *response);
static uint32_t DAP_Disconnect(uint8_t *response);
static uint32_t DAP_ResetTarget(uint8_t *response);

#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
static uint32_t DAP_SWJ_Pins(uint8_t *request, uint8_t *response);		//SWD时主要为复位
#endif

#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
static uint32_t DAP_SWJ_Clock(uint8_t *request, uint8_t *response);
#endif

#if ((DAP_SWD != 0) || (DAP_JTAG != 0))
static uint32_t DAP_SWJ_Sequence(uint8_t *request, uint8_t *response);
#endif

#if (DAP_SWD != 0)
static uint32_t DAP_SWD_Configure(uint8_t *request, uint8_t *response);
#endif

#if (DAP_SWD != 0)
static uint32_t DAP_SWD_Abort(uint8_t *request, uint8_t *response);
#endif

#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_Sequence(uint8_t *request, uint8_t *response);
#endif

#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_Configure(uint8_t *request, uint8_t *response);
#endif

#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_IDCode(uint8_t *request, uint8_t *response);
#endif

#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_Abort(uint8_t *request, uint8_t *response);
#endif

static uint32_t DAP_TransferConfigure(uint8_t *request, uint8_t *response);

#if (DAP_SWD != 0)
static uint32_t DAP_SWD_Transfer(uint8_t *request, uint8_t *response);
#endif

#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_Transfer(uint8_t *request, uint8_t *response);
#endif

#if (DAP_SWD != 0)
static uint32_t DAP_SWD_TransferBlock(uint8_t *request, uint8_t *response);
#endif

#if (DAP_JTAG != 0)
static uint32_t DAP_JTAG_TransferBlock(uint8_t *request, uint8_t *response);
#endif


extern void		SWJ_Sequence	(uint32_t count, uint8_t *data);
extern void		JTAG_Sequence	(uint32_t info,  uint8_t *tdi, uint8_t *tdo);
extern void		JTAG_IR			(uint32_t ir);
extern uint32_t	JTAG_ReadIDCode	(void);
extern void		JTAG_WriteAbort	(uint32_t data);
extern uint8_t	JTAG_Transfer	(uint8_t request, uint32_t *data);
extern uint8_t	SWD_Transfer	(uint8_t request, uint32_t *data);



extern uint32_t	DAP_ProcessVendorCommand(uint8_t *request, uint8_t *response);

extern uint32_t	DAP_ProcessCommand(uint8_t *request, uint8_t *response);
extern void		DAP_Setup(void);

// Configurable delay for clock generation
#define DELAY_SLOW_CYCLES		3	// Number of cycles for one iteration
static __forceinline void PIN_DELAY_SLOW (uint32_t delay)
{
	volatile int32_t count;

	count = delay;
	while (--count)
	{ }
}

// Fixed delay for fast clock generation
#define DELAY_FAST_CYCLES		0	// Number of cycles
static __forceinline void PIN_DELAY_FAST (void)
{
	//__nop();
}

#endif  /* __DAP_H__ */
