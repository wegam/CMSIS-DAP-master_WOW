
#include "CMSIS_CDC.H"
#include "CMSIS_Conf.H"
#include "usbd_cdc_acm.h"
#include "usbd_user_cdc_acm.h"


int32_t usb_rx_ch=0;
int32_t usb_tx_ch=0;

























/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
int32_t CMSIS_CDC_Process(void)
{	
	int32_t rx_num=0;
	//********************��USB���յ����ݷ��ص�USB
		NotifyOnStatusChange();

		//��USB�������ݳ���
		if (usb_rx_ch == -1)
		{
			usb_rx_ch = USBD_CDC_ACM_GetChar();					//��USB��ȡ���ݣ�һ�ֽ�����
//			usb_tx_ch	= usb_rx_ch;			
		}		
		if (usb_rx_ch != -1)
		{
			rx_num=1;
			if (UART_PutChar (usb_rx_ch) == usb_rx_ch)	//�Ӵ��ڷ�������
			usb_rx_ch=-1;
		}
		//��USB�ϴ�����
		if (usb_tx_ch != -1)
		{
			if (USBD_CDC_ACM_PutChar(usb_tx_ch) == usb_tx_ch)			//��USB�ϴ�����
				usb_tx_ch = -1;
		}
		if (usb_tx_ch == -1)
		{
			usb_tx_ch = UART_GetChar();						//�Ӵ��ڶ�ȡ����
		}			
		return(rx_num);
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
void send_char(char ch)
{
	if (ch == '\n')
		send_char('\r');
	while (USBD_CDC_ACM_PutChar(ch) != ch)
	{ }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*******************************************************************************/
PUTCHAR_PROTOTYPE
{
	send_char(ch);
	return ch;
}











