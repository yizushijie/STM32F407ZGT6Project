#ifndef ISP_CFG_H_
#define ISP_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "spi_task.h"
	#include "systick_task.h"
	#include "delay_task.h"
	#include "my_malloc.h"
	#include "hw_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��̿�ѡ���ʱ��
	#define ISP_SCK_AUTO						0																		//---�Զ�
	#define ISP_SCK_KHZ_0_5						1																		//---1ms
	#define ISP_SCK_KHZ_1						2																		//---500us---0.99KHZ
	#define ISP_SCK_KHZ_2						3																		//---250us---1.98KHZ
	#define ISP_SCK_KHZ_4						4																		//---125us---3.96KHZ
	#define ISP_SCK_KHZ_8						5																		//---64us---7.66KHZ
	#define ISP_SCK_KHZ_16						6																		//---32us---15.06KHZ
	#define ISP_SCK_KHZ_32						7																		//---16us---29.05KHZ
	#define ISP_SCK_KHZ_64						8																		//---8us---54.46KHZ
	#define ISP_SCK_KHZ_128						9																		//---4us---89.928KHZ
	#define ISP_SCK_KHZ_256						10																		//---2us---145.35KHZ
	#define ISP_SCK_PRE_256						11																		//---42M/256---163.934KHZ
	#define ISP_SCK_PRE_128						12																		//---42M/128---328.95KHZ
	#define ISP_SCK_PRE_64						13																		//---42M/64---657.89KHZ
	#define ISP_SCK_PRE_32						14																		//---42M/32---1.315M
	#define ISP_SCK_PRE_16						15																		//---42M/16---2.63M
	#define ISP_SCK_PRE_8						16																		//---42M/8
	#define ISP_SCK_PRE_4						17																		//---42M/4
	#define ISP_SCK_PRE_2						18																		//---42M/2
	
	//===Ĭ�ϱ��ʱ��
	#define ISP_SCK_DEFAULT_CLOCK				ISP_SCK_PRE_64
	//===������ɫʱ��
	#define ISP_SCK_MAX_CLOCK					ISP_SCK_PRE_64
	//===���ʱ�����ı�Ĵ���
	#define ISP_SCK_AUTO_MAX_COUNT				18	
	//===��̻������Ĵ�С
	#define ISP_COMM_MAX_SIZE					4	
	//===����ISP״̬���ֵ�ʱ��״̬
	#define ISP_STATE_TIME_OUT_MS				500
	
	//===����ṹ��
	typedef struct _ISP_HandleType				ISP_HandleType;
	//===����ָ��ṹ��
	typedef	struct _ISP_HandleType				*pISP_HandleType;
	//===�ṹ����
	struct _ISP_HandleType
	{
		UINT8_T		msgState;																							//---���״̬��0---����״̬��1---���״̬
		UINT8_T		msgInit;																							//---�ж��Ƿ��ʼ������ 0---δ��ʼ����1---��ʼ��
		UINT8_T		msgSetClok;																							//---���õı��ʱ��
		UINT8_T		msgAutoClock;																						//---�Ƿ�ʹ���Զ�ʱ�ӣ�0---�Զ�ʱ�ӣ�1---�趨��ʱ��
		UINT8_T		msgWaitms;																							//---���֮�����ʱ��������λ��ms
		UINT8_T		msgHideAddr;																						//---�Ӵ�64K������
		UINT8_T		msgPollReady;																						//---�Ƿ���ѯ׼�����źţ�0---����Ҫ��1---��Ҫ
		UINT8_T		msgEepromPageMode;																					//---eeprom�Ƿ�֧��ҳ���ģʽ��0---��֧�֣�1---֧��
		UINT16_T	msgFlashPerPageWordSize;																			//---Flash��ÿҳ����
		UINT16_T	msgEerpomPerPageByteSize;																			//---Eeprom��ÿҳ�ֽ���
		UINT16_T	msgPageWordIndex;																					//---Flash�����������
		UINT8_T		msgWriteByte[ISP_COMM_MAX_SIZE];																	//---��������
		UINT8_T		msgReadByte[ISP_COMM_MAX_SIZE];																		//---��ȡ����
		UINT16_T	msgIntervalTime;																					//---��ѯʱ����,��λ��ms
		UINT32_T	msgRecordTick;																						//---��¼��ʱ�����
#ifdef ISP_USE_lEVEL_SHIFT
		GPIO_HandleType msgOE;																							//---��ƽת��ʹ�ܿ��ƶˣ�0---ʹ�ܣ�1---��ʹ��
#endif
		void(*pMsgDelayms)(UINT32_T delay);																				//---��ʱ����
		SPI_HandleType msgSPI;																							//---ʹ�õ�SPIģʽ
#ifdef ISP_USE_HV_RESET
		void (*pMsgPortRst)(UINT8_T rstState);																			//---��ѹģʽ����RST�˿ڵĺ���
#endif
	};

	//===����RST��״̬
	#define ISP_RST_TO_HZ						0																		//---RST���ڸ���״̬
	#define ISP_RST_TO_GND						1																		//---RST���ڽӵ�
	#define ISP_RST_TO_VCC						2																		//---RST�ӹ�����ѹ

	//===������
	#define ISP_TASK_ONE						pIspDevice0																															//---����1
	#define ISP_TASK_TWO						0																																	//---����2
	#define ISP_TASK_THREE						0																																	//---����3

	//===�ⲿ���ýӿ�
	extern ISP_HandleType						g_IspDevice0;
	extern pISP_HandleType						pIspDevice0;

	//===��������
	UINT8_T ISP_HW_Init(ISP_HandleType *ISPx);
	UINT8_T ISP_SW_Init(ISP_HandleType *ISPx);
	UINT8_T ISP_Init(ISP_HandleType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T ISP_DeInit(ISP_HandleType *ISPx);
	UINT8_T ISP_AutoInit(ISP_HandleType* ISPx);
	UINT8_T ISP_AutoDeInit(ISP_HandleType* ISPx);
	UINT8_T ISP_SetClock(ISP_HandleType *ISPx, UINT8_T clok);
	UINT8_T ISP_SetProgClock(ISP_HandleType* ISPx, UINT8_T clok);
	UINT8_T ISP_SW_SendCmd(ISP_HandleType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4);
	UINT8_T ISP_HW_SendCmd(ISP_HandleType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4);
	UINT8_T ISP_PreEnterProg(ISP_HandleType *ISPx);
	UINT8_T ISP_EnterProg(ISP_HandleType* ISPx, UINT8_T isPollReady);
	UINT8_T ISP_ExitProg(ISP_HandleType *ISPx);
	void	ISP_WatchTask(ISP_HandleType* ISPx);
	UINT8_T ISP_AddWatch(ISP_HandleType* ISPx);
	UINT8_T ISP_RemoveWatch(ISP_HandleType* ISPx);
	UINT8_T ISP_RefreshWatch(ISP_HandleType* ISPx);
	UINT8_T ISP_SetIntervalTime(ISP_HandleType* ISPx, UINT16_T intervalTime);
	UINT16_T ISP_GetIntervalTime(ISP_HandleType* ISPx);
	UINT8_T ISP_ReadReady(ISP_HandleType *ISPx);
	UINT8_T ISP_EraseChip(ISP_HandleType *ISPx);
	UINT8_T ISP_ReadChipID(ISP_HandleType *ISPx, UINT8_T *pVal);
	UINT8_T ISP_ReadChipCalibration(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T length);
	UINT8_T ISP_ReadChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISP_ReadChipLock(ISP_HandleType *ISPx, UINT8_T *pVal);
	UINT8_T ISP_ReadChipRom(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISP_WriteChipLock(ISP_HandleType *ISPx, UINT8_T val);
	UINT8_T ISP_ReadChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_UpdateChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal);
	UINT8_T ISP_UpdateChipEepromAddr(ISP_HandleType* ISPx, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISP_UpdateChipEepromLongAddr(ISP_HandleType* ISPx, UINT16_T addr);
	UINT8_T ISP_WriteChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T ISP_ReadChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipEeprom(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T ISP_UpdateExternAddr(ISP_HandleType *ISPx, UINT8_T addr);
	UINT8_T ISP_UpdateExternLongAddr(ISP_HandleType *ISPx, UINT32_T addr);
	UINT8_T ISP_ReadChipFlashAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_ReadChipFlashLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length);
	UINT8_T ISP_UpdateChipFlashPage(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length);
	UINT8_T ISP_UpdateChipFlashAddr(ISP_HandleType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISP_UpdateChipFlashLongAddr(ISP_HandleType *ISPx, UINT32_T addr);
	UINT8_T ISP_WriteChipFlashPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_CheckChipFlashEmpty(ISP_HandleType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL);
	UINT8_T ISP_CheckChipFlashEmptyLong(ISP_HandleType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum);
	UINT8_T ISP_CheckChipEepromEmpty(ISP_HandleType* ISPx, UINT8_T byteSize, UINT8_T num);
	UINT8_T ISP_SetConfigInfo(ISP_HandleType* ISPx, UINT8_T* pVal);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ISP_CFG_H_ */
