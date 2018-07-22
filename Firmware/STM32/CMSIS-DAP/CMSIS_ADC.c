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
	ADC_InitTypeDef ADC_InitStructure; 						//ADC结构体
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIOA和复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能ADC时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA传输
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //72M/6=12,ADC最大时间不能超过14M

	
		//ADC
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
		//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN ;//复用推挽输出	
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
		#ifdef	ADC_TEST
			//ADC
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING ;//复用推挽输出	
			GPIO_Init(ADC_CONNECTED_PORT,&GPIO_InitStructure);	
			
			//ADC
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING ;//复用推挽输出	
			GPIO_Init(GPIOA,&GPIO_InitStructure);		
		#endif
	

	

	
//	ADC_DeInit(ADC1); 																												//将外设 ADC1 的全部寄存器重设为缺省值
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 													//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ScanConvMode =ENABLE; 																//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 													//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 				//转换由软件而不是外部触发启动--外部触发转换关闭
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 											//ADC数据右对齐
	#ifdef	ADC_TEST
		ADC_InitStructure.ADC_NbrOfChannel = 4; 																		//顺序进行规则转换的ADC通道的数目
	#else
		ADC_InitStructure.ADC_NbrOfChannel = 1; 																		//顺序进行规则转换的ADC通道的数目
	#endif
//	ADC_InitStructure.ADC_NbrOfChannel = ADC_InitStructure.ADC_NbrOfChannel++;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1,ADC_SampleTime_239Cycles5);		//VBAT
	#ifdef	ADC_TEST	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 2,ADC_SampleTime_239Cycles5);		//ADC	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 4,ADC_SampleTime_239Cycles5);		//ADC
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3,ADC_SampleTime_239Cycles5);		//ADC
	#endif
	
	// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
	ADC_DMACmd(ADC1, ENABLE);

	ADC_Cmd(ADC1, ENABLE); 											//使能指定的ADC1
	
		
	DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_Value; //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
	#ifdef	ADC_TEST
		DMA_InitStructure.DMA_BufferSize = 4; //DMA通道的DMA缓存的大小
	#else
		DMA_InitStructure.DMA_BufferSize = 1; //DMA通道的DMA缓存的大小
	#endif
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道

//	DMA_Cmd(DMA1_Channel1, ENABLE); //启动DMA通道

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE); //启动DMA通道
	
	
//	ADC_ResetCalibration(ADC1);   //重新校准 
//	while(ADC_GetResetCalibrationStatus(ADC1));  //等待重新校准完成
//	ADC_StartCalibration(ADC1); 	//开始校准
//	while(ADC_GetCalibrationStatus(ADC1));    //等待校准完成
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	//连续转换开始，ADC通过DMA方式不断的更新RAM区。
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
//		ADC_SoftwareStartConvCmd(ADC1, ENABLE); 	//连续转换开始，ADC通过DMA方式不断的更新RAM区。
//		
////		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
////		ADC_SoftwareStartConvCmd(ADC1,ENABLE);//启动转换
//		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
//		ADC_Result += ADC_GetConversionValue(ADC1);
//	}
//	
////	ADC_Result = ADC_Result >>3;
////	ADC_Result = (unsigned int)(((unsigned long)ADC_Result)*3300>>12);//转换为数字电压值
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















