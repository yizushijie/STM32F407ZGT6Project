#include "timer_cfg.h"

//===ȫ�ֱ�������
CalcFreq_HandlerType  g_CalcFreq;
pCalcFreq_HandlerType pCalcFreq = &g_CalcFreq;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �ⲿ����ģʽ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreqMode_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---ʹ�ܶ�ʱ��ʱ��
	Timer_Clock(TIM3, 1);
	//---ʹ�ܶ˿�ʱ��
	GPIO_Clock(GPIOC, 1);
	//---GPIO��ʼ��---PC6ӳ��ΪTim3_CH1
	GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
#ifdef USE_MCU_STM32F1
	LL_GPIO_AF_RemapPartial_TIM3();
	//GPIO_InitStruct.Mode		= LL_GPIO_MODE_FLOATING;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
#else
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
#endif
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_2;														//---�˿ڸ���ģʽ
#endif
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
#ifdef CALC_FREQ_lEVEL_SHIFT
	pCalcFreq->msgOE[0].msgGPIOPort=GPIOD;
	pCalcFreq->msgOE[0].msgGPIOBit= LL_GPIO_PIN_7;
	//---ʹ�ܶ˿�ʱ��
	GPIO_Clock(pCalcFreq->msgOE[0].msgGPIOPort, 1);
	GPIO_InitStruct.Pin = pCalcFreq->msgOE[0].msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	LL_GPIO_Init(pCalcFreq->msgOE[0].msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(pCalcFreq->msgOE[0].msgGPIOPort, pCalcFreq->msgOE[0].msgGPIOBit);
#endif
	//////////////////////////////////////////////////////////////////////////////
	//---GPIO��ʼ��---PC7ӳ��ΪTim3_CH2
	GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
#ifdef USE_MCU_STM32F1
	LL_GPIO_AF_RemapPartial_TIM3();
	//GPIO_InitStruct.Mode		= LL_GPIO_MODE_FLOATING;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
#else
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
#endif
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_2;														//---�˿ڸ���ģʽ
#endif
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
#ifdef CALC_FREQ_lEVEL_SHIFT
	pCalcFreq->msgOE[1].msgGPIOPort = GPIOD;
	pCalcFreq->msgOE[1].msgGPIOBit = LL_GPIO_PIN_7;
	//---ʹ�ܶ˿�ʱ��
	GPIO_Clock(pCalcFreq->msgOE[1].msgGPIOPort, 1);
	GPIO_InitStruct.Pin = pCalcFreq->msgOE[1].msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	LL_GPIO_Init(pCalcFreq->msgOE[1].msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(pCalcFreq->msgOE[1].msgGPIOPort, pCalcFreq->msgOE[1].msgGPIOBit);
#endif
	/*
	//---��������ʱ�ӵ�Ԥ��Ƶ
	TIM_InitStruct.Prescaler = 0;
	//---���ϼ���
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	//---�Զ�װ��ֵ���Զ�װ��ֵΪ��ʱ��������������
	TIM_InitStruct.Autoreload = 0xFFFFFF;
	//---��ʱ��ʱ�ӷ�Ƶ��
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	//---��ʼ����ʱ��
	LL_TIM_Init(TIM3, &TIM_InitStruct);
	//---�����Զ�װ��
	LL_TIM_EnableARRPreload(TIM3);
	//---���ô�������ͨ��
	LL_TIM_SetTriggerInput(TIM3, LL_TIM_TS_TI2FP2);
	//---��������ͨ��
	LL_TIM_IC_SetActiveInput(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
	//---�����ʺ�ʱ��Դ
	LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_EXT_MODE1);
	//---���ò���/�Ƚ�ͨ��
	LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH2);
	//---����ͨ�����˲�ʱ��
	LL_TIM_IC_SetFilter(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_FILTER_FDIV1);
	//---ͨ��2�������ش���
	LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
	//---���ô����жϣ�TIE��
	LL_TIM_DisableIT_TRIG(TIM3);
	//---����DMA�����жϣ�TIE��
	LL_TIM_DisableDMAReq_TRIG(TIM3);
	//---��ģʽѡ��λ
	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
	//---��ʹ������ģʽ
	LL_TIM_DisableMasterSlaveMode(TIM3);
	//---ʹ�ܼ�����
	//LL_TIM_EnableCounter(TIM5);
	*/
	Timer_CalcFreqMode_DeInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreqMode_DeInit(void)
{
	LL_TIM_DeInit(TIM3);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreqMode_PreInit(UINT8_T ch)
{
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };
	//---��������ʱ�ӵ�Ԥ��Ƶ
	TIM_InitStruct.Prescaler = 0;
	//---���ϼ���
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	//---�Զ�װ��ֵ���Զ�װ��ֵΪ��ʱ��������������
	TIM_InitStruct.Autoreload = 0xFFFFFF;
	//---��ʱ��ʱ�ӷ�Ƶ��
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	//---��ʼ����ʱ��
	LL_TIM_Init(TIM3, &TIM_InitStruct);
	//---�����Զ�װ��
	LL_TIM_EnableARRPreload(TIM3);
	//---ͨ��ѡ��
	if (ch==0)
	{
		//---���ô�������ͨ��
		LL_TIM_SetTriggerInput(TIM3, LL_TIM_TS_TI1FP1);
		//---��������ͨ��
		LL_TIM_IC_SetActiveInput(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
		//---�����ʺ�ʱ��Դ
		LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_EXT_MODE1);
		//---���ò���/�Ƚ�ͨ��
		LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH1);
		//---����ͨ�����˲�ʱ��
		LL_TIM_IC_SetFilter(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1_N2);
		//---ͨ��2�������ش���
		LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
		pCalcFreq->msgChannel = 0;
	}
	else 
	{
		//---���ô�������ͨ��
		LL_TIM_SetTriggerInput(TIM3, LL_TIM_TS_TI2FP2);
		//---��������ͨ��
		LL_TIM_IC_SetActiveInput(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
		//---�����ʺ�ʱ��Դ
		LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_EXT_MODE1);
		//---���ò���/�Ƚ�ͨ��
		LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH2);
		//---����ͨ�����˲�ʱ��
		LL_TIM_IC_SetFilter(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_FILTER_FDIV1_N2);
		//---ͨ��2�������ش���
		LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
		pCalcFreq->msgChannel = 1;
	}
	//---���ô����жϣ�TIE��
	LL_TIM_DisableIT_TRIG(TIM3);
	//---����DMA�����жϣ�TIE��
	LL_TIM_DisableDMAReq_TRIG(TIM3);
	//---��ģʽѡ��λ
	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
	//---��ʹ������ģʽ
	LL_TIM_DisableMasterSlaveMode(TIM3);
	//---ʹ�ܼ�����
	//LL_TIM_EnableCounter(TIM5);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreq_Init(void)
{
	VLTUINT32_T tempFreq = 0;
	//---��������
	static UINT8_T nCount = 0;
	//---��ʱ���������
	static UINT8_T nOverCount = 0;
	//---��ʼ����
	if (pCalcFreq->msgStep[pCalcFreq->msgChannel] == 0)
	{
		pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] = 0;
		pCalcFreq->msgFreqMHz[pCalcFreq->msgChannel] = 0;
		pCalcFreq->msgStep[pCalcFreq->msgChannel] = 1;
		//---���㴥�����жϱ��
		LL_TIM_ClearFlag_TRIG(TIM3);
		//---��������жϱ��
		LL_TIM_ClearFlag_UPDATE(TIM3);
		//---���������
		LL_TIM_SetCounter(TIM3, 0);
		//---ʹ�ܼ�����
		LL_TIM_EnableCounter(TIM3);
	}
	//---��ȡ��ʼֵ
	else if (pCalcFreq->msgStep[pCalcFreq->msgChannel] == 1)
	{
		//---�����жϷ���
		if (LL_TIM_IsActiveFlag_TRIG(TIM3) != 0)
		{
			//---��ȡ��ǰ�ļ������
			pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] = LL_TIM_GetCounter(TIM3);
			//---�����жϱ�־
			LL_TIM_ClearFlag_TRIG(TIM3);
			pCalcFreq->msgStep[pCalcFreq->msgChannel] = 2;
			//---�����������������ݣ�ʹ��������ȫ�ֱ�������Ҫ�ֶ����
			nOverCount = 0;
			nCount = 0;
		}
	}
	else if (pCalcFreq->msgStep[pCalcFreq->msgChannel] == 2)
	{
		//---��������;��μ����ܹ���߻�ȡƵ�ʵľ�׼��
		nCount++;
		//---�����ж�
		if (LL_TIM_IsActiveFlag_UPDATE(TIM3) != 0)
		{
			//---��������жϱ��
			LL_TIM_ClearFlag_UPDATE(TIM3);
			nOverCount++;
		}
		//---�����жϷ���
		if (LL_TIM_IsActiveFlag_TRIG(TIM3) != 0)
		{
			//---�����жϱ�־
			LL_TIM_ClearFlag_TRIG(TIM3);
		}
		//---��ȡ10�κ��ֵ
		if (nCount > 9)
		{
			//---��ȡ��ǰ�ļ������
			tempFreq = LL_TIM_GetCounter(TIM3);
			//---��ʹ�ܼ�����
			LL_TIM_DisableCounter(TIM3);
			//---�������
			pCalcFreq->msgStep[pCalcFreq->msgChannel] = 3;
			//---����Ƶ��
			pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] = (0xFFFF * nOverCount + tempFreq - pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel]);
			//---�����������������ݣ�ʹ��������ȫ�ֱ�������Ҫ�ֶ����
			nOverCount=0;
			nCount=0;
		}
	}
	else
	{
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����Ƶ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreq_Task(UINT8_T ch)
{
#ifdef CALC_FREQ_lEVEL_SHIFT
	GPIO_OUT_0(pCalcFreq->msgOE[ch].msgGPIOPort, pCalcFreq->msgOE[0].msgGPIOBit);
#endif
	//---��ʼ��ʹ�õĶ�ʱ��
	Timer_CalcFreqMode_PreInit(ch);	
	/*
	//---���浱ǰ�δ�ʱ��������
	pCalcFreq->msgFuncTask = pSysTick->msgFuncTick;
	
	//---����ע�ᵱǰ�δ�ʱ�������񣬻�ȡ�����źŵ�Ƶ��---1ms�ɼ��������صĸ�ʽ������ɼ���1������1KHz���ݲ�֧��1KHzһ�µ��ź�
	SysTickTask_FuncTick(Timer_CalcFreq_Init);
	*/
	UINT8_T _return = SysTickTask_CreateTickTask(Timer_CalcFreq_Init);
	//---��ȡ��ǰ�δ�ʱʱ��
	UINT32_T nowTime = 0;
	UINT32_T oldTime = SysTickTask_GetTick();
	UINT32_T cnt = 0;
	if (_return!=0)
	{
		pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] = 0;
		goto GoToExit;
	}
	//---�ȴ��������������
	while (pCalcFreq->msgStep[pCalcFreq->msgChannel] != 3)
	{
		//---��ǰʱ��
		nowTime = SysTickTask_GetTick();
		//---�жϵδ�ʱ�Ƿ����������
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---�ж��Ƿ�ʱ,��ʱ100ms
		if (cnt > 100)
		{
			//---���ͷ�����ʱ����
			break;
		}
	}
	//---������ʱ����
	if (cnt > 100)
	{
		pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] = 0;
	}
	else
	{
		pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] *= 0.099983;
	}
	/*
	//---�ָ��δ�ʱ��������
	SysTickTask_FuncTick(pCalcFreq->msgFuncTask);
	//---ע��������
	pCalcFreq->msgFuncTask = NULL;
	*/
	//---�˳�����
