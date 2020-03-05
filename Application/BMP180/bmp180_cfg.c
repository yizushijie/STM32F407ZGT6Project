#include "bmp180_cfg.h"

//===ȫ�ֱ�������
BMP180_HandleType		g_Bmp180Device0 = { 0 };
pBMP180_HandleType		pBmp180Device0 = &g_Bmp180Device0;


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device0_Init(BMP180_HandleType* BMP180x)
{
	BMP180x->msgI2C.pMsgI2Cx = NULL;
	BMP180x->msgI2C.msgSCL.msgPort = GPIOB;
	BMP180x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	BMP180x->msgI2C.msgSDA.msgPort = GPIOB;
	BMP180x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	BMP180x->msgI2C.msgHwMode = 0;
	BMP180x->msgI2C.msgPluseWidth = 0;
	BMP180x->msgI2C.pMsgDelayus = NULL;
	BMP180x->msgI2C.msgAddr = BMP180_WADDR;
	BMP180x->msgI2C.msgClockSpeed = 100000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device1_Init(BMP180_HandleType* BMP180x)
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
UINT8_T BMP180_I2C_Device2_Init(BMP180_HandleType* BMP180x)
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
UINT8_T BMP180_I2C_Init(BMP180_HandleType* BMP180x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_ONE))
	{
		BMP180_I2C_Device0_Init(BMP180x);
	}
	else if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_TWO))
	{
		BMP180_I2C_Device1_Init(BMP180x);
	}
	else if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_THREE))
	{
		BMP180_I2C_Device2_Init(BMP180x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(BMP180x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(BMP180x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---ms��ʱ����
	BMP180x->pMsgDelayms = ((pFuncDelayms != NULL) ? pFuncDelayms : DelayTask_ms);
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
UINT8_T BMP180_I2C_DeInit(BMP180_HandleType* BMP180x)
{
	return I2CTask_Master_DeInit(&(BMP180x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ֽ�дд�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_SWI2C_WriteSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_HWI2C_WriteSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(BMP180x->msgI2C));
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_WriteSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T val)
{
	if (BMP180x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(BMP180x->msgI2C));
		return  BMP180_HWI2C_WriteSingle(BMP180x, addr, val);
	}
	else
	{
		return  BMP180_SWI2C_WriteSingle(BMP180x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_SWI2C_ReadSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT16_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��ȡ��λ����
	readTemp = I2CTask_MSW_ReadByte(&(BMP180x->msgI2C));
	//---����Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(BMP180x->msgI2C), 0);
	readTemp <<= 8;
	//---��ȡ��λ����
	readTemp |= I2CTask_MSW_ReadByte(&(BMP180x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(BMP180x->msgI2C), 1);
	*pVal = readTemp;
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_HWI2C_ReadSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT16_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(BMP180x->msgI2C), 0);
	//---��ȡ��λ����
	readTemp = I2CTask_MHW_PollMode_ReadByte(&(BMP180x->msgI2C));
	readTemp <<= 8;
	//---������Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(BMP180x->msgI2C), 1);
	//---��ȡ��λ����
	readTemp |= I2CTask_MHW_PollMode_ReadByte(&(BMP180x->msgI2C));
	*pVal = readTemp;
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT16_T* pVal)
{
	if (BMP180x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(BMP180x->msgI2C));
		return  BMP180_HWI2C_ReadSingle(BMP180x, addr, pVal);
	}
	else
	{
		return  BMP180_SWI2C_ReadSingle(BMP180x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_SWI2C_ReadBulk(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	//UINT8_T readTemp[6] = { 0 };
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 0);
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
		pVal[i] = I2CTask_MSW_ReadByte(&(BMP180x->msgI2C));
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(BMP180x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_HWI2C_ReadBulk(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(BMP180x->msgI2C), (i == (length-1))?1:0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(BMP180x->msgI2C));
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadBulk(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (BMP180x->msgI2C.msgHwMode == 1)
	{
		return BMP180_HWI2C_ReadBulk(BMP180x, addr, pVal, length);
	}
	else
	{
		return BMP180_SWI2C_ReadBulk(BMP180x, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadChipId(BMP180_HandleType* BMP180x, UINT8_T* pChipID)
{
	UINT8_T _return = OK_0;
	UINT16_T tempID = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_CHIP_ID, &tempID);
	*pChipID = (UINT8_T)(tempID >> 8);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadDefaultTemp(BMP180_HandleType* BMP180x)
{
	UINT8_T _return = OK_0;
	UINT16_T tempID = 0;
	_return = BMP180_I2C_WriteSingle(BMP180x, BMP180_REG_ADDR_CTRL_MEAS, 0x2E);
	BMP180x->pMsgDelayms(5);
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_OUT_MSB,&tempID);
	BMP180x->msgDefaultTemp=tempID;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadDefaultGasPress(BMP180_HandleType* BMP180x)
{
	UINT8_T _return = OK_0;
	UINT16_T tempID = 0;
	_return = BMP180_I2C_WriteSingle(BMP180x, BMP180_REG_ADDR_CTRL_MEAS, 0x34|(BMP180_OSS<<6));
	#if (BMP180_OSS==1)
		BMP180x->msgDelayms(8);
	#elif  (BMP180_OSS==2)
		BMP180x->msgDelayms(14);
	#elif  (BMP180_OSS==3)
		BMP180x->msgDelayms(26);
	#else
		BMP180x->pMsgDelayms(5);
	#endif
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_OUT_MSB,&tempID);
	BMP180x->msgDefaultGasPress=tempID;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�¶ȣ���ȡ����ѹ�����θ߶�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadTempGasPressAltitude(BMP180_HandleType* BMP180x)
{
	BMP180_I2C_ReadDefaultTemp(BMP180x);
	BMP180_I2C_ReadDefaultGasPress(BMP180x);

	BMP180x->msgParam.msgX1 = ((BMP180x->msgDefaultTemp - BMP180x->msgParam.msgAC6) * BMP180x->msgParam.msgAC5) >> 15;
	BMP180x->msgParam.msgX2 = (((long)BMP180x->msgParam.msgMC) << 11) / (BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgMD);
	BMP180x->msgParam.msgB5 = BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2;
	//---�����¶�
	BMP180x->msgTemp = (BMP180x->msgParam.msgB5 + 8) >> 4;

	BMP180x->msgParam.msgB6 = BMP180x->msgParam.msgB5 - 4000;
	BMP180x->msgParam.msgX1 = ((long)BMP180x->msgParam.msgB2 * ((BMP180x->msgParam.msgB6 * BMP180x->msgParam.msgB6) >> 12)) >> 11;
	BMP180x->msgParam.msgX2 = ((long)BMP180x->msgParam.msgAC2) * BMP180x->msgParam.msgB6 >> 11;
	BMP180x->msgParam.msgX3 = BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2;

	BMP180x->msgParam.msgB3 = (((((long)BMP180x->msgParam.msgAC1) * 4 + BMP180x->msgParam.msgX3)<<(BMP180_OSS) )+ 2) / 4;
	BMP180x->msgParam.msgX1 = (((long)BMP180x->msgParam.msgAC3) * BMP180x->msgParam.msgB6) >> 13;
	BMP180x->msgParam.msgX2 = (((long)BMP180x->msgParam.msgB1) * ((BMP180x->msgParam.msgB6 * BMP180x->msgParam.msgB6) >> 12)) >> 16;
	BMP180x->msgParam.msgX3 = ((BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2) + 2) >> 2;
	BMP180x->msgParam.msgB4 = ((long)BMP180x->msgParam.msgAC4) * (unsigned long)(BMP180x->msgParam.msgX3 + 32768) >> 15;
	BMP180x->msgParam.msgB7 = ((unsigned long)BMP180x->msgDefaultGasPress - BMP180x->msgParam.msgB3) * (50000>> (BMP180_OSS));

	if (BMP180x->msgParam.msgB7 < 0x80000000)
	{
		BMP180x->msgGasPress = (BMP180x->msgParam.msgB7 * 2) / BMP180x->msgParam.msgB4;
	}
	else
	{
		BMP180x->msgGasPress = (BMP180x->msgParam.msgB7 / BMP180x->msgParam.msgB4) * 2;
	}

	BMP180x->msgParam.msgX1 = (BMP180x->msgGasPress >> 8)* (BMP180x->msgGasPress >> 8);
	BMP180x->msgParam.msgX1 = (((long)BMP180x->msgParam.msgX1) * 3038) >> 16;
	BMP180x->msgParam.msgX2 = (-7357 * BMP180x->msgGasPress) >> 16;
	//---�������ѹ
	BMP180x->msgGasPress = BMP180x->msgGasPress + ((BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2 + 3791) >> 4);
	//---���㺣��
	BMP180x->msgAltitude = 44330 * (1 - pow(((BMP180x->msgGasPress) / 101325.0), (1.0 / 5.255)));
	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Config(BMP180_HandleType* BMP180x)
{
	UINT16_T tempReg = 0;
	UINT8_T _return = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC1_H, &tempReg);
	BMP180x->msgParam.msgAC1 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC2_H, &tempReg);
	BMP180x->msgParam.msgAC2 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC3_H, &tempReg);
	BMP180x->msgParam.msgAC3 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC4_H, &tempReg);
	BMP180x->msgParam.msgAC4 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC5_H, &tempReg);
	BMP180x->msgParam.msgAC5 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC6_H, &tempReg);
	BMP180x->msgParam.msgAC6 = tempReg;
	tempReg = 0;

	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_B1_H, &tempReg);
	BMP180x->msgParam.msgB1 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_B2_H, &tempReg);
	BMP180x->msgParam.msgB2 = tempReg;
	tempReg = 0;

	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_MB_H, &tempReg);
	BMP180x->msgParam.msgMB = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_MC_H, &tempReg);
	BMP180x->msgParam.msgMC = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_MD_H, &tempReg);
	BMP180x->msgParam.msgMD = tempReg;
	tempReg = 0;
	
	return _return;
}