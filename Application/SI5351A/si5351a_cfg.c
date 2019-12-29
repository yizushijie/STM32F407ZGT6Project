#include "si5351a_cfg.h"

//===��������
SI5351A_HandlerType			g_Si5351aDevice0={0};
pSI5351A_HandlerType		pSi5351aDevice0=&g_Si5351aDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SI5351A_I2C_ParamsInit(SI5351A_HandlerType* SI5351Ax)
{
	//---��ʼ������
	memset(SI5351Ax->msgClockCTRL,0x4F, SI5351A_CLKOUT_CHANNEL_SIZE);
	//---���ò���
	SI5351Ax->msgIsResetPll=0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_Device0_Init(SI5351A_HandlerType* SI5351Ax)
{
	SI5351Ax->msgI2C.msgI2Cx = NULL;
	SI5351Ax->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	SI5351Ax->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_8;
	SI5351Ax->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	SI5351Ax->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_9;
	SI5351Ax->msgI2C.msgModelIsHW = 0;
	SI5351Ax->msgI2C.msgPluseWidth = 1;
	SI5351Ax->msgI2C.msgDelayus = NULL;
	SI5351Ax->msgI2C.msgAddr = SI5351A_WADDR;
	SI5351Ax->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_Device1_Init(SI5351A_HandlerType* SI5351Ax)
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
UINT8_T SI5351A_I2C_Device2_Init(SI5351A_HandlerType* SI5351Ax)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� д����ģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SWI2C_WriteSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����������д����
	_return = I2CTask_MSW_START(&(SI5351Ax->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(SI5351Ax->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SI5351Ax->msgI2C));
	//---�ж�Ӧ��
	if (_return)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ͼĴ�������
	I2CTask_MSW_SendByte(&(SI5351Ax->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SI5351Ax->msgI2C));
	//---�ж�Ӧ��
	if (_return)
	{
		_return = ERROR_3 + 1;
		goto GoToExit;
	}	
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SI5351Ax->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� Ӳ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_HWI2C_WriteSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_WriteSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T val)
{
	if (SI5351Ax->msgI2C.msgModelIsHW == 0)
	{
		//---���ģ��I2C
		return SI5351A_SWI2C_WriteSingle(SI5351Ax, addr, val);
	}
	else
	{
		//---Ӳ��I2C
		return SI5351A_HWI2C_WriteSingle(SI5351Ax, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ������ģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SWI2C_ReadSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����д����
	_return = I2CTask_MSW_START(&(SI5351Ax->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(SI5351Ax->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SI5351Ax->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SI5351Ax->msgI2C));
	//---������ȡ����
	_return = I2CTask_MSW_START(&(SI5351Ax->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---��ȡ����
	_return = I2CTask_MSW_ReadByte(&(SI5351Ax->msgI2C));
	//---����Ӧ���ź�
	I2CTask_MSW_SendACK(&(SI5351Ax->msgI2C), 1);
	if (pVal!=NULL)
	{
		*pVal=_return;
	}
	_return = OK_0;
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SI5351Ax->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_HWI2C_ReadSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_ReadSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal)
{
	if (SI5351Ax->msgI2C.msgModelIsHW == 0)
	{
		//---���ģ��I2C
		return SI5351A_SWI2C_ReadSingle(SI5351Ax, addr, pVal);
	}
	else
	{
		//---Ӳ��I2C
		return SI5351A_HWI2C_ReadSingle(SI5351Ax, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дBulkģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SWI2C_WriteBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������д����
	_return = I2CTask_MSW_START(&(SI5351Ax->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���͵�ַ
	I2CTask_MSW_SendByte(&(SI5351Ax->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SI5351Ax->msgI2C));
	//---�ж�Ӧ��
	if (_return)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��������
	for (i = 0; i < length; i++)
	{
		//---��������
		I2CTask_MSW_SendByte(&(SI5351Ax->msgI2C), pVal[i]);
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(SI5351Ax->msgI2C));
		//---�ж�Ӧ��
		if (_return)
		{
			_return = ERROR_4 + i;
			goto GoToExit;
		}
	}
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SI5351Ax->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_HWI2C_WriteBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
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
UINT8_T SI5351A_I2C_WriteBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (SI5351Ax->msgI2C.msgModelIsHW == 0)
	{
		//---���ģ��I2C
		return SI5351A_SWI2C_WriteBulk(SI5351Ax, addr, pVal, length);
	}
	else
	{
		//---Ӳ��I2C
		return SI5351A_HWI2C_WriteBulk(SI5351Ax, addr, pVal,length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��Bulkģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SWI2C_ReadBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	//---����д����
	_return = I2CTask_MSW_START(&(SI5351Ax->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(SI5351Ax->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(SI5351Ax->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SI5351Ax->msgI2C));
	//---������ȡ����
	_return = I2CTask_MSW_START(&(SI5351Ax->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(SI5351Ax->msgI2C));
		if (i == (length - 1))
		{
			_return = 1;
		}
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(SI5351Ax->msgI2C), _return);
	}
	_return = OK_0;
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(SI5351Ax->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_HWI2C_ReadBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
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
UINT8_T SI5351A_I2C_ReadBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (SI5351Ax->msgI2C.msgModelIsHW == 0)
	{
		//---���ģ��I2C
		return SI5351A_SWI2C_ReadBulk(SI5351Ax, addr, pVal, length);
	}
	else
	{
		//---Ӳ��I2C
		return SI5351A_HWI2C_ReadBulk(SI5351Ax, addr, pVal, length);
	}
}



///////////////////////////////////////////////////////////////////////////////
//////fVCO is the PLL output, and must be between 600..900MHz,
//////fVCO = fXTAL * (a + (b / c))
//////fXTAL = the crystal input frequency
//////a = an integer between 15 and 90
//////b = the fractional numerator(0..1, 048, 575)
//////c = the fractional denominator(1..1, 048, 575)
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����pllʱ��
//////�������:	
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_ConfigMSNBReg(SI5351A_HandlerType* SI5351Ax, UINT8_T regMSNAddr, UINT32_T a, UINT32_T b, UINT32_T c)
{
	UINT32_T p1 = 0;
	UINT32_T p2 = 0;
	UINT32_T p3 = 0;

	if (b == 0)
	{
		p1 = (UINT32_T)(128 * a - 512);
		p2 = 0;
		p3 = c;
	}
	else
	{
		p1 = (UINT32_T)(128 * ((float)b / (float)c));
		p2 = (UINT32_T)(128 * b - c * p1);
		p1 = (UINT32_T)(128 * a + p1 - 512);
		p3 = c;
	}

	UINT8_T params[10];
	UINT8_T i = 0;
	UINT8_T temp;

	// Registers 26-27 for PLLA
	temp = ((p3 >> 8) & 0xFF);
	params[i++] = temp;
	temp = (UINT8_T)(p3 & 0xFF);
	params[i++] = temp;

	// Register 28 for PLLA
	temp = (UINT8_T)((p1 >> 16) & 0x03);
	params[i++] = temp;

	// Registers 29-30 for PLLA
	temp = (UINT8_T)((p1 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (UINT8_T)(p1 & 0xFF);
	params[i++] = temp;

	// Register 31 for PLLA
	temp = (UINT8_T)((p3 >> 12) & 0xF0);
	temp += (UINT8_T)((p2 >> 16) & 0x0F);
	params[i++] = temp;

	// Registers 32-33 for PLLA
	temp = (UINT8_T)((p2 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (UINT8_T)(p2 & 0xFF);
	params[i++] = temp;
	//---д������
	return SI5351A_I2C_WriteBulk(SI5351Ax, regMSNAddr, params, i);
}

//////////////////////////////////////////////////////////////////////////////
//////fOUT = fVCO / MSx
//////a + b / c
//////a = The integer value, which must be 4, 6 or 8 in integer mode(MSx_INT = 1)
//////or 8..900 in fractional mode(MSx_INT = 0).
//////b = The fractional numerator(0..1, 048, 575)
//////c = The fractional denominator(1..1, 048, 575)
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_ConfigMSREG(SI5351A_HandlerType* SI5351Ax, UINT8_T regMSAddr, UINT32_T pllDIV, UINT32_T clkoutDIV)
{
	UINT32_T p1 = 0;
	UINT32_T p2 = 0;
	UINT32_T p3 = 0;
	//---a=pllDIV
	//---b=0
	//---c=1
	p1 = (UINT32_T)(128 * pllDIV - 512);
	p2 = 0;
	p3 = 1;
	UINT8_T params[10];
	UINT8_T i = 0;
	UINT8_T temp;

	// Registers 42-43 for CLK0
	temp = (UINT8_T)((p3 >> 8) & 0xFF);
	params[i++] = temp;
	temp = (UINT8_T)(p3 & 0xFF);
	params[i++] = temp;

	// Register 44 for CLK0
	temp = ((UINT8_T)((p1 >> 16) & 0x03) | clkoutDIV);
	params[i++] = temp;

	// Registers 45-46 for CLK0
	temp = (UINT8_T)((p1 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (UINT8_T)(p1 & 0xFF);
	params[i++] = temp;

	// Register 47 for CLK0
	temp = ((UINT8_T)((p3 >> 12) & 0xF0)) | ((UINT8_T)((p2 >> 16) & 0x0F));
	params[i++] = temp;

	// Registers 48-49 for CLK0
	temp = (UINT8_T)((p2 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (UINT8_T)(p2 & 0xFF);
	params[i++] = temp;

	//---д������
	return SI5351A_I2C_WriteBulk(SI5351Ax, regMSAddr, params, i);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ò���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_CalcConfig(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, UINT64_T freq)
{
	UINT64_T pllFreq;
	UINT8_T  clkoutDIV = 0;
	UINT32_T a = 0;
	UINT32_T b = 0;
	UINT32_T c = 0;
	UINT32_T pllDIV = 0;
	//---���ʱ��---8 KHz
	if (freq < 8000ULL)
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_128;
		freq <<= 7;
	}
	//---���ʱ��---8-16 KHz
	else if ((freq >= 8000ULL) && (freq < 16000ULL))
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_64;
		freq <<= 6;
	}
	//---���ʱ��---16-32 KHz
	else if ((freq >= 16000ULL) && (freq < 32000ULL))
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_32;
		freq <<= 5;
	}
	//---���ʱ��---32-64 KHz
	else if ((freq >= 32000ULL) && (freq < 64000ULL))
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_16;
		freq <<= 4;
	}
	//---���ʱ��---64-128 KHz
	else if ((freq >= 64000ULL) && (freq < 128000ULL))
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_8;
		freq <<= 3;
	}
	//---���ʱ��---128-256 KHz
	else if ((freq >= 128000ULL) && (freq < 256000ULL))
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_4;
		freq <<= 2;
	}
	//---���ʱ��---256-512 KHz
	else if ((freq >= 256000ULL) && (freq < 512000ULL))
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_2;
		freq <<= 1;
	}
	else
	{
		clkoutDIV = SI5351A_CLKOUT_DIV_1;
	}
	//---У�����Ƶ������
	if (freq < SI5351A_CLKOUT_MIN_HZ)
	{
		freq = SI5351A_CLKOUT_MIN_HZ;
	}
	//---У�����Ƶ������
	if (freq > SI5351A_CLKOUT_MAX_HZ)
	{
		freq = SI5351A_CLKOUT_MAX_HZ;
	}
	//---���໷Ƶ��:900 mhz���������໷�ķ�Ƶ��Fvco;
	pllDIV = (UINT32_T)(900000000 / freq);
	//---У�����
	if (pllDIV > SI5351A_MS_A_MAX)
	{
		pllDIV = SI5351A_MS_A_MAX;
	}
	if (pllDIV < SI5351A_MS_A_MIN)
	{
		pllDIV = SI5351A_MS_A_MIN;
	}
	//---��֤��Ƶ��ż��
	if ((pllDIV & 0x01) != 0)
	{
		pllDIV--;
	}
	//---���¼���PLL��Ƶ��
	pllFreq = pllDIV * freq;
	a = (UINT32_T)(pllFreq / SI5351A_CLK_HZ);
	b = (UINT32_T)(((pllFreq % SI5351A_CLK_HZ) * 1048575) / SI5351A_CLK_HZ);
	c = 1048575;
	//---У�����
	if (b > SI5351A_PLL_B_MAX)
	{
		b -= 1048575;
		a++;
	}
	//---У�����
	if (a > SI5351A_PLL_A_MAX)
	{
		a = SI5351A_PLL_A_MAX;
	}
	if (a < SI5351A_PLL_A_MIN)
	{
		a = SI5351A_PLL_A_MIN;
	}
	clkChannel=(clkChannel > (SI5351A_CLKOUT_CHANNEL_SIZE - 1)) ? (SI5351A_CLKOUT_CHANNEL_SIZE - 1) : clkChannel;
	//---����PLLA
	SI5351A_I2C_ConfigMSNBReg(SI5351Ax, SI5351A_REG_MSNA_ADDR, a, b, c);
	//---����MS��ͨ��0�����ֵ
	clkoutDIV=SI5351A_I2C_ConfigMSREG(SI5351Ax, SI5351A_REG_MS0_ADDR + clkChannel * 18, pllDIV, clkoutDIV);
	//---У���Ƿ�λPLL
	if (SI5351Ax->msgIsResetPll!=0)
	{
		//---��λPLL
		clkoutDIV= SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_PLL_RST_ADDR, SI5351A_PLL_RST_A);
	}
	//---ʹ��ͨ��CLK0���
	// SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_CLK0_ADDR + clkChannel, SI5351Ax->msgClockCTRL[clkChannel]);
	return clkoutDIV;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_Init(SI5351A_HandlerType* SI5351Ax, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---������ʼ��
	SI5351A_I2C_ParamsInit(SI5351Ax);
	//---ѡ���豸����
	if ((SI5351Ax != NULL) && (SI5351Ax == SI5351A_TASK_ONE))
	{
		SI5351A_I2C_Device0_Init(SI5351Ax);
	}
	else if ((SI5351Ax != NULL) && (SI5351Ax == SI5351A_TASK_TWO))
	{
		SI5351A_I2C_Device1_Init(SI5351Ax);
	}
	else if ((SI5351Ax != NULL) && (SI5351Ax == SI5351A_TASK_THREE))
	{
		SI5351A_I2C_Device2_Init(SI5351Ax);
	}
	else
	{
		return ERROR_1;
	}

	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//_return= I2CTask_MHW_Init(&(WM8510x->msgI2C), pFuncDelay);
		SI5351Ax->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		_return = I2CTask_MSW_Init(&(SI5351Ax->msgI2C), pFuncDelayus);
		SI5351Ax->msgI2C.msgModelIsHW = 0;
	}
	_return = SI5351A_I2C_START(SI5351Ax);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_DeInit(SI5351A_HandlerType* SI5351Ax)
{
	//---ע��I2C�豸
	if (SI5351Ax->msgI2C.msgModelIsHW == 1)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(SI5351Ax->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_I2C_START(SI5351A_HandlerType* SI5351Ax)
{
	//---��ȡID��Ϣ
	UINT8_T _return = SI5351A_ReadID(SI5351Ax);
	if (_return==OK_0)
	{
		UINT8_T temp[8]={0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00};
		//---��λPLL
		SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_PLL_RST_ADDR, SI5351A_PLL_RST_B | SI5351A_PLL_RST_A);
		//---��ͨ������PWRģʽ
		SI5351A_I2C_WriteBulk(SI5351Ax, SI5351A_REG_CLK0_ADDR,temp,3);
		//---������������
		SI5351A_SetClockChannelIDRV(SI5351Ax,0, SI5351A_CLK_IDRV_2mA);
		//---�������㴦��
		memset(temp, 0x00, 8);
		SI5351A_I2C_WriteBulk(SI5351Ax, SI5351A_REG_SSC_EN_ADDR,temp,8);
		SI5351A_I2C_WriteBulk(SI5351Ax, 157, temp, 8);
		//---���üĴ���
		SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_FANOUT_ENABLE_ADDR, 0xC0);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λPLL
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_PLLRST(SI5351A_HandlerType* SI5351Ax, UINT8_T pllIndex)
{
	if (pllIndex == SI5351A_PLL_RST_B)
	{
		return SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_PLL_RST_ADDR, SI5351A_PLL_RST_B);
	}
	else
	{
		return SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_PLL_RST_ADDR, SI5351A_PLL_RST_A);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡID��Ϣ,ʹ��ʱ���ڲ����ص��ݵ�������ΪID��ʾ��Ĭ���ϵ�֮���и���ֵ0B11XXXXXX
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_ReadID(SI5351A_HandlerType* SI5351Ax)
{
	UINT8_T temp=0;
	UINT8_T  _return= SI5351A_I2C_ReadSingle(SI5351Ax, SI5351A_REG_CRYSTAL_LOAD_ADDR, &temp);
	if (_return==OK_0)
	{
		temp>>=6;
		if ((temp&0x03)==0x03)
		{
			_return=OK_0;
		}
		else
		{
			_return=ERROR_2;
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
UINT8_T SI5351A_SetFreqHz(SI5351A_HandlerType* SI5351Ax,UINT8_T clkChannel, UINT64_T freq)
{
	return SI5351A_CalcConfig(SI5351Ax, clkChannel,freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SetFreqKHz(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, float freqKHz)
{
	UINT64_T freq= (UINT64_T)freqKHz*1000;
	return SI5351A_CalcConfig(SI5351Ax, clkChannel, freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SetFreqMHz(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, float freqMHz)
{
	UINT64_T freq = (UINT64_T)freqMHz * 1000000;
	return SI5351A_CalcConfig(SI5351Ax, clkChannel, freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ʱ�����ͨ������������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SI5351A_SetClockChannelIDRV(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, UINT8_T idrv)
{
	clkChannel=((clkChannel>(SI5351A_CLKOUT_CHANNEL_SIZE-1))?(SI5351A_CLKOUT_CHANNEL_SIZE-1):clkChannel);
	SI5351Ax->msgClockCTRL[clkChannel]&=0xFC;
	SI5351Ax->msgClockCTRL[clkChannel]|=idrv;
	return SI5351A_I2C_WriteSingle(SI5351Ax, SI5351A_REG_CLK0_ADDR+clkChannel, SI5351Ax->msgClockCTRL[clkChannel]);
}