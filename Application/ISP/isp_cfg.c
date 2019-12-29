#include "isp_cfg.h"

//===ȫ�ֱ����Ķ���
ISP_HandlerType  g_IspDevice0 = { 0 };
pISP_HandlerType pIspDevice0 = &g_IspDevice0;

//===ͳһ���ͺ���
UINT8_T(*ISP_SEND_CMD)(ISP_HandlerType *, UINT8_T, UINT8_T, UINT8_T, UINT8_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_Device0_RST(UINT8_T rstState)
{
	if (rstState == ISP_RST_TO_GND)
	{
		RST_TO_GND;
	}
	else if (rstState == ISP_RST_TO_VCC)
	{
		RST_TO_VCC;
	}
	else
	{
		RST_TO_HZ;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_Device1_RST(UINT8_T rstState)
{
	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_Device2_RST(UINT8_T rstState)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_HW_Init(ISP_HandlerType *ISPx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(ISPx->msgSPI),1);	
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ISPx->msgSPI));
	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct={0};
	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;														//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;												//---8λ����	
	//---ʱ�ӿ���ʱ�ļ���
	if(ISPx->msgSPI.msgCPOL==0)
	{
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;											//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;										//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
	}	
	//---���ݲ�����ʱ�ӱ���λ��
	if (ISPx->msgSPI.msgCPOL == 0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}	
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;															//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;										//---ϵͳʱ��256��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;														//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;									//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	SPITask_MHW_PollMode_Init(&(ISPx->msgSPI), SPI_InitStruct);
	ISPx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SW_Init(ISP_HandlerType *ISPx)
{
	SPITask_DeInit(&(ISPx->msgSPI),1);
	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ISPx->msgSPI));
	//---ʱ�ӿ���ʱ�ļ���
	if (ISPx->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	}
	//---��Ƭѡ�ź�����ߵ�ƽ������˿ڶ�����͵�ƽ��Ĭ�ϵĳ�ʼ���Ǹߵ�ƽ����������Ҫ�Ķ�
	GPIO_OUT_0(ISPx->msgSPI.msgMOSI.msgGPIOPort, ISPx->msgSPI.msgMOSI.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgMISO.msgGPIOPort, ISPx->msgSPI.msgMISO.msgGPIOBit);
	ISPx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸0�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device0_Init(ISP_HandlerType *ISPx)
{
	//---�趨���״̬Ϊ����ģʽ
	ISPx->msgState=0;
	//---�趨��ʼ��״̬
	ISPx->msgInit = 0;
	//---�趨Ӳ����ʱ��
	ISPx->msgSetClok = ISP_SCK_DEFAULT_CLOCK;
	//---��ʼ��
	ISPx->msgDelayms = 0;
	//---��ʼ��
	ISPx->msgHideAddr = 0;
	//---����Ϊ��ʱģʽ
	ISPx->msgIsPollReady=0;
	//---����Eeprom��֧��ҳ���ģʽ
	ISPx->msgEepromIsPageMode=0;
	//---����Flashÿҳ���ֽ���
	ISPx->msgFlashPerPageWordSize=0;
	//---��ʼ�������������
	ISPx->msgPageWordIndex=0;
	//---������ѯʱ��
	ISPx->msgIntervalTime=ISP_STATE_TIME_OUT_MS;
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteByte, 0x00, 4);
	memset(ISPx->msgReadByte, 0x00, 4);
	//---��ƽת��ʹ�ܿ��ƶ�
#ifdef ISP_USE_lEVEL_SHIFT
    #ifdef ISP_USE_HV_RESET
	   ISPx->msgOE.msgGPIOPort=GPIOD;
	   ISPx->msgOE.msgGPIOBit = LL_GPIO_PIN_10;
	#else
	   ISPx->msgOE.msgGPIOPort=GPIOD;
	   ISPx->msgOE.msgGPIOBit = LL_GPIO_PIN_14;
    #endif
#endif
	//---�������
	/**SPI2 GPIO Configuration
	PB12   ------> SPI2_NSS
	PB13   ------> SPI2_SCK
	PB14   ------> SPI2_MISO
	PB15   ------> SPI2_MOSI
	*/
	//---��ѹ��
	/**SPI2 GPIO Configuration
	PB13   ------> SPI2_SCK
	PC2    ------> SPI2_MISO
	PC3    ------> SPI2_MOSI
	*/
	//---CS
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst = ISP_Device0_RST;
	//---SCK
	ISPx->msgSPI.msgSCK.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_13;
	//---MISO
	ISPx->msgSPI.msgMISO.msgGPIOPort = GPIOC;
	ISPx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_2;
	//---MOSI
	ISPx->msgSPI.msgMOSI.msgGPIOPort = GPIOC;
	ISPx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_3;
#else
	ISPx->msgSPI.msgCS.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_12;
	//---SCK
	ISPx->msgSPI.msgSCK.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_13;
	//---MISO
	ISPx->msgSPI.msgMISO.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_14;
	//---MOSI
	ISPx->msgSPI.msgMOSI.msgGPIOPort = GPIOB;
	ISPx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_15;
#endif
	
	//---����ģʽ
#ifndef USE_MCU_STM32F1
	ISPx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
#endif
	//---SPI���
	ISPx->msgSPI.msgSPIx = SPI2;
#ifndef USE_MCU_STM32F1
	//---SPI��Э��
	ISPx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
#endif	
	//---ʱ�ӿ���Ϊ�͵�ƽ
	ISPx->msgSPI.msgCPOL=0;
	//---���ݲ����ڵ�һ��ʱ�ӱ���
	ISPx->msgSPI.msgCPOH=0;	
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸1�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device1_Init(ISP_HandlerType *ISPx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸2�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device2_Init(ISP_HandlerType *ISPx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ISPx != NULL) && (ISPx == ISP_TASK_ONE))
	{
		ISP_Device0_Init(ISPx);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_TWO))
	{
		ISP_Device1_Init(ISPx);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_THREE))
	{
		ISP_Device2_Init(ISPx);
	}
	else
	{
		return ERROR_1;
	}
	//---ע��ms����ʱ����
	if (pFuncDelayms!=NULL)
	{
		ISPx->msgDelayms = pFuncDelayms;
	}
	else
	{
		ISPx->msgDelayms = DelayTask_ms;
	}
	//---ע��us��ʱ����
	if (pFuncDelayus!=NULL)
	{
		ISPx->msgSPI.msgDelayus = pFuncDelayus;
	}
	else
	{
		ISPx->msgSPI.msgDelayus = DelayTask_us;
	}
	//---ע��δ���
	if (pFuncTimerTick != NULL)
	{
		ISPx->msgSPI.msgTimeTick = pFuncTimerTick;
	}
	else
	{
		ISPx->msgSPI.msgTimeTick = SysTickTask_GetTick;
	}
	//---����OE�˿�
