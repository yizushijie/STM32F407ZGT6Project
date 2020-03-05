#include "adc_cfg.h"

//===ȫ�ֱ����Ķ���
ADCASK_HandleType	g_ABChannelADC = { 0 };
pADCASK_HandleType	pABChannelADC = &g_ABChannelADC;
ADCASK_HandleType	g_CDChannelADC = { 0 };
pADCASK_HandleType	pCDChannelADC = &g_CDChannelADC;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_GPIO_Init(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOC, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��----
	//---ADCChannel10---PC0
	//---ADCChannel11---PC1
	//---ADCChannel12---PC2
	//---ADCChannel13---PC3
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0 ;//| LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3;			//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;														//---����״̬Ϊģ����������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;														//---���ö˿�����ʹ��
	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_Clock(ADC_TypeDef *ADCx, UINT8_T isEnable)
{
	if (ADCx == NULL)
	{
		return ERROR_1;
	}
	if (ADCx == ADC1)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ADC1);
		}
	}
#ifdef ADC2
	if (ADCx == ADC2)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ADC2);
		}
	}
#endif

#ifdef ADC3
	if (ADCx == ADC3)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC3);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ADC3);
		}
	}
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
UINT8_T ADC_ADC1_Init(void)
{
	LL_ADC_InitTypeDef ADC_InitStruct = { 0 };
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = { 0 };
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = { 0 };
	//---��ADC1ȫ���Ĵ�����������Ϊȱʡֵ
	LL_ADC_DeInit(ADC1);
	//---ʹ��ADC��ʱ��
	ADC_Clock(ADC1, 1);
#ifndef USE_MCU_STM32F1
	//---12λģʽ
	ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
#endif
	//---�����Ҷ���
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	//---��ͨ��ADC�ɼ���Ҫ����ɨ��ģʽ����ͨ��ADC�ɼ�����Ҫ����ɨ��ģʽ
	ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
	LL_ADC_Init(ADC1, &ADC_InitStruct);
	//---�������ģʽ
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	//---ɨ��ͨ������,��ͨ��ɨ��
	ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE; //LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
	//---����ͨ�����Ͻ��ü��ģʽ
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	//---����ת��ģʽ
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	//---ʹ��DMA����ʹ��DMA
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
#ifdef USE_MCU_STM32F1
	//---72M/6===12M(ADC��ʱ�Ӳ��ܳ���14MHz)
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);
#else
	//---ʱ��4��Ƶ
	ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV8;//LL_ADC_CLOCK_SYNC_PCLK_DIV4;
#endif
	//---����ģʽ
	ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
	//---�������
#ifndef USE_MCU_STM32F1	
	ADC_CommonInitStruct.MultiTwoSamplingDelay = LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES;
#endif
	LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);
	//---��һ��ת��ADC��ͨ��10
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_10);
	//---���ò�������
#ifdef USE_MCU_STM32F1
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_10, LL_ADC_SAMPLINGTIME_7CYCLES_5);
#else
	//---15����������
	//LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_10, LL_ADC_SAMPLINGTIME_15CYCLES);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_10, LL_ADC_SAMPLINGTIME_480CYCLES);
#endif
	/*
	//---�ڶ���ת��ADCͨ��11
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_11);
#ifdef USE_MCU_STM32F1
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_11, LL_ADC_SAMPLINGTIME_7CYCLES_5);
#else
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_11, LL_ADC_SAMPLINGTIME_15CYCLES);
#endif
	*/
	//---ʹ��װ��
	LL_ADC_Enable(ADC1);
	//---F1��ADC��ҪУ׼
#ifdef USE_MCU_STM32F1
	//---����У׼
	ADC_StartCalibration(ADC1);
