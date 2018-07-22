#include "CMSIS_KEY.H"


#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"



void KEY_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//�ر�JTAG,SW���ܿ���
	//����/���
	GPIO_InitStructure.GPIO_Pin=KEY_CONNECTED_PIN;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU ;//�����������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA�͸���ʱ��
	GPIO_Init(KEY_CONNECTED_PORT,&GPIO_InitStructure);
	//������
	GPIO_InitStructure.GPIO_Pin=STDBY_CONNECTED_PIN;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU ;//�����������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOA�͸���ʱ��
	GPIO_Init(STDBY_CONNECTED_PORT,&GPIO_InitStructure);
}

int8_t	Read_Input(void)
{
	int8_t	key=0;
	//�Ҽ�/���
	if(!GPIO_ReadInputDataBit(KEY_CONNECTED_PORT,KEY_CONNECTED_PIN))				//�Ҽ�/���ڳ��
		key=0x01;
	if(!GPIO_ReadInputDataBit(STDBY_CONNECTED_PORT,STDBY_CONNECTED_PIN))		//���/�����
		key|=0x02;

		return key;
	//������
}















