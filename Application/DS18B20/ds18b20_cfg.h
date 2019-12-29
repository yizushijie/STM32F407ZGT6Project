#ifndef DS18B20_CFG_H_
#define DS18B20_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "one_wire_task.h"
	#include "systick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ṹ��
	typedef struct _DS18B20_HandlerType				DS18B20_HandlerType;
	//===����ָ��ṹ
	typedef struct _DS18B20_HandlerType				*pDS18B20_HandlerType;

	//===�ṹ����
	struct _DS18B20_HandlerType
	{
		UINT8_T					msgIsPositive;														//---0---�����ݣ�1---�Ǹ�����2---����ֵ
		UINT8_T					msgTempBit;															//---0---9Bit,1---10Bit,2---11Bit,3---12Bit
		UINT8_T					msgTempTH;															//---�¶����ޣ�7Bit���ݣ���λΪ0��������ֵ
		UINT8_T					msgTempTL;															//---�¶����ޣ�7Bit���ݣ���λΪ0��������ֵ
		UINT16_T				msgTempX100;														//---�¶ȵ�ֵ���Ŵ�100����ֵ
		UINT32_T				msgTempX10000;														//---�¶ȵ�ֵ���Ŵ�1000����ֵ
		UINT16_T				msgIntervalTime;													//---��ѯʱ����,��λ��ms
		UINT16_T				msgTempBitValX10000;												//---�Ķηֱ���ÿBit������¶ȵ�ֵ
		UINT32_T				msgRecordTime;														//---��¼��ʱ�����
		OneWire_HandlerType		msgOneWire;															//---һ��ͨ��
		void(*msgDelayms)(UINT32_T delay);															//---ms��ʱ����
		UINT32_T(*msgTimeTick)(void);																//---ʱ�����
	};

	//===�����������
	#define DS18B20_TASK_ONE						pDs18b20Device0
	#define DS18B20_TASK_TWO						0
	#define DS18B20_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern DS18B20_HandlerType						g_Ds18b20Device0;
	extern pDS18B20_HandlerType						pDs18b20Device0;

	//===�����Ķ���
	UINT8_T  DS18B20_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T  DS18B20_OneWire_Device0_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_Device1_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_Device2_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_DeInit(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_ReadID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
	UINT16_T DS18B20_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x);
	UINT16_T DS18B20_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
	UINT8_T  DS18B20_OneWire_Config(DS18B20_HandlerType* DS18B20x, void(*pFuncDelayus)(UINT32_T delay));
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_CFG_H_ */