#endif
	//LL_ADC_REG_StartConversionSWStart(ADC1);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ADCУ׼
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_StartCalibration(ADC_TypeDef *ADCx)
{
#ifdef USE_MCU_STM32F1
	//---��λУ׼
	if (ADCx != NULL)
	{
		//---��ʱ�ȴ�һ��
		//DelayTask_nop(LL_ADC_DELAY_ENABLE_CALIB_ADC_CYCLES * 32);
		//---��ʼ��У׼�Ĵ���
		SET_BIT(ADCx->CR2, ADC_CR2_RSTCAL);
		//---�ȴ�У׼���
		while ((READ_BIT(ADCx->CR2, ADC_CR2_RSTCAL) == (ADC_CR2_RSTCAL)));
		//---����У׼
		LL_ADC_StartCalibration(ADCx);
		//---�ȴ�У׼���
		while (LL_ADC_IsCalibrationOnGoing(ADCx) != 0);
		return OK_0;
	}
	return ERROR_1;
#else
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC1_DMA_Init(void)
{
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_0);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_0;
#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = ADC_CHANNEL_MAX_SIZE;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)&pABChannelADC->msgADCConvVal;
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T)&ADC1->DR;
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
#else
	//---��ʼ��DMA
	LL_DMA_Init(DMA2, LL_DMA_STREAM_0, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
#endif
	//---DMA��������ж�
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
#else
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_0);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������ADC��DMAģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC1_DMA_Restart(void)
{
	//---����DMA������
#ifdef USE_MCU_STM32F1
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, ADC_CHANNEL_MAX_SIZE);
	//---ʹ��DMA
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
#else
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_0, ADC_CHANNEL_MAX_SIZE);
	//---ʹ��DMA
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
#endif
	//---ʹ��װ��
	LL_ADC_Enable(ADC1);
	//---F1��ADC��ҪУ׼
#ifdef USE_MCU_STM32F1
	//---����У׼
	ADC_StartCalibration(ADC1);
#endif
	ADC_SoftStart(ADC1, NULL, NULL);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC1_DMA_Stop(void)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_ClearFlag_GI1(DMA1);
	//LL_DMA_ClearFlag_HT1(DMA1);
	//LL_DMA_ClearFlag_TC1(DMA1);
	LL_DMA_ClearFlag(DMA1, LL_DMA_CHANNEL_1);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_0);
	//LL_DMA_ClearFlag_HT0(DMA2);
	//LL_DMA_ClearFlag_TC0(DMA2);
	LL_DMA_ClearFlag(DMA2, LL_DMA_STREAM_0);
#endif
	//---ʹ��װ��
	LL_ADC_Disable(ADC1);
#ifndef USE_MCU_STM32F1
	//---�������жϱ�־λ
	LL_ADC_ClearFlag_OVR(ADC1);
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
UINT8_T ADC_ADC3_Init(void)
{
	LL_ADC_InitTypeDef ADC_InitStruct = { 0 };
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = { 0 };
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = { 0 };
	//---��ADC1ȫ���Ĵ�����������Ϊȱʡֵ
	LL_ADC_DeInit(ADC3);
	//---ʹ��ADC��ʱ��
	ADC_Clock(ADC3, 1);
#ifndef USE_MCU_STM32F1
	//---12λģʽ
	ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
#endif
	//---�����Ҷ���
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	//---��ͨ��ADC�ɼ���Ҫ����ɨ��ģʽ����ͨ��ADC�ɼ�����Ҫ����ɨ��ģʽ
	ADC_InitStruct.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
	LL_ADC_Init(ADC3, &ADC_InitStruct);
	//---�������ģʽ
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	//---ɨ��ͨ������
	ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS;
	//---����ͨ�����Ͻ��ü��ģʽ
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	//---����ת��ģʽ
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	//---ʹ��DMA����ʹ��DMA
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	LL_ADC_REG_Init(ADC3, &ADC_REG_InitStruct);

#ifdef USE_MCU_STM32F1
	//---72M/6===12M(ADC��ʱ�Ӳ��ܳ���14MHz)
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);
#else
	//---ʱ��4��Ƶ
	ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV4;
#endif
	//---����ģʽ
	ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
