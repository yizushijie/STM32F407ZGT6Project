#ifndef ISP_TASK_H_
#define ISP_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "isp_lib.h"
	#include "usart_task.h"
	#include "power_task.h"
	#include "adc_Task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===ISP�ı�̵�����Ļ���ַ							
	#define CMD_ISP_BASE_CMD							0x10
	//===�򿪻��߹ر�ISP
	#define	CMD_ISP_OPEN_CLOSE							(	CMD_ISP_BASE_CMD+0	)	
	//===ISP����оƬ
	#define	CMD_ISP_ERASE								(	CMD_ISP_BASE_CMD+1	)	
	//===ISP��ҳ��ȡFlash
	#define CMD_ISP_FLASH_PAGE_READ						(	CMD_ISP_BASE_CMD+2	)	
	//===ISP��ҳд��Flash
	#define CMD_ISP_FLASH_PAGE_WRITE					(	CMD_ISP_BASE_CMD+3	)		
	//===ISP��ҳ��ȡEeeprom
	#define	CMD_ISP_EEPROM_PAGE_READ					(	CMD_ISP_BASE_CMD+4	)			
	//===ISP��ҳд��Eeprom
	#define CMD_ISP_EEPROM_PAGE_WRITE					(	CMD_ISP_BASE_CMD+5	)			
	//===ISP��ȡ��˿λ������λ
	#define CMD_ISP_FUSE_LOCK_READ						(	CMD_ISP_BASE_CMD+6	)		
	//===ISPд����˿λ
	#define CMD_ISP_FUSE_WRITE							(	CMD_ISP_BASE_CMD+7	)		
	//===ISPд������λ
	#define CMD_ISP_LOCK_WRITE							(	CMD_ISP_BASE_CMD+8	)		
	//===ISP��ȡоƬ��ʶ
	#define CMD_ISP_ID_READ								(	CMD_ISP_BASE_CMD+9	)
	//===ISP��ȡУ׼��
	#define CMD_ISP_CALIBRATIONBYTE_READ				(	CMD_ISP_BASE_CMD+10	)	
	//===ISP��ȡROM��Ϣ
	#define CMD_ISP_ROM_PAGE_READ						(	CMD_ISP_BASE_CMD+11	)	
	//===ISP���ʱ������
	#define CMD_ISP_PROG_CLOCK_SET						(	CMD_ISP_BASE_CMD+12	)
	//===���������ַ
	#define CMD_ISP_END_CMD								(   CMD_ISP_BASE_CMD+12	)
	
	//===��������
	UINT8_T ISPTask_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T ISPTask_DeInit(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clok);
	UINT8_T ISPTask_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady);
	UINT8_T ISPTask_EnterProgAndConfigInfo(ISP_HandlerType* ISPx, UINT8_T isPollReady, UINT8_T* pVal);
	UINT8_T ISPTask_ExitProg(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_AddWatch(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_RemoveWatch(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_RefreshWatch(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_SetIntervalTime(ISP_HandlerType* ISPx, UINT16_T intervalTime);
	UINT16_T ISPTask_GetIntervalTime(ISP_HandlerType* ISPx);
	UINT8_T ISPTask_ReadReady(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_EraseChip(ISP_HandlerType *ISPx);
	UINT8_T ISPTask_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length);
	UINT8_T ISPTask_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISPTask_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISPTask_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISPTask_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T val);
	UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_UpdateChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal);
	UINT8_T ISPTask_UpdateChipEepromAddr(ISP_HandlerType* ISPx, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISPTask_UpdateChipEepromLongAddr(ISP_HandlerType* ISPx, UINT16_T addr);
	UINT8_T ISPTask_WriteChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISPTask_WriteChipEeprom(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT32_T addr, UINT16_T length);
	UINT8_T ISPTask_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr);
	UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr);
	UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length);
	UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr);
	UINT8_T ISPTask_WriteChipFlashPage(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISPTask_CheckChipFlashEmpty(ISP_HandlerType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL);
	UINT8_T ISPTask_CheckChipFlashEmptyLong(ISP_HandlerType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum);
	UINT8_T ISPTask_CheckChipEepromEmpty(ISP_HandlerType* ISPx, UINT8_T byteSize, UINT8_T num);
	UINT8_T ISPTask_SetConfigInfo(ISP_HandlerType* ISPx, UINT8_T* pVal);
	UINT8_T ISPTask_ReadChipPower(ISP_HandlerType* ISPx, UINT8_T* pVal);
	UINT8_T ISPTask_WriteChipPower(ISP_HandlerType* ISPx, UINT8_T* pVal);

	//===��ͨѶ�˿ڵĺ�������
	UINT8_T ISPTask_USARTCmd_OpenAndClose(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_EraseChip(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ReadChipID(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ReadChipCalibration(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ReadChipFuseAndLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_WriteChipFuse(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_WriteChipFuse(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_WriteChipLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ReadChipRom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_SetProgClok(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ReadChipFlash(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_WriteChipFlashPage(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ReadChipEeprom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_WriteChipEeprom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	UINT8_T ISPTask_USARTCmd_ChildTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx, UINT8_T isChildCmd);
	UINT8_T ISPTask_USARTCmd_ParentTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx, UINT8_T isChildCmd);
	UINT8_T ISPTask_USARTCmd_Task(ISP_HandlerType* ISPx, USART_HandlerType* USARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ISP_TASK_H_ */
