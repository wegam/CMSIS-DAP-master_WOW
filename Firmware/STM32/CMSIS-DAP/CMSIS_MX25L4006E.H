#ifndef __CMSIS_MX25L4006E_H
#define __CMSIS_MX25L4006E_H

#include "stm32f10x.h"
#include "STM32F10x_BitBand.h"


/* Private define ------------------------------------------------------------*/

//SPI接口定义
#define SPI_FLASH_RCC													RCC_APB2Periph_SPI1
#define SPI_FLASH_SPI_PORT										SPI1
#define SPI_FLASH_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_RCC, FunctionalState)

//MOSI管脚定义
#define SPI_FLASH_MOSI_RCC			RCC_APB2Periph_GPIOA
#define	SPI_FLASH_MOSI_PORT			GPIOA
#define	SPI_FLASH_MOSI_PIN			GPIO_Pin_7
#define SPI_FLASH_MOSI_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MOSI_RCC, FunctionalState)
//MISO管脚定义
#define SPI_FLASH_MISO_RCC			RCC_APB2Periph_GPIOA
#define	SPI_FLASH_MISO_PORT			GPIOA
#define	SPI_FLASH_MISO_PIN			GPIO_Pin_6
#define SPI_FLASH_MISO_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MISO_RCC, FunctionalState)
//SCLK管脚定义
#define SPI_FLASH_SCLK_RCC			RCC_APB2Periph_GPIOA
#define	SPI_FLASH_SCLK_PORT			GPIOA
#define	SPI_FLASH_SCLK_PIN			GPIO_Pin_5
#define SPI_FLASH_SCLK_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_SCLK_RCC, FunctionalState)
//NSS管脚定义
#define SPI_FLASH_NSS_RCC				RCC_APB2Periph_GPIOA
#define	SPI_FLASH_NSS_PORT			GPIOA
#define	SPI_FLASH_NSS_PIN				GPIO_Pin_4
#define SPI_FLASH_NSS_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_NSS_RCC, FunctionalState)

#define	SPI_FLASH_CS_ENABLE		PA4=0
#define	SPI_FLASH_CS_DISABLE	PA4=1

#define	SPI_FLASH_CS_LOW()		PA4=0
#define	SPI_FLASH_CS_HIGH()		PA4=1



#define	MX25L4006E

#if defined (MX25L4006E)			//MX25L4006E命令定义

//MX25L4006E参数：总共8个块，一个块128个扇区，一个扇区16页，一页256Byte
//1)容量：4M-BIT 512KB
//2)块数量：8
//3)扇区数量：128
//4)每个扇区大小：4K
//5)页大小：256Byte

	#define	WRSR		(unsigned char)0x01				//写状态寄存器
	#define	PP			(unsigned char)0x02				//写页面
	#define	READ		(unsigned char)0x03				//读数据
	#define	WRDI		(unsigned char)0x04				//写失能
	#define	RDSR		(unsigned char)0x05				//读状态寄存器
	#define	WREN		(unsigned char)0x06				//写使能
	#define	FREAD		(unsigned char)0x0B				//快速读取数据
	#define	SE			(unsigned char)0x20				//扇区擦除
	#define	DREAD		(unsigned char)0x3B				//
	#define	BE			(unsigned char)0x52				//块擦除		也可以用0XD8
	#define	RDSFDP	(unsigned char)0x5A				//
	#define	CE			(unsigned char)0x60				//芯片擦除; 整片擦除; 也可以用0XC7
	#define	REMS		(unsigned char)0x90				//读制造商代码和产品代码
	#define	RDID		(unsigned char)0x9F				//读设备信息，3byte；第一字节为制造商代码，第二第三字节为芯片代码
	#define	RES			(unsigned char)0xAB				//读器件地址
	#define	DP			(unsigned char)0xB9				//深度省电状态
	#define	RDP			(unsigned char)0xAB				//退出深度掉电

#else
	#define PP      0x02  /* Write to Memory instruction */
	#define WRSR       0x01  /* Write Status Register instruction */
	#define WREN       0x06  /* Write enable instruction */
	#define READ       0x03  /* Read from Memory instruction */
	#define RDSR       0x05  /* Read Status Register instruction  */
	#define RDID       0x9F  /* Read identification */
	#define SE         0x20  /* Sector Erase instruction */
	#define BE         0x52  /* Bulk Erase instruction */
#endif


#define SPI_FLASH_PageSize    256										//页大小




#define WIP_Flag   0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xA5





extern vu32 FLASH_ID;
extern vu32 Temp;



void CMSIS_MX25L4006E_Configuration(void);
void CMSIS_MX25L4006E_Server(void);

void CMSIS_MX25L4006E_GPIO_Configuration(void);
void CMSIS_MX25L4006E_SpiPort_Configuration(void);




/* Exported functions ------------------------------------------------------- */

/*----- 底层函数---宏定义需要修改部分 -----*/
//void SPI_FLASH_CS_LOW(void);
//void SPI_FLASH_CS_HIGH(void);

void SPI_ENABLE(void);		//使能SPI接口
void SPI_DISABLE(void);		//禁止SPI接口

u8 SPI_FLASH_SendByte(u8 byte);	//写一个字节数据
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);	//写入半个字（16位）


/*----- 功能函数 -----*/
void SPI_FLASH_SectorErase(u32 SectorAddr);					//擦除扇区
void SPI_FLASH_BlockErase(void);										//擦除块
void SPI_FLASH_ChipErase(void);											//擦除整个芯片
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);		//页写入
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);	//批量写入
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);		//指读取
u32 SPI_FLASH_ReadID(void);													//读Flash ID
void SPI_FLASH_ReadElectronicManufacturer(void);		//读产品信息和ID
void SPI_FLASH_ReadSFDPMode(void);									//读FLASH参数
void SPI_FLASH_StartReadSequence(u32 ReadAddr);			//读请求
u8 SPI_FLASH_ReadByte(void);												//读一个字节数据
u8 SPI_FLASH_ReadByteHS(u8 byte);										//高速读取一个字节
void SPI_FLASH_WriteEnable(void);										//写使能
void SPI_FLASH_WriteDisable(void);									//写禁止
void SPI_FLASH_WaitForWriteEnd(void);								//等待写入完成
u8 SPI_FLASH_ReadStatusRegister(void);							//读Flash状态寄存器
void SPI_FLASH_WriteStatusRegister(u8 Status);			//宝状态寄存器
void SPI_FLASH_DualOutputMode(void);								//
void SPI_FLASH_DeepPowerDown(void);									//进入深度低功耗
void SPI_FLASH_RSDeepPowerDown(void);								//退出低功耗模式

#endif



