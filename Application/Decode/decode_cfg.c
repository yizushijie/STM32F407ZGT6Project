#include "decode_cfg.h"

//===��ǰ��������ֵ
VLTUINT32_T g_DecodeICPCount[DECODE_SITE_COUNT] = { 0 };
//===����ߵ�����������
VLTUINT32_T g_DecodeHighPulseWidth[DECODE_SITE_COUNT] = { 0 };
//===����͵�����������
VLTUINT32_T g_DecodeLowPulseWidth[DECODE_SITE_COUNT] = { 0 };
//===��¼��ǰ��ͨ����׽ģʽ  1--- �½��� 2---������
VLTUINT8_T g_DecodeICPMode[DECODE_SITE_COUNT] = { 0 };
//===���벽��
VLTUINT8_T g_DecodeNewStep[DECODE_SITE_COUNT] = { 0 };
VLTUINT8_T g_DecodeOldStep[DECODE_SITE_COUNT] = { 0 };
//===��¼��ǰ��ͨ����׽�¼�  1--- ������׽ 2---δ������׽
VLTUINT8_T g_DecodeICPEvent[DECODE_SITE_COUNT] = { 0 };
//===�����SITE��
UINT8_T    g_DecodeActivateSite[DECODE_SITE_COUNT] = { 0 };
//===��¼��ǰ�����ؼ���ֵ
VLTUINT32_T  g_DecodeRiseCount[DECODE_SITE_COUNT] = { 0 };
//===��¼��ǰ�½��ؼ���ֵ
VLTUINT32_T  g_DecodeFallCount[DECODE_SITE_COUNT] = { 0 };
//===��¼��ǰ��ƽ�Ŀ��
VLTUINT32_T  g_DecodeTickCount[DECODE_SITE_COUNT] = { 0 };
//===��¼��ǰ��ƽ�Ŀ��
UINT32_T     g_DecodePulseTick[DECODE_SITE_COUNT] = { 0 };
//===����λ��
UINT16_T     g_DecodeBitIndex[DECODE_SITE_COUNT] = { 0 };
//===���벨��ģʽ��֧������������֡ͣ�ٷ�����PT2262
UINT8_T		 g_DecodeWaveMode[DECODE_SITE_COUNT] = { 0 };
//===֡ͣ��֮��,�ڼ�������֮��ʼ����
UINT16_T	 g_DecodePulseIndex[DECODE_SITE_COUNT] = { 0 };
//===֡�ϸ������������������
UINT8_T		 g_DecodeFrameCount[DECODE_SITE_COUNT] = { 0 };
//===PT2262�Ľ�����
UINT32_T     g_DecodeByteNewVal[DECODE_SITE_COUNT] = { 0 };
UINT32_T     g_DecodeByteOldVal[DECODE_SITE_COUNT] = { 0 };
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeLEDInit(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DECA_LED_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECB_LED_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECC_LED_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECD_LED_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_LED_BIT;
	LL_GPIO_Init(DECA_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_LED_PORT, DECA_LED_BIT);

	//---DECB_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_LED_BIT;
	LL_GPIO_Init(DECB_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_LED_PORT, DECB_LED_BIT);

	//---DECC_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_LED_BIT;
	LL_GPIO_Init(DECC_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_LED_PORT, DECC_LED_BIT);

	//---DECD_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_LED_BIT;
	LL_GPIO_Init(DECD_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_LED_PORT, DECD_LED_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeRSTInit(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DECA_RST_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECB_RST_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECC_RST_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECD_RST_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_RST_BIT;
	LL_GPIO_Init(DECA_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECA_RST_PORT, DECA_RST_BIT);

	//---DECB_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_RST_BIT;
	LL_GPIO_Init(DECB_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECB_RST_PORT, DECB_RST_BIT);

	//---DECC_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_RST_BIT;
	LL_GPIO_Init(DECC_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECC_RST_PORT, DECC_RST_BIT);

	//---DECD_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_RST_BIT;
	LL_GPIO_Init(DECD_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECD_RST_PORT, DECD_RST_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeCHInit(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DECA_CH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECB_CH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECC_CH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECD_CH_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;			//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_CH_BIT;
	LL_GPIO_Init(DECA_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_CH_PORT, DECA_CH_BIT);

	//---DECB_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_CH_BIT;
	LL_GPIO_Init(DECB_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_CH_PORT, DECB_CH_BIT);

	//---DECC_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_CH_BIT;
	LL_GPIO_Init(DECC_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_CH_PORT, DECC_CH_BIT);

	//---DECD_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_CH_BIT;
	LL_GPIO_Init(DECD_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_CH_PORT, DECD_CH_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����ɹ���־λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodePassInit(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DECA_PASS_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECB_PASS_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECC_PASS_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECD_PASS_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_PASS_CTR_BIT;
	LL_GPIO_Init(DECA_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECA_PASS_CTR_PORT, DECA_PASS_CTR_BIT);

	//---DECB_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_PASS_CTR_BIT;
	LL_GPIO_Init(DECB_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECB_PASS_CTR_PORT, DECB_PASS_CTR_BIT);

	//---DECC_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_PASS_CTR_BIT;
	LL_GPIO_Init(DECC_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECC_PASS_CTR_PORT, DECC_PASS_CTR_BIT);

	//---DECD_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_PASS_CTR_BIT;
	LL_GPIO_Init(DECD_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECD_PASS_CTR_PORT, DECD_PASS_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeWaveInit(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DECA_WAVE_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECB_WAVE_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECC_WAVE_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DECD_WAVE_CTR_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---DECA_WAVE_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_WAVE_CTR_BIT;
	LL_GPIO_Init(DECA_WAVE_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_WAVE_CTR_PORT, DECA_WAVE_CTR_BIT);

	//---DECB_WAVE_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_WAVE_CTR_BIT;
	LL_GPIO_Init(DECB_WAVE_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_WAVE_CTR_PORT, DECB_WAVE_CTR_BIT);

	//---DECC_WAVE_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_WAVE_CTR_BIT;
	LL_GPIO_Init(DECC_WAVE_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_WAVE_CTR_PORT, DECC_WAVE_CTR_BIT);

	//---DECD_WAVE_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_WAVE_CTR_BIT;
	LL_GPIO_Init(DECD_WAVE_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_WAVE_CTR_PORT, DECD_WAVE_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����������ʹ�õĶ�ʱ����ʼ��
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeTimerInit(void)
{
	//---ʹ�ܶ�ʱ��ʱ��
	TimerTask_Clock(DECODE_USE_TIM, 1);

	//---��ʱ���Ľṹ��
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };

	//---���벶׽ͨ���ĳ�ʼ��
	LL_TIM_IC_InitTypeDef TIM_ICInitStruct = { 0 };

	//---���ö�ʱ��Ϊȱʡ����
	LL_TIM_DeInit(DECODE_USE_TIM);

	//---�Զ�����ֵ
	TIM_InitStruct.Autoreload = DECODE_TIM_RELOAD;

	//---Ԥ��Ƶ��ֵ---�����������ʱ��Ƶ��---1MHz
	TIM_InitStruct.Prescaler = DECODE_TIM_ARR;//71
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;

	//---�ظ������Ĵ���
	TIM_InitStruct.RepetitionCounter = 0;

	//---��ʼ����ʱ��
	LL_TIM_Init(DECODE_USE_TIM, &TIM_InitStruct);

	//---��ʹ���Զ�����
	LL_TIM_DisableARRPreload(DECODE_USE_TIM);

	//--��ʱ��ʱ��ʹ���ڲ�ʱ��
	LL_TIM_SetClockSource(DECODE_USE_TIM, LL_TIM_CLOCKSOURCE_INTERNAL);

	//---��ģʽѡ��λ
	LL_TIM_SetTriggerOutput(DECODE_USE_TIM, LL_TIM_TRGO_RESET);

	//---��ʹ������ģʽ
	LL_TIM_DisableMasterSlaveMode(DECODE_USE_TIM);

	//---ֱ��ģʽ
	TIM_ICInitStruct.ICActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;

	//---ʱ�Ӳ���Ƶ
	TIM_ICInitStruct.ICPrescaler = LL_TIM_ICPSC_DIV1;

	//---����ģʽ---�����ش���
	TIM_ICInitStruct.ICPolarity = LL_TIM_IC_POLARITY_RISING;

	//---�����˲�---8
	TIM_ICInitStruct.ICFilter = LL_TIM_IC_FILTER_FDIV1; //LL_TIM_IC_FILTER_FDIV1_N8;

	//---�������벶׽ͨ��1
	LL_TIM_IC_Init(DECODE_USE_TIM, LL_TIM_CHANNEL_CH1, &TIM_ICInitStruct);

	//---�������벶׽ͨ��2
	LL_TIM_IC_Init(DECODE_USE_TIM, LL_TIM_CHANNEL_CH2, &TIM_ICInitStruct);

	//---�������벶׽ͨ��3
	LL_TIM_IC_Init(DECODE_USE_TIM, LL_TIM_CHANNEL_CH3, &TIM_ICInitStruct);

	//---�������벶׽ͨ��4
	LL_TIM_IC_Init(DECODE_USE_TIM, LL_TIM_CHANNEL_CH4, &TIM_ICInitStruct);

	//---��ʱ���жϵȼ�
	NVIC_SetPriority(DECODE_USE_TIM_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

	//---ʹ�ܶ�ʱ���ж�
	//NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_EnableIRQ(DECODE_USE_TIM_IRQ);
	
	//---�����־λ
	LL_TIM_ClearFlag(DECODE_USE_TIM);

	//---ʹ�����벶׽ͨ��1���ж�
	LL_TIM_EnableIT_CC1(DECODE_USE_TIM);

	//---ʹ�����벶׽ͨ��2���ж�
	LL_TIM_EnableIT_CC2(DECODE_USE_TIM);

	//---ʹ�����벶׽ͨ��3���ж�
	LL_TIM_EnableIT_CC3(DECODE_USE_TIM);

	//---ʹ�����벶׽ͨ��4���ж�
	LL_TIM_EnableIT_CC4(DECODE_USE_TIM);

	//---ʹ�ܸ����ж�
	//LL_TIM_EnableIT_UPDATE(DECODE_USE_TIM);

	//---ʹ�ܶ�ʱ��
	LL_TIM_EnableCounter(DECODE_USE_TIM);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����������ĳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
void Decode_Init(void)
{
	Decode_DecodeLEDInit();
	Decode_DecodeRSTInit();
	Decode_DecodeCHInit();
	Decode_DecodePassInit();
	Decode_DecodeWaveInit();
	Decode_DecodeTimerInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����������ĳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
void  Decode_ActivateSites(UINT8_T activateSites)
{
	UINT8_T i = 0;
	for (i = 0; i < DECODE_SITE_COUNT; i++)
	{
		if (( activateSites & 0x01 ) != 0)
		{
			g_DecodeActivateSite[i] = 0x01;
		}
		else
		{
			g_DecodeActivateSite[i] = 0x00;
		}

		//---����һλ
		activateSites >>= 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �������е�SITEΪ������״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void  Decode_ClearActivateSites(void)
{
	//---�رս���ָʾ��
	DEC_LED_OFF;

	//---��λ����ʧ��
	DEC_PASS_FAIL;
	memset(g_DecodeActivateSite, 0, DECODE_SITE_COUNT);
	//---�ر�ʵʱ����
	Decode_STOP();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ������е�״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void  Decode_ClearState(void)
{
	int i = 0;
	//---������벽��
	//memset(decodeStep, 0, DECODE_SITE_COUNT);
	//---�������
	for (i = 0; i < DECODE_SITE_COUNT; i++)
	{
		g_DecodeICPCount[i]		= 0;
		g_DecodeHighPulseWidth[i] = 0;
		g_DecodeLowPulseWidth[i] = 0;
		g_DecodeICPMode[i] = 0;
		g_DecodeICPEvent[i] = 0;
		g_DecodeNewStep[i] = 0;
		g_DecodeOldStep[i] = 0;
		g_DecodeRiseCount[i] = 0;
		g_DecodeFallCount[i] = 0;
		g_DecodeTickCount[i] = 0;
		g_DecodePulseTick[i] = 0;
		g_DecodeWaveMode[i] = 0;
		g_DecodePulseIndex[i] = 0;
		g_DecodeFrameCount[i] = 0;
		g_DecodeByteNewVal[i] = 0;
		g_DecodeByteOldVal[i] = 0;
	}
	//---�����ǰ����ֵ
	//memset(decodeNowCount, 0, DECODE_SITE_COUNT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		��������������
//////////////////////////////////////////////////////////////////////////////
void Decode_START(void)
{
	//---�ر�ʵʱ�����
	DEC_LED_OFF;
	//---��λ����ʧ��
	DEC_PASS_FAIL;

	//---�رն�ʱ��
	LL_TIM_DisableCounter(DECODE_USE_TIM);

	//---����жϱ�־λ
	LL_TIM_ClearFlag_UPDATE(DECODE_USE_TIM);
	LL_TIM_ClearFlag_CC1(DECODE_USE_TIM);
	LL_TIM_ClearFlag_CC2(DECODE_USE_TIM);
	LL_TIM_ClearFlag_CC3(DECODE_USE_TIM);
	LL_TIM_ClearFlag_CC4(DECODE_USE_TIM);

	//---�����־λ
	//LL_TIM_ClearFlag(DEC_USE_TIM);
	//---���������
	LL_TIM_SetCounter(DECODE_USE_TIM, 0);

	//---ʹ�ܶ�ʱ��
	LL_TIM_EnableCounter(DECODE_USE_TIM);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����رս�����
//////////////////////////////////////////////////////////////////////////////
void Decode_STOP(void)
{
	//---��ʹ�ܶ�ʱ��
	LL_TIM_DisableCounter(DECODE_USE_TIM);
	DEC_LED_OFF;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��ȡ�����RST�ź�
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_GetRST(void)
{
	UINT8_T _return = 0;

	//---���SOT
	if (DECA_RST_STATE == 0)
	{
		_return |= 0x01;
	}
	if (DECB_RST_STATE == 0)
	{
		_return |= 0x02;
	}
	if (DECC_RST_STATE == 0)
	{
		_return |= 0x04;
	}
	if (DECD_RST_STATE == 0)
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
//////˵		���� ɨ�����RST�ź�
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_ScanRST(void)
{
	//---��ȡRST��״̬
	UINT8_T _return = Decode_GetRST();

	//---����Ƿ��н����ź�
	if (_return != 0)
	{
		#ifndef USE_FT_CP_TEST

		//---��ʱ�ȴ�������ģʽ�������������ͬʱ���ڵȴ�����SITE�Ĵ����źŵĵ���
		//DelayTask_ms(10);
		#endif

		//---��ȡRST��״̬
		_return = Decode_GetRST();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ����ͨ���Ľ��
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodePass(UINT8_T channel, UINT8_T isPass)
{
	switch (channel)
	{
		case 0:
			if (isPass)
			{
				DECA_PASS_OK;
			}
			else
			{
				DECA_PASS_FAIL;
			}
			break;
		case 1:
			if (isPass)
			{
				DECB_PASS_OK;
			}
			else
			{
				DECB_PASS_FAIL;
			}
			break;
		case 2:
			if (isPass)
			{
				DECC_PASS_OK;
			}
			else
			{
				DECC_PASS_FAIL;
			}
			break;
		case 3:
			if (isPass)
			{
				DECD_PASS_OK;
			}
			else
			{
				DECD_PASS_FAIL;
			}
			break;
		default:
			break;
	}
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ʵʱ�����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeLED(UINT8_T channel, UINT8_T isPass)
{
	switch (channel)
	{
		case 0:
			if (isPass)
			{
				DECA_LED_IS_ON;
			}
			else
			{
				DECA_LED_IS_OFF;
			}
			break;
		case 1:
			if (isPass)
			{
				DECB_LED_IS_ON;
			}
			else
			{
				DECB_LED_IS_OFF;
			}
			break;
		case 2:
			if (isPass)
			{
				DECC_LED_IS_ON;
			}
			else
			{
				DECC_LED_IS_OFF;
			}
			break;
		case 3:
			if (isPass)
			{
				DECD_LED_IS_ON;
			}
			else
			{
				DECD_LED_IS_OFF;
			}
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void Decode_CalcPulseWidth(UINT32_T index, UINT8_T site)
{
	//---�������Ե��л�,�½��ش���
	if (LL_TIM_IC_GetPolarity(DECODE_USE_TIM, index) != LL_TIM_IC_POLARITY_RISING)
	{
		//---�л�Ϊ������
		LL_TIM_IC_SetPolarity(DECODE_USE_TIM, index, LL_TIM_IC_POLARITY_RISING);
		//---�½��ؼ���
		g_DecodeFallCount[site] = g_DecodeICPCount[site];
		//---�жϲ�ѯ���������ݲ�һ�£�������жϱ�־δ����
		if (g_DecodeFallCount[site]< g_DecodeRiseCount[site])
		{
			//---����ߵ�ƽ�Ŀ��
			g_DecodeHighPulseWidth[site] = DECODE_TIM_RELOAD  + g_DecodeFallCount[site] - g_DecodeRiseCount[site];

		}
		else 
		{
			//---����ߵ�ƽ�Ŀ��
			g_DecodeHighPulseWidth[site] = g_DecodeFallCount[site] - g_DecodeRiseCount[site];

		}
		//---��׽���½���,����ߵ�ƽ��������
		g_DecodeICPMode[site] = DECODE_LEVEL_HIGH;
	}
	else   //---�����ش���
	{
		//---�л�Ϊ������
		LL_TIM_IC_SetPolarity(DECODE_USE_TIM, index, LL_TIM_IC_POLARITY_FALLING);
		//---�����ؼ���
		g_DecodeRiseCount[site] = g_DecodeICPCount[site];
		//---�жϲ�ѯ���������ݲ�һ�£�������жϱ�־δ����
		if (g_DecodeRiseCount[site] < g_DecodeFallCount[site])
		{
			//---����͵�ƽ�Ŀ��
			g_DecodeLowPulseWidth[site] = DECODE_TIM_RELOAD  + g_DecodeRiseCount[site] - g_DecodeFallCount[site];
		}
		else
		{
			//---����͵�ƽ�Ŀ��
			g_DecodeLowPulseWidth[site] = g_DecodeRiseCount[site] - g_DecodeFallCount[site];
		}
		//---��׽��������,����͵�ƽ��������
		g_DecodeICPMode[site] = DECODE_LEVEL_LOW;
	}
	//---��ȡ��ǰ��ƽ��ʱ��ڵ�
	g_DecodeTickCount[site] = SysTickTask_GetTick();
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ѯ����������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_QueryCalcPulseWidth(UINT8_T site)
{
	UINT8_T _return = ERROR_1;
	UINT32_T icpChannel = 0;
	switch (site)
	{
		case 0:
			icpChannel = LL_TIM_CHANNEL_CH1;
			break;
		case 1:
			icpChannel = LL_TIM_CHANNEL_CH2;
			break;
		case 2:
			icpChannel = LL_TIM_CHANNEL_CH3;
			break;
		case 3:
			icpChannel = LL_TIM_CHANNEL_CH4;
			break;
		default:
			return _return;
	}
	if (g_DecodeICPEvent[site]!=0)
	{
		//---�����־λ
		g_DecodeICPEvent[site] = 0;
		//---����������
		Decode_CalcPulseWidth(icpChannel, site);
		_return = OK_0;
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
void Decode_CalcPulseTick(UINT8_T site)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = SysTickTask_GetTick()+1;
	//---����ʱ�����
	if (nowTime<g_DecodeTickCount[site])
	{
		g_DecodePulseTick[site]= (0xFFFFFFFF - g_DecodeTickCount[site] + nowTime);
	}
	else
	{
		g_DecodePulseTick[site] = (nowTime - g_DecodeTickCount[site]);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����رս�����
//////////////////////////////////////////////////////////////////////////////
void Decode_IRQTask(void)
{
	//---���벶׽1�Ĳ�׽�ж�
	if (LL_TIM_IsActiveFlag_CC1(DECODE_USE_TIM) != RESET)
	{
		//---�������벶׽��ֵ
		g_DecodeICPCount[0] = LL_TIM_IC_GetCaptureCH1(DECODE_USE_TIM);
		//---��¼������׽
		g_DecodeICPEvent[0] += 1;
		////---����������
		//Decode_CalcPulseWidth(LL_TIM_CHANNEL_CH1, 0);
		//---����жϱ�־λ
		LL_TIM_ClearFlag_CC1(DECODE_USE_TIM);
	}

	//---���벶׽2�Ĳ�׽�ж�
	if (LL_TIM_IsActiveFlag_CC2(DECODE_USE_TIM) != RESET)
	{
		#if (DECODE_SITE_COUNT>1)
		//---�������벶׽��ֵ
		g_DecodeICPCount[1] = LL_TIM_IC_GetCaptureCH2(DECODE_USE_TIM);
		//---��¼������׽
		g_DecodeICPEvent[1] += 1;
		#endif
		////---����������
		//Decode_CalcPulseWidth(LL_TIM_CHANNEL_CH2, 1);
		//---����жϱ�־λ
		LL_TIM_ClearFlag_CC2(DECODE_USE_TIM);
	}

	//---���벶׽3�Ĳ�׽�ж�
	if (LL_TIM_IsActiveFlag_CC3(DECODE_USE_TIM) != RESET)
	{
		#if (DECODE_SITE_COUNT>2)
		//---�������벶׽��ֵ
		g_DecodeICPCount[2] = LL_TIM_IC_GetCaptureCH3(DECODE_USE_TIM);
		//---��¼������׽
		g_DecodeICPEvent[2] += 1;
		#endif
		////---����������
		//Decode_CalcPulseWidth(LL_TIM_CHANNEL_CH3, 2);
		//---����жϱ�־λ
		LL_TIM_ClearFlag_CC3(DECODE_USE_TIM);
	}
	//---���벶׽4�Ĳ�׽�ж�
	if (LL_TIM_IsActiveFlag_CC4(DECODE_USE_TIM) != RESET)
	{
		#if (DECODE_SITE_COUNT>3)
		//---�������벶׽��ֵ
		g_DecodeICPCount[3] = LL_TIM_IC_GetCaptureCH4(DECODE_USE_TIM);
		//---��¼������׽
		g_DecodeICPEvent[3] += 1;
		#endif
		////---����������
		//Decode_CalcPulseWidth(LL_TIM_CHANNEL_CH4, 3);
		//---����жϱ�־λ
		LL_TIM_ClearFlag_CC4(DECODE_USE_TIM);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���������ش���
//////////////////////////////////////////////////////////////////////////////
void Decode_SetPolarityRising(UINT8_T site)
{
	switch (site)
	{
		case 0:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
			break;
		case 1:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
			break;
		case 2:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH3, LL_TIM_IC_POLARITY_RISING);
			break;
		case 3:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH4, LL_TIM_IC_POLARITY_RISING);
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����½��ش���
//////////////////////////////////////////////////////////////////////////////
void Decode_SetPolarityFalling(UINT8_T site)
{
	switch (site)
	{
		case 0:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_FALLING);
			break;
		case 1:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_FALLING);
			break;
		case 2:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH3, LL_TIM_IC_POLARITY_FALLING);
			break;
		case 3:
			LL_TIM_IC_SetPolarity(DECODE_USE_TIM, LL_TIM_CHANNEL_CH4, LL_TIM_IC_POLARITY_FALLING);
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����������뵽����ֵ�洢��
//////////////////////////////////////////////////////////////////////////////
void Decode_AddBit(UINT16_T channel, UINT16_T value)
{
	//---�жϽ���ֵ
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ӡ���벨��
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void  Decode_PrintfWave(UINT16_T channel, UINT16_T value)
{
	//---�жϽ���ֵ
	if (value)
	{
		switch (channel)
		{
			case 0:
				DECA_WAVE_CTR_OUT_1;
				break;
			case 1:
				DECB_WAVE_CTR_OUT_1;
				break;
			case 2:
				DECC_WAVE_CTR_OUT_1;
				break;
			case 3:
				DECD_WAVE_CTR_OUT_1;
				break;
			default:
				DECA_WAVE_CTR_OUT_1;
				DECB_WAVE_CTR_OUT_1;
				DECC_WAVE_CTR_OUT_1;
				DECD_WAVE_CTR_OUT_1;
				break;
		}

	}
	else
	{
		switch (channel)
		{
			case 0:
				DECA_WAVE_CTR_OUT_0;
				break;
			case 1:
				DECB_WAVE_CTR_OUT_0;
				break;
			case 2:
				DECC_WAVE_CTR_OUT_0;
				break;
			case 3:
				DECD_WAVE_CTR_OUT_0;
				break;
			default:
				DECA_WAVE_CTR_OUT_0;
				DECB_WAVE_CTR_OUT_0;
				DECC_WAVE_CTR_OUT_0;
				DECD_WAVE_CTR_OUT_0;
				break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ѯʽ����
//////�������:
//////�������:
//////˵		����ʹ�ò�ѯʽ�ķ�ʽʵ�ֽ��룬��ѯ��ʱ�������벶׽��������
//////////////////////////////////////////////////////////////////////////////
void Decode_Query(void)
{
	UINT8_T site = 0;
	UINT8_T isOpenLed = 0;
	//---����·���н���
	for (site = 0; site < DECODE_SITE_COUNT; site++)
	{
		if (g_DecodeActivateSite[site] == 1)
		{
			//---��������ʱ�����
			Decode_CalcPulseTick(site);
			//---��ѯ����������,�ж��Ƿ�����Ч�¼�
			Decode_QueryCalcPulseWidth(site);
			//---�������
			switch (g_DecodeNewStep[site])
			{
				case DECODE_STEP_0:				//---���������ش���
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---���벽��1
					g_DecodeNewStep[site] = DECODE_STEP_1;
					//---��ʼ����׽ģʽ
					g_DecodeICPMode[site] = 0;
					//---�����ؼ���
					g_DecodeRiseCount[site] = 0;
					//---�½��ؼ���
					g_DecodeFallCount[site] = 0;
					//---����ͨ�������ز�׽ģʽ
					Decode_SetPolarityRising(site);
					break;
				case DECODE_STEP_1:				//---��ʼ��
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---����λ����0
					g_DecodeBitIndex[site] = 0;
					//---���������������
					g_DecodePulseIndex[site] = 0;
					//---֡�ϸ������
					g_DecodeFrameCount[site] = 0;
					//---������
					g_DecodeByteNewVal[site] = 0;
					//---�رս���ʵʱ��
					Decode_DecodeLED(site, 0);
					//---��λ����ָʾ��
					Decode_DecodePass(site, 0);
					//---��ӡ����
					Decode_PrintfWave(site, 1);
					//---���벽��
					g_DecodeNewStep[site] = DECODE_STEP_2;
					//---���¼�ʱ���ĵ�ֵ
					g_DecodeTickCount[site] = SysTickTask_GetTick();
					break;
				//===================
				//===�����жϿ�ʼ
				//===================
				case DECODE_STEP_2:				//---��׽�½��أ���֤�ߵ�ƽ��������
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_HIGH)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;

						//---�ж�����Ŀ��,�ж��ǲ�����������
						if (((g_DecodeHighPulseWidth[site] >= DECODE_PT2262_NARROW_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_PT2262_NARROW_WIDTH_MAX))
							||((g_DecodeHighPulseWidth[site] >= DECODE_SQUARE_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_SQUARE_WIDTH_MAX))
							||((g_DecodeHighPulseWidth[site] >= DECODE_FRAME_START_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_FRAME_START_WIDTH_MAX)))
						{
							//---������2262��Ҳ�����Ƿ���
							g_DecodeWaveMode[site] = DECODE_WAVE_SQUARE;
							//---��֤�͵�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_3;
						}
						else if ((g_DecodeHighPulseWidth[site] >= DECODE_PT2262_WIDE_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_PT2262_WIDE_WIDTH_MAX))
						{
							//---�ж�����PT2262
							g_DecodeWaveMode[site] = DECODE_WAVE_PT2262;
							//---��֤խ�͵�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_6;
						}
						else
						{
							//---�ߵ�ƽ��������������������,���벽��1����λ����
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 0);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_3:			//---��׽�����أ���֤�͵�ƽ��������
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---�ж�����Ŀ��,�ж��ǲ�����������
						if (((g_DecodeLowPulseWidth[site] >= DECODE_PT2262_NARROW_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_PT2262_NARROW_WIDTH_MAX))
							|| ((g_DecodeLowPulseWidth[site] >= DECODE_SQUARE_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_SQUARE_WIDTH_MAX))
							|| ((g_DecodeLowPulseWidth[site] >= DECODE_FRAME_START_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_FRAME_START_WIDTH_MAX)))
						{
							//---�ж��Ƿ���
							g_DecodeWaveMode[site] = DECODE_WAVE_SQUARE;
							//---����ⷽ������
							g_DecodeNewStep[site] = DECODE_STEP_9;
							//---1Bit�ĺϸ�����
							g_DecodePulseIndex[site]++;
						}
						else if ((g_DecodeLowPulseWidth[site] >= DECODE_PT2262_WIDE_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_PT2262_WIDE_WIDTH_MAX))
						{
							//---�ж�PT2262
							g_DecodeWaveMode[site] = DECODE_WAVE_PT2262;
							//---��֤�ߵ�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_4;
							//---����ϸ�һ��
							g_DecodeBitIndex[site]++;
							//---�յ�0
							g_DecodeByteNewVal[site] += 0;
							//---����һλ
							g_DecodeByteNewVal[site] <<= 1;
						}
						else
						{
							//---�ߵ�ƽ��������������������,���벽��1����λ����
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 1);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				//===================
				//===�����жϽ���
				//===================

				//===================
				//===PT2262���뿪ʼ
				//===================
				case DECODE_STEP_4:				//---��׽�½��أ���֤�ߵ�ƽ��������		
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�ߵ�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_HIGH)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϸߵ�ƽ
						if ((g_DecodeHighPulseWidth[site] >= DECODE_PT2262_NARROW_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_PT2262_NARROW_WIDTH_MAX))
						{
							//---��֤��͵�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_5;
						}
						else if ((g_DecodeHighPulseWidth[site] >= DECODE_PT2262_WIDE_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_PT2262_WIDE_WIDTH_MAX))
						{
							//---��֤�ߵ�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_6;
							//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ
							Decode_PrintfWave(site, 0);
							//---����ϸ�һ��
							g_DecodeBitIndex[site]++;
							//---�յ�1
							g_DecodeByteNewVal[site] += 1;
							//---����һλ
							g_DecodeByteNewVal[site] <<= 1;
							//---�ж��Ƿ�������
							if (g_DecodeBitIndex[site] >= DECODE_PT2262_PASS_MAX_COUNT)
							{
								//---�����������֤խ�͵�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_6;
							}
						}
						else
						{
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 0);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_5:				//---��͵�ƽ
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϵ͵�ƽ
						if ((g_DecodeLowPulseWidth[site] >= DECODE_PT2262_WIDE_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_PT2262_WIDE_WIDTH_MAX))
						{
							//---��֤�ߵ�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_4;
							//---����ϸ�һ��
							g_DecodeBitIndex[site]++;
							//---�յ�0
							g_DecodeByteNewVal[site] += 0;
							//---����һλ
							g_DecodeByteNewVal[site] <<= 1;
							//---�ж��Ƿ�������
							if (g_DecodeBitIndex[site] >= DECODE_PT2262_PASS_MAX_COUNT)
							{
								//---�����������֤�͵�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_7;
							}
						}
						else 
						{
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 1);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_6:				//---խ�͵�ƽ
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						if ((g_DecodeLowPulseWidth[site] >= DECODE_PT2262_NARROW_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_PT2262_NARROW_WIDTH_MAX))
						{
							//---��֤�ߵ�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_4;
							//---�ж��Ƿ�������
							if (g_DecodeBitIndex[site] >= DECODE_PT2262_PASS_MAX_COUNT)
							{
								//---�����������֤խ�͵�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_7;
							}
						}
						else
						{
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 1);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_7:					//PT2262����֤�ߵ�ƽխ���壬֡ͣ��ǰ��
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�ߵ�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_HIGH)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϸߵ�ƽ
						if ((g_DecodeHighPulseWidth[site] >= DECODE_PT2262_NARROW_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_PT2262_NARROW_WIDTH_MAX))
						{
							//---��֤֡ͣ�ٵĵ͵�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_8;
						}
						else
						{
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 0);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_8:						//PT2262����֤�͵�ƽ���壬֡ͣ��ʱ��
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϵ͵�ƽ
						if ((g_DecodeLowPulseWidth[site] >= DECODE_PT2262_FRAME_PAUSE_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_PT2262_FRAME_PAUSE_MAX))
						{
							//---֡ͣ����֤�ɹ������½���
							g_DecodeNewStep[site] = DECODE_STEP_2;
							//---�������ϸ�BIT
							g_DecodeBitIndex[site] = 0;
							//---����ϸ�֡��
							g_DecodeFrameCount[site]++;
							//---�жϽ���ϸ�֡��
							if (g_DecodeFrameCount[site] >= DECODE_PT2262_PASS_FRAME_MIN_COUNT)
							{
								//---�ж����ν����ֵ�Ƿ���ͬ
								if (g_DecodeByteOldVal[site] == g_DecodeByteNewVal[site])
								{
									isOpenLed = 1;
								}
								else
								{
									isOpenLed = 0;
								}
								//---����ɹ����򿪽���ʵʱ��
								Decode_DecodeLED(site,  isOpenLed);
								//---����ɹ�����λ����ʾ��
								Decode_DecodePass(site, isOpenLed);
								//---����ϸ�֡����
								g_DecodeFrameCount[site] = 0;
								//---���㵱ǰֵ
								g_DecodeByteNewVal[site] = 0;

							}
							else
							{
								//---�����һ�ε�ֵ
								g_DecodeByteOldVal[site] = g_DecodeByteNewVal[site];
								//---���㵱ǰֵ
								g_DecodeByteNewVal[site] = 0;
							}
						}
						else
						{
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 1);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				//===================
				//===PT2262�������
				//===================

				//===================
				//===��֡�������뿪ʼ
				//===================
				case DECODE_STEP_9:					//---��׽�½��أ���֤�ߵ�ƽ��������
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�ߵ�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_HIGH)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�ж��ǲ��ǿ�ʼ�����ĺϸ��ƽ
						if (g_DecodePulseIndex[site]< DECODE_FRAME_PAUSE_COUNT_INDEX)
						{
							if ((g_DecodeHighPulseWidth[site] >= DECODE_FRAME_START_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_FRAME_START_WIDTH_MAX))
							{
								//---��֤��֡�����ĵ͵�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_10;
							}
							else
							{
								//---�ߵ�ƽ����������
								g_DecodeNewStep[site] = DECODE_STEP_1;
							}
						}
						else
						{
							//---�жϸߵ�ƽ
							if ((g_DecodeHighPulseWidth[site] >= DECODE_FRAME_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_FRAME_WIDTH_MAX))
							{
								//---��֤��֡�����ĵ͵�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_10;
							}
							else
							{
								//---�ߵ�ƽ����������
								g_DecodeNewStep[site] = DECODE_STEP_1;
							}
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 0);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_10:				//---��׽�����أ���֤�͵�ƽ��������
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�ж��ǲ��ǿ�ʼ�����ĺϸ��ƽ
						if (g_DecodePulseIndex[site] < DECODE_FRAME_PAUSE_COUNT_INDEX)
						{
							if ((g_DecodeLowPulseWidth[site] >= DECODE_FRAME_START_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_FRAME_START_WIDTH_MAX))
							{
								//---��֤��֡�����ĵ͵�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_9;
								//---��������
								g_DecodePulseIndex[site]++;
								g_DecodeBitIndex[site]=g_DecodePulseIndex[site];
							}
							else
							{
								//---�͵�ƽ����������
								g_DecodeNewStep[site] = DECODE_STEP_1;
							}
						}
						else
						{
							//---�жϵ͵�ƽ
							if ((g_DecodeLowPulseWidth[site] >= DECODE_FRAME_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_FRAME_WIDTH_MAX))
							{
								//---��֤��֡�����ĸߵ�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_9;
								//---�������������BIT��
								g_DecodeBitIndex[site]++;
								//---�ж��Ƿ�ϸ�
								if (g_DecodeBitIndex[site]>= DECODE_FREAME_PASS_MAX_COUNT)
								{
									//---��֤��֡������֡ͣ��
									g_DecodeNewStep[site] = DECODE_STEP_11;
								}
							}
							else
							{
								//---�ߵ�ƽ����������
								g_DecodeNewStep[site] = DECODE_STEP_1;
							}
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 1);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_11:						//---����֡ͣ��ǰ�����壬�ߵ�ƽ
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�ߵ�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_HIGH)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϸߵ�ƽ
						if ((g_DecodeHighPulseWidth[site] >= DECODE_FRAME_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_FRAME_WIDTH_MAX))
						{
							//---��֤֡ͣ��ǰ�ĵ͵�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_12;
						}
						else
						{
							//---�ߵ�ƽ����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 0);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_12:				//---��֤֡ͣ��ʱ��,�͵�ƽ
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϵ͵�ƽ
						if ((g_DecodeLowPulseWidth[site] >= DECODE_FRAME_PAUSE_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_FRAME_PAUSE_MAX))
						{
							//---֡ͣ����֤�ɹ������½���
							g_DecodeNewStep[site] = DECODE_STEP_2;
							//---����ϸ�֡��
							g_DecodeFrameCount[site]++;
							//---�������ϸ�BIT
							g_DecodeBitIndex[site] = 0;
							g_DecodePulseIndex[site]=0;
							//---�жϽ��������ϸ��֡��
							if (g_DecodeFrameCount[site] >= DECODE_FRAME_PASS_FRAME_MIN_COUNT)
							{
								//---����ɹ����򿪽���ʵʱ��
								Decode_DecodeLED(site, 1);
								//---����ɹ�����λ����ʾ��
								Decode_DecodePass(site, 1);
								//---����ϸ�֡����
								g_DecodeFrameCount[site] = 0;
							}
						}
						else if((g_DecodeLowPulseWidth[site] >= DECODE_SQUARE_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_SQUARE_WIDTH_MAX))
						{
							g_DecodeBitIndex[site]++;
							//---�����������봦�����
							g_DecodeWaveMode[site] = DECODE_WAVE_SQUARE;
							//---������������
							g_DecodeNewStep[site] = DECODE_STEP_13;
						}
						else
						{
							//---�͵�ƽ������Ҫ�����½���
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 1);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				//===================
				//===��֡�����������
				//===================

				//===================
				//===�����������뿪ʼ
				//===================
				case DECODE_STEP_13:		//---��׽�½��أ���֤�ߵ�ƽ��������
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�ߵ�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_HIGH)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϸߵ�ƽ
						if ((g_DecodeHighPulseWidth[site] >= DECODE_SQUARE_WIDTH_MIN) && (g_DecodeHighPulseWidth[site] <= DECODE_SQUARE_WIDTH_MAX))
						{
							//---���������ĵ͵�ƽ
							g_DecodeNewStep[site] = DECODE_STEP_14;
						}
						else
						{
							//---�ߵ�ƽ����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
						//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
						Decode_PrintfWave(site, 0);
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				case DECODE_STEP_14:		//---��׽�����أ���֤�͵�ƽ��������
					g_DecodeOldStep[site] = g_DecodeNewStep[site];
					//---��֤�͵�ƽ
					if ((g_DecodeICPMode[site] & DECODE_LEVEL_MASK) == DECODE_LEVEL_LOW)
					{
						//---��λ��ץȡ��¼ֵ
						g_DecodeICPMode[site] = DECODE_LEVEL_NONE;
						//---�жϸߵ�ƽ
						if ((g_DecodeLowPulseWidth[site] >= DECODE_SQUARE_WIDTH_MIN) && (g_DecodeLowPulseWidth[site] <= DECODE_SQUARE_WIDTH_MAX))
						{
							//---����ϸ�������
							g_DecodeBitIndex[site]++;
							//---�жϽ����Ƿ�ϸ�
							if (g_DecodeBitIndex[site]>= DECODE_SQUARE_PASS_MAX_COUNT)
							{
								//---����������֤�ɹ������½���
								g_DecodeNewStep[site] = DECODE_STEP_2;
								//---����ɹ����򿪽���ʵʱ��
								Decode_DecodeLED(site, 1);
								//---����ɹ�����λ����ʾ��
								Decode_DecodePass(site, 1);
								//---�������ϸ�BIT��
								g_DecodeBitIndex[site] = 0;
							}
							else
							{
								//---���������ĸߵ�ƽ
								g_DecodeNewStep[site] = DECODE_STEP_13;
							}
							//---��ʾ��ֵ����һ��ƽ�����ȵ�ֵ����ӡ�������
							Decode_PrintfWave(site, 1);
						}
						else
						{
							//---�ߵ�ƽ����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
						}
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������,�ͬ��ƽ����ʱ����20ms
						if (g_DecodePulseTick[site] > DECODE_SAME_LEVEL_MAX_WIDTH)
						{
							//---ͬ��ƽ����ʱ��,�����������
							g_DecodeNewStep[site] = DECODE_STEP_1;
							//---����ʱ���ǩ�����ⳤʱ��Ľ������״̬
							g_DecodeTickCount[site] = SysTickTask_GetTick();
						}
					}
					break;
				//===================
				//===���������������
				//===================
				default:
					g_DecodeNewStep[site] = DECODE_STEP_0;
					break;
			}
		}
	}
}
