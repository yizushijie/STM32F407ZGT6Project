#include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ϵͳʱ�ӵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void)
{
	//---����FLASH����ʱ��ȡ������
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
	//---�ȴ�FLASH��ʱ�������---�ж������Ƿ�ɹ�
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
	{
		Error_Handler();
	}
	//---PWRʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	//---�����ڲ��������������ѹ
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	#if 1
		//---ʹ��ϵͳ�ⲿ��Դ����
		LL_RCC_HSE_Enable();
	#else
		//---ʹ��ϵͳ�ⲿ��Դ����
		LL_RCC_HSE_EnableBypass();
	#endif
	//---�ȴ��ⲿϵͳ�����ȶ�
	while (LL_RCC_HSE_IsReady() != 1)
	{
	}
	//---ʹ���ڲ���Ƶ����
	LL_RCC_LSI_Enable();
	//---�ȴ��ڲ���Ƶ�����ȶ�
	while (LL_RCC_LSI_IsReady() != 1)
	{
	}
	//---ʹ�ܱ�����ķ���
	LL_PWR_EnableBkUpAccess();
	//---����ϵͳ��PLL,��������ϵͳ����ʱ��
	#if (HSE_VALUE==4000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_2, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==6000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_3, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==8000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==12000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_6, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==16000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==20000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_10, 168, LL_RCC_PLLP_DIV_2);
	#elif (HSE_VALUE==24000000UL)
		LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 168, LL_RCC_PLLP_DIV_2);
	#else
		#error "�ⲿ�������óɴ���ֻ֧��8M��16M������!"
	#endif
	//---����USBʱ��
	//LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
	//---ʹ��PLL
	LL_RCC_PLL_Enable();
	//---�ȴ�PLL�ȶ�
	while (LL_RCC_PLL_IsReady() != 1)
	{
	}
	//---����AHB����ʱ�ӷ�Ƶ
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	//---����APB1����ʱ�ӷ�Ƶ
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	//---����APB2����ʱ�ӷ�Ƶ
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
	//---����ϵͳʱ��
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	//--- �ȴ�ϵͳʱ���ȶ�����PLL������Ƶ֮���Ƶ��
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}
	//LL_Init1msTick( 168000000 );
	//---����ϵͳ�δ�ʱ����ʱ��Ϊϵͳ����ʱ��--ʹ�ܵδ�ʱ����ʱ��
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	//---����ϵͳʱ��
	LL_SetSystemCoreClock(168000000);
	//---ʹ��Flash��Ԥ��ȡ����
	LL_FLASH_EnablePrefetch();
	//---ʹ�����ݻ��湦��
	LL_FLASH_EnableDataCache();
	//---ʹ��ָ����ٻ���
	LL_FLASH_EnableInstCache();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void NVIC_Init(void)
{
	//---����NVIC�ķ���ģʽ
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	/* System interrupt init*/
	/* HardFault_IRQn interrupt configuration */
	#ifdef USE_MCU_STM32F1
		NVIC_SetPriority(HardFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	#endif
	/* MemoryManagement_IRQn interrupt configuration */
	NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* BusFault_IRQn interrupt configuration */
	NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* UsageFault_IRQn interrupt configuration */
	NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* SVCall_IRQn interrupt configuration */
	NVIC_SetPriority(SVCall_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* DebugMonitor_IRQn interrupt configuration */
	NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* PendSV_IRQn interrupt configuration */
	NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Sys_Init(void)
{	
	//---ϵͳʱ�ӵĳ�ʼ��
	SystemClock_Config();	
	//---NVIC��ʼ��
	NVIC_Init();
	//---�Զ����ڴ�����ʼ��
	MyMemInit();
	//---RTC�ĳ�ʼ��
	SysRTCTask_RTCInit(pSysSoftRTC, 0,0,0);
	//---GPIO��ʼ��
	GPIOTask_Init(SysTickTask_GetTick);
	//---�δ�ʱ����ʼ��
	SysTickTask_Init();
	//---�������ʼ��,�����жϷ�ʽ
	RandomTask_Init(0);
	//---CRCУ���ʼ��
	CRCTask_Init();
	//---���ڵĳ�ʼ��
	UARTTask_Init(pUart1, UART1_RX_MAX_SIZE, UART1_RX_BUFFER, UART_CRC_NONE, UART1_TX_MAX_SIZE, UART1_TX_BUFFER, UART_CRC_NONE, SysTickTask_GetTick);
   //---Ӳ����ʼ��
	//HardWare_Init();
	//---��ʼ��MCO�����ʱ��
	//MCO1_Init();
	//---��ʱ����ʼ��
	TimerTask_Init();
	//---�ⲿ�жϳ�ʼ��
	//EXTITask_Init();
	//---HMC5883�ĳ�ʼ��
	//HMC5883Task_I2C_Init(pHmc5883Device0, DelayTask_us,DelayTask_ms, SysTickTask_GetTick, 0);
	//---AHT10�ĳ�ʼ��
	//AHT10Task_I2C_Init(pAht10Device0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 0);
	//---��ʼ��MPU6050
	MPU6050Task_I2C_Init(pMpu6050Device0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 1);
	//UINT8_T tempID = 0;
	//MPU6050Task_I2C_ReadChipID(pMpu6050Device0,&tempID);
	//---ISP�ĳ�ʼ��
	//ISPTask_Init(pIspDevice0,DelayTask_us,DelayTask_ms, SysTickTask_GetTick);
	//---JTAG�ĳ�ʼ��
	//JTAGTask_Init(pJtagDevice0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick);
	//---WM8510
	//WM8510Task_I2C_Init(pWm8510Device0, DelayTask_us, SysTickTask_GetTick, 0);
	//---SI5351A
	//SI5351ATask_I2C_Init(pSi5351aDevice0, DelayTask_us, SysTickTask_GetTick, 0);
	//---ָʾ�Ƶĳ�ʼ��
	//LEDTask_Init();	
	//---DAC�ĳ�ʼ��
	//DACTask_Init(DAC_CHANNEL_SELECT_ALL, DAC_CHANNEL_ENABLE_BUFFER);
	//---�������ߵĳ�ʼ��
	//DataBus_Init();
	//---��ʼ��LM317���Ŀɵ���Դ
	//LM317Task_Init(0,3000);
	//LM317_POWER_ON;
	//HMC5883Task_CalibrateMag(pHmc5883Device0);
	//---ADC��ʼ��
	//ADCTask_ADC_Init();
	//ADCTask_ADCTask_START(ADC1);
	//---�������Ź�
	//IWDGTask_Init(pIWDG);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	UINT8_T ch = 0;
	UINT16_T cnt = 0;
	//---ϵͳ��ʼ������
	Sys_Init();
	//---��ѭ��
	while (1)
	{
		
		//ADS8688_SPI_WriteProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, 0xFF);
		//ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, &ads8688Tem[0]);
		//DelayTask_ms(100);
		//USART_Printf(pUSART1, "д�뵽SEQ_EN���ݣ�%X \r\n", ads8688Tem[1]);
		//ADS8688_SPI_WriteProgramReg(pADS8688Device0, ADS8688_PROG_REG_FEATURE_SELECT, 0x28);
		//ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_FEATURE_SELECT, ads8688Tem);
		//USART_Printf(pUSART1, "д�뵽FEATURE_SELECT���ݣ�%X \r\n", ads8688Tem[1]);
		//ADS868X_SPI_GetAutoRSTResult(pADS8688Device0, 8);
		/*
		ADS868X_SPI_GetAutoRSTNSampleResult(pADS868XDevice0, 8);
		for (ch  = 0; ch < 8; ch++)
		{
			USART_Printf(pUSART1, "ADCSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
			USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		}
		*/
		//ADS8688_SPI_GetManualChannelResult(pADS8688Device0, ADS8688_CMD_REG_MAN_CH_0);
		//USART_Printf(pUSART1, "��������:%d\r\n", cnt+1);
		//ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_0);
		//ch = 0;
		//USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		//USART_Printf(pUSART1, "ƽ����͵Ĳ������\r\n");
		//ADS869X_SPI_GetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0,0);
		////ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0);
		//ch = 0;
		//USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS869XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS869XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS869XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS869XDevice0->msgChannelPowerResult[ch]);

		//USART_Printf(pUSART1, "�������˲��Ĳ������\r\n");
		////ADS869X_SPI_GetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0);
		//ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0,0);
		//ch = 0;
		//USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS869XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS869XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS869XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS869XDevice0->msgChannelPowerResult[ch]);
		/*
		ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_1);
		ch = 1;
		USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		
		ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_2);
		ch = 2;
		USART_Printf(pUSART1, "���ݸ�ʽ:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		USART_Printf(pUSART1, "ͨ��%d��ѹ:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);*/
		//DelayTask_ms(300);
		////---���ߵ�������
		//USARTTask_FuncTask(pUSART1,NULL);
		//---ģ��RTC����
		SysRTCTask_RTCTask(pSysSoftRTC, SysTickTask_GetTick());	
		cnt++;
		if (cnt > 1000)
		{
			//DS1302Task_ReadRTC(pDS1302Device0);
			cnt = 0;
		}
		DelayTask_ms(100);
		UART_Printf(pUart1, "Data:%d\r\n", cnt);
		
		WDT_RESET();
	}
}