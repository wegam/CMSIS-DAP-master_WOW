#include "CMSIS_KEY.H"


#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"



void KEY_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//关闭JTAG,SW功能开启
	//按键/充电
	GPIO_InitStructure.GPIO_Pin=KEY_CONNECTED_PIN;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU ;//复用推挽输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA和复用时钟
	GPIO_Init(KEY_CONNECTED_PORT,&GPIO_InitStructure);
	//充电完成
	GPIO_InitStructure.GPIO_Pin=STDBY_CONNECTED_PIN;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU ;//复用推挽输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOA和复用时钟
	GPIO_Init(STDBY_CONNECTED_PORT,&GPIO_InitStructure);
}

int8_t	Read_Input(void)
{
	int8_t	key=0;
	//右键/充电
	if(!GPIO_ReadInputDataBit(KEY_CONNECTED_PORT,KEY_CONNECTED_PIN))				//右键/正在充电
		key=0x01;
	if(!GPIO_ReadInputDataBit(STDBY_CONNECTED_PORT,STDBY_CONNECTED_PIN))		//左键/充电满
		key|=0x02;

		return key;
	//充电完成
}















