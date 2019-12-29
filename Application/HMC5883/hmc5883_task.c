#include "hmc5883_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883Task_I2C_Init(HMC5883_HandlerType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT8_T isHWI2C)
{
	return HMC5883Lib_I2C_Init(HMC5883x, pFuncDelayus,pFuncDelayms, isHWI2C);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883Task_I2C_SingleWriteReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	return HMC5883Lib_I2C_SingleWriteReg(HMC5883x, addr, val);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883Task_I2C_SingleReadReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	return HMC5883Lib_I2C_SingleReadReg(HMC5883x, addr, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883Task_I2C_BurstReadReg(HMC5883_HandlerType* HMC5883x)
{
	return HMC5883Lib_I2C_BurstReadReg(HMC5883x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883Task_ConfigInit(HMC5883_HandlerType* HMC5883x)
{
	return HMC5883_ConfigInit(HMC5883x);
}