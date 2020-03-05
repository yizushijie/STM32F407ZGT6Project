#ifndef SPI_TASK_H_
#define SPI_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "spi_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===º¯Êý¶¨Òå
	UINT8_T SPITask_MHW_PollMode_Init(SPI_HandleType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct);
	UINT8_T SPITask_MHW_GPIO_Init(SPI_HandleType *SPIx);
	UINT8_T SPITask_MSW_GPIO_Init(SPI_HandleType *SPIx);
	UINT8_T SPITask_GPIO_DeInit(SPI_HandleType *SPIx, UINT8_T isInitSS);
	UINT8_T SPITask_DeInit(SPI_HandleType *SPIx, UINT8_T isInitSS);
	UINT8_T SPITask_MHW_PollMode_WriteAndReadByte(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPITask_MHW_PollMode_WriteAndReadData(SPI_HandleType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPITask_MSW_WriteBitMSB(SPI_HandleType *SPIx, UINT8_T wVal);
	UINT8_T SPITask_MSW_ReadBitMSB(SPI_HandleType *SPIx, UINT8_T *pRVal);
	UINT8_T SPITask_MSW_WriteBitLSB(SPI_HandleType *SPIx, UINT8_T wVal);
	UINT8_T SPITask_MSW_ReadBitLSB(SPI_HandleType *SPIx, UINT8_T *pRVal);
	UINT8_T SPITask_MSW_SetClock(SPI_HandleType *SPIx, UINT32_T clock);
	UINT8_T SPITask_MHW_SetClock(SPI_HandleType *SPIx, UINT32_T clock);
	UINT8_T SPITask_MSW_WriteAndReadByteMSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPITask_MSW_WriteAndReadByteLSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPITask_MSW_WriteAndReadDataMSB(SPI_HandleType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPITask_MSW_WriteAndReadDataLSB(SPI_HandleType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	void  SPITask_IRQTask(SPI_HandleType* SPIx, UINT8_T is16Bit);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SPI_TASK_H_ */
