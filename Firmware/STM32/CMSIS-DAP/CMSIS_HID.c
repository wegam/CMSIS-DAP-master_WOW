#include "CMSIS_HID.H"

#include "usbd_user_hid.h"



int32_t CMSIS_HID_Process(void)
{
	if (usbd_hid_process())		//扫描HID处理
	{
		return 1;
	}
	else
	{
		return 0;
	}

//	if (pUserAppDescriptor == NULL)		//已配置，后面不使用
//		{	// No user application
//			if (led_count++ == 1000)
//			{
//				led_count = 0;
//				LedConnectedToggle();
//			}
//			usbd_hid_process();
//		}
//		else if (!usbd_hid_process())		//扫描HID处理
//		{
			// No packet processing
//			if (led_timeout == 1000)
//			{
//				LedConnectedOn();
//			}
//			else if (led_timeout == 0)
//			{
//				LedConnectedOff();
//				led_timeout = TIMEOUT_DELAY;
//			}
//			led_timeout--;
			
//		}
//		else
//		{
//			led_timeout = TIMEOUT_DELAY;
//		}
}













