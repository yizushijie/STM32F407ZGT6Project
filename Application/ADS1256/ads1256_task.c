#include "ads1256_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS1256Task_SPI_Init(ADS1256_HandleType* ADS1256x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	return ADS1256Lib_SPI_Init(ADS1256x, pFuncDelayus, pFuncDelayms, pFuncTimerTick, isHW);
}