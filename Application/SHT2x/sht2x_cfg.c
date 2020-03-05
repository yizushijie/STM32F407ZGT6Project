#include "sht2x_cfg.h"

//===�����Ķ���
SHT2X_HandleType g_Sht2xDevice0 = { 0 };
pSHT2X_HandleType pSht2xDevice0 = &g_Sht2xDevice0;


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_Device0_Init(SHT2X_HandleType* SHT2x)
{
	SHT2x->msgI2C.pMsgI2Cx = NULL;
	SHT2x->msgI2C.msgSCL.msgPort = GPIOB;
	SHT2x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	SHT2x->msgI2C.msgSDA.msgPort = GPIOB;
	SHT2x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	SHT2x->msgI2C.msgHwMode = 0;
	SHT2x->msgI2C.msgPluseWidth = 0;
	SHT2x->msgI2C.pMsgDelayus = NULL;
	SHT2x->msgI2C.msgAddr = SHT2X_WADDR;//0x80;  // SHT2X_WRITE_ADDR;
	SHT2x->msgI2C.msgClockSpeed = 200000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_Device1_Init(SHT2X_HandleType* SHT2x)
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
UINT8_T SHT2X_I2C_Device2_Init(SHT2X_HandleType* SHT2x)
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
UINT8_T SHT2X_I2C_Init(SHT2X_HandleType *SHT2x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((SHT2x != NULL) && (SHT2x == SHT2X_TASK_ONE))
	{
		SHT2X_I2C_Device0_Init(SHT2x);
	}
	else if ((SHT2x != NULL) && (SHT2x == SHT2X_TASK_TWO))
	{
		SHT2X_I2C_Device1_Init(SHT2x);
	}
	else if ((SHT2x != NULL) && (SHT2x == SHT2X_TASK_THREE))
	{
		SHT2X_I2C_Device2_Init(SHT2x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(SHT2x->msgI2C),pFuncDelayus, pFuncTimerTick)):(_return = I2CTask_MSW_Init(&(SHT2x->msgI2C), pFuncDelayus, pFuncTimerTick));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_DeInit(SHT2X_HandleType *SHT2x)
{
	//---ע��I2C�豸
	return I2CTask_Master_DeInit(&(SHT2x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_SWI2C_WriteCmd(SHT2X_HandleType *SHT2x, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), cmd);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_HWI2C_WriteCmd(SHT2X_HandleType *SHT2x, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), cmd, 1);
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_WriteCmd(SHT2X_HandleType *SHT2x, UINT8_T cmd)
{
	if (SHT2x->msgI2C.msgHwMode == 0)
	{
		return SHT2X_SWI2C_WriteCmd(SHT2x, cmd);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(SHT2x->msgI2C));
		//---Ӳ��I2C
		return SHT2X_HWI2C_WriteCmd(SHT2x, cmd);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_SoftReset(SHT2X_HandleType *SHT2x)
{
	return SHT2X_I2C_WriteCmd(SHT2x, SHT2X_CMD_SOFT_RESET_DEVICE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_SWI2C_GetSerialNumber(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//====Read from memory location 1
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������---Command for readout on-chip memory
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0xFA);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��������---on-chip memory address
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0x0F);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_5;
		goto GoToExit;
	}
	//---Read SNB��Read SNBCRC
	for (i = 0; i < 8; i++)
	{
		//---��ȡ����
		SHT2x->msgSerialNumber[i] = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
		if (i == 7)
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(SHT2x->msgI2C), _return);
	}
	//===Read from memory location 1
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_6;
		goto GoToExit;
	}
	//---��������---Command for readout on-chip memory
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0xFC);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_7;
		goto GoToExit;
	}
	//---��������---on-chip memory address
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0xC9);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_8;
		goto GoToExit;
	}
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_9;
		goto GoToExit;
	}
	//---Read SNC��Read SNCCRC
	for (i = 0; i < 6; i++)
	{
		//---��ȡ����
		SHT2x->msgSerialNumber[8 + i] = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
		if (i == 5)
		{
			_return = 1;
		}
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(SHT2x->msgI2C), _return);
	}

GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_HWI2C_GetSerialNumber(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//====Read from memory location 1
	//---���������͵�ַ
//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������---Command for readout on-chip memory
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0xFA, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��������---on-chip memory address
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0x0F, 1);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---���������͵�ַ
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_5;
		goto GoToExit;
	}
	//---Read SNB��Read SNBCRC
	for (i = 0; i < 8; i++)
	{
		if (i == (7))
		{
			_return = 1;
		}
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(SHT2x->msgI2C), _return);
		//---��ȡ����
		SHT2x->msgSerialNumber[i] = I2CTask_MHW_PollMode_ReadByte(&(SHT2x->msgI2C));
	}
	//===Read from memory location 1
	//---���������͵�ַ
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_6;
		goto GoToExit;
	}
	//---��������---Command for readout on-chip memory
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0xFC, 0);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_7;
		goto GoToExit;
	}
	//---��������---on-chip memory address
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0xC9, 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_8;
		goto GoToExit;
	}
	//---���������͵�ַ
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_9;
		goto GoToExit;
	}
	//---Read SNC��Read SNCCRC
	for (i = 0; i < 6; i++)
	{
		if (i == (5))
		{
			_return = 1;
		}
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(SHT2x->msgI2C), _return);
		//---��ȡ����
		SHT2x->msgSerialNumber[8 + i] = I2CTask_MHW_PollMode_ReadByte(&(SHT2x->msgI2C));
	}
	_return = OK_0;
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(SHT2x->msgI2C));
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_GetSerialNumber(SHT2X_HandleType *SHT2x)
{
	if (SHT2x->msgI2C.msgHwMode == 0)
	{
		return SHT2X_SWI2C_GetSerialNumber(SHT2x);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(SHT2x->msgI2C));
		//---Ӳ��I2C
		return SHT2X_HWI2C_GetSerialNumber(SHT2x);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadUserReg(SHT2X_HandleType *SHT2x, UINT8_T *pReg)
{
	UINT8_T _return = OK_0;
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�������
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), SHT2X_CMD_USER_READ_REG);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---�����ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---��ȡ����
	*pReg = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_WriteUserReg(SHT2X_HandleType *SHT2x, UINT8_T reg)
{
	UINT8_T _return = OK_0;
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�������
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), SHT2X_CMD_USER_WRITE_REG);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---�����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---д������
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), reg);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadPoll(SHT2X_HandleType *SHT2x, UINT16_T *pVal, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	UINT8_T tempL = 0;
	UINT8_T tempH = 0;
	UINT16_T timeout = 0;
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�����¶Ȳ�������
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), cmd);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---�����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�ȴ���������
	while (1)
	{
		//---���������͵�ַ
		_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
		if (_return == OK_0)
		{
			//---�������ݶ�ȡ�ɹ����˳�whileѭ��
			break;
		}
		timeout++;
		//---��ʱ�ж�
		if (timeout > 5000)
		{
			//---������ʱ����
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	//---��ȡ��λ��
	tempH = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---����Ӧ���ź�
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 0);
	//---��ȡ��λ��
	tempL = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 1);
	temp = tempH;
	temp = (temp << 8) + tempL;
	temp &= 0xFFFC;
	*pVal = temp;

GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadTempPoll(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---��ȡ�¶�ֵ
	_return = SHT2X_I2C_ReadPoll(SHT2x, &temp, SHT2X_CMD_TRIG_TEMP_MEASUREMENT_POLL);
	//---�����¶�ֵ
	INT32_T tempX100 = temp;
	tempX100 *= 17572;
	tempX100 >>= 16;
	SHT2x->msgTemp = (INT16_T)(tempX100 - 4685);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadHumiPoll(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---��ȡʪ��ֵ
	_return = SHT2X_I2C_ReadPoll(SHT2x, &temp, SHT2X_CMD_TRIG_HUMI_MEASUREMENT_POLL);
	//---����ʪ��ֵ
	INT32_T tempX100 = temp;
	tempX100 *= 12500;
	tempX100 >>= 16;
	SHT2x->msgHumiX100 = (INT16_T)(tempX100 - 600);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadHM(SHT2X_HandleType *SHT2x, UINT16_T *pVal, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	UINT8_T tempL = 0;
	UINT8_T tempH = 0;
	UINT16_T timeout = 0;
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�����¶Ȳ�������
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), cmd);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---�����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���������͵�ַ
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---�������ݶ�ȡʧ�ܣ��˳�whileѭ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---�ȴ��ӻ��ͷ�SCL������
	while (GPIO_GET_STATE(SHT2x->msgI2C.msgSCL.msgPort, SHT2x->msgI2C.msgSCL.msgBit) ==
		0)
	{
		timeout++;

		//---��ʱ�ж�
		if (timeout > 5000)
		{
			//---������ʱ���󣬴ӻ����ͷ�SCL������
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---��ȡ��λ��
	tempH = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---����Ӧ���ź�
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 0);
	//---��ȡ��λ��
	tempL = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 1);
	temp = tempH;
	temp = (temp << 8) + tempL;
	temp &= 0xFFFC;
	*pVal = temp;
GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadTempHM(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---��ȡ�¶�ֵ
	_return = SHT2X_I2C_ReadHM(SHT2x, &temp, SHT2X_CMD_TRIG_TEMP_MEASUREMENT_HM);
	//---�����¶�ֵ
	INT32_T tempX100 = temp;
	tempX100 *= 17572;
	tempX100 >>= 16;
	SHT2x->msgTemp = (INT16_T)(tempX100 - 4685);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadHumiHM(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---��ȡʪ��ֵ
	_return = SHT2X_I2C_ReadPoll(SHT2x, &temp, SHT2X_CMD_TRIG_HUMI_MEASUREMENT_HM);
	//---����ʪ��ֵ
	INT32_T tempX100 = temp;
	tempX100 *= 12500;
	tempX100 >>= 16;
	SHT2x->msgHumiX100 = (INT16_T)(tempX100 - 600);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float SHT2X_I2C_GetTemp(SHT2X_HandleType* SHT2x)
{
	float tempVal = SHT2x->msgTemp;
	//---ת���¶ȶ�Ӧʵ�ʵ��¶�ֵ
	tempVal /= 100.0;
	return tempVal;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float SHT2X_I2C_GetHumi(SHT2X_HandleType* SHT2x)
{
	float tempVal = SHT2x->msgHumiX100;
	//---ת���¶ȶ�Ӧʵ�ʵ��¶�ֵ
	tempVal /= 100.0;
	return tempVal;
}
