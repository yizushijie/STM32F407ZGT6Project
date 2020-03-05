#include "isp_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_Init(ISP_HandleType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISPLib_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_DeInit(ISP_HandleType *ISPx)
{
	return ISPLib_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置固定编程时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetProgClock(ISP_HandleType* ISPx, UINT8_T clok)
{
	return ISPLib_SetProgClock(ISPx,clok);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入编程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EnterProg(ISP_HandleType *ISPx, UINT8_T isPollReady)
{
	return ISPLib_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EnterProgAndConfigInfo(ISP_HandleType* ISPx, UINT8_T isPollReady,UINT8_T *pVal)
{
	return ISPLib_EnterProgAndConfigInfo(ISPx, isPollReady, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：退出编程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ExitProg(ISP_HandleType *ISPx)
{
	return ISPLib_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：添加监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_AddWatch(ISP_HandleType* ISPx)
{
	return ISPLib_AddWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RemoveWatch(ISP_HandleType* ISPx)
{
	return ISPLib_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：刷新监控
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RefreshWatch(ISP_HandleType* ISPx)
{
	return ISPLib_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置轮询间隔时间
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetIntervalTime(ISP_HandleType* ISPx, UINT16_T intervalTime)
{
	return ISPLib_SetIntervalTime(ISPx, intervalTime);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取轮询间隔时间
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T ISPTask_GetIntervalTime(ISP_HandleType* ISPx)
{
	return ISPLib_GetIntervalTime(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Ready信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadReady(ISP_HandleType *ISPx)
{
	return ISPLib_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EraseChip(ISP_HandleType *ISPx)
{
	return ISPLib_EraseChip(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取ChipID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipID(ISP_HandleType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipID(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipCalibration(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	return ISPLib_ReadChipCalibration(ISPx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_ReadChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipLock(ISP_HandleType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipLock(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取ROM信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipRom(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	return ISPLib_ReadChipRom(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_WriteChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipLock(ISP_HandleType *ISPx, UINT8_T val)
{
	return ISPLib_WriteChipLock(ISPx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_ReadChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写数据到Eeprom缓存区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	return ISPLib_UpdateChipEepromPage( ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到Eeprom存储区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipEepromAddr(ISP_HandleType* ISPx, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISPLib_UpdateChipEepromAddr(ISPx,highAddr,lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到Eeprom存储区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipEepromLongAddr(ISP_HandleType* ISPx, UINT16_T addr)
{
	return ISPLib_UpdateChipEepromLongAddr(ISPx,addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：按页写数据到Eeprom存储区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return ISPLib_WriteChipEepromPage(ISPx,pVal,highAddr,lowAddr,pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程EEPROM
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return  ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEeprom(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return ISP_WriteChipEeprom(ISPx, pVal,  highAddr,  lowAddr,  pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipFlashAddr(ISPx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return ISPLib_ReadChipFlashLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新拓展位地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternAddr(ISP_HandleType* ISPx, UINT8_T addr)
{
	return ISPLib_UpdateExternAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新拓展位地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandleType* ISPx, UINT32_T addr)
{
	return ISPLib_UpdateExternLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到数据缓存区
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	return ISPLib_UpdateChipFlashBuffer(ISPx, pVal, index, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到指定的数据地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandleType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISPLib_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：更新数据到数据的指定地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandleType *ISPx, UINT32_T addr)
{
	return ISPLib_UpdateChipFlashLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：页模式向指定的数据写入Flash
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipFlashPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipFlashPage(ISPx,pVal, externAddr, highAddr, lowAddr,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_CheckChipFlashEmpty(ISP_HandleType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	return ISPLib_CheckChipFlashEmpty(ISPx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_CheckChipFlashEmptyLong(ISP_HandleType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return ISPLib_CheckChipFlashEmptyLong(ISPx, pageByteSize, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_CheckChipEepromEmpty(ISP_HandleType* ISPx, UINT8_T byteSize, UINT8_T num)
{
	return ISPLib_CheckChipEepromEmpty(ISPx, byteSize, num);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetConfigInfo(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	return ISPLib_SetConfigInfo(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipPower(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	//---读取芯片的供电电压
	UINT16_T tempPower= ADCTask_GetChipPower();
	//---读取电压值
	//---填充数据
	*(pVal++)=(UINT8_T)(tempPower>>8);
	*pVal=(UINT8_T)(tempPower);
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipPower(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	UINT16_T tempPower = *(pVal++);
	tempPower= (tempPower<<8)+*(pVal++);
	//---通过DAC设置可调电源LM317的输出值
	LM317Task_Init(0, tempPower);
	//---校验电源是否开启
	if (*pVal>0)
	{
		LM317_POWER_ON;
	}
	else
	{
		LM317_POWER_HZ;
	}
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：退出或者进入编程模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_OpenAndClose(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return=0;
	//---命令位置
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]==1)
	{
		//---进入编程模式，并配置基本参数
		_return=ISPTask_EnterProgAndConfigInfo(ISPx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset], UARTx->msgRxdHandle.pMsgVal+UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1);
	}
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		//---配置基本参数,主要是使不使能EEPROM的页编程模式
		_return= ISPTask_SetConfigInfo(ISPx, UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1);
	}
	else
	{
		_return = ISPTask_ExitProg(ISPx);
	}
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：擦除Chip
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_EraseChip(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T _return=OK_0;
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 0)
	{
		//---设备擦除
		_return= ISPTask_EraseChip(ISPx);
	}
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		//---检查Flash为空
		_return=ISPTask_CheckChipFlashEmpty(ISPx, 
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1], UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 2],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 3], UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 4]
											);
	}
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		//---检查Eeprom为空
		_return = ISPTask_CheckChipEepromEmpty(	ISPx,
												UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1], UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 2]
											  );
	}
	else
	{
		_return=0xFF;
	}
	//---检验是不是查空操作
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]!=0)
	{
		//---填充查空操作的值
		UARTTask_FillMode_AddByte(UARTx, _return);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipID(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	//---读取设备ID信息
	_return = ISPTask_ReadChipID(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex);
	//---数据长度偏移
	UARTx->msgTxdHandle.msgWIndex += 3;
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipCalibration(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	//---读取设备的校准字
	_return = ISPTask_ReadChipCalibration(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
	//---数据地址偏移
	UARTx->msgTxdHandle.msgWIndex += UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset];
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的熔丝位和校准字
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipFuseAndLock(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	//---判断是读取熔丝位还是加密位
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 0)
	{
		//---读取熔丝位
		_return = ISPTask_ReadChipFuse(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset]);
		//---校验是否读取拓展熔丝位
		if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset] != 0)
		{
			UARTx->msgTxdHandle.msgWIndex += 1;
		}
		UARTx->msgTxdHandle.msgWIndex += 2;
	}
	else
	{
		//---读取加密位
		_return = ISPTask_ReadChipLock(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex);
		UARTx->msgTxdHandle.msgWIndex += 1;
	}
	//---执行结果
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程熔丝位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_WriteChipFuse(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	return ISPTask_WriteChipFuse(ISPx, UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：编程加密位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_WriteChipLock(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	return ISPTask_WriteChipLock(ISPx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的ROM信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipRom(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length=0;
	//---计算读取数据的大小
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset];
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
	}
	//---读取ROM页信息
	_return = ISPTask_ReadChipRom(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset], length);
	//---数据的偏移
	UARTx->msgTxdHandle.msgWIndex += length;
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置编程时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_SetProgClok(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T _return=OK_0;
	//---读取电压
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		_return= ISPTask_ReadChipPower(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1);
		UARTx->msgTxdHandle.msgWIndex += 2;
	}
	//---设置电压
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		_return=ISPTask_WriteChipPower(ISPx, UARTx->msgRxdHandle.pMsgVal+UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1);
	}
	else
	{
		//---设置编程时钟
		_return = ISPTask_SetProgClock(ISPx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset+1]);
	}
	
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通过串口命令读取Flash数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipFlash(ISP_HandleType * ISPx, UART_HandleType * UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---计算读取数据的大小
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 3];
	}
	//---读取指定位置的Flash数据
	_return= ISPTask_ReadChipFlashAddr(ISPx,UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, 
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset+1],
											length);
	//---数据的偏移
	UARTx->msgTxdHandle.msgWIndex += length;
	//---执行结果
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通过串口命令编程Flash数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_WriteChipFlashPage(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---计算写入数据的大小
	if (UARTx->msgRxdHandle.msgMaxSize<0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		dataOffset=3;
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 3];
		dataOffset = 4;
	}	
	//---从指定位置编程数据
	return ISPTask_WriteChipFlashPage(ISPx,	UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + dataOffset,
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1],
											length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通过串口命令读取eeprom数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipEeprom(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---计算读取数据的大小
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
	}
	//---读取指定位置的Eeprom数据
	_return = ISPTask_ReadChipEepromAddr(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex,
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
											length);
	//---数据的偏移
	UARTx->msgTxdHandle.msgWIndex += length;
	//---执行结果
	return _return;
	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通过串口命令编程eeprom数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_WriteChipEeprom(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---计算读取数据的大小
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		dataOffset = 2;
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		dataOffset = 3;
	}
	//---编程指定位置的Eeprom数据
	return ISPTask_WriteChipEeprom( ISPx, UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + dataOffset,
									UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
									UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
									length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ChildTask(ISP_HandleType* ISPx, UART_HandleType* UARTx,UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---填充测试执行结果
	UARTTask_FillMode_AddByte(UARTx, 0x00);
	UARTx->msgIndexOffset= (isChildCmd == 0 ? 0 : 1);
	//---依据命令解析数据
	switch (UARTx->msgRxdHandle.pMsgVal[UARTx->msgCmdIndex+ UARTx->msgIndexOffset])
	{
		case CMD_ISP_OPEN_CLOSE:
			//---命令之后，第1字节0---代表关闭，1---代表打开；第2字节与打开有关，与关闭无关
			_return= ISPTask_UARTCmd_OpenAndClose(ISPx,UARTx);
			break;
		case CMD_ISP_ERASE:
			//---擦除设备，第1字节0---代表擦除，1---代表查空Flash，2---代表查空Eeprom
			_return= ISPTask_UARTCmd_EraseChip(ISPx, UARTx);
			break;
		case CMD_ISP_FLASH_PAGE_READ:
			//---读取Flash
			_return= ISPTask_UARTCmd_ReadChipFlash(ISPx, UARTx);
			break;
		case CMD_ISP_FLASH_PAGE_WRITE:
			//---编程Flash
			_return= ISPTask_UARTCmd_WriteChipFlashPage(ISPx, UARTx);
			break;
		case CMD_ISP_EEPROM_PAGE_READ:
			//---读取Eeprom
			_return= ISPTask_UARTCmd_ReadChipEeprom(ISPx, UARTx);
			break;
		case CMD_ISP_EEPROM_PAGE_WRITE:
			//---编程Eeprom
			_return = ISPTask_UARTCmd_WriteChipEeprom(ISPx, UARTx);
			break;
		case CMD_ISP_FUSE_LOCK_READ:
			//---读取熔丝位或者校验位
			_return= ISPTask_UARTCmd_ReadChipFuseAndLock(ISPx,UARTx);
			break;
		case CMD_ISP_FUSE_WRITE	:
			//---编程熔丝位
			_return= ISPTask_UARTCmd_WriteChipFuse(ISPx, UARTx);
			break;
		case CMD_ISP_LOCK_WRITE	:
			//---编程加密位
			_return= ISPTask_UARTCmd_WriteChipLock(ISPx, UARTx);
			break;
		case CMD_ISP_ID_READ:
			//---读取设备的ID
			_return= ISPTask_UARTCmd_ReadChipID(ISPx,UARTx);
			break;
		case CMD_ISP_CALIBRATIONBYTE_READ:
			//---读取校准字
			_return= ISPTask_UARTCmd_ReadChipCalibration(ISPx, UARTx);
			break;
		case CMD_ISP_ROM_PAGE_READ:
			//---读取ROM页信息
			_return= ISPTask_UARTCmd_ReadChipRom(ISPx,UARTx);
			break;
		case CMD_ISP_PROG_CLOCK_SET:
			//---设置编程时钟，多级参数，后续需要有电源的设置和读取
			_return= ISPTask_UARTCmd_SetProgClok(ISPx, UARTx);
			break;
		default:
			//---不识别的命令
			_return = ERROR_1;
			break;
	}
	//---填充测试结果
	UARTTask_FillMode_SetResultFlag(UARTx,_return);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ParentTask(ISP_HandleType* ISPx, UART_HandleType* UARTx, UINT8_T isChildCmd)
{
	if ((UARTx != NULL) && (ISPx != NULL))
	{
		//---判断接收是否完成
		if (UARTTask_GetState(&(UARTx->msgRxdHandle)) == 1)
		{
			//---CRC的校验和设备ID校验
			if ((UARTTask_Read_CRCTask(UARTx) == OK_0) && (UARTTask_DeviceID(UARTx) == OK_0))
			{
				//---任务命令处理函数，数据报头，长度，地址ID,命令的处理
				UARTTask_FillMode_Init(UARTx,isChildCmd);
				//---处理任务
				ISPTask_UARTCmd_ChildTask(ISPx, UARTx, isChildCmd);
				//---启动数据发送
				UARTTask_FillMode_WriteByteSTART(UARTx, 0);
			}
			else
			{
				//---发生CRC校验错误
				UARTTask_Printf(UARTx, "=>>SP%d:CRC Check Error<<=\r\n", (UARTx->msgIndex - 1));
			}
			return UARTTask_Read_Init(UARTx);
		}
		return UARTTask_TimeTask_OverFlow(UARTx,1);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ParentTask_New(ISP_HandleType* ISPx, UART_HandleType* UARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = OK_0;
	//---任务命令处理函数，数据报头，长度，地址ID,命令的处理
	UARTTask_FillMode_Init(UARTx, isChildCmd);
	//---处理任务
	ISPTask_UARTCmd_ChildTask(ISPx, UARTx, isChildCmd);
	//---是否需要增加换行符
	if (UARTx->msgTxdHandle.msgAddNewLine == 1)
	{
		UARTTask_FillMode_AddByte(UARTx, 0x0D);
		UARTTask_FillMode_AddByte(UARTx, 0x0A);
	}
	//---启动数据发送
	UARTTask_FillMode_WriteByteSTART(UARTx, 0);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_Task(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T _return = OK_0;
	//_return= ISPTask_UARTCmd_ParentTask(ISPx, UARTx, 0);
	_return = ISPTask_UARTCmd_ParentTask_New(ISPx, UARTx, 0);
	return _return;
}