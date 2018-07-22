#include "CMSIS_MX25L4006E.H"

#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"


//#include "STM32F10x_BitBand.h"


/*##############################################################################
################################################################################

********************************************************************************

################################################################################
##############################################################################*/




#define  FLASH_WriteAddress     0x000001
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
#define  M25P64_FLASH_ID        0x202017
#define  BufferSize (countof(Tx_Buffer)-1)
//#define  BufferSize (300)

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))



/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private variables ---------------------------------------------------------*/
u8 Tx_Buffer[] = "STM32F10x SPI Firmware Library Example: communication with an M25P64 SPI FLASH";
u8 Index, Rx_Buffer[BufferSize];
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;

/* Private functions ---------------------------------------------------------*/
TestStatus Buffercmp(u8* pBuffer1, u8* pBuffer2, u16 BufferLength);

SPI_InitTypeDef  SPI_InitStructure;

vu32 FLASH_ID = 0;

vu32  Temp = 0;		//测试
u8	PageWriteFLG=0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CMSIS_MX25L4006E_Configuration(void)
{
//	SPI_StructConf(&SPI_InitStructure);										//配置参数
	
//	SPI_BASIC_Configuration(SPI1,&SPI_InitStructure);			//SPI常规配置
	
//	SPI_DMA_Configuration(SPI1,&SPI_InitStructure,(u32*)SPI_TX_Buffer,(u32*)SPI_RX_Buffer,SPI_BUFFERSIZE);				//SPI_DMA配置
	
//	PWM_Configuration(TIM2,7200,5000,50);	
	
//	SPIT_Configuration(SPI1);							//SPI常规使用方式配置
//	SPI_Cmd(SPI1, ENABLE);
//	SPI_I2S_ReceiveData(SPI1);
	
	CMSIS_MX25L4006E_GPIO_Configuration();
	CMSIS_MX25L4006E_SpiPort_Configuration();


}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CMSIS_MX25L4006E_Server(void)
{
	u8 Tsx_Buffer[] = "MX25L4006E";

	if(Temp++>20)
	{
		Temp=0;
		PageWriteFLG++;

	//使能SPI
	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
		
		if(PageWriteFLG<3)
		{
			FLASH_ID=SPI_FLASH_ReadID();
//			SPI_FLASH_SectorErase(0x000FFF);
			SPI_FLASH_PageWrite(Tsx_Buffer, 0x0000F8, 20);
		}
		SPI_FLASH_BufferRead(Rx_Buffer, 0x0000F8, 20);
		
//	FLASH_ID=SPI_FLASH_ReadID();
/* Perform a write in the Flash followed by a read of the written data */
  /* Erase SPI FLASH Sector to write on */
//  SPI_FLASH_SectorErase(FLASH_SectorToErase);

  /* Write Tx_Buffer data to SPI FLASH memory */
//  SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);

  /* Read data from SPI FLASH memory */
//  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);

  /* Check the corectness of written dada */
//  TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
  /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
     are the same */
  /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
     are different */

  /* Perform an erase in the Flash followed by a read of the written data */
  /* Erase SPI FLASH Sector to write on */
//  SPI_FLASH_SectorErase(FLASH_SectorToErase);

  /* Read data from SPI FLASH memory */
//  SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
	
	//关闭SPI
	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
		
	}
	else
	{
//		Temp=0;
		FLASH_ID=0;
////		PA4=1;
////		PA5=1;
////		PA6=1;
////		PA7=1;
//		SPI_FLASH_CS_DISABLE;
//		SPI_Cmd(SPI_FLASH_SPI_PORT,DISABLE);
//		SPI_NSSInternalSoftwareConfig(SPI_FLASH_SPI_PORT,SPI_NSSInternalSoft_Reset);
//		CMSIS_MX25L4006E_ReadID();
	}
	
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CMSIS_MX25L4006E_GPIO_Configuration(void)
{
	//结构体定义
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//打开相应管脚时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	SPI_FLASH_MOSI_CLOCK(ENABLE);
	SPI_FLASH_MISO_CLOCK(ENABLE);
	SPI_FLASH_SCLK_CLOCK(ENABLE);
	SPI_FLASH_NSS_CLOCK(ENABLE);
	
	//MOSI管脚定义
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_MOSI_PORT,&GPIO_InitStructure);
	//MISO管脚定义
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_MISO_PORT,&GPIO_InitStructure);
	//SCLK管脚定义
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_SCLK_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_SCLK_PORT,&GPIO_InitStructure);
	//NSS管脚定义
	GPIO_InitStructure.GPIO_Pin=SPI_FLASH_NSS_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;				//GPIO_Mode_Out_PP  //GPIO_Mode_AF_PP
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(SPI_FLASH_NSS_PORT,&GPIO_InitStructure);
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CMSIS_MX25L4006E_SpiPort_Configuration(void)
{
	//结构体定义
	SPI_InitTypeDef	SPI_InitStructure;
	//打开SPI时钟
	SPI_FLASH_CLOCK(ENABLE);
	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
	//设置SPI参数
	SPI_InitStructure.SPI_Direction						=		SPI_Direction_2Lines_FullDuplex;	//设置方向				（2线全双工、2线只接收、一线发送、一线接收）
	SPI_InitStructure.SPI_Mode								=		SPI_Mode_Master;									//模式         	（从或主设备）
	SPI_InitStructure.SPI_DataSize						=		SPI_DataSize_8b;									//宽度         	（8或16位）
	SPI_InitStructure.SPI_CPOL								=		SPI_CPOL_High;										//时钟极性     	（低或高）
	SPI_InitStructure.SPI_CPHA								=		SPI_CPHA_2Edge;					 					//时钟相位     	（第一个或第二个跳变沿）
	SPI_InitStructure.SPI_NSS									=		SPI_NSS_Hard;											//片选方式     	（硬件或软件方式）
	SPI_InitStructure.SPI_BaudRatePrescaler		=		SPI_BaudRatePrescaler_8;					//波特率预分频 	（从2---256分频）
	SPI_InitStructure.SPI_FirstBit						=		SPI_FirstBit_MSB;									//最先发送的位 	（最低位，还是最高位在先）
	SPI_InitStructure.SPI_CRCPolynomial				=		0X07;															//设置crc多项式 （数字）如7
	//初始化SPI
	SPI_Init(SPI_FLASH_SPI_PORT,&SPI_InitStructure);	
	//3)**********使能SPIx_NESS为主输出模式
	SPI_SSOutputCmd(SPI_FLASH_SPI_PORT, ENABLE);		//如果在主机模式下的片选方式为硬件（SPI_NSS_Hard）方式，此处必须打开，否则NSS无信号
	//使能SPI
	SPI_Cmd(SPI_FLASH_SPI_PORT,DISABLE);
	
//	SPI_NSSInternalSoftwareConfig(SPI_FLASH_SPI_PORT,SPI_NSSInternalSoft_Reset);
}


