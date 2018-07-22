/******************** (C)  ********************
* 功能名称 			:STM32位绑定宏定义
*部分内容来源自网络
*把文件格式修改为.H文件 
********************************************************************************/
/********************************位带定义**************************************
* 位带操作,实现51类似的GPIO控制功能
* 具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
* IO口操作宏定义
******************************************************************************/

/********************************说明**************************************
* 1 位绑定公式--位绑定两个区域
* SRAM 区 0x2000 0000 ~ 0x200f ffff
* 假设绑定后新的地址为 AliasAddr = 0x22000000 +（(A-0x2000 0000)*8 +n）4；
* A 是变量的地址是在SRAM 区之间 具体是哪一个不知道
* n 是在变量中的位
* 片上外设 0x4000 0000 ~ 0x400f ffff
* 假设绑定后新的地址为  AliasAddr = 0x42000000 +（(A-0x4000 0000)*8 +n）4；
* 									0x42000000 +（(A-0x4000 0000)*32 +n*4）；
* 需要注意的是位绑定只有最后一位为有效值；
* (需要先配置IO）
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_BitBand_H
#define __STM32F10x_BitBand_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_map.h"
 

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
 //把该地址转换成一个指针
 #define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))

 #define BIT_ADDR(addr, bitnum)   MEM_ADDR( BITBAND(addr, bitnum)  )

 #define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
 #define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
 #define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
 #define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
 #define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C

 #define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
 #define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
 #define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
 #define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
 #define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808

//-----------------------------------------------------
 //-----------------------------------------------------
 //使用方法：连接字符串			##
 //例：PAout(0)=1;PBout(3)=0;
 //----------------------------------------------------- 
 //**********输出
#define PAO(n)	PA##n
#define PBO(n)	PB##n
#define PCO(n)	PC##n
#define PDO(n)	PD##n
#define PEO(n)	PE##n
//**********输入
#define PAI(n)	PA##n
#define PBI(n)	PB##n
#define PCI(n)	PC##n
#define PDI(n)	PD##n
#define PEI(n)	PE##n
//-----------------------------------------------------
 //-----------------------------------------------------
 //使用方法：
 //例：PAout(0)=1;PBout(3)=0;
 //-----------------------------------------------------
#define PAout(n) BITBAND(GPIOA_ODR_Addr,n)
#define PAin(n) BITBAND(GPIOA_IDR_Addr,n)
#define PBout(n) BITBAND(GPIOB_ODR_Addr,n)
#define PBin(n) BITBAND(GPIOB_IDR_Addr,n)
#define PCout(n) BITBAND(GPIOC_ODR_Addr,n)
#define PCin(n) BITBAND(GPIOC_IDR_Addr,n)
#define PDout(n) BITBAND(GPIOD_ODR_Addr,n)
#define PDin(n) BITBAND(GPIOD_IDR_Addr,n)
#define PEout(n) BITBAND(GPIOE_ODR_Addr,n)
#define PEin(n) BITBAND(GPIOE_IDR_Addr,n)
//-----------------------------------------------------
 //-----------------------------------------------------
 //使用方法：
 //例：PA0=1;PB0=0;
 //-----------------------------------------------------
 #define PA0   BIT_ADDR(GPIOA_ODR_Addr, 0)  //输出
 #define PA1   BIT_ADDR(GPIOA_ODR_Addr, 1)  //输出
 #define PA2   BIT_ADDR(GPIOA_ODR_Addr, 2)  //输出
 #define PA3   BIT_ADDR(GPIOA_ODR_Addr, 3)  //输出
 #define PA4   BIT_ADDR(GPIOA_ODR_Addr, 4)  //输出
 #define PA5   BIT_ADDR(GPIOA_ODR_Addr, 5)  //输出
 #define PA6   BIT_ADDR(GPIOA_ODR_Addr, 6)  //输出
 #define PA7   BIT_ADDR(GPIOA_ODR_Addr, 7)  //输出
 #define PA8   BIT_ADDR(GPIOA_ODR_Addr, 8)  //输出
 #define PA9   BIT_ADDR(GPIOA_ODR_Addr, 9)  //输出
 #define PA10  BIT_ADDR(GPIOA_ODR_Addr, 10) //输出
 #define PA11  BIT_ADDR(GPIOA_ODR_Addr, 11) //输出
 #define PA12  BIT_ADDR(GPIOA_ODR_Addr, 12) //输出
 #define PA13  BIT_ADDR(GPIOA_ODR_Addr, 13) //输出
 #define PA14  BIT_ADDR(GPIOA_ODR_Addr, 14) //输出
 #define PA15  BIT_ADDR(GPIOA_ODR_Addr, 15) //输出

 #define PA0in   BIT_ADDR(GPIOA_IDR_Addr, 0)  //输入
 #define PA1in   BIT_ADDR(GPIOA_IDR_Addr, 1)  //输入
 #define PA2in   BIT_ADDR(GPIOA_IDR_Addr, 2)  //输入
 #define PA3in   BIT_ADDR(GPIOA_IDR_Addr, 3)  //输入
 #define PA4in   BIT_ADDR(GPIOA_IDR_Addr, 4)  //输入
 #define PA5in   BIT_ADDR(GPIOA_IDR_Addr, 5)  //输入
 #define PA6in   BIT_ADDR(GPIOA_IDR_Addr, 6)  //输入
 #define PA7in   BIT_ADDR(GPIOA_IDR_Addr, 7)  //输入
 #define PA8in   BIT_ADDR(GPIOA_IDR_Addr, 8)  //输入
 #define PA9in   BIT_ADDR(GPIOA_IDR_Addr, 9)  //输入
 #define PA10in  BIT_ADDR(GPIOA_IDR_Addr, 10) //输入
 #define PA11in  BIT_ADDR(GPIOA_IDR_Addr, 11) //输入
 #define PA12in  BIT_ADDR(GPIOA_IDR_Addr, 12) //输入
 #define PA13in  BIT_ADDR(GPIOA_IDR_Addr, 13) //输入
 #define PA14in  BIT_ADDR(GPIOA_IDR_Addr, 14) //输入
 #define PA15in  BIT_ADDR(GPIOA_IDR_Addr, 15) //输入

 //-----------------------------------------------------
 #define PB0   BIT_ADDR(GPIOB_ODR_Addr, 0)  //输出
 #define PB1   BIT_ADDR(GPIOB_ODR_Addr, 1)  //输出
 #define PB2   BIT_ADDR(GPIOB_ODR_Addr, 2)  //输出
 #define PB3   BIT_ADDR(GPIOB_ODR_Addr, 3)  //输出
 #define PB4   BIT_ADDR(GPIOB_ODR_Addr, 4)  //输出
 #define PB5   BIT_ADDR(GPIOB_ODR_Addr, 5)  //输出
 #define PB6   BIT_ADDR(GPIOB_ODR_Addr, 6)  //输出
 #define PB7   BIT_ADDR(GPIOB_ODR_Addr, 7)  //输出
 #define PB8   BIT_ADDR(GPIOB_ODR_Addr, 8)  //输出
 #define PB9   BIT_ADDR(GPIOB_ODR_Addr, 9)  //输出
 #define PB10  BIT_ADDR(GPIOB_ODR_Addr, 10) //输出
 #define PB11  BIT_ADDR(GPIOB_ODR_Addr, 11) //输出
 #define PB12  BIT_ADDR(GPIOB_ODR_Addr, 12) //输出
 #define PB13  BIT_ADDR(GPIOB_ODR_Addr, 13) //输出
 #define PB14  BIT_ADDR(GPIOB_ODR_Addr, 14) //输出
 #define PB15  BIT_ADDR(GPIOB_ODR_Addr, 15) //输出

 #define PB0in   BIT_ADDR(GPIOB_IDR_Addr, 0)  //输入
 #define PB1in   BIT_ADDR(GPIOB_IDR_Addr, 1)  //输入
 #define PB2in   BIT_ADDR(GPIOB_IDR_Addr, 2)  //输入
 #define PB3in   BIT_ADDR(GPIOB_IDR_Addr, 3)  //输入
 #define PB4in   BIT_ADDR(GPIOB_IDR_Addr, 4)  //输入
 #define PB5in   BIT_ADDR(GPIOB_IDR_Addr, 5)  //输入
 #define PB6in   BIT_ADDR(GPIOB_IDR_Addr, 6)  //输入
 #define PB7in   BIT_ADDR(GPIOB_IDR_Addr, 7)  //输入
 #define PB8in   BIT_ADDR(GPIOB_IDR_Addr, 8)  //输入
 #define PB9in   BIT_ADDR(GPIOB_IDR_Addr, 9)  //输入
 #define PB10in  BIT_ADDR(GPIOB_IDR_Addr, 10) //输入
 #define PB11in  BIT_ADDR(GPIOB_IDR_Addr, 11) //输入
 #define PB12in  BIT_ADDR(GPIOB_IDR_Addr, 12) //输入
 #define PB13in  BIT_ADDR(GPIOB_IDR_Addr, 13) //输入
 #define PB14in  BIT_ADDR(GPIOB_IDR_Addr, 14) //输入
 #define PB15in  BIT_ADDR(GPIOB_IDR_Addr, 15) //输入
 //----------------------------------------------------
 #define PC0   BIT_ADDR(GPIOC_ODR_Addr, 0)  //输出
 #define PC1   BIT_ADDR(GPIOC_ODR_Addr, 1)  //输出
 #define PC2   BIT_ADDR(GPIOC_ODR_Addr, 2)  //输出
 #define PC3   BIT_ADDR(GPIOC_ODR_Addr, 3)  //输出
 #define PC4   BIT_ADDR(GPIOC_ODR_Addr, 4)  //输出
 #define PC5   BIT_ADDR(GPIOC_ODR_Addr, 5)  //输出
 #define PC6   BIT_ADDR(GPIOC_ODR_Addr, 6)  //输出
 #define PC7   BIT_ADDR(GPIOC_ODR_Addr, 7)  //输出
 #define PC8   BIT_ADDR(GPIOC_ODR_Addr, 8)  //输出
 #define PC9   BIT_ADDR(GPIOC_ODR_Addr, 9)  //输出
 #define PC10  BIT_ADDR(GPIOC_ODR_Addr, 10) //输出
 #define PC11  BIT_ADDR(GPIOC_ODR_Addr, 11) //输出
 #define PC12  BIT_ADDR(GPIOC_ODR_Addr, 12) //输出
 #define PC13  BIT_ADDR(GPIOC_ODR_Addr, 13) //输出
 #define PC14  BIT_ADDR(GPIOC_ODR_Addr, 14) //输出
 #define PC15  BIT_ADDR(GPIOC_ODR_Addr, 15) //输出

 #define PC0in   BIT_ADDR(GPIOC_IDR_Addr, 0)  //输入
 #define PC1in   BIT_ADDR(GPIOC_IDR_Addr, 1)  //输入
 #define PC2in   BIT_ADDR(GPIOC_IDR_Addr, 2)  //输入
 #define PC3in   BIT_ADDR(GPIOC_IDR_Addr, 3)  //输入
 #define PC4in   BIT_ADDR(GPIOC_IDR_Addr, 4)  //输入
 #define PC5in   BIT_ADDR(GPIOC_IDR_Addr, 5)  //输入
 #define PC6in   BIT_ADDR(GPIOC_IDR_Addr, 6)  //输入
 #define PC7in   BIT_ADDR(GPIOC_IDR_Addr, 7)  //输入
 #define PC8in   BIT_ADDR(GPIOC_IDR_Addr, 8)  //输入
 #define PC9in   BIT_ADDR(GPIOC_IDR_Addr, 9)  //输入
 #define PC10in  BIT_ADDR(GPIOC_IDR_Addr, 10) //输入
 #define PC11in  BIT_ADDR(GPIOC_IDR_Addr, 11) //输入
 #define PC12in  BIT_ADDR(GPIOC_IDR_Addr, 12) //输入
 #define PC13in  BIT_ADDR(GPIOC_IDR_Addr, 13) //输入
 #define PC14in  BIT_ADDR(GPIOC_IDR_Addr, 14) //输入
 #define PC15in  BIT_ADDR(GPIOC_IDR_Addr, 15) //输入

 //----------------------------------------------------
 #define PD0   BIT_ADDR(GPIOD_ODR_Addr, 0)  //输出
 #define PD1   BIT_ADDR(GPIOD_ODR_Addr, 1)  //输出
 #define PD2   BIT_ADDR(GPIOD_ODR_Addr, 2)  //输出
 #define PD3   BIT_ADDR(GPIOD_ODR_Addr, 3)  //输出
 #define PD4   BIT_ADDR(GPIOD_ODR_Addr, 4)  //输出
 #define PD5   BIT_ADDR(GPIOD_ODR_Addr, 5)  //输出
 #define PD6   BIT_ADDR(GPIOD_ODR_Addr, 6)  //输出
 #define PD7   BIT_ADDR(GPIOD_ODR_Addr, 7)  //输出
 #define PD8   BIT_ADDR(GPIOD_ODR_Addr, 8)  //输出
 #define PD9   BIT_ADDR(GPIOD_ODR_Addr, 9)  //输出
 #define PD10  BIT_ADDR(GPIOD_ODR_Addr, 10) //输出
 #define PD11  BIT_ADDR(GPIOD_ODR_Addr, 11) //输出
 #define PD12  BIT_ADDR(GPIOD_ODR_Addr, 12) //输出
 #define PD13  BIT_ADDR(GPIOD_ODR_Addr, 13) //输出
 #define PD14  BIT_ADDR(GPIOD_ODR_Addr, 14) //输出
 #define PD15  BIT_ADDR(GPIOD_ODR_Addr, 15) //输出

 #define PD0in   BIT_ADDR(GPIOD_IDR_Addr, 0)  //输入
 #define PD1in   BIT_ADDR(GPIOD_IDR_Addr, 1)  //输入
 #define PD2in   BIT_ADDR(GPIOD_IDR_Addr, 2)  //输入
 #define PD3in   BIT_ADDR(GPIOD_IDR_Addr, 3)  //输入
 #define PD4in   BIT_ADDR(GPIOD_IDR_Addr, 4)  //输入
 #define PD5in   BIT_ADDR(GPIOD_IDR_Addr, 5)  //输入
 #define PD6in   BIT_ADDR(GPIOD_IDR_Addr, 6)  //输入
 #define PD7in   BIT_ADDR(GPIOD_IDR_Addr, 7)  //输入
 #define PD8in   BIT_ADDR(GPIOD_IDR_Addr, 8)  //输入
 #define PD9in   BIT_ADDR(GPIOD_IDR_Addr, 9)  //输入
 #define PD10in  BIT_ADDR(GPIOD_IDR_Addr, 10) //输入
 #define PD11in  BIT_ADDR(GPIOD_IDR_Addr, 11) //输入
 #define PD12in  BIT_ADDR(GPIOD_IDR_Addr, 12) //输入
 #define PD13in  BIT_ADDR(GPIOD_IDR_Addr, 13) //输入
 #define PD14in  BIT_ADDR(GPIOD_IDR_Addr, 14) //输入
 #define PD15in  BIT_ADDR(GPIOD_IDR_Addr, 15) //输入

 //----------------------------------------------------
 #define PE0   BIT_ADDR(GPIOE_ODR_Addr, 0)  //输出
 #define PE1   BIT_ADDR(GPIOE_ODR_Addr, 1)  //输出
 #define PE2   BIT_ADDR(GPIOE_ODR_Addr, 2)  //输出
 #define PE3   BIT_ADDR(GPIOE_ODR_Addr, 3)  //输出
 #define PE4   BIT_ADDR(GPIOE_ODR_Addr, 4)  //输出
 #define PE5   BIT_ADDR(GPIOE_ODR_Addr, 5)  //输出
 #define PE6   BIT_ADDR(GPIOE_ODR_Addr, 6)  //输出
 #define PE7   BIT_ADDR(GPIOE_ODR_Addr, 7)  //输出
 #define PE8   BIT_ADDR(GPIOE_ODR_Addr, 8)  //输出
 #define PE9   BIT_ADDR(GPIOE_ODR_Addr, 9)  //输出
 #define PE10  BIT_ADDR(GPIOE_ODR_Addr, 10) //输出
 #define PE11  BIT_ADDR(GPIOE_ODR_Addr, 11) //输出
 #define PE12  BIT_ADDR(GPIOE_ODR_Addr, 12) //输出
 #define PE13  BIT_ADDR(GPIOE_ODR_Addr, 13) //输出
 #define PE14  BIT_ADDR(GPIOE_ODR_Addr, 14) //输出
 #define PE15  BIT_ADDR(GPIOE_ODR_Addr, 15) //输出

 #define PE0in   BIT_ADDR(GPIOE_IDR_Addr, 0)  //输入
 #define PE1in   BIT_ADDR(GPIOE_IDR_Addr, 1)  //输入
 #define PE2in   BIT_ADDR(GPIOE_IDR_Addr, 2)  //输入
 #define PE3in   BIT_ADDR(GPIOE_IDR_Addr, 3)  //输入
 #define PE4in   BIT_ADDR(GPIOE_IDR_Addr, 4)  //输入
 #define PE5in   BIT_ADDR(GPIOE_IDR_Addr, 5)  //输入
 #define PE6in   BIT_ADDR(GPIOE_IDR_Addr, 6)  //输入
 #define PE7in   BIT_ADDR(GPIOE_IDR_Addr, 7)  //输入
 #define PE8in   BIT_ADDR(GPIOE_IDR_Addr, 8)  //输入
 #define PE9in   BIT_ADDR(GPIOE_IDR_Addr, 9)  //输入
 #define PE10in  BIT_ADDR(GPIOE_IDR_Addr, 10) //输入
 #define PE11in  BIT_ADDR(GPIOE_IDR_Addr, 11) //输入
 #define PE12in  BIT_ADDR(GPIOE_IDR_Addr, 12) //输入
 #define PE13in  BIT_ADDR(GPIOE_IDR_Addr, 13) //输入
 #define PE14in  BIT_ADDR(GPIOE_IDR_Addr, 14) //输入
 #define PE15in  BIT_ADDR(GPIOE_IDR_Addr, 15) //输入

					 
#endif /* __STM32F10x_BitBand_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/