#ifdef ISP_USE_lEVEL_SHIFT
	if (ISPx->msgOE.msgGPIOPort != NULL)
	{
		//---ʹ��GPIO��ʱ��
		GPIOTask_Clock(ISPx->msgOE.msgGPIOPort, 1);
		//---GPIO�Ľṹ��
		LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;													//---����״̬Ϊ���ģʽ
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;											//---GPIO���ٶ�---�����豸
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;										//---���ģʽ---�������
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;														//---����
#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;													//---�˿ڸ���ģʽ
#endif
		//---ISP_OE_BIT�ĳ�ʼ��
		GPIO_InitStruct.Pin = ISPx->msgOE.msgGPIOBit;
		LL_GPIO_Init(ISPx->msgOE.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
	}
#endif
	//---��ǰʱ���
	ISPx->msgRecordTime=ISPx->msgSPI.msgTimeTick();
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ٳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_DeInit(ISP_HandlerType *ISPx)
{
	SPITask_DeInit(&(ISPx->msgSPI),1);
	ISPx->msgInit = 0;
	//---�����ѹ�˿���Ϣ
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst(ISP_RST_TO_HZ);
#endif
	//---�����ƽת��оƬ
#ifdef ISP_USE_lEVEL_SHIFT
	GPIO_OUT_1(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ٳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_AutoInit(ISP_HandlerType* ISPx)
{
	if (ISPx->msgSPI.msgModelIsHW != 0)
	{
		ISP_HW_Init(ISPx);
#ifdef USE_MCU_STM32
		//---���Ʊ�̵�����ٶȣ�С��1MHz��ע����������������ʹ�ã�һ��������ISP��ʱ�ӵȼ���һ��������Ӳ��SPI��ʱ��
		if (ISPx->msgSetClok > ISP_SCK_PRE_32)
		{
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV32;
		}
#endif
		//---����SPI��Ӳ��ʱ��
		SPITask_MHW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgClockSpeed);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_HW_SendCmd;
	}
	else
	{
		ISP_SW_Init(ISPx);
		//---�������ģ�������
		SPITask_MSW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgPluseWidth);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_SW_SendCmd;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ�ע��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_AutoDeInit(ISP_HandlerType* ISPx)
{
	//---ע����ǰ����������
	return	ISP_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ���̱��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SetClock(ISP_HandlerType *ISPx, UINT8_T clok)
{
	switch (clok)
	{
		case ISP_SCK_KHZ_0_5:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 1000;
			break;
		case ISP_SCK_KHZ_1:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 500;
			break;
		case ISP_SCK_KHZ_2:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 250;
			break;
		case ISP_SCK_KHZ_4:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 124;
			break;
		case ISP_SCK_KHZ_8:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 60;
			break;
		case ISP_SCK_KHZ_16:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 28;
			break;
		case ISP_SCK_KHZ_32:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 12;
			break;
		case ISP_SCK_KHZ_64:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 4;
			break;
		case ISP_SCK_KHZ_128	:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 3;
			break;
		case ISP_SCK_KHZ_256	:
			ISPx->msgSPI.msgModelIsHW  = 0;
			ISPx->msgSPI.msgPluseWidth = 0;
			break;
		case ISP_SCK_PRE_256:
			ISPx->msgSPI.msgModelIsHW  = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV256;
			break;
		case ISP_SCK_PRE_128:
			ISPx->msgSPI.msgModelIsHW  = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV128;
			break;
		case ISP_SCK_PRE_64:
			ISPx->msgSPI.msgModelIsHW  = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV64;
			break;
		case ISP_SCK_PRE_32:
			ISPx->msgSPI.msgModelIsHW  = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV32;
			break;
		case ISP_SCK_PRE_16:
		#ifdef USE_MCU_STM32
			ISPx->msgSPI.msgModelIsHW  = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV16;
		#endif
			break;
		case ISP_SCK_PRE_8:
			ISPx->msgSPI.msgModelIsHW  = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV8;
			break;
		case ISP_SCK_PRE_4:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV4;
			break;
		case ISP_SCK_PRE_2:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV2;
			break;
		default:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV256;
			break;
	}
	if (ISPx->msgSPI.msgModelIsHW == 1)
	{
		//---��һ����Ҫ��ʼ���˿ڣ������ģ�ⷽʽ�л���Ӳ����ʽ��Ҳ��Ҫ���³�ʼ��һ�¶˿�
		if ((ISPx->msgInit == 0) || (ISP_SEND_CMD == ISP_SW_SendCmd))
		{
			ISP_HW_Init(ISPx);
		}
	#ifdef USE_MCU_STM32
		//---���Ʊ�̵�����ٶȣ�С��1MHz��ע����������������ʹ�ã�һ��������ISP��ʱ�ӵȼ���һ��������Ӳ��SPI��ʱ��
		if (ISPx->msgSetClok > ISP_SCK_MAX_CLOCK)
		{
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV32;
		}
	#endif
		//---����SPI��Ӳ��ʱ��
		SPITask_MHW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgClockSpeed);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_HW_SendCmd;
	}
	else
	{
		//---��һ����Ҫ��ʼ���˿ڣ������Ӳ����ʽ�л���ģ�ⷽʽ��Ҳ��Ҫ���³�ʼ��һ�¶˿�
		if ((ISPx->msgInit == 0) || (ISP_SEND_CMD == ISP_HW_SendCmd))
		{
			ISP_SW_Init(ISPx);
		}
		//---�������ģ�������
		SPITask_MSW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgPluseWidth);
		//---���ݷ��������
		ISP_SEND_CMD = ISP_SW_SendCmd;
	}
#ifdef ISP_USE_lEVEL_SHIFT
	GPIO_OUT_0(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ù̶����ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clock)
{
	if(((clock<ISP_SCK_AUTO_MAX_COUNT)||(clock==ISP_SCK_AUTO_MAX_COUNT))&&(clock>0))
	{
		ISPx->msgAutoClock=1;
		ISPx->msgSetClok=clock;
	}
	else
	{
		ISPx->msgAutoClock = 0;
		//---�ָ�ΪĬ��ʱ��
		ISPx->msgSetClok = ISP_SCK_DEFAULT_CLOCK;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4)
{
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteByte, 0x00, 4);
	memset(ISPx->msgReadByte, 0x00, 4);
	//---��䷢�ͻ�����
	ISPx->msgWriteByte[0] = val1;
	ISPx->msgWriteByte[1] = Val2;
	ISPx->msgWriteByte[2] = val3;
	ISPx->msgWriteByte[3] = val4;
	//---���ݷ��ͣ���λ��ǰ
	return SPITask_MSW_WriteAndReadDataMSB(&(ISPx->msgSPI), ISPx->msgWriteByte, ISPx->msgReadByte, ISP_COMM_MAX_SIZE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_HW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4)
{
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteByte, 0x00, 4);
	memset(ISPx->msgReadByte, 0x00, 4);
	//---��䷢�ͻ�����
	ISPx->msgWriteByte[0] = val1;
	ISPx->msgWriteByte[1] = Val2;
	ISPx->msgWriteByte[2] = val3;
	ISPx->msgWriteByte[3] = val4;
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadData(&(ISPx->msgSPI), ISPx->msgWriteByte, ISPx->msgReadByte, ISP_COMM_MAX_SIZE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_PreEnterProg(ISP_HandlerType *ISPx)
{
	//---���ö˿�CS�˿�Ϊ���ģʽ
	GPIO_SET_WRITE(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	//---��������ʱ����
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst(ISP_RST_TO_GND);
#else
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
#endif
	//---�򿪵�Դ
	//POWER_DUT_ON;
	//---��������ʱ����
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst(ISP_RST_TO_GND);
#else
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
#endif
	ISPx->msgDelayms(1);
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst(ISP_RST_TO_VCC);
#else
	GPIO_OUT_1(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
#endif
	ISPx->msgDelayms(1);
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst(ISP_RST_TO_GND);
#else
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
#endif
	ISPx->msgDelayms(1);
	//---���64K������
	ISPx->msgHideAddr = 0xFF;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ģʽ
//////�������: isPollReady��0---��ʱģʽ��1---��ѯ׼�����ź�
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_EnterProg(ISP_HandlerType *ISPx,UINT8_T isPollReady)
{
	UINT8_T count = ISP_SCK_AUTO_MAX_COUNT;
	//---����ʱ��
	ISP_SetClock(ISPx, ISPx->msgSetClok);
	//---���ģʽ׼��
	ISP_PreEnterProg(ISPx);
	//---�Զ���ȡ���ʵ��ٶ�
	while (count--)
	{
		//---���ͱ������
		ISP_SEND_CMD(ISPx, 0xAC, 0x53, 0x00, 0x00);
		//---����Ƿ����ɹ�
		if (ISPx->msgReadByte[2] == 0x53)
		{
			//---���״̬Ϊ���ģʽ
			ISPx->msgState = 1;
			//---���ò�ѯ׼�����źŵı�־
			ISPx->msgIsPollReady=isPollReady;
			//---���Ӽ�غ���
			ISP_AddWatch(ISPx);
			return OK_0;
		}
		//---У���Ƿ����Զ�����ģʽ
		if (ISPx->msgAutoClock==0)
		{
			//---�Զ����ٴ���
			if (ISPx->msgSetClok >ISP_SCK_KHZ_2)
			{
				//---���ٴ���
				ISPx->msgSetClok -= 1;
			}
			else
			{
				//---�������ʱ��
				ISPx->msgSetClok = ISP_SCK_KHZ_2;
			}
		}
		else
		{
			count-=1;
		}
		//---����ʱ��
		ISP_SetClock(ISPx, ISPx->msgSetClok);
		//---��λʱ���ߺ�Ƭѡ��
		//GPIO_OUT_1(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
#ifdef ISP_USE_HV_RESET
		ISPx->msgPortRst(ISP_RST_TO_VCC);
#else
		GPIO_OUT_1(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
#endif
		ISPx->msgDelayms(1);
		//---����ʱ���ߺ�Ƭѡ��
		//GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
#ifdef ISP_USE_HV_RESET
		ISPx->msgPortRst(ISP_RST_TO_GND);
#else
		GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
#endif
		ISPx->msgDelayms(1);
	}
	//---����RST�˿�δHZ״̬�������ѹ����
#ifdef ISP_USE_HV_RESET
	ISPx->msgPortRst(ISP_RST_TO_HZ);
#endif 
#ifdef ISP_USE_lEVEL_SHIFT
	GPIO_OUT_1(ISPx->msgOE.msgGPIOPort, ISPx->msgOE.msgGPIOBit);
#endif
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ExitProg(ISP_HandlerType *ISPx)
{
	ISP_DeInit(ISPx);
	//---�Զ����ʱ��У��
	if (ISPx->msgAutoClock==0)
	{
		//---�ָ�ʱ�ӵ��ٶ�
		ISPx->msgSetClok = ISP_SCK_DEFAULT_CLOCK;
	}
	//---���Eepromҳ���ģʽ
	ISPx->msgEepromIsPageMode = 0;
	//---������ݻ����������
	ISPx->msgPageWordIndex = 0;
	//---���64K������
	ISPx->msgHideAddr = 0xFF;
	//---���״̬Ϊ����ģʽ
	ISPx->msgState=0;
	//---����̽���ģʽ����Ϊ��ʱ�ȴ�
	ISPx->msgIsPollReady=0;
	//---�Ƴ�ע��ļ�غ���
	ISP_RemoveWatch(ISPx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_WatchTask(ISP_HandlerType* ISPx)
{
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	if (ISPx->msgState!=0)
	{
		//---��ȡ��ǰʱ�����
		nowTime= ISPx->msgSPI.msgTimeTick();
		//---����ʱ����
		if (ISPx->msgRecordTime > nowTime)
		{
			cnt = (0xFFFFFFFF - ISPx->msgRecordTime + nowTime);
		}
		else
		{
			cnt = nowTime - ISPx->msgRecordTime;
		}
		//if (cnt > ISP_STATE_TIME_OUT_MS)
		//---����Ƿ�����ʱ�¼�
		if (cnt>ISPx->msgIntervalTime)
		{
			ISP_ExitProg(ISPx);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸1�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_AddWatchDevice0(void)
{
	ISP_WatchTask(ISP_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸2�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_AddWatchDevice1(void)
{
	ISP_WatchTask(ISP_TASK_TWO);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸3�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ISP_AddWatchDevice2(void)
{
	ISP_WatchTask(ISP_TASK_THREE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���Ӽ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_AddWatch(ISP_HandlerType* ISPx)
{
	UINT8_T _return=OK_0;
	if (ISPx!=NULL)
	{
		//---ˢ��ʱ��
		_return=ISP_RefreshWatch(ISPx);
		//---ʹ�õ�ISP�Ķ˿�,��ע����Ӧ��������
		if (ISPx == ISP_TASK_ONE)
		{
			SysTickTask_CreateTickTask(ISP_AddWatchDevice0);
		}
		else if (ISPx == ISP_TASK_TWO)
		{
			SysTickTask_CreateTickTask(ISP_AddWatchDevice1);
		}
		else if (ISPx == ISP_TASK_THREE)
		{
			SysTickTask_CreateTickTask(ISP_AddWatchDevice2);
		}
		else
		{
			_return= ERROR_1;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Ƴ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_RemoveWatch(ISP_HandlerType* ISPx)
{
	//---ʹ�õ�ISP�Ķ˿�
	if ((ISPx != NULL) && (ISPx == ISP_TASK_ONE))
	{
		SysTick_DeleteTickTask(ISP_AddWatchDevice0);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_TWO))
	{
		SysTick_DeleteTickTask(ISP_AddWatchDevice1);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_THREE))
	{
		SysTick_DeleteTickTask(ISP_AddWatchDevice2);
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ˢ�¼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_RefreshWatch(ISP_HandlerType* ISPx)
{
	//---������ѵ���Ϊ���ֵ����λ��ms
	ISPx->msgIntervalTime = ISP_STATE_TIME_OUT_MS;
	//---ˢ�¼�¼ʱ��
	ISPx->msgRecordTime = ISPx->msgSPI.msgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ü��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SetIntervalTime(ISP_HandlerType* ISPx,UINT16_T intervalTime)
{
	//---������ѵ���ʱ�䣬��λ��ms
	ISPx->msgIntervalTime= intervalTime;
	//---ˢ�¼�¼ʱ��
	ISPx->msgRecordTime = ISPx->msgSPI.msgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T ISP_GetIntervalTime(ISP_HandlerType* ISPx)
{
	return ISPx->msgIntervalTime;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ׼���ñ�־λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadReady(ISP_HandlerType *ISPx)
{
	UINT8_T _return = 0;
	//---��ȡʱ���ǩ
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT64_T cnt = 0;
	if (ISPx->msgSPI.msgTimeTick != NULL)
	{
		//nowTime = ISPx->msgSPI.msgFuncTick();
		oldTime = ISPx->msgSPI.msgTimeTick();
	}
	//---��ѯæ��־λ
	while (1)
	{
		//---���Ͷ�ȡæ��־������
		_return = ISP_SEND_CMD(ISPx, 0xF0, 0x00, 0x00, 0x00);
		//---����Ƿ��ȡ��æ��־
		if (_return)
		{
			break;
		}
		else
		{
			if ((ISPx->msgReadByte[3] & 0x01) == 0x00)
			{
				_return = OK_0;
				break;
			}
			else
			{
				if (ISPx->msgSPI.msgTimeTick != NULL)
				{
					//---��ǰʱ��
					nowTime = ISPx->msgSPI.msgTimeTick();
					//---�жϵδ�ʱ�Ƿ����������
					if (nowTime < oldTime)
					{
						cnt = (0xFFFFFFFF - oldTime + nowTime);
					}
					else
					{
						cnt = nowTime - oldTime;
					}
					//---�ж��Ƿ�ʱ
					if (cnt > 100)
					{
						//---���ͷ�����ʱ����
						_return = ERROR_2;
						break;
					}
				}
				else
				{
					nowTime++;
					if (nowTime > 100000)
					{
						//---���ͷ�����ʱ����
						_return = ERROR_3;
						break;
					}
				}
			}
		}
		WDT_RESET();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_EraseChip(ISP_HandlerType *ISPx)
{
	UINT8_T _return = 0;
	//---���Ͳ�������
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0x80, 0x00, 0x00);
	if (_return == 0)
	{
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady!=0)
		{
			_return = ISP_ReadReady(ISPx);
			_return+=0x80;
		}
		else
		{
			//---����֮��ĵȴ���ʱ
			ISPx->msgDelayms(10 + ISPx->msgWaitms);
		}
		
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	for (i = 0; i < 3; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0x30, 0x00, i, 0x0);
		if (_return != 0)
		{
			_return = (i + 2);
			break;
		}
		pVal[i] = ISPx->msgReadByte[3];
	}
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0x38, 0x00, i, 0x00);
		if (_return != 0)
		{
			_return = (i + 2);
			break;
		}
		pVal[i] = ISPx->msgReadByte[3];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = 0;
	//---��ȡ��˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0x50, 0x00, 0x00, 0x00);
	if (_return != 0x00)
	{
		return ERROR_2;
	}
	//---�����λֵ
	*(pVal++) = ISPx->msgReadByte[3];
	//---��ȡ��˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0x58, 0x08, 0x00, 0x00);
	if (_return != 0x00)
	{
		return ERROR_3;
	}
	//---�����λֵ
	*(pVal++) = ISPx->msgReadByte[3];
	//---��ȡ��˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---��ȡ��˿����չλֵ
		_return = ISP_SEND_CMD(ISPx, 0x50, 0x08, 0x00, 0x00);
		//---������չλֵ
		*(pVal) = ISPx->msgReadByte[3];
	}
	else
	{
		*pVal = 0xFF;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	//---��ȡ����λ
	UINT8_T _return = ISP_SEND_CMD(ISPx, 0x58, 0x00, 0x00, 0x00);
	*(pVal) = ISPx->msgReadByte[3];
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡROMҳ��Ϣ
//////�������:	pVal---���ݻ�����
//////			addr---���ݵ�ַ����ַ���ֵ�ַ
//////			length---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ��ȣ��ڲ�������ֳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	//---�ж����ݳ����Ƿ���ż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---��ȡROMҳ��Ϣ
	for (i = 0; i < length; i++)
	{
		//---ROMҳ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x30, 0x00, (addr + i), 0x00);
		if (_return != 0)
		{
			return ERROR_3;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
		//---ROMҳ���ֽ�����
		_return = ISP_SEND_CMD(ISPx, 0x38, 0x00, (addr + i), 0x00);
		if (_return != 0)
		{
			return 4;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ,���˳�������ǵ�λ����λ����չλ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = 0;
	//---д����˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA0, 0x00, pVal[0]);
	if (_return != 0x00)
	{
		return ERROR_2;
	}
	//---�����ѯ��ʽ
	if (ISPx->msgIsPollReady != 0)
	{
		_return = ISP_ReadReady(ISPx);
		_return += 0x80;
	}
	else
	{
		//---д��֮����ʱ�ȴ�
		ISPx->msgDelayms(5 + ISPx->msgWaitms);
	}
	//---д����˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA8, 0x00, pVal[1]);
	if (_return != 0x00)
	{
		return ERROR_3;
	}
	//---�����ѯ��ʽ
	if (ISPx->msgIsPollReady != 0)
	{
		_return = ISP_ReadReady(ISPx);
		_return += 0x80;
	}
	else
	{
		//---д��֮����ʱ�ȴ�
		ISPx->msgDelayms(5 + ISPx->msgWaitms);
	}
	//---д����˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---д����չλ
		_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA4, 0x00, pVal[2]);
		//---�ж�д���Ƿ�ɹ�
		if (_return == OK_0)
		{
			//---�����ѯ��ʽ
			if (ISPx->msgIsPollReady != 0)
			{
				_return = ISP_ReadReady(ISPx);
				_return += 0x80;
			}
			else
			{
				//---д��֮����ʱ�ȴ�
				ISPx->msgDelayms(5 + ISPx->msgWaitms);
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T val)
{
	//---д�����λ
	UINT8_T _return = ISP_SEND_CMD(ISPx, 0xAC, 0xE0, 0x00, val|0xC0);
	//---�ж�д���Ƿ�ɹ�
	if (_return == OK_0)
	{
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady != 0)
		{
			_return = ISP_ReadReady(ISPx);
			_return += 0x80;
		}
		else
		{
			//---д��֮����ʱ�ȴ�
			ISPx->msgDelayms(5 + ISPx->msgWaitms);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:  pVal	---���ݻ�����
//////			highAddr---���ݵ�ַ�ĸ��ֽڣ���ַ���ֽڵ�ַ
//////			lowAddr ---���ݵ�ַ�ĵ��ֽڣ���ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0xA0, highAddr, lowAddr, 0x00);
		if (_return != OK_0)
		{
			break;
		}
		//---�����ȡ������
		*(pVal++) = ISPx->msgReadByte[3];
		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:  pVal	---���ݻ�����
//////			addr	---���ݵ�ַ����ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_ReadChipEepromAddr(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:  pVal	---���ݻ�����
//////			highAddr---���ݵ�ַ�ĸ��ֽڣ���ַ���ֽڵ�ַ
//////			lowAddr ---���ݵ�ַ�ĵ��ֽڣ���ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T refreshFlag=0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0xC0, highAddr, lowAddr, pVal[i]);
		if (_return != OK_0)
		{
			break;
		}
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady != 0)
		{
			_return = ISP_ReadReady(ISPx);
			//_return += 0x80;
		}
		else
		{
			//---д��֮����ʱ�ȴ�
			ISPx->msgDelayms(10 + ISPx->msgWaitms);
		}
		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
		}
		refreshFlag++;
		//---��������������ʱ�ȴ���ʱ���˳��˱��ģʽ
		if (refreshFlag>20)
		{
			refreshFlag=0;
			//---ˢ��ʱ��
			ISP_RefreshWatch(ISPx);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����´洢���Ļ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	//---��仺����
	for (i = 0; i < ISPx->msgEerpomPerPageByteSize; i++)
	{
		//---������д�뻺����
		_return = ISP_SEND_CMD(ISPx, 0xC1, 0x00, i, *(pVal++));
		//---У��д����
		if (_return != 0x00)
		{
			return ERROR_3;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ��ҳ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipEepromAddr(ISP_HandlerType* ISPx,UINT8_T highAddr, UINT8_T lowAddr)
{
	UINT8_T _return = OK_0;
	//---������д��洢��ָ����ҳ
	_return = ISP_SEND_CMD(ISPx, 0xC2, highAddr, lowAddr, 0x00);
	//---У��д����
	if (_return == OK_0)
	{
		//---�����ѯ��ʽ
		if (ISPx->msgIsPollReady != 0)
		{
			_return = ISP_ReadReady(ISPx);
			_return += 0x80;
		}
		else
		{
			//---д��֮����ʱ�ȴ�
			ISPx->msgDelayms(10 + ISPx->msgWaitms);
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
UINT8_T ISP_UpdateChipEepromLongAddr(ISP_HandlerType* ISPx, UINT16_T addr)
{
	return ISP_UpdateChipEepromAddr(ISPx, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:  pVal	---���ݻ�����
//////			addr	---���ݵ�ַ����ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromAddr(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	UINT8_T _return = OK_0;
	UINT32_T pageAddr = 0;
	UINT16_T i = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---�����̵�ҳ��
		pageNum /= (ISPx->msgEerpomPerPageByteSize);
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---�����ַ������Eeprom��˵���ֵ�ַҲ���ֽڵ�ַ
		pageAddr = highAddr;
		pageAddr = (pageAddr << 8) + lowAddr;
		//---��ҳ���Eeprom����
		for (i = 0; i < pageNum; i++)
		{
			//---������ݻ���
			_return = ISP_UpdateChipEepromPage(ISPx, pVal);
			//---���㷵�ؽ��
			_return = (_return == OK_0 ? OK_0 : ERROR_2);
			//---�������ݵ�ָ����ҳ��ַ
			_return = ISP_UpdateChipEepromLongAddr(ISPx, pageAddr);
			//---���㷵�ؽ��
			_return = (_return == OK_0 ? OK_0 : ERROR_3);
			//---У��ҳ��̵Ľ��
			if (_return != OK_0)
			{
				//---�����˳����
				_return = ERROR_4;
				break;
			}
			else
			{
				//---�����ַƫ��
				pageAddr += ISPx->msgEerpomPerPageByteSize;
				//---���ݵ�ַƫ��
				pVal += ISPx->msgEerpomPerPageByteSize;
			}
		}
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ձ��EEPROM
//////�������:  pVal	---���ݻ�����
//////			highAddr---���ݵ�ַ�ĸ��ֽڣ���ַ���ֽڵ�ַ
//////			lowAddr ---���ݵ�ַ�ĵ��ֽڣ���ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		�������д��������ǿ����ݣ���ô������д��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pVal[i] != 0xFF)
		{
			_return = ISP_SEND_CMD(ISPx, 0xC0, highAddr, lowAddr, pVal[i]);
			if (_return != OK_0)
			{
				break;
			}
			//---�����ѯ��ʽ
			if (ISPx->msgIsPollReady != 0)
			{
				_return = ISP_ReadReady(ISPx);
				_return += 0x80;
			}
			else
			{
				//---д��֮����ʱ�ȴ�
				ISPx->msgDelayms(10 + ISPx->msgWaitms);
			}
		}
		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ձ��EEPROM
//////�������:  pVal	---���ݻ�����
//////			addr	---���ݵ�ַ����ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEeprom(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	//---У����ģʽ
	if (ISPx->msgEepromIsPageMode != 0)
	{
		//---���ָ��λ�õ�Eeprom����,���ģʽҳģʽ
		return ISP_WriteChipEepromPage(ISPx,pVal,highAddr,lowAddr, pageNum);
	}
	else
	{
		//---���ָ��λ�õ�Eeprom���ݣ����ģʽ��ģʽ
		return ISP_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, pageNum);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������: addr---������չλ��ַ����ַ���ֵ�ַ
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr)
{
	UINT8_T _return = OK_0;
	if (ISPx->msgHideAddr != addr)
	{
		ISPx->msgHideAddr = addr;
		_return = ISP_SEND_CMD(ISPx, 0x4D, 0x00, addr, 0x00);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateExternAddr(ISPx, (UINT8_T)(addr >> 16));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ַ��ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---������չλ
	if (externAddr!=0)
	{
		_return = ISP_UpdateExternAddr(ISPx, externAddr);
		if (_return != OK_0)
		{
			return ERROR_3;
		}
	}
	//---һ�ζ�ȡ����
	for (i = 0; i < length; i++)
	{
		//---��ȡ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x20, highAddr, lowAddr, 0x00);
		if (_return != OK_0)
		{
			return ERROR_4;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
		//---��ȡ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x28, highAddr, lowAddr, 0x00);
		if (_return != 0x00)
		{
			return ERROR_5;
		}
		else
		{
			*(pVal++) = ISPx->msgReadByte[3];
		}
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
			if (highAddr == 0x00)
			{
				externAddr++;
				//---������չλ
				_return = ISP_UpdateExternAddr(ISPx, externAddr);
				if (_return != 0x00)
				{
					return ERROR_6;
				}
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ַ��ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return  ISP_ReadChipFlashAddr(ISPx, pVal, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����Flash������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashPage(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0x00)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---��仺����
	for (i = 0; i < length; i++)
	{
		//---���µ�λ��ַ�Ļ�����
		_return = ISP_SEND_CMD(ISPx, 0x40, 0x00, (index + i), *(pVal++));
		if (_return != 0x00)
		{
			return ERROR_3;
		}
		//---���¸�λ��ַ�Ļ�����
		_return = ISP_SEND_CMD(ISPx, 0x48, 0x00, (index + i), *(pVal++));
		if (_return != 0x00)
		{
			return ERROR_4;
		}
	}
	//---���»���������ţ�
	ISPx->msgPageWordIndex+=length;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ��ҳ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	UINT8_T _return = OK_0;
	if (externAddr!=0)
	{
		_return= ISP_UpdateExternAddr(ISPx, externAddr);
	}	
	if (_return == OK_0)
	{
		_return = ISP_SEND_CMD(ISPx, 0x4C, highAddr, lowAddr, 0x00);
		if (_return == OK_0)
		{
			//---�����ѯ��ʽ
			if (ISPx->msgIsPollReady != 0)
			{
				_return = ISP_ReadReady(ISPx);
				_return += 0x80;
			}
			else
			{
				//---д��֮����ʱ�ȴ�
				ISPx->msgDelayms(5 + ISPx->msgWaitms);
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ��ҳ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateChipFlashAddr(ISPx, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳģʽ��ָ��������д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipFlashPage(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT32_T pageAddr = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---������ݻ���
		_return = ISP_UpdateChipFlashPage(ISPx, pVal, (UINT8_T)ISPx->msgPageWordIndex, length);
		//---���㷵�ؽ��
		_return = (_return == OK_0 ? OK_0 : ERROR_1);
		//---������������ִ������д�����
		if ((_return == OK_0) && (ISPx->msgPageWordIndex == ISPx->msgFlashPerPageWordSize))
		{
			//---�����ֵ�ַ������ĵ�ַ���ֵ�ַ
			pageAddr = externAddr;
			pageAddr = (pageAddr << 8) + highAddr;
			pageAddr = (pageAddr << 8) + lowAddr;
			//---�������ݵ�ָ����ҳ��ַ
			_return = ISP_UpdateChipFlashLongAddr(ISPx, pageAddr);
			//---���ݻ�������
			ISPx->msgPageWordIndex = 0;
			//---���㷵�ؽ��
			_return = (_return == OK_0 ? OK_0 : ERROR_2);
		}
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У��Flash�����Ƿ�Ϊ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_CheckChipFlashEmpty(ISP_HandlerType* ISPx,UINT8_T pageByteSizeH,UINT8_T pageByteSizeL,UINT8_T pageNumH,UINT8_T pageNumL)
{
	UINT8_T _return = OK_0;
	UINT16_T length=0;
	UINT16_T pageNum=0;
	UINT16_T i=0;
	UINT32_T addr=0;
	//---����ÿҳ�ֽ���
	length=pageByteSizeH;
	length=(length<<8)+pageByteSizeL;
	//---����ҳ��
	pageNum=pageNumH;
	pageNum=(pageNum<<8)+pageNumL;
	//---�����ڴ�
	UINT8_T *pFlashBuffer= (UINT8_T*)MyMalloc(length);
	//---�жϻ���ռ������Ƿ�ɹ�
	if (pFlashBuffer == NULL)
	{
		_return = ERROR_1;
		goto GoToExit;
	}
	for (i=0;i<pageNum;i++)
	{
		_return=ISP_ReadChipFlashLongAddr(ISPx,pFlashBuffer,addr,length);
		if (_return!=OK_0)
		{
			_return=ERROR_2;
			goto GoToExit;
		}
		//---У�������Ƿ�ȫ��Ϊ0xFF
		_return=CompareByte(pFlashBuffer,0xFF,length);
		if (_return!=OK_0)
		{
			_return = ERROR_3;
			goto GoToExit;
		}
		//---�����ַƫ��
		addr+=(length>>1);
	}
	//---�˳����
GoToExit:
	//---�ͷŻ���ռ�
	MyFree(pFlashBuffer);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У��Eeprom�����Ƿ�Ϊ��,����Ҳ��С
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_CheckChipFlashEmptyLong(ISP_HandlerType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return ISP_CheckChipFlashEmpty(ISPx,(UINT8_T)(pageByteSize>>8),(UINT8_T)(pageByteSize),(UINT8_T)(pageNum>>8),(UINT8_T)(pageNum));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У��Eeprom�����Ƿ�Ϊ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_CheckChipEepromEmpty(ISP_HandlerType* ISPx, UINT8_T byteSize, UINT8_T num)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT16_T addr = 0;
	//---�����ڴ�
	UINT8_T* pEepromBuffer = (UINT8_T*)MyMalloc(byteSize);
	//---�жϻ���ռ������Ƿ�ɹ�
	if (pEepromBuffer == NULL)
	{
		_return = ERROR_1;
		goto GoToExit;
	}
	for (i = 0; i < num; i++)
	{
		_return = ISP_ReadChipEepromLongAddr(ISPx, pEepromBuffer, addr, byteSize);
		if (_return != OK_0)
		{
			_return = ERROR_2;
			goto GoToExit;
		}
		//---У�������Ƿ�ȫ��Ϊ0xFF
		_return = CompareByte(pEepromBuffer, 0xFF, byteSize);
		if (_return != OK_0)
		{
			_return = ERROR_3;
			goto GoToExit;
		}
		//---�����ַƫ��
		addr += byteSize;
	}
	//---�˳����
GoToExit:
	//---�ͷŻ���ռ�
	MyFree(pEepromBuffer);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����������Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SetConfigInfo(ISP_HandlerType* ISPx,UINT8_T *pVal)
{
	//---Flashÿҳ����
	ISPx->msgFlashPerPageWordSize= *(pVal++);
	ISPx->msgFlashPerPageWordSize=(ISPx->msgFlashPerPageWordSize<<8)+ *(pVal++);
	//---Eepromÿҳ�ֽ���
	ISPx->msgEerpomPerPageByteSize= *(pVal++);
	ISPx->msgEerpomPerPageByteSize = (ISPx->msgEerpomPerPageByteSize<<8)+*(pVal++);
	//---Eeprom�Ƿ�֧��ҳ���ģʽ
	ISPx->msgEepromIsPageMode= *(pVal++);
	return OK_0;
}
