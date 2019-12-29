#ifndef AHT10_CFG_H_
#define AHT10_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "delay_task.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===д����
	#define AHT10_WADDR									0x70	
	//===������
	#define AHT10_RADDR									0x71	
	//===��ʼ������
	#define AHT10_CMD_INIT								0xE1
	//===��������
	#define AHT10_CMD_MEASURE							0xAC	
	//===�����λ
	#define AHT10_CMD_RESET								0xBA

	//===�ṹ�嶨��
	typedef struct _AHT10_HandlerType					AHT10_HandlerType;
	//===ָ��ṹ�嶨��
	typedef struct _AHT10_HandlerType					*pAHT10_HandlerType;
	//===SHT2X�����ݽṹ��
	struct _AHT10_HandlerType
	{
		INT32_T				msgTemp;															//---�Ŵ�100�����¶�ֵ
		INT32_T				msgHumi;															//---�Ŵ�100����ʪ��ֵ
		UINT16_T			msgIntervalTime;														//---��ѯʱ����,��λ��ms
		UINT32_T			msgRecordTime;															//---��¼��ʱ�����
		I2C_HandlerType		msgI2C;																	//---ʹ�õ�I2C
		UINT32_T(*msgTimeTick)(void);																//---ʱ�����
	};

	//===�����������
	#define AHT10_TASK_ONE								pAht10Device0
	#define AHT10_TASK_TWO								0
	#define AHT10_TASK_THREE							0

	//===�ⲿ���ýӿ�
	extern AHT10_HandlerType							g_Aht10Device0;
	extern pAHT10_HandlerType							pAht10Device0;

	//===��������
	UINT8_T AHT10_I2C_DeInit(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_Init(AHT10_HandlerType* AHT10x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T AHT10_I2C_Config(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_StartMeasure(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_STATE(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_ReadTempHumi(AHT10_HandlerType* AHT10x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*AHT10_CFG_H_ */