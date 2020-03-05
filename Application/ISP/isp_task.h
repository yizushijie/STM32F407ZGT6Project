#ifndef ISP_TASK_H_
#define ISP_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "isp_lib.h"
	#include "uart_task.h"
	#include "power_task.h"
	#include "adc_Task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===ISP的编程的命令的基地址							
	#define CMD_ISP_BASE_CMD							0x10
	//===打开或者关闭ISP
	#define	CMD_ISP_OPEN_CLOSE							(	CMD_ISP_BASE_CMD+0	)	
	//===ISP擦除芯片
	#define	CMD_ISP_ERASE								(	CMD_ISP_BASE_CMD+1	)	
	//===ISP按页读取Flash
	#define CMD_ISP_FLASH_PAGE_READ						(	CMD_ISP_BASE_CMD+2	)	
	//===ISP按页写入Flash
	#define CMD_ISP_FLASH_PAGE_WRITE					(	CMD_ISP_BASE_CMD+3	)		
	//===ISP按页读取Eeeprom
	#define	CMD_ISP_EEPROM_PAGE_READ					(	CMD_ISP_BASE_CMD+4	)			
	//===ISP按页写入Eeprom
	#define CMD_ISP_EEPROM_PAGE_WRITE					(	CMD_ISP_BASE_CMD+5	)			
	//===ISP读取熔丝位和锁定位
	#define CMD_ISP_FUSE_LOCK_READ						(	CMD_ISP_BASE_CMD+6	)		
	//===ISP写入熔丝位
	#define CMD_ISP_FUSE_WRITE							(	CMD_ISP_BASE_CMD+7	)		
	//===ISP写入锁定位
	#define CMD_ISP_LOCK_WRITE							(	CMD_ISP_BASE_CMD+8	)		
	//===ISP读取芯片标识
	#define CMD_ISP_ID_READ								(	CMD_ISP_BASE_CMD+9	)
	//===ISP读取校准字
	#define CMD_ISP_CALIBRATIONBYTE_READ				(	CMD_ISP_BASE_CMD+10	)	
	//===ISP读取ROM信息
	#define CMD_ISP_ROM_PAGE_READ						(	CMD_ISP_BASE_CMD+11	)	
	//===ISP编程时钟设置
	#define CMD_ISP_PROG_CLOCK_SET						(	CMD_ISP_BASE_CMD+12	)
	//===命令结束地址
	#define CMD_ISP_END_CMD								(   CMD_ISP_BASE_CMD+12	)
	
	//===函数定义
	UINT8_T ISPTask_Init(ISP_HandleType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T ISPTask_DeInit(ISP_HandleType *ISPx);
	UINT8_T ISPTask_SetProgClock(ISP_HandleType* ISPx, UINT8_T clok);
	UINT8_T ISPTask_EnterProg(ISP_HandleType *ISPx, UINT8_T isPollReady);
	UINT8_T ISPTask_EnterProgAndConfigInfo(ISP_HandleType* ISPx, UINT8_T isPollReady, UINT8_T* pVal);
	UINT8_T ISPTask_ExitProg(ISP_HandleType *ISPx);
	UINT8_T ISPTask_AddWatch(ISP_HandleType* ISPx);
	UINT8_T ISPTask_RemoveWatch(ISP_HandleType* ISPx);
	UINT8_T ISPTask_RefreshWatch(ISP_HandleType* ISPx);
	UINT8_T ISPTask_SetIntervalTime(ISP_HandleType* ISPx, UINT16_T intervalTime);
	UINT16_T ISPTask_GetIntervalTime(ISP_HandleType* ISPx);
	UINT8_T ISPTask_ReadReady(ISP_HandleType *ISPx);
	UINT8_T ISPTask_EraseChip(ISP_HandleType *ISPx);
	UINT8_T ISPTask_ReadChipID(ISP_HandleType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipCalibration(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T length);
	UINT8_T ISPTask_ReadChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISPTask_ReadChipLock(ISP_HandleType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipRom(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISPTask_WriteChipLock(ISP_HandleType *ISPx, UINT8_T val);
	UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_UpdateChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal);
	UINT8_T ISPTask_UpdateChipEepromAddr(ISP_HandleType* ISPx, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISPTask_UpdateChipEepromLongAddr(ISP_HandleType* ISPx, UINT16_T addr);
	UINT8_T ISPTask_WriteChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandleType* ISPx, UINT8_T* pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEeprom(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandleType* ISPx, UINT8_T* pVal, UINT32_T addr, UINT16_T length);
	UINT8_T ISPTask_UpdateExternAddr(ISP_HandleType *ISPx, UINT8_T addr);
	UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandleType *ISPx, UINT32_T addr);
	UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length);
	UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandleType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandleType *ISPx, UINT32_T addr);
	UINT8_T ISPTask_WriteChipFlashPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_CheckChipFlashEmpty(ISP_HandleType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL);
	UINT8_T ISPTask_CheckChipFlashEmptyLong(ISP_HandleType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum);
	UINT8_T ISPTask_CheckChipEepromEmpty(ISP_HandleType* ISPx, UINT8_T byteSize, UINT8_T num);
	UINT8_T ISPTask_SetConfigInfo(ISP_HandleType* ISPx, UINT8_T* pVal);
	UINT8_T ISPTask_ReadChipPower(ISP_HandleType* ISPx, UINT8_T* pVal);
	UINT8_T ISPTask_WriteChipPower(ISP_HandleType* ISPx, UINT8_T* pVal);

	//===带通讯端口的函数定义
	UINT8_T ISPTask_UARTCmd_OpenAndClose(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_EraseChip(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ReadChipID(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ReadChipCalibration(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ReadChipFuseAndLock(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_WriteChipFuse(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_WriteChipFuse(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_WriteChipLock(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ReadChipRom(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_SetProgClok(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ReadChipFlash(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_WriteChipFlashPage(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ReadChipEeprom(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_WriteChipEeprom(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	UINT8_T ISPTask_UARTCmd_ChildTask(ISP_HandleType* ISPx, UART_HandleType* USARTx, UINT8_T isChildCmd);
	UINT8_T ISPTask_UARTCmd_ParentTask(ISP_HandleType* ISPx, UART_HandleType* USARTx, UINT8_T isChildCmd);
	UINT8_T ISPTask_UARTCmd_Task(ISP_HandleType* ISPx, UART_HandleType* USARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ISP_TASK_H_ */
