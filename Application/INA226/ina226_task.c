#include "ina226_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226Task_I2C_Init(INA226_HandleType* INA226x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	return INA226Lib_I2C_Init(INA226x, pFuncDelayus,pFuncTimerTick, isHWI2C);
}