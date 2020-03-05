#include "i2c_cfg.h"

//>>>===ģ��I2C����---��ʼ
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandleType *I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(I2Cx->msgSCL.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(I2Cx->msgSDA.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;																			//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																			//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																	//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																				//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																			//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---us��ʱ����
	I2Cx->pMsgDelayus = ((pFuncDelayus != NULL) ? pFuncDelayus : DelayTask_us);
	//---ע��δ���
	I2Cx->pMsgTimeTick = ((pFuncTimerTick != NULL) ? pFuncTimerTick : SysTickTask_GetTick);
	//---���ģʽ
	I2Cx->msgHwMode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_DeInit(I2C_HandleType *I2Cx)
{
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;					//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_START(I2C_HandleType *I2Cx)
{
	//---������ʼ�����������ź�
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	//---������ʼ�ź�;
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	//---ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---0��ʧ��SDA---1
	return  ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00)?ERROR_1:OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_STOP(I2C_HandleType *I2Cx)
{
	//---����ֹͣ�����������ź�
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---1��ʧ��SDA---0
	return ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) == 0x00) ? ERROR_1 : OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandleType *I2Cx)
{
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---��ʱ�ȴ����ȴ�SCL���ӻ��ͷ�
	//if (I2Cx->msgPluseWidth>0)
	//{
	//	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	//}
	//���SCL���ӻ��ͷ�,SCLΪ��,����ӻ��ͷ�����
	GPIOTask_WaitPinPort(&(I2Cx->msgSCL), 1);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandleType *I2Cx)
{
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---��ʱ�ȴ����ȴ�SCL���ӻ��ͷ�
	//if (I2Cx->msgPluseWidth>0)
	//{
	//	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	//}
	//���SCL���ӻ��ͷ�,SCLΪ��,����ӻ��ͷ�����
	GPIOTask_WaitPinPort(&(I2Cx->msgSCL), 1);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---��ȡӦ���ź�
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---��ʱ�ȴ����ȴ�SCL���ӻ��ͷ�
	//if (I2Cx->msgPluseWidth > 0)
	//{
	//	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	//}
	//���SCL���ӻ��ͷ�,SCLΪ��,����ӻ��ͷ�����
	GPIOTask_WaitPinPort(&(I2Cx->msgSCL), 1);
	//---��ȡSDA��״̬�ź�---ACK״̬��SDAΪ�͵�ƽ
	_return= ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00) ? ERROR_1 : OK_0);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---��ȡӦ���ź�
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---�ȴ�Ӧ���ź�
	//UINT8_T i = 0;
	//for (i = 255; i > 0; i--)
	//{
	//	//---��ȡSDA��״̬
	//	if (GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit))
	//	{
	//		break;
	//	}
	//}
	//if (i == 0)
	//{
	//	I2C_MSW_STOP(I2Cx);
	//	return ERROR_1;
	//}
	////---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	//GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//���SDA��ƽ,SDAΪ��,����ӻ�����ACK
	_return= GPIOTask_WaitPinPort(&(I2Cx->msgSDA), 1);
	if(_return != OK_0) 
	{	  
	 	I2C_MSW_STOP(I2Cx);
	}
	else
	{
	  	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendACK(I2C_HandleType *I2Cx, UINT8_T isNACK)
{
	if (isNACK)
	{
		return I2C_MSW_NACK(I2Cx);
	}
	else
	{
		return I2C_MSW_ACK(I2Cx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBit(I2C_HandleType *I2Cx, UINT8_T bitVal)
{
	((bitVal&0x80)!=0x00)? GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit): GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---һ��ʱ������
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);	
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	//DELAY_NOP_COUNT(2);
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);	
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendByte(I2C_HandleType *I2Cx, UINT8_T val)
{
	UINT8_T i = 0;
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, val);
		val <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---�����ֽڸ���
	UINT8_T byteCount = (bitNum / 8);
	//---����bit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;
	//---���������ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2Cx, pVal[i]);
	}
	//---��������---���ݵķ��ͣ����ȷ��͸�λ
	pVal[byteCount] <<= (8 - bitCount);
	//---�жϷ��������ǲ��ǲ�����1�ֽ�
	if (byteCount == 0)
	{
		//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	//---����ָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2Cx, pVal[byteCount]);
		pVal[byteCount] <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendWord(I2C_HandleType *I2Cx, UINT16_T val)
{
	UINT8_T valH = (UINT8_T)(val >> 8);
	UINT8_T valL = (UINT8_T)(val);
	UINT8_T i = 0;
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, valH);
		//---�������ƶ�
		valH <<= 1;
	}
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, valL);
		//---��������
		valL <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadBit(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---ʱ��������
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	//DELAY_NOP_COUNT(4);
	//---��ȡ����λ
	_return= ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00) ? 1 : 0);
	//---ʱ�Ӹ�����
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandleType *I2Cx)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;
	//---׼�����ݵĶ�ȡ
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2Cx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---��ȡ�ֽڸ���
	UINT8_T byteCount = (bitNum / 8);
	//---��ȡbit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;
	//---��ȡ�����ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2Cx);
	}
	//---���㴦��
	pVal[byteCount] = 0x00;
	//---�ж϶�ȡ��Bit�����ǲ��ǲ�����1�ֽ�
	if (byteCount == 0)
	{
		//---׼�����ݵĶ�ȡ
		GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
		//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	//---��ȡָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2Cx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_CheckDevice(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	if ((GPIO_GET_STATE(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit)) && (GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit)))
	{
		//---���������ź�
		I2C_MSW_START(I2Cx);
		//---���Ͷ�ȡ��������
		I2Cx->msgAddr |= 0x01;
		//---���ʹӻ���ַ
		I2C_MSW_SendByte(I2Cx, (UINT8_T)I2Cx->msgAddr);
		//---��ȡӦ���ź�
		_return = I2C_MSW_ReadACK(I2Cx);
	}
	else
	{
		_return = ERROR_2;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendCMD(I2C_HandleType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---�������������ź�
		_return = I2C_MSW_START(I2Cx);
		if (_return)
		{
			I2C_MSW_STOP(I2Cx);
			return ERROR_1;
		}
	}
	//---��������
	_return = I2C_MSW_SendByte(I2Cx, cmd);
	//---��ȡӦ��
	_return = I2C_MSW_ReadACK(I2Cx);
	//---ֹͣ����������
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2Cx);
	}
	return _return;
}
//////////////////////////////////////////////////////////////////////////////
//<<<===ģ��I2C����---����

