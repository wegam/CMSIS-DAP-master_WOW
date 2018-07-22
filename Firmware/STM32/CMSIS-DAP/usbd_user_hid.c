

#include "usbd_user_hid.h"

#include "string.h"
#include "RTL.h"
#include "rl_usb.h"
//#include <..\..\RL\USB\INC\usb.h>
#include "usb.h"

#define __NO_USB_LIB_C
#include "usb_config.c"

#include "CMSIS_Conf.H"
#include "DAP.h"

#if (USBD_HID_OUTREPORT_MAX_SZ != DAP_PACKET_SIZE)
	#error "USB HID Output Report Size must match DAP Packet Size"
#endif
#if (USBD_HID_INREPORT_MAX_SZ != DAP_PACKET_SIZE)
	#error "USB HID Input Report Size must match DAP Packet Size"
#endif

extern UserAppDescriptor_t * pUserAppDescriptor;

static volatile uint8_t  USB_RequestFlag;       // Request  Buffer Usage Flag		//���󻺳�������ʹ�ñ�־��1δ����0���������
static volatile uint32_t USB_RequestIn;         // Request  Buffer In  Index
static volatile uint32_t USB_RequestOut;        // Request  Buffer Out Index

static volatile uint8_t  USB_ResponseIdle;      // Response Buffer Idle  Flag
static volatile uint8_t  USB_ResponseFlag;      // Response Buffer Usage Flag
static volatile uint32_t USB_ResponseIn;        // Response Buffer In  Index
static volatile uint32_t USB_ResponseOut;       // Response Buffer Out Index

static          uint8_t  USB_Request [DAP_PACKET_COUNT][DAP_PACKET_SIZE];  // Request  Buffer
static          uint8_t  USB_Response[DAP_PACKET_COUNT][DAP_PACKET_SIZE];  // Response Buffer
//!!! static          uint8_t  HID_Flash_Buffer[DAP_PACKET_SIZE];

/*******************************************************************************
*������			:	usbd_hid_init
*��������		:	//HID��ʼ��--����������ΪĬ��ֵ
*����				: 
*����ֵ			:	��
*******************************************************************************/
// USB HID Callback: when system initializes
void usbd_hid_init (void)
{
	USB_RequestFlag   = 0;			// USB_RequestFlag---Request  Buffer Usage Flag		//���󻺳�������ʹ�ñ�־��1δ����0���������
	USB_RequestIn     = 0;
	USB_RequestOut    = 0;
	USB_ResponseIdle  = 1;
	USB_ResponseFlag  = 0;
	USB_ResponseIn    = 0;
	USB_ResponseOut   = 0;
}

