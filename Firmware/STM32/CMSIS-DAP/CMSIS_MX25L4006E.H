#ifndef __CMSIS_MX25L4006E_H
#define __CMSIS_MX25L4006E_H

#include "stm32f10x.h"
#include "STM32F10x_BitBand.h"


/* Private define ------------------------------------------------------------*/

//SPI�ӿڶ���
#define SPI_FLASH_RCC													RCC_APB2Periph_SPI1
#define SPI_FLASH_SPI_PORT										SPI1
#define SPI_FLASH_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_RCC, FunctionalState)

//MOSI�ܽŶ���
#define SPI_FLASH_MOSI_RCC			RCC_APB2Periph_GPIOA
#define	SPI_FLASH_MOSI_PORT			GPIOA
#define	SPI_FLASH_MOSI_PIN			GPIO_Pin_7
#define SPI_FLASH_MOSI_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MOSI_RCC, FunctionalState)
//MISO�ܽŶ���
#define SPI_FLASH_MISO_RCC			RCC_APB2Periph_GPIOA
#define	SPI_FLASH_MISO_PORT			GPIOA
#define	SPI_FLASH_MISO_PIN			GPIO_Pin_6
#define SPI_FLASH_MISO_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_MISO_RCC, FunctionalState)
//SCLK�ܽŶ���
#define SPI_FLASH_SCLK_RCC			RCC_APB2Periph_GPIOA
#define	SPI_FLASH_SCLK_PORT			GPIOA
#define	SPI_FLASH_SCLK_PIN			GPIO_Pin_5
#define SPI_FLASH_SCLK_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_SCLK_RCC, FunctionalState)
//NSS�ܽŶ���
#define SPI_FLASH_NSS_RCC				RCC_APB2Periph_GPIOA
#define	SPI_FLASH_NSS_PORT			GPIOA
#define	SPI_FLASH_NSS_PIN				GPIO_Pin_4
#define SPI_FLASH_NSS_CLOCK(FunctionalState)			RCC_APB2PeriphClockCmd(SPI_FLASH_NSS_RCC, FunctionalState)

#define	SPI_FLASH_CS_ENABLE		PA4=0
#define	SPI_FLASH_CS_DISABLE	PA4=1

#define	SPI_FLASH_CS_LOW()		PA4=0
#define	SPI_FLASH_CS_HIGH()		PA4=1



#define	MX25L4006E

#if defined (MX25L4006E)			//MX25L4006E�����

//MX25L4006E�������ܹ�8���飬һ����128��������һ������16ҳ��һҳ256Byte
//1)������4M-BIT 512KB
//2)��������8
//3)����������128
//4)ÿ��������С��4K
//5)ҳ��С��256Byte

	#define	WRSR		(unsigned char)0x01				//д״̬�Ĵ���
	#define	PP			(unsigned char)0x02				//дҳ��
	#define	READ		(unsigned char)0x03				//������
	#define	WRDI		(unsigned char)0x04				//дʧ��
	#define	RDSR		(unsigned char)0x05				//��״̬�Ĵ���
	#define	WREN		(unsigned char)0x06				//дʹ��
	#define	FREAD		(unsigned char)0x0B				//���ٶ�ȡ����
	#define	SE			(unsigned char)0x20				//��������
	#define	DREAD		(unsigned char)0x3B				//
	#define	BE			(unsigned char)0x52				//�����		Ҳ������0XD8
	#define	RDSFDP	(unsigned char)0x5A				//
	#define	CE			(unsigned char)0x60				//оƬ����; ��Ƭ����; Ҳ������0XC7
	#define	REMS		(unsigned char)0x90				//�������̴���Ͳ�Ʒ����
	#define	RDID		(unsigned char)0x9F				//���豸��Ϣ��3byte����һ�ֽ�Ϊ�����̴��룬�ڶ������ֽ�ΪоƬ����
	#define	RES			(unsigned char)0xAB				//��������ַ
	#define	DP			(unsigned char)0xB9				//���ʡ��״̬
	#define	RDP			(unsigned char)0xAB				//�˳���ȵ���

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


#define SPI_FLASH_PageSize    256										//ҳ��С




#define WIP_Flag   0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xA5





extern vu32 FLASH_ID;
extern vu32 Temp;



void CMSIS_MX25L4006E_Configuration(void);
void CMSIS_MX25L4006E_Server(void);

void CMSIS_MX25L4006E_GPIO_Configuration(void);
void CMSIS_MX25L4006E_SpiPort_Configuration(void);




/* Exported functions ------------------------------------------------------- */

/*----- �ײ㺯��---�궨����Ҫ�޸Ĳ��� -----*/
//void SPI_FLASH_CS_LOW(void);
//void SPI_FLASH_CS_HIGH(void);

void SPI_ENABLE(void);		//ʹ��SPI�ӿ�
void SPI_DISABLE(void);		//��ֹSPI�ӿ�

u8 SPI_FLASH_SendByte(u8 byte);	//дһ���ֽ�����
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);	//д�����֣�16λ��


/*----- ���ܺ��� -----*/
void SPI_FLASH_SectorErase(u32 SectorAddr);					//��������
void SPI_FLASH_BlockErase(void);										//������
void SPI_FLASH_ChipErase(void);											//��������оƬ
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);		//ҳд��
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);	//����д��
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);		//ָ��ȡ
u32 SPI_FLASH_ReadID(void);													//��Flash ID
void SPI_FLASH_ReadElectronicManufacturer(void);		//����Ʒ��Ϣ��ID
void SPI_FLASH_ReadSFDPMode(void);									//��FLASH����
void SPI_FLASH_StartReadSequence(u32 ReadAddr);			//������
u8 SPI_FLASH_ReadByte(void);												//��һ���ֽ�����
u8 SPI_FLASH_ReadByteHS(u8 byte);										//���ٶ�ȡһ���ֽ�
void SPI_FLASH_WriteEnable(void);										//дʹ��
void SPI_FLASH_WriteDisable(void);									//д��ֹ
void SPI_FLASH_WaitForWriteEnd(void);								//�ȴ�д�����
u8 SPI_FLASH_ReadStatusRegister(void);							//��Flash״̬�Ĵ���
void SPI_FLASH_WriteStatusRegister(u8 Status);			//��״̬�Ĵ���
void SPI_FLASH_DualOutputMode(void);								//
void SPI_FLASH_DeepPowerDown(void);									//������ȵ͹���
void SPI_FLASH_RSDeepPowerDown(void);								//�˳��͹���ģʽ

#endif


