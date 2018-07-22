#include "CMSIS_ADC.H"


#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

int16_t ADC_Result[4]={0};
int16_t ADC_Value[4]={0};

int16_t ADC_num=0;
//int16_t ADC_Ch1[10]={0};
//int16_t ADC_Ch2[10]={0};
//int16_t ADC_Ch3[10]={0};
//int16_t ADC_Ch4[10]={0};
//extern int16_t ADC_Value[4];


void ADC_Configuration(void)
{
	#ifdef	STM32_CDC
	
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure; 						//ADC�ṹ��
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIOA�͸���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ʹ��ADCʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ʹ��DMA����
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC���ʱ�䲻�ܳ���14M

	
		//ADC
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
		//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN ;//�����������	
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
		#ifdef	ADC_TEST
			//ADC
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING ;//�����������	
			GPIO_Init(ADC_CONNECTED_PORT,&GPIO_InitStructure);	
			
			//ADC
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING ;//�����������	
			GPIO_Init(GPIOA,&GPIO_InitStructure);		
		#endif
	

	

	
//	ADC_DeInit(ADC1); 																												//������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 													//ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode =ENABLE; 																//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 													//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 				//ת��������������ⲿ��������--�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 											//ADC�����Ҷ���
	#ifdef	ADC_TEST
		ADC_InitStructure.ADC_NbrOfChannel = 4; 																		//˳����й���ת����ADCͨ������Ŀ
	#else
		ADC_InitStructure.ADC_NbrOfChannel = 1; 																		//˳����й���ת����ADCͨ������Ŀ
	#endif
//	ADC_InitStructure.ADC_NbrOfChannel = ADC_InitStructure.ADC_NbrOfChannel++;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,ADC_SampleTime_239Cycles5);		//VBAT
	#ifdef	ADC_TEST	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2,ADC_SampleTime_239Cycles5);		//ADC	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 4,ADC_SampleTime_239Cycles5);		//ADC
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3,ADC_SampleTime_239Cycles5);		//ADC
	#endif
	
	// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
	ADC_DMACmd(ADC1, ENABLE);

	ADC_Cmd(ADC1, ENABLE); 											//ʹ��ָ����ADC1
	
		
	DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_Value; //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	#ifdef	ADC_TEST
		DMA_InitStructure.DMA_BufferSize = 4; //DMAͨ����DMA����Ĵ�С
	#else
		DMA_InitStructure.DMA_BufferSize = 1; //DMAͨ����DMA����Ĵ�С
	#endif
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

//	DMA_Cmd(DMA1_Channel1, ENABLE); //����DMAͨ��

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE); //����DMAͨ��
	
	
//	ADC_ResetCalibration(ADC1);   //����У׼ 
//	while(ADC_GetResetCalibrationStatus(ADC1));  //�ȴ�����У׼���
//	ADC_StartCalibration(ADC1); 	//��ʼУ׼
//	while(ADC_GetCalibrationStatus(ADC1));    //�ȴ�У׼���
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	//����ת����ʼ��ADCͨ��DMA��ʽ���ϵĸ���RAM����
	#endif	
}

int16_t	Read_ADC(void)
{
//	int16_t ADC_NUM=0;

//	ADC_NUM=ADC_GetConversionValue(ADC1);
//	
//	return ADC_NUM;
	
//	int8_t i=0; 
//	
////	unsigned chari,a,b,c,d;
//	for(i=0;i<8;i++)
//	{
//		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,ADC_SampleTime_239Cycles5);
//		ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	//����ת����ʼ��ADCͨ��DMA��ʽ���ϵĸ���RAM����
//		
////		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
////		ADC_SoftwareStartConvCmd(ADC1,ENABLE);//����ת��
//		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
//		ADC_Result += ADC_GetConversionValue(ADC1);
//	}
//	
////	ADC_Result = ADC_Result >>3;
////	ADC_Result = (unsigned int)(((unsigned long)ADC_Result)*3300>>12);//ת��Ϊ���ֵ�ѹֵ
////	a = ADC_Result/1000;
////	b =(ADC_Result-a*1000)/100;
////	c =(ADC_Result-a*1000-b*100)/10;
////	d =(ADC_Result-a*1000-b*100-c*10);
//	ADC_Result=ADC_Result/8;
//	return ADC_Result;

//	return ADC_Value[0];
	++ADC_num;	
	
//	ADC_Ch1[ADC_num]=ADC_Value[0];
//	ADC_Ch2[ADC_num]=ADC_Value[1];
//	ADC_Ch3[ADC_num]=ADC_Value[2];
//	ADC_Ch4[ADC_num]=ADC_Value[3];
	
	ADC_Result[0]=(ADC_Result[0]+ADC_Value[0])/2;
	#ifdef	ADC_TEST
		ADC_Result[1]=(ADC_Result[1]+ADC_Value[1])/2;
		ADC_Result[2]=(ADC_Result[2]+ADC_Value[2])/2;
		ADC_Result[3]=(ADC_Result[3]+ADC_Value[3])/2;
	#endif
	
	if(ADC_num==1000)
	{
		int16_t ADC_temp=0;
		ADC_num=0;
		if(ADC_Result[0]<=2200)
			ADC_temp=0;
		else				
			ADC_temp=((((ADC_Result[0]-2200)*100)/(2400-2200))>100? 100:(((ADC_Result[0]-2200)*100)/(2400-2200)));
		return ADC_temp;
	}
	return -1;
}















