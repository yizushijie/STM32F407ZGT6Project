#ifndef I2C_CFG_H_
#define I2C_CFG_H_
///////////////////////////////////////////////////////////////////////////////
//////ʹ�øú��������ȱ�֤GPIO��ʱ���Ѿ�ʹ�ܣ������ڲ��Ѿ����˿�����Ϊ��©���
//////ʹ��Ӳ����ѯģʽ��������ʽ���ڷ���START�ź�ǰ����Ҫ���STOP�Ƿ�ʹ���ˣ�
//////���ʹ����STOP����Ҫ���STOP�źŵģ������쳣״̬֮��I2C��ʱ���ָܻ�
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "systick_task.h"
	#include "log_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===�����Ƿ�ͨ����λ����I2C��busy����������
	#define USE_RESET_I2C
	//===����ṹ��
	typedef struct _I2C_HandlerType					I2C_HandleType;
	//===����ָ��ṹ��
	typedef	struct _I2C_HandlerType					*pI2C_HandlerType;
	//===�ṹ����
	struct _I2C_HandlerType
	{
		GPIO_HandleType		msgSCL;																						//---SCL
		GPIO_HandleType		msgSDA;																						//---SDA
		UINT8_T				msgHwMode;																					//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
		UINT16_T			msgPluseWidth;																				//---�����ȣ����ģ��ʹ��
		UINT16_T			msgAddr;																					//---�豸�ĵ�ַ
		UINT32_T			msgClockSpeed;																				//---Ӳ��I2C��ʱ���ٶ�
		UINT32_T			msgRegCCR;																					//---Ӳ��I2Cʱ�ӵĲ�������
		void(*pMsgDelayus)(UINT32_T delay);																				//---��ʱ����
	#ifndef USE_MCU_STM32F1
		UINT32_T			msgGPIOAlternate;																			//---�˿ڸ���ģʽ
	#endif
		UINT32_T(*pMsgTimeTick)(void);																					//---���ڳ�ʱ����
		I2C_TypeDef		* pMsgI2Cx;																						//---ʹ�õ�I2C�ӿ�
	#ifdef  USE_RESET_I2C
		LL_I2C_InitTypeDef	msgI2CInitTypeDef;																			//---ʹ�õ�I2C��ʼ������
	#endif 

	};

	//===��������
	UINT8_T I2C_MSW_Init(I2C_HandleType *I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T I2C_MSW_DeInit(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_START(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_STOP(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_ACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_NACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_ReadACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_WaitACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_SendACK(I2C_HandleType *I2Cx, UINT8_T isNACK);
	UINT8_T I2C_MSW_SendByte(I2C_HandleType *I2Cx, UINT8_T val);
	UINT8_T I2C_MSW_SendWord(I2C_HandleType *I2Cx, UINT16_T val);
	UINT8_T I2C_MSW_SendBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2C_MSW_ReadByte(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_ReadBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2C_MSW_CheckDevice(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_SendCMD(I2C_HandleType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);
	UINT8_T I2C_MHW_Init(I2C_HandleType* I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T I2C_MHW_DeInit(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_PollMode_START(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_CheckSTOP(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_PollMode_STOP(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_PollMode_ADDR(I2C_HandleType* I2Cx, UINT8_T isWrite);
	UINT8_T I2C_MHW_CheckClock(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_ClearBusy(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_CheckBusy(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_SendACK(I2C_HandleType* I2Cx, UINT8_T isNACK);
	UINT8_T I2C_MHW_PollMode_SendByte(I2C_HandleType* I2Cx, UINT8_T val, UINT8_T isBTF);
	UINT8_T I2C_MHW_PollMode_ReadByte(I2C_HandleType* I2Cx);
	UINT8_T I2C_Master_DeInit(I2C_HandleType* I2Cx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_CFG_H_ */
