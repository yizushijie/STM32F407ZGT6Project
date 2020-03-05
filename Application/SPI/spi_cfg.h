#ifndef SPI_CFG_H_
#define SPI_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "systick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===定义结构体
	typedef struct _SPI_HandleType					SPI_HandleType;
	//===定义指针结构体
	typedef	struct _SPI_HandleType					*pSPI_HandleType;
	//===结构定义
	struct _SPI_HandleType
	{
		GPIO_HandleType		msgMOSI;																					//---MOSI
		GPIO_HandleType		msgMISO;																					//---MISO
		GPIO_HandleType		msgSCK;																						//---SCK
		GPIO_HandleType		msgCS;																						//---CS
		SPI_TypeDef			*pMsgSPIx;																					//---使用的硬件SPI接口
		VLTUINT8_T			msgState;																					//---工作状态，默认是空闲状态---0，工作状态---1
		UINT8_T				msgHwMode;																					//---工作模式，默认是软件模拟---0，硬件模式---1
		UINT8_T				msgCPOL;																					//---时钟信号的极性	0---时钟空闲为低电平；1---时钟空闲为高电平
		UINT8_T				msgCPOH;																					//---时钟相位的极性	0---时钟的第一个上升或则下降沿数据被采样；1----时钟的第二个上升或则下降沿数据被采样
		UINT8_T				* pMsg8BitTxVal;																			//---发送8Bit数据指针
		UINT8_T				* pMsg8BitRxVal;																			//---接收8Bit数据指针
		UINT16_T			* pMsg16BitTxVal;																			//---发送16Bit数据指针
		UINT16_T			* pMsg16BitRxVal;																			//---接收16Bit数据指针
		UINT16_T			msgDataCount;																				//---数据收发的个数
		UINT16_T			msgPluseWidth;																				//---脉冲宽度，软件模拟使用
		UINT32_T			msgClockSpeed;																				//---硬件SPI的时钟速度
	#ifndef USE_MCU_STM32F1
		UINT32_T			msgGPIOAlternate;																			//---GPIO的复用模式
	#endif
		UINT32_T			msgStandard;																				//---使用的SPI协议
		void(*pMsgDelayus)(UINT32_T delay);																				//---延时参数
		UINT32_T(*pMsgTimeTick)(void);																					//---用于超时计数
	};

	//===函数定义
	UINT8_T SPI_MHW_PollMode_Init(SPI_HandleType *spix, LL_SPI_InitTypeDef SPI_InitStruct);
	void	SPI_MHW_SetTransferBitOrder(SPI_HandleType *SPIx, UINT32_T BitOrder);
	UINT8_T SPI_MHW_GPIO_Init(SPI_HandleType *spix);
	UINT8_T SPI_MSW_GPIO_Init(SPI_HandleType *spix);
	UINT8_T SPI_GPIO_DeInit(SPI_HandleType *spix, UINT8_T isInitSS);
	UINT8_T SPI_DeInit(SPI_HandleType *spix, UINT8_T isInitSS);
	UINT8_T SPI_Clock(SPI_HandleType *spix, UINT8_T isEnable);
	UINT8_T SPI_MHW_PollMode_WriteAndReadByte(SPI_HandleType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPI_MHW_PollMode_WriteAndReadData(SPI_HandleType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPI_MSW_WriteBitMSB(SPI_HandleType *spix, UINT8_T wVal);
	UINT8_T SPI_MSW_ReadBitMSB(SPI_HandleType *SPIx, UINT8_T *pRVal);
	UINT8_T SPI_MSW_WriteBitLSB(SPI_HandleType *spix, UINT8_T wVal);
	UINT8_T SPI_MSW_ReadBitLSB(SPI_HandleType *SPIx, UINT8_T *pRVal);
	UINT8_T SPI_MSW_SetClock(SPI_HandleType *spix, UINT32_T clock);
	UINT8_T SPI_MHW_SetClock(SPI_HandleType *spix, UINT32_T clock);
	UINT8_T SPI_MSW_WriteAndReadByteMSB(SPI_HandleType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPI_MSW_WriteAndReadByteLSB(SPI_HandleType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPI_MSW_WriteAndReadDataMSB(SPI_HandleType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPI_MSW_WriteAndReadBDataLSB(SPI_HandleType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	void  SPI_IRQTask(SPI_HandleType* SPIx, UINT8_T is16Bit);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SPI_CFG_H_ */
