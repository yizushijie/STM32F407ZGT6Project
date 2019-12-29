#include "dac_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_GPIO_Init(UINT8_T ch)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(GPIOA, 1);
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��----
	//---DAC1---PA4
	//---DAC2---PA5
	if (ch == 3)
	{
		GPIO_InitStruct.Pin = LL_GPIO_PIN_4 | LL_GPIO_PIN_5;				//---��Ӧ��GPIO������
	}
	else if (ch == 2)
	{
		GPIO_InitStruct.Pin =LL_GPIO_PIN_5;									//---��Ӧ��GPIO������
	}
	else
	{
		GPIO_InitStruct.Pin = LL_GPIO_PIN_4;								//---��Ӧ��GPIO������
	}
	
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;								//---����״̬Ϊģ����������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;								//---���ö˿�����ʹ��
	//---GPIO�ĳ�ʼ��
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_Clock(UINT8_T isEnableid)
{
	//---����DACʱ��
	if (isEnableid)
	{
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);
	}
	else
	{
		LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_DAC1);
	}

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC1_Init(UINT8_T isEnableBuffer)
{
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---ʹ���������
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---��ʹ�ò��η���
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---ʹ��DAC���������
	if (isEnableBuffer == 1)
	{
		DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;
	}
	else
	{
		DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;
	}
	//---��ʼ��DAC
	LL_DAC_Init(DAC, LL_DAC_CHANNEL_1, &DAC_InitStruct);
	//---ʹ��DAC
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_1);
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_DAC2_Init(UINT8_T isEnableBuffer)
{
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---ʹ���������
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---��ʹ�ò��η���
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---ʹ��DAC���������
	if (isEnableBuffer == 1)
	{
		DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;
	}
	else
	{
		DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;
	}
	//---��ʼ��DAC
	LL_DAC_Init(DAC, LL_DAC_CHANNEL_2, &DAC_InitStruct);
	//---ʹ��DAC
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, 0);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_Channel_Init(UINT8_T ch, UINT8_T isEnableBuffer)
{
	UINT32_T dacChannale = 0;
	LL_DAC_InitTypeDef DAC_InitStruct = { 0 };
	//---ʹ���������
	DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
	//---��ʹ�ò��η���
	DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
	//---ʹ��DAC���������
	if (isEnableBuffer==1)
	{
		DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_ENABLE;
	}
	else
	{
		DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;
	}
	if (ch==2)
	{
		dacChannale = LL_DAC_CHANNEL_2;
	}
	else
	{
		dacChannale = LL_DAC_CHANNEL_1;
	}
	//---��ʼ��DAC
	LL_DAC_Init(DAC, dacChannale, &DAC_InitStruct);
	//---ʹ��DAC
	LL_DAC_Enable(DAC, dacChannale);
	//---�������������ʽ,�Ҷ��룬12λ����
	LL_DAC_ConvertData12RightAligned(DAC, dacChannale, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������ch=1,��ʼ��DACͨ��1��ch=2����ʼ��DACͨ��2��ch=3����ʼ��DACͨ��1��2
////////////// isEnableBuffer=1,ʹ�ܻ�������isEnableBuffer=0����ʹ�ܻ�����
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_Init(UINT8_T ch, UINT8_T isEnableBuffer)
{
	DAC_GPIO_Init(ch);
	DAC_Clock(1);
	if (ch==3)
	{
		DAC_Channel_Init(1, isEnableBuffer);
		DAC_Channel_Init(2, isEnableBuffer);
	}
	else
	{
		DAC_Channel_Init(ch, isEnableBuffer);
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������: ch=1,��ʼ��DACͨ��1��ch=2����ʼ��DACͨ��2��ch=3����ʼ��DACͨ��1��2
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_ChannelUV(UINT8_T ch,UINT32_T volUV)
{
	UINT32_T vol = 0;
	//---�ж��Ƿ񳬳�����
	if (volUV > DAC_REF_POWER_UV)
	{
		volUV = DAC_REF_POWER_UV;
	}
	//---ͨ������õ�ģ����
	vol = (UINT32_T)(volUV / DAC_BIT_POWER_UV);
	//---�ж��Ƿ�����
	if (vol > 0xFFF)
	{
		vol = 0xFFF;
	}
	if(vol>1000)
	{
		vol-=4;
	}
	//---�������������ʽ,�Ҷ��룬12λ����
	if (ch==3)
	{
		LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
		LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_2, vol);
	}
	else if(ch==2)
	{
		LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
	}
	else
	{
		LL_DAC_ConvertData12RightAligned(DAC, LL_DAC_CHANNEL_1, vol);
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
UINT8_T DAC_ChannelMV(UINT8_T ch, UINT32_T volMV)
{
	return DAC_ChannelUV(ch, (volMV * 1000));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DAC_ChannelV(UINT8_T ch, float volV)
{
	return DAC_ChannelUV(ch, (UINT32_T)(volV * 1000000));
}