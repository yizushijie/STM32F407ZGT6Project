#include"encode_cfg.h"

//===��ű������ݵ��ֽ�����
UINT8_T	g_GenCodeByteCycleCode[GEN_CODE_BYTE_OF_CYCLE_COUNT];
//===�洢 #1 2262�����λ����ָ��
UINT8_T *pGenCodeByteCycleCode;
//===�ֽ��������	
VLTUINT16_T g_GenCodeByteIndex = 0;

//===���������ͨ������1
VLTUINT8_T g_GenCodeChannelMask1 = 0x0F;

//===���������ͨ������1
VLTUINT8_T g_GenCodeChannelMask2 = 0x00;

//===ͨ��1���� 433.92MHz�����Ű��ṩ433.92����
EnCode_HandlerType	g_GenCodeCH1[GEN_CODE_FRAME_COUNT] = {
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{	16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															}
														};
//===ͨ��2���ݽṹ������315MHz
EnCode_HandlerType	g_GenCodeCH2[GEN_CODE_FRAME_COUNT] = {
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{	16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															}
														};
//===ͨ��3���ݽṹ������230.4MHz
EnCode_HandlerType	g_GenCodeCH3[GEN_CODE_FRAME_COUNT] = {
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{	16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															}
														};
//===ͨ��4���ݽṹ��433.92MHz---���ź�Դ
EnCode_HandlerType	g_GenCodeCH4[GEN_CODE_FRAME_COUNT] = {
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{   16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															},
															{	16,
																1,
																{2,2,2,2,2,2,2,2,2,2,2,2}
															}
														};

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void EnCode_GPIO_Init(void)
{
	//---�˿ڵ�ʱ��ʹ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(ENCODE_CH1_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(ENCODE_CH2_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(ENCODE_CH3_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(ENCODE_CH4_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---��ʼ����������ͨ��1
	GPIO_InitStruct.Pin = ENCODE_CH1_BIT;
	LL_GPIO_Init(ENCODE_CH1_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(ENCODE_CH1_PORT,ENCODE_CH1_BIT);

	//---��ʼ����������ͨ��2
	GPIO_InitStruct.Pin = ENCODE_CH2_BIT;
	LL_GPIO_Init(ENCODE_CH2_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(ENCODE_CH2_PORT, ENCODE_CH2_BIT);

	//---��ʼ����������ͨ��3
	GPIO_InitStruct.Pin = ENCODE_CH3_BIT;
	LL_GPIO_Init(ENCODE_CH3_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(ENCODE_CH3_PORT, ENCODE_CH3_BIT);

	//---��ʼ����������ͨ��4
	GPIO_InitStruct.Pin = ENCODE_CH4_BIT;
	LL_GPIO_Init(ENCODE_CH4_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(ENCODE_CH4_PORT, ENCODE_CH4_BIT);
}


///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void EnCode_Timer_Init(void)
{
	//---ʹ�ܶ�ʱ��ʱ��
	TimerTask_Clock(ENCODE_USE_TIMER, 1);

	//---��ʱ���Ľṹ��
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };

	//---���ö�ʱ��Ϊȱʡ����
	LL_TIM_DeInit(ENCODE_USE_TIMER);

	//---�Զ�����ֵ
	TIM_InitStruct.Autoreload = ENCODE_TIMER_RELOAD;

	//---Ԥ��Ƶ��ֵ---�����������ʱ��Ƶ��---1MHz
	TIM_InitStruct.Prescaler = ENCODE_TIMER_ARR;//71
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;

	//---�ظ������Ĵ���
	TIM_InitStruct.RepetitionCounter = 0;

	//---��ʼ����ʱ��
	LL_TIM_Init(ENCODE_USE_TIMER, &TIM_InitStruct);

	//---��ʹ���Զ�����
	LL_TIM_DisableARRPreload(ENCODE_USE_TIMER);

	//--��ʱ��ʱ��ʹ���ڲ�ʱ��
	LL_TIM_SetClockSource(ENCODE_USE_TIMER, LL_TIM_CLOCKSOURCE_INTERNAL);

	//---��ģʽѡ��λ
	LL_TIM_SetTriggerOutput(ENCODE_USE_TIMER, LL_TIM_TRGO_RESET);

	//---��ʹ������ģʽ
	LL_TIM_DisableMasterSlaveMode(ENCODE_USE_TIMER);
	
	
	//---��ʱ���жϵȼ�
	NVIC_SetPriority(ENCODE_USE_TIMER_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

	//---ʹ�ܶ�ʱ���ж�
	NVIC_EnableIRQ(ENCODE_USE_TIMER_IRQ);

	//---ʹ�ܸ����ж�
	LL_TIM_EnableIT_UPDATE(ENCODE_USE_TIMER);

	//---ʹ�ܶ�ʱ��
	LL_TIM_EnableCounter(ENCODE_USE_TIMER);


}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� ����1KHz�ķ����źŵ�λ���
//////////////////////////////////////////////////////////////////////////////
void EnCode_SquareWave_1KHzBit( UINT8_T *pbyteCycleCode, UINT8_T codeIndex, UINT8_T mask )
{
	*( pbyteCycleCode + codeIndex * 8 + 0 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 1 ) |= mask;
	*( pbyteCycleCode + codeIndex * 8 + 2 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 3 ) |= mask;
	*( pbyteCycleCode + codeIndex * 8 + 4 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 5 ) |= mask;
	*( pbyteCycleCode + codeIndex * 8 + 6 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 7 ) |= mask;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� ����500Hz�ķ����źŵ�λ���
//////////////////////////////////////////////////////////////////////////////
void EnCode_SquareWave_500HzBit( UINT8_T *pbyteCycleCode, UINT8_T codeIndex, UINT8_T mask )
{
	*( pbyteCycleCode + codeIndex * 8 + 0 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 1 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 2 ) |= mask;
	*( pbyteCycleCode + codeIndex * 8 + 3 ) |= mask;
	*( pbyteCycleCode + codeIndex * 8 + 4 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 5 ) &= ( ~mask );
	*( pbyteCycleCode + codeIndex * 8 + 6 ) |= mask;
	*( pbyteCycleCode + codeIndex * 8 + 7 ) |= mask;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� ���������źŵĳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
void EnCode_SquareWave_Init( UINT8_T mode, UINT8_T* pbyteCycleCode, UINT8_T codeLength, UINT8_T mask )
{
	volatile UINT8_T i = 0;
	//---��䷽��֡Bitֵ
	for (i = 0;i < codeLength;i++)
	{
		if (mode == 1)
		{
			EnCode_SquareWave_1KHzBit( pbyteCycleCode, i, mask );
		}
		else
		{
			EnCode_SquareWave_500HzBit( pbyteCycleCode, i, mask );
		}
	}
	//---��䷽��ֹ֡ͣλ
	for (i = codeLength * 8;i < GEN_CODE_FRAME_LENGTH * 8;i++)
	{
		*( pbyteCycleCode + codeLength * 8 + i ) &= ( ~mask );
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� ����2262�źŵ�λ���
//////////////////////////////////////////////////////////////////////////////
void EnCode_2262Wave_Bit( UINT8_T* pGetCode, UINT8_T* pPutBitCode, UINT8_T codeIndex, UINT8_T mask )
{
	switch (*( pGetCode + codeIndex ))
	{
		case 0:	// 0��
			*( pPutBitCode + codeIndex * 8 + 0 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 1 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 2 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 3 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 4 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 5 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 6 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 7 ) &= ( ~mask );
			break;
		case 1:	// 1��
			*( pPutBitCode + codeIndex * 8 + 0 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 1 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 2 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 3 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 4 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 5 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 6 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 7 ) &= ( ~mask );
			break;
		case 2:	// ����
			*( pPutBitCode + codeIndex * 8 + 0 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 1 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 2 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 3 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 4 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 5 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 6 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 7 ) &= ( ~mask );
			break;
		case 3:
			*( pPutBitCode + codeIndex * 8 + 0 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 1 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 2 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 3 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 4 ) |= mask;
			*( pPutBitCode + codeIndex * 8 + 5 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 6 ) &= ( ~mask );
			*( pPutBitCode + codeIndex * 8 + 7 ) &= ( ~mask );
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� ����2262�źŵĳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
void EnCode_2262Wave_Init( UINT8_T* pGetCode, UINT8_T* pbyteCycleCode, UINT8_T codeLength, UINT8_T mask )
{
	volatile UINT8_T	i;
	//---���2262��Bitֵ
	for (i = 0;i < codeLength;i++)
	{
		EnCode_2262Wave_Bit( pGetCode, pbyteCycleCode, i, mask );
	}
	//---���2262֡λֵ
	*( pbyteCycleCode + codeLength * 8 ) |= mask;
	//---���2262ֹͣλ
	for (i = codeLength * 8;i < GEN_CODE_FRAME_LENGTH * 8;i++)
	{
		*( pbyteCycleCode + codeLength * 8 + i ) &= ( ~mask );
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void Encode_Init( void )
{
	UINT8_T frameIndex=0;

	//---ͨ���ĳ�ʼ��
	EnCode_GPIO_Init();

	//---��ʱ���ĳ�ʼ��
	EnCode_Timer_Init();

	//---λ��������
	pGenCodeByteCycleCode = g_GenCodeByteCycleCode;
	for (frameIndex = 0;frameIndex < GEN_CODE_FRAME_COUNT;frameIndex++)
	{
		if (g_GenCodeCH1[frameIndex].codeMode == 0)
		{
			EnCode_2262Wave_Init( g_GenCodeCH1[frameIndex].codeVal, pGenCodeByteCycleCode, g_GenCodeCH1[frameIndex].codeLength, ENCODE_CH1_INDEX );
		}
		else
		{
			EnCode_SquareWave_Init( g_GenCodeCH1[frameIndex].codeMode, pGenCodeByteCycleCode, g_GenCodeCH1[frameIndex].codeLength, ENCODE_CH1_INDEX );
		}
		pGenCodeByteCycleCode += GEN_CODE_FRAME_LENGTH * 8;
	}
	//---λ��������
	pGenCodeByteCycleCode = g_GenCodeByteCycleCode;
	for (frameIndex = 0;frameIndex < GEN_CODE_FRAME_COUNT;frameIndex++)
	{
		if (g_GenCodeCH2[frameIndex].codeMode == 0)
		{
			EnCode_2262Wave_Init( g_GenCodeCH2[frameIndex].codeVal, pGenCodeByteCycleCode, g_GenCodeCH2[frameIndex].codeLength, ENCODE_CH2_INDEX );
		}
		else
		{
			EnCode_SquareWave_Init( g_GenCodeCH2[frameIndex].codeMode, pGenCodeByteCycleCode, g_GenCodeCH2[frameIndex].codeLength, ENCODE_CH2_INDEX );
		}
		pGenCodeByteCycleCode += GEN_CODE_FRAME_LENGTH * 8;
	}
	//---λ��������
	pGenCodeByteCycleCode = g_GenCodeByteCycleCode;
	for (frameIndex = 0;frameIndex < GEN_CODE_FRAME_COUNT;frameIndex++)
	{
		if (g_GenCodeCH3[frameIndex].codeMode == 0)
		{
			EnCode_2262Wave_Init( g_GenCodeCH3[frameIndex].codeVal, pGenCodeByteCycleCode, g_GenCodeCH3[frameIndex].codeLength, ENCODE_CH3_INDEX );
		}
		else
		{
			EnCode_SquareWave_Init( g_GenCodeCH3[frameIndex].codeMode, pGenCodeByteCycleCode, g_GenCodeCH3[frameIndex].codeLength, ENCODE_CH3_INDEX );
		}
		pGenCodeByteCycleCode += GEN_CODE_FRAME_LENGTH * 8;
	}
	//---λ��������
	pGenCodeByteCycleCode = g_GenCodeByteCycleCode;
	for (frameIndex = 0;frameIndex < GEN_CODE_FRAME_COUNT;frameIndex++)
	{
		if (g_GenCodeCH4[frameIndex].codeMode == 0)
		{
			EnCode_2262Wave_Init( g_GenCodeCH4[frameIndex].codeVal, pGenCodeByteCycleCode, g_GenCodeCH4[frameIndex].codeLength, ENCODE_CH4_INDEX );
		}
		else
		{
			EnCode_SquareWave_Init( g_GenCodeCH4[frameIndex].codeMode, pGenCodeByteCycleCode, g_GenCodeCH4[frameIndex].codeLength, ENCODE_CH4_INDEX );
		}
		pGenCodeByteCycleCode += GEN_CODE_FRAME_LENGTH * 8;
	}
	pGenCodeByteCycleCode = g_GenCodeByteCycleCode;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� 
//////////////////////////////////////////////////////////////////////////////
void EnCode_Task( void )
{
	//ENCODE_BUS_OUT( 0x0F/*g_GenCodeByteCycleCode[g_GenCodeByteIndex++]*/);
	ENCODE_BUS_OUT(((g_GenCodeByteCycleCode[g_GenCodeByteIndex++]&g_GenCodeChannelMask1)|g_GenCodeChannelMask2));
	//---�����λ
	if (g_GenCodeByteIndex >= GEN_CODE_BYTE_OF_CYCLE_COUNT)
	{
		g_GenCodeByteIndex = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� 
//////��	   �ܣ� 
//////�������: 
//////�������: 
//////˵	   ���� 
//////////////////////////////////////////////////////////////////////////////
void EnCode_IRQTask( void )
{
	//---�����ж�
	if (LL_TIM_IsActiveFlag_UPDATE(ENCODE_USE_TIMER) != RESET)
	{
		EnCode_Task();
		//---����жϱ�־λ
		LL_TIM_ClearFlag_UPDATE(ENCODE_USE_TIMER);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ����ָ���ı���ͨ���Ƿ������빦��
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void EnCode_SetChannel(UINT8_T chIndex,UINT8_T isEnCode,UINT8_T isHigh)
{
	switch (chIndex)
	{
		case 1:
			//---ʹ�ܱ���
			if (isEnCode==1)
			{
				g_GenCodeChannelMask1 |= 0x01;
			}
			else
			{
				g_GenCodeChannelMask1 &= 0x0E;
			}

			//---��������ߵ�ƽ
			if (isHigh==1)
			{
				g_GenCodeChannelMask1 |= 0x01;
				g_GenCodeChannelMask2 |= 0x01;
			}
			else 
			{
				g_GenCodeChannelMask2 &= 0x0E;
			}
			break;
		case 2:
			//---ʹ�ܱ���
			if (isEnCode == 1)
			{
				g_GenCodeChannelMask1 |= 0x02;
			}
			else
			{
				g_GenCodeChannelMask1 &= 0x0D;
			}

			//---��������ߵ�ƽ
			if (isHigh == 1)
			{
				g_GenCodeChannelMask1 |= 0x02;
				g_GenCodeChannelMask2 |= 0x02;
			}
			else
			{
				g_GenCodeChannelMask2 &= 0x0D;
			}
			break;
		case 3:
			//---ʹ�ܱ���
			if (isEnCode == 1)
			{
				g_GenCodeChannelMask1 |= 0x04;
			}
			else
			{
				g_GenCodeChannelMask1 &= 0x0B;
			}

			//---��������ߵ�ƽ
			if (isHigh == 1)
			{
				g_GenCodeChannelMask1 |= 0x04;
				g_GenCodeChannelMask2 |= 0x04;
			}
			else
			{
				g_GenCodeChannelMask2 &= 0x0B;
			}
			break;
		case 4:
			//---ʹ�ܱ���
			if (isEnCode == 1)
			{
				g_GenCodeChannelMask1 |= 0x08;
			}
			else
			{
				g_GenCodeChannelMask1 &= 0x07;
			}

			//---��������ߵ�ƽ
			if (isHigh == 1)
			{
				g_GenCodeChannelMask1 |= 0x08;
				g_GenCodeChannelMask2 |= 0x08;
			}
			else
			{
				g_GenCodeChannelMask2 &= 0x07;
			}
			break;
		default:
			//---�ָ�Ĭ��ֵ
			g_GenCodeChannelMask1 = 0x0F;
			g_GenCodeChannelMask2 = 0X00;
			break;
	}
}