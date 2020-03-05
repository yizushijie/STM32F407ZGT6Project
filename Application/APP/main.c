#include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：系统时钟的配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void SystemClock_Config(void)
{
	//---设置FLASH的延时读取周期数
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
	//---等待FLASH延时设置完成---判断设置是否成功
	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
	{
		Error_Handler();
	}
	//---PWR时钟
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	//---设置内部调节器的输出电压
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	#if 1
		//---使能系统外部无源晶振
		LL_RCC_HSE_Enable();
	#else
		//---使能系统外部有源晶振
		LL_RCC_HSE_EnableBypass();
	#endif
	//---等待外部系统晶振稳定
	while (LL_RCC_HSE_IsReady() != 1)
	{
	}
	//---使能内部低频晶振
	LL_RCC_LSI_Enable();
	//---等待内部低频晶振稳定
	while (LL_RCC_LSI_IsReady() != 1)
	{
	}
	//---使能备份域的访问
	LL_PWR_EnableBkUpAccess();
	//---设置系统的PLL,用于配置系统的主时钟
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
		#error "外部晶振配置成错误，只支持8M和16M的配置!"
	#endif
	//---设置USB时钟
	//LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
	//---使能PLL
	LL_RCC_PLL_Enable();
	//---等待PLL稳定
	while (LL_RCC_PLL_IsReady() != 1)
	{
	}
	//---设置AHB总线时钟分频
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	//---设置APB1总线时钟分频
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	//---设置APB2总线时钟分频
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
	//---设置系统时钟
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	//--- 等待系统时钟稳定，即PLL锁定倍频之后的频率
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{
	}
	//LL_Init1msTick( 168000000 );
	//---设置系统滴答定时器的时钟为系统高速时钿--使能滴答定时器的时钟
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	//---设置系统时钟
	LL_SetSystemCoreClock(168000000);
	//---使能Flash的预读取功能
	LL_FLASH_EnablePrefetch();
	//---使能数据缓存功能
	LL_FLASH_EnableDataCache();
	//---使能指令高速缓存
	LL_FLASH_EnableInstCache();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void NVIC_Init(void)
{
	//---设置NVIC的分组模式
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Sys_Init(void)
{	
	//---系统时钟的初始化
	SystemClock_Config();	
	//---NVIC初始化
	NVIC_Init();
	//---自定义内存管理初始化
	MyMemInit();
	//---RTC的初始化
	SysRTCTask_RTCInit(pSysSoftRTC, 0,0,0);
	//---GPIO初始化
	GPIOTask_Init(SysTickTask_GetTick);
	//---滴答定时器初始化
	SysTickTask_Init();
	//---随机数初始化,禁用中断方式
	RandomTask_Init(0);
	//---CRC校验初始化
	CRCTask_Init();
	//---串口的初始化
	UARTTask_Init(pUart1, UART1_RX_MAX_SIZE, UART1_RX_BUFFER, UART_CRC_NONE, UART1_TX_MAX_SIZE, UART1_TX_BUFFER, UART_CRC_NONE, SysTickTask_GetTick);
   //---硬件初始化
	//HardWare_Init();
	//---初始化MCO的输出时钟
	//MCO1_Init();
	//---定时器初始化
	TimerTask_Init();
	//---外部中断初始化
	//EXTITask_Init();
	//---HMC5883的初始化
	//HMC5883Task_I2C_Init(pHmc5883Device0, DelayTask_us,DelayTask_ms, SysTickTask_GetTick, 0);
	//---AHT10的初始化
	//AHT10Task_I2C_Init(pAht10Device0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 0);
	//---初始化MPU6050
	MPU6050Task_I2C_Init(pMpu6050Device0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick, 1);
	//UINT8_T tempID = 0;
	//MPU6050Task_I2C_ReadChipID(pMpu6050Device0,&tempID);
	//---ISP的初始化
	//ISPTask_Init(pIspDevice0,DelayTask_us,DelayTask_ms, SysTickTask_GetTick);
	//---JTAG的初始化
	//JTAGTask_Init(pJtagDevice0, DelayTask_us, DelayTask_ms, SysTickTask_GetTick);
	//---WM8510
	//WM8510Task_I2C_Init(pWm8510Device0, DelayTask_us, SysTickTask_GetTick, 0);
	//---SI5351A
	//SI5351ATask_I2C_Init(pSi5351aDevice0, DelayTask_us, SysTickTask_GetTick, 0);
	//---指示灯的初始化
	//LEDTask_Init();	
	//---DAC的初始化
	//DACTask_Init(DAC_CHANNEL_SELECT_ALL, DAC_CHANNEL_ENABLE_BUFFER);
	//---数据总线的初始化
	//DataBus_Init();
	//---初始化LM317做的可调电源
	//LM317Task_Init(0,3000);
	//LM317_POWER_ON;
	//HMC5883Task_CalibrateMag(pHmc5883Device0);
	//---ADC初始化
	//ADCTask_ADC_Init();
	//ADCTask_ADCTask_START(ADC1);
	//---开启看门狗
	//IWDGTask_Init(pIWDG);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
int main(void)
{
	UINT8_T ch = 0;
	UINT16_T cnt = 0;
	//---系统初始化函数
	Sys_Init();
	//---主循环
	while (1)
	{
		
		//ADS8688_SPI_WriteProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, 0xFF);
		//ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_AUTO_SEQ_EN, &ads8688Tem[0]);
		//DelayTask_ms(100);
		//USART_Printf(pUSART1, "写入到SEQ_EN数据：%X \r\n", ads8688Tem[1]);
		//ADS8688_SPI_WriteProgramReg(pADS8688Device0, ADS8688_PROG_REG_FEATURE_SELECT, 0x28);
		//ADS8688_SPI_ReadProgramReg(pADS8688Device0, ADS8688_PROG_REG_FEATURE_SELECT, ads8688Tem);
		//USART_Printf(pUSART1, "写入到FEATURE_SELECT数据：%X \r\n", ads8688Tem[1]);
		//ADS868X_SPI_GetAutoRSTResult(pADS8688Device0, 8);
		/*
		ADS868X_SPI_GetAutoRSTNSampleResult(pADS868XDevice0, 8);
		for (ch  = 0; ch < 8; ch++)
		{
			USART_Printf(pUSART1, "ADCSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
			USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		}
		*/
		//ADS8688_SPI_GetManualChannelResult(pADS8688Device0, ADS8688_CMD_REG_MAN_CH_0);
		//USART_Printf(pUSART1, "采样次数:%d\r\n", cnt+1);
		//ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_0);
		//ch = 0;
		//USART_Printf(pUSART1, "数据格式:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		//USART_Printf(pUSART1, "平均求和的采样结果\r\n");
		//ADS869X_SPI_GetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0,0);
		////ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0);
		//ch = 0;
		//USART_Printf(pUSART1, "数据格式:%d\r\n", pADS869XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS869XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS869XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch + 1), pADS869XDevice0->msgChannelPowerResult[ch]);

		//USART_Printf(pUSART1, "卡尔曼滤波的采样结果\r\n");
		////ADS869X_SPI_GetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0);
		//ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(pADS869XDevice0, ADS869X_CMD_REG_MAN_CH_0,0);
		//ch = 0;
		//USART_Printf(pUSART1, "数据格式:%d\r\n", pADS869XDevice0->msgIsPositive[ch]);
		//USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS869XDevice0->msgChannelNowADCResult[ch]);
		//USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS869XDevice0->msgChannelOldADCResult[ch]);
		//USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch + 1), pADS869XDevice0->msgChannelPowerResult[ch]);
		/*
		ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_1);
		ch = 1;
		USART_Printf(pUSART1, "数据格式:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);
		
		ADS868X_SPI_GetManualChannelNSampleResult(pADS868XDevice0, ADS868X_CMD_REG_MAN_CH_2);
		ch = 2;
		USART_Printf(pUSART1, "数据格式:%d\r\n", pADS868XDevice0->msgIsPositive[ch]);
		USART_Printf(pUSART1, "ADCNowSampleResult:%d\r\n", pADS868XDevice0->msgChannelNowADCResult[ch]);
		USART_Printf(pUSART1, "ADCOldSampleResult:%d\r\n", pADS868XDevice0->msgChannelOldADCResult[ch]);
		USART_Printf(pUSART1, "通道%d电压:%7duV\r\n", (ch + 1), pADS868XDevice0->msgChannelPowerResult[ch]);*/
		//DelayTask_ms(300);
		////---在线调试命令
		//USARTTask_FuncTask(pUSART1,NULL);
		//---模拟RTC处理
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