// USB HID Callback: when data needs to be prepared for the host
int usbd_hid_get_report (U8 rtype, U8 rid, U8 *buf, U8 req)
{
	switch (rtype)
	{
	case HID_REPORT_INPUT:
		switch (req)
		{
		case USBD_HID_REQ_EP_CTRL:
		case USBD_HID_REQ_PERIOD_UPDATE:
			break;
		case USBD_HID_REQ_EP_INT:
			if ((USB_ResponseOut != USB_ResponseIn) || USB_ResponseFlag)
			{
				memcpy(buf, USB_Response[USB_ResponseOut], DAP_PACKET_SIZE);
				USB_ResponseOut++;
				if (USB_ResponseOut == DAP_PACKET_COUNT)
					USB_ResponseOut = 0;
				if (USB_ResponseOut == USB_ResponseIn)
					USB_ResponseFlag = 0;
				return (DAP_PACKET_SIZE);
			}
			else
				USB_ResponseIdle = 1;
			break;
		}
		break;
	case HID_REPORT_FEATURE:
		break;
	}
	return (0);
}
/*******************************************************************************
*������			:	usbd_hid_set_report
*��������		:	��ȡUSB���ջ��������ݲ����浽USB_Request������
*����				: rtype		��������	HID_REPORT_INPUT==0x01;HID_REPORT_OUTPUT==0x02;HID_REPORT_FEATURE==0x03
							rid			������
							*buf		Դ����ָ��
							len			���ݳ���
							req			USBD_HID_REQ_EP_INT��Request from interrupt endpoint��
*����ֵ			:	��
*******************************************************************************/
// USB HID Callback: when data is received from the host
void usbd_hid_set_report (U8 rtype, U8 rid, U8 *buf, int len, U8 req)
{
	switch (rtype)
	{
		case HID_REPORT_OUTPUT:									//���������������豸���գ�
			if (len == 0)	
				break;
			if (buf[0] == ID_DAP_TransferAbort)		//ID_DAP_TransferAbort			0x07		//��ֹ���������Ӧ
			{
				if (pUserAppDescriptor != NULL)
					pUserAppDescriptor->UserAbort();	//ִ�к�����UserAppAbort();���ܣ�DAP_TransferAbort = 1;��������ֹ��־��1
				break;
			}
			if (USB_RequestFlag && (USB_RequestIn == USB_RequestOut))		// USB_RequestFlag---Request  Buffer Usage Flag		//���󻺳�������ʹ�ñ�־��1δ����0���������
				break;  // Discard packet when buffer is full

			// Store data into request packet buffer
			memcpy(USB_Request[USB_RequestIn], buf, len);		//�����ջ��������ݱ��浽USB_Request����������
			USB_RequestIn++;																//��ά���ݵ�ַ����
			if (USB_RequestIn == DAP_PACKET_COUNT)					//��ά�����Ѵﵽ���洢��64
				USB_RequestIn = 0;														//���ص������ʼ��ַ
			if (USB_RequestIn == USB_RequestOut)
				USB_RequestFlag = 1;													// USB_RequestFlag---Request  Buffer Usage Flag		//���󻺳�������ʹ�ñ�־��1δ����0���������
			break;
		case HID_REPORT_FEATURE:								
			break;
	}
}

#define PACK_DATA_PLONG(offs)	(uint32_t *)(*(uint32_t *)(request + offs))
#define PACK_DATA_PBYTE(offs)	(uint8_t *) (*(uint32_t *)(request + offs))
#define PACK_DATA_LONG(offs)	*(uint32_t *)(request + offs)
#define PACK_DATA_WORD(offs)	*(uint16_t *)(request + 4)

#define HID_Command0	0xD0			//	Get device info
#define HID_Command1	0xD1			//	FLASH_Unlock();
#define HID_Command2	0xD2			//	FLASH_Lock();
#define HID_Command3	0xD3			//	PACK_DATA_LONG(0);
#define HID_Command4	0xD4			// 	Check for blank (0xFF)
#define HID_Command5	0xD5			// 	Write to flash
#define HID_Command6	0xD6			// 	Read from flash
#define HID_Command7	0xD7			// 	Reset device

