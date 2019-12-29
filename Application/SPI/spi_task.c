#include "spi_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MHW_PollMode_Init(SPI_HandlerType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct)
{
	return SPILib_MHW_PollMode_Init(SPIx, SPI_InitStruct);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void SPITask_MHW_SetTransferBitOrder(SPI_HandlerType *SPIx, UINT32_T BitOrder)
{
	SPILib_MHW_SetTransferBitOrder(SPIx, BitOrder);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MHW_GPIO_Init(SPI_HandlerType *SPIx)
{
	return SPILib_MHW_GPIO_Init(SPIx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_GPIO_Init(SPI_HandlerType *SPIx)
{
	return SPILib_MSW_GPIO_Init(SPIx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_GPIO_DeInit(SPI_HandlerType *SPIx, UINT8_T isInitSS)
{
	return SPILib_GPIO_DeInit(SPIx,isInitSS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_DeInit(SPI_HandlerType *SPIx, UINT8_T isInitSS)
{
	return  SPILib_DeInit(SPIx,isInitSS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MHW_PollMode_WriteAndReadByte(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	return  SPILib_MHW_PollMode_WriteAndReadByte(SPIx, wVal, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MHW_PollMode_WriteAndReadData(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	return SPILib_MHW_PollMode_WriteAndReadData(SPIx, pWVal, pRVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_WriteBitMSB(SPI_HandlerType *SPIx, UINT8_T wVal)
{
	return  SPILib_MSW_WriteBitMSB(SPIx, wVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_ReadBitMSB(SPI_HandlerType *SPIx, UINT8_T *pRVal)
{
	return  SPILib_MSW_ReadBitMSB(SPIx, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_WriteBitLSB(SPI_HandlerType *SPIx, UINT8_T wVal)
{
	return  SPILib_MSW_WriteBitLSB(SPIx, wVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_ReadBitLSB(SPI_HandlerType *SPIx, UINT8_T *pRVal)
{
	return  SPILib_MSW_ReadBitLSB(SPIx, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	return SPILib_MSW_SetClock(SPIx, clock);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MHW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	return SPILib_MHW_SetClock(SPIx, clock);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_WriteAndReadByteMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	return SPILib_MSW_WriteAndReadByteMSB(SPIx, wVal, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_WriteAndReadByteLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	return SPILib_MSW_WriteAndReadByteLSB(SPIx, wVal, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_WriteAndReadDataMSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	return SPILib_MSW_WriteAndReadDataMSB(SPIx, pWVal, pRVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPITask_MSW_WriteAndReadDataLSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	return SPILib_MSW_WriteAndReadDataLSB(SPIx, pWVal, pRVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：中断处理函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void  SPITask_IRQTask(SPI_HandlerType* SPIx, UINT8_T is16Bit)
{
	SPILib_IRQTask(SPIx,is16Bit);
}