GoToExit:
	//---ע��������
	_return = SysTickTask_DeleteTickTask(Timer_CalcFreq_Init);
	//---��������
	pCalcFreq->msgStep[pCalcFreq->msgChannel] = 0;
	//---����֮���MHz
	pCalcFreq->msgFreqMHz[pCalcFreq->msgChannel] = (float)(pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel]) / 1000.0;
	//---���ٶ�ʱ��������
	Timer_CalcFreqMode_DeInit();
#ifdef CALC_FREQ_lEVEL_SHIFT
	GPIO_OUT_1(pCalcFreq->msgOE[ch].msgGPIOPort, pCalcFreq->msgOE[0].msgGPIOBit);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float Timer_GetFreqKHz(void)
{
	return pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel];
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float Timer_GetFreqMHz(void)
{
	return pCalcFreq->msgFreqMHz[pCalcFreq->msgChannel];
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_Init(void)
{
	Timer_CalcFreqMode_Init();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_Clock(TIM_TypeDef *TIMx, UINT8_T isEnable)
{
#ifdef TIM1
	if (TIMx == TIM1)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		return;
	}
#endif
#ifdef TIM2
	if (TIMx == TIM2)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		return;
	}
#endif
#ifdef TIM3
	if (TIMx == TIM3)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
		}
		return;
	}
