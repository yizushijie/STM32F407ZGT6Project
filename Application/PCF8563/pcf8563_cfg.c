#include "pcf8563_cfg.h"

//===�����Ķ���
PCF8563_HandlerType g_Pcf8563Device0 = { 0 };
pPCF8563_HandlerType pPcf8563Device0 = &g_Pcf8563Device0;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Init(PCF8563_HandlerType *PCF8563x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---ָ���豸�ĳ�ʼ��
	if ((PCF8563x != NULL) && (PCF8563x == PCF8563_TASK_ONE))
	{
		PCF8563_I2C_Device0_Init(PCF8563x);
	}
	else if ((PCF8563x != NULL) && (PCF8563x == PCF8563_TASK_TWO))
	{
		PCF8563_I2C_Device1_Init(PCF8563x);
	}
	else if ((PCF8563x != NULL) && (PCF8563x == PCF8563_TASK_THREE))
	{
		PCF8563_I2C_Device2_Init(PCF8563x);
	}
	else
	{
		return ERROR_1;
	}

	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(PCF8563x->msgI2C));
		PCF8563x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(PCF8563x->msgI2C), pFuncDelayus);
		PCF8563x->msgI2C.msgModelIsHW = 0;
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
UINT8_T PCF8563_I2C_Device0_Init(PCF8563_HandlerType *PCF8563x)
{
	PCF8563x->msgI2C.msgI2Cx = NULL;
	PCF8563x->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	PCF8563x->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	PCF8563x->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	PCF8563x->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	PCF8563x->msgI2C.msgModelIsHW = 0;
	PCF8563x->msgI2C.msgPluseWidth = 0;
	PCF8563x->msgI2C.msgDelayus = NULL;
	PCF8563x->msgI2C.msgAddr = 0xA2;//PCF8563_WRITE_ADDR;
	PCF8563x->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Device1_Init(PCF8563_HandlerType *PCF8563x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Device2_Init(PCF8563_HandlerType *PCF8563x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_DeInit(PCF8563_HandlerType *PCF8563x)
{
	//---ע��I2C�豸
	if (PCF8563x->msgI2C.msgModelIsHW == 1)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(PCF8563x->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_WriteReg(PCF8563_HandlerType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	UINT8_T _return = OK_0;

	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}

	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), reg);

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}

	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), val);

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_HWI2C_WriteReg(PCF8563_HandlerType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�д�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_WriteReg(PCF8563_HandlerType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	if (PCF8563x->msgI2C.msgModelIsHW == 0)
	{
		return PCF8563_SWI2C_WriteReg(PCF8563x, reg, val);
	}
	else
	{
		return PCF8563_HWI2C_WriteReg(PCF8563x, reg, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_ReadReg(PCF8563_HandlerType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;

	//---����д����
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}

	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), reg);

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));

	//---������ȡ����
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(PCF8563x->msgI2C));
		if (i == (length - 1))
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(PCF8563x->msgI2C), _return);
	}
	_return = OK_0;
GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_HWI2C_ReadReg(PCF8563_HandlerType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadReg(PCF8563_HandlerType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	if (PCF8563x->msgI2C.msgModelIsHW == 0)
	{
		return PCF8563_SWI2C_ReadReg(PCF8563x, reg, pVal, length);
	}
	else
	{
		return PCF8563_HWI2C_ReadReg(PCF8563x, reg, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T PCF8563_ClockOut(UINT8_T preVal)
//////��	   �ܣ� PCF8563���ʱ�ӣ������Ƶ
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ClockOut(PCF8563_HandlerType *PCF8563x, UINT8_T preVal)
{
	UINT8_T _return = OK_0;
	UINT8_T temp = 0;

	//---д�Ĵ���
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_CLKOUT, (preVal | 0x80));
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}

	//---��ȡ�Ĵ���
	_return = PCF8563_I2C_ReadReg(PCF8563x, PCF8563_REG_CLKOUT, &temp, 1);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}

	//---���ݵ�У��
	if ((temp & 0x7F) != preVal)
	{
		_return = ERROR_1;
	}
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadRTC(PCF8563_HandlerType *PCF8563x)
{
	UINT8_T _return = OK_0;
	UINT8_T temp[7];

	//---��ȡʱ��
	_return = PCF8563_I2C_ReadReg(PCF8563x, PCF8563_REG_SECOND, temp, 7);

	//---��������
	if (_return == OK_0)
	{
		//---����ȡ��������䵽������
		PCF8563x->msgRTC.second = (temp[0] & 0x7F);
		PCF8563x->msgRTC.minute = (temp[1] & 0x7F);
		PCF8563x->msgRTC.hour = (temp[2] & 0x3F);
		PCF8563x->msgRTC.day = (temp[3] & 0x3F);
		PCF8563x->msgRTC.week = (temp[4] & 0x07);
		PCF8563x->msgRTC.month = (temp[5] & 0x1F);

		//---���
		PCF8563x->msgRTC.year = temp[6];

		//---����
		if (temp[5] & 0x80)
		{
			PCF8563x->msgRTC.century = 0x19;
		}
		else
		{
			PCF8563x->msgRTC.century = 0x20;
		}
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
UINT8_T PCF8563_I2C_WriteRTC(PCF8563_HandlerType *PCF8563x, RTC_HandlerType rtc)
{
	UINT8_T _return = OK_0;

	//---�ж����������ǲ���BCD��
	if ((rtc.century != 0x19) || (rtc.century != 0x20))
	{
		//===��������λBCD��ʽ
		rtc.second = DecToBcd(rtc.second);
		rtc.minute = DecToBcd(rtc.minute);
		rtc.hour = DecToBcd(rtc.hour);
		rtc.day = DecToBcd(rtc.day);
		rtc.week = DecToBcd(rtc.week);
		rtc.month = DecToBcd(rtc.month);
		rtc.year = DecToBcd(rtc.year);
		rtc.century = DecToBcd(rtc.century);
	}

	//---���Ͳ����Ĵ���
	if (rtc.century == 0x20)
	{
		rtc.month &= 0x3F;
	}
	else
	{
		rtc.month |= 0x80;
	}

	//---д��
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_SECOND, rtc.second);
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}

	//---д��
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_MINUTE, rtc.minute);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}

	//---дʱ
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_HOURS, rtc.hour);
	if (_return != OK_0)
	{
		_return = ERROR_4;
		goto GoToExit;
	}

	//---д��
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_DAY, rtc.day);
	if (_return != OK_0)
	{
		_return = ERROR_5;
		goto GoToExit;
	}

	//---д����
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_WEEK, rtc.week);
	if (_return != OK_0)
	{
		_return = ERROR_6;
		goto GoToExit;
	}

	//---д��
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_MONTH, rtc.month);
	if (_return != OK_0)
	{
		_return = ERROR_7;
		goto GoToExit;
	}

	//---д��
	_return = PCF8563_I2C_WriteReg(PCF8563x, PCF8563_REG_YEAR, rtc.year);
GoToExit:
	return _return;
}