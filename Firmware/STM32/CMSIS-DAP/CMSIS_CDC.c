
#include "CMSIS_CDC.H"
#include "CMSIS_Conf.H"
#include "usbd_cdc_acm.h"
#include "usbd_user_cdc_acm.h"


int32_t usb_rx_ch=0;
int32_t usb_tx_ch=0;

























/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
int32_t CMSIS_CDC_Process(void)
{	
	int32_t rx_num=0;
	//********************从USB接收的数据返回到USB
		NotifyOnStatusChange();

		//从USB接收数据长度
		if (usb_rx_ch == -1)
		{
			usb_rx_ch = USBD_CDC_ACM_GetChar();					//从USB读取数据，一字节数据
//			usb_tx_ch	= usb_rx_ch;			
		}		
		if (usb_rx_ch != -1)
		{
			rx_num=1;
			if (UART_PutChar (usb_rx_ch) == usb_rx_ch)	//从串口发送数据
			usb_rx_ch=-1;
		}
		//从USB上传数据
		if (usb_tx_ch != -1)
		{
			if (USBD_CDC_ACM_PutChar(usb_tx_ch) == usb_tx_ch)			//从USB上传数据
				usb_tx_ch = -1;
		}
		if (usb_tx_ch == -1)
		{
			usb_tx_ch = UART_GetChar();						//从串口读取数据
		}			
		return(rx_num);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void send_char(char ch)
{
	if (ch == '\n')
		send_char('\r');
	while (USBD_CDC_ACM_PutChar(ch) != ch)
	{ }
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
PUTCHAR_PROTOTYPE
{
	send_char(ch);
	return ch;
}











