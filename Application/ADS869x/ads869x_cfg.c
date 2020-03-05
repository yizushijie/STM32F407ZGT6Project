#include "ads869x_cfg.h"

//===ȫ�ֱ�������
ADS869X_HandleType   g_ADS869XDevice0 = { 0 };
pADS869X_HandleType  pADS869XDevice0 = &g_ADS869XDevice0;

//===ͳһ�����ֽ�����
UINT8_T(*ADS869X_SPI_SEND_CMD)(ADS869X_HandleType *, UINT8_T, UINT8_T *);
//===ͳһ������������
UINT8_T(*ADS869X_SPI_SEND_ARRAY)(ADS869X_HandleType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device0_Init(ADS869X_HandleType *ADS869x)
{
	//---��λ�ź�
	ADS869x->msgHWRST.msgPort = NULL;
	ADS869x->msgHWRST.msgBit = LL_GPIO_PIN_0;
	//---GPIOʱ��ʹ��
	#ifndef  USE_FULL_GPIO
	if (ADS869x->msgHWRST.msgPort != NULL)
	{
		GPIOTask_Clock(ADS869x->msgHWRST.msgPort, PERIPHERAL_CLOCK_ENABLE);
	}
	#endif
	//---SPI1�ӿ�
	//---PA4------ > SPI1_NSS
	//---PA5------ > SPI1_SCK
	//---PA6------ > SPI1_MISO
	//---PA7------ > SPI1_MOSI
	
	//---SPI2�ӿ�
	//---PB12------ > SPI2_NSS
	//---PB13------ > SPI2_SCK
	//---PB14------ > SPI2_MISO
	//---PB15------ > SPI2_MOSI

	//---CS
	ADS869x->msgSPI.msgCS.msgPort = GPIOB;				//GPIOA;
	ADS869x->msgSPI.msgCS.msgBit  = LL_GPIO_PIN_12;		//LL_GPIO_PIN_4;
	//---SCK
	ADS869x->msgSPI.msgSCK.msgPort = GPIOB;				//GPIOA;
	ADS869x->msgSPI.msgSCK.msgBit = LL_GPIO_PIN_13;		//LL_GPIO_PIN_5;
	//---MISO  SDO
	ADS869x->msgSPI.msgMISO.msgPort = GPIOB;			//GPIOA;
	ADS869x->msgSPI.msgMISO.msgBit  = LL_GPIO_PIN_14;	//LL_GPIO_PIN_6;
	//---MOSI SDI
	ADS869x->msgSPI.msgMOSI.msgPort = GPIOB;			//GPIOA;
	ADS869x->msgSPI.msgMOSI.msgBit  = LL_GPIO_PIN_15;	//LL_GPIO_PIN_7;
	//---GPIO������
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;															//---����ʹ��
	//---��ʼ��RST
	if (ADS869x->msgHWRST.msgPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS869x->msgHWRST.msgBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS869x->msgHWRST.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS869x->msgHWRST.msgPort, ADS869x->msgHWRST.msgBit);
	}
	//---����ģʽ
	#ifndef USE_MCU_STM32F1
		//---�˿ڸ���ģʽ
		ADS869x->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI���
		ADS869x->msgSPI.pMsgSPIx = SPI2;//SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI��Э��
		ADS869x->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif
	UINT8_T i = 0;
	//---�ο���ѹ����
	ADS869x->msgREFPowerUV = ADS869X_REF_POWER_UV;
	for (i = 0; i < ADS869X_CHANNEL_MAX; i++)
	{
		ADS869x->msgChannelRange[i] = 0;
		ADS869x->msgPositive[i] = 0;
		ADS869x->msgChannelNowADCResult[i] = 0;
		ADS869x->msgChannelOldADCResult[i] = 0;
		ADS869x->msgChannelPowerResult[i] = 0;
		ADS869X_SPI_ChannelRange(ADS869x, i);
	}
	ADS869x->msgReadyOK = 0;
	ADS869x->msgInitRetryCount = 3;
	ADS869x->msgChipID = 0;
	//---Ĭ����������
	ADS869x->msgFeature = 0x28;
	//---Ĭ����0xFF
	ADS869x->msgAutoSeqEn = 0xFF;
	//---����������
	ADS869x->msgSPI.msgPluseWidth = 2;
	//---ʱ�ӿ���Ϊ�͵�ƽ
	ADS869x->msgSPI.msgCPOL = 0;
	//---���ݲ����ڵڶ���ʱ�ӱ���
	ADS869x->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device1_Init(ADS869X_HandleType *ADS869x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device2_Init(ADS869X_HandleType *ADS869x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_SendCmd(ADS869X_HandleType *ADS869x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS869x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_SendArray(ADS869X_HandleType* ADS869x, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS869x->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_SendCmd(ADS869X_HandleType *ADS869x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS869x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_SendArray(ADS869X_HandleType* ADS869x, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS869x->msgSPI), pWVal, pRVal,length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_Init(ADS869X_HandleType *ADS869x)
{
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ADS869x->msgSPI));
	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8λ����
	//---ʱ�Ӽ��Ե�����
	if (ADS869x->msgSPI.msgCPOL == 0)
	{
		//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS869x->msgSPI.msgSCK.msgPort, ADS869x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---���ݲ�����ʱ�ӱ���λ��
	if (ADS869x->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---ϵͳʱ��2��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	//---��ʼ����ѯ��ʽ��SPI
	SPITask_MHW_PollMode_Init(&(ADS869x->msgSPI), SPI_InitStruct);
	//---����ͺ���
	ADS869X_SPI_SEND_CMD = ADS869X_SPI_HW_SendCmd;
	ADS869X_SPI_SEND_ARRAY = ADS869X_SPI_HW_SendArray;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_Init(ADS869X_HandleType *ADS869x)
{
	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ADS869x->msgSPI));
	//---ʱ���ߵļ���
	if (ADS869x->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgSCK.msgPort, ADS869x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgSCK.msgPort, ADS869x->msgSPI.msgSCK.msgBit);
	}
	//---����ͺ���
	ADS869X_SPI_SEND_CMD = ADS869X_SPI_SW_SendCmd;
	ADS869X_SPI_SEND_ARRAY = ADS869X_SPI_SW_SendArray;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_Init(ADS869X_HandleType *ADS869x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ADS869x != NULL) && (ADS869x == ADS869X_TASK_ONE))
	{
		ADS869X_SPI_Device0_Init(ADS869x);
	}
	else if ((ADS869x != NULL) && (ADS869x == ADS869X_TASK_TWO))
	{
		ADS869X_SPI_Device1_Init(ADS869x);
	}
	else if ((ADS869x != NULL) && (ADS869x == ADS869X_TASK_THREE))
	{
		ADS869X_SPI_Device2_Init(ADS869x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж�Ӳ�����������ʽ
	(isHW != 0) ? (ADS869X_SPI_HW_Init(ADS869x)) : (ADS869X_SPI_SW_Init(ADS869x));
	//---ע��ms��ʱʱ��
	(pFuncDelayms != NULL) ? (ADS869x->pMsgDelayms = pFuncDelayms) : (ADS869x->pMsgDelayms = DelayTask_ms);
	//---ע��us��ʱ����
	(pFuncDelayus != NULL) ? (ADS869x->msgSPI.pMsgDelayus = pFuncDelayus) : (ADS869x->msgSPI.pMsgDelayus = DelayTask_us);
	//---ע��δ���
	(pFuncTimerTick != NULL) ? (ADS869x->msgSPI.pMsgTimeTick = pFuncTimerTick) : (ADS869x->msgSPI.pMsgTimeTick = SysTickTask_GetTick);
	//---����ADS869X
	return ADS869X_SPI_ConfigInit(ADS869x,0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ���ʼ��������ͬһ��SPI�˿ڹ��ض���豸���ٶȲ�һ�µ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_AutoInit(ADS869X_HandleType* ADS869x)
{
	if (ADS869x->msgSPI.msgHwMode != 0)
	{
		//---�����ʼ��
		ADS869X_SPI_HW_Init(ADS869x);
	}
	else
	{
		//---Ӳ����ʼ��
		ADS869X_SPI_SW_Init(ADS869x);
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
UINT8_T ADS869X_SPI_AutoDeInit(ADS869X_HandleType* ADS869x)
{
	//---ע����ǰ����������
  return	SPITask_DeInit(&(ADS869x->msgSPI),0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�дADS869X����Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteCommandReg(ADS869X_HandleType *ADS869x, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, wTemp, NULL, 2);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Program Registerд����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteProgramReg(ADS869X_HandleType *ADS869x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, wTemp, NULL, 2);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Program Register������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadProgramReg(ADS869X_HandleType *ADS869x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, wTemp, rTemp, 3);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}

	//---���ݿ���
	pVal[0] = rTemp[1];
	pVal[1] = rTemp[2];

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadCommandBack(ADS869X_HandleType* ADS869x, UINT8_T* pVal,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return=ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_CMD_READ_BACK, pVal);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�����������ѡ�е�״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_NO_OP(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_NO_OP);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_STDBY(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_STDBY);
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_PWRDN(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_PWR_DN);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_HardReset(ADS869X_HandleType *ADS869x)
{
	if (ADS869x->msgHWRST.msgPort!=NULL)
	{
		GPIO_OUT_0(ADS869x->msgHWRST.msgPort, ADS869x->msgHWRST.msgBit);
		ADS869x->pMsgDelayms(1);
		GPIO_OUT_1(ADS869x->msgHWRST.msgPort, ADS869x->msgHWRST.msgBit);
		ADS869x->pMsgDelayms(1);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_SoftReset(ADS869X_HandleType *ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_RST);
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��豸��λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_Reset(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	if (ADS869x->msgHWRST.msgPort != NULL)
	{
		_return = ADS869X_SPI_HardReset(ADS869x);
	}
	else
	{
		_return = ADS869X_SPI_SoftReset(ADS869x,isAutoInit);
	}
	ADS869x->msgReadyOK = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_AUTORST(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_AUTO_RST);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;

}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������ֶ�ɨ��ͨ��
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ManualChannel(ADS869X_HandleType* ADS869x,UINT16_T manualCHCmd, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, manualCHCmd);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChipID(ADS869X_HandleType* ADS869x, UINT8_T devid, UINT8_T isAutoInit)
{
	devid <<= 6;
	ADS869x->msgChipID = (devid & 0xC0) | ADS869x->msgFeature; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, ADS869x->msgChipID);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChipID(ADS869X_HandleType* ADS869x, UINT8_T *pDevID, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, pDevID);
	*pDevID &= 0xC0;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�У���豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_CheckChipID(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = OK_0;
	_return = ADS869X_SPI_ReadChipID(ADS869x, &tempChipID,isAutoInit);
	//---У���ȡ��ID��Ϣ
	if (tempChipID!=ADS869x->msgChipID)
	{
		_return += ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�̽���豸�Ƿ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_DetectionDevice(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = OK_0;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return=ADS869X_SPI_ReadProgramReg(pADS869XDevice0, ADS869X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---У�����Ƿ���ȷ
	if (tempAutoSeqEn[1]!=ADS869x->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---У���豸��ID��Ϣ
		_return = ADS869X_SPI_CheckChipID(ADS869x,0);
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteAUTOSEQEN(ADS869X_HandleType* ADS869x, UINT8_T seq, UINT8_T isAutoInit)
{
	ADS869x->msgAutoSeqEn = seq;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_AUTO_SEQ_EN, seq);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadAUTOSEQEN(ADS869X_HandleType* ADS869x, UINT8_T *pAutoSeqEn, UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return =ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS869x->msgAutoSeqEn)
		{
			*pAutoSeqEn = tempAutoSeqEn[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChannelPWRDN(ADS869X_HandleType* ADS869x, UINT8_T ch, UINT8_T isAutoInit)
{
	ADS869x->msgChannelPWRDN = ch; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_CH_PWR_DN, ch);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChannelPWRDN(ADS869X_HandleType* ADS869x, UINT8_T *pPWRDN, UINT8_T isAutoInit)
{
	UINT8_T tempPWRDN[2] = { 0 }; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS869x->msgChannelPWRDN)
		{
			*pPWRDN = tempPWRDN[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteFeature(ADS869X_HandleType* ADS869x, UINT8_T feature, UINT8_T isAutoInit)
{
	ADS869x->msgFeature = (feature&0x3F)|ADS869x->msgChipID;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, feature);
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadFeature(ADS869X_HandleType* ADS869x, UINT8_T *pFeature, UINT8_T isAutoInit)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS869x->msgFeature)
		{
			*pFeature = tempFeature[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chReg, UINT8_T range, UINT8_T isAutoInit)
{
	UINT8_T ch = ADS869X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS869X_PROG_REG_CH0_SET_RANGE:
			ADS869x->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS869X_PROG_REG_CH1_SET_RANGE:
			ADS869x->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS869X_PROG_REG_CH2_SET_RANGE:
			ADS869x->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS869X_PROG_REG_CH3_SET_RANGE:
			ADS869x->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS869X_PROG_REG_CH4_SET_RANGE:
			ADS869x->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS869X_PROG_REG_CH5_SET_RANGE:
			ADS869x->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS869X_PROG_REG_CH6_SET_RANGE:
			ADS869x->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS869X_PROG_REG_CH7_SET_RANGE:
			ADS869x->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}

	//---ÿ��ͨ�������̵�����
	ADS869X_SPI_ChannelRange(ADS869x, ch);
	//---����ͨ��������
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, chReg, range);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;

}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chReg, UINT8_T *pRange, UINT8_T isAutoInit)
{
	UINT8_T ch = ADS869X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS869X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS869X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS869X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS869X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS869X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS869X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS869X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS869X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---��ȡͨ��������
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, chReg, tempChannelRange);
	//---�ж϶�ȡ���
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS869x->msgChannelRange[ch])
		{
			*pRange = tempChannelRange[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹuv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteREFPowerUV(ADS869X_HandleType* ADS869x, UINT32_T refUV)
{
	ADS869x->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ο���ѹ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS869X_SPI_ReadREFPowerUV(ADS869X_HandleType* ADS869x, UINT32_T refUV)
{
	return ADS869x->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹmv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteREFPowerMV(ADS869X_HandleType* ADS869x, UINT32_T refMV)
{
	ADS869x->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ÿͨ�������̺��������ֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS869X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS869x->msgChannelRange[chIndex])
		{
			//---����1.25����VREF
			case ADS869X_RANGE_5120MV_5120MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 1250);//5120000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = (ADS869x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS869X_ADC_SAMPLE_BITS); //39.0625;
				break;
			//---����0.625����VREF
			case ADS869X_RANGE_2560MV_2560MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 625); //2560000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = (ADS869x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1 << ADS869X_ADC_SAMPLE_BITS); //19.53125;
				break;
			//---��2.5����VREF
			case ADS869X_RANGE_0MV_10240MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 2500);//10240000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = ADS869x->msgChannelRangeFullUVX1000[chIndex] / (1 << ADS869X_ADC_SAMPLE_BITS); //39.0625;
				break;
			//---��1.25����VREF
			case ADS869X_RANGE_0MV_5120MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV* 1250);//5120000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = ADS869x->msgChannelRangeFullUVX1000[chIndex] / (1 << ADS869X_ADC_SAMPLE_BITS); //19.53125;
				break;
			//---����2.5����VREF
			case ADS869X_RANGE_10240MV_10240MV:
			default:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 2500);//10240000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = (ADS869x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1 << ADS869X_ADC_SAMPLE_BITS); //78.125
				break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ��ADC�Ĳɼ��������ADCͨ���ĵ�ѹֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_CalcChannelPower(ADS869X_HandleType* ADS869x, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---����������
	ADS869x->msgPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---�ж��Ƿ���Ҫ�����ֵ
	if (isCalcDelta != 0)
	{
		//---��ȡ�ϴκͱ��εĲ�������ľ��Բ�ֵ
		adcDelta = ABS_SUB(ADS869x->msgChannelNowADCResult[chIndex], ADS869x->msgChannelOldADCResult[chIndex]);
		//---������ݲ�����Ͽ�ʼ
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS869x->msgChannelOldADCResult[chIndex] = MAX(ADS869x->msgChannelNowADCResult[chIndex], ADS869x->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS869x->msgChannelNowADCResult[chIndex] > ADS869x->msgChannelOldADCResult[chIndex])
			{
				ADS869x->msgChannelOldADCResult[chIndex] = ADS869x->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS869x->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else if (ADS869x->msgChannelNowADCResult[chIndex] < ADS869x->msgChannelOldADCResult[chIndex])
			{
				ADS869x->msgChannelOldADCResult[chIndex] -= 1;
			}
			else
			{
				ADS869x->msgChannelOldADCResult[chIndex] = MAX(ADS869x->msgChannelNowADCResult[chIndex], ADS869x->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS869x->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS869x->msgChannelNowADCResult[chIndex];
			ADS869x->msgChannelOldADCResult[chIndex] = ADS869x->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS869x->msgChannelNowADCResult[chIndex];
	}
	calcPower &= ((1<< ADS869X_ADC_SAMPLE_BITS)-1);
	//---������ݲ�����Ͻ���
	//---��������ת��Ϊģ����
	calcPower *= ADS869x->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---�ж�ADC������������˫���Ի��ǵ�����
	if (ADS869x->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if ((ADS869x->msgChannelNowADCResult[chIndex] & (1<< (ADS869X_ADC_SAMPLE_BITS-1))) != 0)
		{
			ADS869x->msgPositive[chIndex] = 2;
			ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS869x->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS869x->msgPositive[chIndex] = 1;
			ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS869x->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS869x->msgPositive[chIndex] = 2;
		ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---�����������
	if (ADS869x->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS869x->msgChannelPowerResult[chIndex];
		adcPower *= ADS869x->msgADCKP[chIndex];
		if (adcPower< ADS869x->msgADCDelta[chIndex])
		{
			ADS869x->msgPositive[chIndex] = 1;
			adcPower = (ADS869x->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS869x->msgADCDelta[chIndex];
		}
		ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ��ͨ�����е�ADת������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_GetAutoRSTResult(ADS869X_HandleType *ADS869x, UINT8_T chNum, UINT8_T isAutoInit)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[5] = { 0 };
	UINT8_T adcWTemp[5] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;

	//---��ȡͨ��������
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS869x->msgReadyOK == 1)
	{
		_return = ADS869X_SPI_ConfigInit(ADS869x,0);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}

	//---�����Զ�ɨ��ģʽ
	_return =ADS869X_SPI_AUTORST(ADS869x,0);

	//---ɨ��ͨ���Ľ��
	for (i = 0; i < chNum; i++)
	{
		//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---׼����ȡ����
			if (ADS869x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
			}
			_return=ADS869X_SPI_SEND_ARRAY(ADS869x, adcWTemp, adcRTemp, 5);
			//---�������ݵĶ�ȡ
			if (ADS869x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
			}
			//---�����ȡ������
			ADS869x->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS869x->msgChannelNowADCResult[i] = (ADS869x->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			ADS869x->msgChannelNowADCResult[i] = (ADS869x->msgChannelNowADCResult[i] << 8) + adcRTemp[4];
			ADS869x->msgChannelNowADCResult[i] >>= ADS869X_DATA_SAMPLE_BITS;
			//---����������
			ADS869X_SPI_CalcChannelPower(ADS869x, i,0);
		}
		rstMode >>= 1;
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_GetAutoRSTNSampleResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;
	//---����������
	UINT32_T adcSampleTemp[ADS869X_CHANNEL_MAX][ADS869X_N_SAMPLE_COUNT] = { 0 };

	//---��ȡͨ��������
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---��ȡ�������
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		//---��ȡ�������
		_return = ADS869X_SPI_GetAutoRSTResult(ADS869x, chNum,0);
		//---�������ݰ���
		for (j=0;j< ADS869X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS869x->msgChannelNowADCResult[j];
		}
		//---У������
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---�������ݰ���
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
			if (rstMode & 0x01)
			{
				//---������������
				AscSortDoubleWord(adcSampleTemp[j], ADS869X_N_SAMPLE_COUNT);
				//---�����ֵ
				ADS869x->msgChannelNowADCResult[j] = CalcAvgDoubleWordFromIndex(adcSampleTemp[j], (ADS869X_N_SAMPLE_COUNT - 2), 2);
				//---��������ĵ�ѹֵ
				ADS869X_SPI_CalcChannelPower(ADS869x, j,1);
			}
			rstMode >>= 1;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_KalmanFilterGetAutoRSTNSampleResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;
	//---����������
	UINT32_T adcSampleTemp[ADS869X_CHANNEL_MAX][ADS869X_N_SAMPLE_COUNT] = { 0 };

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---�������ṹ
	KalmanOneFilter_HandleType kalmanFilterX;
	//---��ȡ�������
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		//---��ȡ�������
		_return = ADS869X_SPI_GetAutoRSTResult(ADS869x, chNum,0);
		//---�������ݰ���
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			adcSampleTemp[j][i] = ADS869x->msgChannelNowADCResult[j];
		}
		//---У������
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---�������ݰ���
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
			if (rstMode & 0x01)
			{
				KalmanOneFilter_Init(&kalmanFilterX, adcSampleTemp[j][0], 5e2);
				for (i = 1; i < ADS869X_N_SAMPLE_COUNT; i++)
				{
					//---�������˲�֮��Ľ��
					ADS869x->msgChannelNowADCResult[j] = (UINT32_T)KalmanOneFilter_Filter(&kalmanFilterX, adcSampleTemp[j][i]);
				}
				//---��������ĵ�ѹֵ
				ADS869X_SPI_CalcChannelPower(ADS869x, j, 0);
			}
			rstMode >>= 1;
		}
	}
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�յ�ɨ��ͨ����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_GetManualChannelResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[5] = { 0 };
	UINT8_T adcWTemp[5] = { 0 };
	UINT8_T adcChannel = 0;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS869x->msgReadyOK==1)
	{
		_return=ADS869X_SPI_ConfigInit(ADS869x,0);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---�����ֶ�ɨ��ͨ��
	_return = ADS869X_SPI_ManualChannel(ADS869x, manualChannel,0);
	//---׼����ȡ���õ�ɨ��ͨ����ֵ
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	//---��ȡADC�����Ľ��
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, adcWTemp, adcRTemp, 5);
	//---������ȡ���õ�ɨ��ͨ����ֵ
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	//---ͨ����ת��
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---�ж��Ƿ���AUXͨ������
	if (adcChannel<8)
	{
		ADS869x->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS869x->msgChannelNowADCResult[adcChannel] = (ADS869x->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		ADS869x->msgChannelNowADCResult[adcChannel] = (ADS869x->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[4];
		ADS869x->msgChannelNowADCResult[adcChannel] >>= ADS869X_DATA_SAMPLE_BITS;
		//---����������
		ADS869X_SPI_CalcChannelPower(ADS869x, adcChannel,0);
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��ֶ�ͨ������N�εĲ��Խ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_GetManualChannelNSampleResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������
	UINT32_T adcSampleTemp[ADS869X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡADC����ͨ�������
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---��ȡ�������
	for ( i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS869X_SPI_GetManualChannelResult(ADS869x, manualChannel,0);
		adcSampleTemp[i] = ADS869x->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---������������
		AscSortDoubleWord(adcSampleTemp, ADS869X_N_SAMPLE_COUNT);
		//---�����ֵ
		ADS869x->msgChannelNowADCResult[adcChannelIndex] = CalcAvgDoubleWordFromIndex(adcSampleTemp, (ADS869X_N_SAMPLE_COUNT - 4), 4);
		//---��������ĵ�ѹֵ
		ADS869X_SPI_CalcChannelPower(ADS869x, adcChannelIndex,1);
	}
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}


	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��������˲���ʽ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������
	UINT32_T adcSampleTemp[ADS869X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡADC����ͨ�������
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---�������ṹ
	KalmanOneFilter_HandleType kalmanFilterX;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---��ȡ�������
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS869X_SPI_GetManualChannelResult(ADS869x, manualChannel,0);
		adcSampleTemp[i] = ADS869x->msgChannelNowADCResult[adcChannelIndex];
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		KalmanOneFilter_Init(&kalmanFilterX, adcSampleTemp[0], 5e2);
		for (i=1;i< ADS869X_N_SAMPLE_COUNT; i++)
		{
			//---�������˲�֮��Ľ��
			ADS869x->msgChannelNowADCResult[adcChannelIndex] =(UINT32_T) KalmanOneFilter_Filter(&kalmanFilterX, adcSampleTemp[i]);
		}
		//---��������ĵ�ѹֵ
		ADS869X_SPI_CalcChannelPower(ADS869x, adcChannelIndex, 1);
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�У׼ͨ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_CalibrationChannelErr(ADS869X_HandleType* ADS869x)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;
	for (i = 0; i < ADS869X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1�Ű����
				//ADS869x->msgADCKP[i] = 1.013216;
				//ADS869x->msgADCDelta[i] = 27130;

				//---2�Ű����
				ADS869x->msgADCKP[i] = 0;//1.013216;
				ADS869x->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1�Ű����
				//ADS869x->msgADCKP[i] = 1.0129;
				//ADS869x->msgADCDelta[i] = 25870;

				//---2�Ű����
				ADS869x->msgADCKP[i] = 0;//1.0129;
				ADS869x->msgADCDelta[i] = 27070;
			}
			
		}
		rstMode >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ʼ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ConfigInit(ADS869X_HandleType* ADS869x,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;

	if (isAutoInit!=0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	if (ADS869x->msgInitRetryCount==0)
	{
		ADS869x->msgInitRetryCount = 1;
	}

	//---ѭ����γ�ʼ���豸
	for (i=0;i< ADS869x->msgInitRetryCount;i++)
	{
		//---��λоƬ
		_return = ADS869X_SPI_Reset(ADS869x,0);
		//---У��
		if (_return == OK_0)
		{
			//---�豸��������
			_return = ADS869X_SPI_WriteFeature(ADS869x, 0x28,0);
			//---У��
			if (_return == OK_0)
			{
				//---��ȡ�豸������
				_return = ADS869X_SPI_ReadFeature(ADS869x, tempBuffer,0);
				//---У��
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}

	//---����ɨ�跽ʽ
	_return = ADS869X_SPI_WriteAUTOSEQEN(ADS869x, 0xF0,0);
	//---��ȡ���õ�ֵ
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_AUTO_SEQ_EN, tempBuffer);

	//---�ж�У��
	if (ADS869x->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS869x->msgReadyOK = 1;
	}
	else
	{
		//---����ͨ��������
		ADS869X_SPI_WriteChannelRange(ADS869x, ADS869X_PROG_REG_CH0_SET_RANGE, ADS869X_RANGE_0MV_5120MV,0);
		ADS869X_SPI_WriteChannelRange(ADS869x, ADS869X_PROG_REG_CH1_SET_RANGE, ADS869X_RANGE_0MV_5120MV,0);
		ADS869X_SPI_WriteChannelRange(ADS869x, ADS869X_PROG_REG_CH2_SET_RANGE, ADS869X_RANGE_0MV_5120MV,0);
		//---���ù���ģʽ
		ADS869X_SPI_AUTORST(ADS869x,0);
	}
	ADS869X_SPI_CalibrationChannelErr(ADS869x);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}