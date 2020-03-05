#include "pcf8563_cfg.h"

//===�����Ķ���
PCF8563_HandleType g_Pcf8563Device0 = { 0 };
pPCF8563_HandleType pPcf8563Device0 = &g_Pcf8563Device0;


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Device0_Init(PCF8563_HandleType* PCF8563x)
{
	PCF8563x->msgI2C.pMsgI2Cx = NULL;
	PCF8563x->msgI2C.msgSCL.msgPort = GPIOB;
	PCF8563x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	PCF8563x->msgI2C.msgSDA.msgPort = GPIOB;
	PCF8563x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	PCF8563x->msgI2C.msgHwMode = 0;
	PCF8563x->msgI2C.msgPluseWidth = 0;
	PCF8563x->msgI2C.pMsgDelayus = NULL;
	PCF8563x->msgI2C.msgAddr = 0xA2;//PCF8563_WRITE_ADDR;
	PCF8563x->msgI2C.msgClockSpeed = 200000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Device1_Init(PCF8563_HandleType* PCF8563x)
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
UINT8_T PCF8563_I2C_Device2_Init(PCF8563_HandleType* PCF8563x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Init(PCF8563_HandleType *PCF8563x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
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
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(PCF8563x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(PCF8563x->msgI2C), pFuncDelayus, pFuncTimerTick));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_DeInit(PCF8563_HandleType *PCF8563x)
{
	//---ע��I2C�豸
	return I2CTask_Master_DeInit(&(PCF8563x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_WriteSingle(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T val)
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
	//---�˳����
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
UINT8_T PCF8563_HWI2C_WriteSingle(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), reg, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�д�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_WriteSingle(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	if (PCF8563x->msgI2C.msgHwMode == 0)
	{
		return PCF8563_SWI2C_WriteSingle(PCF8563x, reg, val);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(PCF8563x->msgI2C));
		//---Ӳ��I2C
		return PCF8563_HWI2C_WriteSingle(PCF8563x, reg, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ��I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_ReadSingle(PCF8563_HandleType* PCF8563x, UINT8_T reg, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), reg);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��ȡ����
	*pVal = I2CTask_MSW_ReadByte(&(PCF8563x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(PCF8563x->msgI2C), 1);
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_HWI2C_ReadSingle(PCF8563_HandleType* PCF8563x, UINT8_T reg, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), reg, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(PCF8563x->msgI2C), 1);
	//---��ȡ����
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(PCF8563x->msgI2C));
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�I2C�����ֽڶ��Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadSingle(PCF8563_HandleType* PCF8563x, UINT8_T reg, UINT8_T* pVal)
{
	if (PCF8563x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(PCF8563x->msgI2C));
		return PCF8563_HWI2C_ReadSingle(PCF8563x, reg, pVal);
	}
	else
	{
		return PCF8563_SWI2C_ReadSingle(PCF8563x, reg, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_ReadBulk(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
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
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(PCF8563x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---�˳����
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
UINT8_T PCF8563_HWI2C_ReadBulk(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), reg, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(PCF8563x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(PCF8563x->msgI2C));
	}
	_return = OK_0;
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadBulk(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	if (PCF8563x->msgI2C.msgHwMode == 0)
	{
		return PCF8563_SWI2C_ReadBulk(PCF8563x, reg, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(PCF8563x->msgI2C));
		//---Ӳ��I2C
		return PCF8563_HWI2C_ReadBulk(PCF8563x, reg, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T PCF8563_ClockOut(UINT8_T preVal)
//////��	   �ܣ� PCF8563���ʱ�ӣ������Ƶ
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ClockOut(PCF8563_HandleType *PCF8563x, UINT8_T preVal)
{
	UINT8_T _return = OK_0;
	UINT8_T temp = 0;
	//---д�Ĵ���
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_CLKOUT, (preVal | 0x80));
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��ȡ�Ĵ���
	_return = PCF8563_I2C_ReadSingle(PCF8563x, PCF8563_REG_CLKOUT, &temp);
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
UINT8_T PCF8563_I2C_ReadRTC(PCF8563_HandleType *PCF8563x)
{
	UINT8_T _return = OK_0;
	UINT8_T temp[7];
	//---��ȡʱ��
	_return = PCF8563_I2C_ReadBulk(PCF8563x, PCF8563_REG_SECOND, temp, 7);
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
UINT8_T PCF8563_I2C_WriteRTC(PCF8563_HandleType *PCF8563x, RTC_HandleType rtc)
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
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_SECOND, rtc.second);
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_MINUTE, rtc.minute);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---дʱ
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_HOURS, rtc.hour);
	if (_return != OK_0)
	{
		_return = ERROR_4;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_DAY, rtc.day);
	if (_return != OK_0)
	{
		_return = ERROR_5;
		goto GoToExit;
	}
	//---д����
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_WEEK, rtc.week);
	if (_return != OK_0)
	{
		_return = ERROR_6;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_MONTH, rtc.month);
	if (_return != OK_0)
	{
		_return = ERROR_7;
		goto GoToExit;
	}
	//---д��
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_YEAR, rtc.year);
GoToExit:
	return _return;
}