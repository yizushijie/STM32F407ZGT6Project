#ifndef I2C_CFG_H_
#define I2C_CFG_H_
///////////////////////////////////////////////////////////////////////////////
//////ʹ�øú��������ȱ�֤GPIO��ʱ���Ѿ�ʹ�ܣ������ڲ��Ѿ����˿�����Ϊ��©���
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ṹ��
	typedef struct _I2C_HandlerType					I2C_HandlerType;

	//===����ָ��ṹ��
	typedef	struct _I2C_HandlerType					*pI2C_HandlerType;

	//===�ṹ����
	struct _I2C_HandlerType
	{
		I2C_TypeDef			*msgI2Cx;																//---ʹ�õ�I2C�ӿ�
		GPIO_HandlerType	msgSCL;																	//---SCL
		GPIO_HandlerType	msgSDA;																	//---SDA
		UINT8_T				msgModelIsHW;															//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
		UINT16_T			msgPluseWidth;															//---�����ȣ����ģ��ʹ��
		UINT16_T			msgAddr;																//---�豸�ĵ�ַ
		UINT32_T			msgClockSpeed;															//---Ӳ��I2C��ʱ���ٶ�
		void(*msgDelayus)(UINT32_T delay);														//---��ʱ����
	};

	//===��������
	UINT8_T I2C_MSW_Init(I2C_HandlerType *I2Cx, void(*pFuncDelayus)(UINT32_T delay));
	UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_START(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_SendACK(I2C_HandlerType *I2Cx, UINT8_T isNACK);
	UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2Cx, UINT8_T val);
	UINT8_T I2C_MSW_SendWord(I2C_HandlerType *I2Cx, UINT16_T val);
	UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2C_MSW_CheckDevice(I2C_HandlerType *I2Cx);
	UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_CFG_H_ */