#ifndef USE_MCU_STM32F1
	//---�������
	ADC_CommonInitStruct.MultiTwoSamplingDelay = LL_ADC_MULTI_TWOSMP_DELAY_20CYCLES;
#endif
	//LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC3), &ADC_CommonInitStruct);
	LL_ADC_CommonInit(ADC3_COMMON, &ADC_CommonInitStruct);
	//---��һ��ת��ADC��ͨ��10
	LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_12);
#ifdef USE_MCU_STM32F1
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_12, LL_ADC_SAMPLINGTIME_28CYCLES_5);
#else
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_12, LL_ADC_SAMPLINGTIME_15CYCLES);
#endif
	//---�ڶ���ת��ADCͨ��11
	LL_ADC_REG_SetSequencerRanks(ADC3, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_13);
#ifdef USE_MCU_STM32F1
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_13, LL_ADC_SAMPLINGTIME_28CYCLES_5);
#else
	//---15����������
	LL_ADC_SetChannelSamplingTime(ADC3, LL_ADC_CHANNEL_13, LL_ADC_SAMPLINGTIME_15CYCLES);
#endif
	//---ʹ��װ��
	LL_ADC_Enable(ADC3);
	//---F1��ADC��ҪУ׼
#ifdef USE_MCU_STM32F1
	//---����У׼
	ADC_StartCalibration(ADC3);
#endif
	//LL_ADC_REG_StartConversionSWStart(ADC3);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC3_DMA_Init(void)
{
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA2, LL_DMA_CHANNEL_5);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_2;
#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = ADC_CHANNEL_MAX_SIZE;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)&pCDChannelADC->msgADCConvVal;;// (UINT32_T)ADC_ConvertedValue1;
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T)&ADC3->DR;
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(DMA2, LL_DMA_CHANNEL_5, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_5);
#else
	//---��ʼ��DMA
	LL_DMA_Init(DMA2, LL_DMA_STREAM_1, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_1);
#endif
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Channel4_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream1_IRQn);
#endif
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(DMA2, LL_DMA_CHANNEL_5);
#else
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_1);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������ADC��DMAģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC3_DMA_Restart(void)
{
#ifdef USE_MCU_STM32F1
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_5, ADC_CHANNEL_MAX_SIZE);
	//---ʹ��DMA
	LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_5);
#else
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_1, ADC_CHANNEL_MAX_SIZE);
	//---ʹ��DMA
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_1);
#endif
	//---ʹ��װ��
	LL_ADC_Enable(ADC3);
	//---F1��ADC��ҪУ׼
#ifdef USE_MCU_STM32F1
	//---����У׼
	ADC_StartCalibration(ADC3);
#endif
	ADC_SoftStart(NULL, NULL, ADC3);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC3_DMA_Stop(void)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_5);
	LL_DMA_ClearFlag_GI5(DMA2);
	LL_DMA_ClearFlag_HT5(DMA2);
	LL_DMA_ClearFlag_TC5(DMA2);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);
	LL_DMA_ClearFlag_HT1(DMA2);
	LL_DMA_ClearFlag_TC1(DMA2);
#endif
	//---ʹ��װ��
	LL_ADC_Disable(ADC3);
#ifndef USE_MCU_STM32F1
	//---�������жϱ�־λ
	LL_ADC_ClearFlag_OVR(ADC3);
