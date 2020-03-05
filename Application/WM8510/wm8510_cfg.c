#include "wm8510_cfg.h"

//===��������
WM8510_HandleType  g_Wm8510Device0 = { 0 };
pWM8510_HandleType pWm8510Device0 = &g_Wm8510Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void WM8510_I2C_ParamsInit(WM8510_HandleType *WM8510x)
{
	WM8510x->msgMclkDIV = 1;
	WM8510x->msgBclkDIV = 1;
	WM8510x->msgPreDIV = 0;
	WM8510x->msgPllN = 0;

	WM8510x->msgR0[0] = 0x00;
	WM8510x->msgR0[1] = 0x00;

	WM8510x->msgR1[0] = 0x02;
	WM8510x->msgR1[1] = 0x23;

	WM8510x->msgNowR6[0] = 0x0D;
	WM8510x->msgNowR6[1] = 0x41;
	WM8510x->msgLastR6[0] = 0x00;
	WM8510x->msgLastR6[1] = 0x00;

	WM8510x->msgNowR36[0] = 0x00;

	WM8510x->msgNowR36[1] = 0x00;
	WM8510x->msgLastR36[0] = 0x00;
	WM8510x->msgLastR36[1] = 0x00;

	WM8510x->msgNowR37[0] = 0x00;
	WM8510x->msgNowR37[1] = 0x00;
	WM8510x->msgLastR37[0] = 0x00;
	WM8510x->msgLastR37[1] = 0x00;

	WM8510x->msgNowR38[0] = 0x00;
	WM8510x->msgNowR38[1] = 0x00;
	WM8510x->msgLastR38[0] = 0x00;
	WM8510x->msgLastR38[1] = 0x00;

	WM8510x->msgNowR39[0] = 0x00;
	WM8510x->msgNowR39[1] = 0x00;
	WM8510x->msgLastR39[0] = 0x00;
	WM8510x->msgLastR39[1] = 0x00;

#ifdef USE_WM8510_RESET
	WM8510x->msgFreqChangeCount = 0;
#endif

	WM8510x->mssgFreqAdd = 0;
	WM8510x->msgPllK = 0;
	WM8510x->magPllFreq = WM8510_MCLK_HZ;
	WM8510x->msgRefOSC = WM8510_MCLK_HZ;
	WM8510x->msgFreqHz = 0;
	WM8510x->msgFreqKHz = 0;
	WM8510x->msgPllRate = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_Device0_Init(WM8510_HandleType *WM8510x)
{
	WM8510x->msgI2C.pMsgI2Cx = NULL;
	#ifdef WM8510_USE_HV_RESET
		WM8510x->msgI2C.msgSCL.msgPort = GPIOB;
		WM8510x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
		WM8510x->msgI2C.msgSDA.msgPort = GPIOB;
		WM8510x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	#else
		WM8510x->msgI2C.msgSCL.msgPort = GPIOB;
		WM8510x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_8;
		WM8510x->msgI2C.msgSDA.msgPort = GPIOB;
		WM8510x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_9;
	#endif
	WM8510x->msgI2C.msgHwMode = 0;
	WM8510x->msgI2C.msgPluseWidth = 2;
	WM8510x->msgI2C.pMsgDelayus = NULL;
	WM8510x->msgI2C.msgAddr = WM8510_WADDR;
	WM8510x->msgI2C.msgClockSpeed = 0;
	#ifdef WM8510_USE_lEVEL_SHIFT
		#ifdef WM8510_USE_HV_RESET
			WM8510x->msgOE.msgPort=GPIOB;
			WM8510x->msgOE.msgBit=LL_GPIO_PIN_5;
		#else
			WM8510x->msgOE.msgPort = GPIOB;
			WM8510x->msgOE.msgBit = LL_GPIO_PIN_4;
		#endif
		//---GPIO�Ľṹ��
		LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;												//---GPIO���ٶ�---�����豸
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
	#endif
		//---OE---���Ϊ��
		GPIO_InitStruct.Pin = WM8510x->msgOE.msgBit;
		LL_GPIO_Init(WM8510x->msgOE.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(WM8510x->msgOE.msgPort,WM8510x->msgOE.msgBit);
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
UINT8_T WM8510_I2C_Device1_Init(WM8510_HandleType *WM8510x)
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
UINT8_T WM8510_I2C_Device2_Init(WM8510_HandleType *WM8510x)
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
UINT8_T WM8510_I2C_Init(WM8510_HandleType *WM8510x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	WM8510_I2C_ParamsInit(WM8510x);
	if ((WM8510x != NULL) && (WM8510x == WM8510_TASK_ONE))
	{
		WM8510_I2C_Device0_Init(WM8510x);
	}
	else if ((WM8510x != NULL) && (WM8510x == WM8510_TASK_TWO))
	{
		WM8510_I2C_Device1_Init(WM8510x);
	}
	else if ((WM8510x != NULL) && (WM8510x == WM8510_TASK_THREE))
	{
		WM8510_I2C_Device2_Init(WM8510x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(WM8510x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(WM8510x->msgI2C), pFuncDelayus, pFuncTimerTick));
	_return = WM8510_I2C_START(WM8510x);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� 0---WM8510��ʼ���ɹ���1---��ʼ��ʧ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_START(WM8510_HandleType *WM8510x)
{
	UINT8_T _return = OK_0;
	//---��������
	WM8510_I2C_SendCMD(WM8510x, WM8510x->msgR0);
	//---����R0�Ĵ���
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgR0);
	if (_return != 0)
	{
		goto GoToExit;
	}
	//---����R0�Ĵ���
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgR1);
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_DeInit(WM8510_HandleType *WM8510x)
{
#ifdef WM8510_USE_lEVEL_SHIFT
	GPIO_OUT_1(WM8510x->msgOE.msgPort, WM8510x->msgOE.msgBit);
#endif
	//---ע��I2C�豸
	return I2CTask_Master_DeInit(&(WM8510x->msgI2C));

}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_SWI2C_WriteReg(WM8510_HandleType *WM8510x, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������д����
	_return = I2CTask_MSW_START(&(WM8510x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	for (i = 0; i < length; i++)
	{
		//---��������
		I2CTask_MSW_SendByte(&(WM8510x->msgI2C), pVal[i]);
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(WM8510x->msgI2C));
		//---�ж�Ӧ��
		if (_return)
		{
			_return = ERROR_3 + i;
			goto GoToExit;
		}
	}
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(WM8510x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� Ӳ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_HWI2C_WriteReg(WM8510_HandleType *WM8510x, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(WM8510x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	for (i = 0; i < length; i++)
	{
		//---�������ݣ��ڲ��Ĵ�������
		_return = I2CTask_MHW_PollMode_SendByte(&(WM8510x->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
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
	I2CTask_MHW_PollMode_STOP(&(WM8510x->msgI2C));
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_SendCMD(WM8510_HandleType *WM8510x, UINT8_T *pVal)
{
	if (WM8510x->msgI2C.msgHwMode == 0)
	{
		//---���ģ��I2C
		return WM8510_SWI2C_WriteReg(WM8510x, pVal, 2);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(WM8510x->msgI2C));
		//---Ӳ��I2C
		return WM8510_HWI2C_WriteReg(WM8510x, pVal, 2);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �������Ƶ�ʵĲ���ֵ��ÿ100KHzƫ��10Hz
//////�������:
//////�������:
//////˵		����������1:1.5�ķ�Ƶ��ƫ����10��ʹ��֮��ƫ����15
//////////////////////////////////////////////////////////////////////////////
void WM8510_Calc_FreqAdd(WM8510_HandleType *WM8510x, UINT32_T freq)
{
	//WM8510x->freqAdd = ( freq / 1000 );
	//WM8510x->freqAdd *= 2;
	WM8510x->mssgFreqAdd = 0;//( WM8510x->freqAdd + 50 ) / 100;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void WM8510_Calc_PllRate(WM8510_HandleType *WM8510x, UINT32_T freq)
{
	//---�����У����Ƶ�ʻᷢ���ı䣬��ÿ��ʹ�õ�ʱ����Ҫ���¸�ֵ
	//WM8510x->pllFreq = WM8510_MCLK_HZ;
	//---Ϊ�˼��ݼ��ݾ������޸�Ϊ������
	WM8510x->magPllFreq = WM8510x->msgRefOSC;
	//---����ֵ��ÿ�ι���
	WM8510x->mssgFreqAdd = 0;
	//---���Ƶ��
	if (freq >= WM8510_OUT_MAX_FREQ)
	{
		//---������Ƶ��
		freq = WM8510_OUT_MAX_FREQ;
		//---���ֵ�Ĳ���
		WM8510x->mssgFreqAdd = WM8510_OUT_MAX_FREQ_ADD;
	}
	//---��СƵ��
	else if (freq < WM8510_OUT_MIN_FREQ)
	{
		//---��С���Ƶ��
		freq = WM8510_OUT_MIN_FREQ;
		//---��Сֵ�Ĳ���
		WM8510x->mssgFreqAdd = WM8510_OUT_MIN_FREQ_ADD;
	}
	//---��������֮��
	else
	{
		//---����Ƶ�ʲ���ֵ
		WM8510_Calc_FreqAdd(WM8510x, freq);
	}
	//---�趨�����Ƶ��
	WM8510x->msgFreqHz = freq;
	WM8510x->msgFreqKHz = (WM8510x->msgFreqHz / 1000);
	//---����֮���ʵ��Ƶ��ֵ
	freq += WM8510x->mssgFreqAdd;
	//===�������㣬�����WM8510��ʱ�Ӿ�����12M����Щ������Ҫ���¼���
	if (freq > PDIV0_MDIV1_BDIV1_MIN)				//18000000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_1;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
	}
	//---�����ⲿ�ֻᵼ������Ĳ��ε�ռ�ձȲ�����1:1�����ܻ�Ӱ�����յĲ��Խ��
	//else if (freq > PDIV0_MDIV1D5_BDIV1_MIN)		//12000000
	//{
	//	WM8510x->preDIV = 0;
	//	WM8510x->mclkDIV = MCLK_DIV_1D5;
	//	WM8510x->bclkDIV = BCLK_DIV_1;
	//	freq *= 3;// ����1.5
	//	freq >>= 1;
	//}
	else if (freq > PDIV0_MDIV2_BDIV1_MIN)		//9000000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_2;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
		freq <<= 1;	// ����2
	}
	else if (freq > PDIV0_MDIV3_BDIV1_MIN)		//6000000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_3;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
		freq *= 3;	// ����3
	}
	else if (freq > PDIV0_MDIV4_BDIV1_MIN)		//4500000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_4;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
		freq <<= 2;	// ����4
	}
	else if (freq > PDIV0_MDIV6_BDIV1_MIN)		//3000000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_6;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
		freq *= 6;	// ����6
	}
	else if (freq > PDIV0_MDIV8_BDIV1_MIN)		//2250000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_8;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
		freq <<= 3;	// ����8
	}
	else if (freq > PDIV0_MDIV12_BDIV1_MIN)		//1500000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_12;
		WM8510x->msgBclkDIV = BCLK_DIV_1;
		freq *= 12;	// ����12
	}
	else if (freq > PDIV0_MDIV8_BDIV2_MIN)		//1125000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_8;
		WM8510x->msgBclkDIV = BCLK_DIV_2;
		freq <<= 4;	// ����16
	}
	else if (freq > PDIV0_MDIV12_BDIV2_MIN)		//750000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_12;
		WM8510x->msgBclkDIV = BCLK_DIV_2;
		freq *= 24;	// ����24
	}
	else if (freq > PDIV0_MDIV8_BDIV4_MIN)		//562500
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_8;
		WM8510x->msgBclkDIV = BCLK_DIV_4;
		freq <<= 5;	// ����32
	}
	else if (freq > PDIV0_MDIV12_BDIV4_MIN)		//375000
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_12;
		WM8510x->msgBclkDIV = BCLK_DIV_4;
		freq *= 48;	// ����48
	}
	else if (freq > PDIV0_MDIV8_BDIV8_MIN)		//281250
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_8;
		WM8510x->msgBclkDIV = BCLK_DIV_8;
		freq <<= 6;	// ����64
	}
	else if (freq > PDIV0_MDIV12_BDIV8_MIN)		//187500
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_12;
		WM8510x->msgBclkDIV = BCLK_DIV_8;
		freq *= 96;	// ����96
	}
	else if (freq > PDIV0_MDIV4_BDIV32_MIN)		//140625
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_4;
		WM8510x->msgBclkDIV = BCLK_DIV_32;
		freq <<= 7;	// ����128
	}
	else if (freq > PDIV0_MDIV6_BDIV32_MIN)		//93750
	{
		WM8510x->msgPreDIV = 0;
		WM8510x->msgMclkDIV = MCLK_DIV_6;
		WM8510x->msgBclkDIV = BCLK_DIV_32;
		freq *= 192;	// ����192
	}
	else if (freq > PDIV1_MDIV8_BDIV16_MIN)		//70313
	{
		WM8510x->msgPreDIV = 1;
		WM8510x->msgMclkDIV = MCLK_DIV_8;
		WM8510x->msgBclkDIV = BCLK_DIV_16;
		freq <<= 7;	// ����128
		WM8510x->magPllFreq >>= 1;
	}
	else if (freq > PDIV1_MDIV12_BDIV16_MIN)	//46875
	{
		WM8510x->msgPreDIV = 1;
		WM8510x->msgMclkDIV = MCLK_DIV_12;
		WM8510x->msgBclkDIV = BCLK_DIV_16;
		freq *= 192;	// ����192
		WM8510x->magPllFreq >>= 1;
	}
	else if (freq > PDIV1_MDIV8_BDIV32_MIN)		//35156
	{
		WM8510x->msgPreDIV = 1;
		WM8510x->msgMclkDIV = MCLK_DIV_8;
		WM8510x->msgBclkDIV = BCLK_DIV_32;
		freq <<= 8;	// ����256
		WM8510x->magPllFreq >>= 1;
	}
	else
	{
		WM8510x->msgPreDIV = 1;
		WM8510x->msgMclkDIV = MCLK_DIV_12;
		WM8510x->msgBclkDIV = BCLK_DIV_32;
		freq *= 384;	// ����384
		WM8510x->magPllFreq >>= 1;
	}
	freq <<= 2;	// ����4
	//---���������ı�ֵ(5��16֮��)
	WM8510x->msgPllRate = (float)freq / WM8510x->magPllFreq;
	//---ȡ����
	WM8510x->msgPllN = (UINT8_T)WM8510x->msgPllRate;
	//---ȡ��Kֵ
	WM8510x->msgPllK = (UINT32_T)((WM8510x->msgPllRate - WM8510x->msgPllN) * (float)0xFFFFFF);
	//===WM8510�����ݸ�ʽ�Ǹ�λ��ǰ����λ�ں�
	//---����ģʽ���Ƿ�ƵPLL�����ֵ
	WM8510x->msgNowR6[0] = (6 << 1) | 0x01;
	WM8510x->msgNowR6[1] = (UINT8_T)WM8510x->msgMclkDIV << 5;
	WM8510x->msgNowR6[1] |= (UINT8_T)WM8510x->msgBclkDIV << 2;
	//---BCLK���ʱ��
	WM8510x->msgNowR6[1] |= 0x01;
	WM8510x->msgNowR36[0] = (36 << 1);
	WM8510x->msgNowR36[1] = (WM8510x->msgPreDIV == 0) ? 0 : (1 << 4);
	WM8510x->msgNowR36[1] |= WM8510x->msgPllN;
	WM8510x->msgNowR37[0] = (37 << 1);
	WM8510x->msgNowR37[1] = (UINT8_T)((WM8510x->msgPllK & 0xFC0000) >> 18);
	WM8510x->msgNowR38[0] = (UINT8_T)((38 << 1) | ((WM8510x->msgPllK & (UINT32_T)0x20000) == 0 ? 0 : 1));
	WM8510x->msgNowR38[1] = (UINT8_T)((WM8510x->msgPllK & 0x1FE00) >> 9);
	WM8510x->msgNowR39[0] = (UINT8_T)((39 << 1) | ((WM8510x->msgPllK & (UINT32_T)0x100) == 0 ? 0 : 1));
	WM8510x->msgNowR39[1] = (UINT8_T)(WM8510x->msgPllK & 0xFF);
#ifdef USE_WM8510_RESET
	//---WM8510������仯һ��
	WM8510x->msgFreqChangeCount += 1;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		��������޸�WM8510��ʱ������ᵼ������쳣�����ÿ�ζ�Ҫ��ƼĴ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_SetFreqHz(WM8510_HandleType *WM8510x, UINT32_T freq)
{
	UINT8_T _return = OK_0;
	//---�ж��Ƿ���Ҫ���¼Ĵ�����ֵ
	if (freq != WM8510x->msgFreqHz)
	{
		//---��������Ĵ�����ֵ
		WM8510_Calc_PllRate(WM8510x, freq);
	}
	//---�ж��Ƿ���Ҫ����Ƶ�ʵĸ�λ
#ifdef USE_WM8510_RESET
	if (WM8510x->msgFreqChangeCount >= WM8510_FREQ_CHANGE_MAX)
	{
		//---ִ���豸��λ����
		WM8510_I2C_Reset(WM8510x);
	}
#endif
	//---�жϼĴ����Ƿ����ı䣬���ı��򲻸�������
	if (memcmp(WM8510x->msgNowR6, WM8510x->msgLastR6, 2) != 0)
	{
		WM8510x->msgLastR6[0] = WM8510x->msgNowR6[0];
		WM8510x->msgLastR6[1] = WM8510x->msgNowR6[1];
		_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR6);
		if (_return != OK_0)
		{
			_return = ERROR_1;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->msgNowR36, WM8510x->msgLastR36, 2) != 0)
	{
		WM8510x->msgLastR36[0] = WM8510x->msgNowR36[0];
		WM8510x->msgLastR36[1] = WM8510x->msgNowR36[1];
		_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR36);
		if (_return != OK_0)
		{
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->msgNowR37, WM8510x->msgLastR37, 2) != 0)
	{
		WM8510x->msgLastR37[0] = WM8510x->msgNowR37[0];
		WM8510x->msgLastR37[1] = WM8510x->msgNowR37[1];
		_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR37);
		if (_return != OK_0)
		{
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->msgNowR38, WM8510x->msgLastR38, 2) != 0)
	{
		WM8510x->msgLastR38[0] = WM8510x->msgNowR38[0];
		WM8510x->msgLastR38[1] = WM8510x->msgNowR38[1];
		_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR38);
		if (_return != OK_0)
		{
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---�жϼĴ�����ֵ�Ƿ����ı�
	if (memcmp(WM8510x->msgNowR39, WM8510x->msgLastR39, 2) != 0)
	{
		WM8510x->msgLastR39[0] = WM8510x->msgNowR39[0];
		WM8510x->msgLastR39[1] = WM8510x->msgNowR39[1];
		_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR39);
		if (_return != OK_0)
		{
			_return = ERROR_5;
		}
	}
	#ifdef WM8510_USE_lEVEL_SHIFT
		GPIO_OUT_0(WM8510x->msgOE.msgPort, WM8510x->msgOE.msgBit);
	#endif
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  WM8510_I2C_SetFreqKHz(WM8510_HandleType *WM8510x, float freq)
{
	UINT32_T temp = (UINT32_T)(freq * 1000);
	return WM8510_I2C_SetFreqHz(WM8510x, temp);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  WM8510_I2C_SetFreqMHz(WM8510_HandleType *WM8510x, float freq)
{
	UINT32_T temp = (UINT32_T)(freq * 1000000);
	return WM8510_I2C_SetFreqHz(WM8510x, temp);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ���� ��ȡWM8510Ҫ�����Ƶ��
//////////////////////////////////////////////////////////////////////////////
UINT32_T WM8510_GetFreqHz(WM8510_HandleType *WM8510x)
{
	return WM8510x->msgFreqHz;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ���� ��λWM8510������
//////////////////////////////////////////////////////////////////////////////
void WM8510_I2C_Reset(WM8510_HandleType *WM8510x)
{
	//---�ȴ���ʼ���ɹ�
	while (WM8510_I2C_START(WM8510x) != 0);
	//---�Ĵ���ֵ����Ϊ��
	memset(WM8510x->msgLastR6, 0, 2);
	memset(WM8510x->msgLastR36, 0, 2);
	memset(WM8510x->msgLastR37, 0, 2);
	memset(WM8510x->msgLastR38, 0, 2);
	memset(WM8510x->msgLastR39, 0, 2);
	//---�Ĵ���ֵ����Ϊ��
	memset(WM8510x->msgNowR6, 0, 2);
	memset(WM8510x->msgNowR36, 0, 2);
	memset(WM8510x->msgNowR37, 0, 2);
	memset(WM8510x->msgNowR38, 0, 2);
	memset(WM8510x->msgNowR39, 0, 2);
	//---����ΪĬ��ֵ
	WM8510x->magPllFreq = WM8510x->msgRefOSC;
	//---���Ƶ�ʹ���
	WM8510x->msgFreqHz = 0;
#ifdef WM8510_USE_lEVEL_SHIFT
	GPIO_OUT_1(WM8510x->msgOE.msgPort, WM8510x->msgOE.msgBit);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   �����������������Ƶ���йصļĴ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_SetFreqHzWithAllFreqReg(WM8510_HandleType *WM8510x, UINT32_T freq)
{
	UINT8_T _return = OK_0;
	//---�ж��Ƿ���Ҫ���¼Ĵ�����ֵ
	if (freq != WM8510x->msgFreqHz)
	{
		//---��������Ĵ�����ֵ
		WM8510_Calc_PllRate(WM8510x, freq);
	}
	//---�ж��Ƿ���Ҫ����Ƶ�ʵĸ�λ
#ifdef USE_WM8510_RESET
	if (WM8510x->msgFreqChangeCount >= WM8510_FREQ_CHANGE_MAX)
	{
		//---ִ���豸��λ����
		WM8510_I2C_Reset(WM8510x);
	}
#endif
	//---���üĴ���R6
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR6);
	if (_return != OK_0)
	{
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���üĴ���R36
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR36);
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���üĴ���R37
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR37);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���üĴ���38
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR38);
	if (_return != OK_0)
	{
		_return = ERROR_4;
		goto GoToExit;
	}
	//---���üĴ���R39
	_return = WM8510_I2C_SendCMD(WM8510x, WM8510x->msgNowR39);
	if (_return != OK_0)
	{
		_return = ERROR_5;
	}
#ifdef WM8510_USE_lEVEL_SHIFT
	GPIO_OUT_0(WM8510x->msgOE.msgPort, WM8510x->msgOE.msgBit);
#endif
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� У׼�����Ƶ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_CalibrateFreqKHzOutPut(WM8510_HandleType *WM8510x)
{
	//---����ʱ��У׼����
	TimerTask_CalcFreq_Task(1);
	//---��ȡ��ǰ�����Ƶ�ʣ��������ݵ������������
	UINT32_T freq = (UINT32_T)(TimerTask_GetFreqKHz()+0.5);
	//---ʵ��Ƶ�����趨Ƶ�ʵĶԱ�У��
	if (freq > WM8510x->msgFreqKHz)
	{
		//---�������
		if ((freq - 10) <= WM8510x->msgFreqKHz)
		{
			return OK_0;
		}
	#if defined(USE_MCU_STM32)&&defined(USE_MCU_STM32F1)
		//---F1���ɼ���Ƶ����32M
		else if (freq > 32000)
		{
			return OK_0;
		}
	#endif
		return ERROR_1;
	}
	else
	{
		//---�������
		if ((freq + 10) >= WM8510x->msgFreqKHz)
		{
			return OK_0;
		}
	#if defined(USE_MCU_STM32)&&defined(USE_MCU_STM32F1)
		//---F1���ɼ���Ƶ����32M
		else if (freq > 32000)
		{
			return OK_0;
		}
	#endif
		return ERROR_2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_SetFreqHzWithAllFreqRegAndCalibrateFreqKHzOutPut(WM8510_HandleType *WM8510x, UINT32_T freq)
{
	if (WM8510_I2C_SetFreqHzWithAllFreqReg(WM8510x, freq) == OK_0)
	{
		return WM8510_CalibrateFreqKHzOutPut(WM8510x);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ʹ�ö�ʱ�����ⲿ����ģʽ������WM8510��Դ�������Ƶ�ʵ�У׼��Ĭ��MCU��ʱ����׼ȷ�ģ�
//////�������:
//////�������:
//////˵		�����м�ʹ����һ��������㣬Ŀ���ǽ���Դ�����Ƶ����12M��ϣ�����������Դ��ʾ�����Ĳ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510_I2C_CalibrateClock(WM8510_HandleType *WM8510x)
{
	UINT8_T _return = OK_0;
	UINT32_T outFreqKHz = WM8510_MCLK_KHZ;
	//---����WM8510����ⲿ�ο�ʱ��
	if (WM8510_I2C_SetFreqHzWithAllFreqReg(WM8510x, outFreqKHz * 1000) == OK_0)
	{
		//---����ʱ��У׼����
		TimerTask_CalcFreq_Task(1);
		//---��ȡ��ǰ�����Ƶ��,���ݽ��������������
		UINT32_T freq =(UINT32_T)(TimerTask_GetFreqKHz()-0.5);
		//---ʵ��Ƶ����Ŀ��Ƶ�ʵ���ϣ������Ƶ����WM8510������ο�ʱ��
		if(freq!=0xFFFF)
		{
			//outFreqKHz *= 10;
			//---Ƶ�ʴ�С�ľ������
			UINT32_T freqDelta = ABS_SUB(outFreqKHz, freq);
			//---����������С����
			if(freqDelta==10)
			{
				freqDelta-=2;
			}
			//---12M��Դ���������,ʵ��Ƶ��С��12M
			if (freqDelta < 10)
			{
				WM8510x->msgRefOSC = WM8510_MCLK_HZ - (freqDelta * 50);
			}
			//---ʵ��Ƶ�ʴ���12M
			else
			{
				WM8510x->msgRefOSC = WM8510_MCLK_HZ + ((freqDelta + 5)) * 10;
			}
		}		
		//---��λ�豸
		WM8510_I2C_Reset(WM8510x);
	}
	else
	{
		_return = ERROR_2;
	}
	return _return;
}