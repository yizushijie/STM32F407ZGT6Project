#include "mpu6050_cfg.h"

//===ȫ�ֱ�������
MPU6050_HandleType			g_Mpu6050Device0 = {0};
pMPU6050_HandleType		pMpu6050Device0=&g_Mpu6050Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������1�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Device0_Init(MPU6050_HandleType* MPU6050x)
{
	MPU6050x->msgI2C.pMsgI2Cx = NULL;
	MPU6050x->msgI2C.msgSCL.msgPort = GPIOB;
	MPU6050x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_8;
	MPU6050x->msgI2C.msgSDA.msgPort = GPIOB;
	MPU6050x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_9;
	MPU6050x->msgI2C.msgHwMode = 0;
	MPU6050x->msgI2C.msgPluseWidth = 0;
	MPU6050x->msgI2C.pMsgDelayus = NULL;
	MPU6050x->msgI2C.msgAddr = MPU6050_WADDR;
	MPU6050x->msgI2C.msgClockSpeed = 200000;
	//---GPIO����ģʽ
	MPU6050x->msgI2C.msgGPIOAlternate = LL_GPIO_AF_4;
	//---Ӳ��I2C��I2C1
	MPU6050x->msgI2C.pMsgI2Cx = I2C1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������2�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Device1_Init(MPU6050_HandleType* MPU6050x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������3�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Device2_Init(MPU6050_HandleType* MPU6050x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Init(MPU6050_HandleType* MPU6050x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((MPU6050x != NULL) && (MPU6050x == MPU6050_TASK_ONE))
	{
		MPU6050_I2C_Device0_Init(MPU6050x);
	}
	else if ((MPU6050x != NULL) && (MPU6050x == MPU6050_TASK_TWO))
	{
		MPU6050_I2C_Device1_Init(MPU6050x);
	}
	else if ((MPU6050x != NULL) && (MPU6050x == MPU6050_TASK_THREE))
	{
		MPU6050_I2C_Device2_Init(MPU6050x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(MPU6050x->msgI2C), pFuncDelayus,pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(MPU6050x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---ms��ʱ����
	MPU6050x->pMsgDelayms = ((pFuncDelayms!=NULL)? pFuncDelayms: DelayTask_ms);
	//---��������
	_return= MPU6050_I2C_ConfigInit(MPU6050x);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ��I2C�����ֽ�дд�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��I2C�����ֽ�дд�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr,0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), val,1);
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�I2C�����ֽ�дд�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val)
{
	if (MPU6050x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		return MPU6050_HWI2C_WriteSingle(MPU6050x, addr, val);
	}
	else
	{
		return MPU6050_SWI2C_WriteSingle(MPU6050x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ��I2C�����ֽ�д�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���Ͷ������ݣ�����д
	for (i=0;i<length;i++)
	{
		//---�������ݣ��ڲ��Ĵ�������
		I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), pVal[i]);
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
		if (_return != OK_0)
		{
			//---�������ݴ���
			_return = (ERROR_3+i);
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��I2C�����ֽ�д�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���Ͷ������ݣ�����д
	for (i = 0; i < length; i++)
	{
		//---�������ݣ��ڲ��Ĵ�������
		_return= I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), pVal[i], ((i==(length-1))?1:0));
		if (_return != OK_0)
		{
			//---�������ݴ���
			_return = (ERROR_3 + i);
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�I2C�����ֽ�д�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	if (MPU6050x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		//---Ӳ��I2C
		return MPU6050_HWI2C_WriteBulk(MPU6050x, addr, pVal,length);
	}
	else
	{
		return MPU6050_SWI2C_WriteBulk(MPU6050x,  addr, pVal,length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ��I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��ȡ����
	*pVal = I2CTask_MSW_ReadByte(&(MPU6050x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(MPU6050x->msgI2C), 1);
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr,0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(MPU6050x->msgI2C), 1);
	//---��ȡ����
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(MPU6050x->msgI2C));
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal)
{
	if (MPU6050x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		return MPU6050_HWI2C_ReadSingle(MPU6050x, addr, pVal);
	}
	else
	{
		return MPU6050_SWI2C_ReadSingle(MPU6050x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ��I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_ReadBulk(MPU6050_HandleType* MPU6050x,UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	//UINT8_T readTemp[6] = { 0 };
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---������ȡ6������
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(MPU6050x->msgI2C));
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(MPU6050x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_ReadBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr,UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr,0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---������ȡ6������
	for (i = 0; i < length; i++)
	{
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(MPU6050x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(MPU6050x->msgI2C));
	}
	_return = OK_0;
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadBulk(MPU6050_HandleType* MPU6050x,UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (MPU6050x->msgI2C.msgHwMode == 1)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		return  MPU6050_HWI2C_ReadBulk(MPU6050x,addr, pVal, length);
	}
	else
	{
		return MPU6050_SWI2C_ReadBulk(MPU6050x, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��ID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadChipID(MPU6050_HandleType* MPU6050x, UINT8_T *pChipID)
{
	//UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_WHO_AM_I, pChipID);
	////---У���ȡ���
	//if (_return!=OK_0)
	//{
	//	_return = ERROR_1;
	//}
	//else
	//{
	//	if (*pChipID!=0x68)
	//	{
	//		_return = ERROR_2;
	//	}
	//}
	//return _return;
	//*pChipID=I2C_HW_Read(MPU6050x->msgI2C.msgAddr, MPU6050_REG_ADDR_WHO_AM_I);
	return  MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_WHO_AM_I, pChipID);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���ٶ�ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadAccel(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempAccel[6] = { 0 };
	//---��ȡ����ֵ
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_ACCEL_XOUT_H, tempAccel, 6);
	//---У���ȡ���
	if (_return==OK_0)
	{
		MPU6050x->msgAccel.xAccel = tempAccel[0];
		MPU6050x->msgAccel.xAccel = (MPU6050x->msgAccel.xAccel << 8) + tempAccel[1];

		MPU6050x->msgAccel.yAccel = tempAccel[2];
		MPU6050x->msgAccel.yAccel = (MPU6050x->msgAccel.yAccel << 8) + tempAccel[3];

		MPU6050x->msgAccel.zAccel = tempAccel[4];
		MPU6050x->msgAccel.zAccel = (MPU6050x->msgAccel.zAccel << 8) + tempAccel[5];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�¶�ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadTemp(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempTemp[2] = { 0 };
	//---��ȡ����ֵ
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_TEMP_OUT_H, tempTemp, 2);
	//---У���ȡ���
	if (_return == OK_0)
	{
		float mpuTemp = tempTemp[0];
		mpuTemp =((UINT16_T)mpuTemp <<8)+ tempTemp[1];
		mpuTemp = mpuTemp / 340.0 + 36.53;
		MPU6050x->msgTemp = (INT32_T)(mpuTemp * 100.0);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ������ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadGyro(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempGyro[6] = { 0 };
	//---��ȡ����ֵ
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_GYRO_XOUT_H, tempGyro, 6);
	//---У���ȡ���
	if (_return == OK_0)
	{
		MPU6050x->msgGyro.xGyro = tempGyro[0];
		MPU6050x->msgGyro.xGyro = (MPU6050x->msgGyro.xGyro << 8) + tempGyro[1];

		MPU6050x->msgGyro.yGyro = tempGyro[2];
		MPU6050x->msgGyro.yGyro = (MPU6050x->msgGyro.yGyro << 8) + tempGyro[3];

		MPU6050x->msgGyro.zGyro = tempGyro[4];
		MPU6050x->msgGyro.zGyro = (MPU6050x->msgGyro.zGyro << 8) + tempGyro[5];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���ٶȣ��¶ȣ������ǵ�ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadAccelTempGyro(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempVal[14] = { 0 };
	MPU6050x->msgAccel.xAccel = 0;
	MPU6050x->msgAccel.yAccel = 0;
	MPU6050x->msgAccel.zAccel = 0;
	MPU6050x->msgTemp = 0;
	MPU6050x->msgGyro.xGyro = 0;
	MPU6050x->msgGyro.yGyro = 0;
	MPU6050x->msgGyro.zGyro = 0;
	//---��ȡ����ֵ
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_ACCEL_XOUT_H, tempVal, 14);
	//---У���ȡ���
	if (_return == OK_0)
	{
		//---������ٶ�
		MPU6050x->msgAccel.xAccel = tempVal[0];
		MPU6050x->msgAccel.xAccel = (MPU6050x->msgAccel.xAccel << 8) + tempVal[1];

		MPU6050x->msgAccel.yAccel = tempVal[2];
		MPU6050x->msgAccel.yAccel = (MPU6050x->msgAccel.yAccel << 8) + tempVal[3];

		MPU6050x->msgAccel.zAccel = tempVal[4];
		MPU6050x->msgAccel.zAccel = (MPU6050x->msgAccel.zAccel << 8) + tempVal[5];

		//---�����¶�
		float mpuTemp = tempVal[6];
		mpuTemp = ((UINT16_T)mpuTemp << 8) + tempVal[7];
		mpuTemp = mpuTemp / 340.0 + 36.53;
		MPU6050x->msgTemp = (INT32_T)(mpuTemp * 100.0);

		//---����������
		MPU6050x->msgGyro.xGyro = tempVal[8];
		MPU6050x->msgGyro.xGyro = (MPU6050x->msgGyro.xGyro << 8) + tempVal[9];

		MPU6050x->msgGyro.yGyro = tempVal[10];
		MPU6050x->msgGyro.yGyro = (MPU6050x->msgGyro.yGyro << 8) + tempVal[11];

		MPU6050x->msgGyro.zGyro = tempVal[12];
		MPU6050x->msgGyro.zGyro = (MPU6050x->msgGyro.zGyro << 8) + tempVal[13];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ʱ�Ӳ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteSMPRTDIV(MPU6050_HandleType* MPU6050x, UINT8_T smprtDiv)
{
	return MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_SMPLRT_DIV, smprtDiv);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡʱ�Ӳ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadSMPRTDIV(MPU6050_HandleType* MPU6050x, UINT8_T *pSMPRTDIV)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_SMPLRT_DIV, pSMPRTDIV);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����������˲���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteLPF(MPU6050_HandleType* MPU6050x, UINT8_T lpf)
{
	UINT8_T tempCFG = 0;
	//---��ȡ������Ϣ
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_CONFIG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~lpf;
		tempCFG |= lpf;
		//---��������Ϣд���豸
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_CONFIG, tempCFG);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Reset(MPU6050_HandleType* MPU6050x)
{
	return MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_PWR_MGMT_1, 0x80);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ж�״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadINTSTATUS(MPU6050_HandleType* MPU6050x, UINT8_T *pINTSTATUS)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_STATUS, pINTSTATUS);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ж�ʹ��Ϊ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadINTENABLE(MPU6050_HandleType* MPU6050x, UINT8_T* pINTENABLE)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, pINTENABLE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д�ж�ʹ��Ϊ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteINTENABLE(MPU6050_HandleType* MPU6050x, UINT8_T intEnable)
{
	UINT8_T tempCFG = 0;
	//---��ȡ������Ϣ
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~intEnable;
		tempCFG |= intEnable;
		//---��������Ϣд���豸
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ж�����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadINTPINCFG(MPU6050_HandleType* MPU6050x, UINT8_T* pINTPINCFG)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, pINTPINCFG);;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д�ж�����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteINTPINCFG(MPU6050_HandleType* MPU6050x, UINT8_T intPinCfg)
{
	UINT8_T tempCFG = 0;
	//---��ȡ������Ϣ
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~intPinCfg;
		tempCFG |= intPinCfg;
		//---��������Ϣд���豸
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�����ǵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadGyroRange(MPU6050_HandleType* MPU6050x, UINT8_T *pGyroRange)
{
	UINT8_T _return= MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_GYRO_CONFIG, pGyroRange);
	*pGyroRange &= MPU6050_GYRO_FS_MASK;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����������ǵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteGyroRange(MPU6050_HandleType* MPU6050x, UINT8_T gyroRange)
{
	UINT8_T tempCFG = 0;
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_GYRO_CONFIG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~gyroRange;
		tempCFG |= gyroRange;
		//---��������Ϣд���豸
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_GYRO_CONFIG, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���ٶȵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadAccelRange(MPU6050_HandleType* MPU6050x, UINT8_T* pAccelRange)
{
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_ACCEL_CONFIG, pAccelRange);
	*pAccelRange &= MPU6050_ACCEL_FS_MASK;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����������ǵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteAccelRange(MPU6050_HandleType* MPU6050x, UINT8_T accelRange)
{
	UINT8_T tempCFG = 0;
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_ACCEL_CONFIG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~accelRange;
		tempCFG |= accelRange;
		//---��������Ϣд���豸
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_ACCEL_CONFIG, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ĭ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ConfigInit(MPU6050_HandleType* MPU6050x)
{
	UINT8_T tempVal = 0;
	//---��ȡID��Ϣ
	UINT8_T _return = MPU6050_I2C_ReadChipID(MPU6050x, &tempVal);
	if ((_return!=OK_0)||(tempVal!=0x68))
	{
		return ERROR_1;
	}
	//---�����豸
	_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_PWR_MGMT_1, 0x00);
	//---���ò���ʱ��,1K/200��Ƶ��50Hz
	_return = MPU6050_I2C_WriteSMPRTDIV(MPU6050x, MPU6050_SMPRT_DIV_20);
	//---���������˲���,����20Hz
	_return = MPU6050_I2C_WriteLPF(MPU6050x, MPU6050_DLPF_BW_20);
	//---���ü��ٶ����̣�+/-8G
	_return = MPU6050_I2C_WriteAccelRange(MPU6050x, MPU6050_ACCEL_FS_8);
	//---�������������̣�+/-2000G
	_return = MPU6050_I2C_WriteGyroRange(MPU6050x, MPU6050_GYRO_FS_2000);
	//---�����ж�����
	_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, 0x80);//MPU6050_INT_LEVEL_LOW| MPU6050_INTDRV_PUSHPULL| MPU6050_INT_LATCH_WAITCLEAR);
	MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, 0x01);                    // ʹ�á�����׼���á��жϡ�
	return _return;
}