//////////////////////////////////////////////////////////////////////////////
//>>>===Ӳ��I2C����---��ʼ


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ʹ��I2C������ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_Clock(I2C_HandleType* I2Cx, UINT8_T isEnable)
{
	#ifdef I2C3
	if (I2Cx->pMsgI2Cx == I2C1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	#ifdef I2C2
	if (I2Cx->pMsgI2Cx == I2C2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
#ifdef I2C3
	if (I2Cx->pMsgI2Cx == I2C3)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_Init(I2C_HandleType* I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(I2Cx->msgSCL.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(I2Cx->msgSDA.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;																			//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;																		//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																	//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																				//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = I2Cx->msgGPIOAlternate;																	//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);

	//---����I2C����ʱ��
	I2C_Clock(I2Cx, PERIPHERAL_CLOCK_ENABLE);
	//---��λI2C
	LL_I2C_DeInit(I2Cx->pMsgI2Cx);
#ifdef  USE_RESET_I2C
	LL_I2C_EnableReset(I2Cx->pMsgI2Cx);
	LL_I2C_DisableReset(I2Cx->pMsgI2Cx);
#endif
	//---��ʼ��I2C
	LL_I2C_InitTypeDef I2C_InitStruct={0};
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;																	//---����ģʽ
	I2C_InitStruct.ClockSpeed = I2Cx->msgClockSpeed;																	//---SCLʱ��Ƶ��
	I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;																		//---ʱ��ռ�ձ�
	I2C_InitStruct.OwnAddress1 = 0;																						//---�����I2C�豸��ַ
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;																		//---ʹ�ܻ��߹ر���Ӧ(Ĭ��һ�㿪��)
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;																//---ָ����ַ�ĳ��ȣ�7Bit����10BIt
	//---��ʼ��
	LL_I2C_Init(I2Cx->pMsgI2Cx, &I2C_InitStruct);
	//---��ȡʱ�ӷ�Ƶ��
	I2Cx->msgRegCCR = LL_I2C_GetClockPeriod(I2Cx->pMsgI2Cx);
	//---�ڶ�����ַ
	LL_I2C_SetOwnAddress2(I2Cx->pMsgI2Cx, 0);
	//---ʹ��I2C
	LL_I2C_Enable(I2Cx->pMsgI2Cx);
	//---us��ʱ����
	I2Cx->pMsgDelayus = ((pFuncDelayus != NULL) ? pFuncDelayus : DelayTask_us);
	//---ע��δ���
	I2Cx->pMsgTimeTick = ((pFuncTimerTick != NULL) ? pFuncTimerTick : SysTickTask_GetTick);
	//---Ӳ��ģʽ
	I2Cx->msgHwMode = 1;
#ifdef  USE_RESET_I2C
	//---����I2C�����ò���
	I2Cx->msgI2CInitTypeDef= I2C_InitStruct;
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_DeInit(I2C_HandleType* I2Cx)
{
	//---��λI2C
	LL_I2C_DeInit(I2Cx->pMsgI2Cx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ѵ��ʽ���ȴ�У���־
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_WaitFlag(I2C_HandleType* I2Cx,UINT32_T (*pFuncActiveFlag)(I2C_TypeDef* I2Cx), FlagStatus flagStatus)
{
	UINT8_T _return = OK_0;
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---��ȡ��ǰʱ�����
	oldTime = ((I2Cx->pMsgTimeTick != NULL) ? I2Cx->pMsgTimeTick() : 0);
	//---��鳬ʱ
	while (1)
	{
		//if (LL_I2C_IsActiveFlag_BUSY(I2Cx->msgI2Cx) == RESET)
		if (pFuncActiveFlag(I2Cx->pMsgI2Cx) == flagStatus)
		{
			break;
		}
		//---��ʱ�ж�
		if (I2Cx->pMsgTimeTick != NULL)
		{
			//---��ǰʱ��
			nowTime = I2Cx->pMsgTimeTick();
			//---�жϵδ�ʱ�Ƿ����������
			if (nowTime < oldTime)
			{
				cnt = (0xFFFFFFFF - oldTime + nowTime);
			}
			else
			{
				cnt = nowTime - oldTime;
			}
			//---�ж��Ƿ�ʱ
			if (cnt > 30)
			{
				//---���ͷ�����ʱ����
				_return = ERROR_1;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---���ͷ�����ʱ����
				_return = ERROR_2;
			}
		}
		//---�˳�ѭ��
		if (_return != OK_0)
		{
			//---���ͽ�������,����״̬�쳣�����ڲ���ֹͣ����
			I2C_MHW_PollMode_STOP(I2Cx);
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����������ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_START(I2C_HandleType* I2Cx)
{
	//---��֤I2C���費��ʹ����
	UINT8_T _return =I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_BUSY,RESET);
	//---У��������
	if (_return == OK_0)
	{
		//---����START�ź�
		LL_I2C_GenerateStartCondition(I2Cx->pMsgI2Cx);
		//---��֤��ʼλ�Ƿ���
		_return=I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_SB, SET);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� У��STOP�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_CheckSTOP(I2C_HandleType* I2Cx)
{
	if (LL_I2C_IsEnabledGenerateStop(I2Cx->pMsgI2Cx)!=0)
	{
		LL_I2C_DisabledGenerateStop(I2Cx->pMsgI2Cx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ֹͣ�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_STOP(I2C_HandleType* I2Cx)
{
	//---���ͽ�������
	LL_I2C_GenerateStopCondition(I2Cx->pMsgI2Cx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ֹͣ�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_ADDR(I2C_HandleType* I2Cx,UINT8_T isWrite)
{
	UINT8_T _return = OK_0;
	//---�����豸��ַ
	LL_I2C_TransmitData8(I2Cx->pMsgI2Cx, (isWrite==1)?(I2Cx->msgAddr&0xFE):(I2Cx->msgAddr |0x01));
	//---��֤��֤��ַ�������
	_return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_ADDR, SET);
	//---�����־λ
	LL_I2C_ClearFlag_ADDR(I2Cx->pMsgI2Cx);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ʱ�Ӳ�����У��У��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_CheckClock(I2C_HandleType* I2Cx)
{
	if (I2Cx->msgRegCCR != LL_I2C_GetClockPeriod(I2Cx->pMsgI2Cx))
	{
		LL_I2C_SetClockPeriod(I2Cx->pMsgI2Cx, I2Cx->msgRegCCR);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_SendACK(I2C_HandleType* I2Cx, UINT8_T isNACK)
{
	LL_I2C_AcknowledgeNextData(I2Cx->pMsgI2Cx, ((isNACK!=0)?LL_I2C_NACK: LL_I2C_ACK));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����Busy��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_ClearBusy(I2C_HandleType* I2Cx)
{
	UINT8_T i = 0;
	LL_I2C_DeInit(I2Cx->pMsgI2Cx);
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																			//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																	//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																				//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																			//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	//---SCL����9�����壬�����ͷ�����
	for (i = 0; i < 9; i++)
	{
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
		I2Cx->pMsgDelayus(10);
		GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
		I2Cx->pMsgDelayus(10);
	}
	//---I2C�˿ڵĸ���ģʽ
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;																		//---����״̬Ϊ���ģʽ
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = I2Cx->msgGPIOAlternate;																	//---�˿ڸ���ģʽ
#endif
	//---SCL�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	//GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	//GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
#ifdef  USE_RESET_I2C
	I2Cx->pMsgDelayus(1000);
	//---���³�ʼ��i2C
	LL_I2C_Init(I2Cx->pMsgI2Cx, &(I2Cx->msgI2CInitTypeDef));
	//---��ȡʱ�ӷ�Ƶ��
	I2Cx->msgRegCCR = LL_I2C_GetClockPeriod(I2Cx->pMsgI2Cx);
	//---�ڶ�����ַ
	LL_I2C_SetOwnAddress2(I2Cx->pMsgI2Cx, 0);
	//---ʹ��I2C
	LL_I2C_Enable(I2Cx->pMsgI2Cx);
#endif
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_CheckBusy(I2C_HandleType* I2Cx)
{
	//---��֤I2C���費��ʹ���У���鵽æ��ʶ
	UINT8_T _return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_BUSY, RESET);
	if(_return!=OK_0)
	{
		_return= I2C_MHW_ClearBusy(I2Cx);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		�������һ�η�������ʹ��isBTFΪ1����ʹ��BTF��־λ��������֤���ݴ������
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_SendByte(I2C_HandleType* I2Cx, UINT8_T val,UINT8_T isBTF)
{
	//---��ַλ�Ѿ���λ,ͨ��TXEҲ�����,Ϊ�˽���,�ٲ�һ��
	UINT8_T _return= I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_TXE, SET);
	//---У���ַ��λ
	if (_return==OK_0)
	{
		//---��������
		LL_I2C_TransmitData8(I2Cx->pMsgI2Cx, val);
		//---У�鷢�ͼĴ�����
		_return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_TXE, SET);
		//---У�����ݴ������
		if ((_return == OK_0) && (isBTF != 0))
		{
			_return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_BTF, SET);
		}
	}	
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_ReadByte(I2C_HandleType* I2Cx)
{
	//---У����ռĴ�����Ϊ��
	UINT8_T _return= I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_RXNE, SET);
	//---У���ȡ
	if (_return==OK_0)
	{
		//---�����Ѷ�ȡ
		_return = LL_I2C_ReceiveData8(I2Cx->pMsgI2Cx);
	}
	return _return;
}
//////////////////////////////////////////////////////////////////////////////
//<<<===Ӳ��I2C����---����

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_Master_DeInit(I2C_HandleType* I2Cx)
{
	//---ע��I2C�豸
	return ((I2Cx->msgHwMode != 0) ? (I2C_MHW_DeInit(I2Cx)) : (I2C_MSW_DeInit(I2Cx)));
}