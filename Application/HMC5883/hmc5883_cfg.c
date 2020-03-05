#include "hmc5883_cfg.h"

//===ȫ�ֱ�������
HMC5883_HandleType		g_Hmc5883Device0 = { 0 };
pHMC5883_HandleType	pHmc5883Device0=&g_Hmc5883Device0;


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Device0_Init(HMC5883_HandleType* HMC5883x)
{
	HMC5883x->msgI2C.pMsgI2Cx = NULL;
	HMC5883x->msgI2C.msgSCL.msgPort = GPIOB;
	HMC5883x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	HMC5883x->msgI2C.msgSDA.msgPort = GPIOB;
	HMC5883x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	HMC5883x->msgI2C.msgHwMode = 0;
	HMC5883x->msgI2C.msgPluseWidth = 0;
	HMC5883x->msgI2C.pMsgDelayus = NULL;
	HMC5883x->msgI2C.msgAddr = HMC5883_WADDR;
	HMC5883x->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Device1_Init(HMC5883_HandleType* HMC5883x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Device2_Init(HMC5883_HandleType* HMC5883x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ʼ��
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Init(HMC5883_HandleType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay),UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((HMC5883x != NULL) && (HMC5883x == HMC5883_TASK_ONE))
	{
		HMC5883_I2C_Device0_Init(HMC5883x);
	}
	else if ((HMC5883x != NULL) && (HMC5883x == HMC5883_TASK_TWO))
	{
		HMC5883_I2C_Device1_Init(HMC5883x);
	}
	else if ((HMC5883x != NULL) && (HMC5883x == HMC5883_TASK_THREE))
	{
		HMC5883_I2C_Device2_Init(HMC5883x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(HMC5883x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(HMC5883x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---ms��ʱ����
	HMC5883x->pMsgDelayms = ((pFuncDelayms != NULL) ? pFuncDelayms : DelayTask_ms);
	//---���ó�ʼ��
	_return = HMC5883_I2C_ConfigInit(HMC5883x);
	//---���ó�ʼ��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_DeInit(HMC5883_HandleType* HMC5883x)
{
	return I2CTask_Master_DeInit(&(HMC5883x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ֽ�дд�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_HWI2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(HMC5883x->msgI2C));
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	if (HMC5883x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(HMC5883x->msgI2C));
		return HMC5883_HWI2C_WriteSingle(HMC5883x, addr, val);
	}
	else
	{
		return HMC5883_SWI2C_WriteSingle(HMC5883x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��ȡ����
	*pVal = I2CTask_MSW_ReadByte(&(HMC5883x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(HMC5883x->msgI2C), 1);
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_HWI2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(HMC5883x->msgI2C), 1);
	//---��ȡ����
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(HMC5883x->msgI2C));
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	if (HMC5883x->msgI2C.msgHwMode!=0)
	{
		I2CTask_MHW_CheckClock(&(HMC5883x->msgI2C));
		//---Ӳ��I2C
		return HMC5883_HWI2C_ReadSingle(HMC5883x, addr, pVal);
	}
	else
	{
		return HMC5883_SWI2C_ReadSingle(HMC5883x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_ReadBulk(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	//UINT8_T readTemp[6] = { 0 };
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 0);
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
		pVal[i] = I2CTask_MSW_ReadByte(&(HMC5883x->msgI2C));
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(HMC5883x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_HWI2C_ReadBulk(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(HMC5883x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(HMC5883x->msgI2C));
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ReadBulk(HMC5883_HandleType* HMC5883x,UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (HMC5883x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(HMC5883x->msgI2C));
		//---Ӳ��I2C
		return  HMC5883_HWI2C_ReadBulk(HMC5883x,addr,pVal, length);
	}
	else
	{
		return HMC5883_SWI2C_ReadBulk(HMC5883x,addr, pVal, length);
	}	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ConfigInit(HMC5883_HandleType* HMC5883x)
{
	return HMC5883_I2C_WriteSingle(HMC5883x,0x02, 0x00);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ų�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ReadRawData(HMC5883_HandleType* HMC5883x)
{
	UINT8_T readTemp[6] = { 0 };
	//---��ȡֵ
	UINT8_T _return = HMC5883_I2C_ReadBulk(HMC5883x, HMC5883_DXMSB_REG,readTemp,6);
	//---���ݼ���
	if (_return == OK_0)
	{
		//---����X��
		HMC5883x->msgX = readTemp[0];
		HMC5883x->msgX = (HMC5883x->msgX << 8) + readTemp[1];
		//---�������ƵĲ���ת��Ϊʵ��ֵ
		if ((HMC5883x->msgX & 0x8000) != 0)
		{
			HMC5883x->msgX = -(0xFFFF - HMC5883x->msgX + 1);
		}
		//---����Z��
		HMC5883x->msgZ = readTemp[2];
		HMC5883x->msgZ = (HMC5883x->msgZ << 8) + readTemp[3];
		//---�������ƵĲ���ת��Ϊʵ��ֵ
		if ((HMC5883x->msgZ & 0x8000) != 0)
		{
			HMC5883x->msgZ = -(0xFFFF - HMC5883x->msgZ + 1);
		}
		//---����Y��
		HMC5883x->msgY = readTemp[4];
		HMC5883x->msgY = (HMC5883x->msgY << 8) + readTemp[5];
		//---�������ƵĲ���ת��Ϊʵ��ֵ
		if ((HMC5883x->msgY & 0x8000) != 0)
		{
			HMC5883x->msgY = -(0xFFFF - HMC5883x->msgY + 1);
		}
		//---����Ƕ�
		HMC5883x->msgAngle = atan2((double)(HMC5883x->msgY - HMC5883x->msgOffsetY), (double)(HMC5883x->msgX - HMC5883x->msgOffsetX)) * (180 / 3.14159265) + 180;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� У׼���㣬��ֵУ׼
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HMC5883_I2C_CalibrateMag(HMC5883_HandleType* HMC5883x)
{
	int x=0, y=0, z=0; //triple axis data
	int xMax=0, xMin=0, yMax=0, yMin=0, zMax=0, zMin=0;
	xMax = xMin = x;
	yMax = yMin = y;
	zMax = zMin = z;
	HMC5883x->msgOffsetX = 0;
	HMC5883x->msgOffsetY = 0;
	HMC5883x->msgOffsetZ = 0;
	//---��ȡֵ
	HMC5883_I2C_ReadRawData(HMC5883x);
	//---׼��У׼
	for (int i = 0; i < 200; i++)
	{
		//---��ȡֵ
		HMC5883_I2C_ReadRawData(HMC5883x);
		if (x > xMax)
		{
			xMax = x;
		}
		if (x < xMin)
		{
			xMin = x;
		}
		if (y > yMax)
		{
			yMax = y;
		}
		if (y < yMin)
		{
			yMin = y;
		}
		if (z > zMax)
		{
			zMax = z;
		}
		if (z < zMin)
		{
			zMin = z;
		}
		HMC5883x->pMsgDelayms(100);
	}
	//---����X��ƫ��
	if (ABS(xMax - xMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetX = (xMax + xMin) / 2;
	}
	//---����Y��ƫ��
	if (ABS(yMax - yMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetY = (yMax + yMin) / 2;
	}
	//---����Z��ƫ��
	if (ABS(zMax - zMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetZ = (zMax + zMin) / 2;
	}
}