/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_ENABLE(void)
{
	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_DISABLE(void)
{
	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
u8 SPI_FLASH_SendByte(u8 byte)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI_FLASH_SPI_PORT, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI_FLASH_SPI_PORT);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_SendHalfWord
* Description    : Sends a Half Word through the SPI interface and return the
*                  Half Word received from the SPI bus.
* Input          : Half Word : Half Word to send.
* Output         : None
* Return         : The value of the received Half Word.
*******************************************************************************/
u16 SPI_FLASH_SendHalfWord(u16 HalfWord)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_TXE) == RESET);

  /* Send Half Word through the SPI1 peripheral */
  SPI_I2S_SendData(SPI_FLASH_SPI_PORT, HalfWord);

  /* Wait to receive a Half Word */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the Half Word read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI_FLASH_SPI_PORT);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_SectorErase(u32 SectorAddr)
{
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();

  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send Sector Erase instruction */
  SPI_FLASH_SendByte(SE);
  /* Send SectorAddr high nibble address byte */
  SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /* Send SectorAddr medium nibble address byte */
  SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /* Send SectorAddr low nibble address byte */
  SPI_FLASH_SendByte(SectorAddr & 0xFF);
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BulkErase
* Description    : Erases the entire FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BlockErase(void)
{
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();

  /* Bulk Erase */
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send Bulk Erase instruction  */
  SPI_FLASH_SendByte(BE);
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_ChipErase(void)
{

}
/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
  /* Enable the write access to the FLASH */
  SPI_FLASH_WriteEnable();

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send "Write to Memory " instruction */
  SPI_FLASH_SendByte(PP);
  /* Send WriteAddr high nibble address byte to write to */
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /* Send WriteAddr medium nibble address byte to write to */
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /* Send WriteAddr low nibble address byte to write to */
  SPI_FLASH_SendByte(WriteAddr & 0xFF);

  /* while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /* Send the current byte */
    SPI_FLASH_SendByte(*pBuffer);
    /* Point on the next byte to be written */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;								//计算起始页地址/
  count = SPI_FLASH_PageSize - Addr;										//计算起始页地址
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;			//计算需要的页数量
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;		//计算不满一整页的字节数

	//******起始地址为页起始地址---可以从页0地址开始按页写
  if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */		
  {
		//******写入数据未超过1页及未跨页
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	//******起始地址非页起始地址--需要限制起始页写入数量以免覆盖及出错
  else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
			//******跨页
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(READ);

  /* Send ReadAddr high nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr	&	0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr	&	0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte to read from */
  SPI_FLASH_SendByte(ReadAddr	& 0xFF);

  while (NumByteToRead--) /* while there is data to be read */
  {
    /* Read a byte from the FLASH */
    *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadID(void)
{
  u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
	
	 /* Send "RDID " instruction */
  SPI_FLASH_SendByte(0x9F);

  /* Read a byte from the FLASH */
  Temp0 = SPI_FLASH_SendByte(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp1 = SPI_FLASH_SendByte(Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp2 = SPI_FLASH_SendByte(Dummy_Byte);
  
	//数据转换
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
	
	
	
	/* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
  return Temp;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	Read Electronic Manufacturer ID & Device ID (REMS)
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_ReadElectronicManufacturer(void)
{

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	Read SFDP Mode
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_ReadSFDPMode(void)
{

}
/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(u32 ReadAddr)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(READ);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
u8 SPI_FLASH_ReadByte(void)
{
  return (SPI_FLASH_SendByte(Dummy_Byte));
}


/*******************************************************************************
*函数名			:	function
*功能描述		:	Read Data Bytes At Higher Speed
*输入				: 
*返回值			:	无
*******************************************************************************/
u8 SPI_FLASH_ReadByteHS(u8 byte)
{

}


/*******************************************************************************
* Function Name  : SPI_FLASH_WriteEnable
* Description    : Enables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Write Enable" instruction */
  SPI_FLASH_SendByte(WREN);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_WriteDisable(void)
{

}
/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
  u8 FLASH_Status = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read Status Register" instruction */
  SPI_FLASH_SendByte(RDSR);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);

  }
  while ((FLASH_Status & WIP_Flag) == SET); /* Write in progress */

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/




/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
u8 SPI_FLASH_ReadStatusRegister(void)
{

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_WriteStatusRegister(u8 Status)
{

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_DualOutputMode(void)
{

}

/*******************************************************************************
*函数名			:	function
*功能描述		:	Deep Power-down
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_DeepPowerDown(void)
{

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	Release from Deep Power-down (RDP), Read Electronic Signature (RES)
*输入				: 
*返回值			:	无
*******************************************************************************/
void SPI_FLASH_RSDeepPowerDown(void)
{

}



















































/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
u8 CMSIS_MX25L4006E_SendByte(u8 byte)
{
	  /* 等待DR寄存器空 */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_TXE) == RESET);
	 
  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI_FLASH_SPI_PORT, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH_SPI_PORT, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI_FLASH_SPI_PORT);

}
/*******************************************************************************
*函数名			:	MX25L4006E_WriteEnable
*功能描述		:	写使能
*输入				: 
*输出				:	无
*返回值			:	无
*例程				:
*调用函数		:
*被调用函数	:
*******************************************************************************/
void CMSIS_MX25L4006E_WriteEnable(void)		//MX25L4006E写使能命令
{
//	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
	SPI_I2S_SendData(SPI_FLASH_SPI_PORT,WREN);
//	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	等待命令执行结束
							执行写使能会值位状态寄存器中的BUSY位，只有BUSY位变为0时说明写使能命令执行完成
*输入				: 
*输出				:	无
*返回值			:	无
*例程				:
*调用函数		:
*被调用函数	:
*******************************************************************************/
void CMSIS_MX25L4006E_WaitForWriteEnd(void)		//等待命令执行结束
{
	u8  FLASH_Status = 0;
  //1)**********使能芯片
//	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
  //2)**********发送读取状态寄存器命令
	CMSIS_MX25L4006E_SendByte(0X05);
  //3)**********读取状态寄存器直到完成
	do
	{
    //3.0)**********发送任意（虚拟）数据，读取状态
		FLASH_Status = CMSIS_MX25L4006E_SendByte(0x00);
	}
  while ((FLASH_Status & 0X01) == SET); 
//	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	扇区擦除//在写入数据前先要对芯片进行擦除。
*输入				: 
*输出				:	无
*返回值			:	无
*例程				:
*调用函数		:
*被调用函数	:
*******************************************************************************/
void CMSIS_MX25L4006E_SectorErase(void)		//扇区擦除
{
	//1)**********发送写使能命令
	CMSIS_MX25L4006E_WriteEnable();				//MX25L4006E写使能命令
	//2)**********使能写命令是一个写状态寄存器的命令，所以要等待该命令执行完，才能写其他命令
	CMSIS_MX25L4006E_WaitForWriteEnd();		//等待命令执行结束
	//3)**********擦除扇区
	//3.1)**********发送写使能命令
//	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
	//3.2)**********发送擦除扇区命令
	CMSIS_MX25L4006E_SendByte(0X20);
	//3.3)**********发送要擦除的起始地址

}

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CMSIS_MX25L4006E_COMMAND(unsigned char Command)
{

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CMSIS_MX25L4006E_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(READ);

  /* Send ReadAddr high nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte to read from */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);

  while (NumByteToRead--) /* while there is data to be read */
  {
    /* Read a byte from the FLASH */
    *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
u32 CMSIS_MX25L4006E_ReadID(void)
{
	u32	Temp0=0,Temp1=0,Temp2=0;
	FLASH_ID=0;
  /* Select the FLASH: Chip Select low */
//  SPI_FLASH_CS_LOW();
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	SPI_FLASH_CS_ENABLE;
//	while(Temp0++<500);
//	SPI_Cmd(SPI_FLASH_SPI_PORT, ENABLE);
  /* Send "RDID " instruction */
  CMSIS_MX25L4006E_SendByte(0x9F);
//	SPI_SendByte(0X00);
//	SPI_SendByte(0X00);
//	SPI_SendByte(0X00);
  /* Read a byte from the FLASH */
  Temp0 = CMSIS_MX25L4006E_SendByte(0X01);

  /* Read a byte from the FLASH */
  Temp1 = CMSIS_MX25L4006E_SendByte(0X01);

  /* Read a byte from the FLASH */
  Temp2 = CMSIS_MX25L4006E_SendByte(0X01);

  /* Deselect the FLASH: Chip Select high */
//  SPI_FLASH_CS_HIGH();
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);

  FLASH_ID = (Temp0 << 16) | (Temp1 << 8) | Temp2;
//	while(Temp0++<500);
//	SPI_Cmd(SPI_FLASH_SPI_PORT, DISABLE);
	SPI_FLASH_CS_DISABLE;
  return FLASH_ID;	
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CMSIS_MX25L4006E_StartReadSequence(u32 ReadAddr)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(READ);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
}




