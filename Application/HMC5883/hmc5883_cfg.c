#include "hmc5883_cfg.h"

//===ȫ�ֱ�������
HMC5883_HandlerType		g_Hmc5883Device0 = { 0 };
pHMC5883_HandlerType	pHmc5883Device0=&g_Hmc5883Device0;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ʼ��
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Init(HMC5883_HandlerType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT8_T isHWI2C)
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
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(HMC5883x->msgI2C));
		//---����ΪӲ��ģʽ
		HMC5883x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(HMC5883x->msgI2C), pFuncDelayus);
		//---����Ϊ�����ģʽ
		HMC5883x->msgI2C.msgModelIsHW = 0;
	}
	HMC5883x->msgDelayms = pFuncDelayms;
	//---���ó�ʼ��
	_return = HMC5883_ConfigInit(HMC5883x);
	//---���ó�ʼ��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Device0_Init(HMC5883_HandlerType* HMC5883x)
{
	HMC5883x->msgI2C.msgI2Cx = NULL;
	HMC5883x->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	HMC5883x->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	HMC5883x->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	HMC5883x->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	HMC5883x->msgI2C.msgModelIsHW = 0;
	HMC5883x->msgI2C.msgPluseWidth = 2;
	HMC5883x->msgI2C.msgDelayus = NULL;
	HMC5883x->msgI2C.msgAddr = 0x3c;
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
UINT8_T HMC5883_I2C_Device1_Init(HMC5883_HandlerType* HMC5883x)
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
UINT8_T HMC5883_I2C_Device2_Init(HMC5883_HandlerType* HMC5883x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ֽ�дд�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_SingleWriteReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T val)
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
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
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
UINT8_T HMC5883_HWI2C_SingleWriteReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T val)
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
UINT8_T HMC5883_I2C_SingleWriteReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	if (HMC5883x->msgI2C.msgModelIsHW == 1)
	{
		return HMC5883_HWI2C_SingleWriteReg(HMC5883x, addr, val);
	}
	else
	{
		return HMC5883_SWI2C_SingleWriteReg(HMC5883x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_SingleReadReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
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
UINT8_T HMC5883_HWI2C_SingleReadReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
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
UINT8_T HMC5883_I2C_SingleReadReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	if (HMC5883x->msgI2C.msgModelIsHW==1)
	{
		return HMC5883_HWI2C_SingleReadReg(HMC5883x, addr, pVal);
	}
	else
	{
		return HMC5883_SWI2C_SingleReadReg(HMC5883x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_BurstReadReg(HMC5883_HandlerType* HMC5883x)
{
	UINT8_T readTemp[6] = { 0 };
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
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), HMC5883_DXMSB_REG);

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

	for (i = 0; i < 6; i++)
	{
		//---��ȡ����
		readTemp[i] = I2CTask_MSW_ReadByte(&(HMC5883x->msgI2C));
		if (i ==5)
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(HMC5883x->msgI2C), _return);
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	//---���ݼ���
	if (_return==OK_0)
	{
		HMC5883x->msgX = readTemp[0];
		HMC5883x->msgX = (HMC5883x->msgX<<8)+readTemp[1];

		HMC5883x->msgZ = readTemp[2];
		HMC5883x->msgZ = (HMC5883x->msgZ << 8) + readTemp[3];

		HMC5883x->msgY = readTemp[4];
		HMC5883x->msgY = (HMC5883x->msgY << 8) + readTemp[5];

		//---����Ƕ�
		HMC5883x->msgAngle = atan2(HMC5883x->msgY-HMC5883x->msgOffsetY, HMC5883x->msgX-HMC5883x->msgOffsetX) * (180 / 3.14159265) + 180; 
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
UINT8_T HMC5883_HWI2C_BurstReadReg(HMC5883_HandlerType* HMC5883x)
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
UINT8_T HMC5883_I2C_BurstReadReg(HMC5883_HandlerType* HMC5883x)
{
	if (HMC5883x->msgI2C.msgModelIsHW == 1)
	{
		return HMC5883_HWI2C_BurstReadReg(HMC5883x);
	}
	else
	{
		return HMC5883_SWI2C_BurstReadReg(HMC5883x);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_ConfigInit(HMC5883_HandlerType* HMC5883x)
{
	return HMC5883_I2C_SingleWriteReg(HMC5883x,0x02, 0x00);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� У׼���㣬��ֵУ׼
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HMC5883_CalibrateMag(HMC5883_HandlerType* HMC5883x)
{
	int x, y, z; //triple axis data
	int xMax, xMin, yMax, yMin, zMax, zMin;
	//---��ȡֵ
	HMC5883_I2C_BurstReadReg(HMC5883x);
	xMax = xMin = x;
	yMax = yMin = y;
	zMax = zMin = z;
	HMC5883x->msgOffsetX = 0;
	HMC5883x->msgOffsetY = 0;
	HMC5883x->msgOffsetZ = 0;
	//---׼��У׼
	for (int i = 0; i < 200; i++)
	{
		//---��ȡֵ
		HMC5883_I2C_BurstReadReg(HMC5883x);
		//get Max and Min
		// this routine will capture the max and min values of the mag X, Y, and Z data while the
		// compass is being rotated 360 degrees through the level plane and the upright plane.
		// i.e. horizontal and vertical circles.
		// This function should be invoked while making continuous measurements on the magnetometers
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
		HMC5883x->msgDelayms(100);
	}
	//---compute offsets,����ƫ��
	if (ABS(xMax - xMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetX = (xMax + xMin) / 2;
	}
	if (ABS(yMax - yMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetY = (yMax + yMin) / 2;
	}
	if (ABS(zMax - zMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetZ = (zMax + zMin) / 2;
	}
}