/*******************************************************************************
*������			:	HID_ProcessCommand
*��������		:	HID�����
*����				: *request---�����������ݻ�������
							*response--��Ӧ/�������洢����
*����ֵ			:	��
*******************************************************************************/
void HID_ProcessCommand(uint8_t *request, uint8_t *response)
{
	uint8_t result   = 0xFF; //! DAP_OK;
	uint16_t data;
	uint16_t length;
	uint32_t address;
	uint8_t *p_address;

	if ((*request >= HID_Command0) && (*request <= HID_Command7))		//*request>=0XD0,*request<=0XD7		//��������USB DFU
	{
		DEBUG("REQ:%2X\n", *request);

		*response++ = *request;
		switch (*request++)
		{
		// Get device info
		case HID_Command0:
			address = DBGMCU->IDCODE;
			*response++ = (address >>  0) & 0xFF;
			*response++ = (address >>  8) & 0xFF;
			*response++ = (address >> 16) & 0xFF;
			*response++ = (address >> 24) & 0xFF;
			break;
		// Unlock flash
		case HID_Command1:
			FLASH_Unlock();
			break;
		// Lock flash
		case HID_Command2:
			FLASH_Lock();
			break;
		// Erase page
		case HID_Command3:
			address = PACK_DATA_LONG(0);
			if (FLASH_ErasePage(address) != FLASH_COMPLETE)
				result = DAP_ERROR;
			break;
		// Check for blank (0xFF)
		case HID_Command4:
			p_address = PACK_DATA_PBYTE(0);
			length  = PACK_DATA_WORD(4);
			while (length-- != 0)
				if (*p_address++ != 0xFF)
				{
					result = DAP_ERROR;
					break;
				}
			break;
		// Write to flash
		case HID_Command5:
			address = PACK_DATA_LONG(0);
			length  = PACK_DATA_WORD(4);
			if (length > (DAP_PACKET_SIZE - (6+2)))	// Check for maximum data payload
				result = DAP_ERROR;
			else
			{
				request += 6;
				while (length-- != 0)
				{
					data = *request++;
					if (length != 0)
					{
						data |= ((uint16_t)(*request++) << 8);
						length--;
					}
					if (FLASH_ProgramHalfWord(address, data) != FLASH_COMPLETE)
					{
						result = DAP_ERROR;
						break;
					}
					address += 2;
				}
			}
			break;
		// Read from flash
		case HID_Command6:
			{
				p_address = PACK_DATA_PBYTE(0);
				length  = PACK_DATA_WORD(4);
				if (length > (DAP_PACKET_SIZE - (2)))	// Check for maximum data payload
					result = DAP_ERROR;
				else
				{
					*response++ = DAP_OK;
					while (length-- != 0)
					{
						if (length == 0)
							result = *p_address;
						else
							*response++ = *p_address++;
					}
				}
			}
			break;
		// Reset device
		case HID_Command7:
			NVIC_SystemReset();
			break;
		default:
			--response;
			result = ID_DAP_Invalid;
		}
		*response = result;
	}
	else		//DAP-�¼�����
	{
		if (pUserAppDescriptor != NULL)
		{
			pUserAppDescriptor->UserProcess(USB_Request[USB_RequestOut], USB_Response[USB_ResponseIn]);	//����DAP���׼����Ӧ����
//			DAP_ProcessCommand(USB_Request[USB_RequestOut], USB_Response[USB_ResponseIn]);
		}
		else
		{
			DEBUG("REQ:%02X no app\n", *request);
			*response = ID_DAP_Invalid;
		}
	}

	DEBUG("RES:%2X\n", *response);
}

// Process USB HID Data
uint8_t usbd_hid_process(void)
{
	uint32_t n;

	// Process pending requests
	if ((USB_RequestOut != USB_RequestIn) || USB_RequestFlag)		// USB_RequestFlag---Request  Buffer Usage Flag		//���󻺳�������ʹ�ñ�־��1δ����0���������
	{
		HID_ProcessCommand(USB_Request[USB_RequestOut], USB_Response[USB_ResponseIn]);		//����HID���DFU�������DAP�����׼����Ӧ���ݣ�USB_Request�������ݻ�������USB_Response��Ӧ/������ݻ�������

		// Update request index and flag
		n = USB_RequestOut + 1;					//��ά�����ַ��1
		if (n == DAP_PACKET_COUNT)			//#define DAP_PACKET_COUNT	64
			n = 0;
		USB_RequestOut = n;

		if (USB_RequestOut == USB_RequestIn)	//USB_Request��USB_Response����ά�����е�ַ��ͬ����ʾ�����Ѿ��������
			USB_RequestFlag = 0;								// Request  Buffer Usage Flag		//���󻺳�������ʹ�ñ�־��1δ����0���������

		if (USB_ResponseIdle)									//��������δ���͸�����
		{	// Request that data is send back to host
			USB_ResponseIdle = 0;
			usbd_hid_get_report_trigger(0, USB_Response[USB_ResponseIn], DAP_PACKET_SIZE);			//#define DAP_PACKET_SIZE			64		//USB�豸HID��ȡ���津����//���ϱ����ݴ���USB��Ӧ������
		}
		else
		{	// Update response index and flag
			n = USB_ResponseIn + 1;
			if (n == DAP_PACKET_COUNT)	//#define DAP_PACKET_COUNT	64
				n = 0;
			USB_ResponseIn = n;

			if (USB_ResponseIn == USB_ResponseOut)
				USB_ResponseFlag = 1;
		}
		return 1;
	}
	return 0;
}
