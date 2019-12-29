#include "rfask_cfg.h"

//===��������
RFASK_HandlerType	g_Rfask = {0};
pRFASK_HandlerType	pRfask = &g_Rfask;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void RFASK_ClkInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(CLKA_CTR_PORT, 1);
	GPIOTask_Clock(CLKB_CTR_PORT, 1);
	GPIOTask_Clock(CLKC_CTR_PORT, 1);
	GPIOTask_Clock(CLKD_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

//---CLKA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = CLKA_CTR_BIT;
	LL_GPIO_Init(CLKA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(CLKA_CTR_PORT, CLKA_CTR_BIT);

	//---CLKB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = CLKB_CTR_BIT;
	LL_GPIO_Init(CLKB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(CLKB_CTR_PORT, CLKB_CTR_BIT);

	//---CLKC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = CLKC_CTR_BIT;
	LL_GPIO_Init(CLKC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(CLKC_CTR_PORT, CLKC_CTR_BIT);

	//---CLKD_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = CLKD_CTR_BIT;
	LL_GPIO_Init(CLKD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(CLKD_CTR_PORT, CLKD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void RFASK_YSELInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(YSEL0A_CTR_PORT, 1);
	GPIOTask_Clock(YSEL1A_CTR_PORT, 1);
	GPIOTask_Clock(YSEL2A_CTR_PORT, 1);
	GPIOTask_Clock(YSEL3A_CTR_PORT, 1);

	GPIOTask_Clock(YSEL0B_CTR_PORT, 1);
	GPIOTask_Clock(YSEL1B_CTR_PORT, 1);
	GPIOTask_Clock(YSEL2B_CTR_PORT, 1);
	GPIOTask_Clock(YSEL3B_CTR_PORT, 1);

	GPIOTask_Clock(YSEL0C_CTR_PORT, 1);
	GPIOTask_Clock(YSEL1C_CTR_PORT, 1);
	GPIOTask_Clock(YSEL2C_CTR_PORT, 1);
	GPIOTask_Clock(YSEL3C_CTR_PORT, 1);

	GPIOTask_Clock(YSEL0D_CTR_PORT, 1);
	GPIOTask_Clock(YSEL1D_CTR_PORT, 1);
	GPIOTask_Clock(YSEL2D_CTR_PORT, 1);
	GPIOTask_Clock(YSEL3D_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

//---YSEL0A_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL0A_CTR_BIT;
	LL_GPIO_Init(YSEL0A_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL0A_CTR_PORT, YSEL0A_CTR_BIT);

	//---YSEL1A_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL1A_CTR_BIT;
	LL_GPIO_Init(YSEL1A_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL1A_CTR_PORT, YSEL1A_CTR_BIT);

	//---YSEL2A_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL2A_CTR_BIT;
	LL_GPIO_Init(YSEL2A_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL2A_CTR_PORT, YSEL2A_CTR_BIT);

	//---YSEL3A_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL3A_CTR_BIT;
	LL_GPIO_Init(YSEL3A_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL3A_CTR_PORT, YSEL3A_CTR_BIT);

	//---YSEL0B_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL0B_CTR_BIT;
	LL_GPIO_Init(YSEL0B_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL0B_CTR_PORT, YSEL0B_CTR_BIT);

	//---YSEL1B_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL1B_CTR_BIT;
	LL_GPIO_Init(YSEL1B_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL1B_CTR_PORT, YSEL1B_CTR_BIT);

	//---YSEL2B_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL2B_CTR_BIT;
	LL_GPIO_Init(YSEL2B_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL2B_CTR_PORT, YSEL2B_CTR_BIT);

	//---YSEL3B_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL3B_CTR_BIT;
	LL_GPIO_Init(YSEL3B_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL3B_CTR_PORT, YSEL3B_CTR_BIT);

	//---YSEL0C_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL0C_CTR_BIT;
	LL_GPIO_Init(YSEL0C_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL0C_CTR_PORT, YSEL0C_CTR_BIT);

	//---YSEL1C_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL1C_CTR_BIT;
	LL_GPIO_Init(YSEL1C_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL1C_CTR_PORT, YSEL1C_CTR_BIT);

	//---YSEL2C_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL2C_CTR_BIT;
	LL_GPIO_Init(YSEL2C_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL2C_CTR_PORT, YSEL2C_CTR_BIT);

	//---YSEL3C_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL3C_CTR_BIT;
	LL_GPIO_Init(YSEL3C_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL3C_CTR_PORT, YSEL3C_CTR_BIT);

	//---YSEL0D_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL0D_CTR_BIT;
	LL_GPIO_Init(YSEL0D_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL0D_CTR_PORT, YSEL0D_CTR_BIT);

	//---YSEL1D_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL1D_CTR_BIT;
	LL_GPIO_Init(YSEL1D_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL1D_CTR_PORT, YSEL1D_CTR_BIT);

	//---YSEL2D_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL2D_CTR_BIT;
	LL_GPIO_Init(YSEL2D_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL2D_CTR_PORT, YSEL2D_CTR_BIT);

	//---YSEL3D_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = YSEL3D_CTR_BIT;
	LL_GPIO_Init(YSEL3D_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(YSEL3D_CTR_PORT, YSEL3D_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void RFASK_StructInit(RFASK_HandlerType *rfask)
{
	//---�豸����
	rfask->msgDeviceType =  SYN590R;//SYN5XXR;                  //1Byte

	//---�����SITE��Ϣ
	memset(rfask->msgActivateSite, 0, FREQ_CURRENT_MAX_SITE);

	//---100���Ŵ�֮��Ĳ�������ֵ
	rfask->msgSampleX100Res = FREQ_CURRENT_SAMPLE_RES;			//2Byte

	//---�Ŵ���
	rfask->msgAmpTimes = FREQ_CURRENT_AMP_TIMES;				//2Byte

	//---100���Ŵ�֮���Ԥ��Ƶ�ʵ�1
	rfask->msgFreqX100MHzYSel1 = FREQ_YSEL1_X100MHZ;			//4Byte

	//---100���Ŵ�֮���Ԥ��Ƶ�ʵ�2
	rfask->msgFreqX100MHzYSel2 = FREQ_YSEL2_X100MHZ;			//4Byte

	//---100���Ŵ�֮���Ԥ��Ƶ�ʵ�3
	rfask->msgFreqX100MHzYSel3 = FREQ_YSEL3_X100MHZ;			//4Byte

	//---100���Ŵ�֮���Ԥ��Ƶ�ʵ�4
	rfask->msgFreqX100MHzYSel4 = FREQ_YSEL4_X100MHZ;			//4Byte

	memset(rfask->msgSitePass, 0, FREQ_CURRENT_MAX_SITE);

	//---��һ����ѹ�µ�Ƶ�ʵ���ɨ��
	rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA = FREQ_CURRENT_HIGH_START_IMAX_X100MA;			//2Byte
	rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA = FREQ_CURRENT_HIGH_START_IMIN_X100MA;			//2Byte
	rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA = FREQ_CURRENT_HIGH_STOP_IMAX_X100MA;				//2Byte
	rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA = FREQ_CURRENT_HIGH_STOP_IMIN_X100MA;				//2Byte
	rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = FREQ_CURRENT_HIGH_FSTART_X100MHZ;					//4Byte
	rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz = FREQ_CURRENT_HIGH_FSTEP_X100MHZ;						//2Byte
	rfask->msgFreqCurrentPointOne.msgFreqPointNum = FREQ_CURRENT_HIGH_FX100MHZ_NUM;							//2Byte
	rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz =  rfask->msgFreqCurrentPointOne.msgFreqPointNum;
	rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz *= rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz;
	rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz += rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz;
	//rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz = rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz + (rfask->msgFreqCurrentPointOne.msgFreqPointNum * rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz);
	

	//---���Ʋ�����Ĵ�С�����ֵ��Ӱ���ϱ���λ����ʱ�����ݻ������Ĵ�С
	if (rfask->msgFreqCurrentPointOne.msgFreqPointNum > FREQ_CURRENT_FREQ_POINT_MAX_NUM)
	{
		rfask->msgFreqCurrentPointOne.msgFreqPointNum = FREQ_CURRENT_FREQ_POINT_MAX_NUM;
	}
	rfask->msgFreqCurrentPointOne.msgFreqCurrentVoltagemV = FREQ_CURRENT_HIGH_POWER_MV;						//2Byte
	rfask->msgFreqCurrentPointOne.msgADCPointNum = FREQ_CURRENT_HIGH_ADC_POINT_NUM;							//2Byte
	rfask->msgFreqCurrentPointOne.msgADCPassMax = FREQ_CURRENT_HIGH_ADC_PASS_MAX;							//2Byte
	rfask->msgFreqCurrentPointOne.msgADCPassMin = FREQ_CURRENT_HIGH_ADC_PASS_MIN;							//2Byte

	//---�ж������ǹ�����
	if (rfask->msgFreqCurrentPointOne.msgADCPointNum > FREQ_CURRENT_HISTORY_MAX_SIZE)
	{
		rfask->msgFreqCurrentPointOne.msgADCPointNum = FREQ_CURRENT_HISTORY_MAX_SIZE;
	}

	//---�ڶ�����ѹ�µ�Ƶ�ʵ���ɨ��
	rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA = FREQ_CURRENT_LOW_START_IMAX_X100MA;			//2Byte
	rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA = FREQ_CURRENT_LOW_START_IMIN_X100MA;			//2Byte
	rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA = FREQ_CURRENT_LOW_STOP_IMAX_X100MA;				//2Byte
	rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA = FREQ_CURRENT_LOW_STOP_IMIN_X100MA;				//2Byte
	rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = FREQ_CURRENT_LOW_FSTART_X100MHZ;					//4Byte
	rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz = FREQ_CURRENT_LOW_FSTEP_X100MHZ;						//2Byte
	rfask->msgFreqCurrentPointTwo.msgFreqPointNum = FREQ_CURRENT_LOW_FX100MHZ_NUM;							//2Byte
	rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz =	rfask->msgFreqCurrentPointTwo.msgFreqPointNum ;
	rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz *=	rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz;
	rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz += rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz;
	//rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz = g_RFASK.msgFreqCurrentPointTwo.msgStartFreqX100MHz + (rfask->msgFreqCurrentPointTwo.msgFreqPointNum * rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz);
	

	//---���Ʋ�����Ĵ�С�����ֵ��Ӱ���ϱ���λ����ʱ�����ݻ������Ĵ�С
	if (rfask->msgFreqCurrentPointTwo.msgFreqPointNum > FREQ_CURRENT_FREQ_POINT_MAX_NUM)
	{
		rfask->msgFreqCurrentPointTwo.msgFreqPointNum = FREQ_CURRENT_FREQ_POINT_MAX_NUM;
	}
	rfask->msgFreqCurrentPointTwo.msgFreqCurrentVoltagemV = FREQ_CURRENT_LOW_POWER_MV;						//2Byte
	rfask->msgFreqCurrentPointTwo.msgADCPointNum = FREQ_CURRENT_LOW_ADC_POINT_NUM;							//2Byte
	rfask->msgFreqCurrentPointTwo.msgADCPassMax = FREQ_CURRENT_LOW_ADC_PASS_MAX;							//2Byte
	rfask->msgFreqCurrentPointTwo.msgADCPassMin = FREQ_CURRENT_LOW_ADC_PASS_MIN;							//2Byte

	//---�ж������ǹ�����
	if (rfask->msgFreqCurrentPointTwo.msgADCPointNum > FREQ_CURRENT_HISTORY_MAX_SIZE)
	{
		rfask->msgFreqCurrentPointTwo.msgADCPointNum = FREQ_CURRENT_HISTORY_MAX_SIZE;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void RFASK_Init(RFASK_HandlerType *rfask)
{
	RFASK_StructInit(rfask);
	RFASK_ClkInit();
	RFASK_YSELInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ���㾧���Ƶ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T RFASK_CalcXTAL(RFASK_HandlerType *rfask, UINT32_T rfX100MHz)
{
	UINT64_T _return = 0;
	switch (rfask->msgDeviceType)
	{
		case SYN4XXR:
			_return = ((860000UL / 315) + 1000000UL);
			_return *= rfX100MHz;
			_return /= 6450;
			break;
		case SYN5XXR:
		case CRUX:
		case SYN590R:
			_return = 12000000UL;
			_return *= rfX100MHz;
			_return /= (3200 * 12 + 110);
			break;
		case F11XT:
			_return = 1000000UL;
			_return *= rfX100MHz;
			_return /= 3200;
			break;
		case CRATER:
		case ARA:
			_return = 1000000UL;
			_return *= rfX100MHz;
			_return /= 6400;
			break;
		default:
			_return = 20000;//20KHz
			break;
	}
	return (UINT32_T)(_return);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���������豸����
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_SetDeviceType(RFASK_HandlerType *rfask, UINT8_T deviceType)
{
	rfask->msgDeviceType = deviceType;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡ�豸����
//////////////////////////////////////////////////////////////////////////////
UINT32_T RFASK_GetDeviceType(RFASK_HandlerType *rfask)
{
	return rfask->msgDeviceType;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡ�����SITE
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASK_ActivateSites(RFASK_HandlerType *rfask, UINT8_T activateSites)
{
	UINT8_T i = 0;
	for (i = 0; i < FREQ_CURRENT_MAX_SITE; i++)
	{
		if ((activateSites & 0x01) != 0)
		{
			rfask->msgActivateSite[i] = 0x01;
		}
		else
		{
			rfask->msgActivateSite[i] = 0x00;
		}

		//---����һλ
		activateSites >>= 1;
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
UINT8_T RFASK_SetFreqCurrentPointCmd(FREQ_CURRENT_HandlerType *rfaskFreqCurrent, UINT8_T cmd)
{
	rfaskFreqCurrent->msgCMD = cmd;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ȫ��Ϊ�ߵ�ʱ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_GetYSELA(void)
{
	UINT8_T _return = 0;

	//---���YSELA
	if (YSEL0A_CTR_STATE == 0)
	{
		_return |= 0x01;
	}
	if (YSEL1A_CTR_STATE == 0)
	{
		_return |= 0x02;
	}
	if (YSEL2A_CTR_STATE == 0)
	{
		_return |= 0x04;
	}
	if (YSEL3A_CTR_STATE == 0)
	{
		_return |= 0x08;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ȫ��Ϊ�ߵ�ʱ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_GetYSELB(void)
{
	UINT8_T _return = 0;

	//---���YSELB
	if (YSEL0B_CTR_STATE == 0)
	{
		_return |= 0x01;
	}
	if (YSEL1B_CTR_STATE == 0)
	{
		_return |= 0x02;
	}
	if (YSEL2B_CTR_STATE == 0)
	{
		_return |= 0x04;
	}
	if (YSEL3B_CTR_STATE == 0)
	{
		_return |= 0x08;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ȫ��Ϊ�ߵ�ʱ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_GetYSELC(void)
{
	UINT8_T _return = 0;

	//---���YSELC
	if (YSEL0C_CTR_STATE == 0)
	{
		_return |= 0x01;
	}
	if (YSEL1C_CTR_STATE == 0)
	{
		_return |= 0x02;
	}
	if (YSEL2C_CTR_STATE == 0)
	{
		_return |= 0x04;
	}
	if (YSEL3C_CTR_STATE == 0)
	{
		_return |= 0x08;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ȫ��Ϊ�ߵ�ʱ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_GetYSELD(void)
{
	UINT8_T _return = 0;

	//---���YSELD
	if (YSEL0D_CTR_STATE == 0)
	{
		_return |= 0x01;
	}
	if (YSEL1D_CTR_STATE == 0)
	{
		_return |= 0x02;
	}
	if (YSEL2D_CTR_STATE == 0)
	{
		_return |= 0x04;
	}
	if (YSEL3D_CTR_STATE == 0)
	{
		_return |= 0x08;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ÿ��SITE��YSELĬ��ֵ���뱣��Ϊ�ߵ�ƽ����ʹSITEʧЧ
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_ScanYSEL(void)
{
	//---��ȡYSELA��ֵ
	UINT8_T _return = RFASK_GetYSELA();

	//---��ȡYSELB��ֵ
	_return |= RFASK_GetYSELB();

	//---��ȡYSELC��ֵ
	_return |= RFASK_GetYSELC();

	//---��ȡYSELD��ֵ
	_return |= RFASK_GetYSELD();

	//---����YSEL���
	_return &= 0x0F;

	//	//---����YSEL��ֵ
	//	if (_return == 0)
	//	{
	//		//---û���յ�YSEL
	//		_return = 0x0F;
	//	}
	//	else if (_return == 0x0F)
	//	{
	//		//---YSELȫ������
	//		_return = 0;
	//	}

		//---�����������
	switch (_return)
	{
		case 1:
			_return = RFASK_TASK_YSEL1;
			break;
		case 2:
			_return = RFASK_TASK_YSEL2;
			break;
		case 3:
			_return = RFASK_TASK_YSEL3;
			break;
		case 4:
			_return = RFASK_TASK_YSEL4;
			break;
		case 5:
			_return = RFASK_TASK_POINT_ONE;
			break;
		case 6:
			_return = RFASK_TASK_POINT_TWO;
			break;
		case 7:
			_return = 7;
			break;
		case 8:
			_return = 8;
			break;
		case 9:
			_return = 9;
			break;
		case 10:
			_return = 10;
			break;
		case 11:
			_return = 11;
			break;
		case 12:
			_return = 12;
			break;
		case 13:
			_return = 13;
			break;
		case 14:
			_return = 14;
			break;
		case 15:
			_return = 15;
			break;
		default:
			_return = 0xFF;
			break;
	}
	return _return;
}