#endif
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �������ADC��װ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_SoftStart(ADC_TypeDef *ADCx1, ADC_TypeDef *ADCx2, ADC_TypeDef *ADCx3)
{
	if (ADCx1 != NULL)
	{
		LL_ADC_REG_StartConversionSWStart(ADCx1);
	}
	if (ADCx2 != NULL)
	{
		LL_ADC_REG_StartConversionSWStart(ADCx2);
	}
	if (ADCx3 != NULL)
	{
		LL_ADC_REG_StartConversionSWStart(ADCx3);
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
UINT8_T ADC_ADC1Task_Init(void)
{
	ADC_ADC1_DMA_Init();
	ADC_ADC1_Init();
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC3Task_Init(void)
{
	ADC_ADC3_DMA_Init();
	ADC_ADC3_Init();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADCTask_Init(void)
{
	ADC_ADC1Task_Init();
	//ADC_ADC3Task_Init();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADC_Init(void)
{
	ADC_GPIO_Init();
	return ADC_ADCTask_Init();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADC_ADCTask_START(ADC_TypeDef *ADCx)
{
	if (ADCx == ADC1)
	{
		pABChannelADC->msgFlag = 0;
		//---����ADC������
		memset(pABChannelADC->msgADCConvVal, 0, ADC_CHANNEL_MAX_SIZE);
		//---����ADCװ��
		return ADC_ADC1_DMA_Restart();
	}
#ifdef ADC2
	if (ADCx == ADC2)
	{
		return OK_0;
	}
#endif
#ifdef ADC3
	if (ADCx == ADC3)
	{
		pCDChannelADC->msgFlag = 0;
		//---����ADC������
		memset(pCDChannelADC->msgADCConvVal, 0, ADC_CHANNEL_MAX_SIZE);
		//---����ADCװ��
		return ADC_ADC3_DMA_Restart();
	}
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
UINT8_T ADC_ADCTask_STOP(ADC_TypeDef *ADCx)
{
	if (ADCx == ADC1)
	{
		pABChannelADC->msgFlag += 1;
		return ADC_ADC1_DMA_Stop();
	}
#ifdef ADC2
	if (ADCx == ADC2)
	{
		return OK_0;
	}
#endif
#ifdef ADC3
	if (ADCx == ADC3)
	{
		pCDChannelADC->msgFlag += 1;
		return ADC_ADC3_DMA_Stop();
	}
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
UINT8_T ADC_HandleChannelVal(ADCASK_HandleType *ADCASKx)
{
	UINT8_T i = 0;
	UINT16_T adcAChannel[ADC_CHANNEL_SIZE] = { 0 };
	UINT16_T adcBChannel[ADC_CHANNEL_SIZE] = { 0 };
	UINT16_T *pADCVal = ADCASKx->msgADCConvVal;
	//---����ͨ�����ݵĻ�ȡ
	for (i = 0; i < ADC_CHANNEL_SIZE; i++)
	{
		//---ȡ��һ��ͨ����ֵ
		adcAChannel[i] = *pADCVal;
		pADCVal++;
		//---ȡ�ڶ���ͨ����ֵ
		//adcBChannel[i] = *pADCVal;
		//pADCVal++;
	}
	//---Aͨ�����ݽ�������
	DescSortWord(adcAChannel, ADC_CHANNEL_SIZE);
	//---Bͨ�����ݽ�������
	//DescSortFun2(adcBChannel, ADC_CHANNEL_SIZE);
	//---����Aͨ������ֵ
	ADCASKx->msgAChannelVal = CalcAvgWordFromIndex(adcAChannel, (ADC_CHANNEL_SIZE - 2), 2);
	//---����Bͨ������ֵ
	//ADCASKx->msgBChannelVal = CalcAvgFun1(adcBChannel, (ADC_CHANNEL_SIZE - 2), 2);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡͨ���ĵ�ѹֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T ADC_GetChipPower(void)
{
	UINT32_T tempPower=pABChannelADC->msgAChannelVal;
	//---�����װ��Ϊ��ѹֵ
	tempPower-=6;
	tempPower*=3260;
	tempPower<<=1;
	return (UINT16_T)(tempPower/4096);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡͨ���ĵ�ѹֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T ADC_GetHVPower(void)
{
	UINT32_T tempPower = pABChannelADC->msgAChannelVal;
	//---�����װ��Ϊ��ѹֵ
	tempPower -= 6;
	tempPower *= 3260;
	tempPower=(tempPower*9)/50;
	return (UINT16_T)(tempPower / 4096);
}