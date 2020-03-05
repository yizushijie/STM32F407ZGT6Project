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

	//===����ṹ��
	typedef struct _SPI_HandleType					SPI_HandleType;
	//===����ָ��ṹ��
	typedef	struct _SPI_HandleType					*pSPI_HandleType;
	//===�ṹ����
	struct _SPI_HandleType
	{
		GPIO_HandleType		msgMOSI;																					//---MOSI
		GPIO_HandleType		msgMISO;																					//---MISO
		GPIO_HandleType		msgSCK;																						//---SCK
		GPIO_HandleType		msgCS;																						//---CS
		SPI_TypeDef			*pMsgSPIx;																					//---ʹ�õ�Ӳ��SPI�ӿ�
		VLTUINT8_T			msgState;																					//---����״̬��Ĭ���ǿ���״̬---0������״̬---1
		UINT8_T				msgHwMode;																					//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
		UINT8_T				msgCPOL;																					//---ʱ���źŵļ���	0---ʱ�ӿ���Ϊ�͵�ƽ��1---ʱ�ӿ���Ϊ�ߵ�ƽ
		UINT8_T				msgCPOH;																					//---ʱ����λ�ļ���	0---ʱ�ӵĵ�һ�����������½������ݱ�������1----ʱ�ӵĵڶ������������½������ݱ�����
		UINT8_T				* pMsg8BitTxVal;																			//---����8Bit����ָ��
		UINT8_T				* pMsg8BitRxVal;																			//---����8Bit����ָ��
		UINT16_T			* pMsg16BitTxVal;																			//---����16Bit����ָ��
		UINT16_T			* pMsg16BitRxVal;																			//---����16Bit����ָ��
		UINT16_T			msgDataCount;																				//---�����շ��ĸ���
		UINT16_T			msgPluseWidth;																				//---�����ȣ����ģ��ʹ��
		UINT32_T			msgClockSpeed;																				//---Ӳ��SPI��ʱ���ٶ�
	#ifndef USE_MCU_STM32F1
		UINT32_T			msgGPIOAlternate;																			//---GPIO�ĸ���ģʽ
	#endif
		UINT32_T			msgStandard;																				//---ʹ�õ�SPIЭ��
		void(*pMsgDelayus)(UINT32_T delay);																				//---��ʱ����
		UINT32_T(*pMsgTimeTick)(void);																					//---���ڳ�ʱ����
	};

	//===��������
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