#endif
#ifdef TIM4
	if (TIMx == TIM4)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
		}
		return;
	}
#endif
#ifdef TIM5
	if (TIMx == TIM5)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
		}
		return;
	}
#endif
#ifdef TIM6
	if (TIMx == TIM6)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
		}
		return;
	}
#endif
#ifdef TIM7
	if (TIMx == TIM7)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
		}
		return;
	}
#endif
#ifdef TIM8
	if (TIMx == TIM8)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM8);
		}
		return;
	}
#endif
#ifdef TIM9
	if (TIMx == TIM9)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM9);
		}
		return;
	}
#endif
#ifdef TIM10
	if (TIMx == TIM10)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM10);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM10);
		}
		return;
	}
#endif
#ifdef TIM11
	if (TIMx == TIM11)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM11);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM11);
		}
		return;
	}
#endif
#ifdef TIM12
	if (TIMx == TIM12)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM12);
		}
		return;
	}
#endif
#ifdef TIM13
	if (TIMx == TIM13)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM13);
		}
		return;
	}
#endif

#ifdef TIM14
	if (TIMx == TIM14)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM14);
		}
		return;
	}
#endif
#ifdef TIM15
	if (TIMx == TIM15)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM15);
		}
		return;
	}
#endif
#ifdef TIM16
	if (TIMx == TIM16)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM16);
		}
		return;
	}
#endif
#ifdef TIM17
	if (TIMx == TIM17)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM17);
		}
		return;
	}
#endif
}